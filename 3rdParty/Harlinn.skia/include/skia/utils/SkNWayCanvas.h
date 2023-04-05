#pragma once

/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkNWayCanvas_DEFINED
#define SkNWayCanvas_DEFINED

#include <skia/core/SkCanvasVirtualEnforcer.h>
#include <skia/private/SkTDArray.h>
#include <skia/utils/SkNoDrawCanvas.h>

class SkNWayCanvas : public SkCanvasVirtualEnforcer<SkNoDrawCanvas> {
public:
    SK_API SkNWayCanvas(int width, int height);
    SK_API ~SkNWayCanvas() override;

    SK_API virtual void addCanvas(SkCanvas*);
    SK_API virtual void removeCanvas(SkCanvas*);
    SK_API virtual void removeAll();

protected:
    SkTDArray<SkCanvas*> fList;

    SK_API void willSave() override;
    SK_API SaveLayerStrategy getSaveLayerStrategy(const SaveLayerRec&) override;
    SK_API bool onDoSaveBehind(const SkRect*) override;
    SK_API void willRestore() override;

    SK_API void onMarkCTM(const char*) override;
    SK_API void didConcat44(const SkM44&) override;
    SK_API void didSetM44(const SkM44&) override;
    SK_API void didScale(SkScalar, SkScalar) override;
    SK_API void didTranslate(SkScalar, SkScalar) override;

    SK_API void onDrawDRRect(const SkRRect&, const SkRRect&, const SkPaint&) override;
    SK_API void onDrawGlyphRunList(const SkGlyphRunList&, const SkPaint&) override;
    SK_API void onDrawTextBlob(const SkTextBlob* blob, SkScalar x, SkScalar y,
                        const SkPaint& paint) override;
    SK_API void onDrawPatch(const SkPoint cubics[12], const SkColor colors[4],
                     const SkPoint texCoords[4], SkBlendMode, const SkPaint& paint) override;

    SK_API void onDrawPaint(const SkPaint&) override;
    SK_API void onDrawBehind(const SkPaint&) override;
    SK_API void onDrawPoints(PointMode, size_t count, const SkPoint pts[], const SkPaint&) override;
    SK_API void onDrawRect(const SkRect&, const SkPaint&) override;
    SK_API void onDrawRegion(const SkRegion&, const SkPaint&) override;
    SK_API void onDrawOval(const SkRect&, const SkPaint&) override;
    SK_API void onDrawArc(const SkRect&, SkScalar, SkScalar, bool, const SkPaint&) override;
    SK_API void onDrawRRect(const SkRRect&, const SkPaint&) override;
    SK_API void onDrawPath(const SkPath&, const SkPaint&) override;

    SK_API void onDrawImage2(const SkImage*, SkScalar, SkScalar, const SkSamplingOptions&,
                      const SkPaint*) override;
    SK_API void onDrawImageRect2(const SkImage*, const SkRect&, const SkRect&, const SkSamplingOptions&,
                          const SkPaint*, SrcRectConstraint) override;
    SK_API void onDrawImageLattice2(const SkImage*, const Lattice&, const SkRect&, SkFilterMode,
                             const SkPaint*) override;
    SK_API void onDrawAtlas2(const SkImage*, const SkRSXform[], const SkRect[], const SkColor[], int,
                  SkBlendMode, const SkSamplingOptions&, const SkRect*, const SkPaint*) override;

    SK_API void onDrawVerticesObject(const SkVertices*, SkBlendMode, const SkPaint&) override;
    SK_API void onDrawShadowRec(const SkPath&, const SkDrawShadowRec&) override;

    SK_API void onClipRect(const SkRect&, SkClipOp, ClipEdgeStyle) override;
    SK_API void onClipRRect(const SkRRect&, SkClipOp, ClipEdgeStyle) override;
    SK_API void onClipPath(const SkPath&, SkClipOp, ClipEdgeStyle) override;
    SK_API void onClipShader(sk_sp<SkShader>, SkClipOp) override;
    SK_API void onClipRegion(const SkRegion&, SkClipOp) override;
    SK_API void onResetClip() override;

    SK_API void onDrawPicture(const SkPicture*, const SkMatrix*, const SkPaint*) override;
    SK_API void onDrawDrawable(SkDrawable*, const SkMatrix*) override;
    SK_API void onDrawAnnotation(const SkRect&, const char[], SkData*) override;

    SK_API void onDrawEdgeAAQuad(const SkRect&, const SkPoint[4], QuadAAFlags, const SkColor4f&,
                          SkBlendMode) override;
    SK_API void onDrawEdgeAAImageSet2(const ImageSetEntry[], int count, const SkPoint[], const SkMatrix[],
                               const SkSamplingOptions&,const SkPaint*, SrcRectConstraint) override;

    SK_API void onFlush() override;

    class Iter;

private:
    using INHERITED = SkCanvasVirtualEnforcer<SkNoDrawCanvas>;
};


#endif
