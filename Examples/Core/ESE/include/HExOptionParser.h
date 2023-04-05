#pragma once
#ifndef __HEXOPTIONPARSER_H__
#define __HEXOPTIONPARSER_H__

#include <HExEngine.h>
#include <iostream>

#include <boost/program_options.hpp>

namespace Harlinn::Common::Core::Examples
{
    namespace
    {
        using namespace boost::program_options;
    }

    inline std::string GetDirectory( const std::string& filename )
    {
        char drive[_MAX_DRIVE + 1];
        char directory[_MAX_DIR + 1];
        _splitpath( filename.c_str( ), drive, directory, nullptr, nullptr );
        char buffer[_MAX_PATH + 1];
        _makepath( buffer, drive, directory, nullptr, nullptr );
        return buffer;
    }

    inline bool ParseOptions( int argc, char* argv[], EngineOptions& options )
    {
        options_description desc( "Allowed options" );
        desc.add_options( )
            ( "help,?", "print usage message" )
            ( "database,d", value( &options.Database ), "database path" )
            ( "systempath,s", value( &options.SystemPath ), "checkpoint file directory" )
            ( "logfilepath,l", value( &options.LogFilePath ), "transaction log file directory" )
            ( "create,c", bool_switch( &options.Create ), "Create new database" )
            ( "replace,r", bool_switch( &options.Replace ), "Replace existing database" )
            ( "unsafe,u", bool_switch( &options.Unsafe ), "Improve performance by reducing resilience" )
            ( "test,t", bool_switch( &options.RunTests ), "Run tests" )
            ( "port,p", value( &options.Port ), "port" );

        variables_map vm;

        positional_options_description p;
        p.add( "database", 1 );

        store( command_line_parser( argc, argv ).options( desc ).positional( p ).run( ), vm );
        notify( vm );

        if ( vm.count( "help" ) || options.Database.empty() )
        {
            std::cout << desc << "\n";
            return false;
        }
        else
        {
            if ( options.SystemPath.empty( ) )
            {
                auto directory = GetDirectory( options.Database );
                options.SystemPath = directory + "System\\";
            }
            if ( options.LogFilePath.empty( ) )
            {
                auto directory = GetDirectory( options.Database );
                options.LogFilePath = directory + "Log\\";
            }
            return true;
        }
    }

}

#endif