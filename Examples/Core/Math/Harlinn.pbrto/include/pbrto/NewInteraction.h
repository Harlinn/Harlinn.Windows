#pragma once
#ifndef PBRTO_NEWINTERACTION_H_
#define PBRTO_NEWINTERACTION_H_

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
        Point3fi pi;
        Float time = 0;
        Vector3f wo;
        Normal3f n;
        Point2f uv;
        const MediumInterface* mediumInterface = nullptr;
        Medium medium = nullptr;

        // Interaction Public Methods
        Interaction( ) = default;

        Interaction( Point3fi pi, Normal3f n, Point2f uv, Vector3f wo, Float time )
            : pi( pi ), n( n ), uv( uv ), wo( Normalize( wo ) ), time( time )
        {
        }

        
        Point3f p( ) const { return Point3f( static_cast< float >( pi.x ), static_cast< float >( pi.y ), static_cast< float >( pi.z ) ); }

        bool IsSurfaceInteraction( ) const { return n != Normal3f( 0, 0, 0 ); }
        bool IsMediumInteraction( ) const { return !IsSurfaceInteraction( ); }

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
        Interaction( Point3f p, Vector3f wo, Float time, Medium medium )
            : pi( p ), time( time ), wo( wo ), medium( medium )
        {
        }
        Interaction( Point3f p, Normal3f n, Float time, Medium medium )
            : pi( p ), n( n ), time( time ), medium( medium )
        {
        }
        Interaction( Point3f p, Point2f uv ) : pi( p ), uv( uv ) {}
        Interaction( const Point3fi& pi, Normal3f n, Float time = 0, Point2f uv = {} )
            : pi( pi ), n( n ), uv( uv ), time( time )
        {
        }
        Interaction( const Point3fi& pi, Normal3f n, Point2f uv ) : pi( pi ), n( n ), uv( uv ) {}
        Interaction( Point3f p, Float time, Medium medium )
            : pi( p ), time( time ), medium( medium )
        {
        }
        Interaction( Point3f p, const MediumInterface* mediumInterface )
            : pi( p ), mediumInterface( mediumInterface )
        {
        }
        Interaction( Point3f p, Float time, const MediumInterface* mediumInterface )
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

        Point3f OffsetRayOrigin( Vector3f w ) const
        {
            return pbrto::OffsetRayOrigin( pi, n, w );
        }

        Point3f OffsetRayOrigin( Point3f pt ) const
        {
            Vector3f v = pt - p( );
            return OffsetRayOrigin( v );
        }

        RayDifferential SpawnRay( Vector3f d ) const
        {
            return RayDifferential( OffsetRayOrigin( d ), d, time, GetMedium( d ) );
        }

        Ray SpawnRayTo( Point3f p2 ) const
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

        Medium GetMedium( Vector3f w ) const
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
        MediumInteraction( ) : phase( nullptr ) {}
        MediumInteraction( Point3f p, Vector3f wo, Float time, Medium medium,
                PhaseFunction phase )
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
        Vector3f dpdu, dpdv;
        Normal3f dndu, dndv;
        struct
        {
            Normal3f n;
            Vector3f dpdu, dpdv;
            Normal3f dndu, dndv;
        } shading;
        int faceIndex = 0;
        Material material;
        Light areaLight;
        Vector3f dpdx, dpdy;
        Float dudx = 0, dvdx = 0, dudy = 0, dvdy = 0;

        // SurfaceInteraction Public Methods
        SurfaceInteraction( ) = default;

        SurfaceInteraction( Point3fi pi, Point2f uv, Vector3f wo, Vector3f dpdu, Vector3f dpdv,
                Normal3f dndu, Normal3f dndv, Float time, bool flipNormal )
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
                n *= static_cast< Float >( -1 );
                shading.n *= -1;
            }
        }

        SurfaceInteraction( Point3fi pi, Point2f uv, Vector3f wo, Vector3f dpdu, Vector3f dpdv,
                Normal3f dndu, Normal3f dndv, Float time, bool flipNormal,
                int faceIndex )
            : SurfaceInteraction( pi, uv, wo, dpdu, dpdv, dndu, dndv, time, flipNormal )
        {
            this->faceIndex = faceIndex;
        }

        void SetShadingGeometry( Normal3f ns, Vector3f dpdus, Vector3f dpdvs, Normal3f dndus,
                Normal3f dndvs, bool orientationIsAuthoritative )
        {
            // Compute _shading.n_ for _SurfaceInteraction_
            shading.n = ns;
            NDCHECK_NE( shading.n, Normal3f( 0, 0, 0 ) );
            if ( orientationIsAuthoritative )
                n = FaceForward( n, shading.n );
            else
                shading.n = FaceForward( shading.n, n );

            // Initialize _shading_ partial derivative values
            shading.dpdu = dpdus;
            shading.dpdv = dpdvs;
            shading.dndu = dndus;
            shading.dndv = dndvs;
            while ( LengthSquared( shading.dpdu ) > 1e16f ||
                LengthSquared( shading.dpdv ) > 1e16f )
            {
                shading.dpdu /= 1e8f;
                shading.dpdv /= 1e8f;
            }
        }

        std::string ToString( ) const;

        void SetIntersectionProperties( Material mtl, Light area,
            const MediumInterface* primMediumInterface,
            Medium rayMedium )
        {
            material = mtl;
            areaLight = area;
            NCHECK_GE( ScalarDot( n, shading.n ), 0.f );
            // Set medium properties at surface intersection
            if ( primMediumInterface && primMediumInterface->IsMediumTransition( ) )
                mediumInterface = primMediumInterface;
            else
                medium = rayMedium;
        }

        void ComputeDifferentials( const RayDifferential& r, Camera camera, int samplesPerPixel );

        void SkipIntersection( RayDifferential* ray, Float t ) const;

        using Interaction::SpawnRay;

        RayDifferential SpawnRay( const RayDifferential& rayi, const BSDF& bsdf, Vector3f wi, int /*BxDFFlags*/ flags, Float eta ) const;

        BSDF GetBSDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer, Sampler sampler );
        BSSRDF GetBSSRDF( const RayDifferential& ray, SampledWavelengths& lambda, Camera camera, ScratchBuffer& scratchBuffer );

        SampledSpectrum Le( Vector3f w, const SampledWavelengths& lambda ) const;

        
    };

}

#endif
