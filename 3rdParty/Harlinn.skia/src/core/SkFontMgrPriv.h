/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFontMgrPriv_DEFINED
#define SkFontMgrPriv_DEFINED

#include <skia/core/SkFontMgr.h>

extern SK_API sk_sp<SkFontMgr> (*gSkFontMgr_DefaultFactory)();

#endif  // SkFontMgrPriv_DEFINED
