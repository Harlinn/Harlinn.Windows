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

#include <pbrto/util/NewPrint.h>
#include <pbrto/util/NewPStd.h>
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

    inline BxDFReflTransFlags operator|( BxDFReflTransFlags a, BxDFReflTransFlags b )
    {
        return BxDFReflTransFlags( ( int )a | ( int )b );
    }

    inline int operator&( BxDFReflTransFlags a, BxDFReflTransFlags b )
    {
        return ( ( int )a & ( int )b );
    }

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

    inline BxDFFlags operator|( BxDFFlags a, BxDFFlags b )
    {
        return BxDFFlags( ( int )a | ( int )b );
    }

    inline int operator&( BxDFFlags a, BxDFFlags b )
    {
        return ( ( int )a & ( int )b );
    }

    inline int operator&( BxDFFlags a, BxDFReflTransFlags b )
    {
        return ( ( int )a & ( int )b );
    }

    inline BxDFFlags& operator|=( BxDFFlags& a, BxDFFlags b )
    {
        ( int& )a |= int( b );
        return a;
    }

    // BxDFFlags Inline Functions
    inline bool IsReflective( BxDFFlags f )
    {
        return f & BxDFFlags::Reflection;
    }
    inline bool IsTransmissive( BxDFFlags f )
    {
        return f & BxDFFlags::Transmission;
    }
    inline bool IsDiffuse( BxDFFlags f )
    {
        return f & BxDFFlags::Diffuse;
    }
    inline bool IsGlossy( BxDFFlags f )
    {
        return f & BxDFFlags::Glossy;
    }
    inline bool IsSpecular( BxDFFlags f )
    {
        return f & BxDFFlags::Specular;
    }
    inline bool IsNonSpecular( BxDFFlags f )
    {
        return f & ( BxDFFlags::Diffuse | BxDFFlags::Glossy );
    }

    std::string ToString( BxDFFlags flags );

    // TransportMode Definition
    enum class TransportMode { Radiance, Importance };

    inline TransportMode operator!( TransportMode mode )
    {
        return ( mode == TransportMode::Radiance ) ? TransportMode::Importance
            : TransportMode::Radiance;
    }

    std::string ToString( TransportMode mode );

    // BSDFSample Definition
    struct alignas( SampledSpectrum::Traits::AlignAs ) BSDFSample
    {
        SampledSpectrum::Simd f;
        Vector3f::Simd wi;
        Float pdf = 0;
        BxDFFlags flags;
        Float eta = 1;
        bool pdfIsProportional = false;

        // BSDFSample Public Methods
        BSDFSample( ) = default;
        BSDFSample( SampledSpectrum f, Vector3f wi, Float pdf, BxDFFlags flags, Float eta = 1, bool pdfIsProportional = false )
            : f( f ),
              wi( wi ),
              pdf( pdf ),
              flags( flags ),
              eta( eta ),
              pdfIsProportional( pdfIsProportional )
        { }

        BSDFSample( const SampledSpectrum::Simd& f, const Vector3f::Simd& wi, Float pdf, BxDFFlags flags, Float eta = 1, bool pdfIsProportional = false )
            : f( f ),
              wi( wi ),
              pdf( pdf ),
              flags( flags ),
              eta( eta ),
              pdfIsProportional( pdfIsProportional )
        { }

        bool IsReflection( ) const { return pbrto::IsReflective( flags ); }
        bool IsTransmission( ) const { return pbrto::IsTransmissive( flags ); }
        bool IsDiffuse( ) const { return pbrto::IsDiffuse( flags ); }
        bool IsGlossy( ) const { return pbrto::IsGlossy( flags ); }
        bool IsSpecular( ) const { return pbrto::IsSpecular( flags ); }

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
    class BxDF
        : public TaggedPointer<DiffuseTransmissionBxDF, DiffuseBxDF, CoatedDiffuseBxDF,
        CoatedConductorBxDF, DielectricBxDF, ThinDielectricBxDF,
        HairBxDF, MeasuredBxDF, ConductorBxDF, NormalizedFresnelBxDF>
    {
    public:
        // BxDF Interface
        inline BxDFFlags Flags( ) const;

        using TaggedPointer::TaggedPointer;

        std::string ToString( ) const;

        inline SampledSpectrum::Simd f( Vector3f::Simd wo, Vector3f::Simd wi, TransportMode mode ) const;

        inline pstdo::optional<BSDFSample> Sample_f( Vector3f::Simd wo, Float uc, Point2f u, TransportMode mode = TransportMode::Radiance, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;

        inline Float PDF( Vector3f::Simd wo, Vector3f::Simd wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;

        template<size_t N>
        SampledSpectrum::Simd rho( Vector3f::Simd wo, const std::array<Float,N>& uc, const std::array<Point2f, N>& u2 ) const;
        template<size_t N>
        SampledSpectrum::Simd rho( const std::array<Point2f, N>& u1, const std::array<Float, N>& uc2, const std::array<Point2f, N>& u2 ) const;

        PBRT_CPU_GPU inline void Regularize( );
    };

}

#endif
