#pragma once
/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkPaintFilterCanvas_DEFINED
#define SkPaintFilterCanvas_DEFINED

#include <skia/core/SkCanvasVirtualEnforcer.h>
#include <skia/utils/SkNWayCanvas.h>

class SkAndroidFrameworkUtils;

/** \class SkPaintFilterCanvas

    A utility proxy base class for implementing draw/paint filters.
*/
class SkPaintFilterCanvas : public SkCanvasVirtualEnforcer<SkNWayCanvas> {
public:
    /**
     * The new SkPaintFilterCanvas is configured for forwarding to the
     * specified canvas.  Also copies the target canvas matrix and clip bounds.
     */
    SK_API SkPaintFilterCanvas(SkCanvas* canvas);

    enum Type {
        kPicture_Type,
    };

    // Forwarded to the wrapped canvas.
    SkISize getBaseLayerSize() const override { return proxy()->getBaseLayerSize(); }
    GrRecordingContext* recordingContext() override { return proxy()->recordingContext(); }

protected:
    /**
     *  Called with the paint that will be used to draw the specified type.
     *  The implementation may modify the paint as they wish.
     *
     *  The result bool is used to determine whether the draw op is to be
     *  executed (true) or skipped (false).
     *
     *  Note: The base implementation calls onFilter() for top-level/explicit paints only.
     *        To also filter encapsulated paints (e.g. SkPicture, SkTextBlob), clients may need to
     *        override the relevant methods (i.e. drawPicture, drawTextBlob).
     */
    virtual bool onFilter(SkPaint& paint) const = 0;

    SK_API void onDrawPaint(const SkPaint&) override;
    SK_API void onDrawBehind(const SkPaint&) override;
    SK_API void onDrawPoints(PointMode, size_t count, const SkPoint pts[], const SkPaint&) override;
    SK_API void onDrawRect(const SkRect&, const SkPaint&) override;
    SK_API void onDrawRRect(const SkRRect&, const SkPaint&) override;
    SK_API void onDrawDRRect(const SkRRect&, const SkRRect&, const SkPaint&) override;
    SK_API void onDrawRegion(const SkRegion&, const SkPaint&) override;
    SK_API void onDrawOval(const SkRect&, const SkPaint&) override;
    SK_API void onDrawArc(const SkRect&, SkScalar, SkScalar, bool, const SkPaint&) override;
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
    SK_API void onDrawPatch(const SkPoint cubics[12], const SkColor colors[4],
                             const SkPoint texCoords[4], SkBlendMode,
                             const SkPaint& paint) override;
    SK_API void onDrawPicture(const SkPicture*, const SkMatrix*, const SkPaint*) override;
    SK_API void onDrawDrawable(SkDrawable*, const SkMatrix*) override;

    SK_API void onDrawGlyphRunList(const SkGlyphRunList&, const SkPaint&) override;
    SK_API void onDrawTextBlob(const SkTextBlob* blob, SkScalar x, SkScalar y,
                        const SkPaint& paint) override;
    SK_API void onDrawAnnotation(const SkRect& rect, const char key[], SkData* value) override;
    SK_API void onDrawShadowRec(const SkPath& path, const SkDrawShadowRec& rec) override;

    SK_API void onDrawEdgeAAQuad(const SkRect&, const SkPoint[4], QuadAAFlags, const SkColor4f&,
                          SkBlendMode) override;
    SK_API void onDrawEdgeAAImageSet2(const ImageSetEntry[], int count, const SkPoint[], const SkMatrix[],
                               const SkSamplingOptions&,const SkPaint*, SrcRectConstraint) override;

    // Forwarded to the wrapped canvas.
    SK_API sk_sp<SkSurface> onNewSurface(const SkImageInfo&, const SkSurfaceProps&) override;
    SK_API bool onPeekPixels(SkPixmap* pixmap) override;
    SK_API bool onAccessTopLayerPixels(SkPixmap* pixmap) override;
    SK_API SkImageInfo onImageInfo() const override;
    SK_API bool onGetProps(SkSurfaceProps* props) const override;

private:
    class AutoPaintFilter;

    SkCanvas* proxy() const { SkASSERT(fList.count() == 1); return fList[0]; }

    SkPaintFilterCanvas* internal_private_asPaintFilterCanvas() const override {
        return const_cast<SkPaintFilterCanvas*>(this);
    }

    friend class SkAndroidFrameworkUtils;
};

#endif
