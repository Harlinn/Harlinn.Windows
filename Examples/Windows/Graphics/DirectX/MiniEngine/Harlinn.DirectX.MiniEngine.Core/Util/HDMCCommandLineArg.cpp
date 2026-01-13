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
// Author:  Jack Elliott
//

#include "pch.h"
#include "Util/HDMCCommandLineArg.h"
#include <unordered_map>
#include <string>
#include <sstream>

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace CommandLineArgs
    {
        std::unordered_map<std::wstring, std::wstring> m_argumentMap;

        template<typename GetStringFunc>
        void GatherArgs( size_t numArgs, const GetStringFunc& pfnGet )
        {
            // the first arg is always the exe name and we are looing for key/value pairs
            if ( numArgs > 1 )
            {
                size_t i = 0;

                while ( i < numArgs )
                {
                    const wchar_t* key = pfnGet( i );
                    i++;
                    if ( i < numArgs && key[ 0 ] == '-' )
                    {
                        const wchar_t* strippedKey = key + 1;
                        m_argumentMap[ strippedKey ] = pfnGet( i );
                        i++;
                    }
                }
            }
        }

        void Initialize( int argc, wchar_t** argv )
        {
            GatherArgs( size_t( argc ), [ argv ]( size_t i ) -> const wchar_t* { return argv[ i ]; } );
        }

        template<typename FunctionType>
        bool Lookup( const wchar_t* key, const FunctionType& pfnFunction )
        {
            const auto found = m_argumentMap.find( key );
            if ( found != m_argumentMap.end( ) )
            {
                pfnFunction( found->second );
                return true;
            }

            return false;
        }

        bool GetInteger( const wchar_t* key, uint32_t& value )
        {
            return Lookup( key, [ &value ]( std::wstring& val )
                {
                    value = std::stoi( val );
                } );
        }

        bool GetFloat( const wchar_t* key, float& value )
        {
            return Lookup( key, [ &value ]( std::wstring& val )
                {
                    value = ( float )_wtof( val.c_str( ) );
                } );
        }

        bool GetString( const wchar_t* key, std::wstring& value )
        {
            return Lookup( key, [ &value ]( std::wstring& val )
                {
                    value = val;
                } );
        }
    }
}