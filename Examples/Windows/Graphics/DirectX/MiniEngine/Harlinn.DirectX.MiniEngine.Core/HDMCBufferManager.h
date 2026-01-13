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

#include "HDMCColorBuffer.h"
#include "HDMCDepthBuffer.h"
#include "HDMCShadowBuffer.h"
#include "HDMCGpuBuffer.h"
#include "HDMCGraphicsCore.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Graphics
    {
        HDMC_EXPORT extern DepthBuffer g_SceneDepthBuffer;  // D32_FLOAT_S8_UINT
        HDMC_EXPORT extern ColorBuffer g_SceneColorBuffer;  // R11G11B10_FLOAT
        HDMC_EXPORT extern ColorBuffer g_SceneNormalBuffer; // R16G16B16A16_FLOAT
        HDMC_EXPORT extern ColorBuffer g_PostEffectsBuffer; // R32_UINT (to support Read-Modify-Write with a UAV)
        HDMC_EXPORT extern ColorBuffer g_OverlayBuffer;     // R8G8B8A8_UNORM
        HDMC_EXPORT extern ColorBuffer g_HorizontalBuffer;  // For separable (bicubic) upsampling

        HDMC_EXPORT extern ColorBuffer g_VelocityBuffer;    // R10G10B10  (3D velocity)
        HDMC_EXPORT extern ShadowBuffer g_ShadowBuffer;

        HDMC_EXPORT extern ColorBuffer g_SSAOFullScreen;	// R8_UNORM
        HDMC_EXPORT extern ColorBuffer g_LinearDepth[ 2 ];	// Normalized planar distance (0 at eye, 1 at far plane) computed from the SceneDepthBuffer
        HDMC_EXPORT extern ColorBuffer g_MinMaxDepth8;		// Min and max depth values of 8x8 tiles
        HDMC_EXPORT extern ColorBuffer g_MinMaxDepth16;		// Min and max depth values of 16x16 tiles
        HDMC_EXPORT extern ColorBuffer g_MinMaxDepth32;		// Min and max depth values of 16x16 tiles
        HDMC_EXPORT extern ColorBuffer g_DepthDownsize1;
        HDMC_EXPORT extern ColorBuffer g_DepthDownsize2;
        HDMC_EXPORT extern ColorBuffer g_DepthDownsize3;
        HDMC_EXPORT extern ColorBuffer g_DepthDownsize4;
        HDMC_EXPORT extern ColorBuffer g_DepthTiled1;
        HDMC_EXPORT extern ColorBuffer g_DepthTiled2;
        HDMC_EXPORT extern ColorBuffer g_DepthTiled3;
        HDMC_EXPORT extern ColorBuffer g_DepthTiled4;
        HDMC_EXPORT extern ColorBuffer g_AOMerged1;
        HDMC_EXPORT extern ColorBuffer g_AOMerged2;
        HDMC_EXPORT extern ColorBuffer g_AOMerged3;
        HDMC_EXPORT extern ColorBuffer g_AOMerged4;
        HDMC_EXPORT extern ColorBuffer g_AOSmooth1;
        HDMC_EXPORT extern ColorBuffer g_AOSmooth2;
        HDMC_EXPORT extern ColorBuffer g_AOSmooth3;
        HDMC_EXPORT extern ColorBuffer g_AOHighQuality1;
        HDMC_EXPORT extern ColorBuffer g_AOHighQuality2;
        HDMC_EXPORT extern ColorBuffer g_AOHighQuality3;
        HDMC_EXPORT extern ColorBuffer g_AOHighQuality4;

        HDMC_EXPORT extern ColorBuffer g_DoFTileClass[ 2 ];
        HDMC_EXPORT extern ColorBuffer g_DoFPresortBuffer;
        HDMC_EXPORT extern ColorBuffer g_DoFPrefilter;
        HDMC_EXPORT extern ColorBuffer g_DoFBlurColor[ 2 ];
        HDMC_EXPORT extern ColorBuffer g_DoFBlurAlpha[ 2 ];
        HDMC_EXPORT extern StructuredBuffer g_DoFWorkQueue;
        HDMC_EXPORT extern StructuredBuffer g_DoFFastQueue;
        HDMC_EXPORT extern StructuredBuffer g_DoFFixupQueue;

        HDMC_EXPORT extern ColorBuffer g_MotionPrepBuffer;		// R10G10B10A2
        HDMC_EXPORT extern ColorBuffer g_LumaBuffer;
        HDMC_EXPORT extern ColorBuffer g_TemporalColor[ 2 ];
        HDMC_EXPORT extern ColorBuffer g_TemporalMinBound;
        HDMC_EXPORT extern ColorBuffer g_TemporalMaxBound;

        HDMC_EXPORT extern ColorBuffer g_aBloomUAV1[ 2 ];		// 640x384 (1/3)
        HDMC_EXPORT extern ColorBuffer g_aBloomUAV2[ 2 ];		// 320x192 (1/6)  
        HDMC_EXPORT extern ColorBuffer g_aBloomUAV3[ 2 ];		// 160x96  (1/12)
        HDMC_EXPORT extern ColorBuffer g_aBloomUAV4[ 2 ];		// 80x48   (1/24)
        HDMC_EXPORT extern ColorBuffer g_aBloomUAV5[ 2 ];		// 40x24   (1/48)
        HDMC_EXPORT extern ColorBuffer g_LumaLR;
        HDMC_EXPORT extern ByteAddressBuffer g_Histogram;
        HDMC_EXPORT extern ByteAddressBuffer g_FXAAWorkQueue;
        HDMC_EXPORT extern TypedBuffer g_FXAAColorQueue;

        HDMC_EXPORT void InitializeRenderingBuffers( uint32_t NativeWidth, uint32_t NativeHeight );
        HDMC_EXPORT void ResizeDisplayDependentBuffers( uint32_t NativeWidth, uint32_t NativeHeight );
        HDMC_EXPORT void DestroyRenderingBuffers( );

    } // namespace Graphics
}