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

#include "HDMCGameCore.h"
#include "HDMCVectorMath.h"
#include "Math/HDMCBoundingSphere.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
        class Camera;
    }

    using namespace Math;

    class CameraController
    {
    public:
        // Assumes worldUp is not the X basis vector
        CameraController( Camera& camera ) : m_TargetCamera( camera ) {}
        virtual ~CameraController( ) {}
        virtual void Update( float dt ) = 0;

        // Helper function
        HDMC_EXPORT static void ApplyMomentum( float& oldValue, float& newValue, float deltaTime );

    protected:
        Camera& m_TargetCamera;

    private:
        CameraController& operator=( const CameraController& ) { return *this; }
    };

    class FlyingFPSCamera : public CameraController
    {
    public:
        HDMC_EXPORT FlyingFPSCamera( Camera& camera, Vector3 worldUp );

        HDMC_EXPORT virtual void Update( float dt ) override;

        void SlowMovement( bool enable ) { m_FineMovement = enable; }
        void SlowRotation( bool enable ) { m_FineRotation = enable; }

        void EnableMomentum( bool enable ) { m_Momentum = enable; }

        HDMC_EXPORT void SetHeadingPitchAndPosition( float heading, float pitch, const Vector3& position );

    private:

        Vector3 m_WorldUp;
        Vector3 m_WorldNorth;
        Vector3 m_WorldEast;
        float m_HorizontalLookSensitivity;
        float m_VerticalLookSensitivity;
        float m_MoveSpeed;
        float m_StrafeSpeed;
        float m_MouseSensitivityX;
        float m_MouseSensitivityY;

        float m_CurrentHeading;
        float m_CurrentPitch;

        bool m_FineMovement;
        bool m_FineRotation;
        bool m_Momentum;

        float m_LastYaw;
        float m_LastPitch;
        float m_LastForward;
        float m_LastStrafe;
        float m_LastAscent;
    };

    class OrbitCamera : public CameraController
    {
    public:
        HDMC_EXPORT OrbitCamera( Math::Camera& camera,
            Math::BoundingSphere focus,
#ifdef HDMC_USES_HCC_MATH
            Math::Vector3 upVec = Math::Vector3( m::Traits::Constants::IdentityR2 ) );
#else
            Math::Vector3 upVec = Math::Vector3( Math::kYUnitVector ) );
#endif

        HDMC_EXPORT virtual void Update( float dt ) override;

        void EnableMomentum( bool enable ) { m_Momentum = enable; }

    private:
        OrbitCamera& operator=( const OrbitCamera& ) { return *this; }

        Math::BoundingSphere m_ModelBounds;
        Math::Vector3 m_WorldUp;

        float m_JoystickSensitivityX;
        float m_JoystickSensitivityY;

        float m_MouseSensitivityX;
        float m_MouseSensitivityY;

        float m_CurrentHeading;
        float m_CurrentPitch;
        float m_CurrentCloseness;

        bool m_Momentum;

        float m_LastYaw;
        float m_LastPitch;
        float m_LastForward;
    };
}