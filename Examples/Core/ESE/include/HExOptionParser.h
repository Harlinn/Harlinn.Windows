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

    inline WideString GetDirectory( const WideString& filename )
    {
        wchar_t drive[_MAX_DRIVE + 1];
        wchar_t directory[_MAX_DIR + 1];
        _wsplitpath( filename.c_str( ), drive, directory, nullptr, nullptr );
        wchar_t buffer[_MAX_PATH + 1];
        _wmakepath( buffer, drive, directory, nullptr, nullptr );
        return WideString(buffer);
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


        options.Database = WideString::From( databasePath );
        options.SystemPath = WideString::From( systemPath );
        options.LogFilePath = WideString::From( logFilePath );


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
                options.SystemPath = WideString(directory.c_str(), directory.length()) + L"System\\";
            }
            if ( options.LogFilePath.empty( ) )
            {
                auto directory = GetDirectory( options.Database );
                options.LogFilePath = WideString( directory.c_str( ), directory.length( ) ) + L"Log\\";
            }
            return true;
        }
    }

}

#endif