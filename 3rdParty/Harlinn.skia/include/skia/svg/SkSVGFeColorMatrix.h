/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeColorMatrix_DEFINED
#define SkSVGFeColorMatrix_DEFINED

#include "skia/effects/SkColorMatrix.h"
#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeColorMatrix final : public SkSVGFe {
public:
    static sk_sp<SkSVGFeColorMatrix> Make() {
        return sk_sp<SkSVGFeColorMatrix>(new SkSVGFeColorMatrix());
    }

    SVG_ATTR(Type, SkSVGFeColorMatrixType, SkSVGFeColorMatrixType(SkSVGFeColorMatrixType::kMatrix))
    SVG_ATTR(Values, SkSVGFeColorMatrixValues, SkSVGFeColorMatrixValues())

protected:
    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override { return {this->getIn()}; }

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

private:
    SkSVGFeColorMatrix() : INHERITED(SkSVGTag::kFeColorMatrix) {}

    SK_API SkColorMatrix makeMatrixForType() const;

    SK_API static SkColorMatrix MakeSaturate(SkSVGNumberType s);

    SK_API static SkColorMatrix MakeHueRotate(SkSVGNumberType degrees);

    SK_API static SkColorMatrix MakeLuminanceToAlpha();

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeColorMatrix_DEFINED
