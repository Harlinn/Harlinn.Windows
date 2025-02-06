//--------------------------------------------------------------------------------------
// File: SpriteBatch.h
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
#include <dxgi1_2.h>
#endif

#include <cstdint>
#include <functional>
#include <memory>

#include <DirectXMath.h>
#include <DirectXColors.h>


namespace DirectX
{
    inline namespace DX11
    {
        enum SpriteSortMode : uint32_t
        {
            SpriteSortMode_Deferred,
            SpriteSortMode_Immediate,
            SpriteSortMode_Texture,
            SpriteSortMode_BackToFront,
            SpriteSortMode_FrontToBack,
        };

        enum SpriteEffects : uint32_t
        {
            SpriteEffects_None = 0,
            SpriteEffects_FlipHorizontally = 1,
            SpriteEffects_FlipVertically = 2,
            SpriteEffects_FlipBoth = SpriteEffects_FlipHorizontally | SpriteEffects_FlipVertically,
        };

        class SpriteBatch
        {
        public:
            HDXTK_EXPORT explicit SpriteBatch(_In_ ID3D11DeviceContext* deviceContext);

            HDXTK_EXPORT SpriteBatch(SpriteBatch&&) noexcept;
            HDXTK_EXPORT SpriteBatch& operator= (SpriteBatch&&) noexcept;

            SpriteBatch(SpriteBatch const&) = delete;
            SpriteBatch& operator= (SpriteBatch const&) = delete;

            HDXTK_EXPORT virtual ~SpriteBatch();

            // Begin/End a batch of sprite drawing operations.
            HDXTK_EXPORT void XM_CALLCONV Begin(SpriteSortMode sortMode = SpriteSortMode_Deferred,
                _In_opt_ ID3D11BlendState* blendState = nullptr,
                _In_opt_ ID3D11SamplerState* samplerState = nullptr,
                _In_opt_ ID3D11DepthStencilState* depthStencilState = nullptr,
                _In_opt_ ID3D11RasterizerState* rasterizerState = nullptr,
                _In_ std::function<void __cdecl()> setCustomShaders = nullptr,
                FXMMATRIX transformMatrix = MatrixIdentity);
            HDXTK_EXPORT void __cdecl End();

            // Draw overloads specifying position, origin and scale as XMFLOAT2.
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, XMFLOAT2 const& position, FXMVECTOR color = Colors::White);
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, XMFLOAT2 const& position, _In_opt_ RECT const* sourceRectangle, FXMVECTOR color = Colors::White, float rotation = 0, XMFLOAT2 const& origin = Float2Zero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, XMFLOAT2 const& position, _In_opt_ RECT const* sourceRectangle, FXMVECTOR color, float rotation, XMFLOAT2 const& origin, XMFLOAT2 const& scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);

            // Draw overloads specifying position, origin and scale via the first two components of an XMVECTOR.
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, FXMVECTOR position, FXMVECTOR color = Colors::White);
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, FXMVECTOR position, _In_opt_ RECT const* sourceRectangle, FXMVECTOR color = Colors::White, float rotation = 0, FXMVECTOR origin = g_XMZero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, FXMVECTOR position, _In_opt_ RECT const* sourceRectangle, FXMVECTOR color, float rotation, FXMVECTOR origin, GXMVECTOR scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);

            // Draw overloads specifying position as a RECT.
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, RECT const& destinationRectangle, FXMVECTOR color = Colors::White);
            HDXTK_EXPORT void XM_CALLCONV Draw(_In_ ID3D11ShaderResourceView* texture, RECT const& destinationRectangle, _In_opt_ RECT const* sourceRectangle, FXMVECTOR color = Colors::White, float rotation = 0, XMFLOAT2 const& origin = Float2Zero, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);

            // Rotation mode to be applied to the sprite transformation
            HDXTK_EXPORT void __cdecl SetRotation(DXGI_MODE_ROTATION mode);
            HDXTK_EXPORT DXGI_MODE_ROTATION __cdecl GetRotation() const noexcept;

            // Set viewport for sprite transformation
            HDXTK_EXPORT void __cdecl SetViewport(const D3D11_VIEWPORT& viewPort);

        private:
            // Private implementation.
            struct Impl;

            std::unique_ptr<Impl> pImpl;

            static const XMMATRIX MatrixIdentity;
            static const XMFLOAT2 Float2Zero;
        };
    }
}
