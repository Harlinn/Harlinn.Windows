#pragma once
#ifndef HCCHTMLNAMEDCHARACTERS_H_
#define HCCHTMLNAMEDCHARACTERS_H_

/*
   Copyright 2024 Espen Harlinn

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

#include "HCCString.h"

namespace Harlinn::Common::Core::Html
{
    struct NamedChar
    {
        std::wstring_view Name;
        std::vector<UInt32> Codepoints;
        std::wstring_view Value;
    };



    HCC_EXPORT WideString Encode( const wchar_t* text, size_t textLength );
    HCC_EXPORT WideString Decode( const wchar_t* text, size_t textLength );

    template<typename StringT>
        requires std::is_same_v<StringT,WideString> || std::is_same_v<StringT, std::wstring> || std::is_same_v<StringT, std::wstring_view>
    inline WideString Encode( const StringT& str )
    {
        if ( str.empty( ) == false )
        {
            return Encode( str.data( ), str.size( ) );
        }
        return {};
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, std::wstring> || std::is_same_v<StringT, std::wstring_view>
    inline WideString Decode( const StringT& str )
    {
        if ( str.empty( ) == false )
        {
            return Decode( str.data( ), str.size( ) );
        }
        return {};
    }


    inline AnsiString Encode( const char* text, size_t textLength )
    {
        WideString ws; 
        ToWideString( text, textLength, ws );
        auto encoded = Encode( ws );
        AnsiString result;
        ToAnsiString( encoded.c_str( ), encoded.size( ), result );
        return result;
    }
    inline AnsiString Decode( const char* text, size_t textLength )
    {
        WideString ws;
        ToWideString( text, textLength, ws );
        auto decoded = Decode( ws );
        AnsiString result;
        ToAnsiString( decoded.c_str( ), decoded.size( ), result );
        return result;
    }


    template<typename StringT>
        requires std::is_same_v<StringT, AnsiString> || std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::string_view>
    inline AnsiString Encode( const StringT& str )
    {
        if ( str.empty( ) == false )
        {
            return Encode( str.data( ), str.size( ) );
        }
        return {};
    }

    template<typename StringT>
        requires std::is_same_v<StringT, AnsiString> || std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::string_view>
    inline AnsiString Decode( const StringT& str )
    {
        if ( str.empty( ) == false )
        {
            return Decode( str.data( ), str.size( ) );
        }
        return {};
    }



    HCC_EXPORT std::span<const NamedChar> CharactersByName( );
    HCC_EXPORT std::span<const NamedChar> CharactersByValue( );

}

#endif
