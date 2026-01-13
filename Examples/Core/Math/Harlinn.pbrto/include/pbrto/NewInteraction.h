#pragma once
#ifndef PBRTO_NEWINTERACTION_H_
#define PBRTO_NEWINTERACTION_H_

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
#include <pbrto/base/NewCamera.h>
#include <pbrto/base/NewLight.h>
#include <pbrto/base/NewMaterial.h>
#include <pbrto/base/NewMedium.h>
#include <pbrto/base/NewSampler.h>
#include <pbrto/NewRay.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedPtr.h>
#include <pbrto/util/NewVecMath.h>

#include <limits>

namespace pbrto
{

    // Interaction Definition
    class Interaction
    {

    public:
        // Interaction Public Members
        Vector3f::Simd wo;
        Normal3f::Simd n;
        Point3fi pi;
        Point2f uv;
        Float time = 0;
        const MediumInterface* mediumInterface = nullptr;
        Medium medium = nullptr;

        // Interaction Public Methods
        Interaction( ) = default;

        Interaction( const Point3fi& pi, const Normal3f::Simd& n, const Point2f& uv, const Vector3f::Simd& wo, Float time )
            : pi( pi ), n( n ), uv( uv ), wo( Normalize( wo ) ), time( time )
        {
        }

        Point3f::Simd p( ) const 
        { 
            return Point3f( pi ); 
        }

        bool IsSurfaceInteraction( ) const 
        { 
            return n != Normal3f::Simd( 0, 0, 0 ); 
        }
        bool IsMediumInteraction( ) const 
        { 
            return !IsSurfaceInteraction( ); 
        }

        const SurfaceInteraction& AsSurface( ) const
        {
            NCHECK( IsSurfaceInteraction( ) );
            return ( const SurfaceInteraction& )*this;
        }

        SurfaceInteraction& AsSurface( )
        {
            NCHECK( IsSurfaceInteraction( ) );
            return ( SurfaceInteraction& )*this;
        }

        // used by medium ctor
        Interaction( const Point3f::Simd& p, const Vector3f::Simd& wo, Float time, Medium medium )
            : pi( p ), time( time ), wo( wo ), medium( medium )
        { }
        Interaction( const Point3f::Simd& p, const Normal3f::Simd& n, Float time, Medium medium )
            : pi( p ), n( n ), time( time ), medium( medium )
        { }
        Interaction( const Point3f::Simd& p, const Point2f& uv )
            : pi( p ), uv( uv ) 
        { }

        Interaction( const Point3fi& pi, const Normal3f::Simd& n, Float time = 0, Point2f uv = {} )
            : pi( pi ), n( n ), uv( uv ), time( time )
        {
        }
        Interaction( const Point3fi& pi, const Normal3f::Simd& n, Point2f uv )
            : pi( pi ), n( n ), uv( uv ) 
        { }

        Interaction( const Point3f::Simd& p, Float time, Medium medium )
            : pi( p ), time( time ), medium( medium )
        {
        }
        Interaction( const Point3f::Simd& p, const MediumInterface* mediumInterface )
            : pi( p ), mediumInterface( mediumInterface )
        {
        }
        Interaction( const Point3f::Simd& p, Float time, const MediumInterface* mediumInterface )
            : pi( p ), time( time ), mediumInterface( mediumInterface )
        {
        }
        const MediumInteraction& AsMedium( ) const
        {
            NCHECK( IsMediumInteraction( ) );
            return ( const MediumInteraction& )*this;
        }
        MediumInteraction& AsMedium( )
        {
            NCHECK( IsMediumInteraction( ) );
            return ( MediumInteraction& )*this;
        }

        std::string ToString( ) const;

        Point3f::Simd OffsetRayOrigin( const Vector3f::Simd& w ) const
        { 
            return pbrto::OffsetRayOrigin( pi, n, w ); 
        }
        

        Point3f::Simd OffsetRayOrigin( const Point3f::Simd& pt ) const
        { 
            return OffsetRayOrigin( pt - p( ) ); 
        }

        RayDifferential SpawnRay( const Vector3f::Simd& d ) const
        {
            return RayDifferential( OffsetRayOrigin( d ), d, time, GetMedium( d ) );
        }

        Ray SpawnRayTo( const Point3f::Simd& p2 ) const
        {
            Ray r = pbrto::SpawnRayTo( pi, n, time, p2 );
            r.medium = GetMedium( r.d );
            return r;
        }

        Ray SpawnRayTo( const Interaction& it ) const
        {
            Ray r = pbrto::SpawnRayTo( pi, n, time, it.pi, it.n );
            r.medium = GetMedium( r.d );
            return r;
        }

        Medium GetMedium( const Vector3f::Simd& w ) const
        {
            if ( mediumInterface )
                return ScalarDot( w, n ) > 0 ? mediumInterface->outside : mediumInterface->inside;
            return medium;
        }

        Medium GetMedium( ) const
        {
            if ( mediumInterface )
                NDCHECK_EQ( mediumInterface->inside, mediumInterface->outside );
            return mediumInterface ? mediumInterface->inside : medium;
        }

        
    };

    // MediumInteraction Definition
    class MediumInteraction : public Interaction
    {
    public:
        // MediumInteraction Public Members
        PhaseFunction phase;

        // MediumInteraction Public Methods
        MediumInteraction( ) 
            : phase( nullptr ) 
        { }
        MediumInteraction( const Point3f::Simd& p, const Vector3f::Simd& wo, Float time, Medium medium, PhaseFunction phase )
            : Interaction( p, wo, time, medium ), phase( phase )
        {
        }

        std::string ToString( ) const;

        
    };

    // SurfaceInteraction Definition
    class SurfaceInteraction : public Interaction
    {
    public:
        // SurfaceInteraction Public Members
        Vector3f::Simd dpdu, dpdv;
        Normal3f::Simd dndu, dndv;
        struct
        {
            Normal3f::Simd n;
            Vector3f::Simd dpdu, dpdv;
            Normal3f::Simd dndu, dndv;
        } shading;
        Vector3f::Simd dpdx, dpdy;
        Float dudx = 0, dvdx = 0, dudy = 0, dvdy = 0;

        int faceIndex = 0;
        Material material;
        Light areaLight;
        

        // SurfaceInteraction Public Methods
        SurfaceInteraction( ) = default;

        SurfaceInteraction( const Point3fi& pi, const Point2f& uv, const Vector3f::Simd& wo, const Vector3f::Simd& dpdu, const Vector3f::Simd& dpdv, const Normal3f::Simd& dndu, const Normal3f::Simd& dndv, Float time, bool flipNormal )
            : Interaction( pi, Normal3f( Normalize( Cross( dpdu, dpdv ) ) ), uv, wo, time ),
              dpdu( dpdu ),
              dpdv( dpdv ),
              dndu( dndu ),
              dndv( dndv )
        {
            // Initialize shading geometry from true geometry
            shading.n = n;
            shading.dpdu = dpdu;
            shading.dpdv = dpdv;
            shading.dndu = dndu;
            shading.dndv = dndv;

            // Adjust normal based on orientation and handedness
            if ( flipNormal )
            {
                n *= -1;
                shading.n *= -1;
            }
        }

        SurfaceInteraction( const Point3fi& pi, const Point2f& uv, const Vector3f::Simd& wo, const Vector3f::Simd& dpdu, const Vector3f::Simd& dpdv, const Normal3f::Simd& dndu, const Normal3f::Simd& dndv, Float time, bool flipNormal, int faceIndex )
            : SurfaceInteraction( pi, uv, wo, dpdu, dpdv, dndu, dndv, time, flipNormal )
        {
            this->faceIndex = faceIndex;
        }

        void SetShadingGeometry( const Normal3f::Simd& ns, const Vector3f::Simd& dpdus, const Vector3f::Simd& dpdvs, const Normal3f::Simd& dndus, const Normal3f::Simd& dndvs, bool orientationIsAuthoritative )
        {
            // Compute _shading.n_ for _SurfaceInteraction_
            shading.n = ns;
            NDCHECK_NE( shading.n, Normal3f::Simd( 0, 0, 0 ) );
            if ( orientationIsAuthoritative )
                n = FaceForward( n, shading.n );
            else
                shading.n = FaceForward( shading.n, n );

            // Initialize _shading_ partial derivative values
            shading.dpdu = dpdus;
            shading.dpdv = dpdvs;
            shading.dndu = dndus;
            shading.dndv = dndvs;
            while ( ScalarLengthSquared( shading.dpdu ) > 1e16f ||
                ScalarLengthSquared( shading.dpdv ) > 1e16f )
            {
                shading.dpdu /= 1e8f;
                shading.dpdv /= 1e8f;
            }
        }

        std::string ToString( ) const;

        void SetIntersectionProperties( Material mtl, Light area, const MediumInterface* primMediumInterface, Medium rayMedium )
        {
            material = mtl;
            areaLight = area;
            NCHECK_GE( ScalarDot( n, shading.n ), 0. );
            // Set medium properties at surface intersection
            if ( primMediumInterface && primMediumInterface->IsMediumTransition( ) )
                mediumInterface = primMediumInterface;
            else
                medium = rayMedium;
        }

        void ComputeDifferentials( const RayDifferential& r, Camera camera, int samplesPerPixel );

        void SkipIntersection( RayDifferential* ray, Float t ) const;

        using Interaction::SpawnRay;
        RayDifferential SpawnRay( const RayDifferential& rayi, const BSDF& bsdf, const Vector3f::Simd& wi, int /*BxDFFlags*/ flags, Float eta ) const;

        BSDF GetBSDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer, Sampler sampler );
        BSSRDF GetBSSRDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer );

        SampledSpectrum Le( const Vector3f::Simd& w, const SampledWavelengths& lambda ) const;

        
    };

}

#endif
