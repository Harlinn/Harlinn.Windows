/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGShape_DEFINED
#define SkSVGShape_DEFINED

#include "skia/core/SkPath.h"
#include "skia/svg/SkSVGTransformableNode.h"

class SkSVGLengthContext;
class SkPaint;

class SkSVGShape : public SkSVGTransformableNode {
public:
    SK_API void appendChild(sk_sp<SkSVGNode>) override;

protected:
    SK_API SkSVGShape(SkSVGTag);

    SK_API void onRender(const SkSVGRenderContext&) const final;

    virtual void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,
                        SkPathFillType) const = 0;

private:
    using INHERITED = SkSVGTransformableNode;
};

#endif // SkSVGShape_DEFINED
