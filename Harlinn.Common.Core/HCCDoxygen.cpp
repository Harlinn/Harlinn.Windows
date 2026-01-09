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
#include "pch.h"
#include "HCCDoxygen.h"
#include "HCCIO.h"
#include "HCCRapidXml.h"


namespace Harlinn::Common::Core::Doxygen
{
    inline std::string DecodeHtml( std::string_view text )
    {
        return Html::Decode<std::string>( text );
    }
    inline std::string DecodeHtml( const std::string& text )
    {
        return Html::Decode<std::string>( text );
    }


    using namespace std::literals::string_view_literals;
    using XmlNodeType = RapidXml::NodeType;

    bool TryParseCmdGroupType( const RapidXml::XmlNode<>& xmlNode, DocCmdGroupType& result )
    {
        if ( xmlNode.NodeType( ) == XmlNodeType::node_element )
        {
            DoxCmdGroupType doxCmdGroupType{};
            auto tmp = xmlNode.Name( );
            std::string nodeName( tmp.data(), tmp.size() );
            if ( TryParse( nodeName, doxCmdGroupType ) )
            {
                result.Type = doxCmdGroupType;
                switch ( doxCmdGroupType )
                {
                    case DoxCmdGroupType::ulink:
                    {
                        result.Value = std::make_shared<DocURLLink>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::bold:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::s:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::strike:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::underline:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::emphasis:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::computeroutput:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::subscript:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::superscript:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::center:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::Small:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::cite:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::del:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::ins:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::htmlonly:
                    {
                        result.Value = std::make_shared<DocHtmlOnlyType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::manonly:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::xmlonly:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::rtfonly:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::latexonly:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::docbookonly:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::image:
                    {
                        result.Value = std::make_shared<DocImageType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::dot:
                    {
                        result.Value = std::make_shared<DocDotMscType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::msc:
                    {
                        result.Value = std::make_shared<DocDotMscType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::plantuml:
                    {
                        result.Value = std::make_shared<DocPlantumlType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::anchor:
                    {
                        result.Value = std::make_shared<DocAnchorType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::formula:
                    {
                        result.Value = std::make_shared<DocFormulaType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::ref:
                    {
                        result.Value = std::make_shared<DocRefTextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::emoji:
                    {
                        result.Value = std::make_shared<DocEmojiType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::preformatted:
                    {
                        result.Value = std::make_shared<DocMarkupType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::programlisting:
                    {
                        result.Value = std::make_shared<ListingType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::verbatim:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::javadocliteral:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::javadoccode:
                    {
                        result.Value = std::make_shared<TextType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::indexentry:
                    {
                        result.Value = std::make_shared<DocIndexEntryType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::orderedlist:
                    {
                        result.Value = std::make_shared<DocListType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::itemizedlist:
                    {
                        result.Value = std::make_shared<DocListType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::simplesect:
                    {
                        result.Value = std::make_shared<DocSimpleSectType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::title:
                    {
                        result.Value = std::make_shared<DocTitleType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::variablelist:
                    {
                        result.Value = std::make_shared<DocVariableListType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::table:
                    {
                        result.Value = std::make_shared<DocTableType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::heading:
                    {
                        result.Value = std::make_shared<DocHeadingType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::dotfile:
                    {
                        result.Value = std::make_shared<DocImageFileType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::mscfile:
                    {
                        result.Value = std::make_shared<DocImageFileType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::diafile:
                    {
                        result.Value = std::make_shared<DocImageFileType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::toclist:
                    {
                        result.Value = std::make_shared<DocTocListType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::language:
                    {
                        result.Value = std::make_shared<DocLanguageType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::parameterlist:
                    {
                        result.Value = std::make_shared<DocParamListType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::xrefsect:
                    {
                        result.Value = std::make_shared<DocXRefSectType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::copydoc:
                    {
                        result.Value = std::make_shared<DocCopyType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::details:
                    {
                        result.Value = std::make_shared<DocDetailsType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::blockquote:
                    {
                        result.Value = std::make_shared<DocBlockQuoteType>( xmlNode );
                    }
                    break;
                    case DoxCmdGroupType::parblock:
                    {
                        result.Value = std::make_shared<DocParBlockType>( xmlNode );
                    }
                    break;
                    default:
                    {
                        result.Value.reset( );
                        return false;
                    }
                    break;
                }
                return true;
            }
        }
        return false;
    }

    bool TryParseTextOrCmdGroupType( const RapidXml::XmlNode<>& xmlNode, DocCmdGroupType& result )
    {
        if ( xmlNode.NodeType( ) == XmlNodeType::node_data )
        {
            if ( xmlNode.NodeType( ) == XmlNodeType::node_data )
            {
                auto text = xmlNode.ToString( );
                if ( text.size( ) )
                {
                    result.Type = DoxCmdGroupType::text;
                    auto decoded = DecodeHtml( text );
                    result.Value = std::make_shared<TextType>( decoded );
                    return true;
                }
            }
            return false;
        }
        else
        {
            return TryParseCmdGroupType( xmlNode, result );
        }
    }


    TextType::TextType( const XmlNode& xmlNode )
    {
        auto value = xmlNode.Value( );
        text_ = DecodeHtml( value );
    }

    TitleType::TitleType( const XmlNode& xmlNode )
    {
        auto value = xmlNode.Value( );
        text_ = DecodeHtml( value );
    }

    DocEmojiType::DocEmojiType( const XmlNode& xmlNode )
    {
        name_ = DecodeHtml( xmlNode.Read<std::string>( "name" ) );
        unicode_ = DecodeHtml( xmlNode.Read<std::string>( "unicode" ) );
    }

    TableOfContentsKindType::TableOfContentsKindType( const XmlNode& xmlNode )
    {
        /*
        name_ = xmlNode.Read<std::string>( L"name" );
        reference_ = xmlNode.Read<std::string>( L"reference" );
        auto childNodes = xmlNode.ChildNodes( );
        for ( auto& childNode : childNodes )
        {
            if ( childNode.NodeType( ) == XmlNodeType::Element )
            {
                auto element = childNode.As<XmlNode>( );
                auto tagName = element.TagName( );
                if ( tagName == L"tableofcontents" )
                {
                    auto tableofcontents = std::make_shared<TableOfContentsType>( element );
                    Add( std::move( tableofcontents ) );
                }
            }
        }
        */
    }

    TableOfContentsType::TableOfContentsType( const XmlNode& xmlNode )
    {

    }

    DocEmptyType::DocEmptyType( const XmlNode& xmlNode )
    {

    }

    DocParBlockType::DocParBlockType( const XmlNode& xmlNode )
    {
        static constexpr auto para = "para"sv;
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                if ( childNode.Name( ) == para )
                {
                    auto docParaType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docParaType ) );
                }
                
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocBlockQuoteType::DocBlockQuoteType( const XmlNode& xmlNode )
    {
        static constexpr auto para = "para"sv;
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                if ( childNode.Name( ) == para )
                {
                    auto docParaType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docParaType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocDetailsType::DocDetailsType( const XmlNode& xmlNode )
    {
        static constexpr auto summary = "summary"sv;
        static constexpr auto para = "para"sv;
        
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                if ( childNode.Name( ) == summary )
                {
                    summary_ = std::make_shared<DocSummaryType>( childNode );
                }
                else if ( childNode.Name( ) == para )
                {
                    auto docParaType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docParaType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocCopyType::DocCopyType( const XmlNode& xmlNode )
    {
        static constexpr auto link = "link"sv;
        static constexpr auto sect1 = "sect1"sv;
        static constexpr auto internal = "internal"sv;
        static constexpr auto para = "para"sv;

        link_ = DecodeHtml( xmlNode.Read<std::string>( link ) );

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                if ( childNode.Name( ) == para )
                {
                    auto item = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( item ) );
                }
                else if ( childNode.Name( ) == sect1 )
                {
                    auto item = std::make_shared<DocSect1Type>( childNode );
                    sect1_.emplace_back( std::move( item ) );
                }
                else if ( childNode.Name( ) == internal )
                {
                    auto item = std::make_shared<DocInternalType>( childNode );
                    internal_.emplace_back( std::move( item ) );
                }
                
                childNode = childNode.NextSibling( para );
            } while ( childNode );
        }
    }

    DocXRefSectType::DocXRefSectType( const XmlNode& xmlNode )
    {
        
    }

    DocParamName::DocParamName( const XmlNode& xmlNode )
    {
        static constexpr auto direction = "direction"sv;
        auto directionAttribute = xmlNode.Attribute( direction );
        if ( directionAttribute )
        {
            direction_ = directionAttribute.Read<DoxParamDir>( );
        }

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( childNode.NodeType( ) == XmlNodeType::node_data )
                {
                    auto text = Trim( childNode.ToString( ) );
                    if ( text.size( ) )
                    {
                        auto decoded = DecodeHtml( text );
                        auto textType = std::make_shared<TextType>( decoded );
                        emplace_back( std::move( textType ) );
                    }
                }
                else if ( nodeName == "ref"sv )
                {
                    ref_ = std::make_shared<RefTextType>( childNode );
                    emplace_back( ref_ );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocParamType::DocParamType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( childNode.NodeType( ) == XmlNodeType::node_data )
                {
                    auto text = Trim( childNode.ToString( ) );
                    if ( text.size( ) )
                    {
                        auto decoded = DecodeHtml( text );
                        auto textType = std::make_shared<TextType>( decoded );
                        emplace_back( std::move( textType ) );
                    }
                }
                else if ( nodeName == "ref"sv )
                {
                    ref_ = std::make_shared<RefTextType>( childNode );
                    emplace_back( ref_ );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocParamNameList::DocParamNameList( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( nodeName == "parametertype"sv )
                {
                    auto item = std::make_shared<DocParamType>( childNode );
                    emplace_back( std::move( item ) );
                }
                else if ( nodeName == "parametername"sv )
                {
                    auto item = std::make_shared<DocParamName>( childNode );
                    emplace_back( std::move( item ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocParamListItem::DocParamListItem( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( nodeName == "parameternamelist"sv )
                {
                    auto item = std::make_shared<DocParamNameList>( childNode );
                    emplace_back( std::move( item ) );
                }
                else if ( nodeName == "parameterdescription"sv )
                {
                    parameterDescription_ = std::make_shared<DescriptionType>( childNode );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocParamListType::DocParamListType( const XmlNode& xmlNode )
    {
        kind_ = xmlNode.Read<DoxParamListKind>( "kind"sv );
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( nodeName == "parameteritem"sv )
                {
                    auto item = std::make_shared<DocParamListItem>( childNode );
                    emplace_back( std::move( item ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocLanguageType::DocLanguageType( const XmlNode& xmlNode )
    {
        static constexpr auto langid = "langid"sv;
        static constexpr auto para = "para"sv;

        langid_ = DecodeHtml( xmlNode.Read<std::string>( langid ) );

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                if ( childNode.Name( ) == para )
                {
                    auto item = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( item ) );
                }

                childNode = childNode.NextSibling( para );
            } while ( childNode );
        }
    }

    DocTocListType::DocTocListType( const XmlNode& xmlNode )
    {

    }

    DocTocItemType::DocTocItemType( const XmlNode& xmlNode )
    {

    }

    DocPlantumlType::DocPlantumlType( const XmlNode& xmlNode )
    {

    }

    DocImageFileType::DocImageFileType( const XmlNode& xmlNode )
    {

    }

    DocDotMscType::DocDotMscType( const XmlNode& xmlNode )
    {

    }

    DocImageType::DocImageType( const XmlNode& xmlNode )
    {

    }

    DocHeadingType::DocHeadingType( const XmlNode& xmlNode )
    {
        static constexpr auto level = "level"sv;
        auto levelAttribute = xmlNode.Attribute( level );
        if ( levelAttribute )
        {
            level_ = levelAttribute.Read<int>( );
        }
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocCaptionType::DocCaptionType( const XmlNode& xmlNode )
    {
        static constexpr auto id = "id"sv;
        auto idAttribute = xmlNode.Attribute( id );
        if ( idAttribute )
        {
            id_ = idAttribute.Read<int>( );
        }
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocEntryType::DocEntryType( const XmlNode& xmlNode )
    {

    }

    DocRowType::DocRowType( const XmlNode& xmlNode )
    {

    }

    DocTableType::DocTableType( const XmlNode& xmlNode )
    {

    }

    DocRefTextType::DocRefTextType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        kindRef_ = xmlNode.Read<DoxRefKind>( "kindref" );
        external_ = DecodeHtml( xmlNode.Read<std::string>( "external" ) );
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocVariableListType::DocVariableListType( const XmlNode& xmlNode )
    {
        
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto childNodeName = childNode.Name( );
                if ( childNodeName == "listitem"sv )
                {
                    auto item = std::make_shared<DocListItemType>( childNode );
                    emplace_back( std::move( item ) );
                }
                else if ( childNodeName == "varlistentry"sv )
                {
                    auto item = std::make_shared<DocVarListEntryType>( childNode );
                    emplace_back( std::move( item ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
        
    }

    /*
    DocVariableListGroup::DocVariableListGroup( const XmlNode& xmlNode )
    {
        varListEntry_ = xmlNode.Child<DocVarListEntryType>( "varlistentry" );
        listItem_ = xmlNode.Child<DocListItemType>( "listitem" );
    }
    */

    DocVarListEntryType::DocVarListEntryType( const XmlNode& xmlNode )
    {
        term_ = xmlNode.Child<DocTitleType>( "title" );
    }

    DocSimpleSectType::DocSimpleSectType( const XmlNode& xmlNode )
    {
        kind_ = xmlNode.Read<DoxSimpleSectKind>( "kind" );
        title_ = xmlNode.Child<DocTitleType>( "title" );

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto childNodeName = childNode.Name( );
                if ( childNodeName == "para"sv )
                {
                    auto docListItemType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docListItemType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocListItemType::DocListItemType( const XmlNode& xmlNode )
    {
        override_ = xmlNode.Read<DoxCheck>( "override" );
        value_ = xmlNode.Read<Int32>( "value" );

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto childNodeName = childNode.Name( );
                if ( childNodeName == "para"sv )
                {
                    auto docListItemType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docListItemType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }

    }

    DocListType::DocListType( const XmlNode& xmlNode )
    {
        type_ = xmlNode.Read<DoxOlType>("type" );
        start_ = xmlNode.Read<Int32>( "start" );
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto childNodeName = childNode.Name( );
                if ( childNodeName == "listitem"sv )
                {
                    auto docListItemType = std::make_shared<DocListItemType>( childNode );
                    emplace_back( std::move( docListItemType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocIndexEntryType::DocIndexEntryType( const XmlNode& xmlNode )
    {
        primary_ = DecodeHtml( xmlNode.Child<std::string>( "primaryie" ) );
        secondary_ = DecodeHtml( xmlNode.Child<std::string>( "secondaryie" ) );
    }

    DocFormulaType::DocFormulaType( const XmlNode& xmlNode )
    {
        id_ = DecodeHtml( xmlNode.Read<std::string>( "id" ) );
        content_ = DecodeHtml( Trim( xmlNode.ToString<std::string>( ) ) );
    }

    DocAnchorType::DocAnchorType( const XmlNode& xmlNode )
    {
        id_ = DecodeHtml( xmlNode.Read<std::string>( "id" ) );
        content_ = DecodeHtml( Trim(xmlNode.ToString<std::string>( )) );
    }

    DocURLLink::DocURLLink( const XmlNode& xmlNode )
    {
        url_ = xmlNode.Read<std::string>( "url" );
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocMarkupType::DocMarkupType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocParaType::DocParaType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    /*
    DocCmdGroup::DocCmdGroup( const XmlNode& xmlNode )
    {

    }
    */

    DocSummaryType::DocSummaryType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    DocTitleType::DocTitleType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do 
            {
                DocCmdGroupType nodeValue;
                if ( TryParseTextOrCmdGroupType( childNode, nodeValue ) )
                {
                    emplace_back( nodeValue );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    /*
    DocTitleCmdGroup::DocTitleCmdGroup( const XmlNode& xmlNode )
    {

    }
    */

    namespace Internal
    {
        template<Doxygen::DoxType doxType>
        DocInternalSectionBaseType<doxType>::DocInternalSectionBaseType( const XmlNode& xmlNode )
        {
            std::string id_ = xmlNode.Read<std::string>( "id" );

            auto childNode = xmlNode.FirstNode( );
            if ( childNode )
            {
                do
                {
                    auto nodeName = childNode.Name( );
                    if ( childNode.NodeType( ) == XmlNodeType::node_data )
                    {
                        auto text = Trim( childNode.ToString( ) );
                        if ( text.size( ) )
                        {
                            auto decoded = DecodeHtml( text );
                            auto textType = std::make_shared<TextType>( decoded );
                            emplace_back( std::move( textType ) );
                        }
                    }
                    else if ( nodeName == "title"sv )
                    {
                        title_ = std::make_shared<TitleType>( childNode );
                        emplace_back( title_ );
                    }
                    else if ( nodeName == "para"sv )
                    {
                        auto paraType = std::make_shared<ParaType>( childNode );
                        para_.emplace_back( paraType );
                        emplace_back( std::move( paraType ) );
                    }
                    childNode = childNode.NextSibling( );
                } while ( childNode );
            }
        }

        template<Doxygen::DoxType doxType, typename SubSectT  >
        DocInternalSectionType<doxType, SubSectT>::DocInternalSectionType( const XmlNode& xmlNode, std::string_view subSectionElementName )
        {
            std::string id_ = xmlNode.Read<std::string>( "id" );

            auto childNode = xmlNode.FirstNode( );
            if ( childNode )
            {
                do
                {
                    auto nodeName = childNode.Name( );
                    if ( childNode.NodeType( ) == XmlNodeType::node_data )
                    {
                        auto text = Trim( childNode.ToString( ) );
                        if ( text.size( ) )
                        {
                            auto decoded = DecodeHtml( text );
                            auto textType = std::make_shared<TextType>( decoded );
                            emplace_back( std::move( textType ) );
                        }
                    }
                    else if ( nodeName == "title"sv )
                    {
                        title_ = std::make_shared<TitleType>( childNode );
                        emplace_back( title_ );
                    }
                    else if ( nodeName == "para"sv )
                    {
                        auto paraType = std::make_shared<ParaType>( childNode );
                        para_.emplace_back( paraType );
                        emplace_back( std::move( paraType ) );
                    }
                    else if ( nodeName == subSectionElementName )
                    {
                        auto subSectType = std::make_shared<SubSectType>( childNode );
                        subSections_.emplace_back( subSectType );
                        emplace_back( std::move( subSectType ) );
                    }
                    childNode = childNode.NextSibling( );
                } while ( childNode );
            }
        }

    }

    DocInternalS6Type::DocInternalS6Type( const XmlNode& xmlNode )
        : Base( xmlNode )
    {
    }

    DocInternalS5Type::DocInternalS5Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect5"sv )
    {
    }

    DocInternalS4Type::DocInternalS4Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect5"sv )
    {
    }

    DocInternalS3Type::DocInternalS3Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect4"sv )
    {
    }

    DocInternalS2Type::DocInternalS2Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect3"sv )
    {
    }

    DocInternalS1Type::DocInternalS1Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect2"sv )
    {
    }

    DocInternalType::DocInternalType( const XmlNode& xmlNode )
        : Base( xmlNode, "sect1"sv )
    {
    }


    namespace Internal
    {
        template<Doxygen::DoxType doxType, typename InternalT>
        DocSectionBaseType<doxType, InternalT>::DocSectionBaseType( const XmlNode& xmlNode )
        {
            std::string id_ = xmlNode.Read<std::string>( "id" );

            auto childNode = xmlNode.FirstNode( );
            if ( childNode )
            {
                do
                {
                    auto nodeName = childNode.Name( );
                    if ( childNode.NodeType( ) == XmlNodeType::node_data )
                    {
                        auto text = Trim( childNode.ToString( ) );
                        if ( text.size( ) )
                        {
                            auto decoded = DecodeHtml( text );
                            auto textType = std::make_shared<TextType>( decoded );
                            emplace_back( std::move( textType ) );
                        }
                    }
                    else if ( nodeName == "title"sv )
                    {
                        title_ = std::make_shared<TitleType>( childNode );
                        emplace_back( title_ );
                    }
                    else if ( nodeName == "para"sv )
                    {
                        auto paraType = std::make_shared<ParaType>( childNode );
                        para_.emplace_back( paraType );
                        emplace_back( std::move( paraType ) );
                    }
                    else if ( nodeName == "internal"sv )
                    {
                        auto internalType = std::make_shared<InternalType>( childNode );
                        internal_.emplace_back( internalType );
                        emplace_back( std::move( internalType ) );
                    }
                    childNode = childNode.NextSibling( );
                } while ( childNode );
            }
        }

        template<Doxygen::DoxType doxType, typename InternalT, typename SubSectT  >
        DocSectionType<doxType, InternalT, SubSectT>::DocSectionType( const XmlNode& xmlNode, std::string_view subSectionElementName )
        {
            std::string id_ = xmlNode.Read<std::string>( "id" );

            auto childNode = xmlNode.FirstNode( );
            if ( childNode )
            {
                do
                {
                    auto nodeName = childNode.Name( );
                    if ( childNode.NodeType( ) == XmlNodeType::node_data )
                    {
                        auto text = Trim( childNode.ToString( ) );
                        if ( text.size( ) )
                        {
                            auto decoded = DecodeHtml( text );
                            auto textType = std::make_shared<TextType>( decoded );
                            emplace_back( std::move( textType ) );
                        }
                    }
                    else if ( nodeName == "title"sv )
                    {
                        title_ = std::make_shared<TitleType>( childNode );
                        emplace_back( title_ );
                    }
                    else if ( nodeName == "para"sv )
                    {
                        auto paraType = std::make_shared<ParaType>( childNode );
                        para_.emplace_back( paraType );
                        emplace_back( std::move( paraType ) );
                    }
                    else if ( nodeName == "internal"sv )
                    {
                        auto internalType = std::make_shared<InternalType>( childNode );
                        internal_.emplace_back( internalType );
                        emplace_back( std::move( internalType ) );
                    }
                    else if ( nodeName == subSectionElementName )
                    {
                        auto subSectType = std::make_shared<SubSectType>( childNode );
                        subSections_.emplace_back( subSectType );
                        emplace_back( std::move( subSectType ) );
                    }
                    childNode = childNode.NextSibling( );
                } while ( childNode );
            }
        }

    }

    DocSect6Type::DocSect6Type( const XmlNode& xmlNode )
        : Base( xmlNode )
    {
    }

    DocSect5Type::DocSect5Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect6"sv )
    {
    }

    DocSect4Type::DocSect4Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect5"sv )
    {
    }

    DocSect3Type::DocSect3Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect4"sv )
    {
    }

    DocSect2Type::DocSect2Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect3"sv )
    {
    }

    DocSect1Type::DocSect1Type( const XmlNode& xmlNode )
        : Base( xmlNode, "sect2"sv )
    {
    }


    LocationType::LocationType( const XmlNode& xmlNode )
    {
        file_ = xmlNode.Read<std::string>( "file" );
        line_ = xmlNode.Read<Int32>( "line" );
        column_ = xmlNode.Read<Int32>( "column" );
        declFile_ = xmlNode.Read<std::string>( "declfile" );
        declLine_ = xmlNode.Read<Int32>( "declline" );
        declColumn_ = xmlNode.Read<Int32>( "declcolumn" );
        bodyFile_ = xmlNode.Read<std::string>( "bodyfile" );
        bodyStart_ = xmlNode.Read<Int32>( "bodystart" );
        bodyEnd_ = xmlNode.Read<Int32>( "bodyend" );
    }

    ReferenceType::ReferenceType( const XmlNode& xmlNode )
    {
        std::string refId_ = xmlNode.Read<std::string>( "refid" );
        std::string compoundRef_ = xmlNode.Read<std::string>( "compoundref" );
        Int32 startLine_ = xmlNode.Read<Int32>( "startline" );
        Int32 endline_ = xmlNode.Read<Int32>( "endline" );
        text_ = Trim( xmlNode.ToString( ) );
    }

    SpType::SpType( const XmlNode& xmlNode )
    {
        value_ = xmlNode.Read<Int32>( "value" );
        text_ = Trim( xmlNode.ToString( ) );
    }

    HighlightType::HighlightType( const XmlNode& xmlNode )
    {
        class_ = xmlNode.Read<DoxHighlightClass>( "class" );

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( childNode.NodeType( ) == XmlNodeType::node_data )
                {
                    auto text = Trim( childNode.ToString( ) );
                    if ( text.size( ) )
                    {
                        auto decoded = DecodeHtml( text );
                        auto textType = std::make_shared<TextType>( decoded );
                        emplace_back( std::move( textType ) );
                    }
                }
                else if ( nodeName == "ref"sv )
                {
                    auto refTextType = std::make_shared<RefTextType>( childNode );
                    ref_.emplace_back( refTextType );
                    emplace_back( std::move( refTextType ) );
                }
                else if ( nodeName == "sp"sv )
                {
                    auto spType = std::make_shared<SpType>( childNode );
                    emplace_back( std::move( spType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    CodeLineType::CodeLineType( const XmlNode& xmlNode )
    {
        lineno_ = xmlNode.Read<Int32>( "lineno" );
        refId_ = xmlNode.Read<std::string>( "refid" );
        refKind_ = xmlNode.Read<DoxRefKind>( "refkind" );
        external_ = xmlNode.Read<bool>( "external" );
        highlight_ = xmlNode.Children<HighlightType>( "highlight" );
    }

    ListingType::ListingType( const XmlNode& xmlNode )
    {
        fileName_ = xmlNode.Read<std::string>( "refid" );
        static_cast< std::vector<CodeLineTypePtr>& >( *this ) = xmlNode.Children<CodeLineType>( "codeline" );
    }

    LinkType::LinkType( const XmlNode& xmlNode )
    {
        std::string refId_ = xmlNode.Read<std::string>( "refid" );
        std::string external_ = xmlNode.Read<std::string>( "external" );
    }

    ChildNodeType::ChildNodeType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<std::string>( "refid" );
        relation_ = xmlNode.Read<DoxGraphRelation>( "relation" );
        edgeLabel_ = xmlNode.Children<std::string>( "edgelabel" );
    }

    NodeType::NodeType( const XmlNode& xmlNode )
    {
        std::string id_ = xmlNode.Read<std::string>( "id" );
        std::string label_ = DecodeHtml( xmlNode.Child<std::string>( "label" ) );
        LinkTypePtr link_ = xmlNode.Child<LinkType>( "link" );
        std::vector<ChildNodeTypePtr> childNode_ = xmlNode.Children<ChildNodeType>( "childnode" );
    }

    GraphType::GraphType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<NodeTypePtr>& >( *this ) = xmlNode.Children<NodeType>( "node" );
    }

    LinkedTextType::LinkedTextType( const XmlNode& xmlNode )
    {
        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( childNode.NodeType( ) == XmlNodeType::node_data )
                {
                    auto text = Trim( childNode.ToString( ) );
                    if ( text.size( ) )
                    {
                        auto decoded = DecodeHtml( text );
                        auto textType = std::make_shared<TextType>( decoded );
                        emplace_back( std::move(textType) );
                    }
                }
                else if ( nodeName == "ref"sv )
                {
                    auto refTextType = std::make_shared<RefTextType>( childNode );
                    ref_.emplace_back( refTextType );
                    emplace_back( std::move( refTextType ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    ParamType::ParamType( const XmlNode& xmlNode )
    {
        attributes_ = DecodeHtml( xmlNode.Child<std::string>( "attributes" ) );
        type_ = xmlNode.Child<LinkedTextType>( "type" );
        declName_ = DecodeHtml( xmlNode.Child<std::string>( "declname" ) );
        defName_ = DecodeHtml( xmlNode.Child<std::string>( "defname" ) );
        array_ = DecodeHtml( xmlNode.Child<std::string>( "array" ) );
        defVal_ = xmlNode.Child<LinkedTextType>( "defval" );
        typeConstraint_ = xmlNode.Child<LinkedTextType>( "typeconstraint" );
        briefDescription_ = xmlNode.Child<DescriptionType>( "briefdescription" );
    }

    TemplateParamListType::TemplateParamListType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<ParamTypePtr>& >( *this ) = xmlNode.Children<ParamType>( "param" );
    }

    EnumvalueType::EnumvalueType( const XmlNode& xmlNode )
    {
        id_ = xmlNode.Read<std::string>( "id" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        name_ = DecodeHtml( xmlNode.Child<std::string>( "name" ) );
        initializer_ = xmlNode.Child<LinkedTextType>( "initializer" );
        briefDescription_ = xmlNode.Child<DescriptionType>( "briefdescription" );
        detailedDescription_ = xmlNode.Child<DescriptionType>( "detaileddescription" );
    }

    DescriptionType::DescriptionType( const XmlNode& xmlNode )
    {
        static constexpr auto title = "title"sv;
        static constexpr auto para = "para"sv;
        static constexpr auto internal = "internal"sv;
        static constexpr auto sect1 = "sect1"sv;

        auto childNode = xmlNode.FirstNode( );
        if ( childNode )
        {
            do
            {
                auto nodeName = childNode.Name( );
                if ( childNode.NodeType( ) == XmlNodeType::node_data )
                {
                    auto tmp = childNode.Value( );
                    std::string value( tmp.data( ), tmp.size( ) );
                    value = Trim( value );
                    if ( value.size( ) )
                    {
                        auto decoded = DecodeHtml( value );
                        auto textType = std::make_shared<TextType>( decoded );
                        emplace_back( std::move( textType ) );
                    }
                }
                else if ( nodeName == title )
                {
                    auto titleType = std::make_shared<TitleType>( childNode );
                    title_ = titleType;
                }
                else if ( nodeName == para )
                {
                    auto docParaType = std::make_shared<DocParaType>( childNode );
                    emplace_back( std::move( docParaType ) );
                }
                else if ( nodeName == internal )
                {
                    auto docInternalType = std::make_shared<DocInternalType>( childNode );
                    internal_.emplace_back( std::move( docInternalType ) );
                }
                else if ( nodeName == sect1 )
                {
                    auto docSect1Type = std::make_shared<DocSect1Type>( childNode );
                    sect1_.emplace_back( std::move( docSect1Type ) );
                }
                childNode = childNode.NextSibling( );
            } while ( childNode );
        }
    }

    MemberDefType::MemberDefType( const XmlNode& xmlNode )
    {
        kind_ = xmlNode.Read<DoxMemberKind>( "kind" );
        id_ = xmlNode.Read<std::string>( "id" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        static_ = xmlNode.Read<bool>( "static" );
        extern_ = xmlNode.Read<bool>( "extern" );
        strong_ = xmlNode.Read<bool>( "strong" );
        const_ = xmlNode.Read<bool>( "const" );
        explicit_ = xmlNode.Read<bool>( "explicit" );
        inline_ = xmlNode.Read<bool>( "inline" );
        refQual_ = xmlNode.Read<DoxRefQualifierKind>( "refqual" );
        virt_ = xmlNode.Read<DoxVirtualKind>( "virt" );
        volatile_ = xmlNode.Read<bool>( "volatile" );
        mutable_ = xmlNode.Read<bool>( "mutable" );
        noExcept_ = xmlNode.Read<bool>( "noexcept" );
        noexceptExpression_ = xmlNode.Read<std::string>( "noexceptexpression" );
        nodiscard_ = xmlNode.Read<bool>( "nodiscard" );
        constexpr_ = xmlNode.Read<bool>( "constexpr" );
        consteval_ = xmlNode.Read<bool>( "consteval" );
        constinit_ = xmlNode.Read<bool>( "constinit" );
        //  Qt property
        readable_ = xmlNode.Read<bool>( "readable" );
        writable_ = xmlNode.Read<bool>( "writable" );
        // C++/CLI variable
        initOnly_ = xmlNode.Read<bool>( "initonly" );
        // C++/CLI and C# property
        settable_ = xmlNode.Read<bool>( "settable" );
        privateSettable_ = xmlNode.Read<bool>( "privatesettable" );
        protectedSettable_ = xmlNode.Read<bool>( "protectedsettable" );
        gettable_ = xmlNode.Read<bool>( "gettable" );
        privateGettable_ = xmlNode.Read<bool>( "privategettable" );
        protectedGettable_ = xmlNode.Read<bool>( "protectedgettable" );
        // C++/CLI function
        final_ = xmlNode.Read<bool>( "final" );
        sealed_ = xmlNode.Read<bool>( "sealed" );
        new_ = xmlNode.Read<bool>( "new" );
        // C++/CLI event
        add_ = xmlNode.Read<bool>( "add" );
        remove_ = xmlNode.Read<bool>( "remove" );
        raise_ = xmlNode.Read<bool>( "raise" );
        // Objective-C 2.0 protocol method
        optional_ = xmlNode.Read<bool>( "optional" );
        required_ = xmlNode.Read<bool>( "required" );
        // Objective-C 2.0 property accessor
        accessor_ = xmlNode.Read<bool>( "accessor" );
        // UNO IDL
        attribute_ = xmlNode.Read<bool>( "attribute" );
        property_ = xmlNode.Read<bool>( "property" );
        readonly_ = xmlNode.Read<bool>( "readonly" );
        bound_ = xmlNode.Read<bool>( "bound" );
        removable_ = xmlNode.Read<bool>( "removable" );
        constrained_ = xmlNode.Read<bool>( "constrained" );
        transient_ = xmlNode.Read<bool>( "transient" );
        maybeVoid_ = xmlNode.Read<bool>( "maybevoid" );
        maybeDefault_ = xmlNode.Read<bool>( "maybedefault" );
        maybeAmbiguous_ = xmlNode.Read<bool>( "maybeambiguous" );


        templateParamList_ = xmlNode.Child<TemplateParamListType>( "templateparamlist" );
        type_ = xmlNode.Child<LinkedTextType>( "type" );
        definition_ = DecodeHtml( xmlNode.Child<std::string>( "definition" ) );
        argsString_ = DecodeHtml( xmlNode.Child<std::string>( "argsstring" ) );
        name_ = DecodeHtml( xmlNode.Child<std::string>( "name" ) );
        qualifiedName_ = DecodeHtml( xmlNode.Child<std::string>( "qualifiedname" ) );
        read_ = DecodeHtml( xmlNode.Child<std::string>( "read" ) );
        write_ = DecodeHtml( xmlNode.Child<std::string>( "write" ) );
        bitField_ = DecodeHtml( xmlNode.Child<std::string>( "bitfield" ) );
        reimplements_ = xmlNode.Children<ReimplementType>( "reimplements" );
        reimplementedBy_ = xmlNode.Children<ReimplementType>( "reimplementedby" );
        qualifier_ = DecodeHtml( xmlNode.Child<std::string>( "qualifier" ) );
        param_ = xmlNode.Children<ParamType>( "param" );
        enumvalue_ = xmlNode.Children<EnumvalueType>( "enumvalue" );
        requiresClause_ = xmlNode.Child<LinkedTextType>( "requiresclause" );
        initializer_ = xmlNode.Child<LinkedTextType>( "initializer" );
        exceptions_ = xmlNode.Child<LinkedTextType>( "exceptions" );
        briefDescription_ = xmlNode.Child<DescriptionType>( "briefdescription" );
        detailedDescription_ = xmlNode.Child<DescriptionType>( "detaileddescription" );
        inbodyDescription_ = xmlNode.Child<DescriptionType>( "inbodydescription" );
        location_ = xmlNode.Child<LocationType>( "location" );
        references_ = xmlNode.Children<ReferenceType>( "references" );
        referencedBy_ = xmlNode.Children<ReferenceType>( "referencedby" );

    }

    SectionDefType::SectionDefType( const XmlNode& xmlNode )
    {
        header_ = DecodeHtml( xmlNode.Child<std::string>( "header" ) );
        description_ = xmlNode.Child<DescriptionType>( "description" );
        memberDef_ = xmlNode.Children<MemberDefType>( "memberdef" );
        member_ = xmlNode.Children<MemberType>( "member" );
        kind_ = xmlNode.Read<DoxSectionKind>( "kind" );
    }

    MemberType::MemberType( const XmlNode& xmlNode )
    {
        name_ = DecodeHtml( xmlNode.Child<std::string>( "name" ) );
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        kind_ = xmlNode.Read<MemberKind>( "kind" );
    }

    RefTextType::RefTextType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        kindRef_ = xmlNode.Read<DoxRefKind>( "kindref" );
        external_ = DecodeHtml( xmlNode.Read<std::string>( "external" ) );
        tooltip_ = DecodeHtml( xmlNode.Read<std::string>( "tooltip" ) );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    RefType::RefType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        inline_ = xmlNode.Read<bool>( "inline" );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    ExportType::ExportType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    ExportsType::ExportsType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<ExportTypePtr>& >( *this ) = xmlNode.Children<ExportType>( "export" );
    }

    IncType::IncType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        local_ = xmlNode.Read<bool>( "local" );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    ReimplementType::ReimplementType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    CompoundRefType::CompoundRefType( const XmlNode& xmlNode )
    {
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        virt_ = xmlNode.Read<DoxVirtualKind>( "virt" );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    DocHtmlOnlyType::DocHtmlOnlyType( const XmlNode& xmlNode )
    {
        block_ = DecodeHtml( xmlNode.Read<std::string>( "block" ) );
        content_ = DecodeHtml( xmlNode.Content<std::string>( ) );
    }

    MemberRefType::MemberRefType( const XmlNode& xmlNode )
    {
        name_ = DecodeHtml( xmlNode.Child<std::string>( "name" ) );
        scope_ = DecodeHtml( xmlNode.Child<std::string>( "scope" ) );
        refId_ = DecodeHtml( xmlNode.Read<std::string>( "refid" ) );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        virt_ = xmlNode.Read<DoxVirtualKind>( "virt" );
        ambiguityScope_ = DecodeHtml( xmlNode.Read<std::string>( "ambiguityscope" ) );
    }

    ListOfAllMembersType::ListOfAllMembersType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<MemberRefTypePtr>& >(*this) = xmlNode.Children<MemberRefType>( "member" );
    }

    CompoundDefType::CompoundDefType( const XmlNode& xmlNode )
    {
        id_ = DecodeHtml( xmlNode.Read<std::string>( "id" ) );
        kind_ = xmlNode.Read<DoxCompoundKind>( "kind" );
        
        language_ = xmlNode.Read<DoxLanguage>( "language" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );

        final_ = xmlNode.Read<bool>( "final" );
        inline_ = xmlNode.Read<bool>( "inline" );
        sealed_ = xmlNode.Read<bool>( "sealed" );
        abstract_ = xmlNode.Read<bool>( "abstract" );

        compoundName_ = DecodeHtml( xmlNode.Child<std::string>( "compoundname" ) );
        title_ = DecodeHtml( xmlNode.Child<std::string>( "title" ) );
        baseCompoundRef_ = xmlNode.Children<CompoundRefType>( "basecompoundref" );

        derivedCompoundRef_ = xmlNode.Children<CompoundRefType>( "derivedcompoundref" );
        includes_ = xmlNode.Children<IncType>( "includes" );
        includedBy_ = xmlNode.Children<IncType>( "includedby" );
        incDepGraph_ = xmlNode.Child<GraphType>( "incdepgraph" );
        invIncDepGraph_ = xmlNode.Child<GraphType>( "invincdepgraph" );
        innerModule_ = xmlNode.Children<RefType>( "innermodule" );
        innerDir_ = xmlNode.Children<RefType>( "innerdir" );
        innerFile_ = xmlNode.Children<RefType>( "innerfile" );
        innerClass_ = xmlNode.Children<RefType>( "innerclass" );
        innerConcept_ = xmlNode.Children<RefType>( "innerconcept" );
        innerNamespace_ = xmlNode.Children<RefType>( "innernamespace" );
        innerPage_ = xmlNode.Children<RefType>( "innerpage" );
        innerGroup_ = xmlNode.Children<RefType>( "innergroup" );
        qualifier_ = xmlNode.Children<std::string>( "qualifier" );
        templateParamList_ = xmlNode.Child<TemplateParamListType>( "templateparamlist" );
        sectiondef_ = xmlNode.Children<SectionDefType>( "sectiondef" );
        tableOfContents_ = xmlNode.Child<TableOfContentsType>( "tableofcontents" );
        requiresClause_ = xmlNode.Child<LinkedTextType>( "requiresclause" );
        initializer_ = xmlNode.Child<LinkedTextType>( "initializer" );
        briefDescription_ = xmlNode.Child<DescriptionType>( "briefdescription" );
        detailedDescription_ = xmlNode.Child<DescriptionType>( "detaileddescription" );
        exports_ = xmlNode.Child<ExportsType>( "exports" );
        inheritanceGraph_ = xmlNode.Child<GraphType>( "inheritancegraph" );
        collaborationGraph_ = xmlNode.Child<GraphType>( "collaborationgraph" );
        programListing_ = xmlNode.Child<ListingType>( "programlisting" );
        location_ = xmlNode.Child<LocationType>( "location" );
        listOfAllMembers_ = xmlNode.Child<ListOfAllMembersType>( "listofallmembers" );
        
    }

    Document::Document( const std::wstring& name, const XmlNode& xmlNode )
        : name_( name )
    {
        auto childNode = xmlNode.FirstNode( "compounddef" );
        if ( childNode )
        {
            do
            {
                auto compoundDef = std::make_shared<CompoundDefType>( childNode );
                emplace_back( compoundDef );

                childNode = childNode.NextSibling( "compounddef" );
            } while ( childNode );
        }
    }

    DocumentCollection::DocumentCollection( )
    {

    }

    void DocumentCollection::AddDirectory( const std::wstring& directoryName )
    {
        IO::FileSystemEntries<std::wstring> fileSystemEntries( directoryName, L"*.xml" );
        while ( fileSystemEntries.Read( ) )
        {
            if ( fileSystemEntries.IsDirectory( ) == false )
            {
                auto fullPath = fileSystemEntries.FullPath( );
                AddFile( fullPath );
            }
        }
    }
    void DocumentCollection::AddFile( const std::wstring& path )
    {
        std::string xml;
        IO::File::ReadAndAppendAllTextTo( path, xml );

        if ( xml.size() )
        {
            RapidXml::XmlParser xmlParser;
            char* xmlText = xml.data( );
            xmlParser.Parse<RapidXml::ParsingFlags::NonDestructive>( xmlText );

            auto xmlDocument = xmlParser.Document( );

            auto xmlNode = xmlDocument.FirstNode( "doxygen" );
            if ( xmlNode )
            {
                IO::SplitPath<std::wstring> splitPath( path );
                auto name = splitPath.Name( );

                auto document = std::make_shared<Document>( name, xmlNode );

                emplace( name, document );
            }
        }
    }

    std::unique_ptr<Structure::TypeSystem> DocumentCollection::TypeSystem( ) const
    {
        auto result = std::make_unique<Structure::TypeSystem>( );
        result->Process( *this );
        return result;
    }

}

