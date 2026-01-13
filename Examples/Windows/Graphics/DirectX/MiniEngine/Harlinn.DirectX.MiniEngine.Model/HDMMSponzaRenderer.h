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
// Author(s):  James Stanard
//

#pragma once

#include "HDMMDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class GraphicsContext;
    class ShadowCamera;
    class ModelH3D;
    class ExpVar;

    namespace Math
    {
        class Camera;
#ifdef HDMC_USES_HCC_MATH
        using Vector3 = m::Vector<float, 3>::Simd;
#else
        class Vector3;
#endif
    }

    namespace Sponza
    {
        HDMM_EXPORT void Startup( Math::Camera& camera );
        HDMM_EXPORT void Cleanup( void );

        HDMM_EXPORT void RenderScene(
            GraphicsContext& gfxContext,
            const Math::Camera& camera,
            const D3D12_VIEWPORT& viewport,
            const D3D12_RECT& scissor,
            bool skipDiffusePass = false,
            bool skipShadowMap = false );

        HDMM_EXPORT const ModelH3D& GetModel( );

        HDMM_EXPORT extern Math::Vector3 m_SunDirection;
        HDMM_EXPORT extern ShadowCamera m_SunShadow;
        HDMM_EXPORT extern ExpVar m_AmbientIntensity;
        HDMM_EXPORT extern ExpVar m_SunLightIntensity;

    }

}