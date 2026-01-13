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

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    // This is an unbounded resource descriptor allocator.  It is intended to provide space for CPU-visible
    // resource descriptors as resources are created.  For those that need to be made shader-visible, they
    // will need to be copied to a DescriptorHeap or a DynamicDescriptorHeap.
    class DescriptorAllocator
    {
    protected:

        static const uint32_t sm_NumDescriptorsPerHeap = 256;
        static std::mutex sm_AllocationMutex;
        static std::vector<D3D12DescriptorHeap> sm_DescriptorHeapPool;
        HDMC_EXPORT static D3D12DescriptorHeap RequestNewHeap( D3D12_DESCRIPTOR_HEAP_TYPE Type );

        D3D12_DESCRIPTOR_HEAP_TYPE m_Type;
        D3D12DescriptorHeap m_CurrentHeap;
        D3D12_CPU_DESCRIPTOR_HANDLE m_CurrentHandle;
        uint32_t m_DescriptorSize;
        uint32_t m_RemainingFreeHandles;
    public:
        DescriptorAllocator( D3D12_DESCRIPTOR_HEAP_TYPE Type ) 
            : m_Type( Type ), m_CurrentHeap( nullptr ), m_DescriptorSize( 0 )
        {
            m_CurrentHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
        }

        HDMC_EXPORT D3D12_CPU_DESCRIPTOR_HANDLE Allocate( uint32_t Count );

        HDMC_EXPORT static void DestroyAll( void );

    
    };

    // This handle refers to a descriptor or a descriptor table (contiguous descriptors) that is shader visible.
    class DescriptorHandle
    {
    private:
        D3D12_CPU_DESCRIPTOR_HANDLE m_CpuHandle;
        D3D12_GPU_DESCRIPTOR_HANDLE m_GpuHandle;
    public:
        DescriptorHandle( )
        {
            m_CpuHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
            m_GpuHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
        }

        /*
        // Should we allow constructing handles that might not be shader visible?
        DescriptorHandle( D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle )
            : m_CpuHandle(CpuHandle)
        {
            m_GpuHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
        }
        */

        DescriptorHandle( D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle )
            : m_CpuHandle( CpuHandle ), m_GpuHandle( GpuHandle )
        {
        }

        DescriptorHandle operator+ ( INT OffsetScaledByDescriptorSize ) const
        {
            DescriptorHandle ret = *this;
            ret += OffsetScaledByDescriptorSize;
            return ret;
        }

        void operator += ( INT OffsetScaledByDescriptorSize )
        {
            if ( m_CpuHandle.ptr != D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
                m_CpuHandle.ptr += OffsetScaledByDescriptorSize;
            if ( m_GpuHandle.ptr != D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN )
                m_GpuHandle.ptr += OffsetScaledByDescriptorSize;
        }

        const D3D12_CPU_DESCRIPTOR_HANDLE* operator&( ) const { return &m_CpuHandle; }
        operator D3D12_CPU_DESCRIPTOR_HANDLE( ) const { return m_CpuHandle; }
        operator D3D12_GPU_DESCRIPTOR_HANDLE( ) const { return m_GpuHandle; }

        size_t GetCpuPtr( ) const { return m_CpuHandle.ptr; }
        uint64_t GetGpuPtr( ) const { return m_GpuHandle.ptr; }
        bool IsNull( ) const { return m_CpuHandle.ptr == D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN; }
        bool IsShaderVisible( ) const { return m_GpuHandle.ptr != D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN; }

    
    };

    class DescriptorHeap
    {
    private:
        D3D12DescriptorHeap m_Heap;
        D3D12_DESCRIPTOR_HEAP_DESC m_HeapDesc;
        uint32_t m_DescriptorSize;
        uint32_t m_NumFreeDescriptors;
        DescriptorHandle m_FirstHandle;
        DescriptorHandle m_NextFreeHandle;
    public:

        DescriptorHeap( void ) {}
        ~DescriptorHeap( void ) { Destroy( ); }

        HDMC_EXPORT void Create( const std::wstring& DebugHeapName, D3D12_DESCRIPTOR_HEAP_TYPE Type, uint32_t MaxCount );
        void Destroy( void ) { m_Heap.ResetPtr(); }

        bool HasAvailableSpace( uint32_t Count ) const { return Count <= m_NumFreeDescriptors; }
        HDMC_EXPORT DescriptorHandle Alloc( uint32_t Count = 1 );

        DescriptorHandle operator[] ( uint32_t arrayIdx ) const { return m_FirstHandle + arrayIdx * m_DescriptorSize; }

        uint32_t GetOffsetOfHandle( const DescriptorHandle& DHandle )
        {
            return ( uint32_t )( DHandle.GetCpuPtr( ) - m_FirstHandle.GetCpuPtr( ) ) / m_DescriptorSize;
        }

        HDMC_EXPORT bool ValidateHandle( const DescriptorHandle& DHandle ) const;

        const D3D12DescriptorHeap& GetHeapPointer( ) const 
        { 
            return m_Heap; 
        }

        uint32_t GetDescriptorSize( void ) const 
        { 
            return m_DescriptorSize; 
        }

    
    };
}