/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkTypes.h>
#if defined(SK_BUILD_FOR_WIN)  // And !SKIA_GDI?

#include <skia/core/SkFontMgr.h>
#include <skia/ports/SkTypeface_win.h>

sk_sp<SkFontMgr> SkFontMgr::Factory() {
    return SkFontMgr_New_DirectWrite();
}

#endif//defined(SK_BUILD_FOR_WIN)
