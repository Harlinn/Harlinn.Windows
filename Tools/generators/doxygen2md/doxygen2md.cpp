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

#include "D2MMarkdownFormatter.h"

using namespace Doxygen2Md;
using namespace Harlinn::Common::Core;


int main(int argc, char* argv[] )
{
    using namespace Harlinn::Common::Core;
    using namespace Doxygen2Md;

    Doxygen2MdOptions options;
    

    if ( options.Parse( argc, argv ) )
    {
        Doxygen::DocumentCollection documentCollection;
        auto directory = options.InputDirectory();
        documentCollection.AddDirectory( to_wstring( directory ) );
        auto typeSystem = documentCollection.TypeSystem( );
        const auto& allCompoundDefs = typeSystem->AllCompoundDefs( );
        auto allCompoundDefsSize = allCompoundDefs.size( );
        
        PathBuilder pathBuilder( options.OutputDirectory( ), options.SiteUrl( ), options.RelativeOutputUrl( ) );
        std::vector<std::string> paths;
        for ( const auto& entry : allCompoundDefs )
        {
            auto compoundDef = entry.second;
            auto kind = compoundDef->Kind( );
            if ( kind != Doxygen::DoxCompoundKind::Dir && kind != Doxygen::DoxCompoundKind::File )
            {
                auto path = pathBuilder.FilePathOf( compoundDef );
                paths.emplace_back( path );
            }
        }

        size_t unexpectedCompoundName = 0;
        std::multimap<std::string, std::string> unexpectedCompoundNames;
        for ( const auto& entry : allCompoundDefs )
        {
            auto compoundDef = entry.second;
            
            auto kind = compoundDef->Kind( );
            
            if ( compoundDef->Language() == Doxygen::DoxLanguage::Cpp && kind != Doxygen::DoxCompoundKind::Dir && kind != Doxygen::DoxCompoundKind::File )
            {
                const std::string& compoundName = compoundDef->CompoundName( );
                const auto& members = compoundDef->Members( );
                for ( const auto& member : members )
                {
                    auto memberDef = member.MemberDef( );
                    const std::string& qualifiedName = member.MemberDef( )->QualifiedName( );
                    
                    if ( compoundName.length() > 0 &&  qualifiedName.starts_with( compoundName ) == false )
                    {
                        unexpectedCompoundNames.emplace( compoundName, qualifiedName );
                        unexpectedCompoundName++;
                    }
                }
            }
        }

        for ( const auto& entry : unexpectedCompoundNames )
        {
            PrintLn( "\"{}\"", entry.first );
            PrintLn( "\"{}\"\n", entry.second );
            
        }



        /*
        std::ranges::sort( paths );

        for ( const auto& path : paths )
        {
            PrintLn( "{}", path );
        }
        */

        size_t unnamedMemberDefs = 0;
        const auto& allMemberDefs = typeSystem->AllMemberDefs( );
        for ( const auto& entry : allMemberDefs )
        {
            auto memberDef = entry.second;
            const auto name = memberDef->Name( );
            if ( name.length( ) == 0 )
            {
                unnamedMemberDefs++;
            }
        }

        PrintLn( "unexpectedCompoundName : {}", unexpectedCompoundName );
        PrintLn( "unnamedMemberDefs : {}", unnamedMemberDefs );

        std::map<std::string, std::vector< Doxygen::Structure::MemberDef* > > memberFiles;

        for ( const auto& entry : allMemberDefs )
        {
            auto memberDef = entry.second;
            auto memberDefKind = memberDef->Kind( );
            if ( ( memberDefKind == Doxygen::DoxMemberKind::Enum || memberDefKind == Doxygen::DoxMemberKind::Function ) &&  memberDef->Language( ) == Doxygen::DoxLanguage::Cpp )
            {
                if ( memberDef->QualifiedName( ).length( ) )
                {
                    auto owner = static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
                    if ( owner->CompoundName( ) != memberDef->QualifiedName( ) )
                    {
                        auto fileName = pathBuilder.FilePathOf( memberDef );
                        auto it = memberFiles.find( fileName );
                        if ( it == memberFiles.end( ) )
                        {
                            memberFiles.emplace( fileName, std::vector< Doxygen::Structure::MemberDef* >{memberDef} );
                        }
                        else
                        {
                            it->second.emplace_back( memberDef );
                        }
                    }
                }
            }
        }

        PrintLn( "Member def count : {}", allMemberDefs.size( ) );
        PrintLn( "Member file count : {}", memberFiles.size() );

        auto templates = Templates::Load( options.Templates( ) );
        auto header = templates.Header( );



    }


}
