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

#include "HDMCPixelBuffer.h"
#include "HDMCColor.h"
#include "HDMCGpuBuffer.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class EsramAllocator;

    class ColorBuffer : public PixelBuffer
    {
    protected:
        Color m_ClearColor;
        D3D12_CPU_DESCRIPTOR_HANDLE m_SRVHandle;
        D3D12_CPU_DESCRIPTOR_HANDLE m_RTVHandle;
        D3D12_CPU_DESCRIPTOR_HANDLE m_UAVHandle[ 12 ];
        uint32_t m_NumMipMaps; // number of texture sublevels
        uint32_t m_FragmentCount;
        uint32_t m_SampleCount;
    public:
        ColorBuffer( Color ClearColor = Color( 0.0f, 0.0f, 0.0f, 0.0f ) )
            : m_ClearColor( ClearColor ), m_NumMipMaps( 0 ), m_FragmentCount( 1 ), m_SampleCount( 1 )
        {
            m_RTVHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
            m_SRVHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
            for ( int i = 0; i < _countof( m_UAVHandle ); ++i )
            {
                m_UAVHandle[ i ].ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
            }
        }

        // Create a color buffer from a swap chain buffer.  Unordered access is restricted.
        HDMC_EXPORT void CreateFromSwapChain( const std::wstring& Name, const D3D12Resource& baseResource );

        // Create a color buffer.  If an address is supplied, memory will not be allocated.
        // The vmem address allows you to alias buffers (which can be especially useful for
        // reusing ESRAM across a frame.)
        HDMC_EXPORT void Create( const std::wstring& Name, uint32_t Width, uint32_t Height, uint32_t NumMips, DXGI_FORMAT Format, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN );

        // Create a color buffer.  If an address is supplied, memory will not be allocated.
        // The vmem address allows you to alias buffers (which can be especially useful for
        // reusing ESRAM across a frame.)
        HDMC_EXPORT void CreateArray( const std::wstring& Name, uint32_t Width, uint32_t Height, uint32_t ArrayCount, DXGI_FORMAT Format, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN );


        // Get pre-created CPU-visible descriptor handles
        const D3D12_CPU_DESCRIPTOR_HANDLE& GetSRV( void ) const { return m_SRVHandle; }
        const D3D12_CPU_DESCRIPTOR_HANDLE& GetRTV( void ) const { return m_RTVHandle; }
        const D3D12_CPU_DESCRIPTOR_HANDLE& GetUAV( void ) const { return m_UAVHandle[ 0 ]; }

        void SetClearColor( Color ClearColor ) { m_ClearColor = ClearColor; }

        void SetMsaaMode( uint32_t NumColorSamples, uint32_t NumCoverageSamples )
        {
            ASSERT( NumCoverageSamples >= NumColorSamples );
            m_FragmentCount = NumColorSamples;
            m_SampleCount = NumCoverageSamples;
        }

        Color GetClearColor( void ) const { return m_ClearColor; }

        // This will work for all texture sizes, but it's recommended for speed and quality
        // that you use dimensions with powers of two (but not necessarily square.)  Pass
        // 0 for ArrayCount to reserve space for mips at creation time.
        HDMC_EXPORT void GenerateMipMaps( CommandContext& Context );

    protected:

        D3D12_RESOURCE_FLAGS CombineResourceFlags( void ) const
        {
            D3D12_RESOURCE_FLAGS Flags = D3D12_RESOURCE_FLAG_NONE;

            if ( Flags == D3D12_RESOURCE_FLAG_NONE && m_FragmentCount == 1 )
            {
                Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
            }

            return D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | Flags;
        }

        // Compute the number of texture levels needed to reduce to 1x1.  This uses
        // _BitScanReverse to find the highest set bit.  Each dimension reduces by
        // half and truncates bits.  The dimension 256 (0x100) has 9 mip levels, same
        // as the dimension 511 (0x1FF).
        static inline uint32_t ComputeNumMips( uint32_t Width, uint32_t Height )
        {
            uint32_t HighBit;
            _BitScanReverse( ( unsigned long* )&HighBit, Width | Height );
            return HighBit + 1;
        }

        HDMC_EXPORT void CreateDerivedViews( const D3D12Device& device, DXGI_FORMAT Format, uint32_t ArraySize, uint32_t NumMips = 1 );

        
    };
}