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

    namespace Display
    {
        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Shutdown( void );
        HDMC_EXPORT void Resize( uint32_t width, uint32_t height );
        HDMC_EXPORT void Present( void );
    }

    class EnumVar;
    namespace Graphics
    {
        HDMC_EXPORT extern EnumVar DebugZoom;
        HDMC_EXPORT extern uint32_t g_DisplayWidth;
        HDMC_EXPORT extern uint32_t g_DisplayHeight;
        HDMC_EXPORT extern bool g_bEnableHDROutput;

        // Returns the number of elapsed frames since application start
        HDMC_EXPORT uint64_t GetFrameCount( void );

        // The amount of time elapsed during the last completed frame.  The CPU and/or
        // GPU may be idle during parts of the frame.  The frame time measures the time
        // between calls to present each frame.
        HDMC_EXPORT float GetFrameTime( void );

        // The total number of frames per second
        HDMC_EXPORT float GetFrameRate( void );

    }
}