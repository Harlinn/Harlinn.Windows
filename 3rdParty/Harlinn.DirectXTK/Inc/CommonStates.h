//--------------------------------------------------------------------------------------
// File: CommonStates.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#include <HDirectXTKDef.h>

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#include <memory>


namespace DirectX
{
    inline namespace DX11
    {
        class CommonStates
        {
        public:
            HDXTK_EXPORT explicit CommonStates(_In_ ID3D11Device* device);

            HDXTK_EXPORT CommonStates(CommonStates&&) noexcept;
            HDXTK_EXPORT CommonStates& operator= (CommonStates&&) noexcept;

            CommonStates(CommonStates const&) = delete;
            CommonStates& operator= (CommonStates const&) = delete;

            HDXTK_EXPORT virtual ~CommonStates();

            // Blend states.
            HDXTK_EXPORT ID3D11BlendState* __cdecl Opaque() const;
            HDXTK_EXPORT ID3D11BlendState* __cdecl AlphaBlend() const;
            HDXTK_EXPORT ID3D11BlendState* __cdecl Additive() const;
            HDXTK_EXPORT ID3D11BlendState* __cdecl NonPremultiplied() const;

            // Depth stencil states.
            HDXTK_EXPORT ID3D11DepthStencilState* __cdecl DepthNone() const;
            HDXTK_EXPORT ID3D11DepthStencilState* __cdecl DepthDefault() const;
            HDXTK_EXPORT ID3D11DepthStencilState* __cdecl DepthRead() const;
            HDXTK_EXPORT ID3D11DepthStencilState* __cdecl DepthReverseZ() const;
            HDXTK_EXPORT ID3D11DepthStencilState* __cdecl DepthReadReverseZ() const;

            // Rasterizer states.
            HDXTK_EXPORT ID3D11RasterizerState* __cdecl CullNone() const;
            HDXTK_EXPORT ID3D11RasterizerState* __cdecl CullClockwise() const;
            HDXTK_EXPORT ID3D11RasterizerState* __cdecl CullCounterClockwise() const;
            HDXTK_EXPORT ID3D11RasterizerState* __cdecl Wireframe() const;

            // Sampler states.
            HDXTK_EXPORT ID3D11SamplerState* __cdecl PointWrap() const;
            HDXTK_EXPORT ID3D11SamplerState* __cdecl PointClamp() const;
            HDXTK_EXPORT ID3D11SamplerState* __cdecl LinearWrap() const;
            HDXTK_EXPORT ID3D11SamplerState* __cdecl LinearClamp() const;
            HDXTK_EXPORT ID3D11SamplerState* __cdecl AnisotropicWrap() const;
            HDXTK_EXPORT ID3D11SamplerState* __cdecl AnisotropicClamp() const;

        private:
            // Private implementation.
            class Impl;

            std::shared_ptr<Impl> pImpl;
        };
    }
}
