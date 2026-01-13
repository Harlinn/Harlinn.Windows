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
// Author(s):  James Stanard
//             Alex Nankervis
//

#include "pch.h"
#include "HDMCSamplerManager.h"
#include "HDMCGraphicsCore.h"
#include "HDMCHash.h"
#include <map>

namespace Harlinn::Windows::DirectX::MiniEngine
{

    using namespace Graphics;

    namespace
    {
        std::map< size_t, D3D12_CPU_DESCRIPTOR_HANDLE > s_SamplerCache;
    }

    D3D12_CPU_DESCRIPTOR_HANDLE SamplerDesc::CreateDescriptor( )
    {
        size_t hashValue = Utility::HashState( this );
        auto iter = s_SamplerCache.find( hashValue );
        if ( iter != s_SamplerCache.end( ) )
        {
            return iter->second;
        }

        D3D12_CPU_DESCRIPTOR_HANDLE Handle = AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER );
        g_Device.CreateSampler( this, Handle );
        return Handle;
    }

    void SamplerDesc::CreateDescriptor( D3D12_CPU_DESCRIPTOR_HANDLE Handle )
    {
        ASSERT( Handle.ptr != 0 && Handle.ptr != -1 );
        g_Device.CreateSampler( this, Handle );
    }

}