/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrOvalEffect_DEFINED
#define GrOvalEffect_DEFINED

#include <skia/core/SkRefCnt.h>
#include <skia/gpu/GrTypes.h>
#include <skia/private/GrTypesPriv.h>
#include "src/gpu/GrFragmentProcessor.h"

class GrShaderCaps;
struct SkRect;

namespace GrOvalEffect {

/**
 * Creates an effect that performs clipping against an oval.
 */
GrFPResult Make(std::unique_ptr<GrFragmentProcessor>, GrClipEdgeType, const SkRect&,
                const GrShaderCaps&);
}  // namespace GrOvalEffect

#endif
