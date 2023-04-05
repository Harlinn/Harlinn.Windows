/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeOffset_DEFINED
#define SkSVGFeOffset_DEFINED

#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeOffset : public SkSVGFe {
public:
    static sk_sp<SkSVGFeOffset> Make() { return sk_sp<SkSVGFeOffset>(new SkSVGFeOffset()); }

    SVG_ATTR(Dx, SkSVGNumberType, SkSVGNumberType(0))
    SVG_ATTR(Dy, SkSVGNumberType, SkSVGNumberType(0))

protected:
    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override { return {this->getIn()}; }

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

private:
    SkSVGFeOffset() : INHERITED(SkSVGTag::kFeOffset) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeOffset_DEFINED
