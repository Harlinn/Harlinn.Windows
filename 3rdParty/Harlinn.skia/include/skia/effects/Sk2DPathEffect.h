#pragma once
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef Sk2DPathEffect_DEFINED
#define Sk2DPathEffect_DEFINED

#include <skia/core/SkPathEffect.h>

class SkMatrix;
class SkPath;

class SkLine2DPathEffect {
public:
    SK_API static sk_sp<SkPathEffect> Make(SkScalar width, const SkMatrix& matrix);

    SK_API static void RegisterFlattenables();
};

class SkPath2DPathEffect {
public:
    SK_API static sk_sp<SkPathEffect> Make(const SkMatrix& matrix, const SkPath& path);

    SK_API static void RegisterFlattenables();
};

#endif
