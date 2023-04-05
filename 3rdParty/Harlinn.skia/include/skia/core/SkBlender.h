#pragma once
/*
 * Copyright 2021 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBlender_DEFINED
#define SkBlender_DEFINED

#include <skia/core/SkBlendMode.h>
#include <skia/core/SkFlattenable.h>

/**
 * SkBlender represents a custom blend function in the Skia pipeline. When an SkBlender is
 * present in a paint, the SkBlendMode is ignored. A blender combines a source color (the
 * result of our paint) and destination color (from the canvas) into a final color.
 */
class SkBlender : public SkFlattenable {
public:
    /**
     * Create a blender that implements the specified BlendMode.
     */
    SK_API static sk_sp<SkBlender> Mode(SkBlendMode mode);

private:
    SkBlender() = default;
    friend class SkBlenderBase;

    using INHERITED = SkFlattenable;
};

#endif
