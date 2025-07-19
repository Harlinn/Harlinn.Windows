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

#include "D2MMarkdownStream.h"

using namespace Doxygen2Md;
using namespace Harlinn::Common::Core;


int main(int argc, char* argv[] )
{
    using namespace Harlinn::Common::Core;
    using namespace Doxygen2Md;

    Doxygen2MdOptions options;
    

    if ( options.Parse( argc, argv ) )
    {
        SubstitutionTable substitutionTable;
        if ( options.HasSubstitutionTable( ) )
        {
            substitutionTable = SubstitutionTable::Load( options.SubstitutionTable( ) );
        }


        Doxygen::DocumentCollection documentCollection;
        auto directory = options.InputDirectory();
        documentCollection.AddDirectory( to_wstring( directory ) );
        auto typeSystem = documentCollection.TypeSystem( );
        const auto& allCompoundDefs = typeSystem->AllCompoundDefs( );
        const auto& allMemberDefs = typeSystem->AllMemberDefs( );
        
        
        PathBuilder pathBuilder( options.OutputDirectory( ), substitutionTable, options.SiteUrl( ), options.RelativeOutputUrl( ) );
        MarkdownFormatter markdownFormatter( *typeSystem, pathBuilder );

        for ( const auto& entry : allCompoundDefs )
        {
            auto* compoundDef = entry.second;

            if ( compoundDef->Language( ) == Doxygen::DoxLanguage::Cpp )
            {
                auto compoundDefFilename = pathBuilder.FilePathOf( compoundDef );

                auto compoundDefKind = compoundDef->Kind( );
                switch ( compoundDefKind )
                {
                    case Doxygen::DoxCompoundKind::Class:
                    {
                        const Doxygen::Structure::ClassCompoundDef& classCompoundDef = static_cast< const Doxygen::Structure::ClassCompoundDef& >( *compoundDef );
                        auto text = markdownFormatter.Format( classCompoundDef );
                        MarkdownStream stream( compoundDefFilename );
                        stream.WriteLine( text );
                        stream.Flush( );
                    }
                    break;
                    case Doxygen::DoxCompoundKind::Struct:
                    {
                        const Doxygen::Structure::StructCompoundDef& structCompoundDef = static_cast< const Doxygen::Structure::StructCompoundDef& >( *compoundDef );
                        auto text = markdownFormatter.Format( structCompoundDef );
                        MarkdownStream stream( compoundDefFilename );
                        stream.WriteLine( text );
                        stream.Flush( );
                    }
                    break;
                    case Doxygen::DoxCompoundKind::Union:
                    {
                        const Doxygen::Structure::UnionCompoundDef& unionCompoundDef = static_cast< const Doxygen::Structure::UnionCompoundDef& >( *compoundDef );
                        auto text = markdownFormatter.Format( unionCompoundDef );
                        MarkdownStream stream( compoundDefFilename );
                        stream.WriteLine( text );
                        stream.Flush( );
                    }
                    break;
                    case Doxygen::DoxCompoundKind::Concept:
                    {
                        const Doxygen::Structure::ConceptCompoundDef& conceptCompoundDef = static_cast< const Doxygen::Structure::ConceptCompoundDef& >( *compoundDef );
                        auto text = markdownFormatter.Format( conceptCompoundDef );
                        MarkdownStream stream( compoundDefFilename );
                        stream.WriteLine( text );
                        stream.Flush( );
                    }
                    break;
                    case Doxygen::DoxCompoundKind::Namespace:
                    {
                        const Doxygen::Structure::NamespaceCompoundDef& namespaceCompoundDef = static_cast< const Doxygen::Structure::NamespaceCompoundDef& >( *compoundDef );
                        auto text = markdownFormatter.Format( namespaceCompoundDef );
                        MarkdownStream stream( compoundDefFilename );
                        stream.WriteLine( text );
                        stream.Flush( );
                    }
                    break;
                }
            }
        }



        std::unordered_map<std::string, std::vector<Doxygen::Structure::FunctionMemberDef*> > functions;

        for ( const auto& entry : allMemberDefs )
        {
            auto* memberDef = entry.second;
            if ( memberDef->Language( ) == Doxygen::DoxLanguage::Cpp )
            {
                auto memberDefKind = memberDef->Kind( );
                if ( memberDefKind == Doxygen::DoxMemberKind::Function )
                {
                    auto owner = static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
                    if ( owner && owner->Kind( ) != Doxygen::DoxCompoundKind::File )
                    {
                        auto functionMemberDef = static_cast< Doxygen::Structure::FunctionMemberDef* >( memberDef );
                        std::string functionMemberDefFilename = pathBuilder.FilePathOf( functionMemberDef );
                        auto it = functions.find( functionMemberDefFilename );
                        if ( it != functions.end( ) )
                        {
                            it->second.push_back( functionMemberDef );
                        }
                        else
                        {
                            functions.emplace( functionMemberDefFilename, std::vector<Doxygen::Structure::FunctionMemberDef*>{ functionMemberDef } );
                        }
                    }
                }
            }
        }

        for ( auto entry : functions )
        {
            const auto& functionMemberDefFilename = entry.first;
            MarkdownStream stream( functionMemberDefFilename );
            for ( auto function : entry.second )
            {
                stream.WriteLine( function->QualifiedName( ) );
            }
            stream.Flush( );
        }





    }


}
