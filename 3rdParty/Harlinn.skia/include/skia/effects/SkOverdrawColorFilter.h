#pragma once
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkColorFilter.h>
#include <skia/core/SkFlattenable.h>

#ifndef SkOverdrawColorFilter_DEFINED
#define SkOverdrawColorFilter_DEFINED

/**
 *  Uses the value in the src alpha channel to set the dst pixel.
 *  0             -> colors[0]
 *  1             -> colors[1]
 *  ...
 *  5 (or larger) -> colors[5]
 *
 */
class SkOverdrawColorFilter {
public:
    static constexpr int kNumColors = 6;

    SK_API static sk_sp<SkColorFilter> MakeWithSkColors(const SkColor[kNumColors]);
};

#endif // SkOverdrawColorFilter_DEFINED
