/*
   Copyright 2024 Espen Harlinn

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
    using XmlNodeType = RapidXml::NodeType;

    DocEmojiType::DocEmojiType( const XmlNode& xmlNode )
    {
        name_ = xmlNode.Read<WideString>( "name" );
        unicode_ = xmlNode.Read<WideString>( "unicode" );
    }

    TableOfContentsKindType::TableOfContentsKindType( const XmlNode& xmlNode )
    {
        /*
        name_ = xmlNode.Read<WideString>( L"name" );
        reference_ = xmlNode.Read<WideString>( L"reference" );
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

    }

    DocBlockQuoteType::DocBlockQuoteType( const XmlNode& xmlNode )
    {

    }

    DocDetailsType::DocDetailsType( const XmlNode& xmlNode )
    {

    }

    DocCopyType::DocCopyType( const XmlNode& xmlNode )
    {

    }

    DocXRefSectType::DocXRefSectType( const XmlNode& xmlNode )
    {

    }

    DocParamName::DocParamName( const XmlNode& xmlNode )
    {

    }

    DocParamType::DocParamType( const XmlNode& xmlNode )
    {

    }

    DocParamNameList::DocParamNameList( const XmlNode& xmlNode )
    {

    }

    DocParamListItem::DocParamListItem( const XmlNode& xmlNode )
    {

    }

    DocParamListType::DocParamListType( const XmlNode& xmlNode )
    {

    }

    DocLanguageType::DocLanguageType( const XmlNode& xmlNode )
    {

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

    }

    DocCaptionType::DocCaptionType( const XmlNode& xmlNode )
    {

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

    }

    DocVariableListType::DocVariableListType( const XmlNode& xmlNode )
    {

    }

    DocVariableListGroup::DocVariableListGroup( const XmlNode& xmlNode )
    {

    }

    DocVarListEntryType::DocVarListEntryType( const XmlNode& xmlNode )
    {

    }

    DocSimpleSectType::DocSimpleSectType( const XmlNode& xmlNode )
    {

    }

    DocListItemType::DocListItemType( const XmlNode& xmlNode )
    {

    }

    DocListType::DocListType( const XmlNode& xmlNode )
    {

    }

    DocIndexEntryType::DocIndexEntryType( const XmlNode& xmlNode )
    {

    }

    DocFormulaType::DocFormulaType( const XmlNode& xmlNode )
    {

    }

    DocAnchorType::DocAnchorType( const XmlNode& xmlNode )
    {

    }

    DocURLLink::DocURLLink( const XmlNode& xmlNode )
    {

    }

    DocMarkupType::DocMarkupType( const XmlNode& xmlNode )
    {

    }

    DocParaType::DocParaType( const XmlNode& xmlNode )
    {

    }

    DocCmdGroup::DocCmdGroup( const XmlNode& xmlNode )
    {

    }

    DocSummaryType::DocSummaryType( const XmlNode& xmlNode )
    {

    }

    DocTitleType::DocTitleType( const XmlNode& xmlNode )
    {

    }

    DocTitleCmdGroup::DocTitleCmdGroup( const XmlNode& xmlNode )
    {

    }

    DocInternalS6Type::DocInternalS6Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
    }

    DocInternalS5Type::DocInternalS5Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect6" );
    }

    DocInternalS4Type::DocInternalS4Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect5" );
    }

    DocInternalS3Type::DocInternalS3Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect4" );
    }

    DocInternalS2Type::DocInternalS2Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect3" );
    }

    DocInternalS1Type::DocInternalS1Type( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect2" );
    }

    DocInternalType::DocInternalType( const XmlNode& xmlNode )
    {
        ParaTypeVector para_ = xmlNode.Children<ParaType>( "para" );
        SubSectTypeVector sections_ = xmlNode.Children<SubSectType>( "sect1" );
    }

    DocSect6Type::DocSect6Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    DocSect5Type::DocSect5Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            constexpr std::string_view subSect( "sect6" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == subSect )
                {
                    SubSectTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<SubSectType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != subSect )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    DocSect4Type::DocSect4Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            constexpr std::string_view subSect( "sect5" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == subSect )
                {
                    SubSectTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<SubSectType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != subSect )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    DocSect3Type::DocSect3Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            constexpr std::string_view subSect( "sect4" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == subSect )
                {
                    SubSectTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<SubSectType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != subSect )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    DocSect2Type::DocSect2Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            constexpr std::string_view subSect( "sect3" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == subSect )
                {
                    SubSectTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<SubSectType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != subSect )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    DocSect1Type::DocSect1Type( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            constexpr std::string_view title( "title" );
            constexpr std::string_view para( "para" );
            constexpr std::string_view internal( "internal" );
            constexpr std::string_view subSect( "sect2" );
            do
            {
                auto name = child.Name( );
                if ( name == title )
                {
                    title_ = child.Content<WideString>( );
                    child = child.NextSibling( );
                }
                else if ( name == para )
                {
                    ParaTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<ParaType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != para )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == internal )
                {
                    InternalTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<InternalType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != internal )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else if ( name == subSect )
                {
                    SubSectTypeVector elements;
                    for ( ;;)
                    {
                        auto element = std::make_shared<SubSectType>( child );
                        elements.emplace_back( std::move( element ) );
                        child = child.NextSibling( );
                        if ( !child || child.Name( ) != subSect )
                        {
                            break;
                        }
                    }
                    contents_.emplace_back( std::move( elements ) );
                }
                else
                {
                    child = child.NextSibling( );
                }
            } while ( child );
        }
    }

    LocationType::LocationType( const XmlNode& xmlNode )
    {
        file_ = xmlNode.Read<WideString>( "file" );
        line_ = xmlNode.Read<Int32>( "line" );
        column_ = xmlNode.Read<Int32>( "column" );
        declFile_ = xmlNode.Read<WideString>( "declfile" );
        declLine_ = xmlNode.Read<Int32>( "declline" );
        declColumn_ = xmlNode.Read<Int32>( "declcolumn" );
        bodyFile_ = xmlNode.Read<WideString>( "bodyfile" );
        bodyStart_ = xmlNode.Read<Int32>( "bodystart" );
        bodyEnd_ = xmlNode.Read<Int32>( "bodyend" );
    }

    ReferenceType::ReferenceType( const XmlNode& xmlNode )
    {
        WideString refId_ = xmlNode.Read<WideString>( "refid" );
        WideString compoundRef_ = xmlNode.Read<WideString>( "compoundref" );
        Int32 startLine_ = xmlNode.Read<Int32>( "startline" );
        Int32 endline_ = xmlNode.Read<Int32>( "endline" );
    }

    /*
    SpType::SpType( const XmlNode& xmlNode )
    {

    }
    */

    HighlightType::HighlightType( const XmlNode& xmlNode )
    {
        class_ = xmlNode.Read<DoxHighlightClass>( "class" );
        static constexpr std::string_view sp( "sp" );
        static constexpr std::string_view ref( "ref" );
        auto child = xmlNode.FirstNode( );
        if ( child )
        {
            do
            {
                auto name = child.Name( );
                if ( name == sp )
                {
                    Int32 value = child.Read<Int32>( "value" );
                    items_.emplace_back( value );
                }
                else if ( name == ref )
                {
                    items_.emplace_back( std::make_shared<RefTextType>( child ) );
                }
                child = child.NextSibling( );
            } while ( child );
        }
    }

    CodeLineType::CodeLineType( const XmlNode& xmlNode )
    {
        lineno_ = xmlNode.Read<Int32>( "lineno" );
        refId_ = xmlNode.Read<WideString>( "refid" );
        refKind_ = xmlNode.Read<DoxRefKind>( "refkind" );
        external_ = xmlNode.Read<bool>( "external" );
        highlight_ = xmlNode.Children<HighlightType>( "highlight" );
    }

    ListingType::ListingType( const XmlNode& xmlNode )
    {
        fileName_ = xmlNode.Read<WideString>( "refid" );
        static_cast< std::vector<CodeLineTypePtr>& >( *this ) = xmlNode.Children<CodeLineType>( "codeline" );
    }

    LinkType::LinkType( const XmlNode& xmlNode )
    {
        WideString refId_ = xmlNode.Read<WideString>( "refid" );
        WideString external_ = xmlNode.Read<WideString>( "external" );
    }

    ChildNodeType::ChildNodeType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        relation_ = xmlNode.Read<DoxGraphRelation>( "relation" );
        edgeLabel_ = xmlNode.Children<WideString>( "edgelabel" );
    }

    NodeType::NodeType( const XmlNode& xmlNode )
    {
        WideString id_ = xmlNode.Read<WideString>( "id" );
        WideString label_ = xmlNode.Child<WideString>( "label" );
        LinkTypePtr link_ = xmlNode.Child<LinkType>( "link" );
        std::vector<ChildNodeTypePtr> childNode_ = xmlNode.Children<ChildNodeType>( "childnode" );
    }

    GraphType::GraphType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<NodeTypePtr>& >( *this ) = xmlNode.Children<NodeType>( "node" );
    }

    LinkedTextType::LinkedTextType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<RefTextTypePtr>& >( *this ) = xmlNode.Children<RefTextType>( "ref" );
    }

    ParamType::ParamType( const XmlNode& xmlNode )
    {
        attributes_ = xmlNode.Child<WideString>( "attributes" );
        type_ = xmlNode.Child<LinkedTextType>( "type" );
        declName_ = xmlNode.Child<WideString>( "declname" );
        defName_ = xmlNode.Child<WideString>( "defname" );
        array_ = xmlNode.Child<WideString>( "array" );
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
        id_ = xmlNode.Read<WideString>( "id" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        name_ = xmlNode.Child<WideString>( "name" );
        initializer_ = xmlNode.Child<LinkedTextType>( "initializer" );
        briefDescription_ = xmlNode.Child<DescriptionType>( "briefdescription" );
        detailedDescription_ = xmlNode.Child<DescriptionType>( "detaileddescription" );
    }

    DescriptionType::DescriptionType( const XmlNode& xmlNode )
    {
        title_ = xmlNode.Child<WideString>( "title" );
        para_ = xmlNode.Children<DocParaType>( "para" );
        internal_ = xmlNode.Children<DocInternalType>( "internal" );
        sect1_ = xmlNode.Children<DocSect1Type>( "sect1" );
    }

    MemberDefType::MemberDefType( const XmlNode& xmlNode )
    {
        kind_ = xmlNode.Read<DoxMemberKind>( "kind" );
        id_ = xmlNode.Read<WideString>( "id" );
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
        noexceptExpression_ = xmlNode.Read<WideString>( "noexceptexpression" );
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
        definition_ = xmlNode.Child<WideString>( "definition" );
        argsString_ = xmlNode.Child<WideString>( "argsstring" );
        name_ = xmlNode.Child<WideString>( "name" );
        qualifiedName_ = xmlNode.Child<WideString>( "qualifiedname" );
        read_ = xmlNode.Child<WideString>( "read" );
        write_ = xmlNode.Child<WideString>( "write" );
        bitField_ = xmlNode.Child<WideString>( "bitfield" );
        reimplements_ = xmlNode.Children<ReimplementType>( "reimplements" );
        reimplementedBy_ = xmlNode.Children<ReimplementType>( "reimplementedby" );
        qualifier_ = xmlNode.Child<WideString>( "qualifier" );
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
        header_ = xmlNode.Child<WideString>( "header" );
        description_ = xmlNode.Child<DescriptionType>( "description" );
        memberDef_ = xmlNode.Children<MemberDefType>( "memberdef" );
        member_ = xmlNode.Children<MemberType>( "member" );
        kind_ = xmlNode.Read<DoxSectionKind>( "kind" );
    }

    MemberType::MemberType( const XmlNode& xmlNode )
    {
        name_ = xmlNode.Child<WideString>( "name" );
        refId_ = xmlNode.Read<WideString>( "refid" );
        kind_ = xmlNode.Read<MemberKind>( "kind" );
    }

    RefTextType::RefTextType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        kindRef_ = xmlNode.Read<DoxRefKind>( "kindref" );
        external_ = xmlNode.Read<WideString>( "external" );
        tooltip_ = xmlNode.Read<WideString>( "tooltip" );
        content_ = xmlNode.Content<WideString>( );
    }

    RefType::RefType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        inline_ = xmlNode.Read<bool>( "inline" );
        content_ = xmlNode.Content<WideString>( );
    }

    ExportType::ExportType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        content_ = xmlNode.Content<WideString>( );
    }

    ExportsType::ExportsType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<ExportTypePtr>& >( *this ) = xmlNode.Children<ExportType>( "export" );
    }

    IncType::IncType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        local_ = xmlNode.Read<bool>( "local" );
        content_ = xmlNode.Content<WideString>( );
    }

    ReimplementType::ReimplementType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        content_ = xmlNode.Content<WideString>( );
    }

    CompoundRefType::CompoundRefType( const XmlNode& xmlNode )
    {
        refId_ = xmlNode.Read<WideString>( "refid" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        virt_ = xmlNode.Read<DoxVirtualKind>( "virt" );
        content_ = xmlNode.Content<WideString>( );
    }

    DocHtmlOnlyType::DocHtmlOnlyType( const XmlNode& xmlNode )
    {
        block_ = xmlNode.Read<WideString>( "block" );
        content_ = xmlNode.Content<WideString>( );
    }

    MemberRefType::MemberRefType( const XmlNode& xmlNode )
    {
        name_ = xmlNode.Child<WideString>( "name" );
        scope_ = xmlNode.Child<WideString>( "scope" );
        refId_ = xmlNode.Read<WideString>( "refid" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );
        virt_ = xmlNode.Read<DoxVirtualKind>( "virt" );
        ambiguityScope_ = xmlNode.Read<WideString>( "ambiguityscope" );
    }

    ListOfAllMembersType::ListOfAllMembersType( const XmlNode& xmlNode )
    {
        static_cast< std::vector<MemberRefTypePtr>& >(*this) = xmlNode.Children<MemberRefType>( "member" );
    }

    CompoundDefType::CompoundDefType( const XmlNode& xmlNode )
    {
        id_ = xmlNode.Read<WideString>( "id" );
        kind_ = xmlNode.Read<DoxCompoundKind>( "kind" );
        
        language_ = xmlNode.Read<DoxLanguage>( "language" );
        prot_ = xmlNode.Read<DoxProtectionKind>( "prot" );

        final_ = xmlNode.Read<bool>( "final" );
        inline_ = xmlNode.Read<bool>( "inline" );
        sealed_ = xmlNode.Read<bool>( "sealed" );
        abstract_ = xmlNode.Read<bool>( "abstract" );

        compoundName_ = xmlNode.Child<WideString>( "compoundname" );
        title_ = xmlNode.Child<WideString>( "title" );
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
        qualifier_ = xmlNode.Children<WideString>( "qualifier" );
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

    Document::Document( const WideString& name, const XmlNode& xmlNode )
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

    void DocumentCollection::AddDirectory( const WideString& directoryName )
    {
        IO::FileSystemEntries<WideString> fileSystemEntries( directoryName, L"*.xml" );
        while ( fileSystemEntries.Read( ) )
        {
            if ( fileSystemEntries.IsDirectory( ) == false )
            {
                auto fullPath = fileSystemEntries.FullPath( );
                AddFile( fullPath );
            }
        }
    }
    void DocumentCollection::AddFile( const WideString& path )
    {
        AnsiString xml;
        IO::File::ReadAndAppendAllTextTo( path, xml );

        if ( xml.size() )
        {
            RapidXml::XmlDocument xmlDocument;
            char* xmlText = xml.data( );
            xmlDocument.Parse<RapidXml::ParsingFlags::NonDestructive>( xmlText );

            auto xmlNode = xmlDocument.FirstNode( "doxygen" );
            if ( xmlNode )
            {
                IO::SplitPath<WideString> splitPath( path );
                auto name = splitPath.Name( );

                auto document = std::make_shared<Document>( name, xmlNode );

                emplace( name, document );
            }
        }
    }

}
