/*
    Copyright 2024-2026 Espen Harlinn
 
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

#include "HDMCQuaternion.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
#ifdef HDMC_USES_HCC_MATH
        // Represents a 3x3 matrix while occupying a 3x4 memory footprint.  The unused row and column are undefined but implicitly
        // (0, 0, 0, 1).  Constructing a Matrix4 will make those values explicit.
        using Matrix3 = m::SquareMatrix<float, 3>::Simd;
        using Matrix4 = m::SquareMatrix<float, 4>::Simd;

        INLINE Matrix3 ToMatrix3( const Vector3& x, const Vector3& y, const Vector3& z )
        {
            return Matrix3( x.simd, y.simd, z.simd );
        }

        INLINE Matrix3 ToMatrix3( const Quaternion& q ) 
        { 
            auto rotation = m::Rotation( q );
            return Matrix3( rotation.simd );
        }

        INLINE Matrix3 ToMatrix3( const Matrix4& source )
        {
            Matrix3 result;
            result.simd[ 0 ] = SetWToZero( source.simd[ 0 ] );
            result.simd[ 1 ] = SetWToZero( source.simd[ 1 ] );
            result.simd[ 2 ] = SetWToZero( source.simd[ 2 ] );
            return result;
        }


        INLINE Matrix3 MakeXRotation( float angle )
        {
            return Matrix3( m::RotationX( angle ).simd );
        }
        INLINE Matrix3 MakeYRotation( float angle )
        {
            return Matrix3( m::RotationY( angle ).simd );
        }
        INLINE Matrix3 MakeZRotation( float angle )
        {
            return Matrix3( m::RotationZ( angle ).simd );
        }

        INLINE Matrix3 Matrix3MakeScale( float scale )
        { 
            return Matrix3( m::Scaling( scale, scale, scale ).simd ); 
        }
        INLINE Matrix3 Matrix3MakeScale( float sx, float sy, float sz )
        { 
            return Matrix3( m::Scaling( sx, sy, sz ).simd);
        }
        
        INLINE Matrix3 Matrix3MakeScale( const Vector3& scale )
        { 
            return Matrix3( m::Scaling( scale ).simd );
        }

        INLINE Matrix3 Matrix3MakeScale( const m::Vector<float,3>& scale )
        {
            return Matrix3( m::Scaling( scale ).simd );
        }

        INLINE Matrix4 Matrix4MakeScale( float scale ) 
        { 
            return m::Scaling( scale );
        }
        INLINE Matrix4 Matrix4MakeScale( Vector3 scale ) 
        { 
            return m::Scaling( scale );
        }

        INLINE Matrix4 ToMatrix4( const Vector3& x, const Vector3& y, const Vector3& z, const Vector3& w )
        {
            return Matrix4( x.simd, y.simd, z.simd, w.simd );
        }

        INLINE void Set3x3( const Matrix3& source, Matrix4& dest )
        {
            dest.simd[ 0 ] = SetWToZero( source.simd[ 0 ] );
            dest.simd[ 1 ] = SetWToZero( source.simd[ 1 ] );
            dest.simd[ 2 ] = SetWToZero( source.simd[ 2 ] );
        }


        INLINE Vector3 operator* ( const Matrix3& matrix, const Vector3& vec ) 
        { 
            using Traits = Vector3::Traits;
            return Traits::TransformNormal( vec.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] );
        }

        INLINE Matrix3 operator | ( const Matrix3& mat, const Matrix3& transformation )
        { 
            return Matrix3( (mat * Vector3(transformation.simd[0])).simd, (mat * Vector3( transformation.simd[ 1 ] )).simd, (mat * Vector3( transformation.simd[ 2 ] )).simd );
        }

        INLINE Matrix3 operator* ( const Matrix3& matrix, const Scalar& scl )
        {
            return Matrix3( (scl * Vector3(matrix.simd[0])).simd, 
                (scl * Vector3( matrix.simd[ 1 ] )).simd, 
                (scl * Vector3( matrix.simd[ 2 ] )).simd );
        }

        INLINE Vector4 operator* ( const Matrix4& matrix, const Vector3& vec )
        { 
            return m::Transform( vec, matrix );
        }
        INLINE Vector4 operator* ( const Matrix4& matrix, const Vector4& vec )
        { 
            return m::Transform( vec, matrix );
        }

        
#else
        

        // Represents a 3x3 matrix while occuping a 3x4 memory footprint.  The unused row and column are undefined but implicitly
        // (0, 0, 0, 1).  Constructing a Matrix4 will make those values explicit.
        __declspec( align( 16 ) ) class Matrix3
        {
        public:
            INLINE Matrix3( ) {}
            INLINE Matrix3( Vector3 x, Vector3 y, Vector3 z ) { m_mat[ 0 ] = x; m_mat[ 1 ] = y; m_mat[ 2 ] = z; }
            INLINE Matrix3( const Matrix3& m ) { m_mat[ 0 ] = m.m_mat[ 0 ]; m_mat[ 1 ] = m.m_mat[ 1 ]; m_mat[ 2 ] = m.m_mat[ 2 ]; }
            INLINE Matrix3( Quaternion q ) { *this = Matrix3( ::DirectX::XMMatrixRotationQuaternion( q ) ); }
            INLINE explicit Matrix3( const XMMATRIX& m ) { m_mat[ 0 ] = Vector3( m.r[ 0 ] ); m_mat[ 1 ] = Vector3( m.r[ 1 ] ); m_mat[ 2 ] = Vector3( m.r[ 2 ] ); }
            INLINE explicit Matrix3( EIdentityTag ) 
            { 
                m_mat[ 0 ] = Vector3( kXUnitVector ); 
                m_mat[ 1 ] = Vector3( kYUnitVector ); 
                m_mat[ 2 ] = Vector3( kZUnitVector ); 
            }
            INLINE explicit Matrix3( EZeroTag ) 
            { 
                m_mat[ 0 ] = m_mat[ 1 ] = m_mat[ 2 ] = Vector3( kZero ); 
            }

            INLINE void SetX( Vector3 x ) { m_mat[ 0 ] = x; }
            INLINE void SetY( Vector3 y ) { m_mat[ 1 ] = y; }
            INLINE void SetZ( Vector3 z ) { m_mat[ 2 ] = z; }

            INLINE Vector3 GetX( ) const { return m_mat[ 0 ]; }
            INLINE Vector3 GetY( ) const { return m_mat[ 1 ]; }
            INLINE Vector3 GetZ( ) const { return m_mat[ 2 ]; }

            static INLINE Matrix3 MakeXRotation( float angle ) 
            { 
                return Matrix3( ::DirectX::XMMatrixRotationX( angle ) ); 
            }
            static INLINE Matrix3 MakeYRotation( float angle ) 
            { 
                return Matrix3( ::DirectX::XMMatrixRotationY( angle ) ); 
            }
            static INLINE Matrix3 MakeZRotation( float angle ) 
            { 
                return Matrix3( ::DirectX::XMMatrixRotationZ( angle ) ); 
            }
            static INLINE Matrix3 MakeScale( float scale ) 
            { 
                return Matrix3( ::DirectX::XMMatrixScaling( scale, scale, scale ) ); 
            }
            static INLINE Matrix3 MakeScale( float sx, float sy, float sz ) 
            { 
                return Matrix3( ::DirectX::XMMatrixScaling( sx, sy, sz ) ); 
            }
            static INLINE Matrix3 MakeScale( const XMFLOAT3& scale ) 
            { 
                return Matrix3( ::DirectX::XMMatrixScaling( scale.x, scale.y, scale.z ) ); 
            }
            static INLINE Matrix3 MakeScale( Vector3 scale ) 
            { 
                return Matrix3( ::DirectX::XMMatrixScalingFromVector( scale ) ); 
            }

            // Useful for DirectXMath interaction.  WARNING:  Only the 3x3 elements are defined.
            INLINE operator XMMATRIX( ) const 
            { 
                return XMMATRIX( m_mat[ 0 ], m_mat[ 1 ], m_mat[ 2 ], ::DirectX::XMVectorZero( ) ); 
            }

            INLINE Matrix3 operator* ( Scalar scl ) const 
            { 
                return Matrix3( scl * GetX( ), scl * GetY( ), scl * GetZ( ) ); 
            }
            
            INLINE Vector3 operator* ( Vector3 vec ) const 
            { 
                return Vector3( ::DirectX::XMVector3TransformNormal( vec, *this ) ); 
            }
            INLINE Matrix3 operator* ( const Matrix3& mat ) const 
            { 
                return Matrix3( *this * mat.GetX( ), *this * mat.GetY( ), *this * mat.GetZ( ) ); 
            }
            
        private:
            Vector3 m_mat[ 3 ];
        };
#endif
        inline std::string ToString( const Matrix3& m )
        {
#ifdef HDMC_USES_HCC_MATH
            m::Vector<float, 4> matrix[ 3 ]{ Vector4( m.simd[ 0 ] ), Vector4( m.simd[ 1 ] ), Vector4( m.simd[ 2 ] ) };
#else
            ::DirectX::XMFLOAT4A matrix[ 3 ];
            ::DirectX::XMStoreFloat4A( &matrix[ 0 ], m.GetX( ) );
            ::DirectX::XMStoreFloat4A( &matrix[ 1 ], m.GetY( ) );
            ::DirectX::XMStoreFloat4A( &matrix[ 2 ], m.GetZ( ) );
#endif
            return std::format( "[ [ {}, {}, {}, ({}) ], [ {}, {}, {}, ({}) ], [ {}, {}, {}, ({}) ] ]", 
                        matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w, 
                        matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w, 
                        matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w );

        }


        inline void Dump( const char* name, const Matrix3& m, const char* file, int line, const char* function )
        {
#ifdef HDMC_USES_HCC_MATH
            m::Vector<float, 4> matrix[ 3 ]{ Vector4( m.simd[ 0 ] ), Vector4( m.simd[ 1 ] ), Vector4( m.simd[ 2 ] ) };
#else
            ::DirectX::XMFLOAT4A matrix[3];
            ::DirectX::XMStoreFloat4A( &matrix[ 0 ], m.GetX( ) );
            ::DirectX::XMStoreFloat4A( &matrix[ 1 ], m.GetY( ) );
            ::DirectX::XMStoreFloat4A( &matrix[ 2 ], m.GetZ( ) );
#endif

            PrintLn( "// {}:", name );
            PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z, matrix[ 0 ].w );
            PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z, matrix[ 1 ].w );
            PrintLn( "// [ {}, {}, {}, {} ]", matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z, matrix[ 2 ].w );
            PrintLn( "// Function: {} ", function );
            PrintLn( "// Position: {}({})", file, line );
            PrintLn( "SquareMatrix<float, 3> {}( {}, {}, {},", name, matrix[ 0 ].x, matrix[ 0 ].y, matrix[ 0 ].z );
            PrintLn( "                           {}, {}, {},", matrix[ 1 ].x, matrix[ 1 ].y, matrix[ 1 ].z );
            PrintLn( "                           {}, {}, {} );", matrix[ 2 ].x, matrix[ 2 ].y, matrix[ 2 ].z );
        }


    } // namespace Math

}