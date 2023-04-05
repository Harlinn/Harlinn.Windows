/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeTurbulence_DEFINED
#define SkSVGFeTurbulence_DEFINED

#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeTurbulence : public SkSVGFe {
public:
    static sk_sp<SkSVGFeTurbulence> Make() {
        return sk_sp<SkSVGFeTurbulence>(new SkSVGFeTurbulence());
    }

    SVG_ATTR(BaseFrequency, SkSVGFeTurbulenceBaseFrequency, SkSVGFeTurbulenceBaseFrequency({}))
    SVG_ATTR(NumOctaves, SkSVGIntegerType, SkSVGIntegerType(1))
    SVG_ATTR(Seed, SkSVGNumberType, SkSVGNumberType(0))
    SVG_ATTR(TurbulenceType,
             SkSVGFeTurbulenceType,
             SkSVGFeTurbulenceType(SkSVGFeTurbulenceType::Type::kTurbulence))

protected:
    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override { return {}; }

    SK_API bool parseAndSetAttribute(const char*, const char*) override;
private:
    SkSVGFeTurbulence() : INHERITED(SkSVGTag::kFeTurbulence) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeTurbulence_DEFINED
