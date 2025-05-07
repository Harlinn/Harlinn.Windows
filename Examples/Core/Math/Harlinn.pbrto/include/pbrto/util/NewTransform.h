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
    class alignas( SquareMatrix<4>::Traits::AlignAs ) Transform
    {
    public:
        using MatrixType = SquareMatrix<4>;
        using MatrixTraits = MatrixType::Traits;
        using MatrixSimdType = SquareMatrix<4>::Simd;

        using VectorType = Vector3f;
        using VectorSimdType = VectorType::Simd;

        using PointType = Point3f;
        using PointSimdType = PointType::Simd;

        using NormalType = Normal3f;
        using NormalSimdType = NormalType::Simd;

    private:
        // Transform Private Members
        MatrixSimdType m_; 
        MatrixSimdType mInv_;
    public:
        // Transform Public Methods
        Transform( )
            : m_( MatrixSimdType::Identity() ), mInv_( MatrixSimdType::Identity( ) )
        { }

        Transform( const MatrixType& m )
            : m_( Transpose( m ) )
        {
            Math::Vector<float, 4>::Simd determinant;
            auto inv = Math::Inverse( m_, &determinant );
            if ( determinant.x( ) != 0.f )
            {
                mInv_ = inv;
            }
            else
            {
                // Initialize _mInv_ with not-a-number values
                constexpr Float NaN = std::numeric_limits<Float>::has_signaling_NaN
                    ? std::numeric_limits<Float>::signaling_NaN( )
                    : std::numeric_limits<Float>::quiet_NaN( );

                mInv_ = MatrixType( NaN, NaN, NaN, NaN,
                    NaN, NaN, NaN, NaN,
                    NaN, NaN, NaN, NaN,
                    NaN, NaN, NaN, NaN ).ToSimd( );

            }
        }

        Transform( const Float( &mat )[ 4 ][ 4 ] )
            : Transform( SquareMatrix<4>( mat ) )
        {
        }

        Transform( const MatrixType& m, const MatrixType& mInv )
            : m_( Transpose( m ) ), mInv_( Transpose( mInv ) )
        { }

        Transform( const MatrixSimdType& m, const MatrixSimdType& mInv, bool )
            : m_( m ), mInv_( mInv )
        { }

        inline Transform( const Frame& frame )
            /*
            : Transform( SquareMatrix<4>(
                frame.x.x, frame.x.y, frame.x.z, 0,
                frame.y.x, frame.y.y, frame.y.z, 0,
                frame.z.x, frame.z.y, frame.z.z, 0,
                0, 0, 0, 1 ) )
            */
            : Transform( SquareMatrix<4>::Simd(
                frame.x.simd,
                frame.y.simd,
                frame.z.simd,
                { 0, 0, 0, 1 } ) )
        { }


        inline Transform( const Quaternion& q )
            : m_( Math::Rotation( q ) )
        {
            mInv_ = Math::Transpose( m_ );
        }

        
        

        PBRTO_EXPORT
        std::string ToString( ) const;

        

        MatrixType GetMatrix( ) const
        { 
            return Transpose( m_ ); 
        }
        MatrixType GetInverseMatrix( ) const
        { 
            return Transpose( mInv_ );
        }

        const MatrixSimdType& GetMatrixSimd( ) const
        {
            return m_;
        }
        const MatrixSimdType& GetInverseMatrixSimd( ) const
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
            Float la2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 1, 0, 0 ) ) );
            Float lb2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 0, 1, 0 ) ) );
            Float lc2 = ScalarLengthSquared( ( *this )( Vector3f::Simd( 0, 0, 1 ) ) );
            return ( Math::FastAbs( la2 - 1 ) > tolerance || Math::FastAbs( lb2 - 1 ) > tolerance || Math::FastAbs( lc2 - 1 ) > tolerance );
        }

        /*
        template <typename T>
        Point3<T> operator()( const Point3<T>& p ) const;
        */
        PointSimdType operator()( const PointSimdType& v ) const;

        /*
        template <typename T>
        inline Point3<T> ApplyInverse( const Point3<T>& p ) const;
        */

        inline PointSimdType ApplyInverse( const PointSimdType& p ) const;

        /*
        template <typename T>
        Vector3<T> operator()( const Vector3<T>& v ) const;
        */

        VectorSimdType operator()( const VectorSimdType& v ) const;

        /*
        template <typename T>
        inline Vector3<T> ApplyInverse( const Vector3<T>& v ) const;
        */

        VectorSimdType ApplyInverse( const VectorSimdType& v ) const;

        /*
        template <typename T>
        Normal3<T> operator()( const Normal3<T>& ) const;
        */

        NormalSimdType operator()( const NormalSimdType& n ) const;

        /*
        template <typename T>
        inline Normal3<T> ApplyInverse( const Normal3<T>& n ) const;
        */

        NormalSimdType ApplyInverse( const NormalSimdType& n ) const;

        Ray operator()( const Ray& r, Float* tMax = nullptr ) const;

        inline Ray ApplyInverse( const Ray& r, Float* tMax = nullptr ) const;

        RayDifferential operator()( const RayDifferential& r, Float* tMax = nullptr ) const;

        inline RayDifferential ApplyInverse( const RayDifferential& r, Float* tMax = nullptr ) const;

        PBRTO_EXPORT
        Bounds3f operator()( const Bounds3f& b ) const;

        Transform operator*( const Transform& t2 ) const
        {
            return Transform( Transpose( Transpose( m_ ) * Transpose( t2.m_ ) ),
                Transpose( Transpose( t2.mInv_ ) * Transpose( mInv_ ) ), true );
        }

        PBRTO_EXPORT
        bool SwapsHandedness( ) const;

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
    };

    // Transform Function Declarations
    PBRTO_EXPORT
    Transform Translate( const Vector3f::Simd& delta );

    PBRTO_EXPORT
    Transform Scale( Float x, Float y, Float z );

    PBRTO_EXPORT
    Transform RotateX( Float theta );
    PBRTO_EXPORT
    Transform RotateY( Float theta );
    PBRTO_EXPORT
    Transform RotateZ( Float theta );

    
    inline Transform LookAt( const Point3f::Simd& pos, const Point3f::Simd& look, const Vector3f::Simd& up )
    {
        auto cameraFromWorld = Math::LookAt( pos, look, up );
        Transform::MatrixSimdType worldFromCamera = Inverse( cameraFromWorld );
        Transform result( cameraFromWorld, worldFromCamera, true );
        return result;
    }

    PBRTO_EXPORT
    Transform Orthographic( Float znear, Float zfar );

    PBRTO_EXPORT
    Transform Perspective( Float fov, Float znear, Float zfar );

    // Transform Inline Functions
    inline Transform Inverse( const Transform& t )
    {
        return Transform( t.GetInverseMatrixSimd( ), t.GetMatrixSimd( ), true );
    }

    inline Transform Transpose( const Transform& t )
    {
        return Transform( Transpose( t.GetMatrixSimd( ) ), Transpose( t.GetInverseMatrixSimd( ) ), true );
    }

    inline Transform Rotate( Float theta, const Vector3f::Simd& axis )
    {
        auto rTheta = Math::Deg2Rad( theta );
        auto m = Math::RotationAxis( axis, rTheta );
        return Transform( m, Math::Transpose( m ), true );
    }

    inline Transform RotateRadians( Float theta, const Vector3f::Simd& axis )
    {
        auto m = Math::RotationAxis( axis, theta );
        return Transform( m, Math::Transpose( m ), true );
    }


    inline Transform RotateFromTo( const Vector3f& from, const Vector3f& to )
    {
        // Compute intermediate vector for vector reflection
        Vector3f refl;
        if ( Math::FastAbs( from.x ) < 0.72f && Math::FastAbs( to.x ) < 0.72f )
            refl = Vector3f( 1, 0, 0 );
        else if ( Math::FastAbs( from.y ) < 0.72f && Math::FastAbs( to.y ) < 0.72f )
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
        return Transform( Transpose( r ), r, true  );
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

        const auto& matrix = m_;

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

        const auto& matrix = m_;

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
    }

    // Transform Inline Methods
    /*
    template <typename T>
    inline Point3<T> Transform::operator()( const Point3<T>& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        const auto& matrix = m_;

        Point3Simd result = Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;
    }
    */

    inline Transform::PointSimdType Transform::operator()( const Transform::PointSimdType& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        const auto& matrix = m_;

        Point3Simd result = Traits::TransformPoint( p.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;
    }

    /*
    template <typename T>
    inline Vector3<T> Transform::operator()( const Vector3<T>& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        const auto& matrix = m_;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( Vector3<float>::Traits::Load( v.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        return result;
    }
    */

    inline Transform::VectorSimdType Transform::operator()( const VectorSimdType& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        const auto& matrix = m_;

        VectorSimdType result = Vector3<float>::Traits::TransformNormal( v.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        return result;
    }

    /*
    template <typename T>
    inline Normal3<T> Transform::operator()( const Normal3<T>& n ) const
    {
        using Traits = Vector3<float>::Traits;
        auto nSimd = Traits::Load( n.values );
        const auto& matrix = mInv_;

        auto result = Traits::Dot<0b01110001>( matrix.simd[ 0 ], nSimd );
        result = Traits::Add( Traits::Dot<0b01110010>( matrix.simd[ 1 ], nSimd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( matrix.simd[ 2 ], nSimd ), result );
        return Normal3<float>::Simd( result );
    }
    */

    inline Transform::NormalSimdType Transform::operator()( const NormalSimdType& n ) const
    {
        using Traits = Vector3<float>::Traits;
        
        const auto& matrix = mInv_;

        auto result = Traits::Dot<0b01110001>( matrix.simd[ 0 ], n.simd );
        result = Traits::Add( Traits::Dot<0b01110010>( matrix.simd[ 1 ], n.simd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( matrix.simd[ 2 ], n.simd ), result );
        return NormalSimdType( result );
    }


    inline Ray Transform::operator()( const Ray& r, Float* tMax ) const
    {
        Point3fi o = ( *this )( Point3fi( r.o ) );
        auto d = ( *this )( r.d );
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

        return Ray( Point3f::Simd( Point3f( o ) ), d, r.time, r.medium );
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


    /*
    template <typename T>
    inline Point3<T> Transform::ApplyInverse( const Point3<T> p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        const auto& matrix = mInv_;

        Point3Simd result = Traits::TransformPoint( Point3<float>::Traits::Load( p.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;
    }
    */

    inline Transform::PointSimdType Transform::ApplyInverse( const PointSimdType& p ) const
    {
        using Traits = SquareMatrix<4>::Traits;
        using Point3Simd = Point3<float>::Simd;

        const auto& matrix = mInv_;

        Point3Simd result = Traits::TransformPoint( p.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] );
        return result;
    }

    /*
    template <typename T>
    inline Vector3<T> Transform::ApplyInverse( const Vector3<T> v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        const auto& matrix = mInv_;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( Vector3<float>::Traits::Load( v.data( ) ), matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        return result;
    }
    */

    inline Transform::VectorSimdType Transform::ApplyInverse( const VectorSimdType& v ) const
    {
        using Traits = Vector3<float>::Traits;
        using Vector3Simd = Vector3<float>::Simd;

        const auto& matrix = mInv_;

        Vector3Simd result = Vector3<float>::Traits::TransformNormal( v.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        return result;
    }

    /*
    template <typename T>
    inline Normal3<T> Transform::ApplyInverse( const Normal3<T> n ) const
    {
        using Traits = Vector3<float>::Traits;
        auto nSimd = Traits::Load( n.values );
        const auto& matrix = m_;

        auto result = Traits::Dot<0b01110001>( matrix.simd[ 0 ], nSimd );
        result = Traits::Add( Traits::Dot<0b01110010>( matrix.simd[ 1 ], nSimd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( matrix.simd[ 2 ], nSimd ), result );
        return Normal3<float>::Simd( result );
    }
    */

    inline Transform::NormalSimdType Transform::ApplyInverse( const NormalSimdType& n ) const
    {
        using Traits = Vector3<float>::Traits;
        const auto& matrix = m_;

        auto result = Traits::Dot<0b01110001>( matrix.simd[ 0 ], n.simd );
        result = Traits::Add( Traits::Dot<0b01110010>( matrix.simd[ 1 ], n.simd ), result );
        result = Traits::Add( Traits::Dot<0b01110100>( matrix.simd[ 2 ], n.simd ), result );
        return Normal3<float>::Simd( result );
    }


    inline Ray Transform::ApplyInverse( const Ray& r, Float* tMax ) const
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
        return Ray( Point3f::Simd( Point3f( o ) ), d, r.time, r.medium );
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

        /*
        Point3f ApplyInverse( Point3f p, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( p );
            return Interpolate( time ).ApplyInverse( p );
        }
        */
        Point3f::Simd ApplyInverse( const Point3f::Simd& p, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( p );
            return Interpolate( time ).ApplyInverse( p );
        }

        /*
        Vector3f ApplyInverse( Vector3f v, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( v );
            return Interpolate( time ).ApplyInverse( v );
        }
        */

        Vector3f::Simd ApplyInverse( const Vector3f::Simd& v, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( v );
            return Interpolate( time ).ApplyInverse( v );
        }

        /*
        PBRTO_EXPORT
        Normal3f operator()( Normal3f n, Float time ) const;
        */
        PBRTO_EXPORT
        Normal3f::Simd operator()( const Normal3f::Simd& n, Float time ) const;
        
        /*
        Normal3f ApplyInverse( Normal3f n, Float time ) const
        {
            if ( !actuallyAnimated )
                return startTransform.ApplyInverse( n );
            return Interpolate( time ).ApplyInverse( n );
        }
        */
        Normal3f::Simd ApplyInverse( const Normal3f::Simd& n, Float time ) const
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

        /*
        PBRTO_EXPORT
        Point3f operator()( Point3f p, Float time ) const;
        */

        PBRTO_EXPORT
        Point3f::Simd operator()( const Point3f::Simd& p, Float time ) const;
        /*
        PBRTO_EXPORT
        Vector3f operator()( Vector3f v, Float time ) const;
        */
        PBRTO_EXPORT
        Vector3f::Simd operator()( const Vector3f::Simd& v, Float time ) const;

        PBRTO_EXPORT
        Bounds3f MotionBounds( const Bounds3f& b ) const;

        PBRTO_EXPORT
        Bounds3f BoundPointMotion( const Point3f::Simd& p ) const;

        // AnimatedTransform Public Members
        Transform startTransform, endTransform;
        Float startTime = 0, endTime = 1;

    private:
        // AnimatedTransform Private Methods
        PBRTO_EXPORT
        static void FindZeros( Float c1, Float c2, Float c3, Float c4, Float c5, Float theta, Interval tInterval, pstdo::span<Float> zeros, int* nZeros, int depth = 8 );

        // AnimatedTransform Private Members
        bool actuallyAnimated = false;
        Vector3f T[ 2 ];
        Quaternion R[ 2 ];
        SquareMatrix<4> S[ 2 ];
        bool hasRotation;
        struct DerivativeTerm
        {
            Float kc, kx, ky, kz;

            DerivativeTerm( ) 
            { }
            DerivativeTerm( Float c, Float x, Float y, Float z ) 
                : kc( c ), kx( x ), ky( y ), kz( z ) 
            { }
            
            Float Eval( Point3f p ) const 
            { 
                return kc + kx * p.x + ky * p.y + kz * p.z; 
            }
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

}


#endif
