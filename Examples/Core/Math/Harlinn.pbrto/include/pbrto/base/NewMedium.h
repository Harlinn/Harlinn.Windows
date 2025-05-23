#pragma once
#ifndef PBRTO_BASE_NEWMEDIUM_H_
#define PBRTO_BASE_NEWMEDIUM_H_

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

#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewRng.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedPtr.h>

#include <string>
#include <vector>

namespace pbrto
{

    // PhaseFunctionSample Definition
    struct PhaseFunctionSample
    {
        Vector3f::Simd wi;
        Float p;
        Float pdf;

        PhaseFunctionSample( ) = default;
        PhaseFunctionSample( Float p, const Vector3f::Simd& wi, Float pdf)
            : p(p), wi(wi), pdf( pdf )
        { }

    };

    // PhaseFunction Definition
    class HGPhaseFunction;

    class PhaseFunction : public TaggedPointer<HGPhaseFunction>
    {
    public:
        // PhaseFunction Interface
        using TaggedPointer::TaggedPointer;

        std::string ToString( ) const;

        inline Float p( const Vector3f::Simd& wo, const Vector3f::Simd& wi ) const;

        inline pstdo::optional<PhaseFunctionSample> Sample_p( const Vector3f::Simd& wo, const Point2f& u ) const;

        inline Float PDF( const Vector3f::Simd& wo, const Vector3f::Simd& wi ) const;
    };

    class HomogeneousMedium;
    class GridMedium;
    class RGBGridMedium;
    class CloudMedium;
    class NanoVDBMedium;

    struct MediumProperties;

    // RayMajorantSegment Definition
    struct RayMajorantSegment
    {
        SampledSpectrum sigma_maj;
        Float tMin, tMax;
        

        RayMajorantSegment( ) = default;

        RayMajorantSegment( Float tMin, Float tMax, const SampledSpectrum& sigma_maj )
            : tMin( tMin ), tMax( tMax ), sigma_maj( sigma_maj )
        { }

        std::string ToString( ) const;
    };

    // RayMajorantIterator Definition
    class HomogeneousMajorantIterator;
    class DDAMajorantIterator;

    class RayMajorantIterator
        : public TaggedPointer<HomogeneousMajorantIterator, DDAMajorantIterator>
    {
    public:
        using TaggedPointer::TaggedPointer;

        pstdo::optional<RayMajorantSegment> Next( );

        std::string ToString( ) const;
    };

    // Medium Definition
    class Medium
        : public TaggedPointer<  // Medium Types
        HomogeneousMedium, GridMedium, RGBGridMedium, CloudMedium, NanoVDBMedium

        >
    {
    public:
        // Medium Interface
        using TaggedPointer::TaggedPointer;

        static Medium Create( const std::string& name, const ParameterDictionary& parameters, const Transform& renderFromMedium, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        bool IsEmissive( ) const;

        MediumProperties SamplePoint( const Point3f::Simd& p, const SampledWavelengths& lambda ) const;

        // Medium Public Methods
        RayMajorantIterator SampleRay( const Ray& ray, Float tMax, const SampledWavelengths& lambda, ScratchBuffer& buf ) const;
    };

    // MediumInterface Definition
    struct MediumInterface
    {
        // MediumInterface Public Methods
        std::string ToString( ) const;

        MediumInterface( ) = default;
        PBRT_CPU_GPU
            MediumInterface( Medium medium ) : inside( medium ), outside( medium ) {}
        PBRT_CPU_GPU
            MediumInterface( Medium inside, Medium outside ) : inside( inside ), outside( outside ) {}

        PBRT_CPU_GPU
            bool IsMediumTransition( ) const { return inside != outside; }

        // MediumInterface Public Members
        Medium inside, outside;
    };

}

#endif
