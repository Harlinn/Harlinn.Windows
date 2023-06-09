/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/codec/SkAndroidCodec.h"
#include "skia/core/SkBitmap.h"
#include "skia/core/SkColor.h"
#include "skia/core/SkColorSpace.h"
#include "skia/core/SkData.h"
#include "skia/core/SkEncodedImageFormat.h"
#include "skia/core/SkImageEncoder.h"
#include "skia/core/SkImageInfo.h"
#include "skia/core/SkStream.h"
#include "tests/Test.h"

#include <memory>
#include <utility>

DEF_TEST(Codec_recommendedF16, r) {
    // Encode an F16 bitmap. SkEncodeImage will encode this to a true-color PNG
    // with a bit depth of 16. SkAndroidCodec should always recommend F16 for
    // such a PNG.
    SkBitmap bm;
    bm.allocPixels(SkImageInfo::Make(10, 10, kRGBA_F16_SkColorType,
            kPremul_SkAlphaType, SkColorSpace::MakeSRGB()));
    // What is drawn is not important.
    bm.eraseColor(SK_ColorBLUE);

    SkDynamicMemoryWStream wstream;
    REPORTER_ASSERT(r, SkEncodeImage(&wstream, bm, SkEncodedImageFormat::kPNG, 100));
    auto data = wstream.detachAsData();
    auto androidCodec = SkAndroidCodec::MakeFromData(std::move(data));
    if (!androidCodec) {
        ERRORF(r, "Failed to create SkAndroidCodec");
        return;
    }

    REPORTER_ASSERT(r, androidCodec->computeOutputColorType(kN32_SkColorType)
            == kRGBA_F16_SkColorType);
}
