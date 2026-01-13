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

#include "HDMCCamera.h"
#include "HDMCVectorMath.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class ShadowCamera : public Math::BaseCamera
    {
    public:

        ShadowCamera( ) {}

        HDMC_EXPORT void UpdateMatrix(
            Math::Vector3 LightDirection,		// Direction parallel to light, in direction of travel
            Math::Vector3 ShadowCenter,		// Center location on far bounding plane of shadowed region
            Math::Vector3 ShadowBounds,		// Width, height, and depth in world space represented by the shadow buffer
            uint32_t BufferWidth,		// Shadow buffer width
            uint32_t BufferHeight,		// Shadow buffer height--usually same as width
            uint32_t BufferPrecision	// Bit depth of shadow buffer--usually 16 or 24
        );

        // Used to transform world space to texture space for shadow sampling
        const Math::Matrix4& GetShadowMatrix( ) const { return m_ShadowMatrix; }

    private:

        Math::Matrix4 m_ShadowMatrix;
    };
}