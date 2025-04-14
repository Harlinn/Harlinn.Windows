#pragma once
#ifndef PBRT_UTIL_NEWTRANSFORM_H_
#define PBRT_UTIL_NEWTRANSFORM_H_

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

#include <pbrto/NewRay.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

#include <stdio.h>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>

//#define USE_NEW_TRANSFORM 1

#ifdef USE_NEW_TRANSFORM

namespace pbrto
{

    // Transform Definition
    class Transform
    {
        // Transform Private Members
        SquareMatrix<4> m;
        SquareMatrix<4> mInv;

        SquareMatrix<4>::Simd m_;
        SquareMatrix<4>::Simd mInv_;

    public:
        // Transform Public Methods
        Transform( )
            : m_( SquareMatrix<4>::Simd::Identity() ), mInv_( SquareMatrix<4>::Simd::Identity( ) )
        { }

        Transform( const SquareMatrix<4>& m )
            : m( m ) , m_( Math::Transpose( m ) )

        {
            pstdo::optional<SquareMatrix<4>> inv = SquareMatrix<4>( Inverse( m ) );

            if ( inv )
            {
                mInv = *inv;
            }
            else
            {
                // Initialize _mInv_ with not-a-number values
                Float NaN = std::numeric_limits<Float>::has_signaling_NaN
                    ? std::numeric_limits<Float>::signaling_NaN( )
                    : std::numeric_limits<Float>::quiet_NaN( );
                for ( int i = 0; i < 4; ++i )
                    for ( int j = 0; j < 4; ++j )
                        mInv[ i ][ j ] = NaN;
            }
            mInv_ = Math::Transpose( mInv );
        }


        Transform( const Float( &mat )[ 4 ][ 4 ] )
            : Transform( SquareMatrix<4>( mat ) )
        {
        }

        Transform( const SquareMatrix<4>& m, const SquareMatrix<4>& mInv )
            : m( m ), mInv( mInv ), m_( Math::Transpose( m ) ), mInv_( Math::Transpose( mInv ) )
        {
        }

        Transform( const SquareMatrix<4>& m, const SquareMatrix<4>& mInv, const SquareMatrix<4>::Simd& mSimd, const SquareMatrix<4>::Simd& mInvSimd )
            : m( m ), mInv( mInv ), m_( mSimd ), mInv_( mInvSimd )
        {
        }


        explicit Transform( const Frame& frame );
        explicit Transform( const Quaternion& q );

        inline Ray ApplyInverse( const Ray& r, Float* tMax = nullptr ) const;

        inline RayDifferential ApplyInverse( const RayDifferential& r, Float* tMax = nullptr ) const;


        //template <typename T>
        PBRT_CPU_GPU inline Vector3<float>::Simd ApplyInverse( const Vector3<float>& v ) const;

        inline Vector3<float>::Simd ApplyInverse( const Vector3<float>::Simd& v ) const;

        //template <typename T>
        PBRT_CPU_GPU inline Normal3<float>::Simd ApplyInverse( const Normal3<float>& n ) const;

        inline Normal3<float>::Simd ApplyInverse( const Normal3<float>::Simd& n ) const;

        const SquareMatrix<4>& GetMatrix( ) const
        {
            return m;
        }

        const SquareMatrix<4>::Simd& GetMatrixSimd( ) const
        {
            return m_;
        }


        const SquareMatrix<4>& GetInverseMatrix( ) const
        {
            return mInv;
        }

        const SquareMatrix<4>::Simd& GetInverseMatrixSimd( ) const
        {
            return mInv_;
        }

        std::string ToString( ) const
        {
            return std::format( "[ m: {} mInv: {} ]", m, mInv );
        }

        bool operator==( const Transform& t ) const
        {
            return t.m_ == m_;
        }

        bool operator!=( const Transform& t ) const
        {
            return t.m_ != m_;
        }
        bool IsIdentity( ) const
        {
            return m.IsIdentity( );
        }

        bool HasScale( Float tolerance = 1e-3f ) const
        {
            Float la2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 1, 0, 0 ) ) );
            Float lb2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 0, 1, 0 ) ) );
            Float lc2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 0, 0, 1 ) ) );

            return ( std::abs( la2 - 1 ) > tolerance || std::abs( lb2 - 1 ) > tolerance ||
                std::abs( lc2 - 1 ) > tolerance );
        }


        Point3<float>::Simd operator()( const Point3<float>& p ) const;

        Point3<float>::Simd operator()( const typename Point3<float>::Simd& p ) const;

        inline Point3<float>::Simd ApplyInverse( const Point3<float>& p ) const;

        inline Point3<float>::Simd ApplyInverse( const typename Point3<float>::Simd& p ) const;

        inline Vector3<float>::Simd operator()( const Vector3<float>& v ) const;

        inline Vector3<float>::Simd operator()( const typename Vector3<float>::Simd& v ) const;

        inline Normal3<float>::Simd operator()( const Normal3<float>& ) const;

        inline Normal3<float>::Simd operator()( const typename Normal3<float>::Simd& ) const;

        Ray operator()( const Ray& r, Float* tMax = nullptr ) const;

        RayDifferential operator()( const RayDifferential& r, Float* tMax = nullptr ) const;

        Bounds3f operator()( const Bounds3f& b ) const;


        Transform operator*( const Transform& t2 ) const
        {
            auto matrix = m_ * t2.m_;
            auto inverseMatrix = t2.mInv_ * mInv_;
            return Transform( Math::Transpose( matrix ), Math::Transpose( inverseMatrix ), matrix, inverseMatrix );
        }

        bool SwapsHandedness( ) const;

        explicit operator Quaternion( ) const;

        void Decompose( Vector3f* T, SquareMatrix<4>* R, SquareMatrix<4>* S ) const;

        Interaction operator()( const Interaction& in ) const;

        Interaction ApplyInverse( const Interaction& in ) const;

        SurfaceInteraction operator()( const SurfaceInteraction& si ) const;

        SurfaceInteraction ApplyInverse( const SurfaceInteraction& in ) const;

        Point3fi operator()( const Point3fi& p ) const;
        Point3fi ApplyInverse( const Point3fi& p ) const;

        Vector3fi operator()( const Vector3fi& v ) const;
    };

    // Transform Function Declarations
    PBRTO_EXPORT Transform Translate( const Vector3f& delta );

    PBRTO_EXPORT Transform Scale( Float x, Float y, Float z );

    PBRTO_EXPORT Transform RotateX( Float theta );
    PBRTO_EXPORT Transform RotateY( Float theta );
    PBRTO_EXPORT Transform RotateZ( Float theta );

    PBRTO_EXPORT Transform LookAt( const Point3f& pos, const Point3f& look, const Vector3f& up );

    
    Transform Orthographic( Float znear, Float zfar );

    Transform Perspective( Float fov, Float znear, Float zfar );

    // Transform Inline Functions
    inline Transform Inverse( const Transform& t )
    {
        return Transform( t.GetInverseMatrix( ), t.GetMatrix( ), t.GetInverseMatrixSimd( ), t.GetMatrixSimd( ) );
    }

    PBRT_CPU_GPU inline Transform Transpose( const Transform& t )
    {
        return Transform( Math::Transpose( t.GetMatrix( ) ),
            Math::Transpose( t.GetInverseMatrix( ) ),
            Math::Transpose( t.GetMatrixSimd( ) ),
            Math::Transpose( t.GetInverseMatrixSimd( ) ) );
    }


    PBRT_CPU_GPU inline Transform Rotate( Float theta, const Vector3f& axis )
    {
        auto rTheta = Math::Deg2Rad( theta );
        SquareMatrix<4> m = Math::RotationAxis( axis, rTheta );
        return Transform( Math::Transpose( m ), m );
    }


    PBRT_CPU_GPU inline Transform RotateFromTo( const Vector3f& from, const Vector3f& to )
    {
        // Compute intermediate vector for vector reflection
        Vector3f refl;
        if ( std::abs( from.x ) < 0.72f && std::abs( to.x ) < 0.72f )
            refl = Vector3f( 1, 0, 0 );
        else if ( std::abs( from.y ) < 0.72f && std::abs( to.y ) < 0.72f )
            refl = Vector3f( 0, 1, 0 );
        else
            refl = Vector3f( 0, 0, 1 );

        // Initialize matrix _r_ for rotation
        Vector3f u = refl - from;
        Vector3f v = refl - to;
        SquareMatrix<4> r;
        auto dotUU = Math::ScalarDot( u, u );
        auto dotVV = Math::ScalarDot( v, v );
        auto dotUV = Math::ScalarDot( u, v );
        for ( int i = 0; i < 3; ++i )
        {
            for ( int j = 0; j < 3; ++j )
            {
                // Initialize matrix element _r[i][j]_
                r[ i ][ j ] = ( ( i == j ) ? 1 : 0 ) -
                    2 / dotUU * u[ i ] * u[ j ] - 2 / dotVV * v[ i ] * v[ j ] +
                    4 * dotUV / ( dotUU * dotVV ) * v[ i ] * u[ j ];
            }
        }
        return Transform( r, Math::Transpose( r ) );
    }



    inline Vector3fi Transform::operator()( const Vector3fi& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;
        constexpr Float gammaValue = gamma( 3 );
        constexpr Traits::SIMDType gammaVector = { gammaValue, gammaValue, gammaValue,0.f };
        constexpr Traits::SIMDType gammaVectorPlussOne = { gammaValue + 1.f, gammaValue + 1.f, gammaValue + 1.f,0.f };

        Float x = Float( v.x ), y = Float( v.y ), z = Float( v.z );
        Traits::SIMDType vec = { x, y, z, 0.f };

        Vector3Simd result = Traits::TransformNormal( vec, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] );

        Vector3Simd vOutError;
        if ( v.IsExact( ) )
        {
            vOutError.simd = Traits::Mul( gammaVector, Traits::Abs( result.simd ) );
        }
        else
        {
            Traits::SIMDType vInError = Traits::Load( v.Error( ).values );
            vOutError.simd = Traits::Add( Traits::Mul( gammaVectorPlussOne, Traits::Abs( Traits::TransformNormal( vInError, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] ) ) ),
                Traits::Mul( gammaVector, Traits::Abs( result.simd ) ) );
        }
        return Vector3fi( Vector3f( result ), Vector3f( vOutError ) );
    }

    inline Point3fi Transform::operator()( const Point3fi& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;
        using Point3Traits = Point3<float>::Traits;

        constexpr Float gammaValue = gamma( 3 );
        constexpr Float gammaPlusOneValue = gammaValue + 1.f;

        Traits::SIMDType gammaVector = Point3Traits::Set( gammaValue, gammaValue, gammaValue );
        Traits::SIMDType gammaVectorPlussOne = Point3Traits::Set( gammaPlusOneValue, gammaPlusOneValue, gammaPlusOneValue );

        Point3Simd point( static_cast< Point3<float> >( p ) );

        Point3Simd result = Traits::TransformPoint( point.simd, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] );

        Point3Simd vOutError;
        if ( p.IsExact( ) )
        {
            vOutError.simd = Traits::Mul( gammaVector, Traits::Abs( result.simd ) );
        }
        else
        {
            Traits::SIMDType vInError = Point3Traits::Load( p.Error( ).values );
            vOutError.simd = Traits::Add( Traits::Mul( gammaVectorPlussOne, Traits::Abs( Traits::TransformPoint( vInError, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] ) ) ), Traits::Mul( gammaVector, Traits::Abs( result.simd ) ) );
        }
        return Point3fi( Point3f( result ), Point3f( vOutError ) );
    }



    // Transform Inline Methods
    //template <typename T>
    PBRT_CPU_GPU inline Point3<float>::Simd Transform::operator()( const Point3<float>& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        Point3Simd result = Traits::SetW( Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] ), 0.f );
        return result;
    }
    inline Point3<float>::Simd Transform::operator()( const typename Point3<float>::Simd& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        Point3Simd result = Traits::SetW( Traits::TransformPoint( p.simd, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] ), 0.f );
        return result;
    }


    PBRT_CPU_GPU inline Vector3<float>::Simd Transform::operator()( const Vector3<float>& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( Vector3<float>::Traits::Load( v.data( ) ), m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] );
        //Vector3Simd result = Vector3<float>::Traits::TransformVector( Vector3<float>::Traits::Load( v.data( ) ), m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] );
        return result;
    }
    inline Vector3<float>::Simd Transform::operator()( const typename Vector3<float>::Simd& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( v.simd, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] );
        //Vector3Simd result = Vector3<float>::Traits::TransformVector( v.simd, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ], m_.simd[ 3 ] );
        return result;
    }

    inline Normal3<float>::Simd Transform::operator()( const typename Normal3<float>::Simd& n ) const
    {
        using Traits = Vector3<float>::Traits;

        auto result = Traits::Dot<0b01110001>( mInv_.simd[ 0 ], n.simd );
        result = Traits::Add( Traits::Dot<0b01110010>( mInv_.simd[ 1 ], n.simd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( mInv_.simd[ 2 ], n.simd ), result );
        return Normal3<float>::Simd( result );
    }

    PBRT_CPU_GPU inline Normal3<float>::Simd Transform::operator()( const Normal3<float>& n ) const
    {
        using Traits = Vector3<float>::Traits;
        auto nSimd = Traits::Load( n.values );
        
        auto result = Traits::Dot<0b01110001>( mInv_.simd[ 0 ], nSimd );
        result = Traits::Add( Traits::Dot<0b01110010>( mInv_.simd[ 1 ], nSimd ), result);
        result = Traits::Add( Traits::Dot<0b01110100>( mInv_.simd[ 2 ], nSimd ), result );
        return Normal3<float>::Simd( result );
    }
    

    PBRT_CPU_GPU inline Ray Transform::operator()( const Ray& r, Float* tMax ) const
    {
        Point3fi o = ( *this )( Point3fi( r.o ) );
        auto d = ( *this )( r.d );
        // Offset ray origin to edge of error bounds and compute _tMax_
        if ( Float lengthSquared = ScalarLengthSquared( d ); lengthSquared > 0 )
        {
            Float dt = ScalarDot( Abs( d ), o.Error( ) ) / lengthSquared;

            o += d * dt;
            if ( tMax )
                *tMax -= dt;
        }
        return Ray( Point3f( o ), Vector3f( d ), r.time, r.medium );
    }


    inline RayDifferential Transform::operator()( const RayDifferential& r, Float* tMax ) const
    {
        Ray tr = ( *this )( Ray( r ), tMax );
        RayDifferential ret( tr.o, tr.d, tr.time, tr.medium );
        ret.hasDifferentials = r.hasDifferentials;
        ret.rxOrigin = ( *this )( r.rxOrigin );
        ret.ryOrigin = ( *this )( r.ryOrigin );
        ret.rxDirection = ( *this )( r.rxDirection );
        ret.ryDirection = ( *this )( r.ryDirection );
        return ret;
    }

    PBRT_CPU_GPU inline Transform::Transform( const Frame& frame )
        : Transform( SquareMatrix<4>( frame.x.x, frame.x.y, frame.x.z, 0, frame.y.x, frame.y.y,
            frame.y.z, 0, frame.z.x, frame.z.y, frame.z.z, 0, 0, 0, 0,
            1 ) )
    {
    }

    PBRT_CPU_GPU inline Transform::Transform( const Quaternion& q )
        : m_( Math::Rotation( q ) )
    {
        mInv_ = Math::Transpose( m_ );
        m = mInv_;
        mInv = m_;
    }


    PBRT_CPU_GPU inline Point3<float>::Simd Transform::ApplyInverse( const Point3<float>& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        Point3Simd result = Traits::SetW( Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), mInv_.simd[ 0 ], mInv_.simd[ 1 ], mInv_.simd[ 2 ], mInv_.simd[ 3 ] ), 0.f );
        return result;
    }
    inline Point3<float>::Simd Transform::ApplyInverse( const typename Point3<float>::Simd& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        Point3Simd result = Traits::SetW( Traits::TransformPoint( p.simd, mInv_.simd[ 0 ], mInv_.simd[ 1 ], mInv_.simd[ 2 ], mInv_.simd[ 3 ] ), 0.f );
        return result;
    }


    PBRT_CPU_GPU inline Vector3<float>::Simd Transform::ApplyInverse( const Vector3<float>& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( Vector3<float>::Traits::Load( v.data( ) ), mInv_.simd[ 0 ], mInv_.simd[ 1 ], mInv_.simd[ 2 ] );
        return result;
    }

    inline Vector3<float>::Simd Transform::ApplyInverse( const Vector3<float>::Simd& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( v.simd, mInv_.simd[ 0 ], mInv_.simd[ 1 ], mInv_.simd[ 2 ] );
        return result;
    }


    PBRT_CPU_GPU inline Normal3<float>::Simd Transform::ApplyInverse( const Normal3<float>& n ) const
    {
        /*
        using Traits = Vector3<float>::Traits;
        using Normal3Simd = Normal3<float>::Simd;

        Normal3Simd result = Normal3<float>::Traits::TransformNormal( Normal3<float>::Traits::Load( n.data( ) ), m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] );
        return result;
        */
        using Traits = Vector3<float>::Traits;
        auto nSimd = Traits::Load( n.values );

        auto result = Traits::Dot<0b01110001>( m_.simd[ 0 ], nSimd );
        result = Traits::Add( Traits::Dot<0b01110010>( m_.simd[ 1 ], nSimd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( m_.simd[ 2 ], nSimd ), result );
        return Normal3<float>::Simd( result );
    }

    inline Normal3<float>::Simd Transform::ApplyInverse( const Normal3<float>::Simd& n ) const
    {
        /*
        using Traits = Vector3<float>::Traits;
        using Normal3Simd = Normal3<float>::Simd;

        Normal3Simd result = Normal3<float>::Traits::TransformNormal( n.simd, m_.simd[ 0 ], m_.simd[ 1 ], m_.simd[ 2 ] );
        return result;
        */
        using Traits = Vector3<float>::Traits;

        auto result = Traits::Dot<0b01110001>( m_.simd[ 0 ], n.simd );
        result = Traits::Add( Traits::Dot<0b01110010>( m_.simd[ 1 ], n.simd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( m_.simd[ 2 ], n.simd ), result );
        return Normal3<float>::Simd( result );
    }


    PBRT_CPU_GPU inline Ray Transform::ApplyInverse( const Ray& r, Float* tMax ) const
    {
        Point3fi o = ApplyInverse( Point3fi( r.o ) );
        auto d = ApplyInverse( r.d );
        // Offset ray origin to edge of error bounds and compute _tMax_
        Float lengthSquared = ScalarLengthSquared( d );
        if ( lengthSquared > 0 )
        {
            Vector3f oError( o.x.Width( ) / 2, o.y.Width( ) / 2, o.z.Width( ) / 2 );
            Float dt = ScalarDot( Abs( d ), oError ) / lengthSquared;
            o += d * dt;
            if ( tMax )
                *tMax -= dt;
        }
        return Ray( Point3f( o ), Vector3f( d ), r.time, r.medium );
    }

    PBRT_CPU_GPU inline RayDifferential Transform::ApplyInverse( const RayDifferential& r, Float* tMax ) const
    {
        Ray tr = ApplyInverse( static_cast< const Ray& >( r ), tMax );
        RayDifferential ret( tr.o, tr.d, tr.time, tr.medium );
        ret.hasDifferentials = r.hasDifferentials;
        ret.rxOrigin = ApplyInverse( r.rxOrigin );
        ret.ryOrigin = ApplyInverse( r.ryOrigin );
        ret.rxDirection = ApplyInverse( r.rxDirection );
        ret.ryDirection = ApplyInverse( r.ryDirection );
        return ret;
    }

    // AnimatedTransform Definition
    class AnimatedTransform
    {
    public:
        // AnimatedTransform Public Methods
        AnimatedTransform( ) = default;
        explicit AnimatedTransform( const Transform& t ) : AnimatedTransform( t, 0, t, 1 ) {}
        AnimatedTransform( const Transform& startTransform, Float startTime,
            const Transform& endTransform, Float endTime );

        PBRT_CPU_GPU
            bool IsAnimated( ) const { return actuallyAnimated; }

        PBRT_CPU_GPU
            Ray ApplyInverse( const Ray& r, Float* tMax = nullptr ) const;

        PBRT_CPU_GPU
            Point3f ApplyInverse( Point3f p, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( p );
            return Interpolate( time ).ApplyInverse( p );
        }
        PBRT_CPU_GPU
            Vector3f ApplyInverse( Vector3f v, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( v );
            return Interpolate( time ).ApplyInverse( v );
        }
        PBRT_CPU_GPU
            Normal3f operator()( Normal3f n, Float time ) const;
        PBRT_CPU_GPU
            Normal3f ApplyInverse( Normal3f n, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( n );
            return Interpolate( time ).ApplyInverse( n );
        }
        PBRT_CPU_GPU
            Interaction operator()( const Interaction& it ) const;
        PBRT_CPU_GPU
            Interaction ApplyInverse( const Interaction& it ) const;
        PBRT_CPU_GPU
            SurfaceInteraction operator()( const SurfaceInteraction& it ) const;
        PBRT_CPU_GPU
            SurfaceInteraction ApplyInverse( const SurfaceInteraction& it ) const;
        PBRT_CPU_GPU
            bool HasScale( ) const 
        { 
            return startTransform.HasScale( ) || endTransform.HasScale( ); 
        }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            Transform Interpolate( Float time ) const;

        PBRT_CPU_GPU
            Ray operator()( const Ray& r, Float* tMax = nullptr ) const;
        PBRT_CPU_GPU
            RayDifferential operator()( const RayDifferential& r, Float* tMax = nullptr ) const;
        PBRT_CPU_GPU
            Point3f operator()( Point3f p, Float time ) const;
        PBRT_CPU_GPU
            Vector3f operator()( Vector3f v, Float time ) const;

        PBRT_CPU_GPU
            Bounds3f MotionBounds( const Bounds3f& b ) const;

        PBRT_CPU_GPU
            Bounds3f BoundPointMotion( Point3f p ) const;

        // AnimatedTransform Public Members
        Transform startTransform, endTransform;
        Float startTime = 0, endTime = 1;

    private:
        // AnimatedTransform Private Methods
        PBRT_CPU_GPU
            static void FindZeros( Float c1, Float c2, Float c3, Float c4, Float c5, Float theta,
                Interval tInterval, pstdo::span<Float> zeros, int* nZeros,
                int depth = 8 );

        // AnimatedTransform Private Members
        bool actuallyAnimated = false;
        Vector3f T[ 2 ];
        Quaternion R[ 2 ];
        SquareMatrix<4> S[ 2 ];
        bool hasRotation;
        struct DerivativeTerm
        {
            PBRT_CPU_GPU
                DerivativeTerm( ) {}
            PBRT_CPU_GPU
                DerivativeTerm( Float c, Float x, Float y, Float z ) : kc( c ), kx( x ), ky( y ), kz( z ) {}
            Float kc, kx, ky, kz;
            PBRT_CPU_GPU
                Float Eval( Point3f p ) const { return kc + kx * p.x + ky * p.y + kz * p.z; }
        };
        DerivativeTerm c1[ 3 ], c2[ 3 ], c3[ 3 ], c4[ 3 ], c5[ 3 ];
    };

}

namespace std
{

    template <>
    struct hash<pbrto::Transform>
    {
        size_t operator()( const pbrto::Transform& t ) const
        {
            pbrto::SquareMatrix<4> m = t.GetMatrix( );
            return pbrto::Hash( m );
        }
    };

    template<typename CharT>
    struct formatter<pbrto::Transform, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const pbrto::Transform& t, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[ m: {} mInv: {}, m_: {} mInv_: {} ]", t.GetMatrix( ), t.GetInverseMatrix( ), t.GetMatrixSimd(), t.GetInverseMatrixSimd( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[ m: {} mInv: {}, m_: {} mInv_: {} ]", t.GetMatrix( ), t.GetInverseMatrix( ), t.GetMatrixSimd( ), t.GetInverseMatrixSimd( ) );
            }
        }
    };


}  // namespace std

#else

namespace pbrto
{

    // Transform Definition
    class Transform
    {
        // Transform Private Members
        SquareMatrix<4> m_, mInv_;
    public:
        // Transform Public Methods
        Transform( ) = default;

        Transform( const SquareMatrix<4>& m ) 
            : m_( m )
        {
            pstdo::optional<SquareMatrix<4>> inv = SquareMatrix<4>( Inverse( m ) );
            if ( inv )
                mInv_ = *inv;
            else
            {
                // Initialize _mInv_ with not-a-number values
                Float NaN = std::numeric_limits<Float>::has_signaling_NaN
                    ? std::numeric_limits<Float>::signaling_NaN( )
                    : std::numeric_limits<Float>::quiet_NaN( );
                for ( int i = 0; i < 4; ++i )
                    for ( int j = 0; j < 4; ++j )
                        mInv_[ i ][ j ] = NaN;
            }
        }

        Transform( const Float( &mat )[ 4 ][ 4 ] )
            : Transform( SquareMatrix<4>( mat ) )
        {
        }

        Transform( const SquareMatrix<4>& m, const SquareMatrix<4>& mInv )
            : m_( m ), mInv_( mInv )
        {
        }


        inline Ray ApplyInverse( const Ray& r, Float* tMax = nullptr ) const;
        inline RayDifferential ApplyInverse( const RayDifferential& r, Float* tMax = nullptr ) const;

        template <typename T>
        inline Vector3<T> ApplyInverse( Vector3<T> v ) const;

        template <typename T>
        inline Normal3<T> ApplyInverse( Normal3<T> ) const;

        PBRTO_EXPORT
        std::string ToString( ) const;

        

        const SquareMatrix<4>& GetMatrix( ) const 
        { 
            return m_; 
        }
        const SquareMatrix<4>& GetInverseMatrix( ) const 
        { 
            return mInv_; 
        }

        bool operator==( const Transform& t ) const 
        { 
            return t.m_ == m_; 
        }
        bool operator!=( const Transform& t ) const 
        { 
            return t.m_ != m_; 
        }
        bool IsIdentity( ) const 
        { 
            return m_.IsIdentity( ); 
        }

        bool HasScale( Float tolerance = 1e-3f ) const
        {
            Float la2 = ScalarLengthSquared( ( *this )( Vector3f( 1, 0, 0 ) ) );
            Float lb2 = ScalarLengthSquared( ( *this )( Vector3f( 0, 1, 0 ) ) );
            Float lc2 = ScalarLengthSquared( ( *this )( Vector3f( 0, 0, 1 ) ) );
            return ( std::abs( la2 - 1 ) > tolerance || std::abs( lb2 - 1 ) > tolerance || std::abs( lc2 - 1 ) > tolerance );
        }

        template <typename T>
        Point3<T> operator()( const Point3<T>& p ) const;

        template <typename T>
        inline Point3<T> ApplyInverse( const Point3<T>& p ) const;

        template <typename T>
        Vector3<T> operator()( const Vector3<T>& v ) const;

        template <typename T>
        Normal3<T> operator()( const Normal3<T>& ) const;

        Ray operator()( const Ray& r, Float* tMax = nullptr ) const;
        RayDifferential operator()( const RayDifferential& r, Float* tMax = nullptr ) const;

        PBRTO_EXPORT
        Bounds3f operator()( const Bounds3f& b ) const;

        Transform operator*( const Transform& t2 ) const
        {
            return Transform( m_ * t2.m_, t2.mInv_ * mInv_ );
        }

        PBRTO_EXPORT
        bool SwapsHandedness( ) const;

        explicit Transform( const Frame& frame );

        explicit Transform( const Quaternion& q );

        PBRTO_EXPORT
        explicit operator Quaternion( ) const;

        void Decompose( Vector3f* T, SquareMatrix<4>* R, SquareMatrix<4>* S ) const;

        PBRTO_EXPORT
        Interaction operator()( const Interaction& in ) const;
        PBRTO_EXPORT
        Interaction ApplyInverse( const Interaction& in ) const;
        PBRTO_EXPORT
        SurfaceInteraction operator()( const SurfaceInteraction& si ) const;

        PBRTO_EXPORT
        SurfaceInteraction ApplyInverse( const SurfaceInteraction& in ) const;

        Point3fi operator()( const Point3fi& p ) const;

        Vector3fi operator()( const Vector3fi& v ) const;
        PBRTO_EXPORT
        Point3fi ApplyInverse( const Point3fi& p ) const;

    private:
        
    };

    // Transform Function Declarations
    PBRTO_EXPORT
    Transform Translate( Vector3f delta );

    PBRTO_EXPORT
    Transform Scale( Float x, Float y, Float z );

    PBRTO_EXPORT
    Transform RotateX( Float theta );
    PBRTO_EXPORT
    Transform RotateY( Float theta );
    PBRTO_EXPORT
    Transform RotateZ( Float theta );

    PBRTO_EXPORT
    Transform LookAt( Point3f pos, Point3f look, Vector3f up );

    PBRTO_EXPORT
    Transform Orthographic( Float znear, Float zfar );

    PBRTO_EXPORT
    Transform Perspective( Float fov, Float znear, Float zfar );

    // Transform Inline Functions
    inline Transform Inverse( const Transform& t )
    {
        return Transform( t.GetInverseMatrix( ), t.GetMatrix( ) );
    }

    inline Transform Transpose( const Transform& t )
    {
        return Transform( Transpose( t.GetMatrix( ) ), Transpose( t.GetInverseMatrix( ) ) );
    }

    inline Transform Rotate( Float sinTheta, Float cosTheta, Vector3f axis )
    {
        Vector3f a = Normalize( axis );
        SquareMatrix<4> m;
        // Compute rotation of first basis vector
        m[ 0 ][ 0 ] = a.x * a.x + ( 1 - a.x * a.x ) * cosTheta;
        m[ 0 ][ 1 ] = a.x * a.y * ( 1 - cosTheta ) - a.z * sinTheta;
        m[ 0 ][ 2 ] = a.x * a.z * ( 1 - cosTheta ) + a.y * sinTheta;
        m[ 0 ][ 3 ] = 0;

        // Compute rotations of second and third basis vectors
        m[ 1 ][ 0 ] = a.x * a.y * ( 1 - cosTheta ) + a.z * sinTheta;
        m[ 1 ][ 1 ] = a.y * a.y + ( 1 - a.y * a.y ) * cosTheta;
        m[ 1 ][ 2 ] = a.y * a.z * ( 1 - cosTheta ) - a.x * sinTheta;
        m[ 1 ][ 3 ] = 0;

        m[ 2 ][ 0 ] = a.x * a.z * ( 1 - cosTheta ) - a.y * sinTheta;
        m[ 2 ][ 1 ] = a.y * a.z * ( 1 - cosTheta ) + a.x * sinTheta;
        m[ 2 ][ 2 ] = a.z * a.z + ( 1 - a.z * a.z ) * cosTheta;
        m[ 2 ][ 3 ] = 0;

        return Transform( m, Transpose( m ) );
    }

    inline Transform Rotate( Float theta, Vector3f axis )
    {
        auto rTheta = Math::Deg2Rad( theta );
        SquareMatrix<4> m = Math::RotationAxis( axis, rTheta );
        return Transform( Math::Transpose( m ), m );
        /*
        Float sinTheta = std::sin( Radians( theta ) );
        Float cosTheta = std::cos( Radians( theta ) );
        return Rotate( sinTheta, cosTheta, axis );
        */
    }

    inline Transform RotateRadians( Float theta, Vector3f axis )
    {
        SquareMatrix<4> m = Math::RotationAxis( axis, theta );
        return Transform( Math::Transpose( m ), m );
        /*
        Float sinTheta = std::sin( Radians( theta ) );
        Float cosTheta = std::cos( Radians( theta ) );
        return Rotate( sinTheta, cosTheta, axis );
        */
    }


    inline Transform RotateFromTo( Vector3f from, Vector3f to )
    {
        // Compute intermediate vector for vector reflection
        Vector3f refl;
        if ( std::abs( from.x ) < 0.72f && std::abs( to.x ) < 0.72f )
            refl = Vector3f( 1, 0, 0 );
        else if ( std::abs( from.y ) < 0.72f && std::abs( to.y ) < 0.72f )
            refl = Vector3f( 0, 1, 0 );
        else
            refl = Vector3f( 0, 0, 1 );

        // Initialize matrix _r_ for rotation
        Vector3f u = refl - from; 
        Vector3f v = refl - to;
        auto uDotU = ScalarDot( u, u );
        auto vDotV = ScalarDot( v, v );
        auto uDotV = ScalarDot( u, v );

        SquareMatrix<4> r;
        for ( int i = 0; i < 3; ++i )
        {
            for ( int j = 0; j < 3; ++j )
            {
                // Initialize matrix element _r[i][j]_
                r[ i ][ j ] = ( ( i == j ) ? 1 : 0 ) - 2 / uDotU * u[ i ] * u[ j ] -
                    2 / vDotV * v[ i ] * v[ j ] +
                    4 * uDotV / ( uDotU * vDotV ) * v[ i ] * u[ j ];
            }
        }
        return Transform( r, Transpose( r ) );
    }

    inline Vector3fi Transform::operator()( const Vector3fi& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;
        constexpr Float gammaValue = gamma( 3 );
        constexpr Traits::SIMDType gammaVector = { gammaValue, gammaValue, gammaValue,0.f };
        constexpr Traits::SIMDType gammaVectorPlussOne = { gammaValue + 1.f, gammaValue + 1.f, gammaValue + 1.f,0.f };

        Float x = Float( v.x ), y = Float( v.y ), z = Float( v.z );
        Traits::SIMDType vec = { x, y, z, 0.f };

        auto matrix = Transpose( m_ );

        Vector3Simd result = Traits::TransformNormal( vec, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );

        Vector3Simd vOutError;
        if ( v.IsExact( ) )
        {
            vOutError.simd = Traits::Mul( gammaVector, Traits::Abs( result.simd ) );
        }
        else
        {
            Traits::SIMDType vInError = Traits::Load( v.Error( ).values );
            vOutError.simd = Traits::Add( Traits::Mul( gammaVectorPlussOne, Traits::Abs( Traits::TransformNormal( vInError, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] ) ) ),
                Traits::Mul( gammaVector, Traits::Abs( result.simd ) ) );
        }
        return Vector3fi( Vector3f( result ), Vector3f( vOutError ) );
        /*
        Float x = Float( v.x ), y = Float( v.y ), z = Float( v.z );
        Vector3f vOutError;
        if ( v.IsExact( ) )
        {
            vOutError.x = gamma( 3 ) * ( std::abs( m_[ 0 ][ 0 ] * x ) + std::abs( m_[ 0 ][ 1 ] * y ) +
                std::abs( m_[ 0 ][ 2 ] * z ) );
            vOutError.y = gamma( 3 ) * ( std::abs( m_[ 1 ][ 0 ] * x ) + std::abs( m_[ 1 ][ 1 ] * y ) +
                std::abs( m_[ 1 ][ 2 ] * z ) );
            vOutError.z = gamma( 3 ) * ( std::abs( m_[ 2 ][ 0 ] * x ) + std::abs( m_[ 2 ][ 1 ] * y ) +
                std::abs( m_[ 2 ][ 2 ] * z ) );
        }
        else
        {
            Vector3f vInError = v.Error( );
            vOutError.x = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 0 ][ 0 ] ) * vInError.x +
                std::abs( m_[ 0 ][ 1 ] ) * vInError.y +
                std::abs( m_[ 0 ][ 2 ] ) * vInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 0 ][ 0 ] * x ) + std::abs( m_[ 0 ][ 1 ] * y ) +
                    std::abs( m_[ 0 ][ 2 ] * z ) );
            vOutError.y = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 1 ][ 0 ] ) * vInError.x +
                std::abs( m_[ 1 ][ 1 ] ) * vInError.y +
                std::abs( m_[ 1 ][ 2 ] ) * vInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 1 ][ 0 ] * x ) + std::abs( m_[ 1 ][ 1 ] * y ) +
                    std::abs( m_[ 1 ][ 2 ] * z ) );
            vOutError.z = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 2 ][ 0 ] ) * vInError.x +
                std::abs( m_[ 2 ][ 1 ] ) * vInError.y +
                std::abs( m_[ 2 ][ 2 ] ) * vInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 2 ][ 0 ] * x ) + std::abs( m_[ 2 ][ 1 ] * y ) +
                    std::abs( m_[ 2 ][ 2 ] * z ) );
        }

        Float xp = m_[ 0 ][ 0 ] * x + m_[ 0 ][ 1 ] * y + m_[ 0 ][ 2 ] * z;
        Float yp = m_[ 1 ][ 0 ] * x + m_[ 1 ][ 1 ] * y + m_[ 1 ][ 2 ] * z;
        Float zp = m_[ 2 ][ 0 ] * x + m_[ 2 ][ 1 ] * y + m_[ 2 ][ 2 ] * z;

        return Vector3fi( Vector3f( xp, yp, zp ), vOutError );
        */
    }

    inline Point3fi Transform::operator()( const Point3fi& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;
        using Point3Traits = Point3<float>::Traits;

        constexpr Float gammaValue = gamma( 3 );
        constexpr Float gammaPlusOneValue = gammaValue + 1.f;

        Traits::SIMDType gammaVector = Point3Traits::Set( gammaValue, gammaValue, gammaValue );
        Traits::SIMDType gammaVectorPlussOne = Point3Traits::Set( gammaPlusOneValue, gammaPlusOneValue, gammaPlusOneValue );

        Point3Simd point( static_cast< Point3<float> >( p ) );

        auto matrix = Transpose( m_ );

        Point3Simd result = Traits::TransformPoint( point.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );

        Point3Simd vOutError;
        if ( p.IsExact( ) )
        {
            vOutError.simd = Traits::Mul( gammaVector, Traits::Abs( result.simd ) );
        }
        else
        {
            Traits::SIMDType vInError = Point3Traits::Load( p.Error( ).values );
            vOutError.simd = Traits::Add( Traits::Mul( gammaVectorPlussOne, Traits::Abs( Traits::TransformPoint( vInError, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] ) ) ), Traits::Mul( gammaVector, Traits::Abs( result.simd ) ) );
        }
        return Point3fi( Point3f( result ), Point3f( vOutError ) );

        /*
        Float x = Float( p.x ), y = Float( p.y ), z = Float( p.z );
        // Compute transformed coordinates from point _(x, y, z)_
        Float xp = ( m_[ 0 ][ 0 ] * x + m_[ 0 ][ 1 ] * y ) + ( m_[ 0 ][ 2 ] * z + m_[ 0 ][ 3 ] );
        Float yp = ( m_[ 1 ][ 0 ] * x + m_[ 1 ][ 1 ] * y ) + ( m_[ 1 ][ 2 ] * z + m_[ 1 ][ 3 ] );
        Float zp = ( m_[ 2 ][ 0 ] * x + m_[ 2 ][ 1 ] * y ) + ( m_[ 2 ][ 2 ] * z + m_[ 2 ][ 3 ] );
        Float wp = ( m_[ 3 ][ 0 ] * x + m_[ 3 ][ 1 ] * y ) + ( m_[ 3 ][ 2 ] * z + m_[ 3 ][ 3 ] );

        // Compute absolute error for transformed point, _pError_
        Vector3f pError;
        if ( p.IsExact( ) )
        {
            // Compute error for transformed exact _p_
            pError.x = gamma( 3 ) * ( std::abs( m_[ 0 ][ 0 ] * x ) + std::abs( m_[ 0 ][ 1 ] * y ) +
                std::abs( m_[ 0 ][ 2 ] * z ) + std::abs( m_[ 0 ][ 3 ] ) );
            pError.y = gamma( 3 ) * ( std::abs( m_[ 1 ][ 0 ] * x ) + std::abs( m_[ 1 ][ 1 ] * y ) +
                std::abs( m_[ 1 ][ 2 ] * z ) + std::abs( m_[ 1 ][ 3 ] ) );
            pError.z = gamma( 3 ) * ( std::abs( m_[ 2 ][ 0 ] * x ) + std::abs( m_[ 2 ][ 1 ] * y ) +
                std::abs( m_[ 2 ][ 2 ] * z ) + std::abs( m_[ 2 ][ 3 ] ) );

        }
        else
        {
            // Compute error for transformed approximate _p_
            Vector3f pInError = p.Error( );
            pError.x = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 0 ][ 0 ] ) * pInError.x +
                std::abs( m_[ 0 ][ 1 ] ) * pInError.y +
                std::abs( m_[ 0 ][ 2 ] ) * pInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 0 ][ 0 ] * x ) + std::abs( m_[ 0 ][ 1 ] * y ) +
                    std::abs( m_[ 0 ][ 2 ] * z ) + std::abs( m_[ 0 ][ 3 ] ) );
            pError.y = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 1 ][ 0 ] ) * pInError.x +
                std::abs( m_[ 1 ][ 1 ] ) * pInError.y +
                std::abs( m_[ 1 ][ 2 ] ) * pInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 1 ][ 0 ] * x ) + std::abs( m_[ 1 ][ 1 ] * y ) +
                    std::abs( m_[ 1 ][ 2 ] * z ) + std::abs( m_[ 1 ][ 3 ] ) );
            pError.z = ( gamma( 3 ) + 1 ) * ( std::abs( m_[ 2 ][ 0 ] ) * pInError.x +
                std::abs( m_[ 2 ][ 1 ] ) * pInError.y +
                std::abs( m_[ 2 ][ 2 ] ) * pInError.z ) +
                gamma( 3 ) * ( std::abs( m_[ 2 ][ 0 ] * x ) + std::abs( m_[ 2 ][ 1 ] * y ) +
                    std::abs( m_[ 2 ][ 2 ] * z ) + std::abs( m_[ 2 ][ 3 ] ) );
        }

        if ( wp == 1 )
            return Point3fi( Point3f( xp, yp, zp ), pError );
        else
            return Point3fi( Point3f( xp, yp, zp ), pError ) / wp;
        */
    }

    // Transform Inline Methods
    template <typename T>
    inline Point3<T> Transform::operator()( const Point3<T>& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        auto matrix = Transpose( m_ );

        Point3Simd result = Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;

        /*
        T xp = m_[ 0 ][ 0 ] * p.x + m_[ 0 ][ 1 ] * p.y + m_[ 0 ][ 2 ] * p.z + m_[ 0 ][ 3 ];
        T yp = m_[ 1 ][ 0 ] * p.x + m_[ 1 ][ 1 ] * p.y + m_[ 1 ][ 2 ] * p.z + m_[ 1 ][ 3 ];
        T zp = m_[ 2 ][ 0 ] * p.x + m_[ 2 ][ 1 ] * p.y + m_[ 2 ][ 2 ] * p.z + m_[ 2 ][ 3 ];
        T wp = m_[ 3 ][ 0 ] * p.x + m_[ 3 ][ 1 ] * p.y + m_[ 3 ][ 2 ] * p.z + m_[ 3 ][ 3 ];
        if ( wp == 1 )
            return Point3<T>( xp, yp, zp );
        else
            return Point3<T>( xp, yp, zp ) / wp;
        */
    }

    template <typename T>
    inline Vector3<T> Transform::operator()( const Vector3<T>& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        auto matrix = Transpose( m_ );

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( Vector3<float>::Traits::Load( v.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        return result;

        /*
        return Vector3<T>( m_[ 0 ][ 0 ] * v.x + m_[ 0 ][ 1 ] * v.y + m_[ 0 ][ 2 ] * v.z,
            m_[ 1 ][ 0 ] * v.x + m_[ 1 ][ 1 ] * v.y + m_[ 1 ][ 2 ] * v.z,
            m_[ 2 ][ 0 ] * v.x + m_[ 2 ][ 1 ] * v.y + m_[ 2 ][ 2 ] * v.z );
        */
    }

    template <typename T>
    PBRT_CPU_GPU inline Normal3<T> Transform::operator()( const Normal3<T>& n ) const
    {
        using Traits = Vector3<float>::Traits;
        auto nSimd = Traits::Load( n.values );
        auto matrix = Transpose( mInv_ );

        auto result = Traits::Dot<0b01110001>( matrix.simd[ 0 ], nSimd );
        result = Traits::Add( Traits::Dot<0b01110010>( matrix.simd[ 1 ], nSimd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( matrix.simd[ 2 ], nSimd ), result );
        return Normal3<float>::Simd( result );
        /*
        T x = n.x, y = n.y, z = n.z;
        return Normal3<T>( 
            mInv_[ 0 ][ 0 ] * x + mInv_[ 1 ][ 0 ] * y + mInv_[ 2 ][ 0 ] * z,
            mInv_[ 0 ][ 1 ] * x + mInv_[ 1 ][ 1 ] * y + mInv_[ 2 ][ 1 ] * z,
            mInv_[ 0 ][ 2 ] * x + mInv_[ 1 ][ 2 ] * y + mInv_[ 2 ][ 2 ] * z );
        */
    }

    inline Ray Transform::operator()( const Ray& r, Float* tMax ) const
    {
        Point3fi o = ( *this )( Point3fi( r.o ) );
        Vector3f d = ( *this )( r.d );
        // Offset ray origin to edge of error bounds and compute _tMax_
        if ( Float lengthSquared = ScalarLengthSquared( d ); lengthSquared > 0 )
        {
            Float dt = ScalarDot( Abs( d ), o.Error( ) ) / lengthSquared;
            o += d * dt;
            if ( tMax )
            {
                *tMax -= dt;
            }
        }

        return Ray( Point3f( o ), d, r.time, r.medium );
    }

    inline RayDifferential Transform::operator()( const RayDifferential& r, Float* tMax ) const
    {
        Ray tr = ( *this )( Ray( r ), tMax );
        RayDifferential ret( tr.o, tr.d, tr.time, tr.medium );
        ret.hasDifferentials = r.hasDifferentials;
        ret.rxOrigin = ( *this )( r.rxOrigin );
        ret.ryOrigin = ( *this )( r.ryOrigin );
        ret.rxDirection = ( *this )( r.rxDirection );
        ret.ryDirection = ( *this )( r.ryDirection );
        return ret;
    }

    inline Transform::Transform( const Frame& frame )
        : Transform( SquareMatrix<4>( 
            frame.x.x, frame.x.y, frame.x.z, 0, 
            frame.y.x, frame.y.y, frame.y.z, 0, 
            frame.z.x, frame.z.y, frame.z.z, 0, 
            0, 0, 0, 1 ) )
    {
    }

    /*
    inline Transform::Transform( const Quaternion& q )
        : mInv_( Math::Rotation( q ) )
    {
        m_ = Math::Transpose( mInv_ );
    }
    */

    
    inline Transform::Transform( const Quaternion& q )
    {
        Float xx = q.v.x * q.v.x, yy = q.v.y * q.v.y, zz = q.v.z * q.v.z;
        Float xy = q.v.x * q.v.y, xz = q.v.x * q.v.z, yz = q.v.y * q.v.z;
        Float wx = q.v.x * q.w, wy = q.v.y * q.w, wz = q.v.z * q.w;

        mInv_[ 0 ][ 0 ] = 1 - 2 * ( yy + zz );
        mInv_[ 0 ][ 1 ] = 2 * ( xy + wz );
        mInv_[ 0 ][ 2 ] = 2 * ( xz - wy );
        mInv_[ 1 ][ 0 ] = 2 * ( xy - wz );
        mInv_[ 1 ][ 1 ] = 1 - 2 * ( xx + zz );
        mInv_[ 1 ][ 2 ] = 2 * ( yz + wx );
        mInv_[ 2 ][ 0 ] = 2 * ( xz + wy );
        mInv_[ 2 ][ 1 ] = 2 * ( yz - wx );
        mInv_[ 2 ][ 2 ] = 1 - 2 * ( xx + yy );

        // Transpose since we are left-handed.  Ugh.
        m_ = Transpose( mInv_ );
    }
    

    template <typename T>
    PBRT_CPU_GPU inline Point3<T> Transform::ApplyInverse( const Point3<T>& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        auto matrix = Transpose( mInv_ );

        Point3Simd result = Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;
        /*
        T x = p.x, y = p.y, z = p.z;
        T xp = ( mInv_[ 0 ][ 0 ] * x + mInv_[ 0 ][ 1 ] * y ) + ( mInv_[ 0 ][ 2 ] * z + mInv_[ 0 ][ 3 ] );
        T yp = ( mInv_[ 1 ][ 0 ] * x + mInv_[ 1 ][ 1 ] * y ) + ( mInv_[ 1 ][ 2 ] * z + mInv_[ 1 ][ 3 ] );
        T zp = ( mInv_[ 2 ][ 0 ] * x + mInv_[ 2 ][ 1 ] * y ) + ( mInv_[ 2 ][ 2 ] * z + mInv_[ 2 ][ 3 ] );
        T wp = ( mInv_[ 3 ][ 0 ] * x + mInv_[ 3 ][ 1 ] * y ) + ( mInv_[ 3 ][ 2 ] * z + mInv_[ 3 ][ 3 ] );
        NCHECK_NE( wp, 0 );
        if ( wp == 1 )
            return Point3<T>( xp, yp, zp );
        else
            return Point3<T>( xp, yp, zp ) / wp;
        */
    }

    template <typename T>
    PBRT_CPU_GPU inline Vector3<T> Transform::ApplyInverse( Vector3<T> v ) const
    {
        T x = v.x, y = v.y, z = v.z;
        return Vector3<T>( 
            mInv_[ 0 ][ 0 ] * x + mInv_[ 0 ][ 1 ] * y + mInv_[ 0 ][ 2 ] * z,
            mInv_[ 1 ][ 0 ] * x + mInv_[ 1 ][ 1 ] * y + mInv_[ 1 ][ 2 ] * z,
            mInv_[ 2 ][ 0 ] * x + mInv_[ 2 ][ 1 ] * y + mInv_[ 2 ][ 2 ] * z );
    }

    template <typename T>
    PBRT_CPU_GPU inline Normal3<T> Transform::ApplyInverse( Normal3<T> n ) const
    {
        T x = n.x, y = n.y, z = n.z;
        return Normal3<T>( 
            m_[ 0 ][ 0 ] * x + m_[ 1 ][ 0 ] * y + m_[ 2 ][ 0 ] * z,
            m_[ 0 ][ 1 ] * x + m_[ 1 ][ 1 ] * y + m_[ 2 ][ 1 ] * z,
            m_[ 0 ][ 2 ] * x + m_[ 1 ][ 2 ] * y + m_[ 2 ][ 2 ] * z );
    }

    inline Ray Transform::ApplyInverse( const Ray& r, Float* tMax ) const
    {
        Point3fi o = ApplyInverse( Point3fi( r.o ) );
        Vector3f d = ApplyInverse( r.d );
        // Offset ray origin to edge of error bounds and compute _tMax_
        Float lengthSquared = ScalarLengthSquared( d );
        if ( lengthSquared > 0 )
        {
            Vector3f oError( o.x.Width( ) / 2, o.y.Width( ) / 2, o.z.Width( ) / 2 );
            Float dt = ScalarDot( Abs( d ), oError ) / lengthSquared;
            o += d * dt;
            if ( tMax )
                *tMax -= dt;
        }
        return Ray( Point3f( o ), d, r.time, r.medium );
    }

    inline RayDifferential Transform::ApplyInverse( const RayDifferential& r, Float* tMax ) const
    {
        Ray tr = ApplyInverse( Ray( r ), tMax );
        RayDifferential ret( tr.o, tr.d, tr.time, tr.medium );
        ret.hasDifferentials = r.hasDifferentials;
        ret.rxOrigin = ApplyInverse( r.rxOrigin );
        ret.ryOrigin = ApplyInverse( r.ryOrigin );
        ret.rxDirection = ApplyInverse( r.rxDirection );
        ret.ryDirection = ApplyInverse( r.ryDirection );
        return ret;
    }

    // AnimatedTransform Definition
    class AnimatedTransform
    {
    public:
        // AnimatedTransform Public Methods
        AnimatedTransform( ) = default;
        explicit AnimatedTransform( const Transform& t ) 
            : AnimatedTransform( t, 0, t, 1 ) 
        { }

        PBRTO_EXPORT
        AnimatedTransform( const Transform& startTransform, Float startTime, const Transform& endTransform, Float endTime );

        bool IsAnimated( ) const 
        { 
            return actuallyAnimated; 
        }

        PBRTO_EXPORT
        Ray ApplyInverse( const Ray& r, Float* tMax = nullptr ) const;

        Point3f ApplyInverse( Point3f p, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( p );
            return Interpolate( time ).ApplyInverse( p );
        }
        Vector3f ApplyInverse( Vector3f v, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( v );
            return Interpolate( time ).ApplyInverse( v );
        }
        PBRTO_EXPORT
        Normal3f operator()( Normal3f n, Float time ) const;
        Normal3f ApplyInverse( Normal3f n, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( n );
            return Interpolate( time ).ApplyInverse( n );
        }
        PBRTO_EXPORT
        Interaction operator()( const Interaction& it ) const;
        PBRTO_EXPORT
        Interaction ApplyInverse( const Interaction& it ) const;
        PBRTO_EXPORT
        SurfaceInteraction operator()( const SurfaceInteraction& it ) const;
        PBRTO_EXPORT
        SurfaceInteraction ApplyInverse( const SurfaceInteraction& it ) const;

        bool HasScale( ) const 
        { 
            return startTransform.HasScale( ) || endTransform.HasScale( ); 
        }

        std::string ToString( ) const;

        PBRTO_EXPORT
        Transform Interpolate( Float time ) const;

        PBRTO_EXPORT
        Ray operator()( const Ray& r, Float* tMax = nullptr ) const;
        PBRTO_EXPORT
        RayDifferential operator()( const RayDifferential& r, Float* tMax = nullptr ) const;

        PBRTO_EXPORT
        Point3f operator()( Point3f p, Float time ) const;
        PBRTO_EXPORT
        Vector3f operator()( Vector3f v, Float time ) const;

        PBRTO_EXPORT
        Bounds3f MotionBounds( const Bounds3f& b ) const;

        PBRTO_EXPORT
        Bounds3f BoundPointMotion( Point3f p ) const;

        // AnimatedTransform Public Members
        Transform startTransform, endTransform;
        Float startTime = 0, endTime = 1;

    private:
        // AnimatedTransform Private Methods
        PBRTO_EXPORT
        static void FindZeros( Float c1, Float c2, Float c3, Float c4, Float c5, Float theta,
                Interval tInterval, pstdo::span<Float> zeros, int* nZeros,
                int depth = 8 );

        // AnimatedTransform Private Members
        bool actuallyAnimated = false;
        Vector3f T[ 2 ];
        Quaternion R[ 2 ];
        SquareMatrix<4> S[ 2 ];
        bool hasRotation;
        struct DerivativeTerm
        {
            DerivativeTerm( ) {}
            DerivativeTerm( Float c, Float x, Float y, Float z ) : kc( c ), kx( x ), ky( y ), kz( z ) {}
            Float kc, kx, ky, kz;
            Float Eval( Point3f p ) const { return kc + kx * p.x + ky * p.y + kz * p.z; }
        };
        DerivativeTerm c1[ 3 ], c2[ 3 ], c3[ 3 ], c4[ 3 ], c5[ 3 ];
    };

}  // namespace pbrt

namespace std
{

    template <>
    struct hash<pbrto::Transform>
    {
        size_t operator()( const pbrto::Transform& t ) const
        {
            pbrto::SquareMatrix<4> m = t.GetMatrix( );
            return pbrto::Hash( m );
        }
    };

}

#endif

#endif
