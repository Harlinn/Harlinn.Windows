// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_GPU_DENOISER_H
#define PBRT_GPU_DENOISER_H

#include <pbrto/pbrt.h>

#include <pbrto/util/color.h>
#include <pbrto/util/vecmath.h>

#include "optix.h"

namespace pbrt
{

    class Denoiser
    {
    public:
        PBRTO_EXPORT Denoiser( Vector2i resolution, bool haveAlbedoAndNormal );

        // All pointers should be to GPU memory.
        // |n| and |albedo| should be nullptr iff \haveAlbedoAndNormal| is false.
        PBRTO_EXPORT void Denoise( RGB* rgb, Normal3f* n, RGB* albedo, RGB* result );

    private:
        Vector2i resolution;
        bool haveAlbedoAndNormal;
        OptixDenoiser denoiserHandle;
        OptixDenoiserSizes memorySizes;
        void* denoiserState, * scratchBuffer, * intensity;
    };

}  // namespace pbrt

#endif  // PBRT_GPU_DENOISER_H
