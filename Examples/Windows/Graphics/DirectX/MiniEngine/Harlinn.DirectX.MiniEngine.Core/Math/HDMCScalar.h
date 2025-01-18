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

#include "HDMCCommon.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
#ifdef HDMC_USES_HCC_MATH
        class Scalar
        {
        public:
            using Traits = m::Traits;
            using SIMDType = m::SIMDType;
        private:
            SIMDType m_vec{};
        public:
            INLINE Scalar( ) {}
            INLINE Scalar( const Scalar& s ) 
            { 
                m_vec = s.m_vec; 
            }
            INLINE Scalar( float f ) 
            { 
                m_vec = Traits::Fill( f );
            }
            INLINE explicit Scalar( SIMDType vec ) 
            { 
                m_vec = vec; 
            }
            INLINE explicit Scalar( EZeroTag ) 
            { 
                m_vec = Traits::Zero( );
            }
            INLINE explicit Scalar( EIdentityTag ) 
            { 
                m_vec = Traits::Fill( 1.f );
            }

            SIMDType ToSimd( ) const
            {
                return m_vec;
            }

            INLINE float Value( ) const
            {
                return Traits::First( m_vec );
            }

            INLINE operator SIMDType( ) const 
            { 
                return m_vec; 
            }
            INLINE operator float( ) const 
            { 
                return Traits::First( m_vec );
            }

            friend INLINE Scalar operator- ( const Scalar& s )
            {
                using Traits = Scalar::Traits;
                return Scalar( Traits::Negate( s.m_vec ) );
            }
            friend INLINE Scalar operator+ ( const Scalar& s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( Traits::Add( s1.m_vec, s2.m_vec ) );
            }
            friend INLINE Scalar operator- ( const Scalar& s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( Traits::Sub( s1.m_vec, s2.m_vec ) );
            }
            friend INLINE Scalar operator* ( const Scalar& s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( Traits::Mul( s1.m_vec, s2.m_vec ) );
            }
            friend INLINE Scalar operator/ ( const Scalar& s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( Traits::Div( s1.m_vec, s2.m_vec ) );
            }
            friend INLINE Scalar operator+ ( const Scalar& s1, float s2 )
            {
                using Traits = Scalar::Traits;
                return s1 + Scalar( s2 );
            }
            friend INLINE Scalar operator- ( const Scalar& s1, float s2 )
            {
                using Traits = Scalar::Traits;
                return s1 - Scalar( s2 );
            }
            friend INLINE Scalar operator* ( const Scalar& s1, float s2 )
            {
                using Traits = Scalar::Traits;
                return s1 * Scalar( s2 );
            }
            friend INLINE Scalar operator/ ( const Scalar& s1, float s2 )
            {
                using Traits = Scalar::Traits;
                return s1 / Scalar( s2 );
            }
            friend INLINE Scalar operator+ ( float s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( s1 ) + s2;
            }
            friend INLINE Scalar operator- ( float s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( s1 ) - s2;
            }
            friend INLINE Scalar operator* ( float s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( s1 ) * s2;
            }
            friend INLINE Scalar operator/ ( float s1, const Scalar& s2 )
            {
                using Traits = Scalar::Traits;
                return Scalar( s1 ) / s2;
            }
            
        };

        
#else
        class Scalar
        {
        public:
            INLINE Scalar( ) {}
            INLINE Scalar( const Scalar& s ) { m_vec = s; }
            INLINE Scalar( float f ) { m_vec = ::DirectX::XMVectorReplicate( f ); }
            INLINE explicit Scalar( FXMVECTOR vec ) { m_vec = vec; }
            INLINE explicit Scalar( EZeroTag ) { m_vec = SplatZero( ); }
            INLINE explicit Scalar( EIdentityTag ) { m_vec = SplatOne( ); }

            INLINE operator XMVECTOR( ) const { return m_vec; }
            INLINE operator float( ) const { return ::DirectX::XMVectorGetX( m_vec ); }

        private:
            XMVECTOR m_vec;
        };

        INLINE Scalar operator- ( Scalar s ) { return Scalar( ::DirectX::XMVectorNegate( s ) ); }
        INLINE Scalar operator+ ( Scalar s1, Scalar s2 ) { return Scalar( ::DirectX::XMVectorAdd( s1, s2 ) ); }
        INLINE Scalar operator- ( Scalar s1, Scalar s2 ) { return Scalar( ::DirectX::XMVectorSubtract( s1, s2 ) ); }
        INLINE Scalar operator* ( Scalar s1, Scalar s2 ) { return Scalar( ::DirectX::XMVectorMultiply( s1, s2 ) ); }
        INLINE Scalar operator/ ( Scalar s1, Scalar s2 ) { return Scalar( ::DirectX::XMVectorDivide( s1, s2 ) ); }
        INLINE Scalar operator+ ( Scalar s1, float s2 ) { return s1 + Scalar( s2 ); }
        INLINE Scalar operator- ( Scalar s1, float s2 ) { return s1 - Scalar( s2 ); }
        INLINE Scalar operator* ( Scalar s1, float s2 ) { return s1 * Scalar( s2 ); }
        INLINE Scalar operator/ ( Scalar s1, float s2 ) { return s1 / Scalar( s2 ); }
        INLINE Scalar operator+ ( float s1, Scalar s2 ) { return Scalar( s1 ) + s2; }
        INLINE Scalar operator- ( float s1, Scalar s2 ) { return Scalar( s1 ) - s2; }
        INLINE Scalar operator* ( float s1, Scalar s2 ) { return Scalar( s1 ) * s2; }
        INLINE Scalar operator/ ( float s1, Scalar s2 ) { return Scalar( s1 ) / s2; }
#endif

    } // namespace Math
}