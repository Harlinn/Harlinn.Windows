#pragma once
#ifndef PBRTO_NEWRAY_H_
#define PBRTO_NEWRAY_H_

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

#include <pbrto/base/NewMedium.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    // Ray Definition
    class Ray
    {
    public:
        // Ray Public Members
        Point3f::Simd o;
        Vector3f::Simd d;
        Float time = 0;
        Medium medium = nullptr;

        // Ray Public Methods
        Ray( ) = default;
        Ray( const Point3f::Simd& o, const Vector3f::Simd& d, Float time = 0.f, Medium medium = nullptr )
            : o( o ), d( d ), time( time ), medium( medium )
        { }

        bool HasNaN( ) const 
        { 
            return ( o.HasNaN( ) || d.HasNaN( ) ); 
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
        Point3f::Simd rxOrigin, ryOrigin;
        Vector3f::Simd rxDirection, ryDirection;

        // RayDifferential Public Methods
        RayDifferential( ) = default;
        RayDifferential( const Point3f::Simd& o, const Vector3f::Simd& d, Float time = 0.f, Medium medium = nullptr )
            : Ray( o, d, time, medium )
        {
        }

        explicit RayDifferential( const Ray& ray ) : Ray( ray ) {}

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
    inline Point3f::Simd OffsetRayOrigin( const Point3fi& pi, const Normal3f::Simd& n, const Vector3f::Simd& w )
    {
        // Find vector _offset_ to corner of error bounds and compute initial _po_
        auto d = Dot( Abs( n ), pi.Error( ) );
        Vector3f offset = d * Vector3f( n );
        if ( ScalarDot( w, n ) < 0 )
            offset = -offset;
        Point3f po = Point3f( pi ) + offset;

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

    inline Ray SpawnRay( const Point3fi& pi, const Normal3f::Simd& n, Float time, const Vector3f::Simd& d )
    {
        return Ray( OffsetRayOrigin( pi, n, d ), d, time );
    }

    inline Ray SpawnRayTo( const Point3fi& pFrom, const Normal3f::Simd& n, Float time, const Point3f::Simd& pTo )
    {
        Vector3f::Simd d = pTo - Point3f( pFrom );
        return SpawnRay( pFrom, n, time, d );
    }

    inline Ray SpawnRayTo( const Point3fi& pFrom, const Normal3f::Simd& nFrom, Float time, const Point3fi& pTo, const Normal3f::Simd& nTo )
    {
        Point3f::Simd pf = OffsetRayOrigin( pFrom, nFrom, Point3f( pTo ) - Point3f( pFrom ) );
        Point3f::Simd pt = OffsetRayOrigin( pTo, nTo, pf - Point3f( pTo ) );
        return Ray( pf, pt - pf, time );
    }


}

#endif
