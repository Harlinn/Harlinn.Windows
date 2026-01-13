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

#ifndef PBRT_BASE_FILM_H
#define PBRT_BASE_FILM_H

#include <pbrto/pbrt.h>

#include <pbrto/base/filter.h>
#include <pbrto/util/pstd.h>
#include <pbrto/util/taggedptr.h>

#include <string>

namespace pbrt {

class VisibleSurface;
class RGBFilm;
class GBufferFilm;
class SpectralFilm;
class PixelSensor;

// Film Definition
class Film : public TaggedPointer<RGBFilm, GBufferFilm, SpectralFilm> {
  public:
    // Film Interface
    PBRT_CPU_GPU inline void AddSample(Point2i pFilm, SampledSpectrum L,
                                       const SampledWavelengths &lambda,
                                       const VisibleSurface *visibleSurface,
                                       Float weight);

    PBRT_CPU_GPU inline Bounds2f SampleBounds() const;

    PBRT_CPU_GPU
    bool UsesVisibleSurface() const;

    PBRT_CPU_GPU
    void AddSplat(Point2f p, SampledSpectrum v, const SampledWavelengths &lambda);

    PBRT_CPU_GPU inline SampledWavelengths SampleWavelengths(Float u) const;

    PBRT_CPU_GPU inline Point2i FullResolution() const;
    PBRT_CPU_GPU inline Bounds2i PixelBounds() const;
    PBRT_CPU_GPU inline Float Diagonal() const;

    void WriteImage(ImageMetadata metadata, Float splatScale = 1);

    PBRT_CPU_GPU inline RGB ToOutputRGB(SampledSpectrum L,
                                        const SampledWavelengths &lambda) const;

    Image GetImage(ImageMetadata *metadata, Float splatScale = 1);

    PBRT_CPU_GPU
    RGB GetPixelRGB(Point2i p, Float splatScale = 1) const;

    PBRT_CPU_GPU inline Filter GetFilter() const;
    PBRT_CPU_GPU inline const PixelSensor *GetPixelSensor() const;
    std::string GetFilename() const;

    using TaggedPointer::TaggedPointer;

    static Film Create(const std::string &name, const ParameterDictionary &parameters,
                       Float exposureTime, const CameraTransform &cameraTransform,
                       Filter filter, const FileLoc *loc, Allocator alloc);

    std::string ToString() const;

    PBRT_CPU_GPU inline void ResetPixel(Point2i p);
};

}  // namespace pbrt

#endif  // PBRT_BASE_FILM_H
