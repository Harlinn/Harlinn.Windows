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

#ifndef PBRT_WAVEFRONT_INTEGRATOR_H
#define PBRT_WAVEFRONT_INTEGRATOR_H

#include <pbrto/pbrt.h>

#include <pbrto/base/bxdf.h>
#include <pbrto/base/camera.h>
#include <pbrto/base/film.h>
#include <pbrto/base/filter.h>
#include <pbrto/base/light.h>
#include <pbrto/base/lightsampler.h>
#include <pbrto/base/sampler.h>
#ifdef PBRT_BUILD_GPU_RENDERER
#include <pbrto/gpu/util.h>
#endif  // PBRT_BUILD_GPU_RENDERER
#include <pbrto/options.h>
#include <pbrto/util/parallel.h>
#include <pbrto/util/pstd.h>
#include <pbrto/wavefront/workitems.h>
#include <pbrto/wavefront/workqueue.h>

namespace pbrt {

class BasicScene;
class GUI;

// WavefrontAggregate Definition
class WavefrontAggregate {
  public:
    // WavefrontAggregate Interface
    virtual ~WavefrontAggregate() = default;

    virtual Bounds3f Bounds() const = 0;

    virtual void IntersectClosest(int maxRays, const RayQueue *rayQ,
                                  EscapedRayQueue *escapedRayQ,
                                  HitAreaLightQueue *hitAreaLightQ,
                                  MaterialEvalQueue *basicMtlQ,
                                  MaterialEvalQueue *universalMtlQ,
                                  MediumSampleQueue *mediumSampleQ,
                                  RayQueue *nextRayQ) const = 0;

    virtual void IntersectShadow(int maxRays, ShadowRayQueue *shadowRayQueue,
                                 SOA<PixelSampleState> *pixelSampleState) const = 0;
    virtual void IntersectShadowTr(int maxRays, ShadowRayQueue *shadowRayQueue,
                                   SOA<PixelSampleState> *pixelSampleState) const = 0;

    virtual void IntersectOneRandom(
        int maxRays, SubsurfaceScatterQueue *subsurfaceScatterQueue) const = 0;
};

// WavefrontPathIntegrator Definition
class WavefrontPathIntegrator {
  public:
    // WavefrontPathIntegrator Public Methods
    Float Render();

    void GenerateCameraRays(int y0, Transform movingFromcamera, int sampleIndex);
    template <typename Sampler>
    void GenerateCameraRays(int y0, Transform movingFromCamera, int sampleIndex);

    void GenerateRaySamples(int wavefrontDepth, int sampleIndex);
    template <typename Sampler>
    void GenerateRaySamples(int wavefrontDepth, int sampleIndex);

    void TraceShadowRays(int wavefrontDepth);
    void SampleMediumInteraction(int wavefrontDepth);
    template <typename PhaseFunction>
    void SampleMediumScattering(int wavefrontDepth);
    void SampleSubsurface(int wavefrontDepth);

    void HandleEscapedRays();
    void HandleEmissiveIntersection();

    void EvaluateMaterialsAndBSDFs(int wavefrontDepth, Transform movingFromCamera);
    template <typename ConcreteMaterial>
    void EvaluateMaterialAndBSDF(int wavefrontDepth, Transform movingFromCamera);
    template <typename ConcreteMaterial, typename TextureEvaluator>
    void EvaluateMaterialAndBSDF(MaterialEvalQueue *evalQueue, Transform movingFromCamera,
                                 int wavefrontDepth);

    void UpdateFilm();

    WavefrontPathIntegrator(pstd::pmr::memory_resource *memoryResource,
                            BasicScene &scene);

    template <typename F>
    void ParallelFor(const char *description, int nItems, F &&func) {
        if (Options->useGPU)
#ifdef PBRT_BUILD_GPU_RENDERER
            GPUParallelFor(description, nItems, func);
#else
            LOG_FATAL("Options->useGPU was set without PBRT_BUILD_GPU_RENDERER enabled");
#endif
        else
            pbrt::ParallelFor(0, nItems, func);
    }

    template <typename F>
    void Do(const char *description, F &&func) {
        if (Options->useGPU)
#ifdef PBRT_BUILD_GPU_RENDERER
            GPUParallelFor(description, 1, [=] PBRT_GPU(int) mutable { func(); });
#else
            LOG_FATAL("Options->useGPU was set without PBRT_BUILD_GPU_RENDERER enabled");
#endif
        else
            func();
    }

    RayQueue *CurrentRayQueue(int wavefrontDepth) {
        return rayQueues[wavefrontDepth & 1];
    }
    RayQueue *NextRayQueue(int wavefrontDepth) {
        return rayQueues[(wavefrontDepth + 1) & 1];
    }

#ifdef PBRT_BUILD_GPU_RENDERER
    void PrefetchGPUAllocations();
#endif  // PBRT_BUILD_GPU_RENDERER

    // --display-server methods
    void StartDisplayThread();
    void UpdateDisplayRGBFromFilm(Bounds2i pixelBounds);
    void StopDisplayThread();

    // --interactive support
    void UpdateFramebufferFromFilm(Bounds2i pixelBounds, Float exposure, RGB *rgb);

    // WavefrontPathIntegrator Member Variables
    bool initializeVisibleSurface;
    bool haveSubsurface;
    bool haveMedia;
    pstd::array<bool, Material::NumTags()> haveBasicEvalMaterial;
    pstd::array<bool, Material::NumTags()> haveUniversalEvalMaterial;

    struct Stats {
        Stats(int maxDepth, Allocator alloc);

        std::string Print() const;

        // Note: not atomics: tid 0 always updates them for everyone...
        uint64_t cameraRays = 0;
        pstd::vector<uint64_t> indirectRays, shadowRays;
    };
    Stats *stats;

    pstd::pmr::memory_resource *memoryResource;

    Filter filter;
    Film film;
    Sampler sampler;
    Camera camera;
    pstd::vector<Light> *infiniteLights;
    LightSampler lightSampler;

    int maxDepth, samplesPerPixel;
    bool regularize;

    int scanlinesPerPass, maxQueueSize;

    SOA<PixelSampleState> pixelSampleState;

    RayQueue *rayQueues[2];

    WavefrontAggregate *aggregate = nullptr;

    MediumSampleQueue *mediumSampleQueue = nullptr;
    MediumScatterQueue *mediumScatterQueue = nullptr;

    EscapedRayQueue *escapedRayQueue = nullptr;

    HitAreaLightQueue *hitAreaLightQueue = nullptr;

    MaterialEvalQueue *basicEvalMaterialQueue = nullptr;
    MaterialEvalQueue *universalEvalMaterialQueue = nullptr;

    ShadowRayQueue *shadowRayQueue = nullptr;

    GetBSSRDFAndProbeRayQueue *bssrdfEvalQueue = nullptr;
    SubsurfaceScatterQueue *subsurfaceScatterQueue = nullptr;

    RGB *displayRGB = nullptr, *displayRGBHost = nullptr;
    std::atomic<bool> *exitCopyThread;
    std::thread *copyThread;
};

}  // namespace pbrt

#endif  // PBRT_WAVEFRONT_INTEGRATOR_H
