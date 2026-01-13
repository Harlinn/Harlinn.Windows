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

#include "HDMCDepthBuffer.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class GraphicsContext;

    class ShadowBuffer : public DepthBuffer
    {
    private:
        D3D12_VIEWPORT m_Viewport;
        D3D12_RECT m_Scissor;
    public:
        ShadowBuffer( ) {}

        HDMC_EXPORT void Create( const std::wstring& Name, uint32_t Width, uint32_t Height, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN );

        D3D12_CPU_DESCRIPTOR_HANDLE GetSRV( ) const 
        { 
            return GetDepthSRV( ); 
        }

        HDMC_EXPORT void BeginRendering( GraphicsContext& context );
        HDMC_EXPORT void EndRendering( GraphicsContext& context );

    
    };

}