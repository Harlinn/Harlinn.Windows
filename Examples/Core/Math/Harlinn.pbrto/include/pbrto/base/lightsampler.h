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

#ifndef PBRT_BASE_LIGHTSAMPLER_H
#define PBRT_BASE_LIGHTSAMPLER_H

#include <pbrto/pbrt.h>

#include <pbrto/util/taggedptr.h>

#include <string>

namespace pbrt {

// SampledLight Definition
struct SampledLight {
    Light light;
    Float p = 0;
    std::string ToString() const;
};

class UniformLightSampler;
class PowerLightSampler;
class BVHLightSampler;
class ExhaustiveLightSampler;

// LightSampler Definition
class LightSampler : public TaggedPointer<UniformLightSampler, PowerLightSampler,
                                          ExhaustiveLightSampler, BVHLightSampler> {
  public:
    // LightSampler Interface
    using TaggedPointer::TaggedPointer;

    static LightSampler Create(const std::string &name, pstd::span<const Light> lights,
                               Allocator alloc);

    std::string ToString() const;

    PBRT_CPU_GPU inline pstd::optional<SampledLight> Sample(const LightSampleContext &ctx,
                                                            Float u) const;

    PBRT_CPU_GPU inline Float PMF(const LightSampleContext &ctx, Light light) const;

    PBRT_CPU_GPU inline pstd::optional<SampledLight> Sample(Float u) const;
    PBRT_CPU_GPU inline Float PMF(Light light) const;
};

}  // namespace pbrt

#endif  // PBRT_BASE_LIGHTSAMPLER_H
