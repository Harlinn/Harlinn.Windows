/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGTransformableNode_DEFINED
#define SkSVGTransformableNode_DEFINED

#include "skia/core/SkMatrix.h"
#include "skia/svg/SkSVGNode.h"

class SkSVGTransformableNode : public SkSVGNode {
public:
    void setTransform(const SkSVGTransformType& t) { fTransform = t; }

protected:
    SK_API SkSVGTransformableNode(SkSVGTag);

    SK_API bool onPrepareToRender(SkSVGRenderContext*) const override;

    SK_API void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

    SK_API void mapToParent(SkPath*) const;

    SK_API void mapToParent(SkRect*) const;

private:
    // FIXME: should be sparse
    SkSVGTransformType fTransform;

    using INHERITED = SkSVGNode;
};

#endif // SkSVGTransformableNode_DEFINED
