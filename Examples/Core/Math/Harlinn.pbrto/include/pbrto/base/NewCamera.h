#pragma once
#ifndef PBRTO_BASE_NEWCAMERA_H_
#define PBRTO_BASE_NEWCAMERA_H_

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
    class Camera : public TaggedPointer<PerspectiveCamera, OrthographicCamera, SphericalCamera, RealisticCamera>
    {
    public:
        // Camera Interface
        using TaggedPointer::TaggedPointer;

        static Camera Create( const std::string& name, const ParameterDictionary& parameters, Medium medium, const CameraTransform& cameraTransform, Film film, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        PBRT_CPU_GPU
            inline pstdo::optional<CameraRay> GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraRayDifferential> GenerateRayDifferential( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU inline Film GetFilm( ) const;

        PBRT_CPU_GPU inline Float SampleTime( Float u ) const;

        void InitMetadata( ImageMetadata* metadata ) const;

        PBRT_CPU_GPU
            inline const CameraTransform& GetCameraTransform( ) const;

        PBRT_CPU_GPU
            void Approximate_dp_dxy( Point3f p, Normal3f n, Float time, int samplesPerPixel, Vector3f* dpdx, Vector3f* dpdy ) const;

        PBRT_CPU_GPU
            SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRasterOut = nullptr ) const;

        PBRT_CPU_GPU
            void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const;
    };

}

#endif
