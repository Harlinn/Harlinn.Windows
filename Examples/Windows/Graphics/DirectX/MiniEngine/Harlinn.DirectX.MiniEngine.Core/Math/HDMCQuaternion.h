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

#include "HDMCVector.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
#ifdef HDMC_USES_HCC_MATH
        using Quaternion = m::Quaternion<float>::Simd;

        INLINE Quaternion Lerp( Quaternion a, Quaternion b, float t )
        {
            Vector4 av( a.simd );
            Vector4 bv( b.simd );
            auto result = m::Lerp(av, bv, t );
            return m::Normalize( Quaternion( result.simd ) );
        }

        INLINE Quaternion Normalize( const Quaternion& q ) 
        { 
            return m::Normalize( q );
        }
        INLINE Quaternion Slerp( Quaternion a, Quaternion b, float t ) 
        { 
            return m::Slerp( a, b, t  ); 
        }

        INLINE Vector3 operator* ( const Quaternion& q, const Vector3& rhs )
        { 
            return m::Rotate( rhs, q );
        }

        INLINE Quaternion operator~ ( const Quaternion& q ) 
        { 
            return m::Conjugate( q );
        }

#else
        class Quaternion
        {
        public:
            INLINE Quaternion( ) { m_vec = ::DirectX::XMQuaternionIdentity( ); }
            INLINE Quaternion( const Vector3& axis, const Scalar& angle ) { m_vec = ::DirectX::XMQuaternionRotationAxis( axis, angle ); }
            INLINE Quaternion( float pitch, float yaw, float roll ) { m_vec = ::DirectX::XMQuaternionRotationRollPitchYaw( pitch, yaw, roll ); }
            INLINE explicit Quaternion( const XMMATRIX& matrix ) { m_vec = XMQuaternionRotationMatrix( matrix ); }
            INLINE explicit Quaternion( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Quaternion( EIdentityTag ) { m_vec = ::DirectX::XMQuaternionIdentity( ); }

            INLINE operator XMVECTOR( ) const { return m_vec; }

            INLINE Quaternion operator~ ( void ) const { return Quaternion( ::DirectX::XMQuaternionConjugate( m_vec ) ); }
            INLINE Quaternion operator- ( void ) const { return Quaternion( ::DirectX::XMVectorNegate( m_vec ) ); }

            INLINE Quaternion operator* ( Quaternion rhs ) const { return Quaternion( ::DirectX::XMQuaternionMultiply( rhs, m_vec ) ); }
            INLINE Vector3 operator* ( Vector3 rhs ) const { return Vector3( ::DirectX::XMVector3Rotate( rhs, m_vec ) ); }

            INLINE Quaternion& operator= ( Quaternion rhs ) { m_vec = rhs; return *this; }
            INLINE Quaternion& operator*= ( Quaternion rhs ) { *this = *this * rhs; return *this; }

        protected:
            XMVECTOR m_vec;
        };

        INLINE Quaternion Normalize( Quaternion q ) { return Quaternion( ::DirectX::XMQuaternionNormalize( q ) ); }
        INLINE Quaternion Slerp( Quaternion a, Quaternion b, float t ) { return Normalize( Quaternion( ::DirectX::XMQuaternionSlerp( a, b, t ) ) ); }
        INLINE Quaternion Lerp( Quaternion a, Quaternion b, float t ) { return Normalize( Quaternion( ::DirectX::XMVectorLerp( a, b, t ) ) ); }
#endif
        inline std::string ToString( const Quaternion& q )
        {
#ifdef HDMC_USES_HCC_MATH
            m::Vector<float, 4> vec( Vector4( q.simd ) );
#else
            ::DirectX::XMFLOAT4A vec;
            ::DirectX::XMStoreFloat4A( &vec, q );
#endif
            return std::format( "[ {}, {}, {}, {} ]", vec.x, vec.y, vec.z, vec.w );

        }

        inline void Dump( const char* name, const Quaternion& q, const char* file, int line, const char* function )
        {
#ifdef HDMC_USES_HCC_MATH
            m::Quaternion<float> vec( q );
#else
            ::DirectX::XMFLOAT4A vec;
            ::DirectX::XMStoreFloat4A( &vec, q );
#endif

            PrintLn( "// {}:", name );
#ifdef HDMC_USES_HCC_MATH
            PrintLn( "// [ {}, {}, {}, {} ]", vec.v.x, vec.v.y, vec.v.z, vec.w );
#else
            PrintLn( "// [ {}, {}, {}, {} ]", vec.x, vec.y, vec.z, vec.w );
#endif
            PrintLn( "// Function: {} ", function );
            PrintLn( "// Position: {}({})", file, line );
#ifdef HDMC_USES_HCC_MATH
            PrintLn( "Quaternion<float> {}( {}, {}, {}, {} );", name, vec.v.x, vec.v.y, vec.v.z, vec.w );
#else
            PrintLn( "Quaternion<float> {}( {}, {}, {}, {} );", name, vec.x, vec.y, vec.z, vec.w );
#endif
        }
    }
}