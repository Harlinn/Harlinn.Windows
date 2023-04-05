/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGOpacityEffect_DEFINED
#define SkSGOpacityEffect_DEFINED

#include "SkSGEffectNode.h"

namespace sksg {

/**
 * Concrete Effect node, applying opacity to its descendants.
 *
 */
class OpacityEffect final : public EffectNode {
public:
    static sk_sp<OpacityEffect> Make(sk_sp<RenderNode> child, float opacity = 1) {
        return child ? sk_sp<OpacityEffect>(new OpacityEffect(std::move(child), opacity)) : nullptr;
    }

    SG_ATTRIBUTE(Opacity, float, fOpacity)

protected:
    SK_API OpacityEffect(sk_sp<RenderNode>, float);

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    float fOpacity;

    using INHERITED = EffectNode;
};

} // namespace sksg

#endif // SkSGOpacityEffect_DEFINED
