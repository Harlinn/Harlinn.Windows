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

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{
    class BoundingSphere
    {
    private:
        Vector4 m_repr;
    public:
#ifdef HDMC_USES_HCC_MATH
        using Constants = m::Traits::Constants;
#endif
        BoundingSphere( ) 
        {}
        BoundingSphere( float x, float y, float z, float r ) 
            : m_repr( x, y, z, r ) 
        {}
#ifdef HDMC_USES_HCC_MATH
        /*
        BoundingSphere( const std::array<float,4>& unaligned_array )
            : m_repr( unaligned_array )
        {
        }
        */
        BoundingSphere( const float* unaligned_array )
            : m_repr( m::Traits::UnalignedLoad( unaligned_array ) )
        {
        }
#else
        BoundingSphere( const XMFLOAT4* unaligned_array ) 
            : m_repr( *unaligned_array ) 
        {}
#endif
#ifdef HDMC_USES_HCC_MATH
        BoundingSphere( const Vector3& center, const Scalar& radius )
            : m_repr( center.simd )
        {
            m_repr.SetW( radius.simd );
        }
#else
        BoundingSphere( const Vector3& center, const Scalar& radius )
            : m_repr( center )
        {
            m_repr.SetW( radius );
        }
#endif
#ifdef HDMC_USES_HCC_MATH
        BoundingSphere( EZeroTag )
            : m_repr( Constants::Zero )
        {
        }
#else
        BoundingSphere( EZeroTag ) 
            : m_repr( kZero ) 
        {}
#endif
#ifdef HDMC_USES_HCC_MATH
        explicit BoundingSphere( const Vector4& sphere )
            : m_repr( sphere )
        { }

        explicit BoundingSphere( const XMFLOAT4& f4 )
            : m_repr( f4 )
        { }

        explicit BoundingSphere( const m::SIMDType& v )
            : m_repr( v )
        { }
#else
        explicit BoundingSphere( const XMVECTOR& v ) 
            : m_repr( v ) 
        {}
        explicit BoundingSphere( const XMFLOAT4& f4 ) 
            : m_repr( f4 ) 
        {}
        explicit BoundingSphere( Vector4 sphere ) 
            : m_repr( sphere ) 
        {}
#endif
        explicit operator const Vector4&( ) const 
        { 
            return m_repr;
        }

#ifdef HDMC_USES_HCC_MATH
        Vector3 GetCenter( void ) const
        {
            return Vector3( SetWToZero( m_repr.simd ) );
        }
#else
        Vector3 GetCenter( void ) const 
        { 
            return Vector3( m_repr ); 
        }
#endif
#ifdef HDMC_USES_HCC_MATH
        Scalar GetRadius( void ) const
        {
            return Scalar( m_repr.W().simd );
        }

        m::Vector<float, 4> Values( ) const
        {
            return m::Vector<float, 4>( m_repr );
        }

#else
        Scalar GetRadius( void ) const 
        { 
            return m_repr.GetW( ); 
        }
#endif

        HDMC_EXPORT BoundingSphere Union( const BoundingSphere& rhs );

    
    };

}