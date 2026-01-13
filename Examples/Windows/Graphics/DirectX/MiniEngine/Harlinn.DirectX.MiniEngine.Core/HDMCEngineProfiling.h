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

#pragma once

#include <string>
#include "HDMCTextRenderer.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandContext;

    namespace EngineProfiling
    {
        HDMC_EXPORT void Update( );

        HDMC_EXPORT void BeginBlock( const std::wstring& name, CommandContext* Context = nullptr );
        HDMC_EXPORT void EndBlock( CommandContext* Context = nullptr );

        HDMC_EXPORT void DisplayFrameRate( TextContext& Text );
        HDMC_EXPORT void DisplayPerfGraph( GraphicsContext& Text );
        HDMC_EXPORT void Display( TextContext& Text, float x, float y, float w, float h );
        HDMC_EXPORT bool IsPaused( );
    }

#ifdef RELEASE
    class ScopedTimer
    {
    public:
        ScopedTimer( const std::wstring& ) {}
        ScopedTimer( const std::wstring&, CommandContext& ) {}
    };
#else
    class ScopedTimer
    {
    public:
        ScopedTimer( const std::wstring& name ) : m_Context( nullptr )
        {
            EngineProfiling::BeginBlock( name );
        }
        ScopedTimer( const std::wstring& name, CommandContext& Context ) : m_Context( &Context )
        {
            EngineProfiling::BeginBlock( name, m_Context );
        }
        ~ScopedTimer( )
        {
            EngineProfiling::EndBlock( m_Context );
        }

    private:
        CommandContext* m_Context;
    };
#endif
}