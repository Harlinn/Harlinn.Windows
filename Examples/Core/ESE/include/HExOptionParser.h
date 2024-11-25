#pragma once
#ifndef __HEXOPTIONPARSER_H__
#define __HEXOPTIONPARSER_H__
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
        return std::string(buffer);
    }

    inline bool ParseOptions( int argc, char* argv[], EngineOptions& options )
    {

        std::string databasePath;
        std::string systemPath;
        std::string logFilePath;

        options_description desc( "Allowed options" );
        desc.add_options( )
            ( "help,?", "print usage message" )
            ( "database,d", value( &databasePath ), "database path" )
            ( "systempath,s", value( &systemPath ), "checkpoint file directory" )
            ( "logfilepath,l", value( &logFilePath ), "transaction log file directory" )
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


        options.Database = databasePath;
        options.SystemPath = systemPath;
        options.LogFilePath = logFilePath;


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
                options.SystemPath = std::string(directory.c_str(), directory.length()) + "System\\";
            }
            if ( options.LogFilePath.empty( ) )
            {
                auto directory = GetDirectory( options.Database );
                options.LogFilePath = std::string( directory.c_str( ), directory.length( ) ) + "Log\\";
            }
            return true;
        }
    }

}

#endif