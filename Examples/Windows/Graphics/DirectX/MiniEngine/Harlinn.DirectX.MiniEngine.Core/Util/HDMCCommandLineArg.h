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
// Author:  Jack Elliott
//

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace CommandLineArgs
    {
        HDMC_EXPORT void Initialize( int argc, wchar_t** argv );
        HDMC_EXPORT bool GetInteger( const wchar_t* key, uint32_t& value );
        HDMC_EXPORT bool GetFloat( const wchar_t* key, float& value );
        HDMC_EXPORT bool GetString( const wchar_t* key, std::wstring& value );
    }
}