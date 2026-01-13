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
#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/pbrt.h>

#include <pbrto/samplers.h>
#include <pbrto/wavefront/integrator.h>

#include <type_traits>

#ifdef interface
#undef interface
#endif  // interface

namespace pbrt {

// WavefrontPathIntegrator Sampler Methods
void WavefrontPathIntegrator::GenerateRaySamples(int wavefrontDepth, int sampleIndex) {
    auto generateSamples = [=](auto sampler) {
        using ConcreteSampler = std::remove_reference_t<decltype(*sampler)>;
        if constexpr (!std::is_same_v<ConcreteSampler, MLTSampler> &&
                      !std::is_same_v<ConcreteSampler, DebugMLTSampler>)
            GenerateRaySamples<ConcreteSampler>(wavefrontDepth, sampleIndex);
    };
    sampler.DispatchCPU(generateSamples);
}

template <typename ConcreteSampler>
void WavefrontPathIntegrator::GenerateRaySamples(int wavefrontDepth, int sampleIndex) {
    // Generate description string _desc_ for ray sample generation
    std::string desc = std::string("Generate ray samples - ") + ConcreteSampler::Name();

    RayQueue *rayQueue = CurrentRayQueue(wavefrontDepth);
    ForAllQueued(
        desc.c_str(), rayQueue, maxQueueSize, PBRT_CPU_GPU_LAMBDA(const RayWorkItem w) {
            // Generate samples for ray segment at current sample index
            // Find first sample dimension
            int dimension = 6 + 7 * w.depth;
            if (haveSubsurface)
                dimension += 3 * w.depth;

            // Initialize _Sampler_ for pixel, sample index, and dimension
            ConcreteSampler pixelSampler = *sampler.Cast<ConcreteSampler>();
            Point2i pPixel = pixelSampleState.pPixel[w.pixelIndex];
            pixelSampler.StartPixelSample(pPixel, sampleIndex, dimension);

            // Initialize _RaySamples_ structure with sample values
            RaySamples rs;
            rs.direct.uc = pixelSampler.Get1D();
            rs.direct.u = pixelSampler.Get2D();
            // Initialize remaining samples in _rs_
            rs.indirect.uc = pixelSampler.Get1D();
            rs.indirect.u = pixelSampler.Get2D();
            rs.indirect.rr = pixelSampler.Get1D();
            // Possibly initialize subsurface subsurface samples in _rs_
            rs.haveSubsurface = haveSubsurface;
            if (haveSubsurface) {
                rs.subsurface.uc = pixelSampler.Get1D();
                rs.subsurface.u = pixelSampler.Get2D();
            }

            // Store _RaySamples_ in pixel sample state
            pixelSampleState.samples[w.pixelIndex] = rs;
        });
}

}  // namespace pbrt
