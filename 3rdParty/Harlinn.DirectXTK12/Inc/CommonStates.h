//--------------------------------------------------------------------------------------
// File: CommonStates.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include <HDirectXTK12Def.h>

#ifdef _GAMING_XBOX_SCARLETT
#include <d3d12_xs.h>
#elif (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <d3d12_x.h>
#elif defined(USING_DIRECTX_HEADERS)
#include <directx/d3d12.h>
#include <dxguids/dxguids.h>
#else
#include <d3d12.h>
#endif

#include <cstdint>
#include <memory>


namespace DirectX
{
    inline namespace DX12
    {
        class CommonStates
        {
        public:
            HDXTK12_EXPORT explicit CommonStates(_In_ ID3D12Device* device);

            HDXTK12_EXPORT CommonStates(CommonStates&&) noexcept;
            HDXTK12_EXPORT CommonStates& operator = (CommonStates&&) noexcept;

            CommonStates(const CommonStates&) = delete;
            CommonStates& operator = (const CommonStates&) = delete;

            HDXTK12_EXPORT virtual ~CommonStates();

            // Blend states.
            HDXTK12_EXPORT static const D3D12_BLEND_DESC Opaque;
            HDXTK12_EXPORT static const D3D12_BLEND_DESC AlphaBlend;
            HDXTK12_EXPORT static const D3D12_BLEND_DESC Additive;
            HDXTK12_EXPORT static const D3D12_BLEND_DESC NonPremultiplied;

            // Depth stencil states.
            HDXTK12_EXPORT static const D3D12_DEPTH_STENCIL_DESC DepthNone;
            HDXTK12_EXPORT static const D3D12_DEPTH_STENCIL_DESC DepthDefault;
            HDXTK12_EXPORT static const D3D12_DEPTH_STENCIL_DESC DepthRead;
            HDXTK12_EXPORT static const D3D12_DEPTH_STENCIL_DESC DepthReverseZ;
            HDXTK12_EXPORT static const D3D12_DEPTH_STENCIL_DESC DepthReadReverseZ;

            // Rasterizer states.
            HDXTK12_EXPORT static const D3D12_RASTERIZER_DESC CullNone;
            HDXTK12_EXPORT static const D3D12_RASTERIZER_DESC CullClockwise;
            HDXTK12_EXPORT static const D3D12_RASTERIZER_DESC CullCounterClockwise;
            HDXTK12_EXPORT static const D3D12_RASTERIZER_DESC Wireframe;

            // Static sampler states.
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticPointWrap(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticPointClamp(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticLinearWrap(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticLinearClamp(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticAnisotropicWrap(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;
            HDXTK12_EXPORT static const D3D12_STATIC_SAMPLER_DESC StaticAnisotropicClamp(unsigned int shaderRegister, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL, unsigned int registerSpace = 0) noexcept;

            // Sampler states.
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE PointWrap() const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE PointClamp() const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE LinearWrap() const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE LinearClamp() const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE AnisotropicWrap() const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE AnisotropicClamp() const;

            // These index into the heap returned by SamplerDescriptorHeap
            enum class SamplerIndex : uint32_t
            {
                PointWrap,
                PointClamp,
                LinearWrap,
                LinearClamp,
                AnisotropicWrap,
                AnisotropicClamp,
                Count
            };

            HDXTK12_EXPORT ID3D12DescriptorHeap* Heap() const noexcept;

        private:
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };
    }
}
