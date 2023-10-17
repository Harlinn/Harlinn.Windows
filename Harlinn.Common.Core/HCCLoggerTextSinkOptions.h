#pragma once
#ifndef HCCLOGGERTEXTSINKOPTIONS_H_
#define HCCLOGGERTEXTSINKOPTIONS_H_

#include <HCCDef.h>
#include <HCCLoggerLevel.h>
#include <HCCString.h>
#include <HCCXml.h>

namespace Harlinn::Common::Core::Logging::Sinks
{
    class TextSinkOptions : std::enable_shared_from_this<TextSinkOptions>
    {
        WideString filename_;
        Logging::Level enabledLevels_ = Logging::Level::Default;
        bool enabled_ = false;
    public:
        using Element = Xml::Dom::Element;
        TextSinkOptions( ) 
            : filename_( L"c:\\Logs\\HCCService01.log" )
        {
        }
        TextSinkOptions( const WideString& filename, Logging::Level enabledLevels = Logging::Level::Default )
            : filename_( filename ), enabledLevels_( enabledLevels ) 
        {

        }

        void ReadFrom( const Element& element )
        {
            if ( element.HasAttribute( L"Filename" ) )
            {
                filename_ = element.Read<WideString>( L"Filename" );
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
            if ( element.HasAttribute( L"Enabled" ) )
            {
                enabled_ = element.Read<bool>( L"Enabled" );
            }
        }

        constexpr bool Enabled( ) const noexcept
        {
            return enabled_;
        }
        void SetEnabled( bool value = true )
        {
            enabled_ = value;
        }


        constexpr const WideString& Filename( ) const noexcept
        {
            return filename_;
        }
        void SetFilename( const WideString& filename )
        {
            filename_ = filename;
        }

        constexpr Logging::Level EnabledLevels( ) const noexcept
        {
            return enabledLevels_;
        }
        void SetEnabledLevels( Logging::Level enabledLevels )
        {
            enabledLevels_ = enabledLevels;
        }

    };
}

#endif
