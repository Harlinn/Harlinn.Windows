// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0
#include "pch.h"

#include <pbrto/util/error.h>

#include <pbrto/util/check.h>
#include <pbrto/util/display.h>
#include <pbrto/util/parallel.h>
#include <pbrto/util/print.h>

#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>

#ifdef PBRT_IS_WINDOWS
#include <windows.h>
#endif

namespace pbrt
{

    static bool quiet = false;

    PBRTO_EXPORT void SuppressErrorMessages( )
    {
        quiet = true;
    }

    std::string FileLoc::ToString( ) const
    {
        return StringPrintf( "%s:%d:%d", std::string( filename.data( ), filename.size( ) ), line,
            column );
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
            LOG_VERBOSE( "%s", errorString );
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

        std::string result = StringPrintf( "%s (%d)", s, errorId );
        LocalFree( s );

        return result;
#else
        return StringPrintf( "%s (%d)", strerror( errorId ), errorId );
#endif
    }

}  // namespace pbrt
