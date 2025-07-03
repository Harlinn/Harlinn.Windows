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

#include "D2MStructure.h"

using namespace Doxygen2Md;
using namespace Harlinn::Common::Core;

class PathBuilder
{
    const std::string outputDirectory_;
public:
    PathBuilder( const std::string& outputDirectory )
        : outputDirectory_( outputDirectory )
    { }


    std::string NameOf( Doxygen::Structure::CompoundDef* compoundDef )
    {
        const std::string& compoundName = compoundDef->CompoundName( );
        auto owner = static_cast< Doxygen::Structure::CompoundDef* >( compoundDef->Owner( ) );
        if ( owner )
        {
            const std::string& ownerCompoundName = owner->CompoundName( );
            auto ownerCompoundNameLength = ownerCompoundName.length( );
            auto compoundNameLength = compoundName.length( );
            if ( compoundNameLength > ownerCompoundNameLength + 2 )
            {
                if ( compoundName[ ownerCompoundNameLength ] != ':' && compoundName[ ownerCompoundNameLength + 1 ] != ':' )
                {
                    throw std::exception( "Expected \"::\"" );
                }
                return compoundName.substr( ownerCompoundNameLength + 2 );
            }
            else
            {
                throw std::exception( "No room for \"::\" + name" );
            }
        }
        else
        {
            return compoundName;
        }
    }

    


    static std::string FileSystemBaseName( const std::string& name )
    {
        StringBuilder<char> sb;
        for ( const auto c : name )
        {
            if ( IsUpper( c ) )
            {
                sb.Append( '_' );
                sb.Append( ToLower( c ) );
            }
            else if ( IsAlnum( c ) )
            {
                sb.Append( c );
            }
            else if(IsSpace( c ) == false)
            {
                switch ( c )
                {
                    case '_':
                    {
                        sb.Append( '_' );
                        sb.Append( '_' );
                    }
                    break;
                    case ':':
                    {
                        sb.Append( '_' );
                        sb.Append( '1' );
                    }
                    break;
                    case '<':
                    {
                        sb.Append( '_' );
                        sb.Append( '2' );
                    }
                    break;
                    case '>':
                    {
                        sb.Append( '_' );
                        sb.Append( '3' );
                    }
                    break;
                }
            }
        }
        return sb.ToString<std::string>( );
    }




    std::string PathOf( Doxygen::Structure::CompoundDef* compoundDef, char separator = '\\' )
    {
        auto owner = static_cast< Doxygen::Structure::CompoundDef* >( compoundDef->Owner( ) );
        if ( owner )
        {
            auto ownerPath = PathOf( owner );
            auto compoundDefName = NameOf( compoundDef );
            auto fileSystemBaseName = FileSystemBaseName( compoundDefName );

            return std::format( "{}{}{}", ownerPath, separator, fileSystemBaseName );
        }
        else
        {
            auto compoundDefName = NameOf( compoundDef );
            auto fileSystemBaseName = FileSystemBaseName( compoundDefName );
            return fileSystemBaseName;
        }

    }

    std::string PathOf( Doxygen::Structure::MemberDef* memberDef, char separator = '\\' )
    {
        auto owner = static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
        if ( owner )
        {
            auto ownerPath = PathOf( owner );
            auto memberDefName = memberDef->Name();
            auto fileSystemBaseName = FileSystemBaseName( memberDefName );

            return std::format( "{}{}{}", ownerPath, separator, fileSystemBaseName );
        }
        else
        {
            auto memberDefName = memberDef->Name( );
            auto fileSystemBaseName = FileSystemBaseName( memberDefName );
            return fileSystemBaseName;
        }

    }

    private:
        static std::string ToString( Doxygen::DoxLanguage language )
        {
            using DoxLanguage = Doxygen::DoxLanguage;
            switch ( language )
            {
                case DoxLanguage::Unknown:
                {
                    return "cpp";
                }
                break;
                case DoxLanguage::IDL:
                {
                    return "idl";
                }
                break;
                case DoxLanguage::Java:
                {
                    return "java";
                }
                break;
                case DoxLanguage::CSharp:
                {
                    return "csharp";
                }
                break;
                case DoxLanguage::D:
                {
                    return "d";
                }
                break;
                case DoxLanguage::PHP:
                {
                    return "php";
                }
                break;
                case DoxLanguage::ObjectiveC:
                {
                    return "objectivec";
                }
                break;
                case DoxLanguage::Cpp:
                {
                    return "cpp";
                }
                break; 
                case DoxLanguage::JavaScript:
                {
                    return "javascript";
                }
                break;
                case DoxLanguage::Python:
                {
                    return "python";
                }
                break;
                case DoxLanguage::Fortran:
                {
                    return "fortran";
                }
                break; 
                case DoxLanguage::VHDL:
                {
                    return "vhdl";
                }
                break;
                case DoxLanguage::XML:
                {
                    return "xml";
                }
                break;
                case DoxLanguage::SQL:
                {
                    return "sql";
                }
                break;
                case DoxLanguage::Markdown:
                {
                    return "markdown";
                }
                break;
                case DoxLanguage::Slice:
                {
                    return "slice";
                }
                break;
                case DoxLanguage::Lex:
                {
                    return "lex";
                }
                break;
            }
            throw std::exception( "Unexpected language" );
        }
    public:

    template<typename T>
    std::string FilePathOf( T* compoundDef, char separator = '\\' )
    {
        auto path = PathOf( compoundDef, separator );
        auto result = std::format( "{}\\{}\\{}", outputDirectory_, ToString( compoundDef->Language() ), path );
        return result;
    }



};


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
        
        PathBuilder pathBuilder( options.OutputDirectory( ) );
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


    }


}
