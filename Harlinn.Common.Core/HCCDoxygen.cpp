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

namespace Harlinn::Common::Core::Doxygen
{
    DocEmojiType::DocEmojiType( const XmlElement& xmlElement )
    {
        name_ = xmlElement.Read<WideString>( L"name" );
        unicode_ = xmlElement.Read<WideString>( L"unicode" );
    }

    TableOfContentsKindType::TableOfContentsKindType( const XmlElement& xmlElement )
    {
        name_ = xmlElement.Read<WideString>( L"name" );
        reference_ = xmlElement.Read<WideString>( L"reference" );
        auto childNodes = xmlElement.ChildNodes( );
        for ( auto& childNode : childNodes )
        {
            if ( childNode.NodeType( ) == XmlNodeType::Element )
            {
                auto element = childNode.As<XmlElement>( );
                auto tagName = element.TagName( );
                if ( tagName == L"tableofcontents" )
                {
                    auto tableofcontents = std::make_shared<TableOfContentsType>( element );
                    Add( std::move( tableofcontents ) );
                }
            }
        }
    }

    TableOfContentsType::TableOfContentsType( const XmlElement& xmlElement )
    {

    }

    DocEmptyType::DocEmptyType( const XmlElement& xmlElement )
    {

    }

    DocParBlockType::DocParBlockType( const XmlElement& xmlElement )
    {

    }

    DocBlockQuoteType::DocBlockQuoteType( const XmlElement& xmlElement )
    {

    }

    DocDetailsType::DocDetailsType( const XmlElement& xmlElement )
    {

    }

    DocCopyType::DocCopyType( const XmlElement& xmlElement )
    {

    }

    DocXRefSectType::DocXRefSectType( const XmlElement& xmlElement )
    {

    }

    DocParamName::DocParamName( const XmlElement& xmlElement )
    {

    }

    DocParamType::DocParamType( const XmlElement& xmlElement )
    {

    }

    DocParamNameList::DocParamNameList( const XmlElement& xmlElement )
    {

    }

    DocParamListItem::DocParamListItem( const XmlElement& xmlElement )
    {

    }

    DocParamListType::DocParamListType( const XmlElement& xmlElement )
    {

    }

    DocLanguageType::DocLanguageType( const XmlElement& xmlElement )
    {

    }

    DocTocListType::DocTocListType( const XmlElement& xmlElement )
    {

    }

    DocTocItemType::DocTocItemType( const XmlElement& xmlElement )
    {

    }

    DocPlantumlType::DocPlantumlType( const XmlElement& xmlElement )
    {

    }

    DocImageFileType::DocImageFileType( const XmlElement& xmlElement )
    {

    }

    DocDotMscType::DocDotMscType( const XmlElement& xmlElement )
    {

    }

    DocImageType::DocImageType( const XmlElement& xmlElement )
    {

    }

    DocHeadingType::DocHeadingType( const XmlElement& xmlElement )
    {

    }

    DocCaptionType::DocCaptionType( const XmlElement& xmlElement )
    {

    }

    DocEntryType::DocEntryType( const XmlElement& xmlElement )
    {

    }

    DocRowType::DocRowType( const XmlElement& xmlElement )
    {

    }

    DocTableType::DocTableType( const XmlElement& xmlElement )
    {

    }

    DocRefTextType::DocRefTextType( const XmlElement& xmlElement )
    {

    }

    DocVariableListType::DocVariableListType( const XmlElement& xmlElement )
    {

    }

    DocVariableListGroup::DocVariableListGroup( const XmlElement& xmlElement )
    {

    }

    DocVarListEntryType::DocVarListEntryType( const XmlElement& xmlElement )
    {

    }

    DocSimpleSectType::DocSimpleSectType( const XmlElement& xmlElement )
    {

    }

    DocListItemType::DocListItemType( const XmlElement& xmlElement )
    {

    }

    DocListType::DocListType( const XmlElement& xmlElement )
    {

    }

    DocIndexEntryType::DocIndexEntryType( const XmlElement& xmlElement )
    {

    }

    DocFormulaType::DocFormulaType( const XmlElement& xmlElement )
    {

    }

    DocAnchorType::DocAnchorType( const XmlElement& xmlElement )
    {

    }

    DocURLLink::DocURLLink( const XmlElement& xmlElement )
    {

    }

    DocMarkupType::DocMarkupType( const XmlElement& xmlElement )
    {

    }

    DocParaType::DocParaType( const XmlElement& xmlElement )
    {

    }

    DocCmdGroup::DocCmdGroup( const XmlElement& xmlElement )
    {

    }

    DocSummaryType::DocSummaryType( const XmlElement& xmlElement )
    {

    }

    DocTitleType::DocTitleType( const XmlElement& xmlElement )
    {

    }

    DocTitleCmdGroup::DocTitleCmdGroup( const XmlElement& xmlElement )
    {

    }

    DocInternalS6Type::DocInternalS6Type( const XmlElement& xmlElement )
    {

    }

    DocInternalS5Type::DocInternalS5Type( const XmlElement& xmlElement )
    {

    }

    DocInternalS4Type::DocInternalS4Type( const XmlElement& xmlElement )
    {

    }

    DocInternalS3Type::DocInternalS3Type( const XmlElement& xmlElement )
    {

    }

    DocInternalS2Type::DocInternalS2Type( const XmlElement& xmlElement )
    {

    }

    DocInternalS1Type::DocInternalS1Type( const XmlElement& xmlElement )
    {

    }

    DocInternalType::DocInternalType( const XmlElement& xmlElement )
    {

    }

    DocSect6Type::DocSect6Type( const XmlElement& xmlElement )
    {

    }

    DocSect5Type::DocSect5Type( const XmlElement& xmlElement )
    {

    }

    DocSect4Type::DocSect4Type( const XmlElement& xmlElement )
    {

    }

    DocSect3Type::DocSect3Type( const XmlElement& xmlElement )
    {

    }

    DocSect2Type::DocSect2Type( const XmlElement& xmlElement )
    {

    }

    DocSect1Type::DocSect1Type( const XmlElement& xmlElement )
    {

    }

    LocationType::LocationType( const XmlElement& xmlElement )
    {

    }

    ReferenceType::ReferenceType( const XmlElement& xmlElement )
    {

    }

    SpType::SpType( const XmlElement& xmlElement )
    {

    }

    HighlightType::HighlightType( const XmlElement& xmlElement )
    {

    }

    CodeLineType::CodeLineType( const XmlElement& xmlElement )
    {

    }

    ListingType::ListingType( const XmlElement& xmlElement )
    {

    }

    LinkType::LinkType( const XmlElement& xmlElement )
    {

    }

    ChildNodeType::ChildNodeType( const XmlElement& xmlElement )
    {

    }

    NodeType::NodeType( const XmlElement& xmlElement )
    {

    }

    GraphType::GraphType( const XmlElement& xmlElement )
    {

    }

    LinkedTextType::LinkedTextType( const XmlElement& xmlElement )
    {

    }

    ParamType::ParamType( const XmlElement& xmlElement )
    {

    }

    TemplateParamListType::TemplateParamListType( const XmlElement& xmlElement )
    {

    }

    EnumvalueType::EnumvalueType( const XmlElement& xmlElement )
    {

    }

    DescriptionType::DescriptionType( const XmlElement& xmlElement )
    {

    }

    MemberDefType::MemberDefType( const XmlElement& xmlElement )
    {

    }

    SectionDefType::SectionDefType( const XmlElement& xmlElement )
    {

    }

    MemberType::MemberType( const XmlElement& xmlElement )
    {

    }

    RefTextType::RefTextType( const XmlElement& xmlElement )
    {

    }

    RefType::RefType( const XmlElement& xmlElement )
    {

    }

    ExportType::ExportType( const XmlElement& xmlElement )
    {

    }

    ExportsType::ExportsType( const XmlElement& xmlElement )
    {

    }

    IncType::IncType( const XmlElement& xmlElement )
    {

    }

    ReimplementType::ReimplementType( const XmlElement& xmlElement )
    {

    }

    CompoundRefType::CompoundRefType( const XmlElement& xmlElement )
    {

    }

    DocHtmlOnlyType::DocHtmlOnlyType( const XmlElement& xmlElement )
    {

    }

    MemberRefType::MemberRefType( const XmlElement& xmlElement )
    {

    }

    ListOfAllMembersType::ListOfAllMembersType( const XmlElement& xmlElement )
    {

    }

    CompoundDefType::CompoundDefType( const XmlElement& xmlElement )
    {

    }

    Document::Document( const XmlElement& xmlElement )
    {

    }

    DocumentCollection::DocumentCollection( const XmlElement& xmlElement )
    {

    }

}
