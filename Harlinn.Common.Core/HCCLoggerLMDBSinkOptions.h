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
        WideString databaseDirectory_;
        Logging::Level enabledLevels_ = Logging::Level::Default;
    public:
        LMDBSinkOptions()
        { }
        LMDBSinkOptions( const WideString& databaseDirectory, Logging::Level enabledLevels = Logging::Level::Default )
            : databaseDirectory_( databaseDirectory ), enabledLevels_( enabledLevels )
        {

        }

        void AddOptions( boost::program_options::options_description& optionsDescription )
        {
            namespace po = boost::program_options;
            optionsDescription.add_options( )
                ( "log_sink_lmdb_database_directory", po::wvalue<WideString>(&databaseDirectory_ ), "" );
        }



        void Load( )
        {

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
