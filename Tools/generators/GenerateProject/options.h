#pragma once
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <boost/program_options.hpp>
#include <iostream>
#include <HCCString.h>

namespace GenerateProject
{
    namespace po = boost::program_options;
    using namespace Harlinn::Common::Core;


    class Options
    {
        // Template name
        AnsiString templateName_;
        // Project name
        AnsiString projectName_;
        bool valid_ = false;
    public:
        Options( int argc, char* argv[] )
        {
            std::string templateName;
            std::string projectName;
            po::options_description desc( "Options" );
            desc.add_options( )
                ( "help", "displays this help message." )
                ( "template", po::value< std::string >( &templateName ), "template name." )
                ( "project", po::value< std::string >( &projectName ), "template name." );

            po::positional_options_description p;
            p.add( "project", -1 );

            po::variables_map vm;
            po::store( po::command_line_parser( argc, argv )
                .options( desc )
                .positional( p ).run( ), vm );
            po::notify( vm );

            templateName_ = templateName;
            projectName_ = projectName;

            if ( vm.count( "help" ) || templateName_.empty( ) || projectName_.empty( ) )
            {
                std::cout << desc << "\n";
            }
            else
            {
                valid_ = true;
            }

        }

        const AnsiString& TemplateName( ) const noexcept
        {
            return templateName_;
        }
        const AnsiString& ProjectName( ) const noexcept
        {
            return projectName_;
        }
        bool IsValid( ) const noexcept
        {
            return valid_;
        }

    };
}



