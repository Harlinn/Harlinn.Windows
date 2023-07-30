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

    class ColorBuffer;
    class BoolVar;
    class NumVar;
    class ComputeContext;

    namespace FXAA
    {
        HDMC_EXPORT extern BoolVar Enable;
        HDMC_EXPORT extern BoolVar DebugDraw;
        HDMC_EXPORT extern NumVar ContrastThreshold;	// Default = 0.20
        HDMC_EXPORT extern NumVar SubpixelRemoval;		// Default = 0.75

        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Shutdown( void );
        HDMC_EXPORT void Render( ComputeContext& Context, bool bUsePreComputedLuma );

    } // namespace FXAA
}