/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGPattern_DEFINED
#define SkSVGPattern_DEFINED

#include "skia/svg/SkSVGHiddenContainer.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGRenderContext;

class SkSVGPattern final : public SkSVGHiddenContainer {
public:
    static sk_sp<SkSVGPattern> Make() {
        return sk_sp<SkSVGPattern>(new SkSVGPattern());
    }

    SVG_ATTR(Href, SkSVGIRI, SkSVGIRI())
    SVG_OPTIONAL_ATTR(X               , SkSVGLength)
    SVG_OPTIONAL_ATTR(Y               , SkSVGLength)
    SVG_OPTIONAL_ATTR(Width           , SkSVGLength)
    SVG_OPTIONAL_ATTR(Height          , SkSVGLength)
    SVG_OPTIONAL_ATTR(PatternTransform, SkSVGTransformType)

protected:
    SK_API SkSVGPattern();

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API bool onAsPaint(const SkSVGRenderContext&, SkPaint*) const override;

private:
    struct PatternAttributes {
        SkTLazy<SkSVGLength>        fX,
                                    fY,
                                    fWidth,
                                    fHeight;
        SkTLazy<SkSVGTransformType> fPatternTransform;
    };

    SK_API const SkSVGPattern* resolveHref(const SkSVGRenderContext&, PatternAttributes*) const;
    SK_API const SkSVGPattern* hrefTarget(const SkSVGRenderContext&) const;

    // TODO:
    //   - patternUnits
    //   - patternContentUnits

    using INHERITED = SkSVGHiddenContainer;
};

#endif // SkSVGPattern_DEFINED
