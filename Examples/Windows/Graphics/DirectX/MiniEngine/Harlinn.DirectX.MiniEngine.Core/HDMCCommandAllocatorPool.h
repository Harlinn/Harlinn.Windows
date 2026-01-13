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