/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGRenderNode_DEFINED
#define SkSGRenderNode_DEFINED

#include "SkSGNode.h"

#include "skia/core/SkBlendMode.h"
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkShader.h"

class SkCanvas;
class SkImageFilter;
class SkPaint;

namespace sksg {

/**
 * Base class for nodes which can render to a canvas.
 */
class RenderNode : public Node {
protected:
    struct RenderContext;

public:
    // Render the node and its descendants to the canvas.
    SK_API void render(SkCanvas*, const RenderContext* = nullptr) const;

    // Perform a front-to-back hit-test, and return the RenderNode located at |point|.
    // Normally, hit-testing stops at leaf Draw nodes.
    SK_API const RenderNode* nodeAt(const SkPoint& point) const;

    // Controls the visibility of the render node.  Invisible nodes are not rendered,
    // but they still participate in revalidation.
    SK_API bool isVisible() const;
    SK_API void setVisible(bool);

protected:
    SK_API explicit RenderNode(uint32_t inval_traits = 0);

    virtual void onRender(SkCanvas*, const RenderContext*) const = 0;
    virtual const RenderNode* onNodeAt(const SkPoint& p)   const = 0;

    // Paint property overrides.
    // These are deferred until we can determine whether they can be applied to the individual
    // draw paints, or whether they require content isolation (applied to a layer).
    struct RenderContext {
        sk_sp<SkColorFilter> fColorFilter;
        sk_sp<SkShader>      fShader;
        sk_sp<SkShader>      fMaskShader;
        SkMatrix             fShaderCTM = SkMatrix::I(),
                             fMaskCTM   = SkMatrix::I();
        float                fOpacity   = 1;
        SkBlendMode          fBlendMode = SkBlendMode::kSrcOver;

        // Returns true if the paint overrides require a layer when applied to non-atomic draws.
        SK_API bool requiresIsolation() const;

        SK_API void modulatePaint(const SkMatrix& ctm, SkPaint*, bool is_layer_paint = false) const;
    };

    class ScopedRenderContext final {
    public:
        SK_API ScopedRenderContext(SkCanvas*, const RenderContext*);
        SK_API ~ScopedRenderContext();

        ScopedRenderContext(ScopedRenderContext&& that) { *this = std::move(that); }

        ScopedRenderContext& operator=(ScopedRenderContext&& that) {
            fCanvas       = that.fCanvas;
            fCtx          = std::move(that.fCtx);
            fMaskShader   = std::move(that.fMaskShader);
            fRestoreCount = that.fRestoreCount;

            // scope ownership is being transferred
            that.fRestoreCount = -1;

            return *this;
        }

        operator const RenderContext*  () const { return &fCtx; }
        const RenderContext* operator->() const { return &fCtx; }

        // Add (cumulative) paint overrides to a render node sub-DAG.
        SK_API ScopedRenderContext&& modulateOpacity(float opacity);
        SK_API ScopedRenderContext&& modulateColorFilter(sk_sp<SkColorFilter>);
        SK_API ScopedRenderContext&& modulateShader(sk_sp<SkShader>, const SkMatrix& shader_ctm);
        SK_API ScopedRenderContext&& modulateMaskShader(sk_sp<SkShader>, const SkMatrix& ms_ctm);
        SK_API ScopedRenderContext&& modulateBlendMode(SkBlendMode);

        // Force content isolation for a node sub-DAG by applying the RenderContext
        // overrides via a layer.
        SK_API ScopedRenderContext&& setIsolation(const SkRect& bounds, const SkMatrix& ctm,
                                           bool do_isolate);

        // Similarly, force content isolation by applying the RenderContext overrides and
        // an image filter via a single layer.
        SK_API ScopedRenderContext&& setFilterIsolation(const SkRect& bounds, const SkMatrix& ctm,
                                                 sk_sp<SkImageFilter>);

    private:
        // stack-only
        void* operator new(size_t)        = delete;
        void* operator new(size_t, void*) = delete;

        // Scopes cannot be copied.
        ScopedRenderContext(const ScopedRenderContext&)            = delete;
        ScopedRenderContext& operator=(const ScopedRenderContext&) = delete;

        SkCanvas*       fCanvas;
        RenderContext   fCtx;
        sk_sp<SkShader> fMaskShader; // to be applied at isolation layer restore time
        int             fRestoreCount;
    };

private:
    friend class ImageFilterEffect;

    using INHERITED = Node;
};

/**
 * Clients outside SkSG looking to implement custom render nodes,
 * should derive from this class instead of RenderNode.  It handles
 * various book-keeping, and provides a controlled extension point.
 */
class CustomRenderNode : public RenderNode {
protected:
    SK_API explicit CustomRenderNode(std::vector<sk_sp<RenderNode>>&& children);
    SK_API ~CustomRenderNode() override;

    const std::vector<sk_sp<RenderNode>>& children() const { return fChildren; }

    SK_API bool hasChildrenInval() const;

private:
    std::vector<sk_sp<RenderNode>> fChildren;

    using INHERITED = RenderNode;
};

} // namespace sksg

#endif // SkSGRenderNode_DEFINED
