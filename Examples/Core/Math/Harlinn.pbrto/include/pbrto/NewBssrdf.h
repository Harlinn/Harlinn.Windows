#pragma once
#ifndef PBRTO_NEWBSSRDF_H_
#define PBRTO_NEWBSSRDF_H_

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

#include <pbrto/base/NewBssrdf.h>
#include <pbrto/NewBsdf.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewScattering.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedptr.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    // BSSRDFSample Definition
    struct BSSRDFSample
    {
        SampledSpectrum Sp, pdf;
        Vector3f::Simd wo;
        BSDF Sw;

        BSSRDFSample( ) = default;
        BSSRDFSample( const SampledSpectrum& Sp, const SampledSpectrum& pdf, const BSDF& Sw, const Vector3f::Simd& wo )
            : Sp( Sp ), pdf( pdf ), wo( wo ), Sw( Sw )
        { }
        
    };

    // SubsurfaceInteraction Definition
    struct SubsurfaceInteraction
    {
        // SubsurfaceInteraction Public Members
        Point3fi pi;
        Normal3f::Simd n, ns;
        Vector3f::Simd dpdu, dpdv, dpdus, dpdvs;

        // SubsurfaceInteraction Public Methods
        SubsurfaceInteraction( ) = default;
        SubsurfaceInteraction( const SurfaceInteraction& si )
            : pi( si.pi ),
              n( si.n ),
              dpdu( si.dpdu ),
              dpdv( si.dpdv ),
              ns( si.shading.n ),
              dpdus( si.shading.dpdu ),
              dpdvs( si.shading.dpdv )
        {
        }

        operator SurfaceInteraction( ) const
        {
            SurfaceInteraction si;
            si.pi = pi;
            si.n = n;
            si.dpdu = dpdu;
            si.dpdv = dpdv;
            si.shading.n = ns;
            si.shading.dpdu = dpdus;
            si.shading.dpdv = dpdvs;
            return si;
        }

        Point3f p( ) const { return Point3f( pi ); }

        
    };

    // BSSRDF Function Declarations
    Float BeamDiffusionSS( Float sigma_s, Float sigma_a, Float g, Float eta, Float r );
    Float BeamDiffusionMS( Float sigma_s, Float sigma_a, Float g, Float eta, Float r );

    void ComputeBeamDiffusionBSSRDF( Float g, Float eta, BSSRDFTable* t );

    // BSSRDFTable Definition
    struct BSSRDFTable
    {
        // BSSRDFTable Public Members
        pstdo::vector<Float> rhoSamples, radiusSamples;
        pstdo::vector<Float> profile;
        pstdo::vector<Float> rhoEff;
        pstdo::vector<Float> profileCDF;

        // BSSRDFTable Public Methods
        BSSRDFTable( int nRhoSamples, int nRadiusSamples, Allocator alloc );

        std::string ToString( ) const;

        Float EvalProfile( int rhoIndex, int radiusIndex ) const
        {
            NCHECK( rhoIndex >= 0 && rhoIndex < rhoSamples.size( ) );
            NCHECK( radiusIndex >= 0 && radiusIndex < radiusSamples.size( ) );
            return profile[ rhoIndex * radiusSamples.size( ) + radiusIndex ];
        }
    };

    // BSSRDFProbeSegment Definition
    struct BSSRDFProbeSegment
    {
        Point3f::Simd p0, p1;

        // BSSRDFProbeSegment Public Methods
        BSSRDFProbeSegment( ) = default;
        BSSRDFProbeSegment( const Point3f::Simd& p0, const Point3f::Simd& p1 )
            : p0( p0 ), p1( p1 ) 
        { }

        
    };

    // TabulatedBSSRDF Definition
    class TabulatedBSSRDF
    {
        // TabulatedBSSRDF Private Members
        Point3f::Simd po;
        Vector3f::Simd wo;
        Normal3f::Simd ns;
        SampledSpectrum sigma_t, rho;
        Float eta;
        const BSSRDFTable* table;
    public:
        // TabulatedBSSRDF Type Definitions
        using BxDF = NormalizedFresnelBxDF;

        // TabulatedBSSRDF Public Methods
        TabulatedBSSRDF( ) = default;
        TabulatedBSSRDF( const Point3f::Simd& po, const Normal3f::Simd& ns, const Vector3f::Simd& wo, Float eta, const SampledSpectrum& sigma_a, const SampledSpectrum& sigma_s, const BSSRDFTable* table )
            : po( po ), wo( wo ), eta( eta ), ns( ns ), table( table )
        {
            sigma_t = sigma_a + sigma_s;
            rho = SafeDiv( sigma_s, sigma_t );
        }

        SampledSpectrum Sp( const Point3f::Simd& pi ) const 
        { 
            return Sr( ScalarDistance( po, pi ) ); 
        }

        SampledSpectrum Sr( Float r ) const
        {
            SampledSpectrum Sr( 0.f );
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                // Convert $r$ into unitless optical radius $r_{\roman{optical}}$
                Float rOptical = r * sigma_t[ i ];

                // Compute spline weights to interpolate BSSRDF at _i_th wavelength
                int rhoOffset, radiusOffset;
                Float rhoWeights[ 4 ], radiusWeights[ 4 ];
                if ( !CatmullRomWeights( table->rhoSamples, rho[ i ], &rhoOffset, rhoWeights ) ||
                    !CatmullRomWeights( table->radiusSamples, rOptical, &radiusOffset, radiusWeights ) )
                    continue;

                // Set BSSRDF value _Sr[i]_ using tensor spline interpolation
                Float sr = 0;
                for ( int j = 0; j < 4; ++j )
                    for ( int k = 0; k < 4; ++k )
                    {
                        // Accumulate contribution of $(j,k)$ table sample
                        if ( Float weight = rhoWeights[ j ] * radiusWeights[ k ]; weight != 0 )
                            sr +=
                            weight * table->EvalProfile( rhoOffset + j, radiusOffset + k );
                    }
                // Cancel marginal PDF factor from tabulated BSSRDF profile
                if ( rOptical != 0 )
                    sr /= 2 * Pi * rOptical;

                Sr[ i ] = sr;
            }
            // Transform BSSRDF value into rendering space units
            Sr *= Sqr( sigma_t );

            return ClampZero( Sr );
        }

        pstdo::optional<Float> SampleSr( Float u ) const
        {
            if ( sigma_t[ 0 ] == 0 )
                return {};
            return SampleCatmullRom2D( table->rhoSamples, table->radiusSamples, table->profile,
                table->profileCDF, rho[ 0 ], u ) /
                sigma_t[ 0 ];
        }

        SampledSpectrum PDF_Sr( Float r ) const
        {
            SampledSpectrum pdf( 0.f );
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                // Convert $r$ into unitless optical radius $r_{\roman{optical}}$
                Float rOptical = r * sigma_t[ i ];

                // Compute spline weights to interpolate BSSRDF at _i_th wavelength
                int rhoOffset, radiusOffset;
                Float rhoWeights[ 4 ], radiusWeights[ 4 ];
                if ( !CatmullRomWeights( table->rhoSamples, rho[ i ], &rhoOffset, rhoWeights ) ||
                    !CatmullRomWeights( table->radiusSamples, rOptical, &radiusOffset,
                        radiusWeights ) )
                    continue;

                // Set BSSRDF profile probability density for wavelength
                Float sr = 0, rhoEff = 0;
                for ( int j = 0; j < 4; ++j )
                    if ( rhoWeights[ j ] != 0 )
                    {
                        // Update _rhoEff_ and _sr_ for wavelength
                        rhoEff += table->rhoEff[ rhoOffset + j ] * rhoWeights[ j ];
                        for ( int k = 0; k < 4; ++k )
                            if ( radiusWeights[ k ] != 0 )
                                sr += table->EvalProfile( rhoOffset + j, radiusOffset + k ) *
                                rhoWeights[ j ] * radiusWeights[ k ];
                    }
                // Cancel marginal PDF factor from tabulated BSSRDF profile
                if ( rOptical != 0 )
                    sr /= 2 * Pi * rOptical;

                pdf[ i ] = sr * Sqr( sigma_t[ i ] ) / rhoEff;
            }
            return ClampZero( pdf );
        }

        pstdo::optional<BSSRDFProbeSegment> SampleSp( Float u1, const Point2f& u2 ) const
        {
            // Choose projection axis for BSSRDF sampling
            Frame f;
            if ( u1 < 0.25f )
                f = Frame::FromX( ns );
            else if ( u1 < 0.5f )
                f = Frame::FromY( ns );
            else
                f = Frame::FromZ( ns );

            // Sample BSSRDF profile in polar coordinates
            pstdo::optional<Float> r = SampleSr( u2[ 0 ] );
            if ( !r )
                return {};
            Float phi = 2 * Pi * u2[ 1 ];

            // Compute BSSRDF profile bounds and intersection height
            pstdo::optional<Float> r_max = SampleSr( 0.999f );
            if ( !r_max || *r >= *r_max )
                return {};
            Float l = 2 * Math::Sqrt( Sqr( *r_max ) - Sqr( *r ) );

            // Return BSSRDF sampling ray segment
            Float sinPhi;
            Float cosPhi;
            SinCos( phi, &sinPhi, &cosPhi );
            Point3f::Simd pStart = po + *r * ( f.x * cosPhi + f.y * sinPhi ) - l * f.z / 2;
            Point3f::Simd pTarget = pStart + l * f.z;
            return BSSRDFProbeSegment{ pStart, pTarget };
        }

        SampledSpectrum PDF_Sp( const Point3f::Simd& pi, const Normal3f::Simd& ni ) const
        {
            // Express $\pti-\pto$ and $\N{}_\roman{i}$ with respect to local coordinates at
            // $\pto$
            Vector3f::Simd d = pi - po;
            Frame f = Frame::FromZ( ns );
            Vector3f dLocal = f.ToLocal( d );
            Normal3f nLocal = f.ToLocal( ni );

            // Compute BSSRDF profile radius under projection along each axis
            Float rProj[ 3 ] = 
            { 
                Math::Hypot( dLocal.y, dLocal.z ),
                Math::Hypot( dLocal.z, dLocal.x ),
                Math::Hypot( dLocal.x, dLocal.y )
            };

            // Return combined probability from all BSSRDF sampling strategies
            SampledSpectrum pdf( 0.f );
            Float axisProb[ 3 ] = { .25f, .25f, .5f };
            for ( int axis = 0; axis < 3; ++axis )
                pdf += PDF_Sr( rProj[ axis ] ) * Math::FastAbs( nLocal[ axis ] ) * axisProb[ axis ];
            return pdf;
        }

        BSSRDFSample ProbeIntersectionToSample( const SubsurfaceInteraction& si, NormalizedFresnelBxDF* bxdf ) const
        {
            *bxdf = NormalizedFresnelBxDF( eta );
            Vector3f::Simd wo = Vector3f::Simd( si.ns );
            BSDF bsdf( si.ns, si.dpdus, bxdf );
            return BSSRDFSample{ Sp( si.p( ) ), PDF_Sp( si.p( ), si.n ), bsdf, wo };
        }

        std::string ToString( ) const;

    private:
        friend struct SOA<TabulatedBSSRDF>;
        
    };

    // BSSRDF Inline Functions
    inline void SubsurfaceFromDiffuse( const BSSRDFTable& t, const SampledSpectrum& rhoEff, const SampledSpectrum& mfp, SampledSpectrum* sigma_a, SampledSpectrum* sigma_s )
    {
        for ( int c = 0; c < NSpectrumSamples; ++c )
        {
            Float rho = InvertCatmullRom( t.rhoSamples, t.rhoEff, rhoEff[ c ] );
            ( *sigma_s )[ c ] = rho / mfp[ c ];
            ( *sigma_a )[ c ] = ( 1 - rho ) / mfp[ c ];
        }
    }

    inline pstdo::optional<BSSRDFProbeSegment> BSSRDF::SampleSp( Float u1, const Point2f& u2 ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->SampleSp( u1, u2 ); };
        return Dispatch( sample );
    }

    inline BSSRDFSample BSSRDF::ProbeIntersectionToSample( const SubsurfaceInteraction& si, ScratchBuffer& scratchBuffer ) const
    {
        auto pits = [ & ]( auto ptr ) {
            using BxDF = typename std::remove_reference_t<decltype( *ptr )>::BxDF;
            BxDF* bxdf = ( BxDF* )scratchBuffer.Alloc( sizeof( BxDF ), alignof( BxDF ) );
            return ptr->ProbeIntersectionToSample( si, bxdf );
            };
        return DispatchCPU( pits );
    }

}

#endif
