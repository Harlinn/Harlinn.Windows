#pragma once
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkOverdrawCanvas_DEFINED
#define SkOverdrawCanvas_DEFINED

#include <skia/core/SkCanvasVirtualEnforcer.h>
#include <skia/utils/SkNWayCanvas.h>

/**
 *  Captures all drawing commands.  Rather than draw the actual content, this device
 *  increments the alpha channel of each pixel every time it would have been touched
 *  by a draw call.  This is useful for detecting overdraw.
 */
class SkOverdrawCanvas : public SkCanvasVirtualEnforcer<SkNWayCanvas> {
public:
    /* Does not take ownership of canvas */
    SK_API SkOverdrawCanvas(SkCanvas*);

    SK_API void onDrawTextBlob(const SkTextBlob*, SkScalar, SkScalar, const SkPaint&) override;
    SK_API void onDrawGlyphRunList(const SkGlyphRunList& glyphRunList, const SkPaint& paint) override;
    SK_API void onDrawPatch(const SkPoint[12], const SkColor[4], const SkPoint[4], SkBlendMode,
                     const SkPaint&) override;
    SK_API void onDrawPaint(const SkPaint&) override;
    SK_API void onDrawBehind(const SkPaint& paint) override;
    SK_API void onDrawRect(const SkRect&, const SkPaint&) override;
    SK_API void onDrawRegion(const SkRegion&, const SkPaint&) override;
    SK_API void onDrawOval(const SkRect&, const SkPaint&) override;
    SK_API void onDrawArc(const SkRect&, SkScalar, SkScalar, bool, const SkPaint&) override;
    SK_API void onDrawDRRect(const SkRRect&, const SkRRect&, const SkPaint&) override;
    SK_API void onDrawRRect(const SkRRect&, const SkPaint&) override;
    SK_API void onDrawPoints(PointMode, size_t, const SkPoint[], const SkPaint&) override;
    SK_API void onDrawVerticesObject(const SkVertices*, SkBlendMode, const SkPaint&) override;
    SK_API void onDrawPath(const SkPath&, const SkPaint&) override;

    SK_API void onDrawImage2(const SkImage*, SkScalar, SkScalar, const SkSamplingOptions&,
                      const SkPaint*) override;
    SK_API void onDrawImageRect2(const SkImage*, const SkRect&, const SkRect&, const SkSamplingOptions&,
                          const SkPaint*, SrcRectConstraint) override;
    SK_API void onDrawImageLattice2(const SkImage*, const Lattice&, const SkRect&, SkFilterMode,
                             const SkPaint*) override;
    SK_API void onDrawAtlas2(const SkImage*, const SkRSXform[], const SkRect[], const SkColor[], int,
                     SkBlendMode, const SkSamplingOptions&, const SkRect*, const SkPaint*) override;

    SK_API void onDrawDrawable(SkDrawable*, const SkMatrix*) override;
    SK_API void onDrawPicture(const SkPicture*, const SkMatrix*, const SkPaint*) override;

    SK_API void onDrawAnnotation(const SkRect&, const char key[], SkData* value) override;
    SK_API void onDrawShadowRec(const SkPath&, const SkDrawShadowRec&) override;

    SK_API void onDrawEdgeAAQuad(const SkRect&, const SkPoint[4], SkCanvas::QuadAAFlags, const SkColor4f&,
                          SkBlendMode) override;
    SK_API void onDrawEdgeAAImageSet2(const ImageSetEntry[], int count, const SkPoint[], const SkMatrix[],
                               const SkSamplingOptions&,const SkPaint*, SrcRectConstraint) override;

private:
    inline SkPaint overdrawPaint(const SkPaint& paint);

    SkPaint   fPaint;

    using INHERITED = SkCanvasVirtualEnforcer<SkNWayCanvas>;
};

#endif
