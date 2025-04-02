#pragma once
#ifndef PBRTO_BASE_NEWSAMPLER_H_
#define PBRTO_BASE_NEWSAMPLER_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewVecMath.h>

#include <string>
#include <vector>

namespace pbrto
{

    // CameraSample Definition
    struct CameraSample
    {
        Point2f pFilm;
        Point2f pLens;
        Float time = 0;
        Float filterWeight = 1;
        std::string ToString( ) const;
    };

    // Sampler Declarations
    class HaltonSampler;
    class PaddedSobolSampler;
    class PMJ02BNSampler;
    class IndependentSampler;
    class SobolSampler;
    class StratifiedSampler;
    class ZSobolSampler;
    class MLTSampler;
    class DebugMLTSampler;

    // Sampler Definition
    class Sampler : public TaggedPointer< PMJ02BNSampler, IndependentSampler, StratifiedSampler, HaltonSampler, PaddedSobolSampler, SobolSampler, ZSobolSampler, MLTSampler, DebugMLTSampler >
    {
    public:
        // Sampler Interface
        using TaggedPointer::TaggedPointer;

        static Sampler Create( const std::string& name, const ParameterDictionary& parameters, Point2i fullResolution, const FileLoc* loc, Allocator alloc );

        PBRT_CPU_GPU
            inline int SamplesPerPixel( ) const;

        PBRT_CPU_GPU
            inline void StartPixelSample( Point2i p, int sampleIndex, int dimension = 0 );

        PBRT_CPU_GPU
            inline Float Get1D( );

        PBRT_CPU_GPU
            inline Point2f Get2D( );

        PBRT_CPU_GPU
            inline Point2f GetPixel2D( );

        Sampler Clone( Allocator alloc = {} );

        std::string ToString( ) const;
    };

}

#endif
