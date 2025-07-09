#pragma once
#ifndef D2MPATHBUILDER_H_
#define D2MPATHBUILDER_H_

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


#include <HCCStringBuilder.h>
#include <HCCDoxygen.h>
#include <HCCIO.h>

namespace Doxygen2Md
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;

    class PathBuilder
    {
        const std::string outputDirectory_;
        const std::string siteUrl_;
        const std::string relativeOutputUrl_;
    public:
        PathBuilder( const std::string& outputDirectory, const std::string& siteUrl, const std::string& relativeOutputUrl )
            : outputDirectory_( outputDirectory ), siteUrl_( siteUrl ), relativeOutputUrl_( relativeOutputUrl )
        {
        }


        static std::string NameOf( Doxygen::Structure::CompoundDef* compoundDef )
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

        static std::string NameOf( Doxygen::Structure::MemberDef* memberDef )
        {
            const std::string& qualifiedName = memberDef->QualifiedName( );
            auto owner = static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
            if ( owner )
            {
                const std::string& ownerCompoundName = owner->CompoundName( );
                auto ownerCompoundNameLength = ownerCompoundName.length( );
                auto qualifiedNameLength = qualifiedName.length( );
                if ( qualifiedNameLength > ownerCompoundNameLength + 2 )
                {
                    if ( qualifiedName[ ownerCompoundNameLength ] != ':' && qualifiedName[ ownerCompoundNameLength + 1 ] != ':' )
                    {
                        throw std::exception( "Expected \"::\"" );
                    }
                    return qualifiedName.substr( ownerCompoundNameLength + 2 );
                }
                else
                {
                    throw std::exception( "No room for \"::\" + name" );
                }
            }
            else
            {
                return qualifiedName;
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
                else if ( IsSpace( c ) == false )
                {
                    switch ( c )
                    {
                        case '_':
                        {
                            sb.Append( '_' );
                            sb.Append( '1' );
                        }
                        break;
                        case ':':
                        {
                            sb.Append( '_' );
                            sb.Append( '2' );
                        }
                        break;
                        case '<':
                        {
                            sb.Append( '_' );
                            sb.Append( '3' );
                        }
                        break;
                        case '>':
                        {
                            sb.Append( '_' );
                            sb.Append( '4' );
                        }
                        break;
                        case ',':
                        {
                            sb.Append( '_' );
                            sb.Append( '5' );
                        }
                        break;
                        case '=':
                        {
                            sb.Append( '_' );
                            sb.Append( '6' );
                        }
                        break;
                        case '+':
                        {
                            sb.Append( '_' );
                            sb.Append( '7' );
                        }
                        break;
                        case '-':
                        {
                            sb.Append( '_' );
                            sb.Append( '8' );
                        }
                        break;
                        case '*':
                        {
                            sb.Append( '_' );
                            sb.Append( '9' );
                        }
                        break;
                        case '/':
                        {
                            sb.Append( '_' );
                            sb.Append( 'A' );
                        }
                        break;
                        case '&':
                        {
                            sb.Append( '_' );
                            sb.Append( 'B' );
                        }
                        break;
                        case '|':
                        {
                            sb.Append( '_' );
                            sb.Append( 'C' );
                        }
                        break;
                        case '%':
                        {
                            sb.Append( '_' );
                            sb.Append( 'D' );
                        }
                        break;
                        case '^':
                        {
                            sb.Append( '_' );
                            sb.Append( 'E' );
                        }
                        break;
                        case '!':
                        {
                            sb.Append( '_' );
                            sb.Append( 'F' );
                        }
                        break;
                        case '~':
                        {
                            sb.Append( '_' );
                            sb.Append( 'G' );
                        }
                        break;
                    }
                }
            }
            return sb.ToString<std::string>( );
        }


        static std::string FileSystemBaseName( Doxygen::Structure::CompoundDef* compoundDef )
        {
            auto compoundDefName = NameOf( compoundDef );
            auto result = FileSystemBaseName( compoundDefName );
            return result;
        }

        static std::string FileSystemBaseName( Doxygen::Structure::MemberDef* memberDef )
        {
            auto memberDefName = NameOf( memberDef );
            auto result = FileSystemBaseName( memberDefName );
            return result;
        }


        static std::string PathOf( Doxygen::Structure::CompoundDef* compoundDef, char separator = '\\' )
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

        static std::string PathOf( Doxygen::Structure::MemberDef* memberDef, char separator = '\\' )
        {
            auto owner = static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
            if ( owner )
            {
                auto ownerPath = PathOf( owner );
                auto memberDefName = memberDef->Name( );
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
    

        template<typename T>
        std::string DirectoryPathOf( T* def, char separator = '\\' ) const
        {
            auto path = PathOf( def, separator );
            auto result = std::format( "{}{}{}{}{}", outputDirectory_, separator,ToString( def->Language( ) ), separator, path );
            return result;
        }
        template<typename T>
        std::string RelativeUrlOf( T* def, char separator = '/' ) const
        {
            auto path = PathOf( def, separator );
            auto result = std::format( "{}{}{}{}{}", relativeOutputUrl_, separator, ToString( def->Language( ) ), separator, path );
            return result;
        }
    public:

        std::string FilePathOf( Doxygen::Structure::CompoundDef* compoundDef, bool ensureDirectoryExist = true, char separator = '\\' ) const
        {
            auto directory = DirectoryPathOf( compoundDef, separator );
            if ( ensureDirectoryExist )
            {
                if ( IO::Directory::Exist( directory ) == false )
                {
                    IO::Directory::Create( directory );
                }
            }
            auto baseName = FileSystemBaseName( compoundDef );
            auto kind = ToLower( to_string( compoundDef->Kind( ) ) );
            auto result = std::format( "{}\\{}_{}.md", directory, kind, baseName );
            return result;
        }

        std::string FilePathOf( Doxygen::Structure::MemberDef* memberDef, bool ensureDirectoryExist = true, char separator = '\\' ) const
        {
            auto directory = DirectoryPathOf( static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner() ), separator );
            if ( ensureDirectoryExist )
            {
                if ( IO::Directory::Exist( directory ) == false )
                {
                    IO::Directory::Create( directory );
                }
            }
            auto baseName = FileSystemBaseName( memberDef );
            auto kind = ToLower( to_string( memberDef->Kind( ) ) );
            auto result = std::format( "{}\\{}_{}.md", directory, kind, baseName );
            return result;
        }

        std::string FileRelativeUrlOf( Doxygen::Structure::CompoundDef* compoundDef, char separator = '/' ) const
        {
            auto directory = RelativeUrlOf( compoundDef, separator );
            auto baseName = FileSystemBaseName( compoundDef );
            auto kind = ToLower( to_string( compoundDef->Kind( ) ) );
            auto result = std::format( "{}\\{}_{}.md", directory, kind, baseName );
            return result;
        }
        std::string FileRelativeUrlOf( Doxygen::Structure::MemberDef* memberDef, char separator = '/' ) const
        {
            auto directory = RelativeUrlOf( static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) ), separator );
            auto baseName = FileSystemBaseName( memberDef );
            auto kind = ToLower( to_string( memberDef->Kind( ) ) );
            auto result = std::format( "{}\\{}_{}.md", directory, kind, baseName );
            return result;
        }



    };


}


#endif
