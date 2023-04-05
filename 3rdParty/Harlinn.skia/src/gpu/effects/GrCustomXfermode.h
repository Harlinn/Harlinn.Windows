/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrCustomXfermode_DEFINED
#define GrCustomXfermode_DEFINED

#include <skia/core/SkBlendMode.h>
#include <skia/core/SkRefCnt.h>

class GrTexture;
class GrXPFactory;

/**
 * Custom Xfer modes are used for blending when the blend mode cannot be represented using blend
 * coefficients.
 */
namespace GrCustomXfermode {
    SK_API bool IsSupportedMode(SkBlendMode mode);
    SK_API const GrXPFactory* Get(SkBlendMode mode);
}  // namespace GrCustomXfermode

#endif
