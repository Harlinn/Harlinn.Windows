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

#include <pbrto/util/NewError.h>

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewDisplay.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewLog.h>

#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>

#ifdef PBRT_IS_WINDOWS
#include <windows.h>
#endif

namespace pbrto
{

    static bool quiet = false;

    PBRTO_EXPORT void SuppressErrorMessages( )
    {
        quiet = true;
    }

    std::string FileLoc::ToString( ) const
    {
        auto s = std::string( filename.data( ), filename.size( ) );
        return std::format( "{}:{}:{}", s, line, column );
    }

    static void processError( const char* errorType, const FileLoc* loc, const char* message )
    {
        // Build up an entire formatted error string and print it all at once;
        // this way, if multiple threads are printing messages at once, they
        // don't get jumbled up...
        std::string errorString = Red( errorType );

        if ( loc )
            errorString += ": " + loc->ToString( );

        errorString += ": ";
        errorString += message;

        // Print the error message (but not more than one time).
        static std::string lastError;
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock( mutex );
        if ( errorString != lastError )
        {
            fprintf( stderr, "%s\n", errorString.c_str( ) );
            NLOG_VERBOSE( "{}", errorString );
            lastError = errorString;
        }
    }

    PBRTO_EXPORT void Warning( const FileLoc* loc, const char* message )
    {
        if ( quiet )
            return;
        processError( "Warning", loc, message );
    }

    PBRTO_EXPORT void Error( const FileLoc* loc, const char* message )
    {
        if ( quiet )
            return;
        processError( "Error", loc, message );
    }

    PBRTO_EXPORT void ErrorExit( const FileLoc* loc, const char* message )
    {
        processError( "Error", loc, message );
        DisconnectFromDisplayServer( );
#ifdef PBRT_IS_OSX
        exit( 1 );
#else
        std::quick_exit( 1 );
#endif
    }

    PBRTO_EXPORT int LastError( )
    {
#ifdef PBRT_IS_WINDOWS
        return GetLastError( );
#else
        return errno;
#endif
    }

    PBRTO_EXPORT std::string ErrorString( int errorId )
    {
#ifdef PBRT_IS_WINDOWS
        char* s = NULL;
        FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorId, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), ( LPSTR )&s, 0,
            NULL );

        std::string result = std::format( "{} ({})", s, errorId );
        LocalFree( s );

        return result;
#else
        return std::format( "{} ({})", strerror( errorId ), errorId );
#endif
    }

}
