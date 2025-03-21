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

#include "HDMCEngineTuning.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandContext;

    namespace TemporalEffects
    {
        // Temporal antialiasing involves jittering sample positions and accumulating color over time to 
        // effectively supersample the image.
        HDMC_EXPORT extern BoolVar EnableTAA;

        HDMC_EXPORT void Initialize( void );

        HDMC_EXPORT void Shutdown( void );

        // Call once per frame to increment the internal frame counter and, in the case of TAA, choosing the next
        // jittered sample position.
        HDMC_EXPORT void Update( uint64_t FrameIndex );

        // Returns whether the frame is odd or even, relevant to checkerboard rendering.
        HDMC_EXPORT uint32_t GetFrameIndexMod2( void );

        // Jitter values are neutral at 0.5 and vary from [0, 1).  Jittering only occurs when temporal antialiasing
        // is enabled.  You can use these values to jitter your viewport or projection matrix.
        HDMC_EXPORT void GetJitterOffset( float& JitterX, float& JitterY );

        HDMC_EXPORT void ClearHistory( CommandContext& Context );

        HDMC_EXPORT void ResolveImage( CommandContext& Context );

    }
}