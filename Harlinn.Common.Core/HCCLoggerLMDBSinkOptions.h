#pragma once
#ifndef __HCCLOGGERLMDBSINKOPTIONS_H__
#define __HCCLOGGERLMDBSINKOPTIONS_H__

#include <HCCDef.h>
#include <HCCLoggerLevel.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::Logging::Sinks
{
    class LMDBSinkOptions
    {
        AnsiString databaseDirectory_;
        Logging::Level enabledLevels_ = Logging::Level::Default;
    public:
        LMDBSinkOptions()
        { }
        LMDBSinkOptions( const AnsiString& databaseDirectory, Logging::Level enabledLevels = Logging::Level::Default )
            : databaseDirectory_( databaseDirectory ), enabledLevels_( enabledLevels )
        {
        }


        void Load( )
        {

        }


        constexpr const AnsiString& DatabaseDirectory( ) const noexcept
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
