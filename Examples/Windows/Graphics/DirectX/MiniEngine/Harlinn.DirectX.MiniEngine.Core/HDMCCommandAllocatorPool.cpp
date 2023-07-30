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
#include "HDMCCommandAllocatorPool.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    CommandAllocatorPool::CommandAllocatorPool( D3D12_COMMAND_LIST_TYPE Type ) :
        m_cCommandListType( Type )
    {
    }

    CommandAllocatorPool::~CommandAllocatorPool( )
    {
        Shutdown( );
    }

    void CommandAllocatorPool::Create( const D3D12Device& pDevice )
    {
        m_Device = pDevice;
    }

    void CommandAllocatorPool::Shutdown( )
    {
        m_AllocatorPool.clear( );
    }

    D3D12CommandAllocator CommandAllocatorPool::RequestAllocator( uint64_t CompletedFenceValue )
    {
        std::lock_guard<std::mutex> LockGuard( m_AllocatorMutex );

        D3D12CommandAllocator pAllocator;

        if ( !m_ReadyAllocators.empty( ) )
        {
            std::pair<uint64_t, D3D12CommandAllocator>& AllocatorPair = m_ReadyAllocators.front( );

            if ( AllocatorPair.first <= CompletedFenceValue )
            {
                pAllocator = AllocatorPair.second;
                pAllocator.Reset( );
                m_ReadyAllocators.pop( );
            }
        }

        // If no allocator's were ready to be reused, create a new one
        if ( pAllocator == nullptr )
        {
            pAllocator = m_Device.CreateCommandAllocator( m_cCommandListType );
            wchar_t AllocatorName[ 32 ];
            swprintf( AllocatorName, 32, L"CommandAllocator %zu", m_AllocatorPool.size( ) );
            pAllocator.SetName( AllocatorName );
            m_AllocatorPool.push_back( pAllocator );
        }

        return pAllocator;
    }

    void CommandAllocatorPool::DiscardAllocator( uint64_t FenceValue, const D3D12CommandAllocator& Allocator )
    {
        std::lock_guard<std::mutex> LockGuard( m_AllocatorMutex );

        // That fence value indicates we are free to reset the allocator
        m_ReadyAllocators.push( std::make_pair( FenceValue, Allocator ) );
    }
}