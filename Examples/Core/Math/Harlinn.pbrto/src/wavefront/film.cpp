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

#include <pbrt/pbrt.h>

#include <pbrt/film.h>
#include <pbrt/wavefront/integrator.h>

namespace pbrt {

// WavefrontPathIntegrator Film Methods
void WavefrontPathIntegrator::UpdateFilm() {
    ParallelFor(
        "Update film", maxQueueSize, PBRT_CPU_GPU_LAMBDA(int pixelIndex) {
            // Check pixel against film bounds
            Point2i pPixel = pixelSampleState.pPixel[pixelIndex];
            if (!InsideExclusive(pPixel, film.PixelBounds()))
                return;

            // Compute final weighted radiance value
            SampledSpectrum Lw = SampledSpectrum(pixelSampleState.L[pixelIndex]) *
                                 pixelSampleState.cameraRayWeight[pixelIndex];

            PBRT_DBG("Adding Lw %f %f %f %f at pixel (%d, %d)\n", Lw[0], Lw[1], Lw[2],
                     Lw[3], pPixel.x, pPixel.y);
            // Provide sample radiance value to film
            SampledWavelengths lambda = pixelSampleState.lambda[pixelIndex];
            Float filterWeight = pixelSampleState.filterWeight[pixelIndex];
            if (initializeVisibleSurface) {
                // Call _Film::AddSample()_ with _VisibleSurface_ for pixel sample
                VisibleSurface visibleSurface =
                    pixelSampleState.visibleSurface[pixelIndex];
                film.AddSample(pPixel, Lw, lambda, &visibleSurface, filterWeight);

            } else
                film.AddSample(pPixel, Lw, lambda, nullptr, filterWeight);
        });
}

}  // namespace pbrt
