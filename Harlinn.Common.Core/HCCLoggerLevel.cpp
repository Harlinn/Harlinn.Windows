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

#include "pch.h"
#include "HCCLoggerLevel.h"

namespace Harlinn::Common::Core::Logging
{
    template<WideStringLike StringT>
    HCC_TEMPLATE_EXPORT_DECL StringT ToString( Level level )
    {
        if ( level == Level::None )
        {
            return StringT(L"None");
        }
        else if ( level == Level::SystemStart )
        {
            return StringT( L"Start" );
        }
        else if ( level == Level::SystemStop )
        {
            return StringT( L"Stop" );
        }
        else if ( level == Level::All )
        {
            return StringT( L"All" );
        }
        else
        {
            StringT result;
            int count = 0;
            if ( (level & Level::Verbose) == Level::Verbose )
            {
                result = L"Verbose";
                count++;
            }
            if ( ( level & Level::Trace ) == Level::Trace )
            {
                result += count ? L"|Trace" : L"Trace";
                count++;
            }
            if ( ( level & Level::Debug ) == Level::Debug )
            {
                result += count ? L"|Debug" : L"Debug";
                count++;
            }
            if ( ( level & Level::Info ) == Level::Info )
            {
                result += count ? L"|Info" : L"Info";
                count++;
            }
            if ( ( level & Level::Notice ) == Level::Notice )
            {
                result += count ? L"|Notice" : L"Notice";
                count++;
            }
            if ( ( level & Level::Warning ) == Level::Warning )
            {
                result += count ? L"|Warning" : L"Warning";
                count++;
            }
            if ( ( level & Level::Error ) == Level::Error )
            {
                result += count ? L"|Error" : L"Error";
                count++;
            }
            if ( ( level & Level::Exception ) == Level::Exception )
            {
                result += count ? L"|Exception" : L"Exception";
                count++;
            }
            if ( ( level & Level::Critical ) == Level::Critical )
            {
                result += count ? L"|Critical" : L"Critical";
                count++;
            }
            if ( ( level & Level::Alert ) == Level::Alert )
            {
                result += count ? L"|Alert" : L"Alert";
                count++;
            }
            if ( ( level & Level::Emergency ) == Level::Emergency )
            {
                result += count ? L"|Emergency" : L"Emergency";
                count++;
            }
            if ( ( level & Level::System ) == Level::System )
            {
                result += count ? L"|System" : L"System";
                count++;
            }
            return result;
        }
    }

    template HCC_EXPORT WideString ToString<WideString>( Level level );
    template HCC_EXPORT std::wstring ToString<std::wstring>( Level level );


    template<AnsiStringLike StringT>
    HCC_TEMPLATE_EXPORT_DECL StringT ToString( Level level )
    {
        if ( level == Level::None )
        {
            return StringT("None");
        }
        else if ( level == Level::SystemStart )
        {
            return StringT( "Start" );
        }
        else if ( level == Level::SystemStop )
        {
            return StringT( "Stop" );
        }
        else if ( level == Level::All )
        {
            return StringT( "All" );
        }
        else
        {
            StringT result;
            int count = 0;
            if ( ( level & Level::Verbose ) == Level::Verbose )
            {
                result = "Verbose";
                count++;
            }
            if ( ( level & Level::Trace ) == Level::Trace )
            {
                result += count ? "|Trace" : "Trace";
                count++;
            }
            if ( ( level & Level::Debug ) == Level::Debug )
            {
                result += count ? "|Debug" : "Debug";
                count++;
            }
            if ( ( level & Level::Info ) == Level::Info )
            {
                result += count ? "|Info" : "Info";
                count++;
            }
            if ( ( level & Level::Notice ) == Level::Notice )
            {
                result += count ? "|Notice" : "Notice";
                count++;
            }
            if ( ( level & Level::Warning ) == Level::Warning )
            {
                result += count ? "|Warning" : "Warning";
                count++;
            }
            if ( ( level & Level::Error ) == Level::Error )
            {
                result += count ? "|Error" : "Error";
                count++;
            }
            if ( ( level & Level::Exception ) == Level::Exception )
            {
                result += count ? "|Exception" : "Exception";
                count++;
            }
            if ( ( level & Level::Critical ) == Level::Critical )
            {
                result += count ? "|Critical" : "Critical";
                count++;
            }
            if ( ( level & Level::Alert ) == Level::Alert )
            {
                result += count ? "|Alert" : "Alert";
                count++;
            }
            if ( ( level & Level::Emergency ) == Level::Emergency )
            {
                result += count ? "|Emergency" : "Emergency";
                count++;
            }
            if ( ( level & Level::System ) == Level::System )
            {
                result += count ? "|System" : "System";
                count++;
            }
            return result;
        }
    }
    template HCC_EXPORT AnsiString ToString<AnsiString>( Level level );
    template HCC_EXPORT std::string ToString<std::string>( Level level );


    bool TryParse( const std::wstring_view& str, Level& result )
    {
        result = Level::None;
        if ( str == L"None" || str.size() == 0 )
        {
            return true;
        }
        else if ( str == L"Start" )
        {
            result = Level::SystemStart;
            return true;
        }
        else if ( str == L"Stop" )
        {
            result = Level::SystemStop;
            return true;
        }
        else if ( str == L"All" )
        {
            result = Level::All;
            return true;
        }
        else if ( str == L"Default" )
        {
            result = Level::Default;
            return true;
        }
        else
        {
            WideStringView view = str;
            std::vector<std::wstring_view> flags;
            view.Split(L'|', flags );

            for ( auto& flag : flags )
            {
                if ( flag == L"Verbose" )
                {
                    result |= Level::Verbose;
                }
                else if ( flag == L"Trace" )
                {
                    result |= Level::Trace;
                }
                else if ( flag == L"Debug" )
                {
                    result |= Level::Debug;
                }
                else if ( flag == L"Info" )
                {
                    result |= Level::Info;
                }
                else if ( flag == L"Notice" )
                {
                    result |= Level::Notice;
                }
                else if ( flag == L"Warning" )
                {
                    result |= Level::Warning;
                }
                else if ( flag == L"Error" )
                {
                    result |= Level::Error;
                }
                else if ( flag == L"Exception" )
                {
                    result |= Level::Exception;
                }
                else if ( flag == L"Critical" )
                {
                    result |= Level::Critical;
                }
                else if ( flag == L"Alert" )
                {
                    result |= Level::Alert;
                }
                else if ( flag == L"Emergency" )
                {
                    result |= Level::Emergency;
                }
                else if ( flag == L"System" )
                {
                    result |= Level::System;
                }
                else if ( flag == L"Default" )
                {
                    result |= Level::Default;
                }
            }
            return true;
        }
    }
    bool TryParse( const std::string_view& str, Level& result )
    {
        result = Level::None;
        if ( str == "None" || str.size( ) == 0 )
        {
            return true;
        }
        else if ( str == "Start" )
        {
            result = Level::SystemStart;
            return true;
        }
        else if ( str == "Stop" )
        {
            result = Level::SystemStop;
            return true;
        }
        else if ( str == "All" )
        {
            result = Level::All;
            return true;
        }
        else if ( str == "Default" )
        {
            result = Level::Default;
            return true;
        }
        else
        {
            AnsiStringView view = str;
            std::vector<std::string_view> flags;
            view.Split( '|', flags );

            for ( auto& flag : flags )
            {
                if ( flag == "Verbose" )
                {
                    result |= Level::Verbose;
                }
                else if ( flag == "Trace" )
                {
                    result |= Level::Trace;
                }
                else if ( flag == "Debug" )
                {
                    result |= Level::Debug;
                }
                else if ( flag == "Info" )
                {
                    result |= Level::Info;
                }
                else if ( flag == "Notice" )
                {
                    result |= Level::Notice;
                }
                else if ( flag == "Warning" )
                {
                    result |= Level::Warning;
                }
                else if ( flag == "Error" )
                {
                    result |= Level::Error;
                }
                else if ( flag == "Exception" )
                {
                    result |= Level::Exception;
                }
                else if ( flag == "Critical" )
                {
                    result |= Level::Critical;
                }
                else if ( flag == "Alert" )
                {
                    result |= Level::Alert;
                }
                else if ( flag == "Emergency" )
                {
                    result |= Level::Emergency;
                }
                else if ( flag == "System" )
                {
                    result |= Level::System;
                }
                else if ( flag == "Default" )
                {
                    result |= Level::Default;
                }
            }
            return true;
        }
    }
}