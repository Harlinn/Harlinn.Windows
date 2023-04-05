/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGContainer_DEFINED
#define SkSVGContainer_DEFINED

#include "skia/private/SkTArray.h"
#include "skia/svg/SkSVGTransformableNode.h"

class SkSVGContainer : public SkSVGTransformableNode {
public:
    SK_API void appendChild(sk_sp<SkSVGNode>) override;

protected:
    SK_API explicit SkSVGContainer(SkSVGTag);

    SK_API void onRender(const SkSVGRenderContext&) const override;

    SK_API SkPath onAsPath(const SkSVGRenderContext&) const override;

    SK_API SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override;

    SK_API bool hasChildren() const final;

    // TODO: add some sort of child iterator, and hide the container.
    SkSTArray<1, sk_sp<SkSVGNode>, true> fChildren;

private:
    using INHERITED = SkSVGTransformableNode;
};

#endif // SkSVGContainer_DEFINED
