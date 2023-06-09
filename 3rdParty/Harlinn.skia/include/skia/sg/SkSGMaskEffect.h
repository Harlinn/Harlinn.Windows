/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGMaskEffect_DEFINED
#define SkSGMaskEffect_DEFINED

#include "SkSGEffectNode.h"

namespace sksg {

/**
 * Concrete Effect node, applying a mask to its descendants.
 *
 */
class MaskEffect final : public EffectNode {
public:
    enum class Mode : uint32_t {
        kAlphaNormal,
        kAlphaInvert,
        kLumaNormal,
        kLumaInvert,
    };

    static sk_sp<MaskEffect> Make(sk_sp<RenderNode> child, sk_sp<RenderNode> mask,
                                  Mode mode = Mode::kAlphaNormal) {
        return (child && mask)
            ? sk_sp<MaskEffect>(new MaskEffect(std::move(child), std::move(mask), mode))
            : nullptr;
    }

    SK_API ~MaskEffect() override;

protected:
    SK_API MaskEffect(sk_sp<RenderNode>, sk_sp<RenderNode> mask, Mode);

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    const sk_sp<RenderNode> fMaskNode;
    const Mode              fMaskMode;

    using INHERITED = EffectNode;
};

} // namespace sksg

#endif // SkSGMaskEffect_DEFINED
