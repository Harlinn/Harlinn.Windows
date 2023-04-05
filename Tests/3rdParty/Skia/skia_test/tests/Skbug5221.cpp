/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "tests/Test.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkSurface.h"
#include "skia/gpu/GrDirectContext.h"

// This passes by not crashing.
static void test(SkCanvas* canvas) {
    canvas->scale(63, 0);
    canvas->drawString("A", 50, 50, SkFont(), SkPaint());
}

DEF_TEST(skbug5221, r) {
    sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::MakeN32Premul(256, 256)));
    test(surface->getCanvas());
}

#ifndef NO_TERMINATING_TESTS
DEF_GPUTEST_FOR_ALL_CONTEXTS(skbug5221_GPU, r, contextInfo) {
    sk_sp<SkSurface> surface(SkSurface::MakeRenderTarget(
            contextInfo.directContext(), SkBudgeted::kYes,
            SkImageInfo::Make(256, 256, kRGBA_8888_SkColorType, kPremul_SkAlphaType)));
    test(surface->getCanvas());
}
#endif