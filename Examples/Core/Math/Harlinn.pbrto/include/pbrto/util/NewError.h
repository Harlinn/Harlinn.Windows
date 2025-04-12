#pragma once
#ifndef PBRTO_UTIL_NEWERROR_H_
#define PBRTO_UTIL_NEWERROR_H_

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
#include <pbrto/util/NewPrint.h>
#include <pbrto/util/NewPStd.h>



#include <string>
#include <string_view>

namespace pbrto
{

    // FileLoc Definition
    struct FileLoc
    {
        FileLoc( ) = default;
        FileLoc( std::string_view filename ) : filename( filename ) {}
        PBRTO_EXPORT
        std::string ToString( ) const;

        std::string_view filename;
        int line = 1, column = 0;
    };

    PBRTO_EXPORT
    void SuppressErrorMessages( );

    // Error Reporting Function Declarations
    PBRTO_EXPORT
    void Warning( const FileLoc* loc, const char* message );
    PBRTO_EXPORT
    void Error( const FileLoc* loc, const char* message );

    [[noreturn]]
    void PBRTO_EXPORT
    ErrorExit( const FileLoc* loc, const char* message );

    template <typename... Args>
    inline void Warning( const char* fmt, Args &&...args );
    template <typename... Args>
    inline void Error( const char* fmt, Args &&...args );
    template <typename... Args>
    [[noreturn]] inline void ErrorExit( const char* fmt, Args &&...args );

    // Error Reporting Inline Functions
    template <typename... Args>
    inline void Warning( const FileLoc* loc, const char* fmt, Args &&...args )
    {
        Warning( loc, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    template <typename... Args>
    inline void Warning( const char* fmt, Args &&...args )
    {
        Warning( nullptr, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    template <typename... Args>
    inline void Error( const char* fmt, Args &&...args )
    {
        Error( nullptr, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    template <typename... Args>
    inline void Error( const FileLoc* loc, const char* fmt, Args &&...args )
    {
        Error( loc, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    template <typename... Args>
    [[noreturn]] inline void ErrorExit( const char* fmt, Args &&...args )
    {
        ErrorExit( nullptr, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    template <typename... Args>
    [[noreturn]] inline void ErrorExit( const FileLoc* loc, const char* fmt, Args &&...args )
    {
        ErrorExit( loc, StringPrintf( fmt, std::forward<Args>( args )... ).c_str( ) );
    }

    PBRTO_EXPORT int LastError( );
    PBRTO_EXPORT std::string ErrorString( int errorId = LastError( ) );

}

#endif
