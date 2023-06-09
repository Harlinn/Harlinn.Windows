#pragma once
/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkStrokeAndFillPathEffect_DEFINED
#define SkStrokeAndFillPathEffect_DEFINED

#include <skia/core/SkPaint.h>
#include <skia/core/SkPathEffect.h>
#include <skia/pathops/SkPathOps.h>

class SkStrokeAndFillPathEffect {
public:
    /*  If the paint is set to stroke, this will add the stroke and fill geometries
     *  together (hoping that the winding-direction works out).
     *
     *  If the paint is set to fill, this effect is ignored.
     *
     *  Note that if the paint is set to stroke and the stroke-width is 0, then
     *  this will turn the geometry into just a fill.
     */
    SK_API static sk_sp<SkPathEffect> Make();
};

#endif
