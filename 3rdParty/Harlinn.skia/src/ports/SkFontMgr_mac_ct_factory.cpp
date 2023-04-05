/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkTypes.h>
#if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)

#include <skia/core/SkFontMgr.h>
#include <skia/ports/SkFontMgr_mac_ct.h>

sk_sp<SkFontMgr> SkFontMgr::Factory() {
    return SkFontMgr_New_CoreText(nullptr);
}

#endif//defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
