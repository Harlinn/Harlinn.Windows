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
// Author(s):  Alex Nankervis
//             James Stanard
//

#pragma once

#include "HDMMDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class StructuredBuffer;
    class ByteAddressBuffer;
    class ColorBuffer;
    class ShadowBuffer;
    class GraphicsContext;
    class IntVar;
    namespace Math
    {
#ifdef HDMC_USES_HCC_MATH
        using Vector3 = m::Vector<float, 3>::Simd;
        using Matrix4 = m::SquareMatrix<float, 4>::Simd;
#else
        class Vector3;
        class Matrix4;
#endif
        class Camera;

    }

    namespace Lighting
    {
        HDMM_EXPORT extern IntVar LightGridDim;

        enum { MaxLights = 128 };

        //LightData m_LightData[MaxLights];
        HDMM_EXPORT extern StructuredBuffer m_LightBuffer;
        HDMM_EXPORT extern ByteAddressBuffer m_LightGrid;

        HDMM_EXPORT extern ByteAddressBuffer m_LightGridBitMask;
        HDMM_EXPORT extern std::uint32_t m_FirstConeLight;
        HDMM_EXPORT extern std::uint32_t m_FirstConeShadowedLight;

        HDMM_EXPORT extern ColorBuffer m_LightShadowArray;
        HDMM_EXPORT extern ShadowBuffer m_LightShadowTempBuffer;
        HDMM_EXPORT extern Math::Matrix4 m_LightShadowMatrix[ MaxLights ];

        HDMM_EXPORT void InitializeResources( void );
        HDMM_EXPORT void CreateRandomLights( const Math::Vector3 minBound, const Math::Vector3 maxBound );
        HDMM_EXPORT void FillLightGrid( GraphicsContext& gfxContext, const Math::Camera& camera );
        HDMM_EXPORT void Shutdown( void );
    }
}