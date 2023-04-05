#pragma once
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkNoDrawCanvas_DEFINED
#define SkNoDrawCanvas_DEFINED

#include <skia/core/SkCanvas.h>
#include <skia/core/SkCanvasVirtualEnforcer.h>

struct SkIRect;

// SkNoDrawCanvas is a helper for SkCanvas subclasses which do not need to
// actually rasterize (e.g., analysis of the draw calls).
//
// It provides the following simplifications:
//
//   * not backed by any device/pixels
//   * conservative clipping (clipping calls only use rectangles)
//
class SkNoDrawCanvas : public SkCanvasVirtualEnforcer<SkCanvas> {
public:
    SK_API SkNoDrawCanvas(int width, int height);
    SK_API SkNoDrawCanvas(const SkIRect&);

    SK_API explicit SkNoDrawCanvas(sk_sp<SkBaseDevice> device);

    // Optimization to reset state to be the same as after construction.
    void resetCanvas(int w, int h)        { this->resetForNextPicture(SkIRect::MakeWH(w, h)); }
    void resetCanvas(const SkIRect& rect) { this->resetForNextPicture(rect); }

protected:
    SK_API SaveLayerStrategy getSaveLayerStrategy(const SaveLayerRec& rec) override;
    SK_API bool onDoSaveBehind(const SkRect*) override;

    // No-op overrides for aborting rasterization earlier than SkNullBlitter.
    SK_API void onDrawAnnotation(const SkRect&, const char[], SkData*) override {}
    SK_API void onDrawDRRect(const SkRRect&, const SkRRect&, const SkPaint&) override {}
    SK_API void onDrawDrawable(SkDrawable*, const SkMatrix*) override {}
    SK_API void onDrawTextBlob(const SkTextBlob*, SkScalar, SkScalar, const SkPaint&) override {}
    SK_API void onDrawPatch(const SkPoint[12], const SkColor[4], const SkPoint[4], SkBlendMode,
                     const SkPaint&) override {}

    SK_API void onDrawPaint(const SkPaint&) override {}
    SK_API void onDrawBehind(const SkPaint&) override {}
    SK_API void onDrawPoints(PointMode, size_t, const SkPoint[], const SkPaint&) override {}
    SK_API void onDrawRect(const SkRect&, const SkPaint&) override {}
    SK_API void onDrawRegion(const SkRegion&, const SkPaint&) override {}
    SK_API void onDrawOval(const SkRect&, const SkPaint&) override {}
    SK_API void onDrawArc(const SkRect&, SkScalar, SkScalar, bool, const SkPaint&) override {}
    SK_API void onDrawRRect(const SkRRect&, const SkPaint&) override {}
    SK_API void onDrawPath(const SkPath&, const SkPaint&) override {}

    SK_API void onDrawImage2(const SkImage*, SkScalar, SkScalar, const SkSamplingOptions&,
                      const SkPaint*) override {}
    SK_API void onDrawImageRect2(const SkImage*, const SkRect&, const SkRect&, const SkSamplingOptions&,
                          const SkPaint*, SrcRectConstraint) override {}
    SK_API void onDrawImageLattice2(const SkImage*, const Lattice&, const SkRect&, SkFilterMode,
                             const SkPaint*) override {}
    SK_API void onDrawAtlas2(const SkImage*, const SkRSXform[], const SkRect[], const SkColor[], int,
                  SkBlendMode, const SkSamplingOptions&, const SkRect*, const SkPaint*) override {}

    SK_API void onDrawVerticesObject(const SkVertices*, SkBlendMode, const SkPaint&) override {}
    SK_API void onDrawShadowRec(const SkPath&, const SkDrawShadowRec&) override {}
    SK_API void onDrawPicture(const SkPicture*, const SkMatrix*, const SkPaint*) override {}

    SK_API void onDrawEdgeAAQuad(const SkRect&, const SkPoint[4], QuadAAFlags, const SkColor4f&,
                          SkBlendMode) override {}
    SK_API void onDrawEdgeAAImageSet2(const ImageSetEntry[], int, const SkPoint[], const SkMatrix[],
                               const SkSamplingOptions&, const SkPaint*,
                               SrcRectConstraint) override {}

private:
    using INHERITED = SkCanvasVirtualEnforcer<SkCanvas>;
};

#endif // SkNoDrawCanvas_DEFINED
