/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDrawingManager_DEFINED
#define GrDrawingManager_DEFINED

#include <skia/core/SkSpan.h>
#include <skia/core/SkSurface.h>
#include <skia/private/SkTArray.h>
#include <skia/private/SkTHash.h>
#include "src/gpu/GrBufferAllocPool.h"
#include "src/gpu/GrDeferredUpload.h"
#include "src/gpu/GrHashMapWithCache.h"
#include "src/gpu/GrResourceCache.h"
#include "src/gpu/GrSurfaceProxy.h"

#if SK_GPU_V1
#include "src/gpu/v1/PathRenderer.h"
#include "src/gpu/v1/PathRendererChain.h"
#endif

// Enabling this will print out which path renderers are being chosen
#define GR_PATH_RENDERER_SPEW 0

class GrArenas;
class GrGpuBuffer;
class GrOnFlushCallbackObject;
class GrOpFlushState;
class GrRecordingContext;
class GrRenderTargetProxy;
class GrRenderTask;
class GrResourceAllocator;
class GrSemaphore;
class GrSurfaceProxyView;
class GrTextureResolveRenderTask;
class SkDeferredDisplayList;
namespace skgpu { namespace v1 {
    class OpsTask;
    class SoftwarePathRenderer;
}}

class GrDrawingManager {
public:
    SK_API ~GrDrawingManager();

    SK_API void freeGpuResources();

#if SK_GPU_V1
    // OpsTasks created at flush time are stored and handled different from the others.
    SK_API sk_sp<skgpu::v1::OpsTask> newOpsTask(GrSurfaceProxyView,
                                         sk_sp<GrArenas> arenas,
                                         bool flushTimeOpsTask);

    // Adds 'atlasTask' to the DAG and leaves it open.
    //
    // If 'previousAtlasTask' is provided, closes it and configures dependencies to guarantee
    // previousAtlasTask and all its users are completely out of service before atlasTask executes.
    SK_API void addAtlasTask(sk_sp<GrRenderTask> atlasTask, GrRenderTask* previousAtlasTask);
#endif

    // Create a render task that can resolve MSAA and/or regenerate mipmap levels on proxies. This
    // method will only add the new render task to the list. It is up to the caller to call
    // addProxy() on the returned object.
    SK_API GrTextureResolveRenderTask* newTextureResolveRenderTask(const GrCaps&);

    // Create a new render task that will cause the gpu to wait on semaphores before executing any
    // more RenderTasks that target proxy. It is possible for this wait to also block additional
    // work (even to other proxies) that has already been recorded or will be recorded later. The
    // only guarantee is that future work to the passed in proxy will wait on the semaphores to be
    // signaled.
    SK_API void newWaitRenderTask(sk_sp<GrSurfaceProxy> proxy,
                           std::unique_ptr<std::unique_ptr<GrSemaphore>[]>,
                           int numSemaphores);

    // Create a new render task which copies the pixels from the srcProxy into the dstBuffer. This
    // is used to support the asynchronous readback API. The srcRect is the region of the srcProxy
    // to be copied. The surfaceColorType says how we should interpret the data when reading back
    // from the source. DstColorType describes how the data should be stored in the dstBuffer.
    // DstOffset is the offset into the dstBuffer where we will start writing data.
    SK_API void newTransferFromRenderTask(sk_sp<GrSurfaceProxy> srcProxy, const SkIRect& srcRect,
                                   GrColorType surfaceColorType, GrColorType dstColorType,
                                   sk_sp<GrGpuBuffer> dstBuffer, size_t dstOffset);

    // Creates a new render task which copies a pixel rectangle from srcView into dstView. The src
    // pixels copied are specified by srcRect. They are copied to a rect of the same size in
    // dstProxy with top left at dstPoint. If the src rect is clipped by the src bounds then  pixel
    // values in the dst rect corresponding to the area clipped by the src rect are not overwritten.
    // This method is not guaranteed to succeed depending on the type of surface, formats, etc, and
    // the backend-specific limitations. On success the task is returned so that the caller may
    // mark it skippable if the copy is later deemed unnecessary.
    SK_API sk_sp<GrRenderTask> newCopyRenderTask(sk_sp<GrSurfaceProxy> src,
                                          SkIRect srcRect,
                                          sk_sp<GrSurfaceProxy> dst,
                                          SkIPoint dstPoint,
                                          GrSurfaceOrigin);

    // Adds a task that writes the data from the passed GrMipLevels to dst. The lifetime of the
    // pixel data in the levels should be tied to the passed SkData or the caller must flush the
    // context before the data may become invalid. srcColorType is the color type of the
    // GrMipLevels. dstColorType is the color type being used with dst and must be compatible with
    // dst's format according to GrCaps::areColorTypeAndFormatCompatible().
    SK_API bool newWritePixelsTask(sk_sp<GrSurfaceProxy> dst,
                            SkIRect rect,
                            GrColorType srcColorType,
                            GrColorType dstColorType,
                            const GrMipLevel[],
                            int levelCount);

    GrRecordingContext* getContext() { return fContext; }

#if SK_GPU_V1
    using PathRenderer = skgpu::v1::PathRenderer;
    using PathRendererChain = skgpu::v1::PathRendererChain;

    SK_API PathRenderer* getPathRenderer(const PathRenderer::CanDrawPathArgs&,
                                  bool allowSW,
                                  PathRendererChain::DrawType,
                                  PathRenderer::StencilSupport* = nullptr);

    SK_API PathRenderer* getSoftwarePathRenderer();

    // Returns a direct pointer to the atlas path renderer, or null if it is not supported and
    // turned on.
    SK_API skgpu::v1::AtlasPathRenderer* getAtlasPathRenderer();

    // Returns a direct pointer to the tessellation path renderer, or null if it is not supported
    // and turned on.
    SK_API PathRenderer* getTessellationPathRenderer();
#endif

    SK_API void flushIfNecessary();

    SK_API static bool ProgramUnitTest(GrDirectContext*, int maxStages, int maxLevels);

    SK_API GrSemaphoresSubmitted flushSurfaces(SkSpan<GrSurfaceProxy*>,
                                        SkSurface::BackendSurfaceAccess,
                                        const GrFlushInfo&,
                                        const GrBackendSurfaceMutableState* newState);

    SK_API void addOnFlushCallbackObject(GrOnFlushCallbackObject*);

#if GR_TEST_UTILS
    SK_API void testingOnly_removeOnFlushCallbackObject(GrOnFlushCallbackObject*);
#if SK_GPU_V1
    PathRendererChain::Options testingOnly_getOptionsForPathRendererChain() {
        return fOptionsForPathRendererChain;
    }
#endif
#endif

    SK_API GrRenderTask* getLastRenderTask(const GrSurfaceProxy*) const;
    SK_API skgpu::v1::OpsTask* getLastOpsTask(const GrSurfaceProxy*) const;
    SK_API void setLastRenderTask(const GrSurfaceProxy*, GrRenderTask*);

    SK_API void moveRenderTasksToDDL(SkDeferredDisplayList* ddl);
    SK_API void createDDLTask(sk_sp<const SkDeferredDisplayList>,
                       sk_sp<GrRenderTargetProxy> newDest,
                       SkIPoint offset);

private:
#if SK_GPU_V1
    SK_API GrDrawingManager(GrRecordingContext*,
                     const PathRendererChain::Options&,
                     bool reduceOpsTaskSplitting);
#else
    SK_API GrDrawingManager(GrRecordingContext*, bool reduceOpsTaskSplitting);
#endif

    SK_API bool wasAbandoned() const;

    SK_API void closeActiveOpsTask();

    // return true if any GrRenderTasks were actually executed; false otherwise
    SK_API bool executeRenderTasks(GrOpFlushState*);

    SK_API void removeRenderTasks();

    SK_API void sortTasks();

    // Attempt to reorder tasks to reduce render passes, and check the memory budget of the
    // resulting intervals. Returns whether the reordering was successful & the memory budget
    // acceptable. If it returns true, fDAG has been updated to reflect the reordered tasks.
    SK_API bool reorderTasks(GrResourceAllocator*);

    SK_API void closeAllTasks();

    SK_API GrRenderTask* appendTask(sk_sp<GrRenderTask>);
    SK_API GrRenderTask* insertTaskBeforeLast(sk_sp<GrRenderTask>);

    SK_API bool flush(SkSpan<GrSurfaceProxy*> proxies,
               SkSurface::BackendSurfaceAccess access,
               const GrFlushInfo&,
               const GrBackendSurfaceMutableState* newState);

    SK_API bool submitToGpu(bool syncToCpu);

    SkDEBUGCODE(void validate() const);

    friend class GrDirectContext; // access to: flush & cleanup
    friend class GrDirectContextPriv; // access to: flush
    friend class GrOnFlushResourceProvider; // this is just a shallow wrapper around this class
    friend class GrRecordingContext;  // access to: ctor
    friend class SkImage; // for access to: flush

    static const int kNumPixelGeometries = 5; // The different pixel geometries
    static const int kNumDFTOptions = 2;      // DFT or no DFT

    GrRecordingContext*                      fContext;

    // This cache is used by both the vertex and index pools. It reuses memory across multiple
    // flushes.
    sk_sp<GrBufferAllocPool::CpuBufferCache> fCpuBufferCache;

    SkTArray<sk_sp<GrRenderTask>>            fDAG;
    skgpu::v1::OpsTask*                      fActiveOpsTask = nullptr;
    // These are the IDs of the opsTask currently being flushed (in internalFlush). They are
    // only stored here to prevent memory thrashing.
    SkSTArray<8, uint32_t, true>             fFlushingRenderTaskIDs;
    // These are the new renderTasks generated by the onFlush CBs
    SkSTArray<4, sk_sp<GrRenderTask>>        fOnFlushRenderTasks;

#if SK_GPU_V1
    PathRendererChain::Options               fOptionsForPathRendererChain;
    std::unique_ptr<PathRendererChain>       fPathRendererChain;
    sk_sp<skgpu::v1::SoftwarePathRenderer>   fSoftwarePathRenderer;
#endif

    GrTokenTracker                           fTokenTracker;
    bool                                     fFlushing = false;
    const bool                               fReduceOpsTaskSplitting;

    SkTArray<GrOnFlushCallbackObject*>       fOnFlushCBObjects;

    struct SurfaceIDKeyTraits {
        static uint32_t GetInvalidKey() {
            return GrSurfaceProxy::UniqueID::InvalidID().asUInt();
        }
    };

    GrHashMapWithCache<uint32_t, GrRenderTask*, SurfaceIDKeyTraits, GrCheapHash> fLastRenderTasks;
};

#endif
