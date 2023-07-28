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