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

#include "HDMCDescriptorHeap.h"
#include "HDMCRootSignature.h"


namespace Harlinn::Windows::DirectX::MiniEngine
{
    class CommandContext;
    namespace Graphics
    {
        HDMC_EXPORT extern D3D12Device g_Device;
    }

    // This class is a linear allocation system for dynamically generated descriptor tables.  It internally caches
    // CPU descriptor handles so that when not enough space is available in the current heap, necessary descriptors
    // can be re-copied to the new heap.
    class DynamicDescriptorHeap
    {
    private:

        // Static members
        static const uint32_t kNumDescriptorsPerHeap = 1024;
        static std::mutex sm_Mutex;
        static std::vector<D3D12DescriptorHeap> sm_DescriptorHeapPool[ 2 ];
        static std::queue<std::pair<uint64_t, D3D12DescriptorHeap>> sm_RetiredDescriptorHeaps[ 2 ];
        static std::queue<D3D12DescriptorHeap> sm_AvailableDescriptorHeaps[ 2 ];

        // Non-static members
        CommandContext& m_OwningContext;
        D3D12DescriptorHeap m_CurrentHeapPtr;
        const D3D12_DESCRIPTOR_HEAP_TYPE m_DescriptorType;
        uint32_t m_DescriptorSize;
        uint32_t m_CurrentOffset;
        DescriptorHandle m_FirstDescriptor;
        std::vector<D3D12DescriptorHeap> m_RetiredHeaps;

        // Describes a descriptor table entry:  a region of the handle cache and which handles have been set
        struct DescriptorTableCache
        {
            DescriptorTableCache( ) : AssignedHandlesBitMap( 0 ) {}
            uint32_t AssignedHandlesBitMap;
            D3D12_CPU_DESCRIPTOR_HANDLE* TableStart;
            uint32_t TableSize;
        };

        struct DescriptorHandleCache
        {
            DescriptorHandleCache( )
            {
                ClearCache( );
            }

            void ClearCache( )
            {
                m_RootDescriptorTablesBitMap = 0;
                m_StaleRootParamsBitMap = 0;
                m_MaxCachedDescriptors = 0;
            }

            uint32_t m_RootDescriptorTablesBitMap;
            uint32_t m_StaleRootParamsBitMap;
            uint32_t m_MaxCachedDescriptors;

            static const uint32_t kMaxNumDescriptors = 256;
            static const uint32_t kMaxNumDescriptorTables = 16;

            HDMC_EXPORT uint32_t ComputeStagedSize( );
            HDMC_EXPORT void CopyAndBindStaleTables( D3D12_DESCRIPTOR_HEAP_TYPE Type, uint32_t DescriptorSize, DescriptorHandle DestHandleStart, const D3D12GraphicsCommandList& CmdList,
                void ( STDMETHODCALLTYPE ID3D12GraphicsCommandList::* SetFunc )( UINT, D3D12_GPU_DESCRIPTOR_HANDLE ) );

            DescriptorTableCache m_RootDescriptorTable[ kMaxNumDescriptorTables ];
            D3D12_CPU_DESCRIPTOR_HANDLE m_HandleCache[ kMaxNumDescriptors ];

            HDMC_EXPORT void UnbindAllValid( );
            HDMC_EXPORT void StageDescriptorHandles( UINT RootIndex, UINT Offset, UINT NumHandles, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] );
            HDMC_EXPORT void ParseRootSignature( D3D12_DESCRIPTOR_HEAP_TYPE Type, const RootSignature& RootSig );
        };

        DescriptorHandleCache m_GraphicsHandleCache;
        DescriptorHandleCache m_ComputeHandleCache;

    public:
        HDMC_EXPORT DynamicDescriptorHeap( CommandContext& OwningContext, D3D12_DESCRIPTOR_HEAP_TYPE HeapType );
        HDMC_EXPORT ~DynamicDescriptorHeap( );

        static void DestroyAll( void )
        {
            sm_DescriptorHeapPool[ 0 ].clear( );
            sm_DescriptorHeapPool[ 1 ].clear( );
        }

        HDMC_EXPORT void CleanupUsedHeaps( uint64_t fenceValue );

        // Copy multiple handles into the cache area reserved for the specified root parameter.
        void SetGraphicsDescriptorHandles( UINT RootIndex, UINT Offset, UINT NumHandles, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_GraphicsHandleCache.StageDescriptorHandles( RootIndex, Offset, NumHandles, Handles );
        }

        void SetComputeDescriptorHandles( UINT RootIndex, UINT Offset, UINT NumHandles, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_ComputeHandleCache.StageDescriptorHandles( RootIndex, Offset, NumHandles, Handles );
        }

        // Bypass the cache and upload directly to the shader-visible heap
        HDMC_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE UploadDirect( D3D12_CPU_DESCRIPTOR_HANDLE Handles );

        // Deduce cache layout needed to support the descriptor tables needed by the root signature.
        void ParseGraphicsRootSignature( const RootSignature& RootSig )
        {
            m_GraphicsHandleCache.ParseRootSignature( m_DescriptorType, RootSig );
        }

        void ParseComputeRootSignature( const RootSignature& RootSig )
        {
            m_ComputeHandleCache.ParseRootSignature( m_DescriptorType, RootSig );
        }

        // Upload any new descriptors in the cache to the shader-visible heap.
        inline void CommitGraphicsRootDescriptorTables( const D3D12GraphicsCommandList& CmdList )
        {
            if ( m_GraphicsHandleCache.m_StaleRootParamsBitMap != 0 )
            {
                CopyAndBindStagedTables( m_GraphicsHandleCache, CmdList, &ID3D12GraphicsCommandList::SetGraphicsRootDescriptorTable );
            }
        }

        inline void CommitComputeRootDescriptorTables( const D3D12GraphicsCommandList& CmdList )
        {
            if ( m_ComputeHandleCache.m_StaleRootParamsBitMap != 0 )
            {
                CopyAndBindStagedTables( m_ComputeHandleCache, CmdList, &ID3D12GraphicsCommandList::SetComputeRootDescriptorTable );
            }
        }

    
    private:
        // Static methods
        static D3D12DescriptorHeap RequestDescriptorHeap( D3D12_DESCRIPTOR_HEAP_TYPE HeapType );
        static void DiscardDescriptorHeaps( D3D12_DESCRIPTOR_HEAP_TYPE HeapType, uint64_t FenceValueForReset, const std::vector<D3D12DescriptorHeap>& UsedHeaps );

        bool HasSpace( uint32_t Count )
        {
            return ( m_CurrentHeapPtr != nullptr && m_CurrentOffset + Count <= kNumDescriptorsPerHeap );
        }

        HDMC_EXPORT void RetireCurrentHeap( void );
        HDMC_EXPORT void RetireUsedHeaps( uint64_t fenceValue );
        HDMC_EXPORT D3D12DescriptorHeap GetHeapPointer( );

        DescriptorHandle Allocate( UINT Count )
        {
            DescriptorHandle ret = m_FirstDescriptor + m_CurrentOffset * m_DescriptorSize;
            m_CurrentOffset += Count;
            return ret;
        }

        HDMC_EXPORT void CopyAndBindStagedTables( DescriptorHandleCache& HandleCache, const D3D12GraphicsCommandList& CmdList,
            void ( STDMETHODCALLTYPE ID3D12GraphicsCommandList::* SetFunc )( UINT, D3D12_GPU_DESCRIPTOR_HANDLE ) );

        // Mark all descriptors in the cache as stale and in need of re-uploading.
        HDMC_EXPORT void UnbindAllValid( void );

    };
}