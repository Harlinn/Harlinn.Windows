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

#include "pch.h"
#include "HDMCGpuResource.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandContext;
    class EsramAllocator;
    class UploadBuffer;

    class GpuBuffer : public GpuResource
    {
    protected:
        D3D12_CPU_DESCRIPTOR_HANDLE m_UAV = {.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN };
        D3D12_CPU_DESCRIPTOR_HANDLE m_SRV = {.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN };

        size_t m_BufferSize = 0;
        uint32_t m_ElementCount = 0;
        uint32_t m_ElementSize = 0;
        D3D12_RESOURCE_FLAGS m_ResourceFlags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    protected:
        GpuBuffer( ) 
        {
        }
    public:
        virtual ~GpuBuffer( ) 
        { 
            Destroy( );
        }

        // Create a buffer.  If initial data is provided, it will be copied into the buffer using the default command context.
        HDMC_EXPORT void Create( const std::wstring& name, uint32_t NumElements, uint32_t ElementSize, const void* initialData = nullptr );

        HDMC_EXPORT void Create( const std::wstring& name, uint32_t NumElements, uint32_t ElementSize, const UploadBuffer& srcData, uint32_t srcOffset = 0 );

        // Sub-Allocate a buffer out of a pre-allocated heap.  If initial data is provided, it will be copied into the buffer using the default command context.
        HDMC_EXPORT void CreatePlaced( const std::wstring& name, const D3D12Heap& pBackingHeap, uint32_t HeapOffset, uint32_t NumElements, uint32_t ElementSize, const void* initialData = nullptr );

        const D3D12_CPU_DESCRIPTOR_HANDLE& GetUAV( void ) const 
        { 
            return m_UAV; 
        }
        const D3D12_CPU_DESCRIPTOR_HANDLE& GetSRV( void ) const 
        { 
            return m_SRV; 
        }

        D3D12_GPU_VIRTUAL_ADDRESS RootConstantBufferView( void ) const 
        { 
            return m_GpuVirtualAddress; 
        }

        HDMC_EXPORT D3D12_CPU_DESCRIPTOR_HANDLE CreateConstantBufferView( uint32_t Offset, uint32_t Size ) const;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView( size_t Offset, uint32_t Size, uint32_t Stride ) const
        {
            D3D12_VERTEX_BUFFER_VIEW VBView;
            VBView.BufferLocation = m_GpuVirtualAddress + Offset;
            VBView.SizeInBytes = Size;
            VBView.StrideInBytes = Stride;
            return VBView;
        }

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView( size_t BaseVertexIndex = 0 ) const
        {
            size_t Offset = BaseVertexIndex * m_ElementSize;
            return VertexBufferView( Offset, ( uint32_t )( m_BufferSize - Offset ), m_ElementSize );
        }

        D3D12_INDEX_BUFFER_VIEW IndexBufferView( size_t Offset, uint32_t Size, bool b32Bit = false ) const
        {
            D3D12_INDEX_BUFFER_VIEW IBView;
            IBView.BufferLocation = m_GpuVirtualAddress + Offset;
            IBView.Format = b32Bit ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
            IBView.SizeInBytes = Size;
            return IBView;
        }
        D3D12_INDEX_BUFFER_VIEW IndexBufferView( size_t StartIndex = 0 ) const
        {
            size_t Offset = StartIndex * m_ElementSize;
            return IndexBufferView( Offset, ( uint32_t )( m_BufferSize - Offset ), m_ElementSize == 4 );
        }

        size_t GetBufferSize( ) const 
        { 
            return m_BufferSize; 
        }
        uint32_t GetElementCount( ) const 
        { 
            return m_ElementCount; 
        }
        uint32_t GetElementSize( ) const 
        { 
            return m_ElementSize; 
        }

    
    protected:
        D3D12_RESOURCE_DESC DescribeBuffer( )
        {
            ASSERT( m_BufferSize != 0 );

            D3D12_RESOURCE_DESC Desc = {};
            Desc.Alignment = 0;
            Desc.DepthOrArraySize = 1;
            Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            Desc.Flags = m_ResourceFlags;
            Desc.Format = DXGI_FORMAT_UNKNOWN;
            Desc.Height = 1;
            Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            Desc.MipLevels = 1;
            Desc.SampleDesc.Count = 1;
            Desc.SampleDesc.Quality = 0;
            Desc.Width = ( UINT64 )m_BufferSize;
            return Desc;
        }
        virtual void CreateDerivedViews( void ) = 0;

        
    };

    class ByteAddressBuffer : public GpuBuffer
    {
    public:
        HDMC_EXPORT virtual void CreateDerivedViews( ) override;
    };

    class IndirectArgsBuffer : public ByteAddressBuffer
    {
    public:
        IndirectArgsBuffer( )
        {
        }
    };

    class StructuredBuffer : public GpuBuffer
    {
    private:
        ByteAddressBuffer m_CounterBuffer;
    public:
        virtual void Destroy( void ) override
        {
            m_CounterBuffer.Destroy( );
            GpuBuffer::Destroy( );
        }

        HDMC_EXPORT virtual void CreateDerivedViews( void ) override;

        ByteAddressBuffer& GetCounterBuffer( void ) { return m_CounterBuffer; }

        HDMC_EXPORT const D3D12_CPU_DESCRIPTOR_HANDLE& GetCounterSRV( CommandContext& Context );
        HDMC_EXPORT const D3D12_CPU_DESCRIPTOR_HANDLE& GetCounterUAV( CommandContext& Context );

    
    };

    class TypedBuffer : public GpuBuffer
    {
    protected:
        DXGI_FORMAT m_DataFormat;
    public:
        TypedBuffer( DXGI_FORMAT Format ) 
            : m_DataFormat( Format ) 
        {}

        HDMC_EXPORT virtual void CreateDerivedViews( void ) override;

    
    };

}