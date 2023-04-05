/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkColorFilter.h>
#include <skia/core/SkMaskFilter.h>
#include <skia/core/SkShader.h>
#include <skia/core/SkTypeface.h>
#include <skia/private/SkChecksum.h>
#include "src/core/SkPictureFlat.h"

#include <memory>

///////////////////////////////////////////////////////////////////////////////

void SkTypefacePlayback::setCount(size_t count) {
    fCount = count;
    fArray = std::make_unique<sk_sp<SkTypeface>[]>(count);
}
