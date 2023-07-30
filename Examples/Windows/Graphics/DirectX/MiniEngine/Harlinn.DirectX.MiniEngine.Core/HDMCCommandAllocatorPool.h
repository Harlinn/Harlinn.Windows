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

    class CommandAllocatorPool
    {
    public:
        CommandAllocatorPool( D3D12_COMMAND_LIST_TYPE Type );
        ~CommandAllocatorPool( );

        void Create( const D3D12Device& device );
        void Shutdown( );

        D3D12CommandAllocator RequestAllocator( uint64_t CompletedFenceValue );
        void DiscardAllocator( uint64_t FenceValue, const D3D12CommandAllocator& Allocator );

        inline size_t Size( ) { return m_AllocatorPool.size( ); }

    private:
        const D3D12_COMMAND_LIST_TYPE m_cCommandListType;

        D3D12Device m_Device;
        std::vector<D3D12CommandAllocator> m_AllocatorPool;
        std::queue<std::pair<uint64_t, D3D12CommandAllocator>> m_ReadyAllocators;
        std::mutex m_AllocatorMutex;
    };
}