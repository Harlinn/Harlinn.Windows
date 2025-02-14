#pragma once
#ifndef __HCCLOGGEROPTIONS_H__
#define __HCCLOGGEROPTIONS_H__
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

#include <HCCLoggerLMDBSinkOptions.h>
#include <HCCLoggerTextSinkOptions.h>
#include <HCCLoggerLevel.h>


namespace Harlinn::Common::Core::Logging
{
    class LoggerOptions : public std::enable_shared_from_this<LoggerOptions>
    {
        Level enabledLevels_ = Level::Default;
        TimeSpan pollInterval_{ TimeSpan::TicksPerSecond * 5 };
        //ConsoleSinkOptions consoleSinkOptions_;
        std::shared_ptr<Sinks::LMDBSinkOptions> lmdbSinkOptions_;
        std::shared_ptr<Sinks::TextSinkOptions> textSinkOptions_;
    public:
        using Element = Xml::Dom::Element;
        LoggerOptions()
            : lmdbSinkOptions_( std::make_shared<Sinks::LMDBSinkOptions>( ) ),
              textSinkOptions_( std::make_shared<Sinks::TextSinkOptions>( ) )
        { }

        explicit LoggerOptions( Level enabledLevels )
            : enabledLevels_( enabledLevels ), 
              lmdbSinkOptions_( std::make_shared<Sinks::LMDBSinkOptions>( ) ),
              textSinkOptions_( std::make_shared<Sinks::TextSinkOptions>( ) )
        {
        }


        void ReadFrom( const Element& element )
        {
            auto sinksElement = element.FindElement( L"Sinks" );
            if ( sinksElement )
            {
                auto lmdbElement = sinksElement.FindElement( L"LMDB" );
                if ( lmdbElement )
                {
                    lmdbSinkOptions_->ReadFrom( lmdbElement );
                }
                auto textElement = sinksElement.FindElement( L"Text" );
                if ( textElement )
                {
                    textSinkOptions_->ReadFrom( textElement );
                }
            }

            if ( element.HasAttribute( L"EnabledLevels" ) )
            {
                auto str = element.Read<WideString>( L"EnabledLevels" );
                Logging::Level enabledLevels{};
                if ( Logging::TryParse( str, enabledLevels ) )
                {
                    enabledLevels_ = enabledLevels;
                }
            }
            
        }

        Level EnabledLevels( ) const noexcept
        {
            return enabledLevels_;
        }

        TimeSpan PollInterval( ) const noexcept
        {
            return pollInterval_;
        }

        //ConsoleSinkOptions consoleSinkOptions_;
        const std::shared_ptr<Sinks::LMDBSinkOptions>& LMDBSinkOptions( ) const noexcept
        {
            return lmdbSinkOptions_;
        }

        const std::shared_ptr<Sinks::TextSinkOptions>& TextSinkOptions( ) const noexcept
        {
            return textSinkOptions_;
        }

    };

}

#endif
