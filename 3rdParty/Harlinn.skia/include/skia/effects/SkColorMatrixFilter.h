#pragma once
/*
 * Copyright 2007 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkColorMatrixFilter_DEFINED
#define SkColorMatrixFilter_DEFINED

#include <skia/core/SkColorFilter.h>
#include <skia/effects/SkColorMatrix.h>

class SkColorMatrixFilter : public SkColorFilter {
public:
    /**
     *  Create a colorfilter that multiplies the RGB channels by one color, and
     *  then adds a second color, pinning the result for each component to
     *  [0..255]. The alpha components of the mul and add arguments
     *  are ignored.
     */
    SK_API static sk_sp<SkColorFilter> MakeLightingFilter(SkColor mul, SkColor add);
};

#endif
