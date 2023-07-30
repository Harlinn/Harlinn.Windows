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

#pragma once
#include "HDMCDef.h"
#include "HDMCGpuBuffer.h"
#include "HDMCParticleEffectProperties.h"
#include "HDMCParticleShaderStructs.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    class ComputeContext;
    class ParticleEffect
    {
    private:

        StructuredBuffer m_StateBuffers[ 2 ];
        uint32_t m_CurrentStateBuffer;
        StructuredBuffer m_RandomStateBuffer;
        IndirectArgsBuffer m_DispatchIndirectArgs;
        IndirectArgsBuffer m_DrawIndirectArgs;

        ParticleEffectProperties m_EffectProperties;
        ParticleEffectProperties m_OriginalEffectProperties;
        float m_ElapsedTime;
        UINT m_effectID;

    public:
        HDMC_EXPORT ParticleEffect( ParticleEffectProperties& effectProperties );
        HDMC_EXPORT void LoadDeviceResources( const D3D12Device& device );
        HDMC_EXPORT void Update( ComputeContext& CompContext, float timeDelta );
        float GetLifetime( ) { return m_EffectProperties.TotalActiveLifetime; }
        float GetElapsedTime( ) { return m_ElapsedTime; }
        HDMC_EXPORT void Reset( );



    };

}