#pragma once
#ifndef PBRTO_BASE_NEWCAMERA_H_
#define PBRTO_BASE_NEWCAMERA_H_

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

#include <pbrto/NewPbrt.h>

#include <pbrto/base/NewFilm.h>
#include <pbrto/base/NewFilter.h>
#include <pbrto/util/NewTransform.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{
    // Camera Declarations
    struct CameraRay;
    struct CameraRayDifferential;
    struct CameraWiSample;

    struct CameraSample;
    class CameraTransform;

    class PerspectiveCamera;
    class OrthographicCamera;
    class SphericalCamera;
    class RealisticCamera;

    // Camera Definition
    class Camera : public TaggedPointer<PerspectiveCamera, OrthographicCamera,
        SphericalCamera, RealisticCamera>
    {
    public:
        // Camera Interface
        using TaggedPointer::TaggedPointer;

        static Camera Create( const std::string& name, const ParameterDictionary& parameters,
            Medium medium, const CameraTransform& cameraTransform, Film film,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        inline pstdo::optional<CameraRay> GenerateRay( const CameraSample& sample, SampledWavelengths& lambda ) const;

        pstdo::optional<CameraRayDifferential> GenerateRayDifferential( const CameraSample& sample, SampledWavelengths& lambda ) const;

        inline Film GetFilm( ) const;

        inline Float SampleTime( Float u ) const;

        void InitMetadata( ImageMetadata* metadata ) const;

        inline const CameraTransform& GetCameraTransform( ) const;

        void Approximate_dp_dxy( const Point3f::Simd& p, const Normal3f::Simd& n, Float time, int samplesPerPixel, Vector3f::Simd* dpdx, Vector3f::Simd* dpdy ) const;

        SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRasterOut = nullptr ) const;

        void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const;

        pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const;
    };

}

#endif
