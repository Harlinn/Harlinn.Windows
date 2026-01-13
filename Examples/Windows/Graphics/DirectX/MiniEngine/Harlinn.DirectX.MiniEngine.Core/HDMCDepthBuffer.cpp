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
#include "HDMCDepthBuffer.h"
#include "HDMCGraphicsCore.h"
#include "HDMCDescriptorHeap.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    using namespace Graphics;

    void DepthBuffer::Create( const std::wstring& Name, uint32_t Width, uint32_t Height, DXGI_FORMAT Format, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr )
    {
        Create( Name, Width, Height, 1, Format, VidMemPtr );
    }

    void DepthBuffer::Create( const std::wstring& Name, uint32_t Width, uint32_t Height, uint32_t Samples, DXGI_FORMAT Format, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr )
    {
        D3D12_RESOURCE_DESC ResourceDesc = DescribeTex2D( Width, Height, 1, 1, Format, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL );
        ResourceDesc.SampleDesc.Count = Samples;

        D3D12_CLEAR_VALUE ClearValue = {};
        ClearValue.Format = Format;
        CreateTextureResource( Graphics::g_Device, Name, ResourceDesc, ClearValue, VidMemPtr );
        CreateDerivedViews( Graphics::g_Device, Format );
    }

    


    void DepthBuffer::CreateDerivedViews( const D3D12Device& Device, DXGI_FORMAT Format )
    {
        const auto& Resource = m_pResource;

        D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
        dsvDesc.Format = GetDSVFormat( Format );
        if ( Resource.GetDesc( ).SampleDesc.Count == 1 )
        {
            dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
            dsvDesc.Texture2D.MipSlice = 0;
        }
        else
        {
            dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
        }

        if ( m_hDSV[ 0 ].ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_hDSV[ 0 ] = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
            m_hDSV[ 1 ] = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
        }

        dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
        Device.CreateDepthStencilView( Resource, &dsvDesc, m_hDSV[ 0 ] );

        dsvDesc.Flags = D3D12_DSV_FLAG_READ_ONLY_DEPTH;
        Device.CreateDepthStencilView( Resource, &dsvDesc, m_hDSV[ 1 ] );

        DXGI_FORMAT stencilReadFormat = GetStencilFormat( Format );
        if ( stencilReadFormat != DXGI_FORMAT_UNKNOWN )
        {
            if ( m_hDSV[ 2 ].ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
            {
                m_hDSV[ 2 ] = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
                m_hDSV[ 3 ] = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
            }

            dsvDesc.Flags = D3D12_DSV_FLAG_READ_ONLY_STENCIL;
            Device.CreateDepthStencilView( Resource, &dsvDesc, m_hDSV[ 2 ] );

            dsvDesc.Flags = D3D12_DSV_FLAG_READ_ONLY_DEPTH | D3D12_DSV_FLAG_READ_ONLY_STENCIL;
            Device.CreateDepthStencilView( Resource, &dsvDesc, m_hDSV[ 3 ] );
        }
        else
        {
            m_hDSV[ 2 ] = m_hDSV[ 0 ];
            m_hDSV[ 3 ] = m_hDSV[ 1 ];
        }

        if ( m_hDepthSRV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
            m_hDepthSRV = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

        // Create the shader resource view
        D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
        SRVDesc.Format = GetDepthFormat( Format );
        if ( dsvDesc.ViewDimension == D3D12_DSV_DIMENSION_TEXTURE2D )
        {
            SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            SRVDesc.Texture2D.MipLevels = 1;
        }
        else
        {
            SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
        }
        SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        Device.CreateShaderResourceView( Resource, &SRVDesc, m_hDepthSRV );

        if ( stencilReadFormat != DXGI_FORMAT_UNKNOWN )
        {
            if ( m_hStencilSRV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
                m_hStencilSRV = Graphics::AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

            SRVDesc.Format = stencilReadFormat;
            Device.CreateShaderResourceView( Resource, &SRVDesc, m_hStencilSRV );
        }
    }
}