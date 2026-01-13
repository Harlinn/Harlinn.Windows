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
//
// Description:  An upload buffer is visible to both the CPU and the GPU, but
// because the memory is write combined, you should avoid reading data with the CPU.
// An upload buffer is intended for moving data to a default GPU buffer.  You can
// read from a file directly into an upload buffer, rather than reading into regular
// cached memory, copying that to an upload buffer, and copying that to the GPU.

#pragma once

#include "HDMCGpuResource.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class UploadBuffer : public GpuResource
    {
    public:
        virtual ~UploadBuffer( ) { Destroy( ); }

        HDMC_EXPORT void Create( const std::wstring& name, size_t BufferSize );

        HDMC_EXPORT void* Map( void );
        HDMC_EXPORT void Unmap( size_t begin = 0, size_t end = -1 );

        size_t GetBufferSize( ) const { return m_BufferSize; }

    protected:

        size_t m_BufferSize;
    };

}