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

#include "HDMCPipelineState.h"
#include "HDMCDescriptorHeap.h"
#include "HDMCRootSignature.h"
#include "HDMCGraphicsCommon.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandListManager;
    class ContextManager;

    namespace Graphics
    {
#ifndef RELEASE
        HDMC_EXPORT extern const GUID WKPDID_D3DDebugObjectName;
#endif


        HDMC_EXPORT void Initialize( bool RequireDXRSupport = false );
        HDMC_EXPORT void Shutdown( void );

        HDMC_EXPORT bool IsDeviceNvidia( ID3D12Device* pDevice );
        HDMC_EXPORT bool IsDeviceAMD( ID3D12Device* pDevice );
        HDMC_EXPORT bool IsDeviceIntel( ID3D12Device* pDevice );

        HDMC_EXPORT extern D3D12Device g_Device;
        HDMC_EXPORT extern CommandListManager g_CommandManager;
        HDMC_EXPORT extern ContextManager g_ContextManager;

        HDMC_EXPORT extern D3D_FEATURE_LEVEL g_D3DFeatureLevel;
        HDMC_EXPORT extern bool g_bTypedUAVLoadSupport_R11G11B10_FLOAT;
        HDMC_EXPORT extern bool g_bTypedUAVLoadSupport_R16G16B16A16_FLOAT;

        HDMC_EXPORT extern DescriptorAllocator g_DescriptorAllocator[ ];
        inline D3D12_CPU_DESCRIPTOR_HANDLE AllocateDescriptor( D3D12_DESCRIPTOR_HEAP_TYPE Type, UINT Count = 1 )
        {
            return g_DescriptorAllocator[ Type ].Allocate( Count );
        }
    }
}