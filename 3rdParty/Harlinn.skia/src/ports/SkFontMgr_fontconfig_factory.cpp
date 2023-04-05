/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkFontMgr.h>
#include <skia/core/SkTypes.h>
#include <skia/ports/SkFontMgr_fontconfig.h>

sk_sp<SkFontMgr> SkFontMgr::Factory() {
    return SkFontMgr_New_FontConfig(nullptr);
}
