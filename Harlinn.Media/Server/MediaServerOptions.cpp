#include "pch.h"
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
#include "MediaServerOptions.h"

namespace Harlinn::Media::Server
{
    
    void MediaServerOptions::ImportCommandLine( )
    {
        int argc = 0;
        wchar_t** wargv = CommandLineToArgvW( GetCommandLineW( ), &argc );
        if ( wargv )
        {
            for ( int i = 0; i < argc; i++ )
            {
                WideString ws( wargv[ i ] );
                if ( ws )
                {
                    emplace_back( ws );
                }
            }
            LocalFree( wargv );
        }
    }
    bool MediaServerOptions::Contains( const WideString& option )
    {
        const std::vector<WideString>& self = *this;
        for ( const auto& ws : self )
        {
            if ( ws == option )
            {
                return true;
            }
        }
        return false;
    }

}

