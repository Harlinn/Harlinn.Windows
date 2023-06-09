/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "tests/Test.h"
#include "skia/tools/Resources.h"
#include "skia/tools/ToolUtils.h"

#include "skia/codec/SkCodec.h"
#include "skia/core/SkBitmap.h"
#include "skia/core/SkData.h"
#include "skia/core/SkEncodedImageFormat.h"
#include "skia/core/SkImageEncoder.h"
#include "skia/core/SkImageInfo.h"

DEF_TEST(AlphaEncodedInfo, r) {
    auto codec = SkCodec::MakeFromStream(GetResourceAsStream("images/grayscale.jpg"));
    REPORTER_ASSERT(r, codec->getInfo().colorType() == kGray_8_SkColorType);

    SkBitmap bm;
    bm.allocPixels(codec->getInfo().makeColorType(kAlpha_8_SkColorType).makeColorSpace(nullptr));
    auto result = codec->getPixels(codec->getInfo(), bm.getPixels(), bm.rowBytes());
    REPORTER_ASSERT(r, result == SkCodec::kSuccess);

    auto data = SkEncodeBitmap(bm, SkEncodedImageFormat::kPNG, 100);
    REPORTER_ASSERT(r, data);

    codec = SkCodec::MakeFromData(std::move(data));
    REPORTER_ASSERT(r, codec);
    // TODO: Make SkEncodedInfo public and compare to its version of kAlpha_8.
    REPORTER_ASSERT(r, codec->getInfo().colorType() == kAlpha_8_SkColorType);

    SkBitmap bm2;
    bm2.allocPixels(codec->getInfo().makeColorSpace(nullptr));
    result = codec->getPixels(bm2.pixmap());
    REPORTER_ASSERT(r, result == SkCodec::kSuccess);

    REPORTER_ASSERT(r, ToolUtils::equal_pixels(bm.pixmap(), bm2.pixmap()));
}
