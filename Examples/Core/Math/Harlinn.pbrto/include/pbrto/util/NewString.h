#pragma once
#ifndef PBRTO_UTIL_NEWSTRING_H_
#define PBRTO_UTIL_NEWSTRING_H_

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

#include <pbrto/NewPbrt.h>

#include <ctype.h>
#include <string>
#include <string_view>
#include <vector>

namespace pbrto
{

    PBRTO_EXPORT bool Atoi( std::string_view str, int* );
    PBRTO_EXPORT bool Atoi( std::string_view str, int64_t* );
    PBRTO_EXPORT bool Atof( std::string_view str, float* );
    PBRTO_EXPORT bool Atof( std::string_view str, double* );

    PBRTO_EXPORT std::vector<std::string> SplitStringsFromWhitespace( std::string_view str );

    PBRTO_EXPORT std::vector<std::string> SplitString( std::string_view str, char ch );
    PBRTO_EXPORT std::vector<int> SplitStringToInts( std::string_view str, char ch );
    PBRTO_EXPORT std::vector<int64_t> SplitStringToInt64s( std::string_view str, char ch );
    PBRTO_EXPORT std::vector<Float> SplitStringToFloats( std::string_view str, char ch );
    PBRTO_EXPORT std::vector<double> SplitStringToDoubles( std::string_view str, char ch );

    // String Utility Function Declarations
    PBRTO_EXPORT std::string UTF8FromUTF16( std::u16string str );
    PBRTO_EXPORT std::u16string UTF16FromUTF8( std::string str );

#ifdef PBRT_IS_WINDOWS
    PBRTO_EXPORT std::wstring WStringFromUTF8( std::string str );
    PBRTO_EXPORT std::string UTF8FromWString( std::wstring str );
#endif  // PBRT_IS_WINDOWS

    PBRTO_EXPORT std::string NormalizeUTF8( std::string str );

    // InternedString Definition
    class InternedString
    {
    public:
        // InternedString Public Methods
        InternedString( ) = default;
        InternedString( const std::string* str ) : str( str ) {}
        operator const std::string& ( ) const { return *str; }

        bool operator==( const char* s ) const { return *str == s; }
        bool operator==( const std::string& s ) const { return *str == s; }
        bool operator!=( const char* s ) const { return *str != s; }
        bool operator!=( const std::string& s ) const { return *str != s; }
        bool operator<( const char* s ) const { return *str < s; }
        bool operator<( const std::string& s ) const { return *str < s; }

        std::string ToString( ) const { return *str; }

    private:
        const std::string* str = nullptr;
    };

    // InternedStringHash Definition
    struct InternedStringHash
    {
        size_t operator()( const InternedString& s ) const
        {
            return std::hash<std::string>( )( s );
        }
    };

}

#endif
