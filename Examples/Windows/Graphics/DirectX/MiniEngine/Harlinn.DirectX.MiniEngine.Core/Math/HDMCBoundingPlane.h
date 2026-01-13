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

#include "HDMCVectorMath.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    namespace Math
    {
        class BoundingPlane
        {
            Vector4 m_repr;
        public:
#ifdef HDMC_USES_HCC_MATH
            using Traits = Vector4::Traits;
#endif
            BoundingPlane( ) {}
            BoundingPlane( Vector3 normalToPlane, float distanceFromOrigin ) 
#ifdef HDMC_USES_HCC_MATH
                : m_repr( Traits::SetW( normalToPlane.simd, distanceFromOrigin ) )
#else
                : m_repr( normalToPlane, distanceFromOrigin ) 
#endif
            {}
            BoundingPlane( Vector3 pointOnPlane, Vector3 normalToPlane );
            BoundingPlane( float A, float B, float C, float D ) : m_repr( A, B, C, D ) {}
            BoundingPlane( const BoundingPlane& plane ) : m_repr( plane.m_repr ) {}
            explicit BoundingPlane( Vector4 plane ) : m_repr( plane ) {}

            INLINE operator Vector4( ) const { return m_repr; }

            INLINE const Vector4& ToVector4( ) const { return m_repr; }

#ifdef HDMC_USES_HCC_MATH
            Vector3 GetNormal( void ) const { return ToVector3( m_repr.simd ); }
#else
            // Returns the direction the plane is facing.  (Warning:  might not be normalized.)
            Vector3 GetNormal( void ) const { return Vector3( XMVECTOR( m_repr ) ); }
#endif

#ifdef HDMC_USES_HCC_MATH
            // Returns the point on the plane closest to the origin
            Vector3 GetPointOnPlane( void ) const 
            { 
                return -GetNormal( ) * ToVector3(m_repr.W( ));
            }
#else
            // Returns the point on the plane closest to the origin
            Vector3 GetPointOnPlane( void ) const { return -GetNormal( ) * m_repr.GetW( ); }
#endif
            // Distance from 3D point
            Scalar DistanceFromPoint( Vector3 point ) const
            {
#ifdef HDMC_USES_HCC_MATH
                return (Dot<0xFF>( point, GetNormal( ) ) + ToVector3( m_repr.W( ) ));
#else
                return Dot( point, GetNormal( ) ) + m_repr.GetW( );
#endif
            }

            // Distance from homogeneous point
            Scalar DistanceFromPoint( Vector4 point ) const
            {
                return Dot( point, m_repr );
            }

            // Most efficient way to transform a plane.  (Involves one quaternion-vector rotation and one dot product.)
            friend BoundingPlane operator* ( const OrthogonalTransform& xform, BoundingPlane plane )
            {
                Vector3 normalToPlane = xform.GetRotation( ) * plane.GetNormal( );
#ifdef HDMC_USES_HCC_MATH
                float distanceFromOrigin = Traits::Extract<3>( plane.m_repr.simd ) - m::ScalarDot( normalToPlane, xform.GetTranslation( ) );
#else
                float distanceFromOrigin = plane.m_repr.GetW( ) - Dot( normalToPlane, xform.GetTranslation( ) );
#endif
                return BoundingPlane( normalToPlane, distanceFromOrigin );
            }

            // Less efficient way to transform a plane (but handles affine transformations.)
            friend BoundingPlane operator* ( const Matrix4& mat, BoundingPlane plane )
            {
                
#ifdef HDMC_USES_HCC_MATH
                return BoundingPlane( m::Transpose( Invert( mat ) ) * plane.m_repr );
#else
                return BoundingPlane( Transpose( Invert( mat ) ) * plane.m_repr );
#endif
            }

        private:

            
        };

        //=======================================================================================================
        // Inline implementations
        //
        inline BoundingPlane::BoundingPlane( Vector3 pointOnPlane, Vector3 normalToPlane )
        {
            // Guarantee a normal.  This constructor isn't meant to be called frequently, but if it is, we can change this.
            normalToPlane = Normalize( normalToPlane );
#ifdef HDMC_USES_HCC_MATH
            m_repr = Math::ToVector4( normalToPlane, -ScalarDot( pointOnPlane, normalToPlane ) );
#else
            m_repr = Vector4( normalToPlane, -Dot( pointOnPlane, normalToPlane ) );
#endif
        }

        //=======================================================================================================
        // Functions operating on planes
        //
        inline BoundingPlane PlaneFromPointsCCW( Vector3 A, Vector3 B, Vector3 C )
        {
            return BoundingPlane( A, Cross( B - A, C - A ) );
        }

        inline std::string ToString( const BoundingPlane& boundingPlane )
        {
            const auto& v = boundingPlane.ToVector4( );
#ifdef HDMC_USES_HCC_MATH
            m::Vector<float, 4> vec( Vector4( v.simd ) );
#else
            ::DirectX::XMFLOAT4A vec;
            ::DirectX::XMStoreFloat4A( &vec, v );
#endif
            return std::format( "[ {}, {}, {}, {} ]", vec.x, vec.y, vec.z, vec.w );

        }

        
        inline void Dump( const char* name, const BoundingPlane& boundingPlane, const char* file, int line, const char* function )
        {
            const auto& v = boundingPlane.ToVector4( );
#ifdef HDMC_USES_HCC_MATH
            m::Vector<float, 4> vec( v );
#else
            ::DirectX::XMFLOAT4A vec;
            ::DirectX::XMStoreFloat4A( &vec, v );
#endif

            PrintLn( "// {}:", name );
            PrintLn( "// [ {}, {}, {}, {} ]", vec.x, vec.y, vec.z, vec.w );
            PrintLn( "// Function: {} ", function );
            PrintLn( "// Position: {}({})", file, line );
        }


    } // namespace Math
}