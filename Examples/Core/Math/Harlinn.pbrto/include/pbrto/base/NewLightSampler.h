#pragma once
#ifndef PBRTO_BASE_NEWLIGHTSAMPLER_H_
#define PBRTO_BASE_NEWLIGHTSAMPLER_H_

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


#include <string>

namespace pbrto
{

    // SampledLight Definition
    struct SampledLight
    {
        Light light;
        Float p = 0;
        std::string ToString( ) const;
    };

    class UniformLightSampler;
    class PowerLightSampler;
    class BVHLightSampler;
    class ExhaustiveLightSampler;

    // LightSampler Definition
    class LightSampler : public TaggedPointer<UniformLightSampler, PowerLightSampler, ExhaustiveLightSampler, BVHLightSampler>
    {
    public:
        // LightSampler Interface
        using TaggedPointer::TaggedPointer;

        static LightSampler Create( const std::string& name, pstdo::span<const Light> lights, Allocator alloc );

        std::string ToString( ) const;

        PBRT_CPU_GPU
            inline pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const;

        PBRT_CPU_GPU
            inline Float PMF( const LightSampleContext& ctx, Light light ) const;

        PBRT_CPU_GPU
            inline pstdo::optional<SampledLight> Sample( Float u ) const;

        PBRT_CPU_GPU
            inline Float PMF( Light light ) const;
    };

}

#endif
