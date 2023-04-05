/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkTypes.h"

#include "skia/core/SkICC.h"
#include "skia/core/SkString.h"
#include "skcms/skcms.h"
#include "src/core/SkColorSpacePriv.h"
#include "tests/Test.h"
#include "skia/tools/Resources.h"

DEF_TEST(AdobeRGB, r) {
    if (sk_sp<SkData> profile = GetResourceAsData("icc_profiles/AdobeRGB1998.icc")) {
        skcms_ICCProfile parsed;
        REPORTER_ASSERT(r, skcms_Parse(profile->data(), profile->size(), &parsed));

        auto got  = SkColorSpace::Make(parsed);
        auto want = SkColorSpace::MakeRGB(SkNamedTransferFn::k2Dot2, SkNamedGamut::kAdobeRGB);
        REPORTER_ASSERT(r, SkColorSpace::Equals(got.get(), want.get()));
    }
}
