#pragma once
#ifndef PBRTO_UTIL_NEWSCATTERING_H_
#define PBRTO_UTIL_NEWSCATTERING_H_

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

#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedPtr.h>
#include <pbrto/util/NewVecMath.h>

namespace pbrto
{

    // Scattering Inline Functions
    inline Vector3f Reflect( Vector3f wo, Vector3f n )
    {
        return -wo + 2 * ScalarDot( wo, n ) * n;
    }

    inline bool Refract( Vector3f wi, Normal3f n, Float eta, Float* etap, Vector3f* wt )
    {
        Float cosTheta_i = ScalarDot( n, wi );
        // Potentially flip interface orientation for Snell's law
        if ( cosTheta_i < 0 )
        {
            eta = 1 / eta;
            cosTheta_i = -cosTheta_i;
            n = -n;
        }

        // Compute $\cos\,\theta_\roman{t}$ using Snell's law
        Float sin2Theta_i = std::max<Float>( 0, 1 - Sqr( cosTheta_i ) );
        Float sin2Theta_t = sin2Theta_i / Sqr( eta );
        // Handle total internal reflection case
        if ( sin2Theta_t >= 1 )
            return false;

        Float cosTheta_t = Math::Sqrt( 1 - sin2Theta_t );

        *wt = -wi / eta + ( cosTheta_i / eta - cosTheta_t ) * Vector3f( n );
        // Provide relative IOR along ray to caller
        if ( etap )
            *etap = eta;

        return true;
    }

    inline bool Refract( const Vector3f::Simd& wi, Normal3f::Simd n, Float eta, Float* etap, Vector3f* wt )
    {
        Float cosTheta_i = ScalarDot( n, wi );
        // Potentially flip interface orientation for Snell's law
        if ( cosTheta_i < 0 )
        {
            eta = 1 / eta;
            cosTheta_i = -cosTheta_i;
            n = -n;
        }

        // Compute $\cos\,\theta_\roman{t}$ using Snell's law
        Float sin2Theta_i = std::max<Float>( 0, 1 - Sqr( cosTheta_i ) );
        Float sin2Theta_t = sin2Theta_i / Sqr( eta );
        // Handle total internal reflection case
        if ( sin2Theta_t >= 1 )
        {
            return false;
        }
        Float cosTheta_t = Math::Sqrt( 1 - sin2Theta_t );

        *wt = -wi / eta + ( cosTheta_i / eta - cosTheta_t ) * n;
        // Provide relative IOR along ray to caller
        if ( etap )
        {
            *etap = eta;
        }

        return true;
    }

    inline Float HenyeyGreenstein( Float cosTheta, Float g )
    {
        // The Henyey-Greenstein phase function isn't suitable for |g| \approx
        // 1 so we clamp it before it becomes numerically instable. (It's an
        // analogous situation to BSDFs: if the BSDF is perfectly specular, one
        // should use one based on a Dirac delta distribution rather than a
        // very smooth microfacet distribution...)
        g = Clamp( g, -.99, .99 );
        Float denom = 1 + Sqr( g ) + 2 * g * cosTheta;
        return Inv4Pi * ( 1 - Sqr( g ) ) / ( denom * SafeSqrt( denom ) );
    }

    // Fresnel Inline Functions
    inline Float FrDielectric( Float cosTheta_i, Float eta )
    {
        cosTheta_i = Clamp( cosTheta_i, -1, 1 );
        // Potentially flip interface orientation for Fresnel equations
        if ( cosTheta_i < 0 )
        {
            eta = 1 / eta;
            cosTheta_i = -cosTheta_i;
        }

        // Compute $\cos\,\theta_\roman{t}$ for Fresnel equations using Snell's law
        Float sin2Theta_i = 1 - Sqr( cosTheta_i );
        Float sin2Theta_t = sin2Theta_i / Sqr( eta );
        if ( sin2Theta_t >= 1 )
            return 1.f;
        Float cosTheta_t = SafeSqrt( 1 - sin2Theta_t );

        Float r_parl = ( eta * cosTheta_i - cosTheta_t ) / ( eta * cosTheta_i + cosTheta_t );
        Float r_perp = ( cosTheta_i - eta * cosTheta_t ) / ( cosTheta_i + eta * cosTheta_t );
        return ( Sqr( r_parl ) + Sqr( r_perp ) ) / 2;
    }

    inline Float FrComplex( Float cosTheta_i, pstdo::complex<Float> eta )
    {
        using Complex = pstdo::complex<Float>;
        cosTheta_i = Clamp( cosTheta_i, 0, 1 );
        // Compute complex $\cos\,\theta_\roman{t}$ for Fresnel equations using Snell's law
        Float sin2Theta_i = 1 - Sqr( cosTheta_i );
        Complex sin2Theta_t = sin2Theta_i / Sqr( eta );
        Complex cosTheta_t = pstdo::sqrt( 1 - sin2Theta_t );

        Complex r_parl = ( eta * cosTheta_i - cosTheta_t ) / ( eta * cosTheta_i + cosTheta_t );
        Complex r_perp = ( cosTheta_i - eta * cosTheta_t ) / ( cosTheta_i + eta * cosTheta_t );
        return ( pstdo::norm( r_parl ) + pstdo::norm( r_perp ) ) / 2;
    }

    inline SampledSpectrum FrComplex( Float cosTheta_i, SampledSpectrum eta, SampledSpectrum k )
    {
        SampledSpectrum result;
        for ( int i = 0; i < NSpectrumSamples; ++i )
        {
            result[ i ] = FrComplex( cosTheta_i, pstdo::complex<Float>( eta[ i ], k[ i ] ) );
        }
        return result;
    }

    // BSSRDF Utility Declarations
    Float FresnelMoment1( Float invEta );
    Float FresnelMoment2( Float invEta );

    // TrowbridgeReitzDistribution Definition
    class TrowbridgeReitzDistribution
    {
        // TrowbridgeReitzDistribution Private Members
        Float alpha_x; 
        Float alpha_y;
    public:
        // TrowbridgeReitzDistribution Public Methods
        TrowbridgeReitzDistribution( ) = default;
        TrowbridgeReitzDistribution( Float ax, Float ay )
            : alpha_x( ax ), alpha_y( ay )
        {
            if ( !EffectivelySmooth( ) )
            {
                // If one direction has some roughness, then the other can't
                // have zero (or very low) roughness; the computation of |e| in
                // D() blows up in that case.
                alpha_x = std::max<Float>( alpha_x, 1e-4f );
                alpha_y = std::max<Float>( alpha_y, 1e-4f );
            }
        }

        inline Float D( Vector3f wm ) const
        {
            Float tan2Theta = Tan2Theta( wm );
            if ( IsInf( tan2Theta ) )
                return 0;
            Float cos4Theta = Sqr( Cos2Theta( wm ) );
            if ( cos4Theta < 1e-16f )
                return 0;
            Float e = tan2Theta * ( Sqr( CosPhi( wm ) / alpha_x ) + Sqr( SinPhi( wm ) / alpha_y ) );
            return 1 / ( Pi * alpha_x * alpha_y * cos4Theta * Sqr( 1 + e ) );
        }

        bool EffectivelySmooth( ) const 
        { 
            return std::max( alpha_x, alpha_y ) < 1e-3f; 
        }

        Float G1( Vector3f w ) const 
        { 
            return 1 / ( 1 + Lambda( w ) ); 
        }

        Float Lambda( Vector3f w ) const
        {
            Float tan2Theta = Tan2Theta( w );
            if ( IsInf( tan2Theta ) )
            {
                return 0;
            }
            Float alpha2 = Sqr( CosPhi( w ) * alpha_x ) + Sqr( SinPhi( w ) * alpha_y );
            return ( Math::Sqrt( 1 + alpha2 * tan2Theta ) - 1 ) / 2;
        }

        Float G( Vector3f wo, Vector3f wi ) const 
        { 
            return 1 / ( 1 + Lambda( wo ) + Lambda( wi ) ); 
        }

        Float D( Vector3f w, Vector3f wm ) const
        {
            return G1( w ) / AbsCosTheta( w ) * D( wm ) * ScalarAbsDot( w, wm );
        }

        Float PDF( Vector3f w, Vector3f wm ) const 
        { 
            return D( w, wm ); 
        }

        Vector3f Sample_wm( Vector3f w, Point2f u ) const
        {
            // Transform _w_ to hemispherical configuration
            Vector3f::Simd wh = Normalize( Vector3f::Simd( alpha_x * w.x, alpha_y * w.y, w.z ) );
            auto whz = wh.z( );
            if ( whz < 0 )
            {
                wh = -wh;
            }
            // Find orthonormal basis for visible normal sampling
            Vector3f::Simd T1 = ( whz < 0.99999f ) ? Normalize( Cross( Vector3f::Simd( 0, 0, 1 ), wh ) ) : Vector3f::Simd( 1, 0, 0 );
            Vector3f::Simd T2 = Cross( wh, T1 );

            // Generate uniformly distributed points on the unit disk
            Point2f p = SampleUniformDiskPolar( u );

            // Warp hemispherical projection for visible normal sampling
            Float h = Math::Sqrt( 1 - Sqr( p.x ) );
            p.y = Lerp( ( 1 + whz ) / 2, h, p.y );

            // Reproject to hemisphere and transform normal to ellipsoid configuration
            Float pz = Math::Sqrt( std::max<Float>( 0, 1 - ScalarLengthSquared( Vector2f( p ) ) ) );
            Vector3f nh = p.x * T1 + p.y * T2 + pz * wh;
            NCHECK_RARE( 1e-5f, nh.z == 0 );
            return Normalize( Vector3f( alpha_x * nh.x, alpha_y * nh.y, std::max<Float>( 1e-6f, nh.z ) ) );
        }

        std::string ToString( ) const;

        // Note that this should probably instead be "return Sqr(roughness)" to
        // be more perceptually uniform, though this wasn't noticed until some
        // time after pbrt-v4 shipped: https://github.com/mmp/pbrt-v4/issues/479.
        // therefore, we will leave it as is so that the rendered results with
        // existing pbrt-v4 scenes doesn't change unexpectedly.
        static Float RoughnessToAlpha( Float roughness ) 
        { 
            return Math::Sqrt( roughness ); 
        }

        void Regularize( )
        {
            if ( alpha_x < 0.3f )
            {
                alpha_x = Clamp( 2 * alpha_x, 0.1f, 0.3f );
            }
            if ( alpha_y < 0.3f )
            {
                alpha_y = Clamp( 2 * alpha_y, 0.1f, 0.3f );
            }
        }
    };

}

#endif
