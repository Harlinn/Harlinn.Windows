/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrBlendFragmentProcessor_DEFINED
#define GrBlendFragmentProcessor_DEFINED

#include <skia/core/SkBlendMode.h>
#include <skia/core/SkRefCnt.h>

class GrFragmentProcessor;

namespace GrBlendFragmentProcessor {

/**
 * Blends src and dst inputs according to the blend mode. If either input is null, fInputColor is
 * used instead.
 */
SK_API std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> src,
                                          std::unique_ptr<GrFragmentProcessor> dst,
                                          SkBlendMode mode);

}  // namespace GrBlendFragmentProcessor

#endif
