/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGColorFilter_DEFINED
#define SkSGColorFilter_DEFINED

#include "SkSGEffectNode.h"

#include "skia/core/SkBlendMode.h"

#include <vector>

class SkColorFilter;

namespace sksg {

class Color;

/**
 * Base class for nodes which apply a color filter when rendering their descendants.
 */
class ColorFilter : public EffectNode {
protected:
    SK_API explicit ColorFilter(sk_sp<RenderNode>);

    SK_API void onRender(SkCanvas*, const RenderContext*) const final;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const final;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) final;

    virtual sk_sp<SkColorFilter> onRevalidateFilter() = 0;

private:
    sk_sp<SkColorFilter> fColorFilter;

    using INHERITED = EffectNode;
};

/**
 * Wrapper for externally-managed SkColorFilters.
 *
 * Allows attaching non-sksg color filters to the render tree.
 */
class ExternalColorFilter final : public EffectNode {
public:
    SK_API static sk_sp<ExternalColorFilter> Make(sk_sp<RenderNode> child);

    SK_API ~ExternalColorFilter() override;

    SG_ATTRIBUTE(ColorFilter, sk_sp<SkColorFilter>, fColorFilter)

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;

private:
    SK_API explicit ExternalColorFilter(sk_sp<RenderNode>);

    sk_sp<SkColorFilter> fColorFilter;

    using INHERITED = EffectNode;
};

/**
 * Concrete SkModeColorFilter Effect node.
 */
class ModeColorFilter final : public ColorFilter {
public:
    SK_API ~ModeColorFilter() override;

    SK_API static sk_sp<ModeColorFilter> Make(sk_sp<RenderNode> child,
                                       sk_sp<Color> color,
                                       SkBlendMode mode);

protected:
    SK_API sk_sp<SkColorFilter> onRevalidateFilter() override;

private:
    SK_API ModeColorFilter(sk_sp<RenderNode>, sk_sp<Color>, SkBlendMode);

    const sk_sp<Color> fColor;
    const SkBlendMode  fMode;

    using INHERITED = ColorFilter;
};

/**
 * Tint/multi-tone color effect: maps RGB colors to the [C0,C1][C1,C2]..[Cn-1,Cn] gradient
 * based on input luminance (where the colors are evenly distributed across the luminance domain),
 * then mixes with the input based on weight.  Leaves alpha unchanged.
 */
class GradientColorFilter final : public ColorFilter {
public:
    SK_API ~GradientColorFilter() override;

    SK_API static sk_sp<GradientColorFilter> Make(sk_sp<RenderNode> child,
                                           sk_sp<Color> c0, sk_sp<Color> c1);
    SK_API static sk_sp<GradientColorFilter> Make(sk_sp<RenderNode> child,
                                           std::vector<sk_sp<Color>>);

    SG_ATTRIBUTE(Weight, float, fWeight)

protected:
    SK_API sk_sp<SkColorFilter> onRevalidateFilter() override;

private:
    SK_API GradientColorFilter(sk_sp<RenderNode>, std::vector<sk_sp<Color>>);

    const std::vector<sk_sp<Color>> fColors;

    float                           fWeight = 0;

    using INHERITED = ColorFilter;
};

} // namespace sksg

#endif // SkSGColorFilter_DEFINED
