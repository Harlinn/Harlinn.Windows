/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGPaint_DEFINED
#define SkSGPaint_DEFINED

#include "SkSGNode.h"

#include "skia/core/SkColor.h"
#include "skia/core/SkPaint.h"

namespace sksg {

class Shader;

/**
 * Base class for nodes which provide a 'paint' (as opposed to geometry) for
 * drawing (e.g. colors, gradients, patterns).
 *
 * Roughly equivalent to Skia's SkPaint.
 */
class PaintNode : public Node {
public:
    SK_API SkPaint makePaint() const;

    SG_ATTRIBUTE(AntiAlias  , bool          , fAntiAlias  )
    SG_ATTRIBUTE(Opacity    , SkScalar      , fOpacity    )
    SG_ATTRIBUTE(BlendMode  , SkBlendMode   , fBlendMode  )
    SG_ATTRIBUTE(StrokeWidth, SkScalar      , fStrokeWidth)
    SG_ATTRIBUTE(StrokeMiter, SkScalar      , fStrokeMiter)
    SG_ATTRIBUTE(Style      , SkPaint::Style, fStyle      )
    SG_ATTRIBUTE(StrokeJoin , SkPaint::Join , fStrokeJoin )
    SG_ATTRIBUTE(StrokeCap  , SkPaint::Cap  , fStrokeCap  )

protected:
    SK_API PaintNode();

    virtual void onApplyToPaint(SkPaint*) const = 0;

private:
    SkScalar       fOpacity     = 1,
                   fStrokeWidth = 1,
                   fStrokeMiter = 4;
    bool           fAntiAlias   = false;
    SkBlendMode    fBlendMode   = SkBlendMode::kSrcOver;
    SkPaint::Style fStyle       = SkPaint::kFill_Style;
    SkPaint::Join  fStrokeJoin  = SkPaint::kMiter_Join;
    SkPaint::Cap   fStrokeCap   = SkPaint::kButt_Cap;

    using INHERITED = Node;
};

/**
 * Concrete Paint node, wrapping an SkColor.
 */
class Color : public PaintNode {
public:
    SK_API static sk_sp<Color> Make(SkColor c);

    SG_ATTRIBUTE(Color, SkColor, fColor)

protected:
    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

    SK_API void onApplyToPaint(SkPaint*) const override;

private:
    SK_API explicit Color(SkColor);

    SkColor fColor;
};

/**
 * Shader-based paint.
 */
class ShaderPaint final : public PaintNode {
public:
    SK_API ~ShaderPaint() override;

    SK_API static sk_sp<ShaderPaint> Make(sk_sp<Shader>);

protected:
    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

    SK_API void onApplyToPaint(SkPaint*) const override;

private:
    SK_API explicit ShaderPaint(sk_sp<Shader>);

    const sk_sp<Shader> fShader;

    using INHERITED = PaintNode;
};

} // namespace sksg

#endif // SkSGPaint_DEFINED
