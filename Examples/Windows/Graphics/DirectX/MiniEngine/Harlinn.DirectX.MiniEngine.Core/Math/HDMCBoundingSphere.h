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
        BoundingSphere( ) 
        {}
        BoundingSphere( float x, float y, float z, float r ) 
            : m_repr( x, y, z, r ) 
        {}
        BoundingSphere( const XMFLOAT4* unaligned_array ) 
            : m_repr( *unaligned_array ) 
        {}
        BoundingSphere( const Vector3& center, const Scalar& radius )
            : m_repr( center )
        {
            m_repr.SetW( radius );
        }
        BoundingSphere( EZeroTag ) 
            : m_repr( kZero ) 
        {}
        explicit BoundingSphere( const XMVECTOR& v ) 
            : m_repr( v ) 
        {}
        explicit BoundingSphere( const XMFLOAT4& f4 ) 
            : m_repr( f4 ) 
        {}
        explicit BoundingSphere( Vector4 sphere ) 
            : m_repr( sphere ) 
        {}

        explicit operator const Vector4&( ) const 
        { 
            return m_repr;
        }

        Vector3 GetCenter( void ) const 
        { 
            return Vector3( m_repr ); 
        }
        Scalar GetRadius( void ) const 
        { 
            return m_repr.GetW( ); 
        }

        HDMC_EXPORT BoundingSphere Union( const BoundingSphere& rhs );

    
    };

}