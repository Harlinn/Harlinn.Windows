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

#include "HDMCTransform.h"

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{
#ifdef HDMC_USES_HCC_MATH
    using Matrix4 = m::SquareMatrix<float, 4>::Simd;

    INLINE Matrix4 ToMatrix4( const Matrix3& xyz, Vector3 w )
    {
        Matrix4 result;
        result.simd[ 0 ] = SetWToZero( xyz.simd[ 0 ] );
        result.simd[ 1 ] = SetWToZero( xyz.simd[ 1 ] );
        result.simd[ 2 ] = SetWToZero( xyz.simd[ 2 ] );
        result.simd[ 3 ] = SetWToOne( w.simd );
        return result;
    }

    INLINE Matrix4 ToMatrix4( const AffineTransform& xform ) 
    { 
        return ToMatrix4( xform.GetBasis( ), xform.GetTranslation( ) );
    }
    INLINE Matrix4 ToMatrix4( const OrthogonalTransform& xform ) 
    { 
        return ToMatrix4( ToMatrix3( xform.GetRotation( ) ), xform.GetTranslation( ) ); 
    }

#else
    __declspec( align( 16 ) ) class Matrix4
    {
    public:
        INLINE Matrix4( ) {}
        INLINE Matrix4( Vector3 x, Vector3 y, Vector3 z, Vector3 w )
        {
            m_mat.r[ 0 ] = SetWToZero( x ); 
            m_mat.r[ 1 ] = SetWToZero( y );
            m_mat.r[ 2 ] = SetWToZero( z ); 
            m_mat.r[ 3 ] = SetWToOne( w );
        }

        INLINE Matrix4( const float* data )
        {
            m_mat = XMLoadFloat4x4( ( XMFLOAT4X4* )data );
        }

        INLINE Matrix4( Vector4 x, Vector4 y, Vector4 z, Vector4 w ) { m_mat.r[ 0 ] = x; m_mat.r[ 1 ] = y; m_mat.r[ 2 ] = z; m_mat.r[ 3 ] = w; }
        INLINE Matrix4( const Matrix4& mat ) { m_mat = mat.m_mat; }
        INLINE Matrix4( const Matrix3& mat )
        {
            m_mat.r[ 0 ] = SetWToZero( mat.GetX( ) );
            m_mat.r[ 1 ] = SetWToZero( mat.GetY( ) );
            m_mat.r[ 2 ] = SetWToZero( mat.GetZ( ) );
            m_mat.r[ 3 ] = CreateWUnitVector( );
        }
        INLINE Matrix4( const Matrix3& xyz, Vector3 w )
        {
            m_mat.r[ 0 ] = SetWToZero( xyz.GetX( ) );
            m_mat.r[ 1 ] = SetWToZero( xyz.GetY( ) );
            m_mat.r[ 2 ] = SetWToZero( xyz.GetZ( ) );
            m_mat.r[ 3 ] = SetWToOne( w );
        }
        INLINE Matrix4( const AffineTransform& xform ) { *this = Matrix4( xform.GetBasis( ), xform.GetTranslation( ) ); }
        INLINE Matrix4( const OrthogonalTransform& xform ) { *this = Matrix4( Matrix3( xform.GetRotation( ) ), xform.GetTranslation( ) ); }
        INLINE explicit Matrix4( const XMMATRIX& mat ) { m_mat = mat; }
        INLINE explicit Matrix4( EIdentityTag ) 
        { 
            m_mat = ::DirectX::XMMatrixIdentity( ); 
        }
        INLINE explicit Matrix4( EZeroTag ) 
        { 
            m_mat.r[ 0 ] = m_mat.r[ 1 ] = m_mat.r[ 2 ] = m_mat.r[ 3 ] = SplatZero( ); 
        }

        INLINE const Matrix3& Get3x3( ) const { return ( const Matrix3& )*this; }
        INLINE void Set3x3( const Matrix3& xyz )
        {
            m_mat.r[ 0 ] = SetWToZero( xyz.GetX( ) );
            m_mat.r[ 1 ] = SetWToZero( xyz.GetY( ) );
            m_mat.r[ 2 ] = SetWToZero( xyz.GetZ( ) );
        }

        INLINE Vector4 GetX( ) const { return Vector4( m_mat.r[ 0 ] ); }
        INLINE Vector4 GetY( ) const { return Vector4( m_mat.r[ 1 ] ); }
        INLINE Vector4 GetZ( ) const { return Vector4( m_mat.r[ 2 ] ); }
        INLINE Vector4 GetW( ) const { return Vector4( m_mat.r[ 3 ] ); }

        INLINE void SetX( Vector4 x ) { m_mat.r[ 0 ] = x; }
        INLINE void SetY( Vector4 y ) { m_mat.r[ 1 ] = y; }
        INLINE void SetZ( Vector4 z ) { m_mat.r[ 2 ] = z; }
        INLINE void SetW( Vector4 w ) { m_mat.r[ 3 ] = w; }

        INLINE operator XMMATRIX( ) const { return m_mat; }

        INLINE Vector4 operator* ( Vector3 vec ) const { return Vector4( XMVector3Transform( vec, m_mat ) ); }
        INLINE Vector4 operator* ( Vector4 vec ) const { return Vector4( XMVector4Transform( vec, m_mat ) ); }
        INLINE Matrix4 operator* ( const Matrix4& mat ) const { return Matrix4( XMMatrixMultiply( mat, m_mat ) ); }

        static INLINE Matrix4 MakeScale( float scale ) { return Matrix4( ::DirectX::XMMatrixScaling( scale, scale, scale ) ); }
        static INLINE Matrix4 MakeScale( Vector3 scale ) { return Matrix4( ::DirectX::XMMatrixScalingFromVector( scale ) ); }

    private:
        XMMATRIX m_mat;
    };
#endif

    inline std::string ToString( const Matrix4& m )
    {
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> matrix[ 4 ]{ Vector4( m.simd[ 0 ] ),
            Vector4( m.simd[ 1 ] ),
            Vector4( m.simd[ 2 ] ),
            Vector4( m.simd[ 3 ] ) };
#else
        ::DirectX::XMFLOAT4A matrix[ 4 ];
        ::DirectX::XMStoreFloat4A( &matrix[ 0 ], m.GetX( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 1 ], m.GetY( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 2 ], m.GetZ( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 3 ], m.GetW( ) );
#endif
        return std::format( "[ [ {}, {}, {}, {} ], [ {}, {}, {}, {} ], [ {}, {}, {}, {} ], [ {}, {}, {}, {} ] ]",
            matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w,
            matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w,
            matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w,
            matrix[ 3 ].x, matrix[ 3 ].y, matrix[ 3 ].z, matrix[ 3 ].w );

    }

    inline void Dump( const char* name, const Matrix4& m, const char* file, int line, const char* function )
    {
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> matrix[ 4 ]{ Vector4( m.simd[ 0 ] ), 
            Vector4( m.simd[ 1 ] ), 
            Vector4( m.simd[ 2 ] ),
            Vector4( m.simd[ 3 ] ) };
#else
        ::DirectX::XMFLOAT4A matrix[ 4 ];
        ::DirectX::XMStoreFloat4A( &matrix[ 0 ], m.GetX( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 1 ], m.GetY( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 2 ], m.GetZ( ) );
        ::DirectX::XMStoreFloat4A( &matrix[ 3 ], m.GetW( ) );
#endif

        PrintLn( "// {}:", name );
        PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w );
        PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w );
        PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w );
        PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 3 ].x, matrix[ 3 ].y, matrix[ 3 ].z, matrix[ 3 ].w );
        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
        PrintLn( "SquareMatrix<float, 4> {}( {}, {}, {}, {},", name, matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w );
        PrintLn( "                           {}, {}, {}, {},", matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w );
        PrintLn( "                           {}, {}, {}, {},", matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w );
        PrintLn( "                           {}, {}, {}, {} );", matrix[ 3 ].x, matrix[ 3 ].y, matrix[ 3 ].z, matrix[ 3 ].w );
    }

}