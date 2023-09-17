#pragma once
#ifndef __HCCLOGGERBACKENDOPTIONS_H__
#define __HCCLOGGERBACKENDOPTIONS_H__

#include <HCCLoggerLMDBSinkOptions.h>
#include <HCCLoggerLevel.h>


namespace Harlinn::Common::Core::Logging
{
    class Backend;


    class BackendOptions : public std::enable_shared_from_this<BackendOptions>
    {
        Level enabledLevels_ = Level::Default;
        //ConsoleSinkOptions consoleSinkOptions_;
        std::shared_ptr<Sinks::LMDBSinkOptions> lmdbSinkOptions_;
    public:
        using Element = Xml::Dom::Element;
        BackendOptions()
            : lmdbSinkOptions_( std::make_shared<Sinks::LMDBSinkOptions>( ) )
        { }

        explicit BackendOptions( Level enabledLevels )
            : enabledLevels_( enabledLevels ), lmdbSinkOptions_( std::make_shared<Sinks::LMDBSinkOptions>() )
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
        //ConsoleSinkOptions consoleSinkOptions_;
        const std::shared_ptr<Sinks::LMDBSinkOptions>& LMDBSinkOptions( ) const noexcept
        {
            return lmdbSinkOptions_;
        }

    };

}

#endif
