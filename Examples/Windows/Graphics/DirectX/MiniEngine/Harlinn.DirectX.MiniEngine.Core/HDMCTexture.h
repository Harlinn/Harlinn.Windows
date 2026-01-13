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

#include "HDMCDef.h"
#include "HDMCGpuResource.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class Texture : public GpuResource
    {
        friend class CommandContext;

    public:

        Texture( ) { m_hCpuDescriptorHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN; }
        Texture( D3D12_CPU_DESCRIPTOR_HANDLE Handle ) : m_hCpuDescriptorHandle( Handle ) {}

        // Create a 1-level textures
        void Create2D( size_t RowPitchBytes, size_t Width, size_t Height, DXGI_FORMAT Format, const void* InitData );
        void CreateCube( size_t RowPitchBytes, size_t Width, size_t Height, DXGI_FORMAT Format, const void* InitialData );

        void CreateTGAFromMemory( const void* memBuffer, size_t fileSize, bool sRGB );
        bool CreateDDSFromMemory( const void* memBuffer, size_t fileSize, bool sRGB );
        void CreatePIXImageFromMemory( const void* memBuffer, size_t fileSize );

        virtual void Destroy( ) override
        {
            GpuResource::Destroy( );
            m_hCpuDescriptorHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
        }

        const D3D12_CPU_DESCRIPTOR_HANDLE& GetSRV( ) const { return m_hCpuDescriptorHandle; }

        uint32_t GetWidth( ) const { return m_Width; }
        uint32_t GetHeight( ) const { return m_Height; }
        uint32_t GetDepth( ) const { return m_Depth; }

    protected:

        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Depth;

        D3D12_CPU_DESCRIPTOR_HANDLE m_hCpuDescriptorHandle;
    };

}