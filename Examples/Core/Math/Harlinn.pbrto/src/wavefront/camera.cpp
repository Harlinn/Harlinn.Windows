#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/pbrt.h>

#include <pbrto/cameras.h>
#include <pbrto/options.h>
#include <pbrto/samplers.h>
#include <pbrto/util/bluenoise.h>
#include <pbrto/util/spectrum.h>
#include <pbrto/util/vecmath.h>
#include <pbrto/wavefront/integrator.h>

namespace pbrt {

// WavefrontPathIntegrator Camera Ray Methods
void WavefrontPathIntegrator::GenerateCameraRays(int y0, Transform movingFromCamera,
                                                 int sampleIndex) {
    // Define _generateRays_ lambda function
    auto generateRays = [=](auto sampler) {
        using ConcreteSampler = std::remove_reference_t<decltype(*sampler)>;
        if constexpr (!std::is_same_v<ConcreteSampler, MLTSampler> &&
                      !std::is_same_v<ConcreteSampler, DebugMLTSampler>)
            GenerateCameraRays<ConcreteSampler>(y0, movingFromCamera, sampleIndex);
    };

    sampler.DispatchCPU(generateRays);
}

template <typename ConcreteSampler>
void WavefrontPathIntegrator::GenerateCameraRays(int y0, Transform movingFromCamera,
                                                 int sampleIndex) {
    RayQueue *rayQueue = CurrentRayQueue(0);
    ParallelFor(
        "Generate camera rays", maxQueueSize, PBRT_CPU_GPU_LAMBDA(int pixelIndex) {
            // Enqueue camera ray and set pixel state for sample
            // Compute pixel coordinates for _pixelIndex_
            Bounds2i pixelBounds = film.PixelBounds();
            int xResolution = pixelBounds.pMax.x - pixelBounds.pMin.x;
            Point2i pPixel(pixelBounds.pMin.x + pixelIndex % xResolution,
                           y0 + pixelIndex / xResolution);
            pixelSampleState.pPixel[pixelIndex] = pPixel;

            // Test pixel coordinates against pixel bounds
            if (!InsideExclusive(pPixel, pixelBounds))
                return;

            // Initialize _Sampler_ for current pixel and sample
            ConcreteSampler pixelSampler = *sampler.Cast<ConcreteSampler>();
            pixelSampler.StartPixelSample(pPixel, sampleIndex, 0);

            // Sample wavelengths for ray path
            Float lu = pixelSampler.Get1D();
            if (GetOptions().disableWavelengthJitter)
                lu = 0.5f;
            SampledWavelengths lambda = film.SampleWavelengths(lu);

            // Generate _CameraSample_ and corresponding ray
            CameraSample cameraSample = GetCameraSample(pixelSampler, pPixel, filter);
            pstd::optional<CameraRay> cameraRay =
                camera.GenerateRay(cameraSample, lambda);
            if (cameraRay)
                cameraRay->ray = movingFromCamera(cameraRay->ray);

            // Initialize remainder of _PixelSampleState_ for ray
            pixelSampleState.L[pixelIndex] = SampledSpectrum(0.f);
            pixelSampleState.lambda[pixelIndex] = lambda;
            pixelSampleState.filterWeight[pixelIndex] = cameraSample.filterWeight;
            if (initializeVisibleSurface)
                pixelSampleState.visibleSurface[pixelIndex] = VisibleSurface();

            // Enqueue camera ray for intersection tests
            if (cameraRay) {
                rayQueue->PushCameraRay(cameraRay->ray, lambda, pixelIndex);
                pixelSampleState.cameraRayWeight[pixelIndex] = cameraRay->weight;
            } else
                pixelSampleState.cameraRayWeight[pixelIndex] = SampledSpectrum(0);
        });
}

}  // namespace pbrt
