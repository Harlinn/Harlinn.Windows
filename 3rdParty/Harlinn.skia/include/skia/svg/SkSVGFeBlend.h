/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeBlend_DEFINED
#define SkSVGFeBlend_DEFINED

#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeBlend : public SkSVGFe {
public:
    enum class Mode {
        kNormal,
        kMultiply,
        kScreen,
        kDarken,
        kLighten,
    };

    static sk_sp<SkSVGFeBlend> Make() { return sk_sp<SkSVGFeBlend>(new SkSVGFeBlend()); }

    SVG_ATTR(Mode, Mode, Mode::kNormal)
    SVG_ATTR(In2, SkSVGFeInputType, SkSVGFeInputType())

protected:
    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override {
        return {this->getIn(), this->getIn2()};
    }

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

private:
    SkSVGFeBlend() : INHERITED(SkSVGTag::kFeBlend) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeBlend_DEFINED
