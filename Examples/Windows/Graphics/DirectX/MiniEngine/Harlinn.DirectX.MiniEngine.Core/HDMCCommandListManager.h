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

#include "HDMCCommandAllocatorPool.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    class CommandQueue
    {
        friend class CommandListManager;
        friend class CommandContext;

        D3D12CommandQueue m_CommandQueue;

        const D3D12_COMMAND_LIST_TYPE m_Type;

        CommandAllocatorPool m_AllocatorPool;
        std::mutex m_FenceMutex;
        std::mutex m_EventMutex;

        // Lifetime of these objects is managed by the descriptor cache
        D3D12Fence m_pFence;
        uint64_t m_NextFenceValue;
        uint64_t m_LastCompletedFenceValue;
        HANDLE m_FenceEventHandle;
    public:
        HDMC_EXPORT CommandQueue( D3D12_COMMAND_LIST_TYPE Type );
        HDMC_EXPORT ~CommandQueue( );

        HDMC_EXPORT void Create( const D3D12Device& pDevice );
        HDMC_EXPORT void Shutdown( );

        inline bool IsReady( )
        {
            return m_CommandQueue != nullptr;
        }

        HDMC_EXPORT uint64_t IncrementFence( );
        HDMC_EXPORT bool IsFenceComplete( uint64_t FenceValue );
        HDMC_EXPORT void StallForFence( uint64_t FenceValue );
        HDMC_EXPORT void StallForProducer( CommandQueue& Producer );
        HDMC_EXPORT void WaitForFence( uint64_t FenceValue );
        void WaitForIdle( void ) { WaitForFence( IncrementFence( ) ); }

        const D3D12CommandQueue& GetCommandQueue( ) { return m_CommandQueue; }

        uint64_t GetNextFenceValue( ) { return m_NextFenceValue; }

    private:
        HDMC_EXPORT uint64_t ExecuteCommandList( const D3D12GraphicsCommandList& List );
        HDMC_EXPORT D3D12CommandAllocator RequestAllocator( );
        HDMC_EXPORT void DiscardAllocator( uint64_t FenceValueForReset, const D3D12CommandAllocator& Allocator );
    };

    class CommandListManager
    {
        friend class CommandContext;
    private:
        D3D12Device m_Device;

        CommandQueue m_GraphicsQueue;
        CommandQueue m_ComputeQueue;
        CommandQueue m_CopyQueue;
    public:
        HDMC_EXPORT CommandListManager( );
        HDMC_EXPORT ~CommandListManager( );

        HDMC_EXPORT void Create( const D3D12Device& pDevice );
        HDMC_EXPORT void Shutdown( );

        CommandQueue& GetGraphicsQueue( void ) { return m_GraphicsQueue; }
        CommandQueue& GetComputeQueue( void ) { return m_ComputeQueue; }
        CommandQueue& GetCopyQueue( void ) { return m_CopyQueue; }

        CommandQueue& GetQueue( D3D12_COMMAND_LIST_TYPE Type = D3D12_COMMAND_LIST_TYPE_DIRECT )
        {
            switch ( Type )
            {
                case D3D12_COMMAND_LIST_TYPE_COMPUTE: return m_ComputeQueue;
                case D3D12_COMMAND_LIST_TYPE_COPY: return m_CopyQueue;
                default: return m_GraphicsQueue;
            }
        }

        const D3D12CommandQueue& GetCommandQueue( )
        {
            return m_GraphicsQueue.GetCommandQueue( );
        }

        HDMC_EXPORT void CreateNewCommandList(
            D3D12_COMMAND_LIST_TYPE Type,
            D3D12GraphicsCommandList* List,
            D3D12CommandAllocator* Allocator );

        // Test to see if a fence has already been reached
        bool IsFenceComplete( uint64_t FenceValue )
        {
            return GetQueue( D3D12_COMMAND_LIST_TYPE( FenceValue >> 56 ) ).IsFenceComplete( FenceValue );
        }

        // The CPU will wait for a fence to reach a specified value
        HDMC_EXPORT void WaitForFence( uint64_t FenceValue );

        // The CPU will wait for all command queues to empty (so that the GPU is idle)
        void IdleGPU( void )
        {
            m_GraphicsQueue.WaitForIdle( );
            m_ComputeQueue.WaitForIdle( );
            m_CopyQueue.WaitForIdle( );
        }
    };
}