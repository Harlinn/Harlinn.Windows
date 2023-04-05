/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkFontMgr.h>
#include <skia/ports/SkFontMgr_directory.h>

#ifndef SK_FONT_FILE_PREFIX
#  if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
#    define SK_FONT_FILE_PREFIX "/System/Library/Fonts/"
#  else
#    define SK_FONT_FILE_PREFIX "/usr/share/fonts/"
#  endif
#endif

sk_sp<SkFontMgr> SkFontMgr::Factory() {
    return SkFontMgr_New_Custom_Directory(SK_FONT_FILE_PREFIX);
}
