#pragma once
#ifndef PBRTO_BASE_NEWBXDF_H_
#define PBRTO_BASE_NEWBXDF_H_

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

#include <pbrto/util/NewPStd.hh>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    struct MeasuredBxDFData;

    // BxDFReflTransFlags Definition
    enum class BxDFReflTransFlags
    {
        Unset = 0,
        Reflection = 1 << 0,
        Transmission = 1 << 1,
        All = Reflection | Transmission
    };

    PBRT_CPU_GPU
        inline BxDFReflTransFlags operator|( BxDFReflTransFlags a, BxDFReflTransFlags b )
    {
        return BxDFReflTransFlags( ( int )a | ( int )b );
    }

    PBRT_CPU_GPU
        inline int operator&( BxDFReflTransFlags a, BxDFReflTransFlags b )
    {
        return ( ( int )a & ( int )b );
    }

    PBRT_CPU_GPU
        inline BxDFReflTransFlags& operator|=( BxDFReflTransFlags& a, BxDFReflTransFlags b )
    {
        ( int& )a |= int( b );
        return a;
    }

    std::string ToString( BxDFReflTransFlags flags );

    // BxDFFlags Definition
    enum BxDFFlags
    {
        Unset = 0,
        Reflection = 1 << 0,
        Transmission = 1 << 1,
        Diffuse = 1 << 2,
        Glossy = 1 << 3,
        Specular = 1 << 4,
        // Composite _BxDFFlags_ definitions
        DiffuseReflection = Diffuse | Reflection,
        DiffuseTransmission = Diffuse | Transmission,
        GlossyReflection = Glossy | Reflection,
        GlossyTransmission = Glossy | Transmission,
        SpecularReflection = Specular | Reflection,
        SpecularTransmission = Specular | Transmission,
        All = Diffuse | Glossy | Specular | Reflection | Transmission

    };

    PBRT_CPU_GPU
        inline BxDFFlags operator|( BxDFFlags a, BxDFFlags b )
    {
        return BxDFFlags( ( int )a | ( int )b );
    }

    PBRT_CPU_GPU
        inline int operator&( BxDFFlags a, BxDFFlags b )
    {
        return ( ( int )a & ( int )b );
    }

    PBRT_CPU_GPU
        inline int operator&( BxDFFlags a, BxDFReflTransFlags b )
    {
        return ( ( int )a & ( int )b );
    }

    PBRT_CPU_GPU
        inline BxDFFlags& operator|=( BxDFFlags& a, BxDFFlags b )
    {
        ( int& )a |= int( b );
        return a;
    }

    // BxDFFlags Inline Functions
    PBRT_CPU_GPU
        inline bool IsReflective( BxDFFlags f )
    {
        return f & BxDFFlags::Reflection;
    }
    PBRT_CPU_GPU
        inline bool IsTransmissive( BxDFFlags f )
    {
        return f & BxDFFlags::Transmission;
    }
    PBRT_CPU_GPU
        inline bool IsDiffuse( BxDFFlags f )
    {
        return f & BxDFFlags::Diffuse;
    }
    PBRT_CPU_GPU
        inline bool IsGlossy( BxDFFlags f )
    {
        return f & BxDFFlags::Glossy;
    }
    PBRT_CPU_GPU
        inline bool IsSpecular( BxDFFlags f )
    {
        return f & BxDFFlags::Specular;
    }
    PBRT_CPU_GPU
        inline bool IsNonSpecular( BxDFFlags f )
    {
        return f & ( BxDFFlags::Diffuse | BxDFFlags::Glossy );
    }

    std::string ToString( BxDFFlags flags );

    // TransportMode Definition
    enum class TransportMode
    {
        Radiance,
        Importance
    };

    PBRT_CPU_GPU
        inline TransportMode operator!( TransportMode mode )
    {
        return ( mode == TransportMode::Radiance ) ? TransportMode::Importance : TransportMode::Radiance;
    }

    std::string ToString( TransportMode mode );

    // BSDFSample Definition
    struct BSDFSample
    {
        SampledSpectrum f;
        Vector3f wi;
        Float pdf = 0;
        BxDFFlags flags;
        Float eta = 1;
        bool pdfIsProportional = false;

        // BSDFSample Public Methods
        BSDFSample( ) = default;
        PBRT_CPU_GPU
#ifdef PBRT_USES_HCCMATH
            BSDFSample( const SampledSpectrum& f, const Vector3f& wi, Float pdf, BxDFFlags flags, Float eta = 1.f, bool pdfIsProportional = false )
#else
            BSDFSample( SampledSpectrum f, Vector3f wi, Float pdf, BxDFFlags flags, Float eta = 1.f, bool pdfIsProportional = false )
#endif
            : f( f ), wi( wi ), pdf( pdf ), flags( flags ), eta( eta ), pdfIsProportional( pdfIsProportional )
        {
        }

        PBRT_CPU_GPU
            bool IsReflection( ) const
        {
            return pbrt::IsReflective( flags );
        }
        PBRT_CPU_GPU
            bool IsTransmission( ) const
        {
            return pbrt::IsTransmissive( flags );
        }
        PBRT_CPU_GPU
            bool IsDiffuse( ) const
        {
            return pbrt::IsDiffuse( flags );
        }
        PBRT_CPU_GPU
            bool IsGlossy( ) const
        {
            return pbrt::IsGlossy( flags );
        }
        PBRT_CPU_GPU
            bool IsSpecular( ) const
        {
            return pbrt::IsSpecular( flags );
        }

        std::string ToString( ) const;

    };

    class DiffuseBxDF;
    class DiffuseTransmissionBxDF;
    class DielectricBxDF;
    class ThinDielectricBxDF;
    class HairBxDF;
    class MeasuredBxDF;
    class ConductorBxDF;
    class NormalizedFresnelBxDF;
    class CoatedDiffuseBxDF;
    class CoatedConductorBxDF;

    // BxDF Definition
    class BxDF : public TaggedPointer<DiffuseTransmissionBxDF, DiffuseBxDF, CoatedDiffuseBxDF, CoatedConductorBxDF, DielectricBxDF, ThinDielectricBxDF, HairBxDF, MeasuredBxDF, ConductorBxDF, NormalizedFresnelBxDF>
    {
    public:
        // BxDF Interface
        PBRT_CPU_GPU inline BxDFFlags Flags( ) const;

        using TaggedPointer::TaggedPointer;

        std::string ToString( ) const;

        PBRT_CPU_GPU
#ifdef PBRT_USES_HCCMATH
            inline SampledSpectrum f( const Vector3f& wo, const Vector3f& wi, TransportMode mode ) const;
#else
            inline SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const;
#endif

        PBRT_CPU_GPU
#ifdef PBRT_USES_HCCMATH
            inline pstdo::optional<BSDFSample> Sample_f( const Vector3f& wo, Float uc, const Point2f& u, TransportMode mode = TransportMode::Radiance, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;
#else
            inline pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode = TransportMode::Radiance, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;
#endif
        PBRT_CPU_GPU
#ifdef PBRT_USES_HCCMATH
            inline Float PDF( const Vector3f& wo, const Vector3f& wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;
#else
            inline Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;
#endif

#ifdef PBRT_USES_HCCMATH
        PBRT_CPU_GPU
            SampledSpectrum rho( const Vector3f& wo, const pstdo::span<const Float>& uc, const pstdo::span<const Point2f>& u2 ) const;
        SampledSpectrum rho( const pstdo::span<const Point2f>& u1, const pstdo::span<const Float>& uc2, const pstdo::span<const Point2f>& u2 ) const;
#else
        PBRT_CPU_GPU
            SampledSpectrum rho( Vector3f wo, pstdo::span<const Float> uc, pstdo::span<const Point2f> u2 ) const;
        SampledSpectrum rho( pstdo::span<const Point2f> u1, pstdo::span<const Float> uc2, pstdo::span<const Point2f> u2 ) const;
#endif
        PBRT_CPU_GPU
            inline void Regularize( );
    };

}  // namespace pbrt

#endif
