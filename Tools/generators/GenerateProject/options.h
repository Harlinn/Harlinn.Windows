#pragma once
#include <boost/program_options.hpp>
#include <iostream>

namespace GenerateProject
{
    namespace po = boost::program_options;


    class Options
    {
        // Template name
        std::string templateName_;
        // Project name
        std::string projectName_;
        bool valid_ = false;
    public:
        Options( int argc, char* argv[] )
        {
            po::options_description desc( "Options" );
            desc.add_options( )
                ( "help", "displays this help message." )
                ( "template", po::value< std::string >( &templateName_ ), "template name." )
                ( "project", po::value< std::string >( &projectName_ ), "template name." );

            po::positional_options_description p;
            p.add( "project", -1 );

            po::variables_map vm;
            po::store( po::command_line_parser( argc, argv )
                .options( desc )
                .positional( p ).run( ), vm );
            po::notify( vm );

            if ( vm.count( "help" ) || templateName_.empty( ) || projectName_.empty( ) )
            {
                std::cout << desc << "\n";
            }
            else
            {
                valid_ = true;
            }

        }

        const std::string& TemplateName( ) const noexcept
        {
            return templateName_;
        }
        const std::string& ProjectName( ) const noexcept
        {
            return projectName_;
        }
        bool IsValid( ) const noexcept
        {
            return valid_;
        }

    };
}



