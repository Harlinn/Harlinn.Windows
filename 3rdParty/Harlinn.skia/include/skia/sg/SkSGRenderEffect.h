/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGRenderEffect_DEFINED
#define SkSGRenderEffect_DEFINED

#include "SkSGEffectNode.h"

#include "skia/core/SkBlendMode.h"
#include "skia/core/SkColor.h"
#include "skia/effects/SkImageFilters.h"

#include <memory>
#include <vector>

// TODO: merge EffectNode.h with this header

class SkImageFilter;
class SkMaskFilter;
class SkShader;

namespace sksg {

/**
 * Shader base class.
 */
class Shader : public Node {
public:
    SK_API ~Shader() override;

    const sk_sp<SkShader>& getShader() const {
        SkASSERT(!this->hasInval());
        return fShader;
    }

protected:
    SK_API Shader();

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) final;

    virtual sk_sp<SkShader> onRevalidateShader() = 0;

private:
    sk_sp<SkShader> fShader;

    using INHERITED = Node;
};

/**
 * Attaches a shader to the render DAG.
 */
class ShaderEffect final : public EffectNode {
public:
    SK_API ~ShaderEffect() override;

    SK_API static sk_sp<ShaderEffect> Make(sk_sp<RenderNode> child, sk_sp<Shader> shader = nullptr);

    SK_API void setShader(sk_sp<Shader>);

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    SK_API ShaderEffect(sk_sp<RenderNode> child, sk_sp<Shader> shader);

    sk_sp<Shader> fShader;

    using INHERITED = EffectNode;
};

/**
 * Attaches a mask shader to the render DAG.
 */
class MaskShaderEffect final : public EffectNode {
public:
    SK_API static sk_sp<MaskShaderEffect> Make(sk_sp<RenderNode>, sk_sp<SkShader> = nullptr);

    SG_ATTRIBUTE(Shader, sk_sp<SkShader>, fShader)

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;

private:
    SK_API MaskShaderEffect(sk_sp<RenderNode>, sk_sp<SkShader>);

    sk_sp<SkShader> fShader;

    using INHERITED = EffectNode;
};

/**
 * ImageFilter base class.
 */
class ImageFilter : public Node {
public:
    SK_API ~ImageFilter() override;

    const sk_sp<SkImageFilter>& getFilter() const {
        SkASSERT(!this->hasInval());
        return fFilter;
    }

protected:
    SK_API explicit ImageFilter(sk_sp<ImageFilter> input = nullptr);

    using InputsT = std::vector<sk_sp<ImageFilter>>;
    SK_API explicit ImageFilter(std::unique_ptr<InputsT> inputs);

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) final;

    virtual sk_sp<SkImageFilter> onRevalidateFilter() = 0;

    SK_API sk_sp<SkImageFilter> refInput(size_t) const;

private:
    const std::unique_ptr<InputsT> fInputs;

    sk_sp<SkImageFilter>           fFilter;

    using INHERITED = Node;
};

/**
 * Attaches an ImageFilter (chain) to the render DAG.
 */
class ImageFilterEffect final : public EffectNode {
public:
    SK_API ~ImageFilterEffect() override;

    SK_API static sk_sp<RenderNode> Make(sk_sp<RenderNode> child, sk_sp<ImageFilter> filter);

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    SK_API ImageFilterEffect(sk_sp<RenderNode> child, sk_sp<ImageFilter> filter);

    sk_sp<ImageFilter> fImageFilter;

    using INHERITED = EffectNode;
};

/**
 * Wrapper for externally-managed SkImageFilters.
 */
class ExternalImageFilter final : public ImageFilter {
public:
    SK_API ~ExternalImageFilter() override;

    static sk_sp<ExternalImageFilter> Make() {
        return sk_sp<ExternalImageFilter>(new ExternalImageFilter());
    }

    SG_ATTRIBUTE(ImageFilter, sk_sp<SkImageFilter>, fImageFilter)

private:
    SK_API ExternalImageFilter();

    sk_sp<SkImageFilter> onRevalidateFilter() override { return fImageFilter; }

    sk_sp<SkImageFilter> fImageFilter;
};

/**
 * SkDropShadowImageFilter node.
 */
class DropShadowImageFilter final : public ImageFilter {
public:
    SK_API ~DropShadowImageFilter() override;

    static sk_sp<DropShadowImageFilter> Make(sk_sp<ImageFilter> input = nullptr);

    enum class Mode { kShadowAndForeground, kShadowOnly };

    SG_ATTRIBUTE(Offset, SkVector, fOffset)
    SG_ATTRIBUTE(Sigma , SkVector, fSigma )
    SG_ATTRIBUTE(Color , SkColor , fColor )
    SG_ATTRIBUTE(Mode  , Mode    , fMode  )

protected:
    SK_API sk_sp<SkImageFilter> onRevalidateFilter() override;

private:
    SK_API explicit DropShadowImageFilter(sk_sp<ImageFilter> input);

    SkVector             fOffset = { 0, 0 },
                         fSigma  = { 0, 0 };
    SkColor              fColor  = SK_ColorBLACK;
    Mode                 fMode   = Mode::kShadowAndForeground;

    using INHERITED = ImageFilter;
};

/**
 * SkBlurImageFilter node.
 */
class BlurImageFilter final : public ImageFilter {
public:
    SK_API ~BlurImageFilter() override;

    static sk_sp<BlurImageFilter> Make(sk_sp<ImageFilter> input = nullptr);

    SG_ATTRIBUTE(Sigma   , SkVector  , fSigma   )
    SG_ATTRIBUTE(TileMode, SkTileMode, fTileMode)

protected:
    SK_API sk_sp<SkImageFilter> onRevalidateFilter() override;

private:
    SK_API explicit BlurImageFilter(sk_sp<ImageFilter> input);

    SkVector   fSigma    = { 0, 0 };
    SkTileMode fTileMode = SkTileMode::kClamp;

    using INHERITED = ImageFilter;
};

/**
 * Applies a SkBlendMode to descendant render nodes.
 */
class BlendModeEffect final : public EffectNode {
public:
    SK_API ~BlendModeEffect() override;

    static sk_sp<BlendModeEffect> Make(sk_sp<RenderNode> child,
                                       SkBlendMode = SkBlendMode::kSrcOver);

    SG_ATTRIBUTE(Mode, SkBlendMode, fMode)

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

private:
    SK_API BlendModeEffect(sk_sp<RenderNode>, SkBlendMode);

    SkBlendMode fMode;

    using INHERITED = EffectNode;
};

class LayerEffect final : public EffectNode {
public:
    SK_API ~LayerEffect() override;

    SK_API static sk_sp<LayerEffect> Make(sk_sp<RenderNode> child,
                                   SkBlendMode mode = SkBlendMode::kSrcOver);

    SG_ATTRIBUTE(Mode, SkBlendMode, fMode)

private:
    SK_API LayerEffect(sk_sp<RenderNode> child, SkBlendMode mode);

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;

    SkBlendMode fMode;

    using INHERITED = EffectNode;
};

} // namespace sksg

#endif // SkSGRenderEffect_DEFINED
