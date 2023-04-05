/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/private/SkTPin.h"
#include "skia/svg/SkSVGRenderContext.h"
#include "skia/svg/SkSVGStop.h"
#include "skia/svg/SkSVGValue.h"

SkSVGStop::SkSVGStop() : INHERITED(SkSVGTag::kStop) {}

bool SkSVGStop::parseAndSetAttribute(const char* n, const char* v) {
    return INHERITED::parseAndSetAttribute(n, v) ||
           this->setOffset(SkSVGAttributeParser::parse<SkSVGLength>("offset", n, v));
}
