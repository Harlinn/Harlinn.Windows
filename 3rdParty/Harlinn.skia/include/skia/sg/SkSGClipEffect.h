/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGClipEffect_DEFINED
#define SkSGClipEffect_DEFINED

#include "SkSGEffectNode.h"

namespace sksg {

class GeometryNode;

/**
 * Concrete Effect node, applying a clip to its descendants.
 *
 */
class ClipEffect final : public EffectNode {
public:
    static sk_sp<ClipEffect> Make(sk_sp<RenderNode> child, sk_sp<GeometryNode> clip,
                                  bool aa = false) {
        return (child && clip)
            ? sk_sp<ClipEffect>(new ClipEffect(std::move(child), std::move(clip), aa))
            : nullptr;
    }

    SK_API ~ClipEffect() override;

protected:
    SK_API ClipEffect(sk_sp<RenderNode>, sk_sp<GeometryNode>, bool aa);

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    const sk_sp<GeometryNode> fClipNode;
    const bool                fAntiAlias;

    bool                      fNoop = false;

    using INHERITED = EffectNode;
};

} // namespace sksg

#endif // SkSGClipEffect_DEFINED
