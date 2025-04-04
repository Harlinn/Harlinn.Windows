//--------------------------------------------------------------------------------------
// File: SpriteFont.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include "SpriteBatch.h"

#include <cstddef>
#include <cstdint>
#include <memory>


namespace DirectX
{
    inline namespace DX12
    {
        class SpriteFont
        {
        public:
            struct Glyph;

            HDXTK12_EXPORT SpriteFont(ID3D12Device* device, ResourceUploadBatch& upload,
                _In_z_ wchar_t const* fileName,
                D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorDest, D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptor,
                bool forceSRGB = false);
            HDXTK12_EXPORT SpriteFont(ID3D12Device* device, ResourceUploadBatch& upload,
                _In_reads_bytes_(dataSize) uint8_t const* dataBlob, size_t dataSize,
                D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorDest, D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptor,
                bool forceSRGB = false);
            HDXTK12_EXPORT SpriteFont(D3D12_GPU_DESCRIPTOR_HANDLE texture, XMUINT2 textureSize,
                _In_reads_(glyphCount) Glyph const* glyphs, size_t glyphCount, float lineSpacing);

            HDXTK12_EXPORT SpriteFont(SpriteFont&&) noexcept;
            HDXTK12_EXPORT SpriteFont& operator= (SpriteFont&&) noexcept;

            SpriteFont(SpriteFont const&) = delete;
            SpriteFont& operator= (SpriteFont const&) = delete;

            HDXTK12_EXPORT virtual ~SpriteFont();

            // Wide-character / UTF-16LE
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ wchar_t const* text, XMFLOAT2 const& position, FXMVECTOR color = Colors::White, float rotation = 0, XMFLOAT2 const& origin = Float2Zero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ wchar_t const* text, XMFLOAT2 const& position, FXMVECTOR color, float rotation, XMFLOAT2 const& origin, XMFLOAT2 const& scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ wchar_t const* text, FXMVECTOR position, FXMVECTOR color = Colors::White, float rotation = 0, FXMVECTOR origin = g_XMZero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ wchar_t const* text, FXMVECTOR position, FXMVECTOR color, float rotation, FXMVECTOR origin, GXMVECTOR scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;

            HDXTK12_EXPORT XMVECTOR XM_CALLCONV MeasureString(_In_z_ wchar_t const* text, bool ignoreWhitespace = true) const;

            HDXTK12_EXPORT RECT __cdecl MeasureDrawBounds(_In_z_ wchar_t const* text, XMFLOAT2 const& position, bool ignoreWhitespace = true) const;
            HDXTK12_EXPORT RECT XM_CALLCONV MeasureDrawBounds(_In_z_ wchar_t const* text, FXMVECTOR position, bool ignoreWhitespace = true) const;

            // UTF-8
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ char const* text, XMFLOAT2 const& position, FXMVECTOR color = Colors::White, float rotation = 0, XMFLOAT2 const& origin = Float2Zero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ char const* text, XMFLOAT2 const& position, FXMVECTOR color, float rotation, XMFLOAT2 const& origin, XMFLOAT2 const& scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ char const* text, FXMVECTOR position, FXMVECTOR color = Colors::White, float rotation = 0, FXMVECTOR origin = g_XMZero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            HDXTK12_EXPORT void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ char const* text, FXMVECTOR position, FXMVECTOR color, float rotation, FXMVECTOR origin, GXMVECTOR scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;

            HDXTK12_EXPORT XMVECTOR XM_CALLCONV MeasureString(_In_z_ char const* text, bool ignoreWhitespace = true) const;

            HDXTK12_EXPORT RECT __cdecl MeasureDrawBounds(_In_z_ char const* text, XMFLOAT2 const& position, bool ignoreWhitespace = true) const;
            HDXTK12_EXPORT RECT XM_CALLCONV MeasureDrawBounds(_In_z_ char const* text, FXMVECTOR position, bool ignoreWhitespace = true) const;

            // Spacing properties
            HDXTK12_EXPORT float __cdecl GetLineSpacing() const noexcept;
            HDXTK12_EXPORT void __cdecl SetLineSpacing(float spacing);

            // Font properties
            HDXTK12_EXPORT wchar_t __cdecl GetDefaultCharacter() const noexcept;
            HDXTK12_EXPORT void __cdecl SetDefaultCharacter(wchar_t character);

            HDXTK12_EXPORT bool __cdecl ContainsCharacter(wchar_t character) const;

            // Custom layout/rendering
            HDXTK12_EXPORT Glyph const* __cdecl FindGlyph(wchar_t character) const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE __cdecl GetSpriteSheet() const noexcept;
            HDXTK12_EXPORT XMUINT2 __cdecl GetSpriteSheetSize() const noexcept;

            // Describes a single character glyph.
            struct Glyph
            {
                uint32_t Character;
                RECT Subrect;
                float XOffset;
                float YOffset;
                float XAdvance;
            };

#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
            SpriteFont(ID3D12Device* device, ResourceUploadBatch& upload, _In_z_ __wchar_t const* fileName, D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorDest, D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptor, bool forceSRGB = false);

            void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ __wchar_t const* text, XMFLOAT2 const& position, FXMVECTOR color = Colors::White, float rotation = 0, XMFLOAT2 const& origin = Float2Zero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;

            void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ __wchar_t const* text, XMFLOAT2 const& position, FXMVECTOR color, float rotation, XMFLOAT2 const& origin, XMFLOAT2 const& scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ __wchar_t const* text, FXMVECTOR position, FXMVECTOR color = Colors::White, float rotation = 0, FXMVECTOR origin = g_XMZero, float scale = 1, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;
            void XM_CALLCONV DrawString(_In_ SpriteBatch* spriteBatch, _In_z_ __wchar_t const* text, FXMVECTOR position, FXMVECTOR color, float rotation, FXMVECTOR origin, GXMVECTOR scale, SpriteEffects effects = SpriteEffects_None, float layerDepth = 0) const;

            XMVECTOR XM_CALLCONV MeasureString(_In_z_ __wchar_t const* text, bool ignoreWhitespace = true) const;

            RECT __cdecl MeasureDrawBounds(_In_z_ __wchar_t const* text, XMFLOAT2 const& position, bool ignoreWhitespace = true) const;
            RECT XM_CALLCONV MeasureDrawBounds(_In_z_ __wchar_t const* text, FXMVECTOR position, bool ignoreWhitespace = true) const;

            void __cdecl SetDefaultCharacter(__wchar_t character);

            bool __cdecl ContainsCharacter(__wchar_t character) const;

            Glyph const* __cdecl FindGlyph(__wchar_t character) const;
#endif // !_NATIVE_WCHAR_T_DEFINED

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;

            HDXTK12_EXPORT static const XMFLOAT2 Float2Zero;
        };
    }
}
