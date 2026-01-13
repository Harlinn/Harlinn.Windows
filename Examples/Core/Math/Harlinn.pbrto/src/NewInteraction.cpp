#include "pch.h"

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

#include <pbrto/NewInteraction.h>

#include <pbrto/base/NewCamera.h>
#include <pbrto/NewCameras.h>
#include <pbrto/NewLights.h>
#include <pbrto/NewMaterials.h>
#include <pbrto/NewOptions.h>
#include <pbrto/NewParamDict.h>
#include <pbrto/NewSamplers.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewRng.h>

#include <cmath>

namespace pbrto
{

    std::string Interaction::ToString( ) const
    {
        return StringPrintf(
            "[ Interaction pi: %s n: %s uv: %s wo: %s time: %s "
            "medium: %s mediumInterface: %s ]",
            pi, n, uv, wo, time, medium ? medium.ToString( ).c_str( ) : "(nullptr)",
            mediumInterface ? mediumInterface->ToString( ).c_str( ) : "(nullptr)" );
    }

    std::string MediumInteraction::ToString( ) const
    {
        return StringPrintf(
            "[ MediumInteraction pi: %s n: %s uv: %s wo: %s time: %s "
            "medium: %s mediumInterface: %s phase: %s ]",
            pi, n, uv, wo, time, medium ? medium.ToString( ).c_str( ) : "(nullptr)",
            mediumInterface ? mediumInterface->ToString( ).c_str( ) : "(nullptr)",
            phase ? phase.ToString( ).c_str( ) : "(nullptr)" );
    }

    // SurfaceInteraction Method Definitions
    void SurfaceInteraction::ComputeDifferentials( const RayDifferential& ray, Camera camera, int samplesPerPixel )
    {
        if ( GetOptions( ).disableTextureFiltering )
        {
            dudx = dudy = dvdx = dvdy = 0;
            dpdx = dpdy = Vector3f::Simd( 0, 0, 0 );
            return;
        }
        auto txd = ScalarDot( n, ray.rxDirection );
        auto tyd = ScalarDot( n, ray.ryDirection );
        if ( ray.hasDifferentials && txd != 0 && tyd != 0 )
        {
            // Estimate screen-space change in $\pt{}$ using ray differentials
            // Compute auxiliary intersection points with plane, _px_ and _py_
            auto pv = p( );
            Float d = -ScalarDot( n, Vector3f::Simd( pv ) );
            
            Float tx = ( -ScalarDot( n, ray.rxOrigin ) - d ) / txd;
            NDCHECK( !IsInf( tx ) && !IsNaN( tx ) );
            Point3f::Simd px = ray.rxOrigin + tx * ray.rxDirection;
            Float ty = ( -ScalarDot( n, ray.ryOrigin ) - d ) / tyd;
            NDCHECK( !IsInf( ty ) && !IsNaN( ty ) );
            Point3f::Simd py = ray.ryOrigin + ty * ray.ryDirection;

            dpdx = px - pv;
            dpdy = py - pv;

        }
        else
        {
            //Vector3f tmpdpdx, tmpdpdy;
            // Approximate screen-space change in $\pt{}$ based on camera projection
            camera.Approximate_dp_dxy( p( ), n, time, samplesPerPixel, &dpdx, &dpdy );
            //dpdx = tmpdpdx, dpdy = tmpdpdy;

        }
        // Estimate screen-space change in $(u,v)$
        // Compute $\transpose{\XFORM{A}} \XFORM{A}$ and its determinant
        Float ata00 = ScalarDot( dpdu, dpdu ); 
        Float ata01 = ScalarDot( dpdu, dpdv );
        Float ata11 = ScalarDot( dpdv, dpdv );
        Float invDet = 1 / DifferenceOfProducts( ata00, ata11, ata01, ata01 );
        invDet = IsFinite( invDet ) ? invDet : 0.f;

        // Compute $\transpose{\XFORM{A}} \VEC{b}$ for $x$ and $y$
        Float atb0x = ScalarDot( dpdu, dpdx ); 
        Float atb1x = ScalarDot( dpdv, dpdx );
        Float atb0y = ScalarDot( dpdu, dpdy ); 
        Float atb1y = ScalarDot( dpdv, dpdy );

        // Compute $u$ and $v$ derivatives with respect to $x$ and $y$
        dudx = DifferenceOfProducts( ata11, atb0x, ata01, atb1x ) * invDet;
        dvdx = DifferenceOfProducts( ata00, atb1x, ata01, atb0x ) * invDet;
        dudy = DifferenceOfProducts( ata11, atb0y, ata01, atb1y ) * invDet;
        dvdy = DifferenceOfProducts( ata00, atb1y, ata01, atb0y ) * invDet;

        // Clamp derivatives of $u$ and $v$ to reasonable values
        dudx = IsFinite( dudx ) ? Clamp( dudx, -1e8f, 1e8f ) : 0.f;
        dvdx = IsFinite( dvdx ) ? Clamp( dvdx, -1e8f, 1e8f ) : 0.f;
        dudy = IsFinite( dudy ) ? Clamp( dudy, -1e8f, 1e8f ) : 0.f;
        dvdy = IsFinite( dvdy ) ? Clamp( dvdy, -1e8f, 1e8f ) : 0.f;
    }

    void SurfaceInteraction::SkipIntersection( RayDifferential* ray, Float t ) const
    {
        *( ( Ray* )ray ) = SpawnRay( ray->d );
        if ( ray->hasDifferentials )
        {
            ray->rxOrigin = ray->rxOrigin + t * ray->rxDirection;
            ray->ryOrigin = ray->ryOrigin + t * ray->ryDirection;
        }
    }

    RayDifferential SurfaceInteraction::SpawnRay( const RayDifferential& rayi, const BSDF& bsdf, const Vector3f::Simd& wi, int flags, Float eta ) const
    {
        RayDifferential rd( SpawnRay( wi ) );
        if ( rayi.hasDifferentials )
        {
            // Compute ray differentials for specular reflection or transmission
            // Compute common factors for specular ray differentials
            Normal3f::Simd n = shading.n;
            Normal3f::Simd dndx = shading.dndu * dudx + shading.dndv * dvdx;
            Normal3f::Simd dndy = shading.dndu * dudy + shading.dndv * dvdy;
            Vector3f::Simd dwodx = -rayi.rxDirection - wo, dwody = -rayi.ryDirection - wo;
            auto pt = p( );
            if ( flags == BxDFFlags::SpecularReflection )
            {
                // Initialize origins of specular differential rays
                rd.hasDifferentials = true;
                rd.rxOrigin = pt + dpdx;
                rd.ryOrigin = pt + dpdy;

                // Compute differential reflected directions
                /*
                Float dwoDotn_dx = ScalarDot( dwodx, n ) + ScalarDot( wo, dndx );
                Float dwoDotn_dy = ScalarDot( dwody, n ) + ScalarDot( wo, dndy );
                rd.rxDirection = wi - dwodx + 2 * Dot( wo, n ) * dndx + dwoDotn_dx * n;
                rd.ryDirection = wi - dwody + 2 * Dot( wo, n ) * dndy + dwoDotn_dy * n;
                */

                auto dwoDotn_dx = Dot( dwodx, n ) + Dot( wo, dndx );
                auto dwoDotn_dy = Dot( dwody, n ) + Dot( wo, dndy );
                rd.rxDirection = wi - dwodx + 2 * Dot( wo, n ) * dndx + dwoDotn_dx * n;
                rd.ryDirection = wi - dwody + 2 * Dot( wo, n ) * dndy + dwoDotn_dy * n;

            }
            else if ( flags == BxDFFlags::SpecularTransmission )
            {
                // Initialize origins of specular differential rays
                rd.hasDifferentials = true;
                rd.rxOrigin = pt + dpdx;
                rd.ryOrigin = pt + dpdy;

                // Compute differential transmitted directions
                // Find oriented surface normal for transmission
                if ( ScalarDot( wo, n ) < 0 )
                {
                    n = -n;
                    dndx = -dndx;
                    dndy = -dndy;
                }

                // Compute partial derivatives of $\mu$
                Float dwoDotn_dx = ScalarDot( dwodx, n ) + ScalarDot( wo, dndx );
                Float dwoDotn_dy = ScalarDot( dwody, n ) + ScalarDot( wo, dndy );
                /*
                Float mu = ScalarDot( wo, n ) / eta - ScalarAbsDot( wi, n );
                Float dmudx = dwoDotn_dx * ( 1 / eta + 1 / Sqr( eta ) * ScalarDot( wo, n ) / ScalarDot( wi, n ) );
                Float dmudy = dwoDotn_dy * ( 1 / eta + 1 / Sqr( eta ) * ScalarDot( wo, n ) / ScalarDot( wi, n ) );
                */

                Float dwon = ScalarDot( wo, n );
                Float dwin = ScalarDot( wi, n );
                Float adwin = FastAbs( dwin );

                Float mu = dwon / eta - adwin;
                Float scale = 1 / eta + 1 / Sqr( eta ) * dwon / dwin;
                Float dmudx = dwoDotn_dx * scale;
                Float dmudy = dwoDotn_dy * scale;

                rd.rxDirection = wi - eta * dwodx + Vector3f::Simd( mu * dndx + dmudx * n );
                rd.ryDirection = wi - eta * dwody + Vector3f::Simd( mu * dndy + dmudy * n );
            }
        }
        // Squash potentially troublesome differentials
        if ( ScalarLengthSquared( rd.rxDirection ) > 1e16f || ScalarLengthSquared( rd.ryDirection ) > 1e16f ||
            ScalarLengthSquared( rd.rxOrigin ) > 1e16f ||
            ScalarLengthSquared( rd.ryOrigin ) > 1e16f )
            rd.hasDifferentials = false;

        return rd;
    }

    BSDF SurfaceInteraction::GetBSDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer, Sampler sampler )
    {
        // Estimate $(u,v)$ and position differentials at intersection point
        ComputeDifferentials( ray, camera, sampler.SamplesPerPixel( ) );

        // Resolve _MixMaterial_ if necessary
        while ( material.Is<MixMaterial>( ) )
        {
            MixMaterial* mix = material.Cast<MixMaterial>( );
            material = mix->ChooseMaterial( UniversalTextureEvaluator( ), *this );
        }

        // Return unset _BSDF_ if surface has a null material
        if ( !material )
            return {};

        // Evaluate normal or bump map, if present
        FloatTexture displacement = material.GetDisplacement( );
        const Image* normalMap = material.GetNormalMap( );
        if ( displacement || normalMap )
        {
            // Get shading $\dpdu$ and $\dpdv$ using normal or bump map
            /*
            Vector3f::Simd dpdu, dpdv;
            if ( normalMap )
                NormalMap( *normalMap, *this, &dpdu, &dpdv );
            else
                BumpMap( UniversalTextureEvaluator( ), displacement, *this, &dpdu, &dpdv );
            */
            auto ns = normalMap ? NormalMap( *normalMap, *this ) : BumpMap( UniversalTextureEvaluator( ), displacement, *this );

            //Normal3f::Simd ns( Normalize( Cross( dpdu, dpdv ) ) );
            SetShadingGeometry( ns, dpdu, dpdv, shading.dndu, shading.dndv, false );
        }

        // Return BSDF for surface interaction
        BSDF bsdf = material.GetBSDF( UniversalTextureEvaluator( ), *this, lambda, scratchBuffer );
        if ( bsdf && GetOptions( ).forceDiffuse )
        {
            // Override _bsdf_ with diffuse equivalent
            SampledSpectrum r = bsdf.rho( wo, { sampler.Get1D( ) }, { sampler.Get2D( ) } );
            bsdf = BSDF( shading.n, shading.dpdu, scratchBuffer.Alloc<DiffuseBxDF>( r ) );
        }
        return bsdf;
    }

    BSSRDF SurfaceInteraction::GetBSSRDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer )
    {
        // Resolve _MixMaterial_ if necessary
        while ( material.Is<MixMaterial>( ) )
        {
            MixMaterial* mix = material.Cast<MixMaterial>( );
            material = mix->ChooseMaterial( UniversalTextureEvaluator( ), *this );
        }

        return material.GetBSSRDF( UniversalTextureEvaluator( ), *this, lambda, scratchBuffer );
    }

    SampledSpectrum SurfaceInteraction::Le( const Vector3f::Simd& w, const SampledWavelengths& lambda ) const
    {
        return areaLight ? SampledSpectrum( areaLight.L( p( ), n, uv, w, lambda ) ) : SampledSpectrum( 0.f );
    }

    std::string SurfaceInteraction::ToString( ) const
    {
        return StringPrintf(
            "[ SurfaceInteraction pi: %s n: %s uv: %s wo: %s time: %s "
            "medium: %s mediumInterface: %s dpdu: %s dpdv: %s dndu: %s dndv: %s "
            "shading.n: %s shading.dpdu: %s shading.dpdv: %s "
            "shading.dndu: %s shading.dndv: %s material: %s "
            "areaLight: %s dpdx: %s dpdy: %s dudx: %f dvdx: %f "
            "dudy: %f dvdy: %f faceIndex: %d ]",
            pi, n, uv, wo, time, medium ? medium.ToString( ).c_str( ) : "(nullptr)",
            mediumInterface ? mediumInterface->ToString( ).c_str( ) : "(nullptr)", dpdu, dpdv,
            dndu, dndv, shading.n, shading.dpdu, shading.dpdv, shading.dndu, shading.dndv,
            material ? material.ToString( ).c_str( ) : "(nullptr)",
            areaLight ? areaLight.ToString( ).c_str( ) : "(nullptr)", dpdx, dpdy, dudx, dvdx,
            dudy, dvdy, faceIndex );
    }

}