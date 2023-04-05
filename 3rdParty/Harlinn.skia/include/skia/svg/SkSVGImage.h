/*
 * Copyright 2021 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGImage_DEFINED
#define SkSVGImage_DEFINED

#include "skia/svg/SkSVGTransformableNode.h"
#include "skia/svg/SkSVGTypes.h"

namespace skresources {
class ResourceProvider;
}

class SkSVGImage final : public SkSVGTransformableNode {
public:
    static sk_sp<SkSVGImage> Make() {
        return sk_sp<SkSVGImage>(new SkSVGImage());
    }

    void appendChild(sk_sp<SkSVGNode>) override {
        SkDebugf("cannot append child nodes to this element.\n");
    }

    SK_API bool onPrepareToRender(SkSVGRenderContext*) const override;
    SK_API void onRender(const SkSVGRenderContext&) const override;
    SK_API SkPath onAsPath(const SkSVGRenderContext&) const override;
    SK_API SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override;

    struct ImageInfo {
        sk_sp<SkImage> fImage;
        SkRect         fDst;
    };
    SK_API static ImageInfo LoadImage(const sk_sp<skresources::ResourceProvider>&,
                               const SkSVGIRI&,
                               const SkRect&,
                               SkSVGPreserveAspectRatio);

    SVG_ATTR(X                  , SkSVGLength             , SkSVGLength(0))
    SVG_ATTR(Y                  , SkSVGLength             , SkSVGLength(0))
    SVG_ATTR(Width              , SkSVGLength             , SkSVGLength(0))
    SVG_ATTR(Height             , SkSVGLength             , SkSVGLength(0))
    SVG_ATTR(Href               , SkSVGIRI                , SkSVGIRI())
    SVG_ATTR(PreserveAspectRatio, SkSVGPreserveAspectRatio, SkSVGPreserveAspectRatio())

protected:
    SK_API bool parseAndSetAttribute(const char*, const char*) override;

private:
    SkSVGImage() : INHERITED(SkSVGTag::kImage) {}

    using INHERITED = SkSVGTransformableNode;
};

#endif  // SkSVGImage_DEFINED
