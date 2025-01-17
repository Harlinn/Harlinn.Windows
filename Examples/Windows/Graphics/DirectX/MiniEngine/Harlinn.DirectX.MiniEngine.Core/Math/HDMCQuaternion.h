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
#ifdef USE_HCC_MATH
        class Quaternion
        {
        public:
            using Simd = Harlinn::Common::Core::Math::Quaternion<float>::Simd;
            using Traits = typename Simd::Traits;
        protected:
            Simd m_vec;
        public:
            INLINE Quaternion( ) 
                : m_vec( Traits::Set(1.f, 0.f, 0.f, 0.f ) )
            { }
            INLINE Quaternion( const Vector3& axis, const Scalar& angle ) 
                : m_vec( Simd::FromAxisAndAngle( axis.ToSimd(), angle ) )
            { }
            INLINE Quaternion( float pitch, float yaw, float roll ) 
                : m_vec( pitch, yaw, roll )
            { }
            
            INLINE explicit Quaternion( const SquareMatrix<float,4>::Simd& matrix )
                : m_vec( Simd::FromMatrix( matrix ) )
            { }
            INLINE explicit Quaternion( FXMVECTOR vec ) 
                : m_vec( vec )
            { }
            INLINE explicit Quaternion( const Simd& vec )
                : m_vec( vec )
            { }
            INLINE explicit Quaternion( EIdentityTag ) 
                : m_vec( Simd::Identity( ) )
            {}

            INLINE operator const Simd&( ) const { return m_vec; }

            INLINE const Simd& ToSimd( ) const { return m_vec; }

            INLINE Quaternion operator~ ( void ) const 
            { 
                return Quaternion( Conjugate( m_vec ) );
            }
            INLINE Quaternion operator- ( void ) const 
            { 
                return Quaternion( -m_vec ); 
            }

            INLINE Quaternion operator* ( Quaternion rhs ) const 
            { 
                return Quaternion( rhs.ToSimd() * m_vec ); 
            }
            INLINE Vector3 operator* ( Vector3 rhs ) const 
            { 
                return Vector3( Rotate( rhs.ToSimd(), m_vec ) );
            }

            INLINE Quaternion& operator= ( Quaternion rhs ) 
            { 
                m_vec = rhs.m_vec;
                return *this; 
            }
            INLINE Quaternion& operator*= ( Quaternion rhs ) 
            { 
                m_vec = m_vec * rhs.m_vec;
                return *this; 
            }

            INLINE Quaternion Normalize( ) const
            {
                namespace m = Harlinn::Common::Core::Math;
                Quaternion( m::Normalize( m_vec ) );
            }

            static Quaternion Slerp( Quaternion a, Quaternion b, float t )
            {
                namespace m = Harlinn::Common::Core::Math;
                return Quaternion( m::Normalize( m::Slerp( a.m_vec, b.m_vec, t ) ) );
            }

            static Quaternion Lerp( Quaternion a, Quaternion b, float t )
            {
                namespace m = Harlinn::Common::Core::Math;
                using VectorSimd = m::Vector<float, 3>::Simd;
                VectorSimd av( a.m_vec.simd );
                VectorSimd bv( b.m_vec.simd );
                auto result = m::Lerp(av, bv, t );
                return Quaternion( result.simd ).Normalize( );
            }
        
        };

        INLINE Quaternion Normalize( const Quaternion& q ) 
        { 
            return q.Normalize( );;
        }
        INLINE Quaternion Slerp( Quaternion a, Quaternion b, float t ) 
        { 
            return Quaternion::Slerp( a, b, t  ); 
        }
        INLINE Quaternion Lerp( Quaternion a, Quaternion b, float t )
        {
            return Quaternion::Lerp( a, b, t );
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
    }
}