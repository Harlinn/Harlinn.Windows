#pragma once
#ifndef DOXYGEN2MDOPTIONS_H_
#define DOXYGEN2MDOPTIONS_H_

/*
   Copyright 2024-2026 Espen Harlinn

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
#include <HCCString.h>
#include <HCCIO.h>

namespace Doxygen2Md
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;


    class Doxygen2MdOptions
    {
        bool help_{};
        std::string inputDirectory_;
        std::string outputDirectory_;
        std::string substitutionTable_;
        std::string templates_;
        std::string siteUrl_;
        std::string relativeOutputUrl_;

        std::string header_;
    public:
        Doxygen2MdOptions( ) = default;

        bool Help( ) const { return help_; }
        const std::string& InputDirectory( ) const { return inputDirectory_; }
        const std::string& OutputDirectory( ) const { return outputDirectory_; }
        const std::string& SubstitutionTable( ) const { return substitutionTable_; }
        bool HasSubstitutionTable( ) const
        {
            return substitutionTable_.length( ) > 0 && IO::File::Exist( substitutionTable_ );
        }
        const std::string& Templates( ) const { return templates_; }
        const std::string& SiteUrl( ) const { return siteUrl_; }
        const std::string& RelativeOutputUrl( ) const { return relativeOutputUrl_; }

        bool IsValid( ) const
        {
            return ( inputDirectory_.empty( ) == false ) &&
                IO::Directory::Exist( inputDirectory_ ) &&
                ( outputDirectory_.empty( ) == false ) &&
                ( help_ == false );
        }

        bool Parse( int argc, char* argv[ ] )
        {
            namespace po = boost::program_options;

            po::options_description desc( "doxygen2md options" );
            desc.add_options( )
                ( "help", po::value<bool>( &help_ )->default_value( false ), "produce help message" )
                ( "doxygen,I", po::value< std::string >( &inputDirectory_ ), "directory containing doxygen generated xml files." )
                ( "md,O", po::value< std::string >( &outputDirectory_ ), "markdown destination directory." )
                ( "substitution,S", po::value< std::string >( &substitutionTable_ ), "Substitution table." )
                ( "templates,T", po::value< std::string >( &templates_ ), "template specification file." )
                ( "siteurl,U", po::value< std::string >( &siteUrl_ ), "Site url." )
                ( "relative,R", po::value< std::string >( &relativeOutputUrl_ ), "Url of the markdown destination directory relative to the site url." )
                ;

            po::variables_map vm;
            po::store( po::parse_command_line( argc, argv, desc ), vm );
            po::notify( vm );

            if ( IsValid( ) == false )
            {
                desc.print( std::cout );
                return false;
            }
            return true;
        }



    };

}
#endif
