/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/sg/SkSGRenderEffect.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkMaskFilter.h"
#include "skia/core/SkShader.h"
#include "src/core/SkMaskFilterBase.h"

namespace sksg {

sk_sp<MaskShaderEffect> MaskShaderEffect::Make(sk_sp<RenderNode> child, sk_sp<SkShader> sh) {
    return child ? sk_sp<MaskShaderEffect>(new MaskShaderEffect(std::move(child), std::move(sh)))
                 : nullptr;
}

MaskShaderEffect::MaskShaderEffect(sk_sp<RenderNode> child, sk_sp<SkShader> sh)
    : INHERITED(std::move(child))
    , fShader(std::move(sh)) {
}

void MaskShaderEffect::onRender(SkCanvas* canvas, const RenderContext* ctx) const {
    const auto local_ctx = ScopedRenderContext(canvas, ctx)
            .modulateMaskShader(fShader, canvas->getTotalMatrix());

    this->INHERITED::onRender(canvas, local_ctx);
}

sk_sp<ShaderEffect> ShaderEffect::Make(sk_sp<RenderNode> child, sk_sp<Shader> shader) {
    return child ? sk_sp<ShaderEffect>(new ShaderEffect(std::move(child), std::move(shader)))
                 : nullptr;
}

ShaderEffect::ShaderEffect(sk_sp<RenderNode> child, sk_sp<Shader> shader)
    : INHERITED(std::move(child))
    , fShader(std::move(shader)) {
    if (fShader) {
        this->observeInval(fShader);
    }
}

ShaderEffect::~ShaderEffect() {
    if (fShader) {
        this->unobserveInval(fShader);
    }
}

void ShaderEffect::setShader(sk_sp<Shader> sh) {
    if (fShader) {
        this->unobserveInval(fShader);
    }

    fShader = std::move(sh);

    if (fShader) {
        this->observeInval(fShader);
    }
}
SkRect ShaderEffect::onRevalidate(InvalidationController* ic, const SkMatrix& ctm) {
    if (fShader) {
        fShader->revalidate(ic, ctm);
    }

    return this->INHERITED::onRevalidate(ic, ctm);
}

void ShaderEffect::onRender(SkCanvas* canvas, const RenderContext* ctx) const {
    const auto local_ctx = ScopedRenderContext(canvas, ctx)
            .modulateShader(fShader ? fShader->getShader() : nullptr, canvas->getTotalMatrix());

    this->INHERITED::onRender(canvas, local_ctx);
}

Shader::Shader() : INHERITED(kBubbleDamage_Trait) {}

Shader::~Shader() = default;

SkRect Shader::onRevalidate(InvalidationController*, const SkMatrix&) {
    SkASSERT(this->hasInval());

    fShader = this->onRevalidateShader();
    return SkRect::MakeEmpty();
}

sk_sp<RenderNode> ImageFilterEffect::Make(sk_sp<RenderNode> child, sk_sp<ImageFilter> filter) {
    return filter ? sk_sp<RenderNode>(new ImageFilterEffect(std::move(child), std::move(filter)))
                  : child;
}

ImageFilterEffect::ImageFilterEffect(sk_sp<RenderNode> child, sk_sp<ImageFilter> filter)
    // filters always override descendent damage
    : INHERITED(std::move(child), kOverrideDamage_Trait)
    , fImageFilter(std::move(filter)) {
    this->observeInval(fImageFilter);
}

ImageFilterEffect::~ImageFilterEffect() {
    this->unobserveInval(fImageFilter);
}

SkRect ImageFilterEffect::onRevalidate(InvalidationController* ic, const SkMatrix& ctm) {
    // FIXME: image filter effects should replace the descendents' damage!
    fImageFilter->revalidate(ic, ctm);

    const auto& filter = fImageFilter->getFilter();

    // Would be nice for this this to stick, but canComputeFastBounds()
    // appears to be conservative (false negatives).
    // SkASSERT(!filter || filter->canComputeFastBounds());

    const auto content_bounds = this->INHERITED::onRevalidate(ic, ctm);

    return filter ? filter->computeFastBounds(content_bounds)
                  : content_bounds;
}

const RenderNode* ImageFilterEffect::onNodeAt(const SkPoint& p) const {
    // TODO: map p through the filter DAG and dispatch to descendants?
    // For now, image filters occlude hit-testing.
    SkASSERT(this->bounds().contains(p.x(), p.y()));
    return this;
}

void ImageFilterEffect::onRender(SkCanvas* canvas, const RenderContext* ctx) const {
    // Note: we're using the source content bounds for saveLayer, not our local/filtered bounds.
    const auto filter_ctx =
        ScopedRenderContext(canvas, ctx).setFilterIsolation(this->getChild()->bounds(),
                                                            canvas->getTotalMatrix(),
                                                            fImageFilter->getFilter());
    this->INHERITED::onRender(canvas, filter_ctx);
}

ImageFilter::ImageFilter(sk_sp<ImageFilter> input)
    : ImageFilter(input ? std::make_unique<InputsT>(1, std::move(input)) : nullptr) {}

ImageFilter::ImageFilter(std::unique_ptr<InputsT> inputs)
    : INHERITED(kBubbleDamage_Trait)
    , fInputs(std::move(inputs)) {
    if (fInputs) {
        for (const auto& input : *fInputs) {
            this->observeInval(input);
        }
    }
}

ImageFilter::~ImageFilter() {
    if (fInputs) {
        for (const auto& input : *fInputs) {
            this->unobserveInval(input);
        }
    }
}

sk_sp<SkImageFilter> ImageFilter::refInput(size_t i) const {
    return (fInputs && i < fInputs->size()) ? (*fInputs)[i]->getFilter() : nullptr;
}

SkRect ImageFilter::onRevalidate(InvalidationController*, const SkMatrix&) {
    SkASSERT(this->hasInval());

    fFilter = this->onRevalidateFilter();
    return SkRect::MakeEmpty();
}

ExternalImageFilter:: ExternalImageFilter() = default;
ExternalImageFilter::~ExternalImageFilter() = default;

sk_sp<DropShadowImageFilter> DropShadowImageFilter::Make(sk_sp<ImageFilter> input) {
    return sk_sp<DropShadowImageFilter>(new DropShadowImageFilter(std::move(input)));
}

DropShadowImageFilter::DropShadowImageFilter(sk_sp<ImageFilter> input)
    : INHERITED(std::move(input)) {}

DropShadowImageFilter::~DropShadowImageFilter() = default;

sk_sp<SkImageFilter> DropShadowImageFilter::onRevalidateFilter() {
    if (fMode == Mode::kShadowOnly) {
        return SkImageFilters::DropShadowOnly(fOffset.x(), fOffset.y(), fSigma.x(), fSigma.y(),
                                              fColor, this->refInput(0));
    } else {
        return SkImageFilters::DropShadow(fOffset.x(), fOffset.y(), fSigma.x(), fSigma.y(),
                                          fColor, this->refInput(0));
    }
}

sk_sp<BlurImageFilter> BlurImageFilter::Make(sk_sp<ImageFilter> input) {
    return sk_sp<BlurImageFilter>(new BlurImageFilter(std::move(input)));
}

BlurImageFilter::BlurImageFilter(sk_sp<ImageFilter> input)
    : INHERITED(std::move(input)) {}

BlurImageFilter::~BlurImageFilter() = default;

sk_sp<SkImageFilter> BlurImageFilter::onRevalidateFilter() {
    return SkImageFilters::Blur(fSigma.x(), fSigma.y(), fTileMode, this->refInput(0));
}

sk_sp<BlendModeEffect> BlendModeEffect::Make(sk_sp<RenderNode> child, SkBlendMode mode) {
    return child ? sk_sp<BlendModeEffect>(new BlendModeEffect(std::move(child), mode))
                 : nullptr;
}

BlendModeEffect::BlendModeEffect(sk_sp<RenderNode> child, SkBlendMode mode)
    : INHERITED(std::move(child))
    , fMode(mode) {}

BlendModeEffect::~BlendModeEffect() = default;

void BlendModeEffect::onRender(SkCanvas* canvas, const RenderContext* ctx) const {
    const auto local_ctx = ScopedRenderContext(canvas, ctx).modulateBlendMode(fMode);

    this->INHERITED::onRender(canvas, local_ctx);
}

const RenderNode* BlendModeEffect::onNodeAt(const SkPoint& p) const {
    // TODO: we likely need to do something more sophisticated than delegate to descendants here.
    return this->INHERITED::onNodeAt(p);
}

sk_sp<LayerEffect> LayerEffect::Make(sk_sp<RenderNode> child, SkBlendMode mode) {
    return child ? sk_sp<LayerEffect>(new LayerEffect(std::move(child), mode))
                 : nullptr;
}

LayerEffect::LayerEffect(sk_sp<RenderNode> child, SkBlendMode mode)
    : INHERITED(std::move(child))
    , fMode(mode) {}

LayerEffect::~LayerEffect() = default;

void LayerEffect::onRender(SkCanvas* canvas, const RenderContext* ctx) const {
    SkAutoCanvasRestore acr(canvas, false);

    // Commit any potential pending paint effects to their own layer.
    const auto local_ctx = ScopedRenderContext(canvas, ctx).setIsolation(this->bounds(),
                                                                         canvas->getTotalMatrix(),
                                                                         true);

    SkPaint layer_paint;
    if (ctx) {
        // Apply all optional context overrides upfront.
        ctx->modulatePaint(canvas->getTotalMatrix(), &layer_paint);
    }
    layer_paint.setBlendMode(fMode);

    canvas->saveLayer(nullptr, &layer_paint);

    this->INHERITED::onRender(canvas, nullptr);
}

} // namespace sksg
