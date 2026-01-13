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

#include "HDMCSamplerManager.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class SamplerDesc;
    class CommandSignature;
    class RootSignature;
    class ComputePSO;
    class GraphicsPSO;

    namespace Graphics
    {
        HDMC_EXPORT void InitializeCommonState( void );
        HDMC_EXPORT void DestroyCommonState( void );

        HDMC_EXPORT extern SamplerDesc SamplerLinearWrapDesc;
        HDMC_EXPORT extern SamplerDesc SamplerAnisoWrapDesc;
        HDMC_EXPORT extern SamplerDesc SamplerShadowDesc;
        HDMC_EXPORT extern SamplerDesc SamplerLinearClampDesc;
        HDMC_EXPORT extern SamplerDesc SamplerVolumeWrapDesc;
        HDMC_EXPORT extern SamplerDesc SamplerPointClampDesc;
        HDMC_EXPORT extern SamplerDesc SamplerPointBorderDesc;
        HDMC_EXPORT extern SamplerDesc SamplerLinearBorderDesc;

        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearWrap;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerAnisoWrap;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerShadow;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearClamp;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerVolumeWrap;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerPointClamp;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerPointBorder;
        HDMC_EXPORT extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearBorder;

        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerDefault;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerDefaultMsaa;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerDefaultCw;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerDefaultCwMsaa;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerTwoSided;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerTwoSidedMsaa;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerShadow;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerShadowCW;
        HDMC_EXPORT extern D3D12_RASTERIZER_DESC RasterizerShadowTwoSided;

        HDMC_EXPORT extern D3D12_BLEND_DESC BlendNoColorWrite;		// XXX
        HDMC_EXPORT extern D3D12_BLEND_DESC BlendDisable;			// 1, 0
        HDMC_EXPORT extern D3D12_BLEND_DESC BlendPreMultiplied;		// 1, 1-SrcA
        HDMC_EXPORT extern D3D12_BLEND_DESC BlendTraditional;		// SrcA, 1-SrcA
        HDMC_EXPORT extern D3D12_BLEND_DESC BlendAdditive;			// 1, 1
        HDMC_EXPORT extern D3D12_BLEND_DESC BlendTraditionalAdditive;// SrcA, 1

        HDMC_EXPORT extern D3D12_DEPTH_STENCIL_DESC DepthStateDisabled;
        HDMC_EXPORT extern D3D12_DEPTH_STENCIL_DESC DepthStateReadWrite;
        HDMC_EXPORT extern D3D12_DEPTH_STENCIL_DESC DepthStateReadOnly;
        HDMC_EXPORT extern D3D12_DEPTH_STENCIL_DESC DepthStateReadOnlyReversed;
        HDMC_EXPORT extern D3D12_DEPTH_STENCIL_DESC DepthStateTestEqual;

        HDMC_EXPORT extern CommandSignature DispatchIndirectCommandSignature;
        HDMC_EXPORT extern CommandSignature DrawIndirectCommandSignature;

        enum eDefaultTexture
        {
            kMagenta2D,  // Useful for indicating missing textures
            kBlackOpaque2D,
            kBlackTransparent2D,
            kWhiteOpaque2D,
            kWhiteTransparent2D,
            kDefaultNormalMap,
            kBlackCubeMap,

            kNumDefaultTextures
        };
        HDMC_EXPORT D3D12_CPU_DESCRIPTOR_HANDLE GetDefaultTexture( eDefaultTexture texID );

        HDMC_EXPORT extern RootSignature g_CommonRS;
        HDMC_EXPORT extern ComputePSO g_GenerateMipsLinearPSO[ 4 ];
        HDMC_EXPORT extern ComputePSO g_GenerateMipsGammaPSO[ 4 ];
        HDMC_EXPORT extern GraphicsPSO g_DownsampleDepthPSO;
    }
}