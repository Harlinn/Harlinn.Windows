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
#include "HDMCEngineTuning.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class ComputeContext;

    namespace PostEffects
    {
        HDMC_EXPORT extern BoolVar EnableHDR;			// Turn on tone mapping features

        // Tone mapping parameters
        HDMC_EXPORT extern ExpVar Exposure;				// Brightness scaler when adapative exposure is disabled
        HDMC_EXPORT extern BoolVar EnableAdaptation;	// Automatically adjust brightness based on perceived luminance

        // Adapation parameters
        HDMC_EXPORT extern ExpVar MinExposure;
        HDMC_EXPORT extern ExpVar MaxExposure;
        HDMC_EXPORT extern NumVar TargetLuminance;
        HDMC_EXPORT extern NumVar AdaptationRate;

        // Bloom parameters
        HDMC_EXPORT extern BoolVar BloomEnable;
        HDMC_EXPORT extern NumVar BloomThreshold;
        HDMC_EXPORT extern NumVar BloomStrength;

        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Shutdown( void );
        HDMC_EXPORT void Render( void );

        // Copy the contents of the post effects buffer onto the main scene buffer
        HDMC_EXPORT void CopyBackPostBuffer( ComputeContext& Context );
    }
}