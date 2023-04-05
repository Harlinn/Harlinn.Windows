/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGGroup_DEFINED
#define SkSGGroup_DEFINED

#include "SkSGRenderNode.h"

#include <vector>

namespace sksg {

/**
 * Concrete node, grouping together multiple descendants.
 */
class Group : public RenderNode {
public:
    static sk_sp<Group> Make() {
        return sk_sp<Group>(new Group(std::vector<sk_sp<RenderNode>>()));
    }

    static sk_sp<Group> Make(std::vector<sk_sp<RenderNode>> children) {
        return sk_sp<Group>(new Group(std::move(children)));
    }

    SK_API void addChild(sk_sp<RenderNode>);
    SK_API void removeChild(const sk_sp<RenderNode>&);

    size_t size() const { return fChildren.size(); }
    bool  empty() const { return fChildren.empty(); }
    SK_API void  clear();

protected:
    SK_API Group();
    SK_API explicit Group(std::vector<sk_sp<RenderNode>>);
    SK_API ~Group() override;

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    std::vector<sk_sp<RenderNode>> fChildren;
    bool                           fRequiresIsolation = true;

    using INHERITED = RenderNode;
};

} // namespace sksg

#endif // SkSGGroup_DEFINED
