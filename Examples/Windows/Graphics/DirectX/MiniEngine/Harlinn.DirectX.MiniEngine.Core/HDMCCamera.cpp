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

#include "pch.h"
#include "HDMCCamera.h"
#include <cmath>

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{

    void BaseCamera::SetLookDirection( Vector3 forward, Vector3 up )
    {
        // Given, but ensure normalization
        
#ifdef HDMC_USES_HCC_MATH
        auto forwardLenSq = LengthSquared( forward );
        forward = m::Traits::Select( (forward * m::ReciprocalSqrt( forwardLenSq )).simd, ( -Vector3( m::Traits::Constants::IdentityR2 )).simd, m::Traits::Less( forwardLenSq.simd, Scalar( 0.000001f ).simd ) );
#else
        Scalar forwardLenSq = LengthSquare( forward );
        forward = Select( forward * RecipSqrt( forwardLenSq ), -Vector3( kZUnitVector ), forwardLenSq < Scalar( 0.000001f ) );
#endif
        // Deduce a valid, orthogonal right vector
        Vector3 right = Cross( forward, up );
#ifdef HDMC_USES_HCC_MATH
        auto rightLenSq = LengthSquared( right );
        right = m::Traits::Select( (right * m::ReciprocalSqrt( rightLenSq )).simd, 
            Rotate( forward, Quaternion::FromAxisAndAngle( m::Vector3f::Simd( m::Traits::Constants::IdentityR2 ).simd, -::DirectX::XM_PIDIV2 ) ).simd, 
            m::Traits::Less(rightLenSq.simd, Scalar( 0.000001f ).simd ) );
#else
        Scalar rightLenSq = LengthSquare( right );
        right = Select( right * RecipSqrt( rightLenSq ), Quaternion( Vector3( kYUnitVector ), -::DirectX::XM_PIDIV2 ) * forward, rightLenSq < Scalar( 0.000001f ) );
#endif
        // Compute actual up vector
        up = Cross( right, forward );

        // Finish constructing basis
#ifdef HDMC_USES_HCC_MATH
        m_Basis = ToMatrix3( right, up, -forward );
        m_CameraToWorld.SetRotation( Quaternion::FromMatrix( m_Basis.simd ) );
#else
        m_Basis = Matrix3( right, up, -forward );
        m_CameraToWorld.SetRotation( Quaternion( m_Basis ) );
#endif
    }

    void BaseCamera::Update( )
    {
        m_PreviousViewProjMatrix = m_ViewProjMatrix;
#ifdef HDMC_USES_HCC_MATH
        m_ViewMatrix = ToMatrix4(~m_CameraToWorld);
#else
        m_ViewMatrix = Matrix4( ~m_CameraToWorld );
#endif
#ifdef HDMC_USES_HCC_MATH
        m_ViewProjMatrix = m_ViewMatrix * m_ProjMatrix;
        m_ReprojectMatrix = Invert( GetViewProjMatrix( ) ) * m_PreviousViewProjMatrix;
#else
        m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
        m_ReprojectMatrix = m_PreviousViewProjMatrix * Invert( GetViewProjMatrix( ) );
#endif
        m_FrustumVS = Frustum( m_ProjMatrix );
        m_FrustumWS = m_CameraToWorld * m_FrustumVS;
    }


    void Camera::UpdateProjMatrix( void )
    {
        float Y = 1.0f / std::tanf( m_VerticalFOV * 0.5f );
        float X = Y * m_AspectRatio;

        float Q1, Q2;

        // ReverseZ puts far plane at Z=0 and near plane at Z=1.  This is never a bad idea, and it's
        // actually a great idea with F32 depth buffers to redistribute precision more evenly across
        // the entire range.  It requires clearing Z to 0.0f and using a GREATER variant depth test.
        // Some care must also be done to properly reconstruct linear W in a pixel shader from hyperbolic Z.
        if ( m_ReverseZ )
        {
            if ( m_InfiniteZ )
            {
                Q1 = 0.0f;
                Q2 = m_NearClip;
            }
            else
            {
                Q1 = m_NearClip / ( m_FarClip - m_NearClip );
                Q2 = Q1 * m_FarClip;
            }
        }
        else
        {
            if ( m_InfiniteZ )
            {
                Q1 = -1.0f;
                Q2 = -m_NearClip;
            }
            else
            {
                Q1 = m_FarClip / ( m_NearClip - m_FarClip );
                Q2 = Q1 * m_NearClip;
            }
        }
#ifdef HDMC_USES_HCC_MATH
        SetProjMatrix( Matrix4(
            Vector4( X, 0.0f, 0.0f, 0.0f ).simd,
            Vector4( 0.0f, Y, 0.0f, 0.0f ).simd,
            Vector4( 0.0f, 0.0f, Q1, -1.0f ).simd,
            Vector4( 0.0f, 0.0f, Q2, 0.0f ).simd
        ) );
#else
        SetProjMatrix( Matrix4(
            Vector4( X, 0.0f, 0.0f, 0.0f ),
            Vector4( 0.0f, Y, 0.0f, 0.0f ),
            Vector4( 0.0f, 0.0f, Q1, -1.0f ),
            Vector4( 0.0f, 0.0f, Q2, 0.0f )
        ) );
#endif
    }
}