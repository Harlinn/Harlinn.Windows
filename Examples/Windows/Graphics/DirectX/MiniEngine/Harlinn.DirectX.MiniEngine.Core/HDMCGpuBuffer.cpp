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
#include "pch.h"

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


#include "HDMCGpuBuffer.h"
#include "HDMCGraphicsCore.h"
#include "HDMCCommandContext.h"
#include "HDMCBufferManager.h"
#include "HDMCUploadBuffer.h"
#include "Math/HDMCCommon.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    using namespace Graphics;

    void GpuBuffer::Create( const std::wstring& name, uint32_t NumElements, uint32_t ElementSize, const void* initialData )
    {
        Destroy( );

        m_ElementCount = NumElements;
        m_ElementSize = ElementSize;
        m_BufferSize = NumElements * ElementSize;

        D3D12_RESOURCE_DESC ResourceDesc = DescribeBuffer( );

        m_UsageState = D3D12_RESOURCE_STATE_COMMON;

        D3D12_HEAP_PROPERTIES HeapProps;
        HeapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
        HeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        HeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        HeapProps.CreationNodeMask = 1;
        HeapProps.VisibleNodeMask = 1;

        m_pResource = g_Device.CreateCommittedResource( &HeapProps, D3D12_HEAP_FLAG_NONE, &ResourceDesc, m_UsageState, nullptr );

        m_GpuVirtualAddress = m_pResource.GetGPUVirtualAddress( );

        if ( initialData )
            CommandContext::InitializeBuffer( *this, initialData, m_BufferSize );

#ifdef RELEASE
        ( name );
#else
        m_pResource.SetName( name.c_str( ) );
#endif

        CreateDerivedViews( );
    }

    void GpuBuffer::Create( const std::wstring& name, uint32_t NumElements, uint32_t ElementSize, const UploadBuffer& srcData, uint32_t srcOffset )
    {
        Destroy( );

        m_ElementCount = NumElements;
        m_ElementSize = ElementSize;
        m_BufferSize = NumElements * ElementSize;

        D3D12_RESOURCE_DESC ResourceDesc = DescribeBuffer( );

        m_UsageState = D3D12_RESOURCE_STATE_COMMON;

        D3D12_HEAP_PROPERTIES HeapProps;
        HeapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
        HeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        HeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        HeapProps.CreationNodeMask = 1;
        HeapProps.VisibleNodeMask = 1;
        
        m_pResource = g_Device.CreateCommittedResource( &HeapProps, D3D12_HEAP_FLAG_NONE, &ResourceDesc, m_UsageState, nullptr );

        m_GpuVirtualAddress = m_pResource.GetGPUVirtualAddress( );

        CommandContext::InitializeBuffer( *this, srcData, srcOffset );

#ifdef RELEASE
        ( name );
#else
        m_pResource.SetName( name.c_str( ) );
#endif

        CreateDerivedViews( );
    }

    // Sub-Allocate a buffer out of a pre-allocated heap.  If initial data is provided, it will be copied into the buffer using the default command context.
    void GpuBuffer::CreatePlaced( const std::wstring& name, const D3D12Heap& pBackingHeap, uint32_t HeapOffset, uint32_t NumElements, uint32_t ElementSize,
        const void* initialData )
    {
        m_ElementCount = NumElements;
        m_ElementSize = ElementSize;
        m_BufferSize = NumElements * ElementSize;

        D3D12_RESOURCE_DESC ResourceDesc = DescribeBuffer( );

        m_UsageState = D3D12_RESOURCE_STATE_COMMON;

        m_pResource = g_Device.CreatePlacedResource( pBackingHeap, HeapOffset, &ResourceDesc, m_UsageState, nullptr );

        m_GpuVirtualAddress = m_pResource.GetGPUVirtualAddress( );

        if ( initialData )
        {
            CommandContext::InitializeBuffer( *this, initialData, m_BufferSize );
        }

#ifdef RELEASE
        ( name );
#else
        m_pResource.SetName( name.c_str( ) );
#endif

        CreateDerivedViews( );

    }

    D3D12_CPU_DESCRIPTOR_HANDLE GpuBuffer::CreateConstantBufferView( uint32_t Offset, uint32_t Size ) const
    {
        ASSERT( Offset + Size <= m_BufferSize );

        Size = Math::AlignUp( Size, 16 );

        D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc;
        CBVDesc.BufferLocation = m_GpuVirtualAddress + ( size_t )Offset;
        CBVDesc.SizeInBytes = Size;

        D3D12_CPU_DESCRIPTOR_HANDLE hCBV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        g_Device.CreateConstantBufferView( &CBVDesc, hCBV );
        return hCBV;
    }


    void ByteAddressBuffer::CreateDerivedViews( void )
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
        SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        SRVDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        SRVDesc.Buffer.NumElements = ( UINT )m_BufferSize / 4;
        SRVDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;

        if ( m_SRV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_SRV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateShaderResourceView( m_pResource, &SRVDesc, m_SRV );

        D3D12_UNORDERED_ACCESS_VIEW_DESC UAVDesc = {};
        UAVDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        UAVDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        UAVDesc.Buffer.NumElements = ( UINT )m_BufferSize / 4;
        UAVDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;

        if ( m_UAV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_UAV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateUnorderedAccessView( m_pResource, UAVDesc, m_UAV );
    }

    void StructuredBuffer::CreateDerivedViews( void )
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
        SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
        SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        SRVDesc.Buffer.NumElements = m_ElementCount;
        SRVDesc.Buffer.StructureByteStride = m_ElementSize;
        SRVDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

        if ( m_SRV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_SRV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateShaderResourceView( m_pResource, &SRVDesc, m_SRV );

        D3D12_UNORDERED_ACCESS_VIEW_DESC UAVDesc = {};
        UAVDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
        UAVDesc.Buffer.CounterOffsetInBytes = 0;
        UAVDesc.Buffer.NumElements = m_ElementCount;
        UAVDesc.Buffer.StructureByteStride = m_ElementSize;
        UAVDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

        m_CounterBuffer.Create( L"StructuredBuffer::Counter", 1, 4 );

        if ( m_UAV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_UAV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateUnorderedAccessView( m_pResource, m_CounterBuffer.GetResource( ), &UAVDesc, m_UAV );
    }

    void TypedBuffer::CreateDerivedViews( void )
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
        SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        SRVDesc.Format = m_DataFormat;
        SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        SRVDesc.Buffer.NumElements = m_ElementCount;
        SRVDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

        if ( m_SRV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_SRV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateShaderResourceView( m_pResource, &SRVDesc, m_SRV );

        D3D12_UNORDERED_ACCESS_VIEW_DESC UAVDesc = {};
        UAVDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        UAVDesc.Format = m_DataFormat;
        UAVDesc.Buffer.NumElements = m_ElementCount;
        UAVDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

        if ( m_UAV.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
        {
            m_UAV = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        }
        g_Device.CreateUnorderedAccessView( m_pResource, UAVDesc, m_UAV );
    }

    const D3D12_CPU_DESCRIPTOR_HANDLE& StructuredBuffer::GetCounterSRV( CommandContext& Context )
    {
        Context.TransitionResource( m_CounterBuffer, D3D12_RESOURCE_STATE_GENERIC_READ );
        return m_CounterBuffer.GetSRV( );
    }

    const D3D12_CPU_DESCRIPTOR_HANDLE& StructuredBuffer::GetCounterUAV( CommandContext& Context )
    {
        Context.TransitionResource( m_CounterBuffer, D3D12_RESOURCE_STATE_UNORDERED_ACCESS );
        return m_CounterBuffer.GetUAV( );
    }
}