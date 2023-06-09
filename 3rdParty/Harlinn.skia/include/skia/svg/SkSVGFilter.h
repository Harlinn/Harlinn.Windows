/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFilter_DEFINED
#define SkSVGFilter_DEFINED

#include "skia/svg/SkSVGHiddenContainer.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFilter final : public SkSVGHiddenContainer {
public:
    static sk_sp<SkSVGFilter> Make() { return sk_sp<SkSVGFilter>(new SkSVGFilter()); }

    SK_API sk_sp<SkImageFilter> buildFilterDAG(const SkSVGRenderContext&) const;

    SVG_ATTR(X, SkSVGLength, SkSVGLength(-10, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Y, SkSVGLength, SkSVGLength(-10, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Width, SkSVGLength, SkSVGLength(120, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Height, SkSVGLength, SkSVGLength(120, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(FilterUnits,
             SkSVGObjectBoundingBoxUnits,
             SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kObjectBoundingBox))
    SVG_ATTR(PrimitiveUnits,
             SkSVGObjectBoundingBoxUnits,
             SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kUserSpaceOnUse))

private:
    SkSVGFilter() : INHERITED(SkSVGTag::kFilter) {}

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    using INHERITED = SkSVGHiddenContainer;
};

#endif  // SkSVGFilter_DEFINED
