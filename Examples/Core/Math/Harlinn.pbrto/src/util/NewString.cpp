#include "pch.h"

/*
   Copyright 2024-2025 Espen Harlinn

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifdef PBRT_IS_WINDOWS
#ifndef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif
#endif  // PBRT_IS_WINDOWS

#include <pbrto/util/NewString.h>

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewError.h>

#ifndef UTF8PROC_STATIC
#define UTF8PROC_STATIC
#endif
#include <utf8proc/utf8proc.h>

#include <ctype.h>
#include <codecvt>
#include <locale>
#include <string>

namespace pbrto
{

    PBRTO_EXPORT
        bool Atoi( std::string_view str, int* ptr )
    {
        try
        {
            *ptr = std::stoi( std::string( str.begin( ), str.end( ) ) );
        }
        catch ( ... )
        {
            return false;
        }
        return true;
    }

    PBRTO_EXPORT
        bool Atoi( std::string_view str, int64_t* ptr )
    {
        try
        {
            *ptr = std::stoll( std::string( str.begin( ), str.end( ) ) );
        }
        catch ( ... )
        {
            return false;
        }
        return true;
    }

    PBRTO_EXPORT
        bool Atof( std::string_view str, float* ptr )
    {
        try
        {
            *ptr = std::stof( std::string( str.begin( ), str.end( ) ) );
        }
        catch ( ... )
        {
            return false;
        }
        return true;
    }

    PBRTO_EXPORT
        bool Atof( std::string_view str, double* ptr )
    {
        try
        {
            *ptr = std::stod( std::string( str.begin( ), str.end( ) ) );
        }
        catch ( ... )
        {
            return false;
        }
        return true;
    }

    PBRTO_EXPORT
        std::vector<std::string> SplitStringsFromWhitespace( std::string_view str )
    {
        std::vector<std::string> ret;

        std::string_view::iterator start = str.begin( );
        do
        {
            // skip leading ws
            while ( start != str.end( ) && isspace( *start ) )
                ++start;

            // |start| is at the start of the current word
            auto end = start;
            while ( end != str.end( ) && !isspace( *end ) )
                ++end;

            ret.push_back( std::string( start, end ) );
            start = end;
        } while ( start != str.end( ) );

        return ret;
    }

    PBRTO_EXPORT
        std::vector<std::string> SplitString( std::string_view str, char ch )
    {
        std::vector<std::string> strings;

        if ( str.empty( ) )
            return strings;

        std::string_view::iterator begin = str.begin( );
        while ( true )
        {
            std::string_view::iterator end = begin;
            while ( end != str.end( ) && *end != ch )
                ++end;

            strings.push_back( std::string( begin, end ) );

            if ( end == str.end( ) )
                break;

            begin = end + 1;
        }

        return strings;
    }

    PBRTO_EXPORT
        std::vector<int> SplitStringToInts( std::string_view str, char ch )
    {
        std::vector<std::string> strs = SplitString( str, ch );
        std::vector<int> ints( strs.size( ) );

        for ( size_t i = 0; i < strs.size( ); ++i )
            if ( !Atoi( strs[ i ], &ints[ i ] ) )
                return {};
        return ints;
    }

    PBRTO_EXPORT
        std::vector<int64_t> SplitStringToInt64s( std::string_view str, char ch )
    {
        std::vector<std::string> strs = SplitString( str, ch );
        std::vector<int64_t> ints( strs.size( ) );

        for ( size_t i = 0; i < strs.size( ); ++i )
            if ( !Atoi( strs[ i ], &ints[ i ] ) )
                return {};
        return ints;
    }

    PBRTO_EXPORT
        std::vector<Float> SplitStringToFloats( std::string_view str, char ch )
    {
        std::vector<std::string> strs = SplitString( str, ch );
        std::vector<Float> floats( strs.size( ) );

        for ( size_t i = 0; i < strs.size( ); ++i )
            if ( !Atof( strs[ i ], &floats[ i ] ) )
                return {};
        return floats;
    }

    PBRTO_EXPORT
        std::vector<double> SplitStringToDoubles( std::string_view str, char ch )
    {
        std::vector<std::string> strs = SplitString( str, ch );
        std::vector<double> doubles( strs.size( ) );

        for ( size_t i = 0; i < strs.size( ); ++i )
            if ( !Atof( strs[ i ], &doubles[ i ] ) )
                return {};
        return doubles;
    }

#ifdef PBRT_IS_WINDOWS
    PBRTO_EXPORT
        std::wstring WStringFromU16String( std::u16string str )
    {
        std::wstring ws;
        ws.reserve( str.size( ) );
        for ( char16_t c : str )
            ws.push_back( c );
        return ws;
    }

    PBRTO_EXPORT
        std::wstring WStringFromUTF8( std::string str )
    {
        return WStringFromU16String( UTF16FromUTF8( str ) );
    }

    PBRTO_EXPORT
        std::u16string U16StringFromWString( std::wstring str )
    {
        std::u16string su16;
        su16.reserve( str.size( ) );
        for ( wchar_t c : str )
            su16.push_back( c );
        return su16;
    }

    PBRTO_EXPORT
        std::string UTF8FromWString( std::wstring str )
    {
        return UTF8FromUTF16( U16StringFromWString( str ) );
    }

#endif  // PBRT_IS_WINDOWS

    // https://stackoverflow.com/a/52703954
    PBRTO_EXPORT
        std::string UTF8FromUTF16( std::u16string str )
    {
        std::wstring_convert<
            std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>,
            char16_t>
            cnv;
        std::string utf8 = cnv.to_bytes( str );
        NCHECK_GE( cnv.converted( ), str.size( ) );
        return utf8;
    }

    PBRTO_EXPORT
        std::u16string UTF16FromUTF8( std::string str )
    {
        std::wstring_convert<
            std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>,
            char16_t>
            cnv;
        std::u16string utf16 = cnv.from_bytes( str );
        NCHECK_GE( cnv.converted( ), str.size( ) );
        return utf16;
    }

    PBRTO_EXPORT
        std::string NormalizeUTF8( std::string str )
    {
        utf8proc_option_t options = UTF8PROC_COMPOSE;

        utf8proc_uint8_t* result;
        utf8proc_ssize_t length =
            utf8proc_map( ( const unsigned char* )str.data( ), str.size( ), &result, options );
        if ( length < 0 )
            ErrorExit( "Unicode normalization error: %s: \"%s\"", utf8proc_errmsg( length ),
                str );

        str = std::string( result, result + length );
        free( result );
        return str;
    }

}