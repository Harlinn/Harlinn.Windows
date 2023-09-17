#pragma once
#ifndef __HCCLOGGERLMDBSINKOPTIONS_H__
#define __HCCLOGGERLMDBSINKOPTIONS_H__

#include <HCCDef.h>
#include <HCCLoggerLevel.h>
#include <HCCString.h>
#include <HCCXml.h>

namespace Harlinn::Common::Core::Logging::Sinks
{
    class LMDBSinkOptions : std::enable_shared_from_this<LMDBSinkOptions>
    {
        WideString databaseDirectory_;
        Logging::Level enabledLevels_ = Logging::Level::Default;
        bool enabled_ = true;
    public:
        using Element = Xml::Dom::Element;
        LMDBSinkOptions()
        { }
        LMDBSinkOptions( const WideString& databaseDirectory, Logging::Level enabledLevels = Logging::Level::Default )
            : databaseDirectory_( databaseDirectory ), enabledLevels_( enabledLevels )
        {

        }

        void ReadFrom( const Element& element )
        {
            if ( element.HasAttribute( L"DatabaseDirectory" ) )
            {
                databaseDirectory_ = element.Read<WideString>( L"DatabaseDirectory" );
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


        constexpr const WideString& DatabaseDirectory( ) const noexcept
        {
            return databaseDirectory_;
        }
        constexpr Logging::Level EnabledLevels( ) const noexcept
        {
            return enabledLevels_;
        }

    };
}

#endif
