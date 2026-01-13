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

#include "HDMCBoundingPlane.h"
#include "HDMCBoundingSphere.h"
#include "HDMCBoundingBox.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
        class Frustum
        {
#ifdef HDMC_USES_HCC_MATH
            // the corners of the frustum
            std::array<Vector3,8> m_FrustumCorners;
            // the bounding planes
            std::array<BoundingPlane, 6> m_FrustumPlanes;
#else
            Vector3 m_FrustumCorners[ 8 ];		// the corners of the frustum
            BoundingPlane m_FrustumPlanes[ 6 ];			// the bounding planes
#endif
        public:
#ifdef HDMC_USES_HCC_MATH
            using Traits = Vector4::Traits;
#endif
            Frustum( ) {}

            Frustum( const Matrix4& ProjectionMatrix );

            enum CornerID
            {
                kNearLowerLeft, kNearUpperLeft, kNearLowerRight, kNearUpperRight,
                kFarLowerLeft, kFarUpperLeft, kFarLowerRight, kFarUpperRight
            };

            enum PlaneID
            {
                kNearPlane, kFarPlane, kLeftPlane, kRightPlane, kTopPlane, kBottomPlane
            };
#ifdef HDMC_USES_HCC_MATH
            const Vector3& GetFrustumCorner( CornerID id ) const 
            { 
                return m_FrustumCorners[ id ]; 
            }
            const BoundingPlane& GetFrustumPlane( PlaneID id ) const 
            { 
                return m_FrustumPlanes[ id ]; 
            }
#else
            Vector3         GetFrustumCorner( CornerID id ) const { return m_FrustumCorners[ id ]; }
            BoundingPlane   GetFrustumPlane( PlaneID id ) const { return m_FrustumPlanes[ id ]; }
#endif

            // Test whether the bounding sphere intersects the frustum.  Intersection is defined as either being
            // fully contained in the frustum, or by intersecting one or more of the planes.
#ifdef HDMC_USES_HCC_MATH
            bool IntersectSphere( const BoundingSphere& sphere ) const;
#else
            bool IntersectSphere( BoundingSphere sphere ) const;
#endif
            // We don't officially have a AxisAlignedBox class yet, but let's assume it's forthcoming.  (There is a
            // simple struct in the Model project.)
            bool IntersectBoundingBox( const AxisAlignedBox& aabb ) const;

            friend Frustum  operator* ( const OrthogonalTransform& xform, const Frustum& frustum );	// Fast
            friend Frustum  operator* ( const AffineTransform& xform, const Frustum& frustum );		// Slow
            friend Frustum  operator* ( const Matrix4& xform, const Frustum& frustum );				// Slowest (and most general)

        private:

            // Perspective frustum constructor (for pyramid-shaped frusta)
            void ConstructPerspectiveFrustum( float HTan, float VTan, float NearClip, float FarClip );

            // Orthographic frustum constructor (for box-shaped frusta)
            void ConstructOrthographicFrustum( float Left, float Right, float Top, float Bottom, float NearClip, float FarClip );

            
        };

        //=======================================================================================================
        // Inline implementations
        //
#ifdef HDMC_USES_HCC_MATH
        inline bool Frustum::IntersectSphere( const BoundingSphere& sphere ) const
#else
        inline bool Frustum::IntersectSphere( BoundingSphere sphere ) const
#endif
        {
#ifdef HDMC_USES_HCC_MATH
            float radius = First( sphere.GetRadius( ) );
#else
            float radius = sphere.GetRadius( );
#endif
            for ( int i = 0; i < 6; ++i )
            {
#ifdef HDMC_USES_HCC_MATH
                if ( First( m_FrustumPlanes[ i ].DistanceFromPoint( sphere.GetCenter( ) ) ) + radius < 0.0f )
#else
                if ( m_FrustumPlanes[ i ].DistanceFromPoint( sphere.GetCenter( ) ) + radius < 0.0f )
#endif
                {
                    return false;
                }
            }
            return true;
        }

        inline bool Frustum::IntersectBoundingBox( const AxisAlignedBox& aabb ) const
        {
            for ( int i = 0; i < 6; ++i )
            {
                BoundingPlane p = m_FrustumPlanes[ i ];
#ifdef HDMC_USES_HCC_MATH
                Vector3 farCorner( Traits::Select( aabb.GetMin( ).simd, aabb.GetMax( ).simd, Traits::Greater( p.GetNormal( ).simd, Traits::Constants::Zero ) ) );
#else
                Vector3 farCorner = Select( aabb.GetMin( ), aabb.GetMax( ), p.GetNormal( ) > Vector3( kZero ) );
#endif
                if ( p.DistanceFromPoint( farCorner ) < 0.0f )
                    return false;
            }

            return true;
        }

        inline Frustum operator* ( const OrthogonalTransform& xform, const Frustum& frustum )
        {
            Frustum result;

            for ( int i = 0; i < 8; ++i )
                result.m_FrustumCorners[ i ] = xform * frustum.m_FrustumCorners[ i ];

            for ( int i = 0; i < 6; ++i )
                result.m_FrustumPlanes[ i ] = xform * frustum.m_FrustumPlanes[ i ];

            return result;
        }

        inline Frustum operator* ( const AffineTransform& xform, const Frustum& frustum )
        {
            Frustum result;

            for ( int i = 0; i < 8; ++i )
                result.m_FrustumCorners[ i ] = xform * frustum.m_FrustumCorners[ i ];
#ifdef HDMC_USES_HCC_MATH
            Matrix4 XForm = m::Transpose( m::Inverse( xform.ToMatrix4( ) ) );
#else
            Matrix4 XForm = Transpose( Invert( Matrix4( xform ) ) );
#endif
            for ( int i = 0; i < 6; ++i )
            {
                result.m_FrustumPlanes[ i ] = BoundingPlane( XForm * Vector4( frustum.m_FrustumPlanes[ i ] ) );
            }

            return result;
        }

        inline Frustum operator* ( const Matrix4& mtx, const Frustum& frustum )
        {
            Frustum result;

            for ( int i = 0; i < 8; ++i )
            {
                
#ifdef HDMC_USES_HCC_MATH
                result.m_FrustumCorners[ i ] = ToVector3( mtx * frustum.m_FrustumCorners[ i ] );
#else
                result.m_FrustumCorners[ i ] = Vector3( mtx * frustum.m_FrustumCorners[ i ] );
#endif
            }
#ifdef HDMC_USES_HCC_MATH
            Matrix4 XForm = m::Transpose( m::Inverse( mtx ) );
#else
            Matrix4 XForm = Transpose( Invert( mtx ) );
#endif
            for ( int i = 0; i < 6; ++i )
            {
                result.m_FrustumPlanes[ i ] = BoundingPlane( XForm * Vector4( frustum.m_FrustumPlanes[ i ] ) );
            }

            return result;
        }

        inline void Dump( const char* name, const Frustum& frustum, const char* file, int line, const char* function )
        {
            constexpr const char* cornerNames[ ] =
            {
                "NearLowerLeft", "NearUpperLeft", "NearLowerRight", "NearUpperRight",
                "FarLowerLeft", "FarUpperLeft", "FarLowerRight", "FarUpperRight"
            };

            constexpr const char* planeNames[ ] =
            {
                "NearPlane", "FarPlane", "LeftPlane", "RightPlane", "TopPlane", "BottomPlane"
            };


            PrintLn( "// {}:", name );
            PrintLn( "//   Corners:" );
            for ( int i = 0; i < 8; i++ )
            {
                const auto& c = frustum.GetFrustumCorner( static_cast< Frustum::CornerID >( i ) );
#ifdef HDMC_USES_HCC_MATH
                m::Vector<float, 4> vec( Vector4( c.simd ) );
#else
                ::DirectX::XMFLOAT4A vec;
                ::DirectX::XMStoreFloat4A( &vec, c );
#endif
                const char* cornerName = cornerNames[ i ];
                PrintLn( "//     {}: [ {}, {}, {}, {} ]", cornerName, vec.x, vec.y, vec.z, vec.w );

            }
            PrintLn( "//   Planes:" );
            for ( int i = 0; i < 6; i++ )
            {
                const auto& p = frustum.GetFrustumPlane( static_cast< Frustum::PlaneID >( i ) );
                const char* planeName = planeNames[ i ];
#ifdef HDMC_USES_HCC_MATH
                m::Vector<float, 4> vec( p.ToVector4( ) );
#else
                ::DirectX::XMFLOAT4A vec;
                ::DirectX::XMStoreFloat4A( &vec, p.ToVector4( ) );
#endif
                PrintLn( "//     {}: [ {}, {}, {}, {} ]", planeName, vec.x, vec.y, vec.z, vec.w );

            }


            PrintLn( "// Function: {} ", function );
            PrintLn( "// Position: {}({})", file, line );

        }


    } // namespace Math
}