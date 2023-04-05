/*
 * Copyright 2021 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGMask_DEFINED
#define SkSVGMask_DEFINED

#include "skia/svg/SkSVGHiddenContainer.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGMask final : public SkSVGHiddenContainer {
public:
    static sk_sp<SkSVGMask> Make() {
        return sk_sp<SkSVGMask>(new SkSVGMask());
    }

    SVG_ATTR(X     , SkSVGLength, SkSVGLength(-10, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Y     , SkSVGLength, SkSVGLength(-10, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Width , SkSVGLength, SkSVGLength(120, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Height, SkSVGLength, SkSVGLength(120, SkSVGLength::Unit::kPercentage))

    SVG_ATTR(MaskUnits, SkSVGObjectBoundingBoxUnits,
             SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kObjectBoundingBox))
    SVG_ATTR(MaskContentUnits, SkSVGObjectBoundingBoxUnits,
             SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kUserSpaceOnUse))

private:
    friend class SkSVGRenderContext;

    SkSVGMask() : INHERITED(SkSVGTag::kMask) {}

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API SkRect bounds(const SkSVGRenderContext&) const;
    SK_API void renderMask(const SkSVGRenderContext&) const;

    using INHERITED = SkSVGHiddenContainer;
};

#endif // SkSVGMask_DEFINED
