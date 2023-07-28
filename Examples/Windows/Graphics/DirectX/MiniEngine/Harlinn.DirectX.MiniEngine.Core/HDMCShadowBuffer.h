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

    class EsramAllocator;

    class GraphicsContext;

    class ShadowBuffer : public DepthBuffer
    {
    public:
        ShadowBuffer( ) {}

        HDMC_EXPORT void Create( const std::wstring& Name, uint32_t Width, uint32_t Height,
            D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN );
        HDMC_EXPORT void Create( const std::wstring& Name, uint32_t Width, uint32_t Height, EsramAllocator& Allocator );

        D3D12_CPU_DESCRIPTOR_HANDLE GetSRV( ) const { return GetDepthSRV( ); }

        HDMC_EXPORT void BeginRendering( GraphicsContext& context );
        HDMC_EXPORT void EndRendering( GraphicsContext& context );

    private:
        D3D12_VIEWPORT m_Viewport;
        D3D12_RECT m_Scissor;
    };

}