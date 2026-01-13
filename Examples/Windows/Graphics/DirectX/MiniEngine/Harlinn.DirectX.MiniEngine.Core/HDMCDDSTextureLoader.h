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
//--------------------------------------------------------------------------------------
//
// Functions for loading a DDS texture and creating a Direct3D runtime resource for it
//
// Note these functions are useful as a light-weight runtime loader for DDS files. For
// a full-featured DDS file reader, writer, and texture processing pipeline see
// the 'Texconv' sample and the 'DirectXTex' library.
//
// http://go.microsoft.com/fwlink/?LinkId=248926
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#include "HDMCDef.h"


namespace Harlinn::Windows::DirectX::MiniEngine
{

    enum DDS_ALPHA_MODE
    {
        DDS_ALPHA_MODE_UNKNOWN = 0,
        DDS_ALPHA_MODE_STRAIGHT = 1,
        DDS_ALPHA_MODE_PREMULTIPLIED = 2,
        DDS_ALPHA_MODE_OPAQUE = 3,
        DDS_ALPHA_MODE_CUSTOM = 4,
    };

    D3D12Resource __cdecl CreateDDSTextureFromMemory( _In_ const D3D12Device& d3dDevice,
        _In_reads_bytes_( ddsDataSize ) const uint8_t* ddsData,
        _In_ size_t ddsDataSize,
        _In_ size_t maxsize,
        _In_ bool forceSRGB,
        _In_ D3D12_CPU_DESCRIPTOR_HANDLE textureView,
        _Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
    );




    D3D12Resource __cdecl CreateDDSTextureFromFile( _In_ const D3D12Device& d3dDevice,
        _In_z_ const wchar_t* szFileName,
        _In_ size_t maxsize,
        _In_ bool forceSRGB,
        _In_ D3D12_CPU_DESCRIPTOR_HANDLE textureView,
        _Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
    );

    size_t BitsPerPixel( _In_ DXGI_FORMAT fmt );

}