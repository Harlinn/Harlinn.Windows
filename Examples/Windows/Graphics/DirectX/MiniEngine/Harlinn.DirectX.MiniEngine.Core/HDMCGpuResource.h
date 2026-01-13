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

    class GpuResource 
    {
        friend class CommandContext;
        friend class GraphicsContext;
        friend class ComputeContext;
    protected:
        D3D12Resource m_pResource;
        D3D12_RESOURCE_STATES m_UsageState = D3D12_RESOURCE_STATE_COMMON;
        D3D12_RESOURCE_STATES m_TransitioningState = ( D3D12_RESOURCE_STATES )-1;
        D3D12_GPU_VIRTUAL_ADDRESS m_GpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;

        // Used to identify when a resource changes so descriptors can be copied etc.
        uint32_t m_VersionID = 0;
    public:

        GpuResource( ) 
        {
        }

        explicit GpuResource( const D3D12Resource& pResource, D3D12_RESOURCE_STATES CurrentState = D3D12_RESOURCE_STATE_COMMON, bool addRef = false )
            : m_pResource( pResource ),
              m_UsageState( CurrentState )
        {
        }

        ~GpuResource( ) 
        { 
            Destroy( ); 
        }

        virtual void Destroy( )
        {
            m_pResource.ResetPtr( );
            m_GpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;
            ++m_VersionID;
        }

        void Map( UINT subResource, _In_opt_ const D3D12_RANGE* readRange, _Outptr_opt_result_bytebuffer_( _Inexpressible_( "Dependent on resource" ) )  void** ppData ) const
        {
            m_pResource.Map( subResource, readRange, ppData );
        }

        void Unmap( UINT subresource, _In_opt_  const D3D12_RANGE* pWrittenRange ) const
        {
            m_pResource.Unmap( subresource, pWrittenRange );
        }

        D3D12_RESOURCE_DESC GetDesc( ) const
        {
            return m_pResource.GetDesc( );
        }

        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress( ) const
        {
            return m_pResource.GetGPUVirtualAddress( );
        }

        void WriteToSubresource( UINT DstSubresource, _In_opt_ const D3D12_BOX* pDstBox, _In_ const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch ) const
        {
            m_pResource.WriteToSubresource( DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch );
        }

        void ReadFromSubresource( _Out_ void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, _In_opt_ const D3D12_BOX* pSrcBox ) const
        {
            m_pResource.ReadFromSubresource( pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox );
        }

        void GetHeapProperties( _Out_opt_ D3D12_HEAP_PROPERTIES* pHeapProperties, _Out_opt_ D3D12_HEAP_FLAGS* pHeapFlags ) const
        {
            m_pResource.GetHeapProperties( pHeapProperties, pHeapFlags );
        }
        

        D3D12Resource& GetResource( ) noexcept
        { 
            return m_pResource; 
        }
        const D3D12Resource& GetResource( ) const noexcept
        { 
            return m_pResource; 
        }

        D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress( ) const noexcept
        { 
            return m_GpuVirtualAddress; 
        }

        uint32_t GetVersionID( ) const 
        { 
            return m_VersionID; 
        }

    
    };
}