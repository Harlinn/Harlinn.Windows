/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/effects/SkImageFilters.h"
#include "skia/svg/SkSVGAttributeParser.h"
#include "skia/svg/SkSVGFeOffset.h"
#include "skia/svg/SkSVGFilterContext.h"
#include "skia/svg/SkSVGRenderContext.h"
#include "skia/svg/SkSVGValue.h"

bool SkSVGFeOffset::parseAndSetAttribute(const char* name, const char* value) {
    return INHERITED::parseAndSetAttribute(name, value) ||
           this->setDx(SkSVGAttributeParser::parse<SkSVGNumberType>("dx", name, value)) ||
           this->setDy(SkSVGAttributeParser::parse<SkSVGNumberType>("dy", name, value));
}

sk_sp<SkImageFilter> SkSVGFeOffset::onMakeImageFilter(const SkSVGRenderContext& ctx,
                                                      const SkSVGFilterContext& fctx) const {
    const auto d = SkV2{this->getDx(), this->getDy()}
                 * ctx.transformForCurrentOBB(fctx.primitiveUnits()).scale;

    sk_sp<SkImageFilter> in =
            fctx.resolveInput(ctx, this->getIn(), this->resolveColorspace(ctx, fctx));
    return SkImageFilters::Offset(d.x, d.y, std::move(in), this->resolveFilterSubregion(ctx, fctx));
}
