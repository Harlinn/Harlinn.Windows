/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkCanvas.h"
#include "skia/core/SkMaskFilter.h"
#include "skia/core/SkSurface.h"
#include "skia/effects/SkImageFilters.h"
#include "tests/Test.h"
#include "skia/tools/Resources.h"

DEF_TEST(skbug_6389, r) {
    auto s = SkSurface::MakeRasterN32Premul(100, 100);
    SkPaint p;
    p.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, 5));
    p.setImageFilter(SkImageFilters::Image(GetResourceAsImage("images/mandrill_512.png"),
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, SkSamplingOptions()));
    s->getCanvas()->drawPaint(p);
}
