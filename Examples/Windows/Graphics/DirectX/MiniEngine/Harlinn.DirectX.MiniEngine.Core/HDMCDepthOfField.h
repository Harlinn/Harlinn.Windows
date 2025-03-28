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
#include "HDMCCommandContext.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace DepthOfField
    {
        HDMC_EXPORT extern BoolVar Enable;

        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Shutdown( void );

        HDMC_EXPORT void Render( CommandContext& BaseContext, float NearClipDist, float FarClipDist );
    }
}