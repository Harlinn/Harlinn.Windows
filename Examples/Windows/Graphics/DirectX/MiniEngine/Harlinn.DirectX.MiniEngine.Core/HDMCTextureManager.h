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
// Author(s):  James Stanard
//

#pragma once

#include "HDMCDef.h"
#include "HDMCGpuResource.h"
#include "HDMCUtility.h"
#include "HDMCTexture.h"
#include "HDMCGraphicsCommon.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    // A referenced-counted pointer to a Texture.  See methods below.
    class TextureRef;

    //
    // Texture file loading system.
    //
    // References to textures are passed around so that a texture may be shared.  When
    // all references to a texture expire, the texture memory is reclaimed.
    //
    namespace TextureManager
    {
        using Graphics::eDefaultTexture;
        using Graphics::kMagenta2D;

        HDMC_EXPORT void Initialize( const std::wstring& RootPath );
        HDMC_EXPORT void Shutdown( void );

        // Load a texture from a DDS file.  Never returns null references, but if a 
        // texture cannot be found, ref->IsValid() will return false.
        HDMC_EXPORT TextureRef LoadDDSFromFile( const std::wstring& filePath, eDefaultTexture fallback = kMagenta2D, bool sRGB = false );
        HDMC_EXPORT TextureRef LoadDDSFromFile( const std::string& filePath, eDefaultTexture fallback = kMagenta2D, bool sRGB = false );
    }

    // Forward declaration; private implementation
    class ManagedTexture;

    //
    // A handle to a ManagedTexture.  Constructors and destructors modify the reference
    // count.  When the last reference is destroyed, the TextureManager is informed that
    // the texture should be deleted.
    //
    class TextureRef
    {
    public:

        HDMC_EXPORT TextureRef( const TextureRef& ref );
        HDMC_EXPORT TextureRef( ManagedTexture* tex = nullptr );
        HDMC_EXPORT ~TextureRef( );

        HDMC_EXPORT void operator= ( std::nullptr_t );
        HDMC_EXPORT void operator= ( const TextureRef& rhs );

        // Check that this points to a valid texture (which loaded successfully)
        HDMC_EXPORT bool IsValid( ) const;

        // Gets the SRV descriptor handle.  If the reference is invalid,
        // returns a valid descriptor handle (specified by the fallback)
        HDMC_EXPORT D3D12_CPU_DESCRIPTOR_HANDLE GetSRV( ) const;

        // Get the texture pointer.  Client is responsible to not dereference
        // null pointers.
        HDMC_EXPORT const Texture* Get( void ) const;

        HDMC_EXPORT const Texture* operator->( void ) const;

    private:
        ManagedTexture* m_ref;
    };
}