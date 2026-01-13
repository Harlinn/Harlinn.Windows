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

#include "pch.h"
#include "HDMCShadowCamera.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    using namespace Math;

    void ShadowCamera::UpdateMatrix(
        Vector3 LightDirection, Vector3 ShadowCenter, Vector3 ShadowBounds,
        uint32_t BufferWidth, uint32_t BufferHeight, uint32_t BufferPrecision )
    {
#ifdef HDMC_USES_HCC_MATH
        SetLookDirection( LightDirection, Vector3( m::Traits::Constants::IdentityR3 ) );
#else
        SetLookDirection( LightDirection, Vector3( kZUnitVector ) );
#endif

        // Converts world units to texel units so we can quantize the camera position to whole texel units
#ifdef HDMC_USES_HCC_MATH
        Vector3 RcpDimensions = m::Reciprocal( ShadowBounds );
#else
        Vector3 RcpDimensions = Recip( ShadowBounds );
#endif
        Vector3 QuantizeScale = Vector3( ( float )BufferWidth, ( float )BufferHeight, ( float )( ( 1 << BufferPrecision ) - 1 ) ) * RcpDimensions;

        //
        // Recenter the camera at the quantized position
        //

        // Transform to view space
        ShadowCenter = ~GetRotation( ) * ShadowCenter;
        // Scale to texel units, truncate fractional part, and scale back to world units
        ShadowCenter = Floor( ShadowCenter * QuantizeScale ) / QuantizeScale;
        // Transform back into world space
        ShadowCenter = GetRotation( ) * ShadowCenter;

        SetPosition( ShadowCenter );
#ifdef HDMC_USES_HCC_MATH
        SetProjMatrix( Matrix4MakeScale( Vector3( 2.0f, 2.0f, 1.0f ) * RcpDimensions ) );
#else
        SetProjMatrix( Matrix4::MakeScale( Vector3( 2.0f, 2.0f, 1.0f ) * RcpDimensions ) );
#endif

        Update( );

        // Transform from clip space to texture space
#ifdef HDMC_USES_HCC_MATH
        m_ShadowMatrix = m_ViewProjMatrix * ToMatrix4( AffineTransform( Matrix3MakeScale( 0.5f, -0.5f, 1.0f ), Vector3( 0.5f, 0.5f, 0.0f ) ) );
#else
        m_ShadowMatrix = Matrix4( AffineTransform( Matrix3::MakeScale( 0.5f, -0.5f, 1.0f ), Vector3( 0.5f, 0.5f, 0.0f ) ) ) * m_ViewProjMatrix;
#endif
    }

}