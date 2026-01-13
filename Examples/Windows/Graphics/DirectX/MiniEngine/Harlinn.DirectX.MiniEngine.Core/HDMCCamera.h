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
#include "Math/HDMCFrustum.h"
#include "Math/HDMCTransform.h"

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{
    class BaseCamera
    {
    public:

        // Call this function once per frame and after you've changed any state.  This
        // regenerates all matrices.  Calling it more or less than once per frame will break
        // temporal effects and cause unpredictable results.
        HDMC_EXPORT void Update( );

        // Public functions for controlling where the camera is and its orientation
        void SetEyeAtUp( Vector3 eye, Vector3 at, Vector3 up );
        HDMC_EXPORT void SetLookDirection( Vector3 forward, Vector3 up );
        void SetRotation( Quaternion basisRotation );
        void SetPosition( Vector3 worldPos );
        void SetTransform( const AffineTransform& xform );
        HDMC_EXPORT void SetTransform( const OrthogonalTransform& xform );

        const Quaternion GetRotation( ) const 
        { 
            return m_CameraToWorld.GetRotation( ); 
        }
#ifdef HDMC_USES_HCC_MATH
        const Vector3 GetRightVec( ) const 
        { 
            return m_Basis.simd[ 0 ]; 
        }
        const Vector3 GetUpVec( ) const 
        { 
            return m_Basis.simd[ 1 ]; 
        }
        const Vector3 GetForwardVec( ) const 
        { 
            return -Vector3(m_Basis.simd[ 2 ]); 
        }
#else
        const Vector3 GetRightVec( ) const 
        { 
            return m_Basis.GetX( ); 
        }
        const Vector3 GetUpVec( ) const 
        { 
            return m_Basis.GetY( ); 
        }
        const Vector3 GetForwardVec( ) const 
        { 
            return -m_Basis.GetZ( ); 
        }
#endif
        const Vector3 GetPosition( ) const 
        { 
            return m_CameraToWorld.GetTranslation( ); 
        }

        // Accessors for reading the various matrices and frusta
        const Matrix4& GetViewMatrix( ) const 
        { 
            return m_ViewMatrix; 
        }
        const Matrix4& GetProjMatrix( ) const 
        { 
            return m_ProjMatrix; 
        }
        const Matrix4& GetViewProjMatrix( ) const 
        { 
            return m_ViewProjMatrix; 
        }
        const Matrix4& GetReprojectionMatrix( ) const 
        { 
            return m_ReprojectMatrix; 
        }
        const Frustum& GetViewSpaceFrustum( ) const 
        { 
            return m_FrustumVS; 
        }
        const Frustum& GetWorldSpaceFrustum( ) const 
        { 
            return m_FrustumWS; 
        }

    protected:

        BaseCamera( ) 
            : m_CameraToWorld( kIdentity ), 
#ifdef HDMC_USES_HCC_MATH
              m_Basis( Matrix3::Identity( ) )
#else
              m_Basis( kIdentity ) 
#endif
        {
        }

        void SetProjMatrix( const Matrix4& ProjMat ) 
        { 
            m_ProjMatrix = ProjMat; 
        }

        OrthogonalTransform m_CameraToWorld;

        // Redundant data cached for faster lookups.
        Matrix3 m_Basis;

        // Transforms homogeneous coordinates from world space to view space.  In this case, view space is defined as +X is
        // to the right, +Y is up, and -Z is forward.  This has to match what the projection matrix expects, but you might
        // also need to know what the convention is if you work in view space in a shader.
        Matrix4 m_ViewMatrix;		// i.e. "World-to-View" matrix
        // The projection matrix transforms view space to clip space.  Once division by W has occurred, the final coordinates
        // can be transformed by the viewport matrix to screen space.  The projection matrix is determined by the screen aspect 
        // and camera field of view.  A projection matrix can also be orthographic.  In that case, field of view would be defined
        // in linear units, not angles.
        Matrix4 m_ProjMatrix;		// i.e. "View-to-Projection" matrix
        // A concatenation of the view and projection matrices.
        Matrix4 m_ViewProjMatrix;	// i.e.  "World-To-Projection" matrix.
        // The view-projection matrix from the previous frame
        Matrix4 m_PreviousViewProjMatrix;
        // Projects a clip-space coordinate to the previous frame (useful for temporal effects).
        Matrix4 m_ReprojectMatrix;
        Frustum m_FrustumVS;		// View-space view frustum
        Frustum m_FrustumWS;		// World-space view frustum

    };


    inline void Dump( const char* name, const BaseCamera& baseCamera, const char* file, int line, const char* function )
    {
        PrintLn( "// {}:", name );

        auto Rotation = baseCamera.GetRotation( );

        PrintLn( "//   Rotation: {}", ToString( Rotation ) );
        auto Position = baseCamera.GetPosition( );
        PrintLn( "//   Position: {}", ToString( Position ) );
        auto Right = baseCamera.GetRightVec( );
        PrintLn( "//   Right: {}", ToString( Right ) );
        auto Up = baseCamera.GetUpVec( );
        PrintLn( "//   Up: {}", ToString( Up ) );
        auto Forward = baseCamera.GetForwardVec( );
        PrintLn( "//   Forward: {}", ToString( Forward ) );

        const auto& ViewMatrix = baseCamera.GetViewMatrix( );
        PrintLn( "//   ViewMatrix: {}", ToString( ViewMatrix ) );

        const auto& ProjMatrix = baseCamera.GetProjMatrix( );
        PrintLn( "//   ProjMatrix: {}", ToString( ProjMatrix ) );

        const auto& ViewProjMatrix = baseCamera.GetViewProjMatrix( );
        PrintLn( "//   ViewProjMatrix: {}", ToString( ViewProjMatrix ) );



        PrintLn( "// Function: {} ", function );
        PrintLn( "// Position: {}({})", file, line );
    }


    class Camera : public BaseCamera
    {
    public:
        Camera( );

        // Controls the view-to-projection matrix
        void SetPerspectiveMatrix( float verticalFovRadians, float aspectHeightOverWidth, float nearZClip, float farZClip );
        void SetFOV( float verticalFovInRadians ) 
        { 
            m_VerticalFOV = verticalFovInRadians; UpdateProjMatrix( ); 
        }
        void SetAspectRatio( float heightOverWidth ) 
        { 
            m_AspectRatio = heightOverWidth; UpdateProjMatrix( ); 
        }
        void SetZRange( float nearZ, float farZ ) 
        { 
            m_NearClip = nearZ; m_FarClip = farZ; 
            UpdateProjMatrix( ); 
        }
        void ReverseZ( bool enable ) 
        { 
            m_ReverseZ = enable; UpdateProjMatrix( ); 
        }

        float GetFOV( ) const 
        { 
            return m_VerticalFOV; 
        }
        float GetNearClip( ) const 
        { 
            return m_NearClip; 
        }
        float GetFarClip( ) const 
        { 
            return m_FarClip; 
        }
        float GetClearDepth( ) const 
        { 
            return m_ReverseZ ? 0.0f : 1.0f; 
        }

    private:

        HDMC_EXPORT void UpdateProjMatrix( void );

        float m_VerticalFOV;	// Field of view angle in radians
        float m_AspectRatio;
        float m_NearClip;
        float m_FarClip;
        bool m_ReverseZ;		// Invert near and far clip distances so that Z=1 at the near plane
        bool m_InfiniteZ;       // Move the far plane to infinity
    };

    inline void BaseCamera::SetEyeAtUp( Vector3 eye, Vector3 at, Vector3 up )
    {
        SetLookDirection( at - eye, up );
        SetPosition( eye );
    }

    inline void BaseCamera::SetPosition( Vector3 worldPos )
    {
        m_CameraToWorld.SetTranslation( worldPos );
    }

    inline void BaseCamera::SetTransform( const AffineTransform& xform )
    {
        // By using these functions, we rederive an orthogonal transform.
        SetLookDirection( -xform.GetZ( ), xform.GetY( ) );
        SetPosition( xform.GetTranslation( ) );
    }

    inline void BaseCamera::SetRotation( Quaternion basisRotation )
    {
        m_CameraToWorld.SetRotation( Normalize( basisRotation ) );
#ifdef HDMC_USES_HCC_MATH
        m_Basis = Matrix3( m::Rotation( m_CameraToWorld.GetRotation( ) ).simd );
#else
        m_Basis = Matrix3( m_CameraToWorld.GetRotation( ) );
#endif
    }

    inline Camera::Camera( ) : m_ReverseZ( true ), m_InfiniteZ( false )
    {
        SetPerspectiveMatrix( ::DirectX::XM_PIDIV4, 9.0f / 16.0f, 1.0f, 1000.0f );
    }

    inline void Camera::SetPerspectiveMatrix( float verticalFovRadians, float aspectHeightOverWidth, float nearZClip, float farZClip )
    {
        m_VerticalFOV = verticalFovRadians;
        m_AspectRatio = aspectHeightOverWidth;
        m_NearClip = nearZClip;
        m_FarClip = farZClip;

        UpdateProjMatrix( );

        m_PreviousViewProjMatrix = m_ViewProjMatrix;
    }
}