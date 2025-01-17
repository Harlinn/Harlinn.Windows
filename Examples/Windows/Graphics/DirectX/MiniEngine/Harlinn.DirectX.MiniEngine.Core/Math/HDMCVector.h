//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCScalar.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
        

        // A 3-vector with an unspecified fourth component.  Depending on the context, the W can be 0 or 1, but both are implicit.
        // The actual value of the fourth component is undefined for performance reasons.
#ifdef USE_HCC_MATH
        class Vector4;
        class Vector3
        {
        public:
            using Simd = Vector3f::Simd;
            using Traits = typename Simd::Traits;
            
        protected:
            Simd m_vec;
        public:

            INLINE Vector3( ) {}
            INLINE Vector3( float x, float y, float z )
                : m_vec( x, y, z, z )
            { }
            INLINE Vector3( const XMFLOAT3& v ) { m_vec = XMLoadFloat3( &v ); }
            INLINE Vector3( const Vector3& v ) { m_vec = v; }
            INLINE Vector3( Scalar s ) { m_vec = s.ToSimd(); }
            INLINE explicit Vector3( Vector4 vec );
            INLINE explicit Vector3( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Vector3( const Simd& vec )
                : m_vec( vec )
            { }
            INLINE explicit Vector3( EZeroTag ) { m_vec = SplatZero( ); }
            INLINE explicit Vector3( EIdentityTag ) { m_vec = SplatOne( ); }
            INLINE explicit Vector3( EXUnitVector ) { m_vec = CreateXUnitVector( ); }
            INLINE explicit Vector3( EYUnitVector ) { m_vec = CreateYUnitVector( ); }
            INLINE explicit Vector3( EZUnitVector ) { m_vec = CreateZUnitVector( ); }

            INLINE operator Simd( ) const { return m_vec; }

            INLINE Simd ToSimd( ) const { return m_vec; }

            INLINE Scalar GetX( ) const { return Scalar( m_vec.X( ).simd ); }
            INLINE Scalar GetY( ) const { return Scalar( m_vec.Y( ).simd ); }
            INLINE Scalar GetZ( ) const { return Scalar( m_vec.Z( ).simd ); }
            INLINE void SetX( Scalar x ) { m_vec.SetX( x.ToSimd() ); }
            INLINE void SetY( Scalar y ) { m_vec.SetY( y.ToSimd() ); }
            INLINE void SetZ( Scalar z ) { m_vec.SetZ( z.ToSimd() ); }

            INLINE Vector3 operator- ( ) const { return Vector3( -m_vec ); }
            INLINE Vector3 operator+ ( Vector3 v2 ) const { return Vector3( m_vec + v2.m_vec ); }
            INLINE Vector3 operator- ( Vector3 v2 ) const { return Vector3( m_vec - v2.m_vec ); }
            INLINE Vector3 operator* ( Vector3 v2 ) const { return Vector3( m_vec * v2.m_vec ); }
            INLINE Vector3 operator/ ( Vector3 v2 ) const { return Vector3( m_vec / v2.m_vec ); }
            INLINE Vector3 operator* ( Scalar  v2 ) const { return *this * Vector3( v2 ); }
            INLINE Vector3 operator/ ( Scalar  v2 ) const { return *this / Vector3( v2 ); }
            INLINE Vector3 operator* ( float  v2 ) const { return *this * Scalar( v2 ); }
            INLINE Vector3 operator/ ( float  v2 ) const { return *this / Scalar( v2 ); }

            INLINE Vector3& operator += ( Vector3 v ) { m_vec += v; return *this; }
            INLINE Vector3& operator -= ( Vector3 v ) { m_vec -= v; return *this; }
            INLINE Vector3& operator *= ( Vector3 v ) { m_vec *= v; return *this; }
            INLINE Vector3& operator /= ( Vector3 v ) { m_vec /= v; return *this; }

            INLINE friend Vector3 operator* ( Scalar  v1, Vector3 v2 ) { return Vector3( v1 ) * v2; }
            INLINE friend Vector3 operator/ ( Scalar  v1, Vector3 v2 ) { return Vector3( v1 ) / v2; }
            INLINE friend Vector3 operator* ( float   v1, Vector3 v2 ) { return Scalar( v1 ) * v2; }
            INLINE friend Vector3 operator/ ( float   v1, Vector3 v2 ) { return Scalar( v1 ) / v2; }

        
        };

        // A 4-vector, completely defined.
        class Vector4
        {
        public:
            using Simd = Harlinn::Common::Core::Math::Vector<float,4>::Simd;
            using Traits = typename Simd::Traits;
        protected:
            Simd m_vec;
        public:
            INLINE Vector4( ) {}
            INLINE Vector4( float x, float y, float z, float w ) 
                : m_vec( x, y, z, w )
            { }
            INLINE Vector4( const XMFLOAT4& v ) { m_vec = XMLoadFloat4( &v ); }
            INLINE Vector4( Vector3 xyz, float w ) { m_vec = ::DirectX::XMVectorSetW( xyz.ToSimd().simd, w ); }
            INLINE Vector4( const Vector4& v ) { m_vec = v.m_vec; }
            INLINE Vector4( const Simd& v )
                : m_vec( v )
            { }
            INLINE Vector4( const Scalar& s ) { m_vec = s.ToSimd(); }
            INLINE explicit Vector4( Vector3 xyz ) { m_vec = SetWToOne( xyz.ToSimd().simd ); }
            INLINE explicit Vector4( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Vector4( EZeroTag ) { m_vec = SplatZero( ); }
            INLINE explicit Vector4( EIdentityTag ) { m_vec = SplatOne( ); }
            INLINE explicit Vector4( EXUnitVector ) { m_vec = CreateXUnitVector( ); }
            INLINE explicit Vector4( EYUnitVector ) { m_vec = CreateYUnitVector( ); }
            INLINE explicit Vector4( EZUnitVector ) { m_vec = CreateZUnitVector( ); }
            INLINE explicit Vector4( EWUnitVector ) { m_vec = CreateWUnitVector( ); }

            INLINE operator Simd( ) const { return m_vec; }

            INLINE Simd ToSimd( ) const { return m_vec; }

            INLINE Scalar GetX( ) const { return Scalar( m_vec.X( ).simd ); }
            INLINE Scalar GetY( ) const { return Scalar( m_vec.Y( ).simd ); }
            INLINE Scalar GetZ( ) const { return Scalar( m_vec.Z( ).simd ); }
            INLINE Scalar GetW( ) const { return Scalar( m_vec.W( ).simd ); }
            INLINE void SetX( Scalar x ) { m_vec.SetX( x.ToSimd( ) ); }
            INLINE void SetY( Scalar y ) { m_vec.SetY( y.ToSimd( ) ); }
            INLINE void SetZ( Scalar z ) { m_vec.SetZ( z.ToSimd( ) ); }
            INLINE void SetW( Scalar w ) { m_vec.SetW( w.ToSimd( ) ); }
            INLINE void SetXYZ( Vector3 xyz ) { m_vec.SetXYZ( xyz.ToSimd().simd ); }

            INLINE Vector4 operator- ( ) const { return Vector4( -m_vec ); }
            INLINE Vector4 operator+ ( Vector4 v2 ) const { return Vector4( m_vec + v2.m_vec ); }
            INLINE Vector4 operator- ( Vector4 v2 ) const { return Vector4( m_vec - v2.m_vec ); }
            INLINE Vector4 operator* ( Vector4 v2 ) const { return Vector4( m_vec * v2.m_vec ); }
            INLINE Vector4 operator/ ( Vector4 v2 ) const { return Vector4( m_vec / v2.m_vec ); }
            INLINE Vector4 operator* ( Scalar  v2 ) const { return *this * Vector4( v2 ); }
            INLINE Vector4 operator/ ( Scalar  v2 ) const { return *this / Vector4( v2 ); }
            INLINE Vector4 operator* ( float   v2 ) const { return *this * Scalar( v2 ); }
            INLINE Vector4 operator/ ( float   v2 ) const { return *this / Scalar( v2 ); }

            INLINE void operator*= ( float   v2 ) { *this = *this * Scalar( v2 ); }
            INLINE void operator/= ( float   v2 ) { *this = *this / Scalar( v2 ); }

            INLINE friend Vector4 operator* ( Scalar  v1, Vector4 v2 ) { return Vector4( v1 ) * v2; }
            INLINE friend Vector4 operator/ ( Scalar  v1, Vector4 v2 ) { return Vector4( v1 ) / v2; }
            INLINE friend Vector4 operator* ( float   v1, Vector4 v2 ) { return Scalar( v1 ) * v2; }
            INLINE friend Vector4 operator/ ( float   v1, Vector4 v2 ) { return Scalar( v1 ) / v2; }

        
        };

        // Defined after Vector4 methods are declared
        INLINE Vector3::Vector3( Vector4 vec ) 
            : m_vec( vec.ToSimd( ).simd )
        {
        }

        // For W != 1, divide XYZ by W.  If W == 0, do nothing
        INLINE Vector3 MakeHomogeneous( Vector4 v )
        {
            using Traits = Vector4::Traits;
            Scalar W = v.GetW( );
            return Vector3( Traits::Select( Traits::Div( v.ToSimd().simd, W.ToSimd() ), v.ToSimd( ).simd, Traits::Equal( W.ToSimd( ), SplatZero( ) ) ) );
        }

        class BoolVector
        {
        public:
            INLINE BoolVector( FXMVECTOR vec ) { m_vec = vec; }
            INLINE operator XMVECTOR( ) const { return m_vec; }
        protected:
            XMVECTOR m_vec;
        };
#else
        class Vector4;
        class Vector3
        {
        public:

            INLINE Vector3( ) {}
            INLINE Vector3( float x, float y, float z ) { m_vec = ::DirectX::XMVectorSet( x, y, z, z ); }
            INLINE Vector3( const XMFLOAT3& v ) { m_vec = XMLoadFloat3( &v ); }
            INLINE Vector3( const Vector3& v ) { m_vec = v; }
            INLINE Vector3( Scalar s ) { m_vec = s; }
            INLINE explicit Vector3( Vector4 vec );
            INLINE explicit Vector3( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Vector3( EZeroTag ) { m_vec = SplatZero( ); }
            INLINE explicit Vector3( EIdentityTag ) { m_vec = SplatOne( ); }
            INLINE explicit Vector3( EXUnitVector ) { m_vec = CreateXUnitVector( ); }
            INLINE explicit Vector3( EYUnitVector ) { m_vec = CreateYUnitVector( ); }
            INLINE explicit Vector3( EZUnitVector ) { m_vec = CreateZUnitVector( ); }

            INLINE operator XMVECTOR( ) const { return m_vec; }

            INLINE Scalar GetX( ) const { return Scalar( ::DirectX::XMVectorSplatX( m_vec ) ); }
            INLINE Scalar GetY( ) const { return Scalar( ::DirectX::XMVectorSplatY( m_vec ) ); }
            INLINE Scalar GetZ( ) const { return Scalar( ::DirectX::XMVectorSplatZ( m_vec ) ); }
            INLINE void SetX( Scalar x ) { m_vec = ::DirectX::XMVectorPermute<4, 1, 2, 3>( m_vec, x ); }
            INLINE void SetY( Scalar y ) { m_vec = ::DirectX::XMVectorPermute<0, 5, 2, 3>( m_vec, y ); }
            INLINE void SetZ( Scalar z ) { m_vec = ::DirectX::XMVectorPermute<0, 1, 6, 3>( m_vec, z ); }

            INLINE Vector3 operator- ( ) const { return Vector3( ::DirectX::XMVectorNegate( m_vec ) ); }
            INLINE Vector3 operator+ ( Vector3 v2 ) const { return Vector3( ::DirectX::XMVectorAdd( m_vec, v2 ) ); }
            INLINE Vector3 operator- ( Vector3 v2 ) const { return Vector3( ::DirectX::XMVectorSubtract( m_vec, v2 ) ); }
            INLINE Vector3 operator* ( Vector3 v2 ) const { return Vector3( ::DirectX::XMVectorMultiply( m_vec, v2 ) ); }
            INLINE Vector3 operator/ ( Vector3 v2 ) const { return Vector3( ::DirectX::XMVectorDivide( m_vec, v2 ) ); }
            INLINE Vector3 operator* ( Scalar  v2 ) const { return *this * Vector3( v2 ); }
            INLINE Vector3 operator/ ( Scalar  v2 ) const { return *this / Vector3( v2 ); }
            INLINE Vector3 operator* ( float  v2 ) const { return *this * Scalar( v2 ); }
            INLINE Vector3 operator/ ( float  v2 ) const { return *this / Scalar( v2 ); }

            INLINE Vector3& operator += ( Vector3 v ) { *this = *this + v; return *this; }
            INLINE Vector3& operator -= ( Vector3 v ) { *this = *this - v; return *this; }
            INLINE Vector3& operator *= ( Vector3 v ) { *this = *this * v; return *this; }
            INLINE Vector3& operator /= ( Vector3 v ) { *this = *this / v; return *this; }

            INLINE friend Vector3 operator* ( Scalar  v1, Vector3 v2 ) { return Vector3( v1 ) * v2; }
            INLINE friend Vector3 operator/ ( Scalar  v1, Vector3 v2 ) { return Vector3( v1 ) / v2; }
            INLINE friend Vector3 operator* ( float   v1, Vector3 v2 ) { return Scalar( v1 ) * v2; }
            INLINE friend Vector3 operator/ ( float   v1, Vector3 v2 ) { return Scalar( v1 ) / v2; }

        protected:
            XMVECTOR m_vec;
        };

        // A 4-vector, completely defined.
        class Vector4
        {
        public:
            INLINE Vector4( ) {}
            INLINE Vector4( float x, float y, float z, float w ) { m_vec = ::DirectX::XMVectorSet( x, y, z, w ); }
            INLINE Vector4( const XMFLOAT4& v ) { m_vec = XMLoadFloat4( &v ); }
            INLINE Vector4( Vector3 xyz, float w ) { m_vec = ::DirectX::XMVectorSetW( xyz, w ); }
            INLINE Vector4( const Vector4& v ) { m_vec = v; }
            INLINE Vector4( const Scalar& s ) { m_vec = s; }
            INLINE explicit Vector4( Vector3 xyz ) { m_vec = SetWToOne( xyz ); }
            INLINE explicit Vector4( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Vector4( EZeroTag ) { m_vec = SplatZero( ); }
            INLINE explicit Vector4( EIdentityTag ) { m_vec = SplatOne( ); }
            INLINE explicit Vector4( EXUnitVector ) { m_vec = CreateXUnitVector( ); }
            INLINE explicit Vector4( EYUnitVector ) { m_vec = CreateYUnitVector( ); }
            INLINE explicit Vector4( EZUnitVector ) { m_vec = CreateZUnitVector( ); }
            INLINE explicit Vector4( EWUnitVector ) { m_vec = CreateWUnitVector( ); }

            INLINE operator XMVECTOR( ) const { return m_vec; }

            INLINE Scalar GetX( ) const { return Scalar( ::DirectX::XMVectorSplatX( m_vec ) ); }
            INLINE Scalar GetY( ) const { return Scalar( ::DirectX::XMVectorSplatY( m_vec ) ); }
            INLINE Scalar GetZ( ) const { return Scalar( ::DirectX::XMVectorSplatZ( m_vec ) ); }
            INLINE Scalar GetW( ) const { return Scalar( ::DirectX::XMVectorSplatW( m_vec ) ); }
            INLINE void SetX( Scalar x ) { m_vec = ::DirectX::XMVectorPermute<4, 1, 2, 3>( m_vec, x ); }
            INLINE void SetY( Scalar y ) { m_vec = ::DirectX::XMVectorPermute<0, 5, 2, 3>( m_vec, y ); }
            INLINE void SetZ( Scalar z ) { m_vec = ::DirectX::XMVectorPermute<0, 1, 6, 3>( m_vec, z ); }
            INLINE void SetW( Scalar w ) { m_vec = ::DirectX::XMVectorPermute<0, 1, 2, 7>( m_vec, w ); }
            INLINE void SetXYZ( Vector3 xyz ) { m_vec = ::DirectX::XMVectorPermute<0, 1, 2, 7>( xyz, m_vec ); }

            INLINE Vector4 operator- ( ) const { return Vector4( ::DirectX::XMVectorNegate( m_vec ) ); }
            INLINE Vector4 operator+ ( Vector4 v2 ) const { return Vector4( ::DirectX::XMVectorAdd( m_vec, v2 ) ); }
            INLINE Vector4 operator- ( Vector4 v2 ) const { return Vector4( ::DirectX::XMVectorSubtract( m_vec, v2 ) ); }
            INLINE Vector4 operator* ( Vector4 v2 ) const { return Vector4( ::DirectX::XMVectorMultiply( m_vec, v2 ) ); }
            INLINE Vector4 operator/ ( Vector4 v2 ) const { return Vector4( ::DirectX::XMVectorDivide( m_vec, v2 ) ); }
            INLINE Vector4 operator* ( Scalar  v2 ) const { return *this * Vector4( v2 ); }
            INLINE Vector4 operator/ ( Scalar  v2 ) const { return *this / Vector4( v2 ); }
            INLINE Vector4 operator* ( float   v2 ) const { return *this * Scalar( v2 ); }
            INLINE Vector4 operator/ ( float   v2 ) const { return *this / Scalar( v2 ); }

            INLINE void operator*= ( float   v2 ) { *this = *this * Scalar( v2 ); }
            INLINE void operator/= ( float   v2 ) { *this = *this / Scalar( v2 ); }

            INLINE friend Vector4 operator* ( Scalar  v1, Vector4 v2 ) { return Vector4( v1 ) * v2; }
            INLINE friend Vector4 operator/ ( Scalar  v1, Vector4 v2 ) { return Vector4( v1 ) / v2; }
            INLINE friend Vector4 operator* ( float   v1, Vector4 v2 ) { return Scalar( v1 ) * v2; }
            INLINE friend Vector4 operator/ ( float   v1, Vector4 v2 ) { return Scalar( v1 ) / v2; }

        protected:
            XMVECTOR m_vec;
        };

        // Defined after Vector4 methods are declared
        INLINE Vector3::Vector3( Vector4 vec ) : m_vec( ( XMVECTOR )vec )
        {
        }

        // For W != 1, divide XYZ by W.  If W == 0, do nothing
        INLINE Vector3 MakeHomogeneous( Vector4 v )
        {
            Scalar W = v.GetW( );
            return Vector3( ::DirectX::XMVectorSelect( ::DirectX::XMVectorDivide( v, W ), v, ::DirectX::XMVectorEqual( W, SplatZero( ) ) ) );
        }

        class BoolVector
        {
        public:
            INLINE BoolVector( FXMVECTOR vec ) { m_vec = vec; }
            INLINE operator XMVECTOR( ) const { return m_vec; }
        protected:
            XMVECTOR m_vec;
        };
#endif
    } // namespace Math

}