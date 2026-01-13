#pragma once
#ifndef D2MPATHBUILDER_H_
#define D2MPATHBUILDER_H_

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


#include <HCCStringBuilder.h>
#include <HCCDoxygen.h>
#include <HCCIO.h>

#include "D2MSubstitutionTable.h"

namespace Doxygen2Md
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;

    class PathBuilder
    {
        using StringBuilder = StringBuilder<char>;
        const std::string outputDirectory_;
        const std::string siteUrl_;
        const std::string relativeOutputUrl_;
        const SubstitutionTable substitutionTable_;
    public:
        PathBuilder( const std::string& outputDirectory, const SubstitutionTable& substitutionTable, const std::string& siteUrl, const std::string& relativeOutputUrl )
            : outputDirectory_( outputDirectory ), substitutionTable_( substitutionTable ), siteUrl_( siteUrl ), relativeOutputUrl_( relativeOutputUrl )
        {
        }

    private:
        static std::string NameOf( const Doxygen::Structure::CompoundDef* compoundDef )
        {
            const std::string& compoundName = compoundDef->CompoundName( );
            auto owner = static_cast< const Doxygen::Structure::CompoundDef* >( compoundDef->Owner( ) );
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

        static std::string NameOf( const Doxygen::Structure::MemberDef* memberDef )
        {
            const std::string& qualifiedName = memberDef->QualifiedName( );
            auto owner = static_cast< const Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) );
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
                    if ( owner->Kind( ) == Doxygen::DoxCompoundKind::File )
                    {
                        return qualifiedName;
                    }
                    throw std::exception( "No room for \"::\" + name" );
                }
            }
            else
            {
                return qualifiedName;
            }
        }




        template<typename SpanT>
            requires std::is_same_v<typename SpanT::value_type, char>
        static std::string FileSystemBaseName( const SpanT& name )
        {
            StringBuilder sb;
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


        static std::string FileSystemBaseName( const Doxygen::Structure::CompoundDef* compoundDef )
        {
            auto compoundDefName = NameOf( compoundDef );
            auto result = FileSystemBaseName( compoundDefName );
            return result;
        }

        std::string MemberDefBaseName( const Doxygen::Structure::MemberDef* memberDef ) const
        {
            auto memberDefName = NameOf( memberDef );
            std::string shortName;
            if ( Substitute( memberDefName, shortName ) )
            {
                auto result = FileSystemBaseName( shortName );
                return result;
            }
            else
            {
                auto result = FileSystemBaseName( memberDefName );
                return result;
            }
        }


        static std::string PathOf( const Doxygen::Structure::CompoundDef* compoundDef, char separator = '\\' )
        {
            auto owner = static_cast< Doxygen::Structure::CompoundDef* >( compoundDef->Owner( ) );
            if ( owner )
            {
                auto ownerPath = PathOf( owner, separator );
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

        static std::string PathOf( const std::string& shortName, char separator = '\\' )
        {
            std::vector<std::string_view> parts;
            auto start = shortName.begin( );
            auto it = start;
            auto shortNameEnd = shortName.end( );
            while ( it != shortNameEnd )
            {
                auto c = *it;
                switch ( c )
                {
                    case '.':
                    case ':':
                    {
                        if ( it != start )
                        {
                            std::string_view part( start, it );
                            parts.emplace_back( part );
                        }
                        start = it + 1;
                    }
                    break;
                    case '<':
                    {
                        std::string_view part( start, shortNameEnd );
                        parts.emplace_back( part );
                        start = shortNameEnd;
                        it = shortNameEnd;
                        continue;
                    }
                    break;
                }
                it++;
            }
            if ( start != shortNameEnd )
            {
                std::string_view part( start, shortNameEnd );
                parts.emplace_back( part );
            }
            StringBuilder sb;
            bool first = true;
            for ( const auto& part : parts )
            {
                auto baseName = FileSystemBaseName( part );
                if ( !first )
                {
                    sb.Append( separator );
                }
                sb.Append( baseName );
                first = false;
            }

            return sb.ToString<std::string>( );
        }


        static std::string PathOf( const Doxygen::Structure::MemberDef* memberDef, char separator = '\\' )
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
        std::string DirectoryPathOf( const T* def, char separator = '\\' ) const
        {
            std::string path;
            std::string shortName;
            if ( Substitute( def->QualifiedName( ), shortName ) )
            {
                path = PathOf( shortName, separator );
            }
            else
            {
                path = PathOf( def, separator );
            }
            
            auto result = std::format( "{}{}{}{}{}", outputDirectory_, separator,ToString( def->Language( ) ), separator, path );
            return result;
        }
        template<typename T>
        std::string RelativeUrlOf( const T* def, char separator = '/' ) const
        {
            std::string path;
            std::string shortName;
            if ( Substitute( def->QualifiedName( ), shortName ) )
            {
                path = PathOf( shortName, separator );
            }
            else
            {
                path = PathOf( def, separator );
            }
            auto result = std::format( "{}{}{}{}{}", relativeOutputUrl_, separator, ToString( def->Language( ) ), separator, path );
            return result;
        }

        bool Substitute( const std::string& qualifiedName, std::string& shortName ) const
        {
            std::string str = qualifiedName;
            bool result = false;
            for ( const auto& entry : substitutionTable_ )
            {
                const auto& replace = entry.Replace( );
                const auto& with = entry.With( );
                auto offset = str.find( replace );
                if ( offset != std::string::npos )
                {
                    do
                    {
                        str.replace( offset, replace.length( ), with );
                        result = true;
                        offset = str.find( replace );
                    } while ( offset != std::string::npos );
                }
            }
            if ( result )
            {
                shortName = str;
            }
            return result;
        }



    public:

        std::string FilePathOf( Doxygen::Structure::CompoundDef* compoundDef, char separator = '\\' ) const
        {
            auto directory = DirectoryPathOf( compoundDef, separator );
            auto result = std::format( "{}{}index.md", directory, separator );
            return result;
        }

        std::string FilePathOf( Doxygen::Structure::MemberDef* memberDef, char separator = '\\' ) const
        {
            auto directory = DirectoryPathOf( static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner() ), separator );
            auto baseName = MemberDefBaseName( memberDef );
            auto kind = ToLower( to_string( memberDef->Kind( ) ) );
            auto result = std::format( "{}{}{}_{}.md", directory, separator, kind, baseName );
            return result;
        }

        std::string FileRelativeUrlOf( const Doxygen::Structure::CompoundDef* compoundDef, char separator = '/' ) const
        {
            auto directory = RelativeUrlOf( compoundDef, separator );
            auto result = std::format( "{}{}index.html", directory, separator );
            return result;
        }
        std::string FileRelativeUrlOf( const Doxygen::Structure::MemberDef* memberDef, char separator = '/' ) const
        {
            auto directory = RelativeUrlOf( static_cast< Doxygen::Structure::CompoundDef* >( memberDef->Owner( ) ), separator );
            auto baseName = MemberDefBaseName( memberDef );
            auto kind = ToLower( to_string( memberDef->Kind( ) ) );
            auto result = std::format( "{}{}{}_{}.html", directory, separator, kind, baseName );
            return result;
        }



    };


}


#endif
