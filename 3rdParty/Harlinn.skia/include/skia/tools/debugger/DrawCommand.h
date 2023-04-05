/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKDRAWCOMMAND_H_
#define SKDRAWCOMMAND_H_

#include <skia/core/SkBitmap.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkFlattenable.h>
#include <skia/core/SkPath.h>
#include <skia/core/SkRRect.h>
#include <skia/core/SkRSXform.h>
#include <skia/core/SkRegion.h>
#include <skia/core/SkString.h>
#include <skia/core/SkVertices.h>
#include <skia/private/SkTDArray.h>
#include "src/core/SkDrawShadowInfo.h"
#include "src/core/SkTLazy.h"
#include "src/utils/SkJSONWriter.h"
#include <skia/tools/UrlDataManager.h>

class DebugLayerManager;

class DrawCommand {
public:
    enum OpType {
        kBeginDrawPicture_OpType,
        kClear_OpType,
        kClipPath_OpType,
        kClipRegion_OpType,
        kClipRect_OpType,
        kClipRRect_OpType,
        kClipShader_OpType,
        kResetClip_OpType,
        kConcat_OpType,
        kConcat44_OpType,
        kDrawAnnotation_OpType,
        kDrawBitmap_OpType,
        kDrawBitmapRect_OpType,
        kDrawDRRect_OpType,
        kDrawImage_OpType,
        kDrawImageLattice_OpType,
        kDrawImageRect_OpType,
        kDrawImageRectLayer_OpType, // unique to DebugCanvas
        kDrawOval_OpType,
        kDrawArc_OpType,
        kDrawPaint_OpType,
        kDrawPatch_OpType,
        kDrawPath_OpType,
        kDrawPoints_OpType,
        kDrawRect_OpType,
        kDrawRRect_OpType,
        kDrawRegion_OpType,
        kDrawShadow_OpType,
        kDrawTextBlob_OpType,
        kDrawVertices_OpType,
        kDrawAtlas_OpType,
        kDrawDrawable_OpType,
        kDrawEdgeAAQuad_OpType,
        kDrawEdgeAAImageSet_OpType,
        kEndDrawPicture_OpType,
        kRestore_OpType,
        kSave_OpType,
        kSaveLayer_OpType,
        kSetMatrix_OpType,
        kSetM44_OpType,

        kLast_OpType = kSetM44_OpType
    };

    static const int kOpTypeCount = kLast_OpType + 1;

    SK_API static void WritePNG(SkBitmap bitmap, SkWStream& out);

    SK_API DrawCommand(OpType opType);

    virtual ~DrawCommand() {}

    bool isVisible() const { return fVisible; }

    void setVisible(bool toggle) { fVisible = toggle; }

    virtual void execute(SkCanvas*) const = 0;

    virtual bool render(SkCanvas* canvas) const { return false; }

    SK_API virtual void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const;

    SK_API static const char* GetCommandString(OpType type);

    // Helper methods for converting things to JSON
    SK_API static void MakeJsonColor(SkJSONWriter&, const SkColor color);
    SK_API static void MakeJsonColor4f(SkJSONWriter&, const SkColor4f& color);
    SK_API static void MakeJsonPoint(SkJSONWriter&, const SkPoint& point);
    SK_API static void MakeJsonPoint(SkJSONWriter&, SkScalar x, SkScalar y);
    SK_API static void MakeJsonPoint3(SkJSONWriter&, const SkPoint3& point);
    SK_API static void MakeJsonRect(SkJSONWriter&, const SkRect& rect);
    SK_API static void MakeJsonIRect(SkJSONWriter&, const SkIRect&);
    SK_API static void MakeJsonMatrix(SkJSONWriter&, const SkMatrix&);
    SK_API static void MakeJsonMatrix44(SkJSONWriter&, const SkM44&);
    SK_API static void MakeJsonPath(SkJSONWriter&, const SkPath& path);
    SK_API static void MakeJsonRegion(SkJSONWriter&, const SkRegion& region);
    SK_API static void MakeJsonPaint(SkJSONWriter&, const SkPaint& paint, UrlDataManager& urlDataManager);
    SK_API static void MakeJsonLattice(SkJSONWriter&, const SkCanvas::Lattice& lattice);

    SK_API static void flatten(const SkFlattenable* flattenable,
                        SkJSONWriter&        writer,
                        UrlDataManager&      urlDataManager);
    SK_API static bool flatten(const SkImage& image, SkJSONWriter& writer, UrlDataManager& urlDataManager);
    SK_API static bool flatten(const SkBitmap& bitmap,
                        SkJSONWriter&   writer,
                        UrlDataManager& urlDataManager);
    OpType getOpType() const { return fOpType; }

private:
    OpType fOpType;
    bool   fVisible;
};

class RestoreCommand : public DrawCommand {
public:
    SK_API RestoreCommand();
    SK_API void execute(SkCanvas* canvas) const override;

private:
    using INHERITED = DrawCommand;
};

class ClearCommand : public DrawCommand {
public:
    SK_API ClearCommand(SkColor color);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkColor fColor;

    using INHERITED = DrawCommand;
};

class ClipPathCommand : public DrawCommand {
public:
    SK_API ClipPathCommand(const SkPath& path, SkClipOp op, bool doAA);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPath   fPath;
    SkClipOp fOp;
    bool     fDoAA;

    using INHERITED = DrawCommand;
};

class ClipRegionCommand : public DrawCommand {
public:
    SK_API ClipRegionCommand(const SkRegion& region, SkClipOp op);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRegion fRegion;
    SkClipOp fOp;

    using INHERITED = DrawCommand;
};

class ClipRectCommand : public DrawCommand {
public:
    SK_API ClipRectCommand(const SkRect& rect, SkClipOp op, bool doAA);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRect   fRect;
    SkClipOp fOp;
    bool     fDoAA;

    using INHERITED = DrawCommand;
};

class ClipRRectCommand : public DrawCommand {
public:
    SK_API ClipRRectCommand(const SkRRect& rrect, SkClipOp op, bool doAA);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRRect  fRRect;
    SkClipOp fOp;
    bool     fDoAA;

    using INHERITED = DrawCommand;
};

class ClipShaderCommand : public DrawCommand {
public:
    SK_API ClipShaderCommand(sk_sp<SkShader>, SkClipOp);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    sk_sp<SkShader> fShader;
    SkClipOp fOp;

    using INHERITED = DrawCommand;
};

class ResetClipCommand : public DrawCommand {
public:
    SK_API ResetClipCommand();
    SK_API void execute(SkCanvas* canvas) const override;

private:
    using INHERITED = DrawCommand;
};

class ConcatCommand : public DrawCommand {
public:
    SK_API ConcatCommand(const SkMatrix& matrix);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkMatrix fMatrix;

    using INHERITED = DrawCommand;
};

class Concat44Command : public DrawCommand {
public:
    SK_API Concat44Command(const SkM44& matrix);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkM44 fMatrix;

    using INHERITED = DrawCommand;
};

class DrawAnnotationCommand : public DrawCommand {
public:
    SK_API DrawAnnotationCommand(const SkRect&, const char key[], sk_sp<SkData> value);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRect        fRect;
    SkString      fKey;
    sk_sp<SkData> fValue;

    using INHERITED = DrawCommand;
};

class DrawImageCommand : public DrawCommand {
public:
    SK_API DrawImageCommand(const SkImage* image, SkScalar left, SkScalar top,
                     const SkSamplingOptions&, const SkPaint* paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;
    SK_API uint64_t imageId(UrlDataManager& udb) const;

private:
    sk_sp<const SkImage> fImage;
    SkScalar             fLeft;
    SkScalar             fTop;
    SkSamplingOptions    fSampling;
    SkTLazy<SkPaint>     fPaint;

    using INHERITED = DrawCommand;
};

class DrawImageLatticeCommand : public DrawCommand {
public:
    SK_API DrawImageLatticeCommand(const SkImage*           image,
                            const SkCanvas::Lattice& lattice,
                            const SkRect&            dst,
                            SkFilterMode,
                            const SkPaint*           paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;
    SK_API uint64_t imageId(UrlDataManager& udb) const;

private:
    sk_sp<const SkImage> fImage;
    SkCanvas::Lattice    fLattice;
    SkRect               fDst;
    SkFilterMode         fFilter;
    SkTLazy<SkPaint>     fPaint;

    using INHERITED = DrawCommand;
};

class DrawImageRectCommand : public DrawCommand {
public:
    SK_API DrawImageRectCommand(const SkImage*              image,
                         const SkRect&               src,
                         const SkRect&               dst,
                         const SkSamplingOptions&    sampling,
                         const SkPaint*              paint,
                         SkCanvas::SrcRectConstraint constraint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;
    SK_API uint64_t imageId(UrlDataManager& udm) const;

private:
    sk_sp<const SkImage>        fImage;
    SkRect                      fSrc;
    SkRect                      fDst;
    SkSamplingOptions           fSampling;
    SkTLazy<SkPaint>            fPaint;
    SkCanvas::SrcRectConstraint fConstraint;

    using INHERITED = DrawCommand;
};

// Command for resolving the deferred SkImage representing an android layer
// Functions like DrawImageRect except it uses the saved UrlDataManager to resolve the image
// at the time execute() is called.
class DrawImageRectLayerCommand : public DrawCommand {
public:
    SK_API DrawImageRectLayerCommand(DebugLayerManager*          layerManager,
                              const int                   nodeId,
                              const int                   frame,
                              const SkRect&               src,
                              const SkRect&               dst,
                              const SkSamplingOptions&    sampling,
                              const SkPaint*              paint,
                              SkCanvas::SrcRectConstraint constraint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    DebugLayerManager*          fLayerManager;
    int                         fNodeId;
    int                         fFrame;
    SkRect                      fSrc;
    SkRect                      fDst;
    SkSamplingOptions           fSampling;
    SkTLazy<SkPaint>            fPaint;
    SkCanvas::SrcRectConstraint fConstraint;

    using INHERITED = DrawCommand;
};

class DrawOvalCommand : public DrawCommand {
public:
    SK_API DrawOvalCommand(const SkRect& oval, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRect  fOval;
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawArcCommand : public DrawCommand {
public:
    SK_API DrawArcCommand(const SkRect&  oval,
                   SkScalar       startAngle,
                   SkScalar       sweepAngle,
                   bool           useCenter,
                   const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRect   fOval;
    SkScalar fStartAngle;
    SkScalar fSweepAngle;
    bool     fUseCenter;
    SkPaint  fPaint;

    using INHERITED = DrawCommand;
};

class DrawPaintCommand : public DrawCommand {
public:
    SK_API DrawPaintCommand(const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawBehindCommand : public DrawCommand {
public:
    SK_API DrawBehindCommand(const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawPathCommand : public DrawCommand {
public:
    SK_API DrawPathCommand(const SkPath& path, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPath  fPath;
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class BeginDrawPictureCommand : public DrawCommand {
public:
    SK_API BeginDrawPictureCommand(const SkPicture* picture, const SkMatrix* matrix, const SkPaint* paint);

    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;

private:
    sk_sp<const SkPicture> fPicture;
    SkTLazy<SkMatrix>      fMatrix;
    SkTLazy<SkPaint>       fPaint;

    using INHERITED = DrawCommand;
};

class EndDrawPictureCommand : public DrawCommand {
public:
    SK_API EndDrawPictureCommand(bool restore);

    SK_API void execute(SkCanvas* canvas) const override;

private:
    bool fRestore;

    using INHERITED = DrawCommand;
};

class DrawPointsCommand : public DrawCommand {
public:
    SK_API DrawPointsCommand(SkCanvas::PointMode mode,
                      size_t              count,
                      const SkPoint       pts[],
                      const SkPaint&      paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkCanvas::PointMode fMode;
    SkTDArray<SkPoint>  fPts;
    SkPaint             fPaint;

    using INHERITED = DrawCommand;
};

class DrawRegionCommand : public DrawCommand {
public:
    SK_API DrawRegionCommand(const SkRegion& region, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRegion fRegion;
    SkPaint  fPaint;

    using INHERITED = DrawCommand;
};

class DrawTextBlobCommand : public DrawCommand {
public:
    SK_API DrawTextBlobCommand(sk_sp<SkTextBlob> blob, SkScalar x, SkScalar y, const SkPaint& paint);

    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    sk_sp<SkTextBlob> fBlob;
    SkScalar          fXPos;
    SkScalar          fYPos;
    SkPaint           fPaint;

    using INHERITED = DrawCommand;
};

class DrawPatchCommand : public DrawCommand {
public:
    SK_API DrawPatchCommand(const SkPoint  cubics[12],
                     const SkColor  colors[4],
                     const SkPoint  texCoords[4],
                     SkBlendMode    bmode,
                     const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPoint     fCubics[12];
    SkColor*    fColorsPtr;
    SkColor     fColors[4];
    SkPoint*    fTexCoordsPtr;
    SkPoint     fTexCoords[4];
    SkBlendMode fBlendMode;
    SkPaint     fPaint;

    using INHERITED = DrawCommand;
};

class DrawRectCommand : public DrawCommand {
public:
    SK_API DrawRectCommand(const SkRect& rect, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRect  fRect;
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawRRectCommand : public DrawCommand {
public:
    SK_API DrawRRectCommand(const SkRRect& rrect, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRRect fRRect;
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawDRRectCommand : public DrawCommand {
public:
    SK_API DrawDRRectCommand(const SkRRect& outer, const SkRRect& inner, const SkPaint& paint);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkRRect fOuter;
    SkRRect fInner;
    SkPaint fPaint;

    using INHERITED = DrawCommand;
};

class DrawVerticesCommand : public DrawCommand {
public:
    SK_API DrawVerticesCommand(sk_sp<SkVertices>, SkBlendMode, const SkPaint&);

    SK_API void execute(SkCanvas* canvas) const override;

private:
    sk_sp<SkVertices> fVertices;
    SkBlendMode       fBlendMode;
    SkPaint           fPaint;

    using INHERITED = DrawCommand;
};

class DrawAtlasCommand : public DrawCommand {
public:
    SK_API DrawAtlasCommand(const SkImage*,
                     const SkRSXform[],
                     const SkRect[],
                     const SkColor[],
                     int,
                     SkBlendMode,
                     const SkSamplingOptions&,
                     const SkRect*,
                     const SkPaint*);

    SK_API void execute(SkCanvas* canvas) const override;

private:
    sk_sp<const SkImage> fImage;
    SkTDArray<SkRSXform> fXform;
    SkTDArray<SkRect>    fTex;
    SkTDArray<SkColor>   fColors;
    SkBlendMode          fBlendMode;
    SkSamplingOptions    fSampling;
    SkTLazy<SkRect>      fCull;
    SkTLazy<SkPaint>     fPaint;

    using INHERITED = DrawCommand;
};

class SaveCommand : public DrawCommand {
public:
    SK_API SaveCommand();
    SK_API void execute(SkCanvas* canvas) const override;

private:
    using INHERITED = DrawCommand;
};

class SaveLayerCommand : public DrawCommand {
public:
    SK_API SaveLayerCommand(const SkCanvas::SaveLayerRec&);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkTLazy<SkRect>            fBounds;
    SkTLazy<SkPaint>           fPaint;
    sk_sp<const SkImageFilter> fBackdrop;
    uint32_t                   fSaveLayerFlags;
    SkScalar                   fBackdropScale;

    using INHERITED = DrawCommand;
};

class SetMatrixCommand : public DrawCommand {
public:
    SK_API SetMatrixCommand(const SkMatrix& matrix);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkMatrix fMatrix;

    using INHERITED = DrawCommand;
};

class SetM44Command : public DrawCommand {
public:
    SK_API SetM44Command(const SkM44& matrix);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkM44 fMatrix;

    using INHERITED = DrawCommand;
};

class DrawShadowCommand : public DrawCommand {
public:
    SK_API DrawShadowCommand(const SkPath& path, const SkDrawShadowRec& rec);
    SK_API void execute(SkCanvas* canvas) const override;
    SK_API bool render(SkCanvas* canvas) const override;
    SK_API void toJSON(SkJSONWriter& writer, UrlDataManager& urlDataManager) const override;

private:
    SkPath          fPath;
    SkDrawShadowRec fShadowRec;

    using INHERITED = DrawCommand;
};

class DrawDrawableCommand : public DrawCommand {
public:
    SK_API DrawDrawableCommand(SkDrawable*, const SkMatrix*);
    SK_API void execute(SkCanvas* canvas) const override;

private:
    sk_sp<SkDrawable> fDrawable;
    SkTLazy<SkMatrix> fMatrix;

    using INHERITED = DrawCommand;
};

class DrawEdgeAAQuadCommand : public DrawCommand {
public:
    SK_API DrawEdgeAAQuadCommand(const SkRect&         rect,
                          const SkPoint         clip[4],
                          SkCanvas::QuadAAFlags aa,
                          const SkColor4f&      color,
                          SkBlendMode           mode);
    SK_API void execute(SkCanvas* canvas) const override;

private:
    SkRect                fRect;
    SkPoint               fClip[4];
    int                   fHasClip;
    SkCanvas::QuadAAFlags fAA;
    SkColor4f             fColor;
    SkBlendMode           fMode;

    using INHERITED = DrawCommand;
};

class DrawEdgeAAImageSetCommand : public DrawCommand {
public:
    SK_API DrawEdgeAAImageSetCommand(const SkCanvas::ImageSetEntry[],
                              int count,
                              const SkPoint[],
                              const SkMatrix[],
                              const SkSamplingOptions&,
                              const SkPaint*,
                              SkCanvas::SrcRectConstraint);
    SK_API void execute(SkCanvas* canvas) const override;

private:
    SkAutoTArray<SkCanvas::ImageSetEntry> fSet;
    int                                   fCount;
    SkAutoTArray<SkPoint>                 fDstClips;
    SkAutoTArray<SkMatrix>                fPreViewMatrices;
    SkSamplingOptions                     fSampling;
    SkTLazy<SkPaint>                      fPaint;
    SkCanvas::SrcRectConstraint           fConstraint;

    using INHERITED = DrawCommand;
};
#endif
