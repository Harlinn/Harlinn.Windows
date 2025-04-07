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

#endif
