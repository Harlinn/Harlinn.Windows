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

#include "HDMCEngineTuning.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    // Forward declarations
#ifdef HDMC_USES_HCC_MATH
    namespace Math
    {
        using Matrix4 = m::SquareMatrix<float, 4>::Simd;
        class Camera;
    }
#else
    namespace Math { class Matrix4; class Camera; }
#endif
    class ColorBuffer;
    class CommandContext;

    namespace MotionBlur
    {
        HDMC_EXPORT extern BoolVar Enable;

        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Shutdown( void );

        HDMC_EXPORT void GenerateCameraVelocityBuffer( CommandContext& Context, const Math::Camera& camera, bool UseLinearZ = true );
        HDMC_EXPORT void GenerateCameraVelocityBuffer( CommandContext& Context, const Math::Matrix4& reprojectionMatrix, float nearClip, float farClip, bool UseLinearZ = true );

        // Generate motion blur only associated with the camera.  Does not handle fast-moving objects well, but
        // does not require a full screen velocity buffer.
        HDMC_EXPORT void RenderCameraBlur( CommandContext& Context, const Math::Camera& camera, bool UseLinearZ = true );
        HDMC_EXPORT void RenderCameraBlur( CommandContext& Context, const Math::Matrix4& reprojectionMatrix, float nearClip, float farClip, bool UseLinearZ = true );

        // Generate proper motion blur that takes into account the velocity of each pixel.  Requires a pre-generated
        // velocity buffer (R16G16_FLOAT preferred.)
        HDMC_EXPORT void RenderObjectBlur( CommandContext& Context, ColorBuffer& velocityBuffer );
    }
}