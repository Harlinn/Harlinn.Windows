#pragma once
#ifndef PBRTO_NEWSHAPES_H_
#define PBRTO_NEWSHAPES_H_

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

#include <pbrto/base/NewShape.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewRay.h>
#include <pbrto/util/NewBufferCache.h>
#include <pbrto/util/NewMesh.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewTransform.h>
#include <pbrto/util/NewVecMath.h>

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

namespace pbrto
{

    // ShapeSample Definition
    struct ShapeSample
    {
        Interaction intr;
        Float pdf;
        std::string ToString( ) const;
    };

    // ShapeSampleContext Definition
    struct ShapeSampleContext
    {
        Normal3f::Simd n, ns;
        Point3fi pi;
        Float time;

        // ShapeSampleContext Public Methods
        ShapeSampleContext( ) = default;
        ShapeSampleContext( const Point3fi& pi, const Normal3f::Simd& n, const Normal3f::Simd& ns, Float time )
            : pi( pi ), n( n ), ns( ns ), time( time )
        {
        }
        ShapeSampleContext( const SurfaceInteraction& si )
            : pi( si.pi ), n( si.n ), ns( si.shading.n ), time( si.time )
        {
        }
        ShapeSampleContext( const MediumInteraction& mi ) 
            : pi( mi.pi ), time( mi.time ) 
        { }

        Point3f::Simd p( ) const 
        { 
            return Point3f( pi ); 
        }

        inline Point3f::Simd OffsetRayOrigin( const Vector3f::Simd& w ) const;
        Point3f::Simd OffsetRayOrigin( const Point3f::Simd& pt ) const;
        Ray SpawnRay( const Vector3f::Simd& w ) const;

        
    };

    // ShapeSampleContext Inline Methods
    inline Point3f::Simd ShapeSampleContext::OffsetRayOrigin( const Vector3f::Simd& w ) const
    {
        // Find vector _offset_ to corner of error bounds and compute initial _po_
        auto d = Dot( Abs( n ), pi.Error( ) );
        Vector3f tmp = d * Vector3f( n );
        if ( ScalarDot( w, n ) < 0 )
            tmp = -tmp;
        Point3f po = Point3f( pi ) + tmp;
        Vector3f offset = tmp;

        // Round offset point _po_ away from _p_
        for ( int i = 0; i < 3; ++i )
        {
            if ( offset[ i ] > 0 )
                po[ i ] = NextFloatUp( po[ i ] );
            else if ( offset[ i ] < 0 )
                po[ i ] = NextFloatDown( po[ i ] );
        }

        return po;
    }


    inline Point3f::Simd ShapeSampleContext::OffsetRayOrigin( const Point3f::Simd& pt ) const
    {
        return OffsetRayOrigin( pt - p( ) );
    }

    inline Ray ShapeSampleContext::SpawnRay( const Vector3f::Simd& w ) const
    {
        // Note: doesn't set medium, but that's fine, since this is only
        // used by shapes to see if ray would have intersected them
        return Ray( OffsetRayOrigin( w ), w, time );
    }

    // ShapeIntersection Definition
    struct ShapeIntersection
    {
        SurfaceInteraction intr;
        Float tHit;
        std::string ToString( ) const;
    };

    // QuadricIntersection Definition
    struct QuadricIntersection
    {
        Point3f::Simd pObj;
        Float tHit;
        Float phi;

        QuadricIntersection( ) = default;
        QuadricIntersection( Float tHit, Point3f::Simd pObj, Float phi )
            : tHit( tHit ), pObj( pObj ), phi( phi )
        { }
    };

    // Sphere Definition
    class Sphere
    {
        // Sphere Private Members
        Float radius;
        Float zMin, zMax;
        Float thetaZMin, thetaZMax, phiMax;
        const Transform* renderFromObject, * objectFromRender;
        bool reverseOrientation, transformSwapsHandedness;
    public:
        // Sphere Public Methods
        static Sphere* Create( const Transform* renderFromObject,
            const Transform* objectFromRender, bool reverseOrientation,
            const ParameterDictionary& parameters, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

        Sphere( const Transform* renderFromObject, const Transform* objectFromRender,
            bool reverseOrientation, Float radius, Float zMin, Float zMax, Float phiMax )
            : renderFromObject( renderFromObject ),
            objectFromRender( objectFromRender ),
            reverseOrientation( reverseOrientation ),
            transformSwapsHandedness( renderFromObject->SwapsHandedness( ) ),
            radius( radius ),
            zMin( Clamp( std::min( zMin, zMax ), -radius, radius ) ),
            zMax( Clamp( std::max( zMin, zMax ), -radius, radius ) ),
            thetaZMin( Math::ACos( Clamp( std::min( zMin, zMax ) / radius, -1, 1 ) ) ),
            thetaZMax( Math::ACos( Clamp( std::max( zMin, zMax ) / radius, -1, 1 ) ) ),
            phiMax( Radians( Clamp( phiMax, 0, 360 ) ) )
        {
        }

        Bounds3f Bounds( ) const;

        DirectionCone NormalBounds( ) const 
        { 
            return DirectionCone::EntireSphere( ); 
        }

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const
        {
            pstdo::optional<QuadricIntersection> isect = BasicIntersect( ray, tMax );
            if ( !isect )
                return {};
            SurfaceInteraction intr = InteractionFromIntersection( *isect, -ray.d, ray.time );
            return ShapeIntersection{ intr, isect->tHit };
        }

        pstdo::optional<QuadricIntersection> BasicIntersect( const Ray& r, Float tMax ) const
        {
            Float phi;
            Point3f pHit;
            // Transform _Ray_ origin and direction to object space
            Point3fi oi = ( *objectFromRender )( Point3fi( r.o ) );
            Vector3fi di = ( *objectFromRender )( Vector3fi( r.d ) );

            // Solve quadratic equation to compute sphere _t0_ and _t1_
            Interval t0, t1;
            // Compute sphere quadratic coefficients
            Interval a = Sqr( di.x ) + Sqr( di.y ) + Sqr( di.z );
            Interval b = 2.f * ( di.x * oi.x + di.y * oi.y + di.z * oi.z );
            Interval c = Sqr( oi.x ) + Sqr( oi.y ) + Sqr( oi.z ) - Sqr( Interval( radius ) );

            // Compute sphere quadratic discriminant _discrim_
            Vector3fi v( oi - b / ( 2.f * a ) * di );
            Interval length = ScalarLength( v );
            Interval discrim = 4.f * a * ( Interval( radius ) + length ) * ( Interval( radius ) - length );
            if ( discrim.LowerBound( ) < 0 )
                return {};

            // Compute quadratic $t$ values
            Interval rootDiscrim = Sqrt( discrim );
            Interval q;
            if ( ( Float )b < 0 )
                q = -.5f * ( b - rootDiscrim );
            else
                q = -.5f * ( b + rootDiscrim );
            t0 = q / a;
            t1 = c / q;
            // Swap quadratic $t$ values so that _t0_ is the lesser
            if ( t0.LowerBound( ) > t1.LowerBound( ) )
                pstdo::swap( t0, t1 );

            // Check quadric shape _t0_ and _t1_ for nearest intersection
            if ( t0.UpperBound( ) > tMax || t1.LowerBound( ) <= 0 )
                return {};
            Interval tShapeHit = t0;
            if ( tShapeHit.LowerBound( ) <= 0 )
            {
                tShapeHit = t1;
                if ( tShapeHit.UpperBound( ) > tMax )
                    return {};
            }

            // Compute sphere hit position and $\phi$
            pHit = Point3f( oi ) + ( Float )tShapeHit * Vector3f( di );
            // Refine sphere intersection point
            pHit *= radius / ScalarDistance( pHit, Point3f( 0, 0, 0 ) );

            if ( pHit.x == 0 && pHit.y == 0 )
                pHit.x = 1e-5f * radius;
            phi = Math::ATan2( pHit.y, pHit.x );
            if ( phi < 0 )
                phi += 2 * Pi;

            // Test sphere intersection against clipping parameters
            if ( ( zMin > -radius && pHit.z < zMin ) || ( zMax < radius && pHit.z > zMax ) ||
                phi > phiMax )
            {
                if ( tShapeHit == t1 )
                    return {};
                if ( t1.UpperBound( ) > tMax )
                    return {};
                tShapeHit = t1;
                // Compute sphere hit position and $\phi$
                pHit = Point3f( oi ) + ( Float )tShapeHit * Vector3f( di );
                // Refine sphere intersection point
                pHit *= radius / ScalarDistance( pHit, Point3f( 0, 0, 0 ) );

                if ( pHit.x == 0 && pHit.y == 0 )
                    pHit.x = 1e-5f * radius;
                phi = Math::ATan2( pHit.y, pHit.x );
                if ( phi < 0 )
                    phi += 2 * Pi;

                if ( ( zMin > -radius && pHit.z < zMin ) || ( zMax < radius && pHit.z > zMax ) ||
                    phi > phiMax )
                    return {};
            }

            // Return _QuadricIntersection_ for sphere intersection
            return QuadricIntersection{ Float( tShapeHit ), pHit, phi };
        }

        bool IntersectP( const Ray& r, Float tMax = Infinity ) const
        {
            return BasicIntersect( r, tMax ).has_value( );
        }

        SurfaceInteraction InteractionFromIntersection( const QuadricIntersection& isect, Vector3f::Simd wo, Float time ) const
        {
            Point3f pHit = isect.pObj;
            Float phi = isect.phi;
            // Find parametric representation of sphere hit
            Float u = phi / phiMax;
            Float cosTheta = pHit.z / radius;
            Float theta = SafeACos( cosTheta );
            Float v = ( theta - thetaZMin ) / ( thetaZMax - thetaZMin );
            // Compute sphere $\dpdu$ and $\dpdv$
            Float zRadius = Math::Hypot(pHit.x, pHit.y );
            Float cosPhi = pHit.x / zRadius, sinPhi = pHit.y / zRadius;
            Vector3f::Simd dpdu( -phiMax * pHit.y, phiMax * pHit.x, 0 );
            Float sinTheta = SafeSqrt( 1 - Sqr( cosTheta ) );
            Vector3f::Simd dpdv = ( thetaZMax - thetaZMin ) * Vector3f::Simd( pHit.z * cosPhi, pHit.z * sinPhi, -radius * sinTheta );

            // Compute sphere $\dndu$ and $\dndv$
            Vector3f::Simd d2Pduu = -phiMax * phiMax * Vector3f::Simd( pHit.x, pHit.y, 0 );
            Vector3f::Simd d2Pduv = ( thetaZMax - thetaZMin ) * pHit.z * phiMax * Vector3f::Simd( -sinPhi, cosPhi, 0.f );
            Vector3f d2Pdvv = -Sqr( thetaZMax - thetaZMin ) * Vector3f::Simd( pHit.x, pHit.y, pHit.z );
            // Compute coefficients for fundamental forms
            Float E = ScalarDot( dpdu, dpdu ), F = ScalarDot( dpdu, dpdv ), G = ScalarDot( dpdv, dpdv );
            Vector3f::Simd n = Normalize( Cross( dpdu, dpdv ) );
            Float e = ScalarDot( n, d2Pduu ), f = ScalarDot( n, d2Pduv ), g = ScalarDot( n, d2Pdvv );

            // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
            Float EGF2 = DifferenceOfProducts( E, G, F, F );
            Float invEGF2 = ( EGF2 == 0 ) ? Float( 0 ) : 1 / EGF2;
            Normal3f::Simd dndu( ( f * F - e * G ) * invEGF2 * dpdu + ( e * F - f * E ) * invEGF2 * dpdv );
            Normal3f::Simd dndv( ( g * F - f * G ) * invEGF2 * dpdu + ( f * F - g * E ) * invEGF2 * dpdv );

            // Compute error bounds for sphere intersection
            Vector3f pError = gamma( 5 ) * Abs( ( Vector3f )pHit );

            // Return _SurfaceInteraction_ for quadric intersection
            bool flipNormal = reverseOrientation ^ transformSwapsHandedness;
            Vector3f::Simd woObject = ( *objectFromRender )( wo );
            return ( *renderFromObject )( SurfaceInteraction( Point3fi( pHit, pError ), Point2f( u, v ), woObject, dpdu, dpdv, dndu, dndv, time, flipNormal ) );
        }

        Float Area( ) const 
        { 
            return phiMax * radius * ( zMax - zMin ); 
        }

        pstdo::optional<ShapeSample> Sample( Point2f u ) const;

        Float PDF( const Interaction& ) const 
        { 
            return 1 / Area( ); 
        }

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const
        {
            // Sample uniformly on sphere if $\pt{}$ is inside it
            Point3f::Simd pCenter = ( *renderFromObject )( Point3f::Simd( 0, 0, 0 ) );
            Point3f::Simd pOrigin = ctx.OffsetRayOrigin( pCenter );
            if ( ScalarDistanceSquared( pOrigin, pCenter ) <= Sqr( radius ) )
            {
                // Sample shape by area and compute incident direction _wi_
                pstdo::optional<ShapeSample> ss = Sample( u );
                NDCHECK( ss.has_value( ) );
                ss->intr.time = ctx.time;
                Vector3f::Simd wi = ss->intr.p( ) - ctx.p( );
                if ( ScalarLengthSquared( wi ) == 0 )
                    return {};
                wi = Normalize( wi );

                // Convert area sampling PDF in _ss_ to solid angle measure
                ss->pdf /= ScalarAbsDot( ss->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), ss->intr.p( ) );
                if ( IsInf( ss->pdf ) )
                    return {};

                return ss;
            }

            // Sample sphere uniformly inside subtended cone
            // Compute quantities related to the $\theta_\roman{max}$ for cone
            Float sinThetaMax = radius / ScalarDistance( ctx.p( ), pCenter );
            Float sin2ThetaMax = Sqr( sinThetaMax );
            Float cosThetaMax = SafeSqrt( 1 - sin2ThetaMax );
            Float oneMinusCosThetaMax = 1 - cosThetaMax;

            // Compute $\theta$ and $\phi$ values for sample in cone
            Float cosTheta = ( cosThetaMax - 1 ) * u[ 0 ] + 1;
            Float sin2Theta = 1 - Sqr( cosTheta );
            if ( sin2ThetaMax < 0.00068523f /* sin^2(1.5 deg) */ )
            {
                // Compute cone sample via Taylor series expansion for small angles
                sin2Theta = sin2ThetaMax * u[ 0 ];
                cosTheta = Math::Sqrt( 1 - sin2Theta );
                oneMinusCosThetaMax = sin2ThetaMax / 2;
            }

            // Compute angle $\alpha$ from center of sphere to sampled point on surface
            Float cosAlpha = sin2Theta / sinThetaMax +
                cosTheta * SafeSqrt( 1 - sin2Theta / Sqr( sinThetaMax ) );
            Float sinAlpha = SafeSqrt( 1 - Sqr( cosAlpha ) );

            // Compute surface normal and sampled point on sphere
            Float phi = u[ 1 ] * 2 * Pi;
            Vector3f::Simd w = SphericalDirection( sinAlpha, cosAlpha, phi );
            Frame samplingFrame = Frame::FromZ( Normalize( pCenter - ctx.p( ) ) );
            Normal3f::Simd n( samplingFrame.FromLocal( -w ) );
            Point3f::Simd p = pCenter + radius * Point3f::Simd( n );
            if ( reverseOrientation )
                n *= -1;

            // Return _ShapeSample_ for sampled point on sphere
            // Compute _pError_ for sampled point on sphere
            Vector3f pError = gamma( 5 ) * Abs( Vector3f::Simd( p ) );

            // Compute $(u,v)$ coordinates for sampled point on sphere
            Point3f pObj = ( *objectFromRender )( p );
            Float theta = SafeACos( pObj.z / radius );
            Float spherePhi = Math::ATan2( pObj.y, pObj.x );
            if ( spherePhi < 0 )
                spherePhi += 2 * Pi;
            Point2f uv( spherePhi / phiMax, ( theta - thetaZMin ) / ( thetaZMax - thetaZMin ) );

            NDCHECK_NE( oneMinusCosThetaMax, 0 );  // very small far away sphere
            return ShapeSample{ Interaction( Point3fi( p, pError ), n, ctx.time, uv ),
                               1 / ( 2 * Pi * oneMinusCosThetaMax ) };
        }

        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
        {
            Point3f::Simd pCenter = ( *renderFromObject )( Point3f::Simd( 0, 0, 0 ) );
            Point3f::Simd pOrigin = ctx.OffsetRayOrigin( pCenter );
            if ( ScalarDistanceSquared( pOrigin, pCenter ) <= Sqr( radius ) )
            {
                // Return solid angle PDF for point inside sphere
                // Intersect sample ray with shape geometry
                Ray ray = ctx.SpawnRay( wi );
                pstdo::optional<ShapeIntersection> isect = Intersect( ray );
                if ( !isect )
                    return 0;

                // Compute PDF in solid angle measure from shape intersection point
                Float pdf = ( 1 / Area( ) ) / ( ScalarAbsDot( isect->intr.n, -wi ) /
                    ScalarDistanceSquared( ctx.p( ), isect->intr.p( ) ) );
                if ( IsInf( pdf ) )
                    pdf = 0;

                return pdf;
            }
            // Compute general solid angle sphere PDF
            Float sin2ThetaMax = radius * radius / ScalarDistanceSquared( ctx.p( ), pCenter );
            Float cosThetaMax = SafeSqrt( 1 - sin2ThetaMax );
            Float oneMinusCosThetaMax = 1 - cosThetaMax;
            // Compute more accurate _oneMinusCosThetaMax_ for small solid angle
            if ( sin2ThetaMax < 0.00068523f /* sin^2(1.5 deg) */ )
                oneMinusCosThetaMax = sin2ThetaMax / 2;

            return 1 / ( 2 * Pi * oneMinusCosThetaMax );
        }

    private:
        
    };

    // Disk Definition
    class Disk
    {
        // Disk Private Members
        const Transform* renderFromObject, * objectFromRender;
        bool reverseOrientation, transformSwapsHandedness;
        Float height, radius, innerRadius, phiMax;
    public:
        // Disk Public Methods
        Disk( const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation, Float height, Float radius, Float innerRadius, Float phiMax )
            : renderFromObject( renderFromObject ),
              objectFromRender( objectFromRender ),
              reverseOrientation( reverseOrientation ),
              transformSwapsHandedness( renderFromObject->SwapsHandedness( ) ),
              height( height ),
              radius( radius ),
              innerRadius( innerRadius ),
              phiMax( Radians( Clamp( phiMax, 0, 360 ) ) )
        {
        }

        static Disk* Create( const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation, const ParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        Float Area( ) const 
        { 
            return phiMax * 0.5f * ( Sqr( radius ) - Sqr( innerRadius ) ); 
        }

        Bounds3f Bounds( ) const;

        DirectionCone NormalBounds( ) const;

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const
        {
            pstdo::optional<QuadricIntersection> isect = BasicIntersect( ray, tMax );
            if ( !isect )
                return {};
            SurfaceInteraction intr = InteractionFromIntersection( *isect, -ray.d, ray.time );
            return ShapeIntersection{ intr, isect->tHit };
        }

        pstdo::optional<QuadricIntersection> BasicIntersect( const Ray& r, Float tMax ) const
        {
            // Transform _Ray_ origin and direction to object space
            Point3fi oi = ( *objectFromRender )( Point3fi( r.o ) );
            Vector3fi di = ( *objectFromRender )( Vector3fi( r.d ) );

            // Compute plane intersection for disk
            // Reject disk intersections for rays parallel to the disk's plane
            if ( Float( di.z ) == 0 )
                return {};

            Float tShapeHit = ( height - Float( oi.z ) ) / Float( di.z );
            if ( tShapeHit <= 0 || tShapeHit >= tMax )
                return {};

            // See if hit point is inside disk radii and $\phimax$
            Point3f pHit = Point3f( oi ) + ( Float )tShapeHit * Vector3f( di );
            Float dist2 = Sqr( pHit.x ) + Sqr( pHit.y );
            if ( dist2 > Sqr( radius ) || dist2 < Sqr( innerRadius ) )
                return {};
            // Test disk $\phi$ value against $\phimax$
            Float phi = Math::ATan2( pHit.y, pHit.x );
            if ( phi < 0 )
                phi += 2 * Pi;
            if ( phi > phiMax )
                return {};

            // Return _QuadricIntersection_ for disk intersection
            return QuadricIntersection{ tShapeHit, pHit, phi };
        }

        SurfaceInteraction InteractionFromIntersection( const QuadricIntersection& isect, Vector3f::Simd wo, Float time ) const
        {
            Point3f pHit = isect.pObj;
            Float phi = isect.phi;
            // Find parametric representation of disk hit
            Float u = phi / phiMax;
            Float rHit = Math::Hypot( pHit.x, pHit.y );
            Float v = ( radius - rHit ) / ( radius - innerRadius );
            Vector3f::Simd dpdu( -phiMax * pHit.y, phiMax * pHit.x, 0 );
            Vector3f::Simd dpdv = Vector3f( pHit.x, pHit.y, 0 ) * ( innerRadius - radius ) / rHit;
            Normal3f::Simd dndu( 0, 0, 0 ), dndv( 0, 0, 0 );

            // Refine disk intersection point
            pHit.z = height;

            // Compute error bounds for disk intersection
            Vector3f pError( 0, 0, 0 );

            // Return _SurfaceInteraction_ for quadric intersection
            bool flipNormal = reverseOrientation ^ transformSwapsHandedness;
            Vector3f::Simd woObject = ( *objectFromRender )( wo );
            return ( *renderFromObject )( SurfaceInteraction( Point3fi( pHit, pError ), Point2f( u, v ), woObject, dpdu, dpdv, dndu, dndv, time, flipNormal ) );
        }

        bool IntersectP( const Ray& r, Float tMax = Infinity ) const
        {
            return BasicIntersect( r, tMax ).has_value( );
        }

        pstdo::optional<ShapeSample> Sample( Point2f u ) const
        {
            Point2f pd = SampleUniformDiskConcentric( u );
            Point3f pObj( pd.x * radius, pd.y * radius, height );
            Point3fi pi = ( *renderFromObject )( Point3fi( pObj ) );
            Normal3f::Simd n = Normalize( ( *renderFromObject )( Normal3f::Simd( 0, 0, 1 ) ) );

            if ( reverseOrientation )
                n *= -1;
            // Compute $(u,v)$ for sampled point on disk
            Float phi = Math::ATan2( pd.y, pd.x );
            if ( phi < 0 )
                phi += 2 * Pi;
            Float radiusSample = Math::Hypot( pObj.x, pObj.y );
            Point2f uv( phi / phiMax, ( radius - radiusSample ) / ( radius - innerRadius ) );

            return ShapeSample{ Interaction( pi, n, uv ), 1 / Area( ) };
        }

        Float PDF( const Interaction& ) const 
        { 
            return 1 / Area( ); 
        }

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const
        {
            // Sample shape by area and compute incident direction _wi_
            pstdo::optional<ShapeSample> ss = Sample( u );
            NDCHECK( ss.has_value( ) );
            ss->intr.time = ctx.time;
            Vector3f::Simd wi = ss->intr.p( ) - ctx.p( );
            if ( ScalarLengthSquared( wi ) == 0 )
                return {};
            wi = Normalize( wi );

            // Convert area sampling PDF in _ss_ to solid angle measure
            ss->pdf /= ScalarAbsDot( ss->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), ss->intr.p( ) );
            if ( IsInf( ss->pdf ) )
                return {};

            return ss;
        }

        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
        {
            // Intersect sample ray with shape geometry
            Ray ray = ctx.SpawnRay( wi );
            pstdo::optional<ShapeIntersection> isect = Intersect( ray );
            if ( !isect )
                return 0;

            // Compute PDF in solid angle measure from shape intersection point
            Float pdf = ( 1 / Area( ) ) / ( ScalarAbsDot( isect->intr.n, -wi ) /
                ScalarDistanceSquared( ctx.p( ), isect->intr.p( ) ) );
            if ( IsInf( pdf ) )
                pdf = 0;

            return pdf;
        }

    private:
        
    };

    // Cylinder Definition
    class Cylinder
    {
        // Cylinder Private Members
        const Transform* renderFromObject, * objectFromRender;
        bool reverseOrientation, transformSwapsHandedness;
        Float radius, zMin, zMax, phiMax;
    public:
        // Cylinder Public Methods
        Cylinder( const Transform* renderFromObj, const Transform* objFromRender, bool reverseOrientation, Float radius, Float zMin, Float zMax, Float phiMax );

        static Cylinder* Create( const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation, const ParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        Bounds3f Bounds( ) const;

        std::string ToString( ) const;

        Float Area( ) const 
        { 
            return ( zMax - zMin ) * radius * phiMax; 
        }

        DirectionCone NormalBounds( ) const 
        { 
            return DirectionCone::EntireSphere( ); 
        }

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const
        {
            pstdo::optional<QuadricIntersection> isect = BasicIntersect( ray, tMax );
            if ( !isect )
                return {};
            SurfaceInteraction intr = InteractionFromIntersection( *isect, -ray.d, ray.time );
            return ShapeIntersection{ intr, isect->tHit };
        }

        pstdo::optional<QuadricIntersection> BasicIntersect( const Ray& r, Float tMax ) const
        {
            // Transform _Ray_ origin and direction to object space
            Point3fi oi = ( *objectFromRender )( Point3fi( r.o ) );
            Vector3fi di = ( *objectFromRender )( Vector3fi( r.d ) );

            // Solve quadratic equation to find cylinder _t0_ and _t1_ values
            Interval t0, t1;
            // Compute cylinder quadratic coefficients
            Interval a = Sqr( di.x ) + Sqr( di.y );
            Interval b = 2.f * ( di.x * oi.x + di.y * oi.y );
            Interval c = Sqr( oi.x ) + Sqr( oi.y ) - Sqr( Interval( radius ) );

            // Compute cylinder quadratic discriminant _discrim_
            Interval f = b / ( 2.f * a );
            Interval vx = oi.x - f * di.x, vy = oi.y - f * di.y;
            Interval length = Sqrt( Sqr( vx ) + Sqr( vy ) );
            Interval discrim = 4.f * a * ( Interval( radius ) + length ) * ( Interval( radius ) - length );
            if ( discrim.LowerBound( ) < 0 )
                return {};

            // Compute quadratic $t$ values
            Interval rootDiscrim = Sqrt( discrim );
            Interval q;
            if ( ( Float )b < 0 )
                q = -.5f * ( b - rootDiscrim );
            else
                q = -.5f * ( b + rootDiscrim );
            t0 = q / a;
            t1 = c / q;
            // Swap quadratic $t$ values so that _t0_ is the lesser
            if ( t0.LowerBound( ) > t1.LowerBound( ) )
                pstdo::swap( t0, t1 );

            // Check quadric shape _t0_ and _t1_ for nearest intersection
            if ( t0.UpperBound( ) > tMax || t1.LowerBound( ) <= 0 )
                return {};
            Interval tShapeHit = t0;
            if ( tShapeHit.LowerBound( ) <= 0 )
            {
                tShapeHit = t1;
                if ( tShapeHit.UpperBound( ) > tMax )
                    return {};
            }

            // Compute cylinder hit point and $\phi$
            Point3f pHit = Point3f( oi ) + ( Float )tShapeHit * Vector3f( di );
            // Refine cylinder intersection point
            Float hitRad = Math::Hypot( pHit.x, pHit.y );
            pHit.x *= radius / hitRad;
            pHit.y *= radius / hitRad;

            Float phi = Math::ATan2( pHit.y, pHit.x );
            if ( phi < 0 )
                phi += 2 * Pi;

            // Test cylinder intersection against clipping parameters
            if ( pHit.z < zMin || pHit.z > zMax || phi > phiMax )
            {
                if ( tShapeHit == t1 )
                    return {};
                tShapeHit = t1;
                if ( t1.UpperBound( ) > tMax )
                    return {};
                // Compute cylinder hit point and $\phi$
                pHit = Point3f( oi ) + ( Float )tShapeHit * Vector3f( di );
                // Refine cylinder intersection point
                Float hitRad = Math::Hypot( pHit.x, pHit.y );
                pHit.x *= radius / hitRad;
                pHit.y *= radius / hitRad;

                phi = Math::ATan2( pHit.y, pHit.x );
                if ( phi < 0 )
                    phi += 2 * Pi;

                if ( pHit.z < zMin || pHit.z > zMax || phi > phiMax )
                    return {};
            }

            // Return _QuadricIntersection_ for cylinder intersection
            return QuadricIntersection{ Float( tShapeHit ), pHit, phi };
        }

        bool IntersectP( const Ray& r, Float tMax = Infinity ) const
        {
            return BasicIntersect( r, tMax ).has_value( );
        }

        SurfaceInteraction InteractionFromIntersection( const QuadricIntersection& isect, Vector3f::Simd wo, Float time ) const
        {
            Point3f pHit = isect.pObj;
            Float phi = isect.phi;
            // Find parametric representation of cylinder hit
            Float u = phi / phiMax;
            Float v = ( pHit.z - zMin ) / ( zMax - zMin );
            // Compute cylinder $\dpdu$ and $\dpdv$
            Vector3f::Simd dpdu( -phiMax * pHit.y, phiMax * pHit.x, 0 );
            Vector3f::Simd dpdv( 0, 0, zMax - zMin );

            // Compute cylinder $\dndu$ and $\dndv$
            Vector3f::Simd d2Pduu = -phiMax * phiMax * Vector3f::Simd( pHit.x, pHit.y, 0 );
            Vector3f::Simd d2Pduv( 0, 0, 0 ), d2Pdvv( 0, 0, 0 );
            // Compute coefficients for fundamental forms
            Float E = ScalarDot( dpdu, dpdu ), F = ScalarDot( dpdu, dpdv ), G = ScalarDot( dpdv, dpdv );
            Vector3f::Simd n = Normalize( Cross( dpdu, dpdv ) );
            Float e = ScalarDot( n, d2Pduu ), f = ScalarDot( n, d2Pduv ), g = ScalarDot( n, d2Pdvv );

            // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
            Float EGF2 = DifferenceOfProducts( E, G, F, F );
            Float invEGF2 = ( EGF2 == 0 ) ? Float( 0 ) : 1 / EGF2;
            Normal3f::Simd dndu( ( f * F - e * G ) * invEGF2 * dpdu + ( e * F - f * E ) * invEGF2 * dpdv );
            Normal3f::Simd dndv( ( g * F - f * G ) * invEGF2 * dpdu + ( f * F - g * E ) * invEGF2 * dpdv );

            // Compute error bounds for cylinder intersection
            Vector3f pError = gamma( 3 ) * Abs( Vector3f( pHit.x, pHit.y, 0 ) );

            // Return _SurfaceInteraction_ for quadric intersection
            bool flipNormal = reverseOrientation ^ transformSwapsHandedness;
            Vector3f::Simd woObject = ( *objectFromRender )( wo );
            return ( *renderFromObject )( SurfaceInteraction( Point3fi( pHit, pError ), Point2f( u, v ), woObject, dpdu, dpdv, dndu, dndv, time, flipNormal ) );
        }

        pstdo::optional<ShapeSample> Sample( Point2f u ) const
        {
            Float z = Lerp2( u[ 0 ], zMin, zMax );
            Float phi = u[ 1 ] * phiMax;
            // Compute cylinder sample position _pi_ and normal _n_ from $z$ and $\phi$
            Float sinPhi;
            Float cosPhi;
            SinCos( phi, &sinPhi, &cosPhi );
            Point3f pObj = Point3f( radius * cosPhi, radius * sinPhi, z );
            // Reproject _pObj_ to cylinder surface and compute _pObjError_
            Float hitRad = Math::Hypot( pObj.x, pObj.y );
            pObj.x *= radius / hitRad;
            pObj.y *= radius / hitRad;
            Vector3f pObjError = gamma( 3 ) * Abs( Vector3f( pObj.x, pObj.y, 0 ) );

            Point3fi pi = ( *renderFromObject )( Point3fi( pObj, pObjError ) );
            Normal3f::Simd n = Normalize( ( *renderFromObject )( Normal3f( pObj.x, pObj.y, 0 ) ) );
            if ( reverseOrientation )
                n *= -1.f;

            Point2f uv( phi / phiMax, ( pObj.z - zMin ) / ( zMax - zMin ) );
            return ShapeSample{ Interaction( pi, n, uv ), 1 / Area( ) };
        }

        Float PDF( const Interaction& ) const 
        { 
            return 1 / Area( ); 
        }

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const
        {
            // Sample shape by area and compute incident direction _wi_
            pstdo::optional<ShapeSample> ss = Sample( u );
            NDCHECK( ss.has_value( ) );
            ss->intr.time = ctx.time;
            Vector3f::Simd wi = ss->intr.p( ) - ctx.p( );
            if ( ScalarLengthSquared( wi ) == 0 )
                return {};
            wi = Normalize( wi );

            // Convert area sampling PDF in _ss_ to solid angle measure
            ss->pdf /= ScalarAbsDot( ss->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), ss->intr.p( ) );
            if ( IsInf( ss->pdf ) )
                return {};

            return ss;
        }

        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
        {
            // Intersect sample ray with shape geometry
            Ray ray = ctx.SpawnRay( wi );
            pstdo::optional<ShapeIntersection> isect = Intersect( ray );
            if ( !isect )
                return 0;

            // Compute PDF in solid angle measure from shape intersection point
            Float pdf = ( 1 / Area( ) ) / ( ScalarAbsDot( isect->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), isect->intr.p( ) ) );
            if ( IsInf( pdf ) )
                pdf = 0;

            return pdf;
        }

    private:
        
    };

    // Cylinder Inline Methods
    inline Cylinder::Cylinder( const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation, Float radius, Float zMin, Float zMax, Float phiMax )
        : renderFromObject( renderFromObject ),
          objectFromRender( objectFromRender ),
          reverseOrientation( reverseOrientation ),
          transformSwapsHandedness( renderFromObject->SwapsHandedness( ) ),
          radius( radius ),
          zMin( std::min( zMin, zMax ) ),
          zMax( std::max( zMin, zMax ) ),
          phiMax( Radians( Clamp( phiMax, 0, 360 ) ) )
    {
    }

    // Triangle Declarations
#if defined(PBRT_BUILD_GPU_RENDERER) && defined(__CUDACC__)
    extern PBRT_GPU pstdo::vector<const TriangleMesh*>* allTriangleMeshesGPU;
#endif

    // TriangleIntersection Definition
    struct TriangleIntersection
    {
        Float b0, b1, b2;
        Float t;
        std::string ToString( ) const;
    };

    // Triangle Function Declarations
    PBRTO_EXPORT pstdo::optional<TriangleIntersection> IntersectTriangle( const Ray& ray, Float tMax, Point3f::Simd p0, Point3f::Simd p1, Point3f::Simd p2 );

    // Triangle Definition
    class Triangle
    {
        // Triangle Private Members
        int meshIndex = -1, triIndex = -1;
        static pstdo::vector<const TriangleMesh*>* allMeshes;
        static constexpr Float MinSphericalSampleArea = 3e-4;
        static constexpr Float MaxSphericalSampleArea = 6.22;
    public:
        // Triangle Public Methods
        static pstdo::vector<Shape> CreateTriangles( const TriangleMesh* mesh, Allocator alloc );

        Triangle( ) = default;
        Triangle( int meshIndex, int triIndex ) 
            : meshIndex( meshIndex ), triIndex( triIndex ) 
        { }

        static void Init( Allocator alloc );

        Bounds3f Bounds( ) const;

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const;
        bool IntersectP( const Ray& ray, Float tMax = Infinity ) const;

        Float Area( ) const
        {
            // Get triangle vertices in _p0_, _p1_, and _p2_
            const TriangleMesh* mesh = GetMesh( );
            const int* v = &mesh->vertexIndices[ 3 * triIndex ];
            Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

            return 0.5f * ScalarLength( Cross( p1 - p0, p2 - p0 ) );
        }

        DirectionCone NormalBounds( ) const;

        std::string ToString( ) const;

        static TriangleMesh* CreateMesh( const Transform* renderFromObject, bool reverseOrientation, const ParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        Float SolidAngle( Point3f::Simd p ) const
        {
            // Get triangle vertices in _p0_, _p1_, and _p2_
            const TriangleMesh* mesh = GetMesh( );
            const int* v = &mesh->vertexIndices[ 3 * triIndex ];
            Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

            return SphericalTriangleArea( Normalize( p0 - p ), Normalize( p1 - p ), Normalize( p2 - p ) );
        }

        static SurfaceInteraction InteractionFromIntersection( const TriangleMesh* mesh, int triIndex, TriangleIntersection ti, Float time, Vector3f::Simd wo )
        {
            const int* v = &mesh->vertexIndices[ 3 * triIndex ];
            Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];
            // Compute triangle partial derivatives
            // Compute deltas and matrix determinant for triangle partial derivatives
            // Get triangle texture coordinates in _uv_ array
            pstdo::array<Point2f, 3> uv =
                mesh->uv
                ? pstdo::array<Point2f, 3>(
                    { mesh->uv[ v[ 0 ] ], mesh->uv[ v[ 1 ] ], mesh->uv[ v[ 2 ] ] } )
                : pstdo::array<Point2f, 3>( { Point2f( 0, 0 ), Point2f( 1, 0 ), Point2f( 1, 1 ) } );

            Vector2f duv02 = uv[ 0 ] - uv[ 2 ], duv12 = uv[ 1 ] - uv[ 2 ];
            Vector3f::Simd dp02 = p0 - p2, dp12 = p1 - p2;
            Float determinant = DifferenceOfProducts( duv02[ 0 ], duv12[ 1 ], duv02[ 1 ], duv12[ 0 ] );

            Vector3f::Simd dpdu, dpdv;
            bool degenerateUV = Math::FastAbs( determinant ) < 1e-9f;
            if ( !degenerateUV )
            {
                // Compute triangle $\dpdu$ and $\dpdv$ via matrix inversion
                Float invdet = 1 / determinant;
                dpdu = DifferenceOfProducts( duv12[ 1 ], dp02, duv02[ 1 ], dp12 ) * invdet;
                dpdv = DifferenceOfProducts( duv02[ 0 ], dp12, duv12[ 0 ], dp02 ) * invdet;
            }
            // Handle degenerate triangle $(u,v)$ parameterization or partial derivatives
            if ( degenerateUV || ScalarLengthSquared( Cross( dpdu, dpdv ) ) == 0 )
            {
                Vector3f::Simd ng = Cross( p2 - p0, p1 - p0 );
                if ( ScalarLengthSquared( ng ) == 0 )
                {
                    Point3<double> p0d( p0.x( ), p0.y( ), p0.z( ) );
                    Point3<double> p1d( p1.x( ), p1.y( ), p1.z( ) );
                    Point3<double> p2d( p2.x( ), p2.y( ), p2.z( ) );
                    ng = Vector3f( Cross( Vector3<double>( p2d - p0d ), Vector3<double>( p1d - p0d ) ) );
                    NCHECK_NE( ScalarLengthSquared( ng ), 0 );
                }
                Vector3f tmpdpdu, tmpdpdv;
                CoordinateSystem( Vector3f( Normalize( ng ) ), &tmpdpdu, &tmpdpdv );
                dpdu = tmpdpdu, dpdv = tmpdpdv;
            }

            // Interpolate $(u,v)$ parametric coordinates and hit point
            Point3f::Simd pHit = ti.b0 * p0 + ti.b1 * p1 + ti.b2 * p2;
            Point2f uvHit = ti.b0 * uv[ 0 ] + ti.b1 * uv[ 1 ] + ti.b2 * uv[ 2 ];

            // Return _SurfaceInteraction_ for triangle hit
            bool flipNormal = mesh->reverseOrientation ^ mesh->transformSwapsHandedness;
            // Compute error bounds _pError_ for triangle intersection
            Point3f pAbsSum = Abs( ti.b0 * p0 ) + Abs( ti.b1 * p1 ) + Abs( ti.b2 * p2 );
            Vector3f pError = gamma( 7 ) * Vector3f( pAbsSum );

            SurfaceInteraction isect( Point3fi( pHit, pError ), uvHit, wo, dpdu, dpdv, Normal3f( ), Normal3f( ), time, flipNormal );
            isect.faceIndex = mesh->faceIndices ? mesh->faceIndices[ triIndex ] : 0;
            // Set final surface normal and shading geometry for triangle
            // Override surface normal in _isect_ for triangle
            isect.n = isect.shading.n = Normal3f::Simd( Normalize( Cross( dp02, dp12 ) ) );
            if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
            {
                isect.n = isect.shading.n = -isect.n;
            }

            if ( mesh->n || mesh->s )
            {
                // Initialize _Triangle_ shading geometry
                // Compute shading normal _ns_ for triangle
                Normal3f::Simd ns;
                if ( mesh->n )
                {
                    ns = ti.b0 * mesh->n[ v[ 0 ] ] + ti.b1 * mesh->n[ v[ 1 ] ] + ti.b2 * mesh->n[ v[ 2 ] ];
                    ns = ScalarLengthSquared( ns ) > 0 ? Normalize( ns ) : Normal3f::Simd( isect.n );
                }
                else
                    ns = isect.n;

                // Compute shading tangent _ss_ for triangle
                Vector3f::Simd ss;
                if ( mesh->s )
                {
                    ss = ti.b0 * mesh->s[ v[ 0 ] ] + ti.b1 * mesh->s[ v[ 1 ] ] + ti.b2 * mesh->s[ v[ 2 ] ];
                    if ( ScalarLengthSquared( ss ) == 0 )
                        ss = isect.dpdu;
                }
                else
                    ss = isect.dpdu;

                // Compute shading bitangent _ts_ for triangle and adjust _ss_
                Vector3f ts = Cross( ns, ss );
                if ( ScalarLengthSquared( ts ) > 0 )
                {
                    ss = Cross( ts, ns );
                }
                else
                {
                    Vector3f tmpss, tmpts;
                    CoordinateSystem( Normal3f( ns ), &tmpss, &tmpts );
                    ss = tmpss;
                    ts = tmpts;
                }

                // Compute $\dndu$ and $\dndv$ for triangle shading geometry
                Normal3f::Simd dndu, dndv;
                if ( mesh->n )
                {
                    // Compute deltas for triangle partial derivatives of normal
                    Vector2f duv02 = uv[ 0 ] - uv[ 2 ];
                    Vector2f duv12 = uv[ 1 ] - uv[ 2 ];
                    Normal3f::Simd dn1 = mesh->n[ v[ 0 ] ] - mesh->n[ v[ 2 ] ];
                    Normal3f::Simd dn2 = mesh->n[ v[ 1 ] ] - mesh->n[ v[ 2 ] ];

                    Float determinant = DifferenceOfProducts( duv02[ 0 ], duv12[ 1 ], duv02[ 1 ], duv12[ 0 ] );
                    bool degenerateUV = Math::FastAbs( determinant ) < 1e-9;
                    if ( degenerateUV )
                    {
                        // We can still compute dndu and dndv, with respect to the
                        // same arbitrary coordinate system we use to compute dpdu
                        // and dpdv when this happens. It's important to do this
                        // (rather than giving up) so that ray differentials for
                        // rays reflected from triangles with degenerate
                        // parameterizations are still reasonable.
                        Vector3f dn = Cross( Vector3f( mesh->n[ v[ 2 ] ] - mesh->n[ v[ 0 ] ] ),
                            Vector3f( mesh->n[ v[ 1 ] ] - mesh->n[ v[ 0 ] ] ) );

                        if ( ScalarLengthSquared( dn ) == 0 )
                            dndu = dndv = Normal3f( 0, 0, 0 );
                        else
                        {
                            Vector3f dnu, dnv;
                            CoordinateSystem( dn, &dnu, &dnv );
                            dndu = Normal3f( dnu );
                            dndv = Normal3f( dnv );
                        }
                    }
                    else
                    {
                        Float invDet = 1 / determinant;
                        dndu = DifferenceOfProducts( duv12[ 1 ], dn1, duv02[ 1 ], dn2 ) * invDet;
                        dndv = DifferenceOfProducts( duv02[ 0 ], dn2, duv12[ 0 ], dn1 ) * invDet;
                    }
                }
                else
                    dndu = dndv = Normal3f( 0, 0, 0 );

                isect.SetShadingGeometry( ns, ss, ts, dndu, dndv, true );
            }

            return isect;
        }

        pstdo::optional<ShapeSample> Sample( Point2f u ) const
        {
            // Get triangle vertices in _p0_, _p1_, and _p2_
            const TriangleMesh* mesh = GetMesh( );
            const int* v = &mesh->vertexIndices[ 3 * triIndex ];
            Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

            // Sample point on triangle uniformly by area
            pstdo::array<Float, 3> b = SampleUniformTriangle( u );
            Point3f::Simd p = b[ 0 ] * p0 + b[ 1 ] * p1 + b[ 2 ] * p2;

            // Compute surface normal for sampled point on triangle
            Normal3f::Simd n = Normalize( Normal3f::Simd( Cross( p1 - p0, p2 - p0 ) ) );
            if ( mesh->n )
            {
                Normal3f::Simd ns( b[ 0 ] * mesh->n[ v[ 0 ] ] + b[ 1 ] * mesh->n[ v[ 1 ] ] + ( 1 - b[ 0 ] - b[ 1 ] ) * mesh->n[ v[ 2 ] ] );
                n = FaceForward( n, ns );
            }
            else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
                n *= -1;

            // Compute $(u,v)$ for sampled point on triangle
            // Get triangle texture coordinates in _uv_ array
            pstdo::array<Point2f, 3> uv =
                mesh->uv
                ? pstdo::array<Point2f, 3>(
                    { mesh->uv[ v[ 0 ] ], mesh->uv[ v[ 1 ] ], mesh->uv[ v[ 2 ] ] } )
                : pstdo::array<Point2f, 3>( { Point2f( 0, 0 ), Point2f( 1, 0 ), Point2f( 1, 1 ) } );

            Point2f uvSample = b[ 0 ] * uv[ 0 ] + b[ 1 ] * uv[ 1 ] + b[ 2 ] * uv[ 2 ];

            // Compute error bounds _pError_ for sampled point on triangle
            Point3f::Simd pAbsSum = Abs( b[ 0 ] * p0 ) + Abs( b[ 1 ] * p1 ) + Abs( ( 1 - b[ 0 ] - b[ 1 ] ) * p2 );
            Vector3f pError = Vector3f( gamma( 6 ) * pAbsSum );

            return ShapeSample{ Interaction( Point3fi( p, pError ), n, uvSample ), 1 / Area( ) };
        }

        Float PDF( const Interaction& ) const 
        { 
            return 1 / Area( ); 
        }

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const
        {
            // Get triangle vertices in _p0_, _p1_, and _p2_
            const TriangleMesh* mesh = GetMesh( );
            const int* v = &mesh->vertexIndices[ 3 * triIndex ];
            Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

            // Use uniform area sampling for numerically unstable cases
            Float solidAngle = SolidAngle( ctx.p( ) );
            if ( solidAngle < MinSphericalSampleArea || solidAngle > MaxSphericalSampleArea )
            {
                // Sample shape by area and compute incident direction _wi_
                pstdo::optional<ShapeSample> ss = Sample( u );
                NDCHECK( ss.has_value( ) );
                ss->intr.time = ctx.time;
                Vector3f wi = ss->intr.p( ) - ctx.p( );
                if ( ScalarLengthSquared( wi ) == 0 )
                    return {};
                wi = Normalize( wi );

                // Convert area sampling PDF in _ss_ to solid angle measure
                ss->pdf /= ScalarAbsDot( ss->intr.n, -wi ) / ScalarDistanceSquared( ctx.p( ), ss->intr.p( ) );
                if ( IsInf( ss->pdf ) )
                    return {};

                return ss;
            }

            // Sample spherical triangle from reference point
            // Apply warp product sampling for cosine factor at reference point
            Float pdf = 1;
            if ( ctx.ns != Normal3f::Simd( 0, 0, 0 ) )
            {
                // Compute $\cos\theta$-based weights _w_ at sample domain corners
                Point3f::Simd rp = ctx.p( );
                Vector3f::Simd wi[ 3 ] = { Normalize( p0 - rp ), Normalize( p1 - rp ), Normalize( p2 - rp ) };
                pstdo::array<Float, 4> w =
                    pstdo::array<Float, 4>{std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 1 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 1 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 0 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 2 ] ) )};

                u = SampleBilinear( u, w );
                NDCHECK( u[ 0 ] >= 0 && u[ 0 ] < 1 && u[ 1 ] >= 0 && u[ 1 ] < 1 );
                pdf = BilinearPDF( u, w );
            }

            Float triPDF;
            std::array<Float, 3> b = SampleSphericalTriangle( { p0, p1, p2 }, ctx.p( ), u, &triPDF );
            if ( triPDF == 0 )
                return {};
            pdf *= triPDF;

            // Compute error bounds _pError_ for sampled point on triangle
            Point3f::Simd pAbsSum = Abs( b[ 0 ] * p0 ) + Abs( b[ 1 ] * p1 ) + Abs( ( 1 - b[ 0 ] - b[ 1 ] ) * p2 );
            Vector3f pError = Vector3f( gamma( 6 ) * pAbsSum );

            // Return _ShapeSample_ for solid angle sampled point on triangle
            Point3f::Simd p = b[ 0 ] * p0 + b[ 1 ] * p1 + b[ 2 ] * p2;
            // Compute surface normal for sampled point on triangle
            Normal3f::Simd n = Normalize( Normal3f::Simd( Cross( p1 - p0, p2 - p0 ) ) );
            if ( mesh->n )
            {
                Normal3f::Simd ns( b[ 0 ] * mesh->n[ v[ 0 ] ] + b[ 1 ] * mesh->n[ v[ 1 ] ] + ( 1 - b[ 0 ] - b[ 1 ] ) * mesh->n[ v[ 2 ] ] );
                n = FaceForward( n, ns );
            }
            else if ( mesh->reverseOrientation ^ mesh->transformSwapsHandedness )
                n *= -1;

            // Compute $(u,v)$ for sampled point on triangle
            // Get triangle texture coordinates in _uv_ array
            pstdo::array<Point2f, 3> uv =
                mesh->uv
                ? pstdo::array<Point2f, 3>(
                    { mesh->uv[ v[ 0 ] ], mesh->uv[ v[ 1 ] ], mesh->uv[ v[ 2 ] ] } )
                : pstdo::array<Point2f, 3>( { Point2f( 0, 0 ), Point2f( 1, 0 ), Point2f( 1, 1 ) } );

            Point2f uvSample = b[ 0 ] * uv[ 0 ] + b[ 1 ] * uv[ 1 ] + b[ 2 ] * uv[ 2 ];

            return ShapeSample{ Interaction( Point3fi( p, pError ), n, ctx.time, uvSample ), pdf };
        }

        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
        {
            Float solidAngle = SolidAngle( ctx.p( ) );
            // Return PDF based on uniform area sampling for challenging triangles
            if ( solidAngle < MinSphericalSampleArea || solidAngle > MaxSphericalSampleArea )
            {
                // Intersect sample ray with shape geometry
                Ray ray = ctx.SpawnRay( wi );
                pstdo::optional<ShapeIntersection> isect = Intersect( ray );
                if ( !isect )
                    return 0;

                // Compute PDF in solid angle measure from shape intersection point
                Float pdf = ( 1 / Area( ) ) / ( ScalarAbsDot( isect->intr.n, -wi ) /
                    ScalarDistanceSquared( ctx.p( ), isect->intr.p( ) ) );
                if ( IsInf( pdf ) )
                    pdf = 0;

                return pdf;
            }

            Float pdf = 1 / solidAngle;
            // Adjust PDF for warp product sampling of triangle $\cos\theta$ factor
            if ( ctx.ns != Normal3f( 0, 0, 0 ) )
            {
                // Get triangle vertices in _p0_, _p1_, and _p2_
                const TriangleMesh* mesh = GetMesh( );
                const int* v = &mesh->vertexIndices[ 3 * triIndex ];
                Point3f::Simd p0 = mesh->p[ v[ 0 ] ], p1 = mesh->p[ v[ 1 ] ], p2 = mesh->p[ v[ 2 ] ];

                Point2f u = InvertSphericalTriangleSample( { p0, p1, p2 }, ctx.p( ), wi );
                // Compute $\cos\theta$-based weights _w_ at sample domain corners
                Point3f::Simd rp = ctx.p( );
                Vector3f::Simd wi[ 3 ] = { Normalize( p0 - rp ), Normalize( p1 - rp ), Normalize( p2 - rp ) };
                pstdo::array<Float, 4> w =
                    pstdo::array<Float, 4>{std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 1 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 1 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 0 ] ) ),
                    std::max<Float>( 0.01, ScalarAbsDot( ctx.ns, wi[ 2 ] ) )};

                pdf *= BilinearPDF( u, w );
            }

            return pdf;
        }

    private:
        // Triangle Private Methods
        const TriangleMesh* GetMesh( ) const
        {
#ifdef PBRT_IS_GPU_CODE
            return ( *allTriangleMeshesGPU )[ meshIndex ];
#else
            return ( *allMeshes )[ meshIndex ];
#endif
        }

        
    };

    // CurveType Definition
    enum class CurveType { Flat, Cylinder, Ribbon };

    std::string ToString( CurveType type );

    // CurveCommon Definition
    struct CurveCommon
    {
        // CurveCommon Public Members
        std::array<Point3f, 4> cpObj;
        boost::container::small_vector<Normal3f,2> n;
        CurveType type;
        std::array<Float,2> width;
        Float normalAngle, invSinNormalAngle;
        const Transform* renderFromObject, * objectFromRender;
        bool reverseOrientation, transformSwapsHandedness;

        // CurveCommon Public Methods
        CurveCommon( const std::array<Point3f,4>& c, Float w0, Float w1, CurveType type,
            const boost::container::small_vector<Normal3f, 2>& norm, const Transform* renderFromObject,
            const Transform* objectFromRender, bool reverseOrientation );

        std::string ToString( ) const;

        
    };

    // Curve Definition
    class Curve
    {
        // Curve Private Members
        const CurveCommon* common;
        Float uMin, uMax;
    public:
        // Curve Public Methods
        Curve( const CurveCommon* common, Float uMin, Float uMax )
            : common( common ), uMin( uMin ), uMax( uMax )
        {
        }

        static pstdo::vector<Shape> Create( const Transform* renderFromObject, const Transform* objectFromRender, bool reverseOrientation, const ParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        Bounds3f Bounds( ) const;
        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax ) const;
        bool IntersectP( const Ray& ray, Float tMax ) const;
        Float Area( ) const;

        pstdo::optional<ShapeSample> Sample( Point2f u ) const;
        Float PDF( const Interaction& ) const;

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const;
        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const;

        std::string ToString( ) const;

        

        DirectionCone NormalBounds( ) const { return DirectionCone::EntireSphere( ); }

    private:
        // Curve Private Methods
        bool IntersectRay( const Ray& r, Float tMax,
            pstdo::optional<ShapeIntersection>* si ) const;
        bool RecursiveIntersect( const Ray& r, Float tMax, std::span<const Point3f, 4> cp,
            const Transform& ObjectFromRay, Float u0, Float u1, int depth,
            pstdo::optional<ShapeIntersection>* si ) const;

        
    };

    // BilinearPatch Declarations
#if defined(PBRT_BUILD_GPU_RENDERER) && defined(__CUDACC__)
    extern PBRT_GPU pstdo::vector<const BilinearPatchMesh*>* allBilinearMeshesGPU;
#endif

    // BilinearIntersection Definition
    struct BilinearIntersection
    {
        Point2f uv;
        Float t;
        std::string ToString( ) const;
    };

    // Bilinear Patch Inline Functions
    inline pstdo::optional<BilinearIntersection> IntersectBilinearPatch( const Ray& ray, Float tMax, Point3f::Simd p00, Point3f::Simd p10, Point3f::Simd p01, Point3f::Simd p11 )
    {
        // Find quadratic coefficients for distance from ray to $u$ iso-lines
        Float a = ScalarDot( Cross( p10 - p00, p01 - p11 ), ray.d );
        Float c = ScalarDot( Cross( p00 - ray.o, ray.d ), p01 - p00 );
        Float b = ScalarDot( Cross( p10 - ray.o, ray.d ), p11 - p10 ) - ( a + c );

        // Solve quadratic for bilinear patch $u$ intersection
        Float u1, u2;
        if ( !Quadratic( a, b, c, &u1, &u2 ) )
            return {};

        // Find epsilon _eps_ to ensure that candidate $t$ is greater than zero
        Float eps =
            gamma( 30 ) * ( MaxComponentValue( Abs( ray.o ) ) + MaxComponentValue( Abs( ray.d ) ) +
                MaxComponentValue( Abs( p00 ) ) + MaxComponentValue( Abs( p10 ) ) +
                MaxComponentValue( Abs( p01 ) ) + MaxComponentValue( Abs( p11 ) ) );

        // Compute $v$ and $t$ for the first $u$ intersection
        Float t = tMax, u, v;
        if ( 0 <= u1 && u1 <= 1 )
        {
            // Precompute common terms for $v$ and $t$ computation
            Point3f::Simd uo = Lerp2( u1, p00, p10 );
            Vector3f ud = Lerp2( u1, p01, p11 ) - uo;
            Vector3f deltao = uo - ray.o;
            Vector3f perp = Cross( ray.d, ud );
            Float p2 = ScalarLengthSquared( perp );

            // Compute matrix determinants for $v$ and $t$ numerators
            Vector3f rayD( ray.d );
            Float v1 =
                ScalarDeterminant( SquareMatrix<3>( deltao.x, rayD.x, perp.x, deltao.y, rayD.y,
                    perp.y, deltao.z, rayD.z, perp.z ) );
            Float t1 = ScalarDeterminant( SquareMatrix<3>( deltao.x, ud.x, perp.x, deltao.y, ud.y,
                perp.y, deltao.z, ud.z, perp.z ) );

            // Set _u_, _v_, and _t_ if intersection is valid
            if ( t1 > p2 * eps && 0 <= v1 && v1 <= p2 )
            {
                u = u1;
                v = v1 / p2;
                t = t1 / p2;
            }
        }

        // Compute $v$ and $t$ for the second $u$ intersection
        if ( 0 <= u2 && u2 <= 1 && u2 != u1 )
        {
            Point3f::Simd uo = Lerp2( u2, p00, p10 );
            Vector3f ud = Lerp2( u2, p01, p11 ) - uo;
            Vector3f deltao = uo - ray.o;
            Vector3f perp = Cross( ray.d, ud );
            Float p2 = ScalarLengthSquared( perp );
            Vector3f rayD( ray.d );
            Float v2 =
                ScalarDeterminant( SquareMatrix<3>( deltao.x, rayD.x, perp.x, deltao.y, rayD.y,
                    perp.y, deltao.z, rayD.z, perp.z ) );
            Float t2 = ScalarDeterminant( SquareMatrix<3>( deltao.x, ud.x, perp.x, deltao.y, ud.y,
                perp.y, deltao.z, ud.z, perp.z ) );
            t2 /= p2;
            if ( 0 <= v2 && v2 <= p2 && t > t2 && t2 > eps )
            {
                t = t2;
                u = u2;
                v = v2 / p2;
            }
        }

        // TODO: reject hits with sufficiently small t that we're not sure.
        // Check intersection $t$ against _tMax_ and possibly return intersection
        if ( t >= tMax )
            return {};
        return BilinearIntersection{ {u, v}, t };
    }

    // BilinearPatch Definition
    class BilinearPatch
    {
        // BilinearPatch Private Members
        int meshIndex, blpIndex;
        static pstdo::vector<const BilinearPatchMesh*>* allMeshes;
        Float area;
        static constexpr Float MinSphericalSampleArea = 1e-4;
    public:
        // BilinearPatch Public Methods
        BilinearPatch( const BilinearPatchMesh* mesh, int meshIndex, int blpIndex );

        static void Init( Allocator alloc );

        static BilinearPatchMesh* CreateMesh( const Transform* renderFromObject,
            bool reverseOrientation,
            const ParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        static pstdo::vector<Shape> CreatePatches( const BilinearPatchMesh* mesh, Allocator alloc );

        Bounds3f Bounds( ) const;

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const;

        bool IntersectP( const Ray& ray, Float tMax = Infinity ) const;

        pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const;

        Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const;

        pstdo::optional<ShapeSample> Sample( Point2f u ) const;

        Float PDF( const Interaction& ) const;

        DirectionCone NormalBounds( ) const;

        std::string ToString( ) const;

        Float Area( ) const 
        { 
            return area; 
        }

        static SurfaceInteraction InteractionFromIntersection( const BilinearPatchMesh* mesh, int blpIndex, Point2f uv, Float time, Vector3f::Simd wo )
        {
            // Compute bilinear patch point $\pt{}$, $\dpdu$, and $\dpdv$ for $(u,v)$
            // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
            const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
            Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
            Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

            Point3f::Simd p = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], p00, p01 ), Lerp2( uv[ 1 ], p10, p11 ) );
            Vector3f::Simd dpdu = Lerp2( uv[ 1 ], p10, p11 ) - Lerp2( uv[ 1 ], p00, p01 );
            Vector3f::Simd dpdv = Lerp2( uv[ 0 ], p01, p11 ) - Lerp2( uv[ 0 ], p00, p10 );

            // Compute $(s,t)$ texture coordinates at bilinear patch $(u,v)$
            Point2f st = uv;
            Float duds = 1, dudt = 0, dvds = 0, dvdt = 1;
            if ( mesh->uv )
            {
                // Compute texture coordinates for bilinear patch intersection point
                Point2f uv00 = mesh->uv[ v[ 0 ] ], uv10 = mesh->uv[ v[ 1 ] ];
                Point2f uv01 = mesh->uv[ v[ 2 ] ], uv11 = mesh->uv[ v[ 3 ] ];
                st = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], uv00, uv01 ), Lerp2( uv[ 1 ], uv10, uv11 ) );

                // Update bilinear patch $\dpdu$ and $\dpdv$ accounting for $(s,t)$
                // Compute partial derivatives of $(u,v)$ with respect to $(s,t)$
                Vector2f dstdu = Lerp2( uv[ 1 ], uv10, uv11 ) - Lerp2( uv[ 1 ], uv00, uv01 );
                Vector2f dstdv = Lerp2( uv[ 0 ], uv01, uv11 ) - Lerp2( uv[ 0 ], uv00, uv10 );
                duds = Math::FastAbs( dstdu[ 0 ] ) < 1e-8f ? 0 : 1 / dstdu[ 0 ];
                dvds = Math::FastAbs( dstdv[ 0 ] ) < 1e-8f ? 0 : 1 / dstdv[ 0 ];
                dudt = Math::FastAbs( dstdu[ 1 ] ) < 1e-8f ? 0 : 1 / dstdu[ 1 ];
                dvdt = Math::FastAbs( dstdv[ 1 ] ) < 1e-8f ? 0 : 1 / dstdv[ 1 ];

                // Compute partial derivatives of $\pt{}$ with respect to $(s,t)$
                Vector3f::Simd dpds = dpdu * duds + dpdv * dvds;
                Vector3f::Simd dpdt = dpdu * dudt + dpdv * dvdt;

                // Set _dpdu_ and _dpdv_ to updated partial derivatives
                if ( Cross( dpds, dpdt ) != Vector3f( 0, 0, 0 ) )
                {
                    if ( ScalarDot( Cross( dpdu, dpdv ), Cross( dpds, dpdt ) ) < 0 )
                        dpdt = -dpdt;
                    NDCHECK_GE( ScalarDot( Normalize( Cross( dpdu, dpdv ) ), Normalize( Cross( dpds, dpdt ) ) ),
                        -1e-3 );
                    dpdu = dpds;
                    dpdv = dpdt;
                }
            }

            // Find partial derivatives $\dndu$ and $\dndv$ for bilinear patch
            Vector3f::Simd d2Pduu( 0, 0, 0 ), d2Pdvv( 0, 0, 0 );
            Vector3f::Simd d2Pduv = ( p00 - p01 ) + ( p11 - p10 );
            // Compute coefficients for fundamental forms
            Float E = ScalarDot( dpdu, dpdu ), F = ScalarDot( dpdu, dpdv ), G = ScalarDot( dpdv, dpdv );
            Vector3f::Simd n = Normalize( Cross( dpdu, dpdv ) );
            Float e = ScalarDot( n, d2Pduu ), f = ScalarDot( n, d2Pduv ), g = ScalarDot( n, d2Pdvv );

            // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
            Float EGF2 = DifferenceOfProducts( E, G, F, F );
            Float invEGF2 = ( EGF2 == 0 ) ? Float( 0 ) : 1 / EGF2;
            Normal3f::Simd dndu( ( f * F - e * G ) * invEGF2 * dpdu + ( e * F - f * E ) * invEGF2 * dpdv );
            Normal3f::Simd dndv( ( g * F - f * G ) * invEGF2 * dpdu + ( f * F - g * E ) * invEGF2 * dpdv );

            // Update $\dndu$ and $\dndv$ to account for $(s,t)$ parameterization
            Normal3f::Simd dnds = dndu * duds + dndv * dvds;
            Normal3f::Simd dndt = dndu * dudt + dndv * dvdt;
            dndu = dnds;
            dndv = dndt;

            // Initialize bilinear patch intersection point error _pError_
            Point3f::Simd pAbsSum = Abs( p00 ) + Abs( p01 ) + Abs( p10 ) + Abs( p11 );
            Vector3f pError = gamma( 6 ) * Vector3f( pAbsSum );

            // Initialize _SurfaceInteraction_ for bilinear patch intersection
            int faceIndex = mesh->faceIndices ? mesh->faceIndices[ blpIndex ] : 0;
            bool flipNormal = mesh->reverseOrientation ^ mesh->transformSwapsHandedness;
            SurfaceInteraction isect( Point3fi( p, pError ), st, wo, dpdu, dpdv, dndu, dndv, time, flipNormal, faceIndex );

            // Compute bilinear patch shading normal if necessary
            if ( mesh->n )
            {
                // Compute shading normals for bilinear patch intersection point
                Normal3f::Simd n00 = mesh->n[ v[ 0 ] ], n10 = mesh->n[ v[ 1 ] ];
                Normal3f::Simd n01 = mesh->n[ v[ 2 ] ], n11 = mesh->n[ v[ 3 ] ];
                Normal3f::Simd ns = Lerp2( uv[ 0 ], Lerp2( uv[ 1 ], n00, n01 ), Lerp2( uv[ 1 ], n10, n11 ) );
                if ( ScalarLengthSquared( ns ) > 0 )
                {
                    ns = Normalize( ns );
                    // Set shading geometry for bilinear patch intersection
                    Normal3f::Simd dndu = Lerp2( uv[ 1 ], n10, n11 ) - Lerp2( uv[ 1 ], n00, n01 );
                    Normal3f::Simd dndv = Lerp2( uv[ 0 ], n01, n11 ) - Lerp2( uv[ 0 ], n00, n10 );
                    // Update $\dndu$ and $\dndv$ to account for $(s,t)$ parameterization
                    Normal3f::Simd dnds = dndu * duds + dndv * dvds;
                    Normal3f::Simd dndt = dndu * dudt + dndv * dvdt;
                    dndu = dnds;
                    dndv = dndt;

                    Transform r = RotateFromTo( Vector3f( Normalize( isect.n ) ), Vector3f( ns ) );
                    isect.SetShadingGeometry( ns, r( dpdu ), r( dpdv ), dndu, dndv, true );
                }
            }

            return isect;
        }

    private:
        // BilinearPatch Private Methods
        PBRT_CPU_GPU
            const BilinearPatchMesh* GetMesh( ) const
        {
#ifdef PBRT_IS_GPU_CODE
            return ( *allBilinearMeshesGPU )[ meshIndex ];
#else
            return ( *allMeshes )[ meshIndex ];
#endif
        }

        bool IsRectangle( const BilinearPatchMesh* mesh ) const
        {
            // Get bilinear patch vertices in _p00_, _p01_, _p10_, and _p11_
            const int* v = &mesh->vertexIndices[ 4 * blpIndex ];
            Point3f::Simd p00 = mesh->p[ v[ 0 ] ], p10 = mesh->p[ v[ 1 ] ];
            Point3f::Simd p01 = mesh->p[ v[ 2 ] ], p11 = mesh->p[ v[ 3 ] ];

            if ( p00 == p01 || p01 == p11 || p11 == p10 || p10 == p00 )
                return false;
            // Check if bilinear patch vertices are coplanar
            Normal3f::Simd n( Normalize( Cross( p10 - p00, p01 - p00 ) ) );
            if ( ScalarAbsDot( Normalize( p11 - p00 ), n ) > 1e-5f )
                return false;

            // Check if planar vertices form a rectangle
            Point3f::Simd pCenter = ( p00 + p01 + p10 + p11 ) / 4;
            Float d2[ 4 ] = { ScalarDistanceSquared( p00, pCenter ), ScalarDistanceSquared( p01, pCenter ),
                           ScalarDistanceSquared( p10, pCenter ), ScalarDistanceSquared( p11, pCenter ) };
            for ( int i = 1; i < 4; ++i )
                if ( Math::FastAbs( d2[ i ] - d2[ 0 ] ) / d2[ 0 ] > 1e-4f )
                    return false;
            return true;
        }

        
    };

    inline Bounds3f Shape::Bounds( ) const
    {
        auto bounds = [ & ]( auto ptr ) { return ptr->Bounds( ); };
        return Dispatch( bounds );
    }

    inline pstdo::optional<ShapeIntersection> Shape::Intersect( const Ray& ray, Float tMax ) const
    {
        auto intr = [ & ]( auto ptr ) { return ptr->Intersect( ray, tMax ); };
        return Dispatch( intr );
    }

    inline bool Shape::IntersectP( const Ray& ray, Float tMax ) const
    {
        auto intr = [ & ]( auto ptr ) { return ptr->IntersectP( ray, tMax ); };
        return Dispatch( intr );
    }

    inline Float Shape::Area( ) const
    {
        auto area = [ & ]( auto ptr ) { return ptr->Area( ); };
        return Dispatch( area );
    }

    inline pstdo::optional<ShapeSample> Shape::Sample( Point2f u ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->Sample( u ); };
        return Dispatch( sample );
    }

    inline Float Shape::PDF( const Interaction& in ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PDF( in ); };
        return Dispatch( pdf );
    }

    inline pstdo::optional<ShapeSample> Shape::Sample( const ShapeSampleContext& ctx,
        Point2f u ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->Sample( ctx, u ); };
        return Dispatch( sample );
    }

    inline Float Shape::PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PDF( ctx, wi ); };
        return Dispatch( pdf );
    }

    inline DirectionCone Shape::NormalBounds( ) const
    {
        auto nb = [ & ]( auto ptr ) { return ptr->NormalBounds( ); };
        return Dispatch( nb );
    }

}


#endif
