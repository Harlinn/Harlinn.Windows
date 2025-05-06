#pragma once
#ifndef PBRTO_BASE_NEWLIGHT_H_
#define PBRTO_BASE_NEWLIGHT_H_

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

#include <pbrto/base/NewMedium.h>
#include <pbrto/base/NewShape.h>
#include <pbrto/base/NewTexture.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewTaggedPtr.h>

#include <string>

namespace pbrto
{

    // LightType Definition
    enum class LightType { DeltaPosition, DeltaDirection, Area, Infinite };

    class PointLight;
    class DistantLight;
    class ProjectionLight;
    class GoniometricLight;
    class DiffuseAreaLight;
    class UniformInfiniteLight;
    class ImageInfiniteLight;
    class PortalImageInfiniteLight;
    class SpotLight;

    class LightSampleContext;
    class LightBounds;
    class CompactLightBounds;
    struct LightLiSample;
    struct LightLeSample;

    // Light Definition
    class Light : public TaggedPointer<  // Light Source Types
        PointLight, DistantLight, ProjectionLight, GoniometricLight, SpotLight,
        DiffuseAreaLight, UniformInfiniteLight, ImageInfiniteLight,
        PortalImageInfiniteLight

    >
    {
    public:
        // Light Interface
        using TaggedPointer::TaggedPointer;

        static Light Create( const std::string& name, const ParameterDictionary& parameters,
            const Transform& renderFromLight,
            const CameraTransform& cameraTransform, Medium outsideMedium,
            const FileLoc* loc, Allocator alloc );
        static Light CreateArea( const std::string& name,
            const ParameterDictionary& parameters,
            const Transform& renderFromLight,
            const MediumInterface& mediumInterface, const Shape shape,
            FloatTexture alpha, const FileLoc* loc, Allocator alloc );

        SampledSpectrum Phi( const SampledWavelengths& lambda ) const;

        inline LightType Type( ) const;

        inline pstdo::optional<LightLiSample> SampleLi( const LightSampleContext& ctx, const Point2f& u, const SampledWavelengths& lambda, bool allowIncompletePDF = false ) const;

        inline Float PDF_Li( const LightSampleContext& ctx, const Vector3f::Simd& wi, bool allowIncompletePDF = false ) const;

        std::string ToString( ) const;

        // AreaLights only
        inline SampledSpectrum L( const Point3f::Simd& p, const Normal3f::Simd& n, const Point2f& uv, const Vector3f::Simd& w, const SampledWavelengths& lambda ) const;

        // InfiniteLights only
        inline SampledSpectrum Le( const Ray& ray, const SampledWavelengths& lambda ) const;

        void Preprocess( const Bounds3f& sceneBounds );

        pstdo::optional<LightBounds> Bounds( ) const;

        pstdo::optional<LightLeSample> SampleLe( const Point2f& u1, const Point2f& u2, SampledWavelengths& lambda, Float time ) const;

        void PDF_Le( const Ray& ray, Float* pdfPos, Float* pdfDir ) const;

        // AreaLights only
        void PDF_Le( const Interaction& intr, const Vector3f::Simd& w, Float* pdfPos, Float* pdfDir ) const;
    };

}

#endif
