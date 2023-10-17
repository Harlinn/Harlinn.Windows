#pragma once
#ifndef __HCCLOGGEROPTIONS_H__
#define __HCCLOGGEROPTIONS_H__

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
