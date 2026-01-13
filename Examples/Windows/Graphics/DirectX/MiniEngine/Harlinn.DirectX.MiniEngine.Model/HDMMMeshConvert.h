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

#include "HDMMglTF.h"
#include "Math/HDMCBoundingSphere.h"
#include "Math/HDMCBoundingBox.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Renderer
    {
        using namespace Math;

        struct Primitive
        {
            BoundingSphere m_BoundsLS;  // local space bounds
            BoundingSphere m_BoundsOS;  // object space bounds
            AxisAlignedBox m_BBoxLS;       // local space AABB
            AxisAlignedBox m_BBoxOS;       // object space AABB
            Utility::ByteArray VB;
            Utility::ByteArray IB;
            Utility::ByteArray DepthVB;
            uint32_t primCount;
            union
            {
                uint32_t hash;
                struct
                {
                    uint32_t psoFlags : 16;
                    uint32_t index32 : 1;
                    uint32_t materialIdx : 15;
                };
            };
            uint16_t vertexStride;
        };
    }

    HDMM_EXPORT void OptimizeMesh( Renderer::Primitive& outPrim, const glTF::Primitive& inPrim, const Math::Matrix4& localToObject );
}