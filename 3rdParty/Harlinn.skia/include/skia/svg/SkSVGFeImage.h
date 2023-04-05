/*
 * Copyright 2021 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeImage_DEFINED
#define SkSVGFeImage_DEFINED

#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeImage : public SkSVGFe {
public:
    static sk_sp<SkSVGFeImage> Make() { return sk_sp<SkSVGFeImage>(new SkSVGFeImage()); }

    SVG_ATTR(Href               , SkSVGIRI                , SkSVGIRI())
    SVG_ATTR(PreserveAspectRatio, SkSVGPreserveAspectRatio, SkSVGPreserveAspectRatio())

protected:
    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override { return {}; }

private:
    SkSVGFeImage() : INHERITED(SkSVGTag::kFeImage) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeImage_DEFINED
