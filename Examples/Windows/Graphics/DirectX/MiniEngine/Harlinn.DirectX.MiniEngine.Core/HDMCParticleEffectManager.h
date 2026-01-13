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
// Author(s):  Julia Careaga
//             James Stanard
//

#pragma once

#include "HDMCParticleEffectProperties.h"
#include "HDMCParticleEffect.h"
#include "HDMCCommandContext.h"
#include "HDMCEngineTuning.h"
#include "Math/HDMCRandom.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace Math
    {
        class Camera;
    }

    namespace ParticleEffectManager
    {
        HDMC_EXPORT void Initialize( uint32_t MaxDisplayWidth, uint32_t MaxDisplayHeight );
        HDMC_EXPORT void Shutdown( );
        HDMC_EXPORT void ClearAll( );

        HDMC_EXPORT void Update( ComputeContext& Context, float timeDelta );

        typedef uint32_t EffectHandle;
        HDMC_EXPORT EffectHandle InstantiateEffect( ParticleEffectProperties& effectProperties );
        HDMC_EXPORT void Update( ComputeContext& Context, float timeDelta );
        HDMC_EXPORT void Render( CommandContext& Context, const Math::Camera& Camera, ColorBuffer& ColorTarget, DepthBuffer& DepthTarget, ColorBuffer& LinearDepth );
        HDMC_EXPORT void ResetEffect( EffectHandle EffectID );
        HDMC_EXPORT float GetCurrentLife( EffectHandle EffectID );
        HDMC_EXPORT void RegisterTexture( uint32_t index, const Texture& texture );

        HDMC_EXPORT extern BoolVar Enable;
        HDMC_EXPORT extern BoolVar PauseSim;
        HDMC_EXPORT extern BoolVar EnableTiledRendering;
        HDMC_EXPORT extern bool Reproducible; //If you want to repro set to true. When true, effect uses the same set of random numbers each run
        HDMC_EXPORT extern UINT ReproFrame;
    } // namespace ParticleEffectManager
}