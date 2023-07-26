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
#include "HDMCUploadBuffer.h"
#include "HDMCGraphicsCore.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    using namespace Graphics;

    void UploadBuffer::Create( const std::wstring& name, size_t BufferSize )
    {
        Destroy( );

        m_BufferSize = BufferSize;

        // Create an upload buffer.  This is CPU-visible, but it's write combined memory, so
        // avoid reading back from it.
        D3D12_HEAP_PROPERTIES HeapProps;
        HeapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
        HeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        HeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        HeapProps.CreationNodeMask = 1;
        HeapProps.VisibleNodeMask = 1;

        // Upload buffers must be 1-dimensional
        D3D12_RESOURCE_DESC ResourceDesc = {};
        ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        ResourceDesc.Width = m_BufferSize;
        ResourceDesc.Height = 1;
        ResourceDesc.DepthOrArraySize = 1;
        ResourceDesc.MipLevels = 1;
        ResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        ResourceDesc.SampleDesc.Count = 1;
        ResourceDesc.SampleDesc.Quality = 0;
        ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        ResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        g_Device.CreateCommittedResource( &HeapProps, D3D12_HEAP_FLAG_NONE, &ResourceDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, MY_IID_PPV_ARGS( &m_pResource ) );

        m_GpuVirtualAddress = m_pResource.GetGPUVirtualAddress( );

#ifdef RELEASE
        ( name );
#else
        m_pResource.SetName( name.c_str( ) );
#endif
    }


    void* UploadBuffer::Map( void )
    {
        void* Memory;
        CD3DX12_RANGE range( 0, m_BufferSize );
        m_pResource.Map( 0, &range, &Memory );
        return Memory;
    }

    void UploadBuffer::Unmap( size_t begin, size_t end )
    {
        CD3DX12_RANGE range( begin, std::min( end, m_BufferSize ) );
        m_pResource.Unmap( 0, &range );
    }
}