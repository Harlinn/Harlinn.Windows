/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGEffectNode_DEFINED
#define SkSGEffectNode_DEFINED

#include "SkSGRenderNode.h"

namespace sksg {

/**
 * Base class for nodes which apply some transformation when rendering
 * their descendants.
 *
 * This includes transforms, clipping, filters, etc.
 */
class EffectNode : public RenderNode {
protected:
    SK_API explicit EffectNode(sk_sp<RenderNode>, uint32_t inval_traits = 0);
    SK_API ~EffectNode() override;

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

    const sk_sp<RenderNode>& getChild() const { return fChild; }

private:
    sk_sp<RenderNode> fChild;

    using INHERITED = RenderNode;
};

} // namespace sksg

#endif // SkSGEffectNode_DEFINED
