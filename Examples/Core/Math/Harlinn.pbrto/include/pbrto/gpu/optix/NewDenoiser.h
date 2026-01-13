/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_GPU_DENOISER_H
#define PBRT_GPU_DENOISER_H

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewVecMath.h>

#include "NewOptix.h"

namespace pbrto
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
