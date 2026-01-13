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

#include "pch.h"
#include "HDMCGraphicsCore.h"
#include "HDMCPipelineState.h"
#include "HDMCRootSignature.h"
#include "HDMCHash.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    using Math::IsAligned;
    using namespace Graphics;

    static std::map< size_t, D3D12PipelineState > s_GraphicsPSOHashMap;
    static std::map< size_t, D3D12PipelineState > s_ComputePSOHashMap;

    void PSO::DestroyAll( void )
    {
        s_GraphicsPSOHashMap.clear( );
        s_ComputePSOHashMap.clear( );
    }


    GraphicsPSO::GraphicsPSO( const wchar_t* Name )
        : PSO( Name )
    {
        ZeroMemory( &m_PSODesc, sizeof( m_PSODesc ) );
        m_PSODesc.NodeMask = 1;
        m_PSODesc.SampleMask = 0xFFFFFFFFu;
        m_PSODesc.SampleDesc.Count = 1;
        m_PSODesc.InputLayout.NumElements = 0;
    }

    void GraphicsPSO::SetBlendState( const D3D12_BLEND_DESC& BlendDesc )
    {
        m_PSODesc.BlendState = BlendDesc;
    }

    void GraphicsPSO::SetRasterizerState( const D3D12_RASTERIZER_DESC& RasterizerDesc )
    {
        m_PSODesc.RasterizerState = RasterizerDesc;
    }

    void GraphicsPSO::SetDepthStencilState( const D3D12_DEPTH_STENCIL_DESC& DepthStencilDesc )
    {
        m_PSODesc.DepthStencilState = DepthStencilDesc;
    }

    void GraphicsPSO::SetSampleMask( UINT SampleMask )
    {
        m_PSODesc.SampleMask = SampleMask;
    }

    void GraphicsPSO::SetPrimitiveTopologyType( D3D12_PRIMITIVE_TOPOLOGY_TYPE TopologyType )
    {
        ASSERT( TopologyType != D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED, "Can't draw with undefined topology" );
        m_PSODesc.PrimitiveTopologyType = TopologyType;
    }

    void GraphicsPSO::SetPrimitiveRestart( D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBProps )
    {
        m_PSODesc.IBStripCutValue = IBProps;
    }

    void GraphicsPSO::SetDepthTargetFormat( DXGI_FORMAT DSVFormat, UINT MsaaCount, UINT MsaaQuality )
    {
        SetRenderTargetFormats( 0, nullptr, DSVFormat, MsaaCount, MsaaQuality );
    }

    void GraphicsPSO::SetRenderTargetFormat( DXGI_FORMAT RTVFormat, DXGI_FORMAT DSVFormat, UINT MsaaCount, UINT MsaaQuality )
    {
        SetRenderTargetFormats( 1, &RTVFormat, DSVFormat, MsaaCount, MsaaQuality );
    }

    void GraphicsPSO::SetRenderTargetFormats( UINT NumRTVs, const DXGI_FORMAT* RTVFormats, DXGI_FORMAT DSVFormat, UINT MsaaCount, UINT MsaaQuality )
    {
        ASSERT( NumRTVs == 0 || RTVFormats != nullptr, "Null format array conflicts with non-zero length" );
        for ( UINT i = 0; i < NumRTVs; ++i )
        {
            ASSERT( RTVFormats[ i ] != DXGI_FORMAT_UNKNOWN );
            m_PSODesc.RTVFormats[ i ] = RTVFormats[ i ];
        }
        for ( UINT i = NumRTVs; i < m_PSODesc.NumRenderTargets; ++i )
            m_PSODesc.RTVFormats[ i ] = DXGI_FORMAT_UNKNOWN;
        m_PSODesc.NumRenderTargets = NumRTVs;
        m_PSODesc.DSVFormat = DSVFormat;
        m_PSODesc.SampleDesc.Count = MsaaCount;
        m_PSODesc.SampleDesc.Quality = MsaaQuality;
    }

    void GraphicsPSO::SetInputLayout( UINT NumElements, const D3D12_INPUT_ELEMENT_DESC* pInputElementDescs )
    {
        m_PSODesc.InputLayout.NumElements = NumElements;

        if ( NumElements > 0 )
        {
            D3D12_INPUT_ELEMENT_DESC* NewElements = ( D3D12_INPUT_ELEMENT_DESC* )malloc( sizeof( D3D12_INPUT_ELEMENT_DESC ) * NumElements );
            memcpy( NewElements, pInputElementDescs, NumElements * sizeof( D3D12_INPUT_ELEMENT_DESC ) );
            m_InputLayouts.reset( ( const D3D12_INPUT_ELEMENT_DESC* )NewElements );
        }
        else
            m_InputLayouts = nullptr;
    }

    void GraphicsPSO::Finalize( )
    {
        // Make sure the root signature is finalized first
        m_PSODesc.pRootSignature = m_RootSignature->GetSignature( ).GetInterfacePointer< ID3D12RootSignature >();
        ASSERT( m_PSODesc.pRootSignature != nullptr );

        m_PSODesc.InputLayout.pInputElementDescs = nullptr;
        size_t HashCode = Utility::HashState( &m_PSODesc );
        HashCode = Utility::HashState( m_InputLayouts.get( ), m_PSODesc.InputLayout.NumElements, HashCode );
        m_PSODesc.InputLayout.pInputElementDescs = m_InputLayouts.get( );

        ID3D12PipelineState** PSORef = nullptr;
        bool firstCompile = false;
        {
            static std::mutex s_HashMapMutex;
            std::lock_guard<std::mutex> CS( s_HashMapMutex );
            auto iter = s_GraphicsPSOHashMap.find( HashCode );

            // Reserve space so the next inquiry will find that someone got here first.
            if ( iter == s_GraphicsPSOHashMap.end( ) )
            {
                firstCompile = true;
                PSORef = reinterpret_cast< ID3D12PipelineState** >( &s_GraphicsPSOHashMap[ HashCode ] );
            }
            else
                PSORef = reinterpret_cast< ID3D12PipelineState** >( &iter->second );
        }

        if ( firstCompile )
        {
            ASSERT( m_PSODesc.DepthStencilState.DepthEnable != ( m_PSODesc.DSVFormat == DXGI_FORMAT_UNKNOWN ) );
            m_PSO = g_Device.CreateGraphicsPipelineState( &m_PSODesc );
            s_GraphicsPSOHashMap[ HashCode ] = m_PSO;
            m_PSO.SetName( m_Name );
        }
        else
        {
            while ( *PSORef == nullptr )
            {
                Harlinn::Common::Core::CurrentThread::Yield( );
            }
            m_PSO = *PSORef;
        }
    }

    void ComputePSO::Finalize( )
    {
        // Make sure the root signature is finalized first
        m_PSODesc.pRootSignature = m_RootSignature->GetSignature( ).GetInterfacePointer< ID3D12RootSignature >( );
        ASSERT( m_PSODesc.pRootSignature != nullptr );

        size_t HashCode = Utility::HashState( &m_PSODesc );

        ID3D12PipelineState** PSORef = nullptr;
        bool firstCompile = false;
        {
            static std::mutex s_HashMapMutex;
            std::lock_guard<std::mutex> CS( s_HashMapMutex );
            auto iter = s_ComputePSOHashMap.find( HashCode );

            // Reserve space so the next inquiry will find that someone got here first.
            if ( iter == s_ComputePSOHashMap.end( ) )
            {
                firstCompile = true;
                PSORef = reinterpret_cast< ID3D12PipelineState** >( &s_ComputePSOHashMap[ HashCode ] );
            }
            else
                PSORef = reinterpret_cast< ID3D12PipelineState** >( &iter->second );
        }

        if ( firstCompile )
        {
            m_PSO = g_Device.CreateComputePipelineState( &m_PSODesc );
            s_ComputePSOHashMap[ HashCode ] = m_PSO;
            m_PSO.SetName( m_Name );
        }
        else
        {
            while ( *PSORef == nullptr )
            {
                Harlinn::Common::Core::CurrentThread::Yield( );
            }
            m_PSO = *PSORef;
        }
    }

    ComputePSO::ComputePSO( const wchar_t* Name )
        : PSO( Name )
    {
        ZeroMemory( &m_PSODesc, sizeof( m_PSODesc ) );
        m_PSODesc.NodeMask = 1;
    }
}