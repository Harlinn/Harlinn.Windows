//--------------------------------------------------------------------------------------
// File: GraphicsMemory.h
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

#include <cstddef>
#include <memory>


namespace DirectX
{
    inline namespace DX11
    {
        class GraphicsMemory
        {
        public:
        #if defined(_XBOX_ONE) && defined(_TITLE)
            HDXTK_EXPORT GraphicsMemory(_In_ ID3D11DeviceX* device, unsigned int backBufferCount = 2);
        #else
            HDXTK_EXPORT GraphicsMemory(_In_ ID3D11Device* device, unsigned int backBufferCount = 2);
        #endif

            HDXTK_EXPORT GraphicsMemory(GraphicsMemory&&) noexcept;
            HDXTK_EXPORT GraphicsMemory& operator= (GraphicsMemory&&) noexcept;

            HDXTK_EXPORT GraphicsMemory(GraphicsMemory const&) = delete;
            HDXTK_EXPORT GraphicsMemory& operator=(GraphicsMemory const&) = delete;

            HDXTK_EXPORT virtual ~GraphicsMemory();

            HDXTK_EXPORT void* __cdecl Allocate(_In_opt_ ID3D11DeviceContext* context, size_t size, int alignment);

            HDXTK_EXPORT void __cdecl Commit();

            // Singleton
            HDXTK_EXPORT static GraphicsMemory& __cdecl Get();

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };
    }
}
