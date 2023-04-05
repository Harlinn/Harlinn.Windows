/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGUse_DEFINED
#define SkSVGUse_DEFINED

#include "skia/svg/SkSVGTransformableNode.h"
#include "skia/svg/SkSVGTypes.h"

/**
 * Implements support for <use> (reference) elements.
 * (https://www.w3.org/TR/SVG11/struct.html#UseElement)
 */
class SkSVGUse final : public SkSVGTransformableNode {
public:
    static sk_sp<SkSVGUse> Make() { return sk_sp<SkSVGUse>(new SkSVGUse()); }

    SK_API void appendChild(sk_sp<SkSVGNode>) override;

    SVG_ATTR(X   , SkSVGLength, SkSVGLength(0))
    SVG_ATTR(Y   , SkSVGLength, SkSVGLength(0))
    SVG_ATTR(Href, SkSVGIRI   , SkSVGIRI())

protected:
    SK_API bool onPrepareToRender(SkSVGRenderContext*) const override;
    SK_API void onRender(const SkSVGRenderContext&) const override;
    SK_API SkPath onAsPath(const SkSVGRenderContext&) const override;
    SK_API SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override;

private:
    SK_API SkSVGUse();

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    using INHERITED = SkSVGTransformableNode;
};

#endif // SkSVGUse_DEFINED
