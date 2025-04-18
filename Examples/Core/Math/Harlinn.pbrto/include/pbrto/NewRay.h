#pragma once
#ifndef PBRTO_NEWRAY_H_
#define PBRTO_NEWRAY_H_

#include <pbrto/NewPbrt.h>

#include <pbrto/base/NewMedium.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    // Ray Definition
    class alignas( Point3f::Traits::AlignAs ) Ray
    {
    public:
        // Ray Public Members
        Point3f::Simd o;
        Vector3f::Simd d;
        Float time = 0;
        Medium medium = nullptr;

        // Ray Public Methods
        Ray( ) = default;
        Ray( const Point3f& o, const Vector3f& d, Float time = 0.f, Medium medium = nullptr )
            : o( o ), d( d ), time( time ), medium( medium )
        { }
        Ray( const Point3f::Simd& o, const Vector3f::Simd& d, Float time = 0.f, Medium medium = nullptr )
            : o( o ), d( d ), time( time ), medium( medium )
        { }

        bool HasNaN( ) const 
        { 
            return o.HasNaN( ) || d.HasNaN( ); 
        }

        std::string ToString( ) const;

        Point3f::Simd operator()( Float t ) const
        { 
            return o + d * t; 
        }

        

        
    };

    // RayDifferential Definition
    class RayDifferential : public Ray
    {
    public:
        // RayDifferential Public Members
        bool hasDifferentials = false;
        Point3f::Simd rxOrigin; 
        Point3f::Simd ryOrigin;
        Vector3f::Simd rxDirection;
        Vector3f::Simd ryDirection;

        // RayDifferential Public Methods
        RayDifferential( ) = default;
        RayDifferential( const Point3f& o, const Vector3f& d, Float time = 0.f, Medium medium = nullptr )
            : Ray( o, d, time, medium )
        { }
        RayDifferential( const Point3f::Simd& o, const Vector3f::Simd& d, Float time = 0.f, Medium medium = nullptr )
            : Ray( o, d, time, medium )
        { }

        explicit RayDifferential( const Ray& ray ) 
            : Ray( ray ) 
        { }

        void ScaleDifferentials( Float s )
        {
            rxOrigin = o + ( rxOrigin - o ) * s;
            ryOrigin = o + ( ryOrigin - o ) * s;
            rxDirection = d + ( rxDirection - d ) * s;
            ryDirection = d + ( ryDirection - d ) * s;
        }

        bool HasNaN( ) const
        {
            return Ray::HasNaN( ) ||
                ( hasDifferentials && ( rxOrigin.HasNaN( ) || ryOrigin.HasNaN( ) ||
                    rxDirection.HasNaN( ) || ryDirection.HasNaN( ) ) );
        }
        std::string ToString( ) const;

        
    };

    // Ray Inline Functions
    inline Point3f OffsetRayOrigin( const Point3fi pi, const Normal3f n, const Vector3f w )
    {
        // Find vector _offset_ to corner of error bounds and compute initial _po_
        auto d = Dot( Abs( n ), pi.Error( ) );
        Vector3f offset = d * n;
        if ( ScalarDot( w, n ) < 0 )
        {
            offset = -offset;
        }
        Point3f po = Point3f( pi ) + offset;

        // Round offset point _po_ away from _p_
        for ( int i = 0; i < 3; ++i )
        {
            if ( offset[ i ] > 0 )
                po[ i ] = NextUp( po[ i ] );
            else if ( offset[ i ] < 0 )
                po[ i ] = NextDown( po[ i ] );
        }
        return po;
    }
    inline Point3f::Simd OffsetRayOrigin( const Point3fi pi, const Normal3f::Simd& n, const Vector3f::Simd& w )
    {
        // Find vector _offset_ to corner of error bounds and compute initial _po_
        auto d = Dot( Abs( n ), pi.Error( ) );
        Vector3f offset = d * n;
        if ( ScalarDot( w, n ) < 0 )
            offset = -offset;
        Point3f po = Point3f( pi ) + offset;

        // Round offset point _po_ away from _p_
        for ( int i = 0; i < 3; ++i )
        {
            if ( offset[ i ] > 0 )
                po[ i ] = NextUp( po[ i ] );
            else if ( offset[ i ] < 0 )
                po[ i ] = NextDown( po[ i ] );
        }

        return po;
    }


    inline Ray SpawnRay( Point3fi pi, Normal3f n, Float time, Vector3f d )
    {
        return Ray( OffsetRayOrigin( pi, n, d ), d, time );
    }
    inline Ray SpawnRay( Point3fi pi, const Normal3f::Simd& n, Float time, const Vector3f::Simd& d )
    {
        return Ray( OffsetRayOrigin( pi, n, d ), d, time );
    }

    inline Ray SpawnRayTo( Point3fi pFrom, Normal3f n, Float time, Point3f pTo )
    {
        Vector3f d = pTo - Point3f( pFrom );
        return SpawnRay( pFrom, n, time, d );
    }
    inline Ray SpawnRayTo( Point3fi pFrom, const Normal3f::Simd& n, Float time, const Point3f::Simd& pTo )
    {
        auto d = pTo - Point3f( pFrom );
        return SpawnRay( pFrom, n, time, d );
    }


    inline Ray SpawnRayTo( Point3fi pFrom, Normal3f nFrom, Float time, Point3fi pTo, Normal3f nTo )
    {
        Point3f pf = OffsetRayOrigin( pFrom, nFrom, ToVector3f( Point3f( pTo ) - Point3f( pFrom ) ) );
        Point3f pt = OffsetRayOrigin( pTo, nTo, ToVector3f( pf - Point3f( pTo ) ) );
        return Ray( pf, pt - pf, time );
    }

    inline Ray SpawnRayTo( Point3fi pFrom, const Normal3f::Simd& nFrom, Float time, Point3fi pTo, const Normal3f::Simd& nTo )
    {
        auto pf = OffsetRayOrigin( pFrom, nFrom, Vector3f::Simd( Point3f( pTo ) - Point3f( pFrom ) ) );
        Point3f pt = OffsetRayOrigin( pTo, nTo, Vector3f::Simd( pf - Point3f( pTo ) ) );
        return Ray( pf, pt - pf, time );
    }


}

#endif
