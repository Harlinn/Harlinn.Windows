#include "pch.h"

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/NewArgs.h>

#ifdef PBRT_IS_WINDOWS
#include <Windows.h>
#endif

namespace pbrto
{

    PBRTO_EXPORT
        std::vector<std::string> GetCommandLineArguments( char* argv[ ] )
    {
        std::vector<std::string> argStrings;
#ifdef PBRT_IS_WINDOWS
        // Handle UTF16-encoded arguments on Windows
        int argc;
        LPWSTR* argvw = CommandLineToArgvW( GetCommandLineW( ), &argc );
        NCHECK( argv != nullptr );
        for ( int i = 1; i < argc; ++i )
            argStrings.push_back( UTF8FromWString( argvw[ i ] ) );
#else
        ++argv;  // skip executable name
        while ( *argv )
        {
            argStrings.push_back( *argv );
            ++argv;
        }
#endif  // PBRT_IS_WINDOWS
        return argStrings;
    }

}