#pragma once
#ifndef D2MSTRUCTURE_H_
#define D2MSTRUCTURE_H_

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

#include <HCCDoxygen.h>
#include <HCCStringBuilder.h>
#include <HCCString.h>
#include "doxygen2mdOptions.h"
#include "D2MTemplates.h"

namespace Doxygen2Md
{
    class MarkdownFormatter
    {
    public:
        using TypeSystem = Doxygen::Structure::TypeSystem;
        using StringBuilder = StringBuilder<char>;

        using BaseDef = Doxygen::Structure::BaseDef;
        using CompoundDef = Doxygen::Structure::CompoundDef;
        using MemberDef = Doxygen::Structure::MemberDef;


        using DoxType = Doxygen::DoxType;
        using DoxCmdGroupType = Doxygen::DoxCmdGroupType;

        using DocBaseType = Doxygen::DocBaseType;

        using TextType = Doxygen::TextType;
        using TitleType = Doxygen::TitleType;
        using DocEmojiType = Doxygen::DocEmojiType;
        using TableOfContentsKindType = Doxygen::TableOfContentsKindType;
        using TableOfContentsType = Doxygen::TableOfContentsType;
        using DocEmptyType = Doxygen::DocEmptyType;
        using DocParBlockType = Doxygen::DocParBlockType;
        using DocBlockQuoteType = Doxygen::DocBlockQuoteType;
        using DocDetailsType = Doxygen::DocDetailsType;
        using DocCopyType = Doxygen::DocCopyType;
        using DocXRefSectType = Doxygen::DocXRefSectType;
        using DocParamName = Doxygen::DocParamName;
        using DocParamType = Doxygen::DocParamType;
        using DocParamNameList = Doxygen::DocParamNameList;
        using DocParamListItem = Doxygen::DocParamListItem;
        using DocParamListType = Doxygen::DocParamListType;
        using DocLanguageType = Doxygen::DocLanguageType;
        using DocTocListType = Doxygen::DocTocListType;
        using DocTocItemType = Doxygen::DocTocItemType;
        using DocPlantumlType = Doxygen::DocPlantumlType;
        using DocImageFileType = Doxygen::DocImageFileType;
        using DocDotMscType = Doxygen::DocDotMscType;
        using DocImageType = Doxygen::DocImageType;
        using DocHeadingType = Doxygen::DocHeadingType;
        using DocCaptionType = Doxygen::DocCaptionType;
        using DocEntryType = Doxygen::DocEntryType;
        using DocRowType = Doxygen::DocRowType;
        using DocTableType = Doxygen::DocTableType;
        using DocRefTextType = Doxygen::DocRefTextType;
        using DocVariableListType = Doxygen::DocVariableListType;
        using DocVarListEntryType = Doxygen::DocVarListEntryType;
        using DocSimpleSectType = Doxygen::DocSimpleSectType;
        using DocListItemType = Doxygen::DocListItemType;
        using DocListType = Doxygen::DocListType;
        using DocIndexEntryType = Doxygen::DocIndexEntryType;
        using DocFormulaType = Doxygen::DocFormulaType;
        using DocAnchorType = Doxygen::DocAnchorType;
        using DocURLLink = Doxygen::DocURLLink;
        using DocMarkupType = Doxygen::DocMarkupType;
        using DocParaType = Doxygen::DocParaType;
        using DocCmdGroup = Doxygen::DocCmdGroup;
        using DocSummaryType = Doxygen::DocSummaryType;
        using DocTitleType = Doxygen::DocTitleType;
        using DocTitleCmdGroup = Doxygen::DocTitleCmdGroup;
        using DocInternalS6Type = Doxygen::DocInternalS6Type;
        using DocInternalS5Type = Doxygen::DocInternalS5Type;
        using DocInternalS4Type = Doxygen::DocInternalS4Type;
        using DocInternalS3Type = Doxygen::DocInternalS3Type;
        using DocInternalS2Type = Doxygen::DocInternalS2Type;
        using DocInternalS1Type = Doxygen::DocInternalS1Type;
        using DocInternalType = Doxygen::DocInternalType;
        using DocSect6Type = Doxygen::DocSect6Type;
        using DocSect5Type = Doxygen::DocSect5Type;
        using DocSect4Type = Doxygen::DocSect4Type;
        using DocSect3Type = Doxygen::DocSect3Type;
        using DocSect2Type = Doxygen::DocSect2Type;
        using DocSect1Type = Doxygen::DocSect1Type;
        using LocationType = Doxygen::LocationType;
        using ReferenceType = Doxygen::ReferenceType;
        using SpType = Doxygen::SpType;
        using HighlightType = Doxygen::HighlightType;
        using CodeLineType = Doxygen::CodeLineType;
        using ListingType = Doxygen::ListingType;
        using LinkType = Doxygen::LinkType;
        using ChildNodeType = Doxygen::ChildNodeType;
        using NodeType = Doxygen::NodeType;
        using GraphType = Doxygen::GraphType;
        using LinkedTextType = Doxygen::LinkedTextType;
        using ParamType = Doxygen::ParamType;
        using TemplateParamListType = Doxygen::TemplateParamListType;
        using EnumvalueType = Doxygen::EnumvalueType;
        using DescriptionType = Doxygen::DescriptionType;
        using MemberDefType = Doxygen::MemberDefType;
        using SectionDefType = Doxygen::SectionDefType;
        using MemberType = Doxygen::MemberType;
        using RefTextType = Doxygen::RefTextType;
        using RefType = Doxygen::RefType;
        using ExportType = Doxygen::ExportType;
        using ExportsType = Doxygen::ExportsType;
        using IncType = Doxygen::IncType;
        using ReimplementType = Doxygen::ReimplementType;
        using CompoundRefType = Doxygen::CompoundRefType;
        using DocHtmlOnlyType = Doxygen::DocHtmlOnlyType;
        using MemberRefType = Doxygen::MemberRefType;
        using ListOfAllMembersType = Doxygen::ListOfAllMembersType;
        using CompoundDefType = Doxygen::CompoundDefType;
        
        using DocCmdGroupType = Doxygen::DocCmdGroupType;
    private:
        const TypeSystem& typeSystem_;
        const PathBuilder& pathBuilder_;
    public:
        MarkdownFormatter( const TypeSystem& typeSystem, const PathBuilder& pathBuilder )
            : typeSystem_( typeSystem ), pathBuilder_( pathBuilder )
        { }

        // Not in switch
        void FormatDocCmdGroupTypeTo( const BaseDef& context, size_t indentation, const DocCmdGroupType& source, StringBuilder& dest ) const
        {
            using DoxCmdGroupType = Doxygen::DoxCmdGroupType;
            auto sourceType = source.Type;
            switch ( sourceType )
            {
                case DoxCmdGroupType::ulink: //DocURLLink
                {
                    FormatDocURLLinkTo( context, indentation, static_cast< const DocURLLink& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::bold: //DocMarkupType 
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::s: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::strike: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::underline: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::emphasis: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::computeroutput: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::subscript: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::superscript: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::center: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::Small: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::cite: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::del: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::ins: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::htmlonly: //DocHtmlOnlyType
                {
                    FormatDocHtmlOnlyTypeTo( context, indentation, static_cast< const DocHtmlOnlyType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::manonly: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::xmlonly: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::rtfonly: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::latexonly: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::docbookonly: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::image: //DocImageType
                {
                    FormatDocImageTypeTo( context, indentation, static_cast< const DocImageType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::dot: //DocDotMscType
                {
                    FormatDocDotMscTypeTo( context, indentation, static_cast< const DocDotMscType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::msc: //DocDotMscType
                {
                    FormatDocDotMscTypeTo( context, indentation, static_cast< const DocDotMscType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::plantuml: //DocPlantumlType
                {
                    FormatDocPlantumlTypeTo( context, indentation, static_cast< const DocPlantumlType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::anchor: //DocAnchorType
                {
                    FormatDocAnchorTypeTo( context, indentation, static_cast< const DocAnchorType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::formula: //DocFormulaType
                {
                    FormatDocFormulaTypeTo( context, indentation, static_cast< const DocFormulaType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::ref: //DocRefTextType
                {
                    FormatDocRefTextTypeTo( context, indentation, static_cast< const DocRefTextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::emoji: //DocEmojiType
                {
                    FormatDocEmojiTypeTo( context, indentation, static_cast< const DocEmojiType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::preformatted: //DocMarkupType
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( *source.Value ), dest, sourceType );
                }
                break;
                case DoxCmdGroupType::programlisting: //ListingType
                {
                    FormatListingTypeTo( context, indentation, static_cast< const ListingType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::verbatim: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::javadocliteral: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::javadoccode: //TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::indexentry: //DocIndexEntryType
                {
                    FormatDocIndexEntryTypeTo( context, indentation, static_cast< const DocIndexEntryType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::orderedlist: //DocListType
                {
                    FormatDocListTypeTo( context, indentation, static_cast< const DocListType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::itemizedlist: //DocListType
                {
                    FormatDocListTypeTo( context, indentation, static_cast< const DocListType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::simplesect: //DocSimpleSectType
                {
                    FormatDocSimpleSectTypeTo( context, indentation, static_cast< const DocSimpleSectType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::title: //DocTitleType
                {
                    FormatDocTitleTypeTo( context, indentation, static_cast< const DocTitleType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::variablelist: //DocVariableListType
                {
                    FormatDocVariableListTypeTo( context, indentation, static_cast< const DocVariableListType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::table: //DocTableType
                {
                    FormatDocTableTypeTo( context, indentation, static_cast< const DocTableType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::heading: //DocHeadingType
                {
                    FormatDocHeadingTypeTo( context, indentation, static_cast< const DocHeadingType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::dotfile: //DocImageFileType
                {
                    FormatDocImageFileTypeTo( context, indentation, static_cast< const DocImageFileType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::mscfile: //DocImageFileType
                {
                    FormatDocImageFileTypeTo( context, indentation, static_cast< const DocImageFileType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::diafile: //DocImageFileType
                {
                    FormatDocImageFileTypeTo( context, indentation, static_cast< const DocImageFileType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::toclist: //DocTocListType
                {
                    FormatDocTocListTypeTo( context, indentation, static_cast< const DocTocListType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::language: //DocLanguageType
                {
                    FormatDocLanguageTypeTo( context, indentation, static_cast< const DocLanguageType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::parameterlist: //DocParamListType
                {
                    FormatDocParamListTypeTo( context, indentation, static_cast< const DocParamListType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::xrefsect: //DocXRefSectType
                {
                    FormatDocXRefSectTypeTo( context, indentation, static_cast< const DocXRefSectType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::copydoc: //DocCopyType
                {
                    FormatDocCopyTypeTo( context, indentation, static_cast< const DocCopyType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::details: //DocDetailsType
                {
                    FormatDocDetailsTypeTo( context, indentation, static_cast< const DocDetailsType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::blockquote: //DocBlockQuoteType
                {
                    FormatDocBlockQuoteTypeTo( context, indentation, static_cast< const DocBlockQuoteType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::parblock:  //DocParBlockType
                {
                    FormatDocParBlockTypeTo( context, indentation, static_cast< const DocParBlockType& >( *source.Value ), dest );
                }
                break;
                case DoxCmdGroupType::text:  // TextType
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *source.Value ), dest );
                }
                break;
                default:
                {
                    FormatDoxCmdGroupTypeTo( context, indentation, sourceType, dest );
                }
                break;


            }
        }

        static void FormatDoxCmdGroupTypeTo( const BaseDef& context, size_t indentation, DoxCmdGroupType cmdGroupType, StringBuilder& dest )
        {
            switch ( cmdGroupType )
            {
                case DoxCmdGroupType::linebreak:
                {
                    dest.AppendLine( );
                    Indent( std::string( ), indentation );
                }
                break;
            }
        }

        static std::string Indent( const std::string& source, size_t indentation )
        {
            if ( indentation )
            {
                StringBuilder dest;
                bool newLine = true;
                for ( auto c : source )
                {
                    if ( newLine )
                    {
                        dest.Append( '\x20', indentation );
                        newLine = false;
                    }
                    dest.Append( c );
                    if ( c == '\n' )
                    {
                        newLine = true;
                    }
                }
                return dest.ToString<std::string>( );
            }
            else
            {
                return source;
            }
        }

        static std::string Indent( const std::string& source, size_t indentation, const std::string& prefix  )
        {
            StringBuilder dest;
            bool newLine = true;
            for ( auto c : source )
            {
                if ( newLine )
                {
                    if ( indentation )
                    {
                        dest.Append( '\x20', indentation );
                    }
                    dest.Append( prefix );
                    newLine = false;
                }
                dest.Append( c );
                if ( c == '\n' )
                {
                    newLine = true;
                }
            }
            return dest.ToString<std::string>( );
        }



        void FormatTextTypeTo(const BaseDef& context, size_t indentation, const TextType& source, StringBuilder& dest ) const
        {
            dest.Append( Indent( source.Text( ), indentation ) );
        }

        void FormatTitleTypeTo( const BaseDef& context, size_t indentation, const TitleType& source, StringBuilder& dest ) const
        {
            dest.Append( Indent( source.Text( ), indentation ) );
        }

        void FormatDocEmojiTypeTo( const BaseDef& context, size_t indentation, const DocEmojiType& source, StringBuilder& dest ) const
        {

        }

        void FormatTableOfContentsKindTypeTo( const BaseDef& context, size_t indentation, const TableOfContentsKindType& source, StringBuilder& dest ) const
        {

        }

        void FormatTableOfContentsTypeTo( const BaseDef& context, size_t indentation, const TableOfContentsType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocEmptyTypeTo( const BaseDef& context, size_t indentation, const DocEmptyType& source, StringBuilder& dest ) const
        {

        }

        

        void FormatDocParBlockTypeTo( const BaseDef& context, size_t indentation, const DocParBlockType& source, StringBuilder& dest ) const
        {
            for ( const auto& ptr : source )
            {
                FormatDocParaTypeTo( context, indentation, *ptr, dest );
            }
        }

        void FormatDocBlockQuoteTypeTo( const BaseDef& context, size_t indentation, const DocBlockQuoteType& source, StringBuilder& dest ) const
        {
            StringBuilder tmp;
            for ( const auto& ptr : source )
            {
                FormatDocParaTypeTo( context, 0, *ptr, tmp );
            }
            auto text = tmp.ToString<std::string>( );
            auto quoteText = Indent( text, indentation, "> " );
            dest.Append( quoteText );
        }

        void FormatDocDetailsTypeTo( const BaseDef& context, size_t indentation, const DocDetailsType& source, StringBuilder& dest ) const
        {
            const auto& summary = source.Summary( );
            if ( summary )
            {
                FormatDocSummaryTypeTo( context, indentation, *summary, dest );
            }
            for ( const auto& ptr : source )
            {
                FormatDocParaTypeTo( context, indentation, *ptr, dest );
            }
        }

        void FormatDocCopyTypeTo( const BaseDef& context, size_t indentation, const DocCopyType& source, StringBuilder& dest ) const
        {
            
        }

        void FormatDocXRefSectTypeTo( const BaseDef& context, size_t indentation, const DocXRefSectType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocParamNameTo( const BaseDef& context, size_t indentation, const DocParamName& source, StringBuilder& dest ) const
        {
            using DoxType = Doxygen::DoxType;
            for ( const auto& ptr : source )
            {
                auto doxType = ptr->DoxType( );
                switch ( doxType )
                {
                    case DoxType::TextType:
                    {
                        FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *ptr ), dest );
                    }
                    break;
                    case DoxType::RefTextType:
                    {
                        FormatRefTextTypeTo( context, indentation, static_cast< const RefTextType& >( *ptr ), dest );
                    }
                    break;
                    default:
                    {
                        auto message = std::format( "Unexpected {}", to_string( doxType ) );
                        throw std::exception( message.c_str( ) );
                    }
                    break;
                }
            }
        }

        void FormatDocParamTypeTo( const BaseDef& context, size_t indentation, const DocParamType& source, StringBuilder& dest ) const
        {
            using DoxType = Doxygen::DoxType;
            for ( const auto& ptr : source )
            {
                auto doxType = ptr->DoxType( );
                switch ( doxType )
                {
                    case DoxType::TextType:
                    {
                        FormatTextTypeTo( context, indentation, static_cast< const TextType& >( *ptr ), dest );
                    }
                    break;
                    case DoxType::RefTextType:
                    {
                        FormatRefTextTypeTo( context, indentation, static_cast< const RefTextType& >( *ptr ), dest );
                    }
                    break;
                    default:
                    {
                        auto message = std::format( "Unexpected {}", to_string( doxType ) );
                        throw std::exception( message.c_str( ) );
                    }
                    break;
                }
            }
        }

        void FormatDocParamNameListTo( const BaseDef& context, size_t indentation, const DocParamNameList& source, StringBuilder& dest ) const
        {
            using DoxType = Doxygen::DoxType;
            for ( const auto& ptr : source )
            {
                auto doxType = ptr->DoxType( );
                switch ( doxType )
                {
                    case DoxType::DocParamType:
                    {
                        FormatDocParamTypeTo( context, indentation, static_cast< const DocParamType& >( *ptr ), dest );
                    }
                    break;
                    case DoxType::DocParamName:
                    {
                        FormatDocParamNameTo( context, indentation, static_cast< const DocParamName& >( *ptr ), dest );
                    }
                    break;
                    default:
                    {
                        auto message = std::format( "Unexpected {}", to_string( doxType ) );
                        throw std::exception( message.c_str( ) );
                    }
                    break;
                }
            }
        }

        void FormatDocParamListItemTo( const BaseDef& context, size_t indentation, const DocParamListItem& source, StringBuilder& dest ) const
        {
            using DoxType = Doxygen::DoxType;
            if ( source.size( ) != 1 )
            {
                auto message = std::format( "Unexpected size: {}", source.size( ) );
                throw std::exception( message.c_str( ) );
            }

            const auto& ptr = source.front( );
            FormatDocParamNameListTo( context, indentation, static_cast< const DocParamNameList& >( *ptr ), dest );
            dest.AppendLine( );
            dest.AppendLine( );
            const auto& parameterDescription = source.ParameterDescription( );
            if ( parameterDescription )
            {
                FormatDescriptionTypeTo( context, indentation, *parameterDescription, dest );
            }
        }

        void FormatDocParamListTypeTo( const BaseDef& context, size_t indentation, const DocParamListType& source, StringBuilder& dest ) const
        {
            using DoxType = Doxygen::DoxType;
            for ( const auto& ptr : source )
            {
                auto doxType = ptr->DoxType( );
                switch ( doxType )
                {
                    case DoxType::DocParamListItem:
                    {
                        FormatDocParamListItemTo( context, indentation, static_cast< const DocParamListItem& >( *ptr ), dest );
                        dest.AppendLine( );
                        dest.AppendLine( );
                    }
                    break;
                    default:
                    {
                        auto message = std::format( "Unexpected {}", to_string( doxType ) );
                        throw std::exception( message.c_str( ) );
                    }
                    break;
                }
            }
        }

        void FormatDocLanguageTypeTo( const BaseDef& context, size_t indentation, const DocLanguageType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocTocListTypeTo( const BaseDef& context, size_t indentation, const DocTocListType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocTocItemTypeTo( const BaseDef& context, size_t indentation, const DocTocItemType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocPlantumlTypeTo( const BaseDef& context, size_t indentation, const DocPlantumlType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocImageFileTypeTo( const BaseDef& context, size_t indentation, const DocImageFileType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocDotMscTypeTo( const BaseDef& context, size_t indentation, const DocDotMscType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocImageTypeTo( const BaseDef& context, size_t indentation, const DocImageType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocHeadingTypeTo( const BaseDef& context, size_t indentation, const DocHeadingType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocCaptionTypeTo( const BaseDef& context, size_t indentation, const DocCaptionType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocEntryTypeTo( const BaseDef& context, size_t indentation, const DocEntryType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocRowTypeTo( const BaseDef& context, size_t indentation, const DocRowType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocTableTypeTo( const BaseDef& context, size_t indentation, const DocTableType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocRefTextTypeTo( const BaseDef& context, size_t indentation, const DocRefTextType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocVariableListTypeTo( const BaseDef& context, size_t indentation, const DocVariableListType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocVarListEntryTypeTo( const BaseDef& context, size_t indentation, const DocVarListEntryType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSimpleSectTypeTo( const BaseDef& context, size_t indentation, const DocSimpleSectType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocListItemTypeTo( const BaseDef& context, size_t indentation, const DocListItemType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocListTypeTo( const BaseDef& context, size_t indentation, const DocListType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocIndexEntryTypeTo( const BaseDef& context, size_t indentation, const DocIndexEntryType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocFormulaTypeTo( const BaseDef& context, size_t indentation, const DocFormulaType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocAnchorTypeTo( const BaseDef& context, size_t indentation, const DocAnchorType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocURLLinkTo( const BaseDef& context, size_t indentation, const DocURLLink& source, StringBuilder& dest ) const
        {

        }

        void FormatDocMarkupTypeTo( const BaseDef& context, size_t indentation, const DocMarkupType& source, StringBuilder& dest, DoxCmdGroupType cmdGroupType = DoxCmdGroupType::Unknown ) const
        {
            
        }

        void FormatDocParaTypeTo( const BaseDef& context, size_t indentation, const DocParaType& source, StringBuilder& dest ) const
        {
            for ( const DocCmdGroupType& cmdGroup : source )
            {
                FormatDocCmdGroupTypeTo( context, indentation, cmdGroup, dest );
            }
        }

        void FormatDocCmdGroupTo( const BaseDef& context, size_t indentation, const DocCmdGroup& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSummaryTypeTo( const BaseDef& context, size_t indentation, const DocSummaryType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocTitleTypeTo( const BaseDef& context, size_t indentation, const DocTitleType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocTitleCmdGroupTo( const BaseDef& context, size_t indentation, const DocTitleCmdGroup& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS6TypeTo( const BaseDef& context, size_t indentation, const DocInternalS6Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS5TypeTo( const BaseDef& context, size_t indentation, const DocInternalS5Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS4TypeTo( const BaseDef& context, size_t indentation, const DocInternalS4Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS3TypeTo( const BaseDef& context, size_t indentation, const DocInternalS3Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS2TypeTo( const BaseDef& context, size_t indentation, const DocInternalS2Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalS1TypeTo( const BaseDef& context, size_t indentation, const DocInternalS1Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocInternalTypeTo( const BaseDef& context, size_t indentation, const DocInternalType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect6TypeTo( const BaseDef& context, size_t indentation, const DocSect6Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect5TypeTo( const BaseDef& context, size_t indentation, const DocSect5Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect4TypeTo( const BaseDef& context, size_t indentation, const DocSect4Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect3TypeTo( const BaseDef& context, size_t indentation, const DocSect3Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect2TypeTo( const BaseDef& context, size_t indentation, const DocSect2Type& source, StringBuilder& dest ) const
        {

        }

        void FormatDocSect1TypeTo( const BaseDef& context, size_t indentation, const DocSect1Type& source, StringBuilder& dest ) const
        {

        }

        void FormatLocationTypeTo( const BaseDef& context, size_t indentation, const LocationType& source, StringBuilder& dest ) const
        {

        }

        void FormatReferenceTypeTo( const BaseDef& context, size_t indentation, const ReferenceType& source, StringBuilder& dest ) const
        {

        }

        void FormatSpTypeTo( const BaseDef& context, size_t indentation, const SpType& source, StringBuilder& dest ) const
        {

        }

        void FormatHighlightTypeTo( const BaseDef& context, size_t indentation, const HighlightType& source, StringBuilder& dest ) const
        {

        }

        void FormatCodeLineTypeTo( const BaseDef& context, size_t indentation, const CodeLineType& source, StringBuilder& dest ) const
        {

        }

        void FormatListingTypeTo( const BaseDef& context, size_t indentation, const ListingType& source, StringBuilder& dest ) const
        {

        }

        void FormatLinkTypeTo( const BaseDef& context, size_t indentation, const LinkType& source, StringBuilder& dest ) const
        {

        }

        void FormatChildNodeTypeTo( const BaseDef& context, size_t indentation, const ChildNodeType& source, StringBuilder& dest ) const
        {

        }

        void FormatNodeTypeTo( const BaseDef& context, size_t indentation, const NodeType& source, StringBuilder& dest ) const
        {

        }

        void FormatGraphTypeTo( const BaseDef& context, size_t indentation, const GraphType& source, StringBuilder& dest ) const
        {

        }

        void FormatLinkedTextTypeTo( const BaseDef& context, size_t indentation, const LinkedTextType& source, StringBuilder& dest ) const
        {

        }

        void FormatParamTypeTo( const BaseDef& context, size_t indentation, const ParamType& source, StringBuilder& dest ) const
        {

        }

        void FormatTemplateParamListTypeTo( const BaseDef& context, size_t indentation, const TemplateParamListType& source, StringBuilder& dest ) const
        {

        }

        void FormatEnumvalueTypeTo( const BaseDef& context, size_t indentation, const EnumvalueType& source, StringBuilder& dest ) const
        {

        }

        void FormatDescriptionTypeTo( const BaseDef& context, size_t indentation, const DescriptionType& source, StringBuilder& dest ) const
        {

        }

        void FormatMemberDefTypeTo( const BaseDef& context, size_t indentation, const MemberDefType& source, StringBuilder& dest ) const
        {

        }

        void FormatSectionDefTypeTo( const BaseDef& context, size_t indentation, const SectionDefType& source, StringBuilder& dest ) const
        {

        }

        void FormatMemberTypeTo( const BaseDef& context, size_t indentation, const MemberType& source, StringBuilder& dest ) const
        {

        }

        void FormatRefTextTypeTo( const BaseDef& context, size_t indentation, const RefTextType& source, StringBuilder& dest ) const
        {

        }

        void FormatRefTypeTo( const BaseDef& context, size_t indentation, const RefType& source, StringBuilder& dest ) const
        {

        }

        void FormatExportTypeTo( const BaseDef& context, size_t indentation, const ExportType& source, StringBuilder& dest ) const
        {

        }

        void FormatExportsTypeTo( const BaseDef& context, size_t indentation, const ExportsType& source, StringBuilder& dest ) const
        {

        }

        void FormatIncTypeTo( const BaseDef& context, size_t indentation, const IncType& source, StringBuilder& dest ) const
        {

        }

        void FormatReimplementTypeTo( const BaseDef& context, size_t indentation, const ReimplementType& source, StringBuilder& dest ) const
        {

        }

        void FormatCompoundRefTypeTo( const BaseDef& context, size_t indentation, const CompoundRefType& source, StringBuilder& dest ) const
        {

        }

        void FormatDocHtmlOnlyTypeTo( const BaseDef& context, size_t indentation, const DocHtmlOnlyType& source, StringBuilder& dest ) const
        {

        }

        void FormatMemberRefTypeTo( const BaseDef& context, size_t indentation, const MemberRefType& source, StringBuilder& dest ) const
        {

        }

        void FormatListOfAllMembersTypeTo( const BaseDef& context, size_t indentation, const ListOfAllMembersType& source, StringBuilder& dest ) const
        {

        }

        void FormatCompoundDefTypeTo( const BaseDef& context, size_t indentation, const CompoundDefType& source, StringBuilder& dest ) const
        {

        }



        void FormatTo( const BaseDef& context, size_t indentation, const DocBaseType& source, StringBuilder& dest ) const
        {
            auto type = source.DoxType( );
            switch ( type )
            {
                case DoxType::TextType:
                {
                    FormatTextTypeTo( context, indentation, static_cast< const TextType& >( source ), dest );
                }
                break;
                case DoxType::TitleType:
                {
                    FormatTitleTypeTo( context, indentation, static_cast< const TitleType& >( source ), dest );
                }
                break;
                case DoxType::DocEmojiType:
                {
                    FormatDocEmojiTypeTo( context, indentation, static_cast< const DocEmojiType& >( source ), dest );
                }
                break;
                case DoxType::TableOfContentsKindType:
                {
                    FormatTableOfContentsKindTypeTo( context, indentation, static_cast< const TableOfContentsKindType& >( source ), dest );
                }
                break;
                case DoxType::TableOfContentsType:
                {
                    FormatTableOfContentsTypeTo( context, indentation, static_cast< const TableOfContentsType& >( source ), dest );
                }
                break;
                case DoxType::DocEmptyType:
                {
                    FormatDocEmptyTypeTo( context, indentation, static_cast< const DocEmptyType& >( source ), dest );
                }
                break;
                case DoxType::DocParBlockType:
                {
                    FormatDocParBlockTypeTo( context, indentation, static_cast< const DocParBlockType& >( source ), dest );
                }
                break;
                case DoxType::DocBlockQuoteType:
                {
                    FormatDocBlockQuoteTypeTo( context, indentation, static_cast< const DocBlockQuoteType& >( source ), dest );
                }
                break;
                case DoxType::DocDetailsType:
                {
                    FormatDocDetailsTypeTo( context, indentation, static_cast< const DocDetailsType& >( source ), dest );
                }
                break;
                case DoxType::DocCopyType:
                {
                    FormatDocCopyTypeTo( context, indentation, static_cast< const DocCopyType& >( source ), dest );
                }
                break;
                case DoxType::DocXRefSectType:
                {
                    FormatDocXRefSectTypeTo( context, indentation, static_cast< const DocXRefSectType& >( source ), dest );
                }
                break;
                case DoxType::DocParamName:
                {
                    FormatDocParamNameTo( context, indentation, static_cast< const DocParamName& >( source ), dest );
                }
                break;
                case DoxType::DocParamType:
                {
                    FormatDocParamTypeTo( context, indentation, static_cast< const DocParamType& >( source ), dest );
                }
                break;
                case DoxType::DocParamNameList:
                {
                    FormatDocParamNameListTo( context, indentation, static_cast< const DocParamNameList& >( source ), dest );
                }
                break;
                case DoxType::DocParamListItem:
                {
                    FormatDocParamListItemTo( context, indentation, static_cast< const DocParamListItem& >( source ), dest );
                }
                break;
                case DoxType::DocParamListType:
                {
                    FormatDocParamListTypeTo( context, indentation, static_cast< const DocParamListType& >( source ), dest );
                }
                break;
                case DoxType::DocLanguageType:
                {
                    FormatDocLanguageTypeTo( context, indentation, static_cast< const DocLanguageType& >( source ), dest );
                }
                break;
                case DoxType::DocTocListType:
                {
                    FormatDocTocListTypeTo( context, indentation, static_cast< const DocTocListType& >( source ), dest );
                }
                break;
                case DoxType::DocTocItemType:
                {
                    FormatDocTocItemTypeTo( context, indentation, static_cast< const DocTocItemType& >( source ), dest );
                }
                break;
                case DoxType::DocPlantumlType:
                {
                    FormatDocPlantumlTypeTo( context, indentation, static_cast< const DocPlantumlType& >( source ), dest );
                }
                break;
                case DoxType::DocImageFileType:
                {
                    FormatDocImageFileTypeTo( context, indentation, static_cast< const DocImageFileType& >( source ), dest );
                }
                break;
                case DoxType::DocDotMscType:
                {
                    FormatDocDotMscTypeTo( context, indentation, static_cast< const DocDotMscType& >( source ), dest );
                }
                break;
                case DoxType::DocImageType:
                {
                    FormatDocImageTypeTo( context, indentation, static_cast< const DocImageType& >( source ), dest );
                }
                break;
                case DoxType::DocHeadingType:
                {
                    FormatDocHeadingTypeTo( context, indentation, static_cast< const DocHeadingType& >( source ), dest );
                }
                break;
                case DoxType::DocCaptionType:
                {
                    FormatDocCaptionTypeTo( context, indentation, static_cast< const DocCaptionType& >( source ), dest );
                }
                break;
                case DoxType::DocEntryType:
                {
                    FormatDocEntryTypeTo( context, indentation, static_cast< const DocEntryType& >( source ), dest );
                }
                break;
                case DoxType::DocRowType:
                {
                    FormatDocRowTypeTo( context, indentation, static_cast< const DocRowType& >( source ), dest );
                }
                break;
                case DoxType::DocTableType:
                {
                    FormatDocTableTypeTo( context, indentation, static_cast< const DocTableType& >( source ), dest );
                }
                break;
                case DoxType::DocRefTextType:
                {
                    FormatDocRefTextTypeTo( context, indentation, static_cast< const DocRefTextType& >( source ), dest );
                }
                break;
                case DoxType::DocVariableListType:
                {
                    FormatDocVariableListTypeTo( context, indentation, static_cast< const DocVariableListType& >( source ), dest );
                }
                break;
                case DoxType::DocVarListEntryType:
                {
                    FormatDocVarListEntryTypeTo( context, indentation, static_cast< const DocVarListEntryType& >( source ), dest );
                }
                break;
                case DoxType::DocSimpleSectType:
                {
                    FormatDocSimpleSectTypeTo( context, indentation, static_cast< const DocSimpleSectType& >( source ), dest );
                }
                break;
                case DoxType::DocListItemType:
                {
                    FormatDocListItemTypeTo( context, indentation, static_cast< const DocListItemType& >( source ), dest );
                }
                break;
                case DoxType::DocListType:
                {
                    FormatDocListTypeTo( context, indentation, static_cast< const DocListType& >( source ), dest );
                }
                break;
                case DoxType::DocIndexEntryType:
                {
                    FormatDocIndexEntryTypeTo( context, indentation, static_cast< const DocIndexEntryType& >( source ), dest );
                }
                break;
                case DoxType::DocFormulaType:
                {
                    FormatDocFormulaTypeTo( context, indentation, static_cast< const DocFormulaType& >( source ), dest );
                }
                break;
                case DoxType::DocAnchorType:
                {
                    FormatDocAnchorTypeTo( context, indentation, static_cast< const DocAnchorType& >( source ), dest );
                }
                break;
                case DoxType::DocURLLink:
                {
                    FormatDocURLLinkTo( context, indentation, static_cast< const DocURLLink& >( source ), dest );
                }
                break;
                case DoxType::DocMarkupType:
                {
                    FormatDocMarkupTypeTo( context, indentation, static_cast< const DocMarkupType& >( source ), dest );
                }
                break;
                case DoxType::DocParaType:
                {
                    FormatDocParaTypeTo( context, indentation, static_cast< const DocParaType& >( source ), dest );
                }
                break;
                case DoxType::DocCmdGroup:
                {
                    FormatDocCmdGroupTo( context, indentation, static_cast< const DocCmdGroup& >( source ), dest );
                }
                break;
                case DoxType::DocSummaryType:
                {
                    FormatDocSummaryTypeTo( context, indentation, static_cast< const DocSummaryType& >( source ), dest );
                }
                break;
                case DoxType::DocTitleType:
                {
                    FormatDocTitleTypeTo( context, indentation, static_cast< const DocTitleType& >( source ), dest );
                }
                break;
                case DoxType::DocTitleCmdGroup:
                {
                    FormatDocTitleCmdGroupTo( context, indentation, static_cast< const DocTitleCmdGroup& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS6Type:
                {
                    FormatDocInternalS6TypeTo( context, indentation, static_cast< const DocInternalS6Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS5Type:
                {
                    FormatDocInternalS5TypeTo( context, indentation, static_cast< const DocInternalS5Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS4Type:
                {
                    FormatDocInternalS4TypeTo( context, indentation, static_cast< const DocInternalS4Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS3Type:
                {
                    FormatDocInternalS3TypeTo( context, indentation, static_cast< const DocInternalS3Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS2Type:
                {
                    FormatDocInternalS2TypeTo( context, indentation, static_cast< const DocInternalS2Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalS1Type:
                {
                    FormatDocInternalS1TypeTo( context, indentation, static_cast< const DocInternalS1Type& >( source ), dest );
                }
                break;
                case DoxType::DocInternalType:
                {
                    FormatDocInternalTypeTo( context, indentation, static_cast< const DocInternalType& >( source ), dest );
                }
                break;
                case DoxType::DocSect6Type:
                {
                    FormatDocSect6TypeTo( context, indentation, static_cast< const DocSect6Type& >( source ), dest );
                }
                break;
                case DoxType::DocSect5Type:
                {
                    FormatDocSect5TypeTo( context, indentation, static_cast< const DocSect5Type& >( source ), dest );
                }
                break;
                case DoxType::DocSect4Type:
                {
                    FormatDocSect4TypeTo( context, indentation, static_cast< const DocSect4Type& >( source ), dest );
                }
                break;
                case DoxType::DocSect3Type:
                {
                    FormatDocSect3TypeTo( context, indentation, static_cast< const DocSect3Type& >( source ), dest );
                }
                break;
                case DoxType::DocSect2Type:
                {
                    FormatDocSect2TypeTo( context, indentation, static_cast< const DocSect2Type& >( source ), dest );
                }
                break;
                case DoxType::DocSect1Type:
                {
                    FormatDocSect1TypeTo( context, indentation, static_cast< const DocSect1Type& >( source ), dest );
                }
                break;
                case DoxType::LocationType:
                {
                    FormatLocationTypeTo( context, indentation, static_cast< const LocationType& >( source ), dest );
                }
                break;
                case DoxType::ReferenceType:
                {
                    FormatReferenceTypeTo( context, indentation, static_cast< const ReferenceType& >( source ), dest );
                }
                break;
                case DoxType::SpType:
                {
                    FormatSpTypeTo( context, indentation, static_cast< const SpType& >( source ), dest );
                }
                break;
                case DoxType::HighlightType:
                {
                    FormatHighlightTypeTo( context, indentation, static_cast< const HighlightType& >( source ), dest );
                }
                break;
                case DoxType::CodeLineType:
                {
                    FormatCodeLineTypeTo( context, indentation, static_cast< const CodeLineType& >( source ), dest );
                }
                break;
                case DoxType::ListingType:
                {
                    FormatListingTypeTo( context, indentation, static_cast< const ListingType& >( source ), dest );
                }
                break;
                case DoxType::LinkType:
                {
                    FormatLinkTypeTo( context, indentation, static_cast< const LinkType& >( source ), dest );
                }
                break;
                case DoxType::ChildNodeType:
                {
                    FormatChildNodeTypeTo( context, indentation, static_cast< const ChildNodeType& >( source ), dest );
                }
                break;
                case DoxType::NodeType:
                {
                    FormatNodeTypeTo( context, indentation, static_cast< const NodeType& >( source ), dest );
                }
                break;
                case DoxType::GraphType:
                {
                    FormatGraphTypeTo( context, indentation, static_cast< const GraphType& >( source ), dest );
                }
                break;
                case DoxType::LinkedTextType:
                {
                    FormatLinkedTextTypeTo( context, indentation, static_cast< const LinkedTextType& >( source ), dest );
                }
                break;
                case DoxType::ParamType:
                {
                    FormatParamTypeTo( context, indentation, static_cast< const ParamType& >( source ), dest );
                }
                break;
                case DoxType::TemplateParamListType:
                {
                    FormatTemplateParamListTypeTo( context, indentation, static_cast< const TemplateParamListType& >( source ), dest );
                }
                break;
                case DoxType::EnumvalueType:
                {
                    FormatEnumvalueTypeTo( context, indentation, static_cast< const EnumvalueType& >( source ), dest );
                }
                break;
                case DoxType::DescriptionType:
                {
                    FormatDescriptionTypeTo( context, indentation, static_cast< const DescriptionType& >( source ), dest );
                }
                break;
                case DoxType::MemberDefType:
                {
                    FormatMemberDefTypeTo( context, indentation, static_cast< const MemberDefType& >( source ), dest );
                }
                break;
                case DoxType::SectionDefType:
                {
                    FormatSectionDefTypeTo( context, indentation, static_cast< const SectionDefType& >( source ), dest );
                }
                break;
                case DoxType::MemberType:
                {
                    FormatMemberTypeTo( context, indentation, static_cast< const MemberType& >( source ), dest );
                }
                break;
                case DoxType::RefTextType:
                {
                    FormatRefTextTypeTo( context, indentation, static_cast< const RefTextType& >( source ), dest );
                }
                break;
                case DoxType::RefType:
                {
                    FormatRefTypeTo( context, indentation, static_cast< const RefType& >( source ), dest );
                }
                break;
                case DoxType::ExportType:
                {
                    FormatExportTypeTo( context, indentation, static_cast< const ExportType& >( source ), dest );
                }
                break;
                case DoxType::ExportsType:
                {
                    FormatExportsTypeTo( context, indentation, static_cast< const ExportsType& >( source ), dest );
                }
                break;
                case DoxType::IncType:
                {
                    FormatIncTypeTo( context, indentation, static_cast< const IncType& >( source ), dest );
                }
                break;
                case DoxType::ReimplementType:
                {
                    FormatReimplementTypeTo( context, indentation, static_cast< const ReimplementType& >( source ), dest );
                }
                break;
                case DoxType::CompoundRefType:
                {
                    FormatCompoundRefTypeTo( context, indentation, static_cast< const CompoundRefType& >( source ), dest );
                }
                break;
                case DoxType::DocHtmlOnlyType:
                {
                    FormatDocHtmlOnlyTypeTo( context, indentation, static_cast< const DocHtmlOnlyType& >( source ), dest );
                }
                break;
                case DoxType::MemberRefType:
                {
                    FormatMemberRefTypeTo( context, indentation, static_cast< const MemberRefType& >( source ), dest );
                }
                break;
                case DoxType::ListOfAllMembersType:
                {
                    FormatListOfAllMembersTypeTo( context, indentation, static_cast< const ListOfAllMembersType& >( source ), dest );
                }
                break;
                case DoxType::CompoundDefType:
                {
                    FormatCompoundDefTypeTo( context, indentation, static_cast< const CompoundDefType& >( source ), dest );
                }
                break;

            }
        }

    };

        

}


#endif
