/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef OpsTask_DEFINED
#define OpsTask_DEFINED

#include <skia/core/SkMatrix.h>
#include <skia/core/SkRefCnt.h>
#include <skia/core/SkSpan.h>
#include <skia/core/SkStrokeRec.h>
#include <skia/core/SkTypes.h>
#include <skia/gpu/GrRecordingContext.h>
#include <skia/private/SkTArray.h>
#include <skia/private/SkTDArray.h>
#include "src/core/SkArenaAlloc.h"
#include "src/core/SkClipStack.h"
#include "src/core/SkStringUtils.h"
#include "src/core/SkTLazy.h"
#include "src/gpu/GrAppliedClip.h"
#include "src/gpu/GrDstProxyView.h"
#include "src/gpu/GrGeometryProcessor.h"
#include "src/gpu/GrProcessorSet.h"
#include "src/gpu/GrRenderTask.h"
#include "src/gpu/ops/GrOp.h"

class GrAuditTrail;
class GrCaps;
class GrClearOp;
class GrGpuBuffer;
class GrRenderTargetProxy;
class OpsTaskTestingAccess;

namespace skgpu::v1 {

class SurfaceDrawContext;

class OpsTask : public GrRenderTask {
public:
    // Manage the arenas life time by maintaining are reference to it.
    SK_API OpsTask(GrDrawingManager*, GrSurfaceProxyView, GrAuditTrail*, sk_sp<GrArenas>);
    SK_API ~OpsTask() override;

    OpsTask* asOpsTask() override { return this; }

    bool isEmpty() const { return fOpChains.empty(); }
    bool usesMSAASurface() const { return fUsesMSAASurface; }
    GrXferBarrierFlags renderPassXferBarriers() const { return fRenderPassXferBarriers; }

    /**
     * Empties the draw buffer of any queued up draws.
     */
    SK_API void endFlush(GrDrawingManager*) override;

    SK_API void onPrePrepare(GrRecordingContext*) override;
    /**
     * Together these two functions flush all queued up draws to GrCommandBuffer. The return value
     * of onExecute() indicates whether any commands were actually issued to the GPU.
     */
    SK_API void onPrepare(GrOpFlushState* flushState) override;
    SK_API bool onExecute(GrOpFlushState* flushState) override;

    void addSampledTexture(GrSurfaceProxy* proxy) {
        // This function takes a GrSurfaceProxy because all subsequent uses of the proxy do not
        // require the specifics of GrTextureProxy, so this avoids a number of unnecessary virtual
        // asTextureProxy() calls. However, sampling the proxy implicitly requires that the proxy
        // be a texture. Eventually, when proxies are a unified type with flags, this can just
        // assert that capability.
        SkASSERT(proxy->asTextureProxy());
        fSampledProxies.push_back(proxy);
    }

    SK_API void addOp(GrDrawingManager*, GrOp::Owner, GrTextureResolveManager, const GrCaps&);

    SK_API void addDrawOp(GrDrawingManager*, GrOp::Owner, bool usesMSAA, const GrProcessorSet::Analysis&,
                   GrAppliedClip&&, const GrDstProxyView&, GrTextureResolveManager, const GrCaps&);

    SK_API void discard();

    enum class CanDiscardPreviousOps : bool {
        kYes = true,
        kNo = false
    };

    // Perform book-keeping for a fullscreen clear, regardless of how the clear is implemented later
    // (i.e. setColorLoadOp(), adding a ClearOp, or adding a FillRectOp that covers the device).
    // Returns true if the clear can be converted into a load op (barring device caps).
    SK_API bool resetForFullscreenClear(CanDiscardPreviousOps);

    // Must only be called if native color buffer clearing is enabled.
    SK_API void setColorLoadOp(GrLoadOp op, std::array<float, 4> color = {0, 0, 0, 0});

    // Returns whether the given opsTask can be appended at the end of this one.
    SK_API bool canMerge(const OpsTask*) const;

    // Merge as many opsTasks as possible from the head of 'tasks'. They should all be
    // renderPass compatible. Return the number of tasks merged into 'this'.
    SK_API int mergeFrom(SkSpan<const sk_sp<GrRenderTask>> tasks);

#ifdef SK_DEBUG
    int numClips() const override { return fNumClips; }
    SK_API void visitProxies_debugOnly(const GrVisitProxyFunc&) const override;
#endif

#if GR_TEST_UTILS
    SK_API void dump(const SkString& label,
              SkString indent,
              bool printDependencies,
              bool close) const override;
    const char* name() const final { return "Ops"; }
    int numOpChains() const { return fOpChains.count(); }
    const GrOp* getChain(int index) const { return fOpChains[index].head(); }
#endif

protected:
    enum class StencilContent {
        kDontCare,
        kUserBitsCleared,  // User bits: cleared
                           // Clip bit: don't care (Ganesh always pre-clears the clip bit.)
        kPreserved
    };

    // Lets the caller specify what the content of the stencil buffer should be at the beginning
    // of the render pass.
    //
    // When requesting kClear: Tilers will load the stencil buffer with a "clear" op; non-tilers
    // will clear the stencil on first load, and then preserve it on subsequent loads. (Preserving
    // works because SurfaceDrawContexts are required to leave the user bits in a cleared state
    // once finished.)
    //
    // NOTE: initialContent must not be kClear if caps.performStencilClearsAsDraws() is true.
    void setInitialStencilContent(StencilContent initialContent) {
        fInitialStencilContent = initialContent;
    }

    SK_API void recordOp(GrOp::Owner, bool usesMSAA, GrProcessorSet::Analysis, GrAppliedClip*,
                  const GrDstProxyView*, const GrCaps&);

    SK_API ExpectedOutcome onMakeClosed(GrRecordingContext*, SkIRect* targetUpdateBounds) override;

private:
    bool isColorNoOp() const {
        // TODO: GrLoadOp::kDiscard (i.e., storing a discard) should also be grounds for skipping
        // execution. We currently don't because of Vulkan. See http://skbug.com/9373.
        return fOpChains.empty() && GrLoadOp::kLoad == fColorLoadOp;
    }

    SK_API void deleteOps();

    // If a surfaceDrawContext splits its opsTask, it uses this method to guarantee stencil values
    // get preserved across its split tasks.
    void setMustPreserveStencil() { fMustPreserveStencil = true; }

    // Prevents this opsTask from merging backward. This is used by DMSAA when a non-multisampled
    // opsTask cannot be promoted to MSAA, or when we split a multisampled opsTask in order to
    // resolve its texture.
    void setCannotMergeBackward() { fCannotMergeBackward = true; }

    class OpChain {
    public:
        SK_API OpChain(GrOp::Owner, GrProcessorSet::Analysis, GrAppliedClip*, const GrDstProxyView*);
        ~OpChain() {
            // The ops are stored in a GrMemoryPool and must be explicitly deleted via the pool.
            SkASSERT(fList.empty());
        }

        OpChain(const OpChain&) = delete;
        OpChain& operator=(const OpChain&) = delete;
        OpChain(OpChain&&) = default;
        OpChain& operator=(OpChain&&) = default;

        SK_API void visitProxies(const GrVisitProxyFunc&) const;

        GrOp* head() const { return fList.head(); }

        GrAppliedClip* appliedClip() const { return fAppliedClip; }
        const GrDstProxyView& dstProxyView() const { return fDstProxyView; }
        const SkRect& bounds() const { return fBounds; }

        // Deletes all the ops in the chain.
        SK_API void deleteOps();

        // Attempts to move the ops from the passed chain to this chain at the head. Also attempts
        // to merge ops between the chains. Upon success the passed chain is empty.
        // Fails when the chains aren't of the same op type, have different clips or dst proxies.
        SK_API bool prependChain(OpChain*, const GrCaps&, SkArenaAlloc* opsTaskArena, GrAuditTrail*);

        // Attempts to add 'op' to this chain either by merging or adding to the tail. Returns
        // 'op' to the caller upon failure, otherwise null. Fails when the op and chain aren't of
        // the same op type, have different clips or dst proxies.
        SK_API GrOp::Owner appendOp(GrOp::Owner op, GrProcessorSet::Analysis, const GrDstProxyView*,
                             const GrAppliedClip*, const GrCaps&, SkArenaAlloc* opsTaskArena,
                             GrAuditTrail*);

        bool shouldExecute() const {
            return SkToBool(this->head());
        }

    private:
        class List {
        public:
            List() = default;
            SK_API List(GrOp::Owner);
            SK_API List(List&&);
            SK_API List& operator=(List&& that);

            bool empty() const { return !SkToBool(fHead); }
            GrOp* head() const { return fHead.get(); }
            GrOp* tail() const { return fTail; }

            GrOp::Owner popHead();
            GrOp::Owner removeOp(GrOp* op);
            SK_API void pushHead(GrOp::Owner op);
            SK_API void pushTail(GrOp::Owner);

            SK_API void validate() const;

        private:
            GrOp::Owner fHead{nullptr};
            GrOp* fTail{nullptr};
        };

        SK_API void validate() const;

        SK_API bool tryConcat(List*, GrProcessorSet::Analysis, const GrDstProxyView&, const GrAppliedClip*,
                       const SkRect& bounds, const GrCaps&, SkArenaAlloc* opsTaskArena,
                       GrAuditTrail*);
        SK_API static List DoConcat(List, List, const GrCaps&, SkArenaAlloc* opsTaskArena, GrAuditTrail*);

        List fList;
        GrProcessorSet::Analysis fProcessorAnalysis;
        GrDstProxyView fDstProxyView;
        GrAppliedClip* fAppliedClip;
        SkRect fBounds;
    };

    SK_API void onMakeSkippable() override;

    SK_API bool onIsUsed(GrSurfaceProxy*) const override;

    SK_API void gatherProxyIntervals(GrResourceAllocator*) const override;

    SK_API void forwardCombine(const GrCaps&);

    // Remove all ops, proxies, etc. Used in the merging algorithm when tasks can be skipped.
    SK_API void reset();

    friend class ::OpsTaskTestingAccess;

    // The SDC and OpsTask have to work together to handle buffer clears. In most cases, buffer
    // clearing can be done natively, in which case the op list's load ops are sufficient. In other
    // cases, draw ops must be used, which makes the SDC the best place for those decisions. This,
    // however, requires that the SDC be able to coordinate with the op list to achieve similar ends
    friend class skgpu::v1::SurfaceDrawContext;

    GrAuditTrail* fAuditTrail;

    bool fUsesMSAASurface;
    GrSwizzle fTargetSwizzle;
    GrSurfaceOrigin fTargetOrigin;

    GrLoadOp fColorLoadOp = GrLoadOp::kLoad;
    std::array<float, 4> fLoadClearColor = {0, 0, 0, 0};
    StencilContent fInitialStencilContent = StencilContent::kDontCare;
    bool fMustPreserveStencil = false;
    bool fCannotMergeBackward = false;

    uint32_t fLastClipStackGenID = SK_InvalidUniqueID;
    SkIRect fLastDevClipBounds;
    int fLastClipNumAnalyticElements;

    GrXferBarrierFlags fRenderPassXferBarriers = GrXferBarrierFlags::kNone;

    // For ops/opsTask we have mean: 5 stdDev: 28
    SkSTArray<25, OpChain> fOpChains;

    sk_sp<GrArenas> fArenas;
    SkDEBUGCODE(int fNumClips;)

    // TODO: We could look into this being a set if we find we're adding a lot of duplicates that is
    // causing slow downs.
    SkTArray<GrSurfaceProxy*, true> fSampledProxies;

    SkRect fTotalBounds = SkRect::MakeEmpty();
    SkIRect fClippedContentBounds = SkIRect::MakeEmpty();
};

} // namespace skgpu::v1

#endif // OpsTask_DEFINED
