#pragma once
#ifndef __HCCLOGGERLMDBSINKOPTIONS_H__
#define __HCCLOGGERLMDBSINKOPTIONS_H__

#include <HCCDef.h>
#include <HCCLoggerLevel.h>

namespace Harlinn::Common::Core::Logging::Sinks
{
    class LMDBSinkOptions
    {
        std::string databaseDirectory_;
        Logging::Level enabledLevels_ = Logging::Level::Default;
    public:
        LMDBSinkOptions()
        { }
        LMDBSinkOptions( const std::string& databaseDirectory, Logging::Level enabledLevels = Logging::Level::Default )
            : databaseDirectory_( databaseDirectory ), enabledLevels_( enabledLevels )
        {
        }


        void Load( )
        {

        }


        constexpr const std::string& DatabaseDirectory( ) const noexcept
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
