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

#include "HDMCGameCore.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandContext;

    namespace GpuTimeManager
    {
        HDMC_EXPORT void Initialize( uint32_t MaxNumTimers = 4096 );
        HDMC_EXPORT void Shutdown( );

        // Reserve a unique timer index
        HDMC_EXPORT uint32_t NewTimer( );

        // Write start and stop time stamps on the GPU timeline
        HDMC_EXPORT void StartTimer( CommandContext& Context, uint32_t TimerIdx );
        HDMC_EXPORT void StopTimer( CommandContext& Context, uint32_t TimerIdx );

        // Bookend all calls to GetTime() with Begin/End which correspond to Map/Unmap.  This
        // needs to happen either at the very start or very end of a frame.
        HDMC_EXPORT void BeginReadBack( void );
        HDMC_EXPORT void EndReadBack( void );

        // Returns the time in milliseconds between start and stop queries
        HDMC_EXPORT float GetTime( uint32_t TimerIdx );
    }
}