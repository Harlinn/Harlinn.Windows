#pragma once
#ifndef HCCDOXYGEN_H_
#define HCCDOXYGEN_H_

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

/*
 * Parses doxygen xml output 
 */

#include <HCCString.h>

namespace Harlinn::Common::Core::RapidXml
{
    template<typename Ch = char>
    class XmlAttribute;
    template<typename Ch = char>
    class XmlNode;
    template<typename Ch = char>
    class XmlDocument;
}

namespace Harlinn::Common::Core::Doxygen
{
    

    enum class MemberKind
    {
        Unknown,
        Define,
        Property,
        Event,
        Variable,
        Typedef,
        Enum,
        Enumvalue,
        Function,
        Signal,
        Prototype,
        Friend,
        DCop,
        Slot
    };

    using DoxBool = bool;

    enum class DoxGraphRelation
    {
        Unknown,
        Include,
        Usage,
        TemplateInstance,
        PublicInheritance,
        ProtectedInheritance,
        PrivateInheritance,
        TypeConstraint
    };

    enum class DoxRefKind
    {
        Unknown,
        Compound,
        Member
    };

    enum class DoxMemberKind
    {
        Unknown,
        Define,
        Property,
        Event,
        Variable,
        Typedef,
        Enum,
        Function,
        Signal,
        Prototype,
        Friend,
        DCop,
        Slot,
        Interface,
        Service
    };

    enum class DoxProtectionKind
    {
        Unknown,
        Public,
        Protected,
        Private,
        Package
    };


    enum class DoxRefQualifierKind
    {
        Unknown,
        LValue,
        RValue
    };

    enum class DoxLanguage
    {
        Unknown,
        IDL,
        Java,
        CSharp,
        D,
        PHP,
        ObjectiveC,
        Cpp,
        JavaScript,
        Python,
        Fortran,
        VHDL,
        XML,
        SQL,
        Markdown,
        Slice,
        Lex
    };

    enum class DoxVirtualKind
    {
        Unknown,
        NonVirtual,
        Virtual,
        PureVirtual
    };

    enum class DoxCompoundKind
    {
        Unknown,
        Class,
        Struct,
        Union,
        Interface,
        Protocol,
        Category,
        Exception,
        Service,
        Singleton,
        Module,
        Type,
        File,
        Namespace,
        Group,
        Page,
        Example,
        Dir,
        Concept
    };

    enum class DoxSectionKind
    {
        UserDefined,
        PublicType,
        PublicFunc,
        PublicAttrib,
        PublicSlot,
        Signal,
        DcopFunc,
        Property,
        Event,
        PublicStaticFunc,
        PublicStaticAttrib,
        ProtectedType,
        ProtectedFunc,
        ProtectedAttrib,
        ProtectedSlot,
        ProtectedStaticFunc,
        ProtectedStaticAttrib,
        PackageType,
        PackageFunc,
        PackageAttrib,
        PackageStaticFunc,
        PackageStaticAttrib,
        PrivateType,
        PrivateFunc,
        PrivateAttrib,
        PrivateSlot,
        PrivateStaticFunc,
        PrivateStaticAttrib,
        Friend,
        Related,
        Define,
        Prototype,
        Typedef,
        Enum,
        Func,
        Var
    };


    enum class DoxHighlightClass
    {
        Comment,
        Normal,
        Preprocessor,
        Keyword,
        KeywordType,
        KeywordFlow,
        StringLiteral,
        XmlCData,
        CharLiteral,
        VhdlKeyword,
        VhdlLogic,
        VhdlChar,
        VhdlDigit
    };

    enum class DoxSimpleSectKind
    {
        See,
        Return,
        Author,
        Authors,
        Version,
        Since,
        Date,
        Note,
        Warning,
        Pre,
        Post,
        Copyright,
        Invariant,
        Remark,
        Attention,
        Important,
        Par,
        Rcs
    };

    enum class DoxCheck
    {
        Checked,
        Unchecked
    };

    using DoxVersionNumber = WideString;

    enum class DoxImageKind
    {
        Html,
        Latex,
        Docbook,
        Rtf,
        Xml
    };

    enum class DoxPlantumlEngine
    {
        Uml,
        Bpm,
        Wire,
        Dot,
        Ditaa,
        Salt,
        Math,
        Latex,
        Gantt,
        Mindmap,
        Wbs,
        Yaml,
        Creole,
        Json,
        Flow,
        Board,
        Git,
        Hcl,
        Regex,
        Ebnf,
        Files
    };

    enum class DoxParamListKind
    {
        Param,
        Retval,
        Exception,
        TemplateParam
    };

    enum DoxParamDir
    {
        In,
        Out,
        InOut
    };

    enum class DoxAccessor
    {
        Retain,
        Copy,
        Assign,
        Weak,
        Strong,
        Unretained
    };

    enum class DoxAlign
    {
        Left,
        Right,
        Center
    };

    enum class DoxVerticalAlign
    {
        Bottom,
        Top,
        Middle
    };

    enum class DoxOlType
    {
        Numbered,
        a,
        A,
        i,
        I
    };


    enum class DoxType
    {
        Unknown,
        DocEmojiType,
        TableOfContentsKindType,
        TableOfContentsType,
        DocEmptyType,
        DocParBlockType,
        DocBlockQuoteType,
        DocDetailsType,
        DocCopyType,
        DocXRefSectType,
        DocParamName,
        DocParamType,
        DocParamNameList,
        DocParamListItem,
        DocParamListType,
        DocLanguageType,
        DocTocListType,
        DocTocItemType,
        DocPlantumlType,
        DocImageFileType,
        DocDotMscType,
        DocImageType,
        DocHeadingType,
        DocCaptionType,
        DocEntryType,
        DocRowType,
        DocTableType,
        DocRefTextType,
        DocVariableListType,
        DocVariableListGroup,
        DocVarListEntryType,
        DocSimpleSectType,
        DocListItemType,
        DocListType,
        DocIndexEntryType,
        DocFormulaType,
        DocAnchorType,
        DocURLLink,
        DocMarkupType,
        DocParaType,
        DocCmdGroup,
        DocSummaryType,
        DocTitleType,
        DocTitleCmdGroup,
        DocInternalS6Type,
        DocInternalS5Type,
        DocInternalS4Type,
        DocInternalS3Type,
        DocInternalS2Type,
        DocInternalS1Type,
        DocInternalType,
        DocSect6Type,
        DocSect5Type,
        DocSect4Type,
        DocSect3Type,
        DocSect2Type,
        DocSect1Type,
        LocationType,
        ReferenceType,
        SpType,
        HighlightType,
        CodeLineType,
        ListingType,
        LinkType,
        ChildNodeType,
        NodeType,
        GraphType,
        LinkedTextType,
        ParamType,
        TemplateParamListType,
        EnumvalueType,
        DescriptionType,
        MemberDefType,
        SectionDefType,
        MemberType,
        RefTextType,
        RefType,
        ExportType,
        ExportsType,
        IncType,
        ReimplementType,
        CompoundRefType,
        DocHtmlOnlyType,
        MemberRefType,
        ListOfAllMembersType,
        CompoundDefType,
        Document,
        DocumentCollection
    };


    /////////////////////////////////
     
    class DocEmojiType;
    class TableOfContentsKindType;
    class TableOfContentsType;
    class DocEmptyType;
    class DocParBlockType;
    class DocBlockQuoteType;
    class DocDetailsType;
    class DocCopyType;
    class DocXRefSectType;
    class DocParamName;
    class DocParamType;
    class DocParamNameList;
    class DocParamListItem;
    class DocParamListType;
    class DocLanguageType;
    class DocTocListType;
    class DocTocItemType;
    class DocPlantumlType;
    class DocImageFileType;
    class DocDotMscType;
    class DocImageType;
    class DocHeadingType;
    class DocCaptionType;
    class DocEntryType;
    class DocRowType;
    class DocTableType;
    class DocRefTextType;
    class DocVariableListType;
    class DocVariableListGroup;
    class DocVarListEntryType;
    class DocSimpleSectType;
    class DocListItemType;
    class DocListType;
    class DocIndexEntryType;
    class DocFormulaType;
    class DocAnchorType;
    class DocURLLink;
    class DocMarkupType;
    class DocParaType;
    class DocCmdGroup;
    class DocSummaryType;
    class DocTitleType;
    class DocTitleCmdGroup;
    class DocInternalS6Type;
    class DocInternalS5Type;
    class DocInternalS4Type;
    class DocInternalS3Type;
    class DocInternalS2Type;
    class DocInternalS1Type;
    class DocInternalType;
    class DocSect6Type;
    class DocSect5Type;
    class DocSect4Type;
    class DocSect3Type;
    class DocSect2Type;
    class DocSect1Type;
    class LocationType;
    class ReferenceType;
    //class SpType;
    class HighlightType;
    class CodeLineType;
    class ListingType;
    class LinkType;
    class ChildNodeType;
    class NodeType;
    class GraphType;
    class LinkedTextType;
    class ParamType;
    class TemplateParamListType;
    class EnumvalueType;
    class DescriptionType;
    class MemberDefType;
    class SectionDefType;
    class MemberType;
    class RefTextType;
    class RefType;
    class ExportType;
    class ExportsType;
    class IncType;
    class ReimplementType;
    class CompoundRefType;
    class DocHtmlOnlyType;
    class MemberRefType;
    class ListOfAllMembersType;
    class CompoundDefType;
    class Document;
    class DocumentCollection;

    using DocEmojiTypePtr = std::shared_ptr<DocEmojiType>;
    using TableOfContentsKindTypePtr = std::shared_ptr<TableOfContentsKindType>;
    using TableOfContentsTypePtr = std::shared_ptr<TableOfContentsType>;
    using DocEmptyTypePtr = std::shared_ptr<DocEmptyType>;
    using DocParBlockTypePtr = std::shared_ptr<DocParBlockType>;
    using DocBlockQuoteTypePtr = std::shared_ptr<DocBlockQuoteType>;
    using DocDetailsTypePtr = std::shared_ptr<DocDetailsType>;
    using DocCopyTypePtr = std::shared_ptr<DocCopyType>;
    using DocXRefSectTypePtr = std::shared_ptr<DocXRefSectType>;
    using DocParamNamePtr = std::shared_ptr<DocParamName>;
    using DocParamTypePtr = std::shared_ptr<DocParamType>;
    using DocParamNameListPtr = std::shared_ptr<DocParamNameList>;
    using DocParamListItemPtr = std::shared_ptr<DocParamListItem>;
    using DocParamListTypePtr = std::shared_ptr<DocParamListType>;
    using DocLanguageTypePtr = std::shared_ptr<DocLanguageType>;
    using DocTocListTypePtr = std::shared_ptr<DocTocListType>;
    using DocTocItemTypePtr = std::shared_ptr<DocTocItemType>;
    using DocPlantumlTypePtr = std::shared_ptr<DocPlantumlType>;
    using DocImageFileTypePtr = std::shared_ptr<DocImageFileType>;
    using DocDotMscTypePtr = std::shared_ptr<DocDotMscType>;
    using DocImageTypePtr = std::shared_ptr<DocImageType>;
    using DocHeadingTypePtr = std::shared_ptr<DocHeadingType>;
    using DocCaptionTypePtr = std::shared_ptr<DocCaptionType>;
    using DocEntryTypePtr = std::shared_ptr<DocEntryType>;
    using DocRowTypePtr = std::shared_ptr<DocRowType>;
    using DocTableTypePtr = std::shared_ptr<DocTableType>;
    using DocRefTextTypePtr = std::shared_ptr<DocRefTextType>;
    using DocVariableListTypePtr = std::shared_ptr<DocVariableListType>;
    using DocVariableListGroupPtr = std::shared_ptr<DocVariableListGroup>;
    using DocVarListEntryTypePtr = std::shared_ptr<DocVarListEntryType>;
    using DocSimpleSectTypePtr = std::shared_ptr<DocSimpleSectType>;
    using DocListItemTypePtr = std::shared_ptr<DocListItemType>;
    using DocListTypePtr = std::shared_ptr<DocListType>;
    using DocIndexEntryTypePtr = std::shared_ptr<DocIndexEntryType>;
    using DocFormulaTypePtr = std::shared_ptr<DocFormulaType>;
    using DocAnchorTypePtr = std::shared_ptr<DocAnchorType>;
    using DocURLLinkPtr = std::shared_ptr<DocURLLink>;
    using DocMarkupTypePtr = std::shared_ptr<DocMarkupType>;
    using DocParaTypePtr = std::shared_ptr<DocParaType>;
    using DocCmdGroupPtr = std::shared_ptr<DocCmdGroup>;
    using DocSummaryTypePtr = std::shared_ptr<DocSummaryType>;
    using DocTitleTypePtr = std::shared_ptr<DocTitleType>;
    using DocTitleCmdGroupPtr = std::shared_ptr<DocTitleCmdGroup>;
    using DocInternalS6TypePtr = std::shared_ptr<DocInternalS6Type>;
    using DocInternalS5TypePtr = std::shared_ptr<DocInternalS5Type>;
    using DocInternalS4TypePtr = std::shared_ptr<DocInternalS4Type>;
    using DocInternalS3TypePtr = std::shared_ptr<DocInternalS3Type>;
    using DocInternalS2TypePtr = std::shared_ptr<DocInternalS2Type>;
    using DocInternalS1TypePtr = std::shared_ptr<DocInternalS1Type>;
    using DocInternalTypePtr = std::shared_ptr<DocInternalType>;
    using DocSect6TypePtr = std::shared_ptr<DocSect6Type>;
    using DocSect5TypePtr = std::shared_ptr<DocSect5Type>;
    using DocSect4TypePtr = std::shared_ptr<DocSect4Type>;
    using DocSect3TypePtr = std::shared_ptr<DocSect3Type>;
    using DocSect2TypePtr = std::shared_ptr<DocSect2Type>;
    using DocSect1TypePtr = std::shared_ptr<DocSect1Type>;
    using LocationTypePtr = std::shared_ptr<LocationType>;
    using ReferenceTypePtr = std::shared_ptr<ReferenceType>;
    //using SpTypePtr = std::shared_ptr<SpType>;
    using HighlightTypePtr = std::shared_ptr<HighlightType>;
    using CodeLineTypePtr = std::shared_ptr<CodeLineType>;
    using ListingTypePtr = std::shared_ptr<ListingType>;
    using LinkTypePtr = std::shared_ptr<LinkType>;
    using ChildNodeTypePtr = std::shared_ptr<ChildNodeType>;
    using NodeTypePtr = std::shared_ptr<NodeType>;
    using GraphTypePtr = std::shared_ptr<GraphType>;
    using LinkedTextTypePtr = std::shared_ptr<LinkedTextType>;
    using ParamTypePtr = std::shared_ptr<ParamType>;
    using TemplateParamListTypePtr = std::shared_ptr<TemplateParamListType>;
    using EnumvalueTypePtr = std::shared_ptr<EnumvalueType>;
    using DescriptionTypePtr = std::shared_ptr<DescriptionType>;
    using MemberDefTypePtr = std::shared_ptr<MemberDefType>;
    using SectionDefTypePtr = std::shared_ptr<SectionDefType>;
    using MemberTypePtr = std::shared_ptr<MemberType>;
    using RefTextTypePtr = std::shared_ptr<RefTextType>;
    using RefTypePtr = std::shared_ptr<RefType>;
    using ExportTypePtr = std::shared_ptr<ExportType>;
    using ExportsTypePtr = std::shared_ptr<ExportsType>;
    using IncTypePtr = std::shared_ptr<IncType>;
    using ReimplementTypePtr = std::shared_ptr<ReimplementType>;
    using CompoundRefTypePtr = std::shared_ptr<CompoundRefType>;
    using DocHtmlOnlyTypePtr = std::shared_ptr<DocHtmlOnlyType>;
    using MemberRefTypePtr = std::shared_ptr<MemberRefType>;
    using ListOfAllMembersTypePtr = std::shared_ptr<ListOfAllMembersType>;
    using CompoundDefTypePtr = std::shared_ptr<CompoundDefType>;
    using DocumentPtr = std::shared_ptr<Document>;

    /////////////////////////////////


    class DocBaseType : std::enable_shared_from_this<DocBaseType>
    {
    public:
        using XmlNode = RapidXml::XmlNode<>;
        
        virtual ~DocBaseType( ) = default;
        virtual Doxygen::DoxType DoxType( ) const = 0;

    };

    namespace Internal
    {

        template<Doxygen::DoxType doxType>
        class DocBase : public DocBaseType
        {
        public:
            static constexpr Doxygen::DoxType DOXTYPE = doxType;

            virtual Doxygen::DoxType DoxType( ) const override
            {
                return DOXTYPE;
            }
        };
    }



    class DocEmojiType : public Internal::DocBase<Doxygen::DoxType::DocEmojiType>
    {
        WideString name_;
        WideString unicode_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocEmojiType>;
        DocEmojiType( ) = default;
        HCC_EXPORT explicit DocEmojiType( const XmlNode& xmlNode );

        const WideString& Name( ) const
        {
            return name_;
        }
        const WideString& Unicode( ) const
        {
            return unicode_;
        }

    };

    class TableOfContentsKindType : public Internal::DocBase<Doxygen::DoxType::TableOfContentsKindType>
    {
        WideString name_;
        WideString reference_;
        std::vector<std::shared_ptr<TableOfContentsType>> tableOfContents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TableOfContentsKindType>;
        TableOfContentsKindType( ) = default;
        HCC_EXPORT explicit TableOfContentsKindType( const XmlNode& xmlNode );


        const WideString& Name( ) const
        {
            return name_;
        }

        const WideString& Reference( ) const
        {
            return reference_;
        }
        const std::vector<std::shared_ptr<TableOfContentsType>>& TableOfContents( ) const
        {
            return tableOfContents_;
        }

        void Add( std::shared_ptr<TableOfContentsType>&& tableOfContents )
        {
            tableOfContents_.emplace_back( std::move(tableOfContents) );
        }
        void Add( const std::shared_ptr<TableOfContentsType>& tableOfContents )
        {
            tableOfContents_.emplace_back( tableOfContents );
        }

    };


    class TableOfContentsType : public Internal::DocBase<Doxygen::DoxType::TableOfContentsType>
    {
        std::vector<std::shared_ptr<TableOfContentsKindType>> tocSect_;
        std::vector<std::shared_ptr<TableOfContentsType>> tableOfContents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TableOfContentsType>;

        TableOfContentsType( ) = default;
        HCC_EXPORT explicit TableOfContentsType( const XmlNode& xmlNode );

        const std::vector<std::shared_ptr<TableOfContentsKindType>>& TocSect( ) const
        {
            return tocSect_;
        }

        void Add( std::shared_ptr<TableOfContentsKindType>&& tocSect )
        {
            tocSect_.emplace_back( std::move( tocSect ) );
        }
        void Add( const std::shared_ptr<TableOfContentsKindType>& tocSect )
        {
            tocSect_.emplace_back( tocSect );
        }

        const std::vector<std::shared_ptr<TableOfContentsType>>& TableOfContents( )
        {
            return tableOfContents_;
        }

        void Add( std::shared_ptr<TableOfContentsType>&& tableOfContents )
        {
            tableOfContents_.emplace_back( std::move( tableOfContents ) );
        }
        void Add( const std::shared_ptr<TableOfContentsType>& tableOfContents )
        {
            tableOfContents_.emplace_back( tableOfContents );
        }

    };


    class DocEmptyType : public Internal::DocBase<Doxygen::DoxType::DocEmptyType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocEmptyType>;

        DocEmptyType( ) = default;
        HCC_EXPORT explicit DocEmptyType( const XmlNode& xmlNode );
    };

    class DocParBlockType : public Internal::DocBase<Doxygen::DoxType::DocParBlockType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParBlockType>;

        DocParBlockType( ) = default;
        HCC_EXPORT explicit DocParBlockType( const XmlNode& xmlNode );
    };

    class DocBlockQuoteType : public Internal::DocBase<Doxygen::DoxType::DocBlockQuoteType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocBlockQuoteType>;

        DocBlockQuoteType( ) = default;
        HCC_EXPORT explicit DocBlockQuoteType( const XmlNode& xmlNode );
    };

    class DocDetailsType : public Internal::DocBase<Doxygen::DoxType::DocDetailsType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocDetailsType>;

        DocDetailsType( ) = default;
        HCC_EXPORT explicit DocDetailsType( const XmlNode& xmlNode );

    };


    class DocCopyType : public Internal::DocBase<Doxygen::DoxType::DocCopyType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCopyType>;

        DocCopyType( ) = default;
        HCC_EXPORT explicit DocCopyType( const XmlNode& xmlNode );

    };

    class DocXRefSectType : public Internal::DocBase<Doxygen::DoxType::DocXRefSectType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocXRefSectType>;

        DocXRefSectType( ) = default;
        HCC_EXPORT explicit DocXRefSectType( const XmlNode& xmlNode );

    };

    class DocParamName : public Internal::DocBase<Doxygen::DoxType::DocParamName>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamName>;

        DocParamName( ) = default;
        HCC_EXPORT explicit DocParamName( const XmlNode& xmlNode );
    };

    class DocParamType : public Internal::DocBase<Doxygen::DoxType::DocParamType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamType>;

        DocParamType( ) = default;
        HCC_EXPORT explicit DocParamType( const XmlNode& xmlNode );
    };

    class DocParamNameList : public Internal::DocBase<Doxygen::DoxType::DocParamNameList>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamNameList>;

        DocParamNameList( ) = default;
        HCC_EXPORT explicit DocParamNameList( const XmlNode& xmlNode );
    };

    class DocParamListItem : public Internal::DocBase<Doxygen::DoxType::DocParamListItem>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamListItem>;

        DocParamListItem( ) = default;
        HCC_EXPORT explicit DocParamListItem( const XmlNode& xmlNode );
    };

    class DocParamListType : public Internal::DocBase<Doxygen::DoxType::DocParamListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamListType>;

        DocParamListType( ) = default;
        HCC_EXPORT explicit DocParamListType( const XmlNode& xmlNode );
    };

    class DocLanguageType : public Internal::DocBase<Doxygen::DoxType::DocLanguageType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocLanguageType>;

        DocLanguageType( ) = default;
        HCC_EXPORT explicit DocLanguageType( const XmlNode& xmlNode );
    };


    class DocTocListType : public Internal::DocBase<Doxygen::DoxType::DocTocListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTocListType>;

        DocTocListType( ) = default;
        HCC_EXPORT explicit DocTocListType( const XmlNode& xmlNode );
    };

    class DocTocItemType : public Internal::DocBase<Doxygen::DoxType::DocTocItemType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTocItemType>;

        DocTocItemType( ) = default;
        HCC_EXPORT explicit DocTocItemType( const XmlNode& xmlNode );
    };

    class DocPlantumlType : public Internal::DocBase<Doxygen::DoxType::DocPlantumlType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocPlantumlType>;

        DocPlantumlType( ) = default;
        HCC_EXPORT explicit DocPlantumlType( const XmlNode& xmlNode );
    };

    class DocImageFileType : public Internal::DocBase<Doxygen::DoxType::DocImageFileType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocImageFileType>;

        DocImageFileType( ) = default;
        HCC_EXPORT explicit DocImageFileType( const XmlNode& xmlNode );
    };

    class DocDotMscType : public Internal::DocBase<Doxygen::DoxType::DocDotMscType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocDotMscType>;

        DocDotMscType( ) = default;
        HCC_EXPORT explicit DocDotMscType( const XmlNode& xmlNode );
    };

    class DocImageType : public Internal::DocBase<Doxygen::DoxType::DocImageType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocImageType>;

        DocImageType( ) = default;
        HCC_EXPORT explicit DocImageType( const XmlNode& xmlNode );

    };


    class DocHeadingType : public Internal::DocBase<Doxygen::DoxType::DocHeadingType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHeadingType>;

        DocHeadingType( ) = default;
        HCC_EXPORT explicit DocHeadingType( const XmlNode& xmlNode );

    };

    class DocCaptionType : public Internal::DocBase<Doxygen::DoxType::DocCaptionType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCaptionType>;

        DocCaptionType( ) = default;
        HCC_EXPORT explicit DocCaptionType( const XmlNode& xmlNode );
    };

    class DocEntryType : public Internal::DocBase<Doxygen::DoxType::DocEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocEntryType>;

        DocEntryType( ) = default;
        HCC_EXPORT explicit DocEntryType( const XmlNode& xmlNode );
    };

    class DocRowType : public Internal::DocBase<Doxygen::DoxType::DocRowType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRowType>;

        DocRowType( ) = default;
        HCC_EXPORT explicit DocRowType( const XmlNode& xmlNode );
    };

    class DocTableType : public Internal::DocBase<Doxygen::DoxType::DocTableType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTableType>;

        DocTableType( ) = default;
        HCC_EXPORT explicit DocTableType( const XmlNode& xmlNode );
    };

    class DocRefTextType : public Internal::DocBase<Doxygen::DoxType::DocRefTextType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRefTextType>;

        DocRefTextType( ) = default;
        HCC_EXPORT explicit DocRefTextType( const XmlNode& xmlNode );
    };

    class DocVariableListType : public Internal::DocBase<Doxygen::DoxType::DocVariableListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListType>;

        DocVariableListType( ) = default;
        HCC_EXPORT explicit DocVariableListType( const XmlNode& xmlNode );
    };

    class DocVariableListGroup : public Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>;

        DocVariableListGroup( ) = default;
        HCC_EXPORT explicit DocVariableListGroup( const XmlNode& xmlNode );
    };

    class DocVarListEntryType : public Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>;

        DocVarListEntryType( ) = default;
        HCC_EXPORT explicit DocVarListEntryType( const XmlNode& xmlNode );
    };

    class DocSimpleSectType : public Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>;

        DocSimpleSectType( ) = default;
        HCC_EXPORT explicit DocSimpleSectType( const XmlNode& xmlNode );
    };

    class DocListItemType : public Internal::DocBase<Doxygen::DoxType::DocListItemType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListItemType>;

        DocListItemType( ) = default;
        HCC_EXPORT explicit DocListItemType( const XmlNode& xmlNode );
    };

    class DocListType : public Internal::DocBase<Doxygen::DoxType::DocListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListType>;

        DocListType( ) = default;
        HCC_EXPORT explicit DocListType( const XmlNode& xmlNode );
    };

    class DocIndexEntryType : public Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>;

        DocIndexEntryType( ) = default;
        HCC_EXPORT explicit DocIndexEntryType( const XmlNode& xmlNode );
    };

    class DocFormulaType : public Internal::DocBase<Doxygen::DoxType::DocFormulaType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocFormulaType>;

        DocFormulaType( ) = default;
        HCC_EXPORT explicit DocFormulaType( const XmlNode& xmlNode );
    };

    class DocAnchorType : public Internal::DocBase<Doxygen::DoxType::DocAnchorType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocAnchorType>;

        DocAnchorType( ) = default;
        HCC_EXPORT explicit DocAnchorType( const XmlNode& xmlNode );

    };

    class DocURLLink : public Internal::DocBase<Doxygen::DoxType::DocURLLink>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocURLLink>;

        DocURLLink( ) = default;
        HCC_EXPORT explicit DocURLLink( const XmlNode& xmlNode );
    };

    class DocMarkupType : public Internal::DocBase<Doxygen::DoxType::DocMarkupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocMarkupType>;

        DocMarkupType( ) = default;
        HCC_EXPORT explicit DocMarkupType( const XmlNode& xmlNode );
    };


    class DocParaType : public Internal::DocBase<Doxygen::DoxType::DocParaType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParaType>;

        DocParaType( ) = default;
        HCC_EXPORT explicit DocParaType( const XmlNode& xmlNode );
    };

    class DocCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocCmdGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCmdGroup>;

        DocCmdGroup( ) = default;
        HCC_EXPORT explicit DocCmdGroup( const XmlNode& xmlNode );
    };

    class DocSummaryType : public Internal::DocBase<Doxygen::DoxType::DocSummaryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSummaryType>;

        DocSummaryType( ) = default;
        HCC_EXPORT explicit DocSummaryType( const XmlNode& xmlNode );
    };

    class DocTitleType : public Internal::DocBase<Doxygen::DoxType::DocTitleType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleType>;

        DocTitleType( ) = default;
        HCC_EXPORT explicit DocTitleType( const XmlNode& xmlNode );
    };

    class DocTitleCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>
    {

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>;

        DocTitleCmdGroup( ) = default;
        HCC_EXPORT explicit DocTitleCmdGroup( const XmlNode& xmlNode );
    };

    class DocInternalS6Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS6Type>
    {
    public:
        using ParaType = DocParaType;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
    private:
        ParaTypeVector para_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS6Type>;

        DocInternalS6Type( ) = default;
        HCC_EXPORT explicit DocInternalS6Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
    };

    class DocInternalS5Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS5Type>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS6Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS5Type>;

        DocInternalS5Type( ) = default;
        HCC_EXPORT explicit DocInternalS5Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }
    };

    class DocInternalS4Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS4Type>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS5Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS4Type>;

        DocInternalS4Type( ) = default;
        HCC_EXPORT explicit DocInternalS4Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }
    };

    class DocInternalS3Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS3Type>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS4Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS3Type>;

        DocInternalS3Type( ) = default;
        HCC_EXPORT explicit DocInternalS3Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }
    };

    class DocInternalS2Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS2Type>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS3Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS2Type>;

        DocInternalS2Type( ) = default;
        HCC_EXPORT explicit DocInternalS2Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }
    };

    class DocInternalS1Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS1Type>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS2Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS1Type>;

        DocInternalS1Type( ) = default;
        HCC_EXPORT explicit DocInternalS1Type( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }
    };


    class DocInternalType : public Internal::DocBase<Doxygen::DoxType::DocInternalType>
    {
    public:
        using ParaType = DocParaType;
        using SubSectType = DocInternalS1Type;
        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
    private:
        ParaTypeVector para_;
        SubSectTypeVector sections_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalType>;

        DocInternalType( ) = default;
        HCC_EXPORT explicit DocInternalType( const XmlNode& xmlNode );

        const ParaTypeVector& Para( ) const { return para_; }
        const SubSectTypeVector& Sections( ) const { return sections_; }

    };

    class DocSect6Type : public Internal::DocBase<Doxygen::DoxType::DocSect6Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS5Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect6Type>;

        DocSect6Type( ) = default;
        HCC_EXPORT explicit DocSect6Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }
    };


    class DocSect5Type : public Internal::DocBase<Doxygen::DoxType::DocSect5Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS5Type;
        using SubSectType = DocSect6Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector, SubSectTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect5Type>;

        DocSect5Type( ) = default;
        HCC_EXPORT explicit DocSect5Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }
    };

    class DocSect4Type : public Internal::DocBase<Doxygen::DoxType::DocSect4Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS4Type;
        using SubSectType = DocSect5Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector, SubSectTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect4Type>;

        DocSect4Type( ) = default;
        HCC_EXPORT explicit DocSect4Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }
    };

    class DocSect3Type : public Internal::DocBase<Doxygen::DoxType::DocSect3Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS3Type;
        using SubSectType = DocSect4Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector, SubSectTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect3Type>;

        DocSect3Type( ) = default;
        HCC_EXPORT explicit DocSect3Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }
    };

    class DocSect2Type : public Internal::DocBase<Doxygen::DoxType::DocSect2Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS2Type;
        using SubSectType = DocSect3Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector, SubSectTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect2Type>;

        DocSect2Type( ) = default;
        HCC_EXPORT explicit DocSect2Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }
    };

    class DocSect1Type : public Internal::DocBase<Doxygen::DoxType::DocSect1Type>
    {
    public:
        using ParaType = DocParaType;
        using InternalType = DocInternalS1Type;
        using SubSectType = DocSect2Type;

        using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;

        using ContentType = std::variant<ParaTypeVector, InternalTypeVector, SubSectTypeVector>;
        using ContentTypeVector = std::vector<ContentType>;
    private:
        WideString id_;
        WideString title_;
        ContentTypeVector contents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect1Type>;

        DocSect1Type( ) = default;
        HCC_EXPORT explicit DocSect1Type( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Title( ) const { return title_; }
        const ContentTypeVector& Contents( ) const { return contents_; }

    };

    class LocationType : public Internal::DocBase<Doxygen::DoxType::LocationType>
    {
        WideString file_;
        Int32 line_ = 0;
        Int32 column_ = 0;
        WideString declFile_;
        Int32 declLine_ = 0;
        Int32 declColumn_ = 0;
        WideString bodyFile_;
        Int32 bodyStart_ = 0;
        Int32 bodyEnd_ = 0;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LocationType>;

        LocationType( ) = default;
        HCC_EXPORT explicit LocationType( const XmlNode& xmlNode );

        const WideString& File( ) const { return file_; }
        Int32 Line( ) const { return line_; }
        Int32 Column( ) const { return column_; }
        const WideString& DeclFile( ) const { return declFile_; }
        Int32 DeclLine( ) const { return declLine_; }
        Int32 DeclColumn( ) const { return declColumn_; }
        const WideString& BodyFile( ) const { return bodyFile_; }
        Int32 BodyStart( ) const { return bodyStart_; }
        Int32 BodyEnd( ) const { return bodyEnd_; }

    };

    class ReferenceType : public Internal::DocBase<Doxygen::DoxType::ReferenceType>
    {
        WideString refId_;
        WideString compoundRef_;
        Int32 startLine_ = 0;
        Int32 endline_ = 0;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReferenceType>;

        ReferenceType( ) = default;
        HCC_EXPORT explicit ReferenceType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }

        const WideString& CompoundRef( ) const { return compoundRef_; }
        Int32 StartLine( ) const { return startLine_; }
        Int32 Endline( ) const { return endline_; }

    };
    /*
    class SpType : public Internal::DocBase<Doxygen::DoxType::SpType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SpType>;

        SpType( ) = default;
        HCC_EXPORT explicit SpType( const XmlNode& xmlNode );
    };
    */
    class HighlightType : public Internal::DocBase<Doxygen::DoxType::HighlightType>
    {
    public:
        using SpOrRef = std::variant<Int32, std::shared_ptr<RefTextType>>;
    private:
        DoxHighlightClass class_;
        std::vector<SpOrRef> items_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::HighlightType>;
        
        HighlightType( ) = default;
        HCC_EXPORT explicit HighlightType( const XmlNode& xmlNode );

        DoxHighlightClass Class( ) const { return class_; }
        const std::vector<SpOrRef>& Items( ) const { return items_; }
    };

    class CodeLineType : public Internal::DocBase<Doxygen::DoxType::CodeLineType>
    {
        Int32 lineno_ = 0;
        WideString refId_;
        DoxRefKind refKind_{};
        bool external_{};
        std::vector<HighlightTypePtr> highlight_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CodeLineType>;

        CodeLineType( ) = default;
        HCC_EXPORT explicit CodeLineType( const XmlNode& xmlNode );

        Int32 LineNo( ) const { return lineno_; }
        const WideString& RefId( ) const { return refId_; }
        DoxRefKind RefKind( ) const { return refKind_; }
        bool External( ) const { return external_; }
        const std::vector<HighlightTypePtr>& Highlight( ) const { return highlight_; }

    };

    class ListingType : public Internal::DocBase<Doxygen::DoxType::ListingType>, public std::vector<CodeLineTypePtr>
    {
        WideString fileName_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ListingType>;

        ListingType( ) = default;
        HCC_EXPORT explicit ListingType( const XmlNode& xmlNode );

        const WideString& fileName( ) const { return fileName_; }

    };

    class LinkType : public Internal::DocBase<Doxygen::DoxType::LinkType>
    {
        WideString refId_;
        WideString external_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LinkType>;

        LinkType( ) = default;
        HCC_EXPORT explicit LinkType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        const WideString& External( ) const { return external_; }
    };

    class ChildNodeType : public Internal::DocBase<Doxygen::DoxType::ChildNodeType>
    {
        WideString refId_;
        std::vector<WideString> edgeLabel_;
        DoxGraphRelation relation_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ChildNodeType>;

        ChildNodeType( ) = default;
        HCC_EXPORT explicit ChildNodeType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        const std::vector<WideString>& EdgeLabel( ) const { return edgeLabel_; }
        DoxGraphRelation Relation( ) const { return relation_; }
    };

    class NodeType : public Internal::DocBase<Doxygen::DoxType::NodeType>
    {
        WideString id_;
        WideString label_;
        LinkTypePtr link_;
        std::vector<ChildNodeTypePtr> childNode_;

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::NodeType>;

        NodeType( ) = default;
        HCC_EXPORT explicit NodeType( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Label( ) const { return label_; }
        const LinkTypePtr& Link( ) const { return link_; }
        const std::vector<ChildNodeTypePtr>& ChildNode( ) const { return childNode_; }

    };

    class GraphType : public Internal::DocBase<Doxygen::DoxType::GraphType>, public std::vector<NodeTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::GraphType>;

        GraphType( ) = default;
        HCC_EXPORT explicit GraphType( const XmlNode& xmlNode );
    };

    class LinkedTextType : public Internal::DocBase<Doxygen::DoxType::LinkedTextType>, public std::vector<RefTextTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LinkedTextType>;

        LinkedTextType( ) = default;
        HCC_EXPORT explicit LinkedTextType( const XmlNode& xmlNode );
    };

    class ParamType : public Internal::DocBase<Doxygen::DoxType::ParamType>
    {
        WideString attributes_;
        LinkedTextTypePtr type_;
        WideString declName_;
        WideString defName_;
        WideString array_;
        LinkedTextTypePtr defVal_;
        LinkedTextTypePtr typeConstraint_;
        DescriptionTypePtr briefDescription_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ParamType>;

        ParamType( ) = default;
        HCC_EXPORT explicit ParamType( const XmlNode& xmlNode );

        const WideString& Attributes( ) const { return attributes_; }
        const LinkedTextTypePtr& Type( ) const { return type_; }
        const WideString& DeclName( ) const { return declName_; }
        const WideString& DefName( ) const { return defName_; }
        const WideString& Array( ) const { return array_; }
        const LinkedTextTypePtr& DefVal( ) const { return defVal_; }
        const LinkedTextTypePtr& TypeConstraint( ) const { return typeConstraint_; }
        const DescriptionTypePtr& BriefDescription( ) const { return briefDescription_; }

    };


    class TemplateParamListType : public Internal::DocBase<Doxygen::DoxType::TemplateParamListType>, public std::vector<ParamTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TemplateParamListType>;

        TemplateParamListType( ) = default;
        HCC_EXPORT explicit TemplateParamListType( const XmlNode& xmlNode );
    };

    class EnumvalueType : public Internal::DocBase<Doxygen::DoxType::EnumvalueType>
    {
        WideString id_;
        DoxProtectionKind prot_;
        WideString name_;
        LinkedTextTypePtr initializer_;
        DescriptionTypePtr briefDescription_;
        DescriptionTypePtr detailedDescription_;

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::EnumvalueType>;

        EnumvalueType( ) = default;
        HCC_EXPORT explicit EnumvalueType( const XmlNode& xmlNode );
    };

    class DescriptionType : public Internal::DocBase<Doxygen::DoxType::DescriptionType>
    {
        WideString title_;
        std::vector<DocParaTypePtr> para_;
        std::vector<DocInternalTypePtr> internal_;
        std::vector<DocSect1TypePtr> sect1_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DescriptionType>;

        DescriptionType( ) = default;
        HCC_EXPORT explicit DescriptionType( const XmlNode& xmlNode );

        const WideString& Title( ) const { return title_; }
        const std::vector<DocParaTypePtr>& Para( ) const { return para_; }
        const std::vector<DocInternalTypePtr>& Internal( ) const { return internal_; }
        const std::vector<DocSect1TypePtr>& Sect1( ) const { return sect1_; }

    };


    class MemberDefType : public Internal::DocBase<Doxygen::DoxType::MemberDefType>
    {
        DoxMemberKind kind_{};
        WideString id_;
        DoxProtectionKind prot_{};
        bool static_{};
        bool extern_{};
        bool strong_{};
        bool const_{};
        bool explicit_{};
        bool inline_{};
        DoxRefQualifierKind refQual_{};
        DoxVirtualKind virt_{};
        bool volatile_{};
        bool mutable_{};
        bool noExcept_{};
        WideString noexceptExpression_;
        bool nodiscard_{};
        bool constexpr_{};
        bool consteval_{};
        bool constinit_{};
        //  Qt property
        bool readable_{};
        bool writable_{};
        // C++/CLI variable
        bool initOnly_{};
        // C++/CLI and C# property
        bool settable_{};
        bool privateSettable_{};
        bool protectedSettable_{};
        bool gettable_{};
        bool privateGettable_{};
        bool protectedGettable_{};
        // C++/CLI function
        bool final_{};
        bool sealed_{};
        bool new_{};
        // C++/CLI event
        bool add_{};
        bool remove_{};
        bool raise_{};
        // Objective-C 2.0 protocol method
        bool optional_{};
        bool required_{};
        // Objective-C 2.0 property accessor
        bool accessor_{};
        // UNO IDL
        bool attribute_{};
        bool property_{};
        bool readonly_{};
        bool bound_{};
        bool removable_{};
        bool constrained_{};
        bool transient_{};
        bool maybeVoid_{};
        bool maybeDefault_{};
        bool maybeAmbiguous_{};

        TemplateParamListTypePtr templateParamList_;
        LinkedTextTypePtr type_;
        WideString definition_;
        WideString argsString_;
        WideString name_;
        WideString qualifiedName_;
        WideString read_;
        WideString write_;
        WideString bitField_;
        std::vector<ReimplementTypePtr> reimplements_;
        std::vector<ReimplementTypePtr> reimplementedBy_;
        WideString qualifier_;
        std::vector<ParamTypePtr> param_;
        std::vector<EnumvalueTypePtr> enumvalue_;
        LinkedTextTypePtr requiresClause_;
        LinkedTextTypePtr initializer_;
        LinkedTextTypePtr exceptions_;
        DescriptionTypePtr briefDescription_;
        DescriptionTypePtr detailedDescription_;
        DescriptionTypePtr inbodyDescription_;
        LocationTypePtr location_;
        std::vector<ReferenceTypePtr> references_;
        std::vector<ReferenceTypePtr> referencedBy_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberDefType>;

        MemberDefType( ) = default;
        HCC_EXPORT explicit MemberDefType( const XmlNode& xmlNode );

        DoxMemberKind Kind( ) const { return kind_; }
        const WideString& Id( ) const { return id_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        bool Static( ) const { return static_; }
        bool Extern( ) const { return extern_; }
        bool Strong( ) const { return strong_; }
        bool Const( ) const { return const_; }
        bool Explicit( ) const { return explicit_; }
        bool Inline( ) const { return inline_; }
        DoxRefQualifierKind RefQual( ) const { return refQual_; }
        DoxVirtualKind Virt( ) const { return virt_; }
        bool Volatile( ) const { return volatile_; }
        bool Mutable( ) const { return mutable_; }
        bool NoExcept( ) const { return noExcept_; }
        const WideString& NoexceptExpression( ) const { return noexceptExpression_; }
        bool Nodiscard( ) const { return nodiscard_; }
        bool Constexpr( ) const { return constexpr_; }
        bool Consteval( ) const { return consteval_; }
        bool Constinit( ) const { return constinit_; }
        bool Readable( ) const { return readable_; }
        bool Writable( ) const { return writable_; }
        bool InitOnly( ) const { return initOnly_; }
        bool Settable( ) const { return settable_; }
        bool PrivateSettable( ) const { return privateSettable_; }
        bool ProtectedSettable( ) const { return protectedSettable_; }
        bool Gettable( ) const { return gettable_; }
        bool PrivateGettable( ) const { return privateGettable_; }
        bool ProtectedGettable( ) const { return protectedGettable_; }
        bool Final( ) const { return final_; }
        bool Sealed( ) const { return sealed_; }
        bool New( ) const { return new_; }
        bool Add( ) const { return add_; }
        bool Remove( ) const { return remove_; }
        bool Raise( ) const { return raise_; }
        bool Optional( ) const { return optional_; }
        bool Required( ) const { return required_; }
        bool Accessor( ) const { return accessor_; }
        bool Attribute( ) const { return attribute_; }
        bool Property( ) const { return property_; }
        bool Readonly( ) const { return readonly_; }
        bool Bound( ) const { return bound_; }
        bool Removable( ) const { return removable_; }
        bool Constrained( ) const { return constrained_; }
        bool Transient( ) const { return transient_; }
        bool MaybeVoid( ) const { return maybeVoid_; }
        bool MaybeDefault( ) const { return maybeDefault_; }
        bool MaybeAmbiguous( ) const { return maybeAmbiguous_; }

        const TemplateParamListTypePtr& TemplateParamList( ) const { return templateParamList_; }
        const LinkedTextTypePtr& Type( ) const { return type_; }
        const WideString& Definition( ) const { return definition_; }
        const WideString& ArgsString( ) const { return argsString_; }
        const WideString& Name( ) const { return name_; }
        const WideString& QualifiedName( ) const { return qualifiedName_; }
        const WideString& Read( ) const { return read_; }
        const WideString& Write( ) const { return write_; }
        const WideString& BitField( ) const { return bitField_; }
        const std::vector<ReimplementTypePtr>& Reimplements( ) const { return reimplements_; }
        const std::vector<ReimplementTypePtr>& ReimplementedBy( ) const { return reimplementedBy_; }
        const WideString& Qualifier( ) const { return qualifier_; }
        const std::vector<ParamTypePtr>& Param( ) const { return param_; }
        const std::vector<EnumvalueTypePtr>& Enumvalue( ) const { return enumvalue_; }
        const LinkedTextTypePtr& RequiresClause( ) const { return requiresClause_; }
        const LinkedTextTypePtr& Initializer( ) const { return initializer_; }
        const LinkedTextTypePtr& Exceptions( ) const { return exceptions_; }
        const DescriptionTypePtr& BriefDescription( ) const { return briefDescription_; }
        const DescriptionTypePtr& DetailedDescription( ) const { return detailedDescription_; }
        const DescriptionTypePtr& InbodyDescription( ) const { return inbodyDescription_; }
        const LocationTypePtr& Location( ) const { return location_; }
        const std::vector<ReferenceTypePtr>& References( ) const { return references_; }
        const std::vector<ReferenceTypePtr>& ReferencedBy( ) const { return referencedBy_; }

    };

    class SectionDefType : public Internal::DocBase<Doxygen::DoxType::SectionDefType>
    {
        WideString header_;
        DescriptionTypePtr description_;
        std::vector<MemberDefTypePtr> memberDef_;
        std::vector<MemberTypePtr> member_;
        DoxSectionKind kind_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SectionDefType>;

        SectionDefType( ) = default;
        HCC_EXPORT explicit SectionDefType( const XmlNode& xmlNode );

        const WideString& Header( ) const { return header_; }
        const DescriptionTypePtr& Description( ) const { return description_; }
        const std::vector<MemberDefTypePtr>& MemberDef( ) const { return memberDef_; }
        const std::vector<MemberTypePtr>& Member( ) const { return member_; }
        DoxSectionKind Kind( ) const { return kind_; }

    };

    class MemberType : public Internal::DocBase<Doxygen::DoxType::MemberType>
    {
        WideString name_;
        WideString refId_;
        MemberKind kind_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberType>;

        MemberType( ) = default;
        HCC_EXPORT explicit MemberType( const XmlNode& xmlNode );


        const WideString& Name( ) const { return name_; }
        const WideString& RefId( ) const { return refId_; }
        MemberKind kind( ) const { return kind_; }
    };

    class RefTextType : public Internal::DocBase<Doxygen::DoxType::RefTextType>
    {
        WideString refId_;
        DoxRefKind kindRef_{};
        WideString external_;
        WideString tooltip_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefTextType>;

        RefTextType( ) = default;
        HCC_EXPORT explicit RefTextType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        DoxRefKind KindRef( ) const { return kindRef_; }
        const WideString& External( ) const { return external_; }
        const WideString& Tooltip( ) const { return tooltip_; }
        const WideString& Content( ) const { content_; }

    };

    class RefType : public Internal::DocBase<Doxygen::DoxType::RefType>
    {
        WideString refId_;
        DoxProtectionKind prot_{};
        bool inline_ = false;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefType>;

        RefType( ) = default;
        HCC_EXPORT explicit RefType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        bool Inline( ) const { return inline_; }

        const WideString& Content( ) const
        {
            return content_;
        }
    };


    class ExportType : public Internal::DocBase<Doxygen::DoxType::ExportType>
    {
        WideString refId_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ExportType>;

        ExportType( ) = default;
        HCC_EXPORT explicit ExportType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }

        const WideString& Content( ) const
        {
            return content_;
        }
    };

    class ExportsType : public Internal::DocBase<Doxygen::DoxType::ExportsType>, public std::vector<ExportTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ExportsType>;

        ExportsType( ) = default;
        HCC_EXPORT explicit ExportsType( const XmlNode& xmlNode );
    };

    class IncType : public Internal::DocBase<Doxygen::DoxType::IncType>
    {
        WideString refId_;
        bool local_ = false;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::IncType>;

        IncType( ) = default;
        HCC_EXPORT explicit IncType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        bool Local( ) const { return local_; }

        const WideString& Content( ) const
        {
            return content_;
        }
    };

    class ReimplementType : public Internal::DocBase<Doxygen::DoxType::ReimplementType>
    {
        WideString refId_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReimplementType>;

        ReimplementType( ) = default;
        HCC_EXPORT explicit ReimplementType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }

        const WideString& Content( ) const
        {
            return content_;
        }
    };


    class CompoundRefType : public Internal::DocBase<Doxygen::DoxType::CompoundRefType>
    {
        WideString refId_;
        DoxProtectionKind prot_{};
        DoxVirtualKind virt_{};
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CompoundRefType>;

        CompoundRefType( ) = default;
        HCC_EXPORT explicit CompoundRefType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        DoxVirtualKind Virt( ) const { return virt_; }

        const WideString& Content( ) const
        {
            return content_;
        }
    };


    class DocHtmlOnlyType : public Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>
    {
        WideString block_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>;

        DocHtmlOnlyType( ) = default;
        HCC_EXPORT explicit DocHtmlOnlyType( const XmlNode& xmlNode );

        const WideString& Block( ) const
        {
            return block_;
        }

        const WideString& Content( ) const
        {
            return content_;
        }

    };


    class MemberRefType : public Internal::DocBase<Doxygen::DoxType::MemberRefType>
    {
        WideString name_;
        WideString scope_;
        WideString refId_;
        DoxProtectionKind prot_{};
        DoxVirtualKind virt_{};
        WideString ambiguityScope_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberRefType>;

        MemberRefType( ) = default;
        HCC_EXPORT explicit MemberRefType( const XmlNode& xmlNode );

        const WideString& Name( ) const { return name_; }
        const WideString& Scope( ) const { return scope_; }
        const WideString& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        DoxVirtualKind Virt( ) const { return virt_; }
        const WideString& AmbiguityScope( ) const { return ambiguityScope_; }

    };


    class ListOfAllMembersType : public Internal::DocBase<Doxygen::DoxType::ListOfAllMembersType>, public std::vector<MemberRefTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ListOfAllMembersType>;

        ListOfAllMembersType( ) = default;
        HCC_EXPORT explicit ListOfAllMembersType( const XmlNode& xmlNode );
    };


    class CompoundDefType : public Internal::DocBase<Doxygen::DoxType::CompoundDefType>
    {
        WideString id_;
        DoxCompoundKind kind_{};
        DoxLanguage language_{};
        DoxProtectionKind prot_{};
        bool final_{};
        bool inline_{};
        bool sealed_{};
        bool abstract_{};
        WideString compoundName_;
        WideString title_;
        std::vector<CompoundRefTypePtr> baseCompoundRef_;
        std::vector<CompoundRefTypePtr> derivedCompoundRef_;
        std::vector<IncTypePtr> includes_;
        std::vector<IncTypePtr> includedBy_;
        GraphTypePtr incDepGraph_;
        GraphTypePtr invIncDepGraph_;
        std::vector<RefTypePtr> innerModule_;
        std::vector<RefTypePtr> innerDir_;
        std::vector<RefTypePtr> innerFile_;
        std::vector<RefTypePtr> innerClass_;
        std::vector<RefTypePtr> innerConcept_;
        std::vector<RefTypePtr> innerNamespace_;
        std::vector<RefTypePtr> innerPage_;
        std::vector<RefTypePtr> innerGroup_;
        std::vector<WideString> qualifier_;
        TemplateParamListTypePtr templateParamList_;
        std::vector<SectionDefTypePtr> sectiondef_;
        TableOfContentsTypePtr tableOfContents_;
        LinkedTextTypePtr requiresClause_;
        LinkedTextTypePtr initializer_;
        DescriptionTypePtr briefDescription_;
        DescriptionTypePtr detailedDescription_;
        ExportsTypePtr exports_;
        GraphTypePtr inheritanceGraph_;
        GraphTypePtr collaborationGraph_;
        ListingTypePtr programListing_;
        LocationTypePtr location_;
        ListOfAllMembersTypePtr listOfAllMembers_;
        
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CompoundDefType>;

        CompoundDefType( ) = default;
        HCC_EXPORT explicit CompoundDefType( const XmlNode& xmlNode );

        const WideString& Id() const { return id_; }
        DoxCompoundKind Kind( ) const { return kind_; }
        DoxLanguage Language( ) const { return language_; }
        DoxProtectionKind Prot() const { return prot_; }
        bool Final() const { return final_; }
        bool Inline() const { return inline_; }
        bool Sealed() const { return sealed_; }
        bool Abstract() const { return abstract_; }
        const WideString& CompoundName() const { return compoundName_; }
        const WideString& Title() const { return title_; }
        const std::vector<CompoundRefTypePtr>& BaseCompoundRef() const { return baseCompoundRef_; }
        const std::vector<CompoundRefTypePtr>& DerivedCompoundRef() const { return derivedCompoundRef_; }
        const std::vector<IncTypePtr>& Includes() const { return includes_; }
        const std::vector<IncTypePtr>& IncludedBy() const { return includedBy_; }
        const GraphTypePtr& IncDepGraph() const { return incDepGraph_; }
        const GraphTypePtr& InvIncDepGraph() const { return invIncDepGraph_; }
        const std::vector<RefTypePtr>& InnerModule() const { return innerModule_; }
        const std::vector<RefTypePtr>& InnerDir() const { return innerDir_; }
        const std::vector<RefTypePtr>& InnerFile() const { return innerFile_; }
        const std::vector<RefTypePtr>& InnerClass() const { return innerClass_; }
        const std::vector<RefTypePtr>& InnerConcept() const { return innerConcept_; }
        const std::vector<RefTypePtr>& InnerNamespace() const { return innerNamespace_; }
        const std::vector<RefTypePtr>& InnerPage() const { return innerPage_; }
        const std::vector<RefTypePtr>& InnerGroup() const { return innerGroup_; }
        const std::vector<WideString>& Qualifier() const { return qualifier_; }
        const TemplateParamListTypePtr& TemplateParamList() const { return templateParamList_; }
        const std::vector<SectionDefTypePtr>& Sectiondef() const { return sectiondef_; }
        const TableOfContentsTypePtr& TableOfContents() const { return tableOfContents_; }
        const LinkedTextTypePtr& RequiresClause() const { return requiresClause_; }
        const LinkedTextTypePtr& Initializer() const { return initializer_; }
        const DescriptionTypePtr& BriefDescription() const { return briefDescription_; }
        const DescriptionTypePtr& DetailedDescription() const { return detailedDescription_; }
        const ExportsTypePtr& Exports() const { return exports_; }
        const GraphTypePtr& InheritanceGraph() const { return inheritanceGraph_; }
        const GraphTypePtr& CollaborationGraph() const { return collaborationGraph_; }
        const ListingTypePtr& ProgramListing() const { return programListing_; }
        const LocationTypePtr& Location() const { return location_; }
        const ListOfAllMembersTypePtr& ListOfallMembers( ) const { return listOfAllMembers_; }

    };

    class Document : public Internal::DocBase<Doxygen::DoxType::Document>, public std::vector<CompoundDefTypePtr>
    {
        WideString name_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::Document>;

        Document( ) = default;
        HCC_EXPORT explicit Document( const WideString& name, const XmlNode& xmlNode );
    };

    class DocumentCollection : public std::unordered_map<WideString, DocumentPtr>
    {
         
    public:
        using Base = std::unordered_map<WideString, DocumentPtr>;

        HCC_EXPORT explicit DocumentCollection( );

        HCC_EXPORT void AddDirectory( const WideString& directoryName );
        HCC_EXPORT void AddFile( const WideString& filename );

    };


}


namespace Harlinn::Common::Core
{
    HCC_EXPORT WideString ToWideString( Doxygen::MemberKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::MemberKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::MemberKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::MemberKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT MemberKind ParseMemberKind( const WideString& str );
        HCC_EXPORT MemberKind ParseMemberKind( const WideString& str, MemberKind defaultResult );
        HCC_EXPORT bool TryParseMemberKind( const WideString& str, MemberKind& value );

        inline MemberKind ParseMemberKind( const AnsiString& str )
        {
            return ParseMemberKind( ToWideString( str ) );
        }
        inline MemberKind ParseMemberKind( const AnsiString& str, MemberKind defaultResult )
        {
            return ParseMemberKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseMemberKind( const AnsiString& str, MemberKind& value )
        {
            return TryParseMemberKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::MemberKind& value )
    {
        return Doxygen::TryParseMemberKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::MemberKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::MemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseMemberKind( str );
    }


    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxGraphRelation value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxGraphRelation value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxGraphRelation value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxGraphRelation value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxGraphRelation ParseDoxGraphRelation( const WideString& str );
        HCC_EXPORT DoxGraphRelation ParseDoxGraphRelation( const WideString& str, DoxGraphRelation defaultResult );
        HCC_EXPORT bool TryParseDoxGraphRelation( const WideString& str, DoxGraphRelation& value );

        inline DoxGraphRelation ParseDoxGraphRelation( const AnsiString& str )
        {
            return ParseDoxGraphRelation( ToWideString( str ) );
        }
        inline DoxGraphRelation ParseDoxGraphRelation( const AnsiString& str, DoxGraphRelation defaultResult )
        {
            return ParseDoxGraphRelation( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxGraphRelation( const AnsiString& str, DoxGraphRelation& value )
        {
            return TryParseDoxGraphRelation( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxGraphRelation& value )
    {
        return Doxygen::TryParseDoxGraphRelation( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxGraphRelation, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxGraphRelation( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxGraphRelation, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxGraphRelation( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxRefKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxRefKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxRefKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxRefKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxRefKind ParseDoxRefKind( const WideString& str );
        HCC_EXPORT DoxRefKind ParseDoxRefKind( const WideString& str, DoxRefKind defaultResult );
        HCC_EXPORT bool TryParseDoxRefKind( const WideString& str, DoxRefKind& value );

        inline DoxRefKind ParseDoxRefKind( const AnsiString& str )
        {
            return ParseDoxRefKind( ToWideString( str ) );
        }
        inline DoxRefKind ParseDoxRefKind( const AnsiString& str, DoxRefKind defaultResult )
        {
            return ParseDoxRefKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxRefKind( const AnsiString& str, DoxRefKind& value )
        {
            return TryParseDoxRefKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxRefKind& value )
    {
        return Doxygen::TryParseDoxRefKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxRefKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxRefKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxMemberKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxMemberKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxMemberKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxMemberKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxMemberKind ParseDoxMemberKind( const WideString& str );
        HCC_EXPORT DoxMemberKind ParseDoxMemberKind( const WideString& str, DoxMemberKind defaultResult );
        HCC_EXPORT bool TryParseDoxMemberKind( const WideString& str, DoxMemberKind& value );

        inline DoxMemberKind ParseDoxMemberKind( const AnsiString& str )
        {
            return ParseDoxMemberKind( ToWideString( str ) );
        }
        inline DoxMemberKind ParseDoxMemberKind( const AnsiString& str, DoxMemberKind defaultResult )
        {
            return ParseDoxMemberKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxMemberKind( const AnsiString& str, DoxMemberKind& value )
        {
            return TryParseDoxMemberKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxMemberKind& value )
    {
        return Doxygen::TryParseDoxMemberKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxMemberKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxMemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxMemberKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxProtectionKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxProtectionKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxProtectionKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxProtectionKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxProtectionKind ParseDoxProtectionKind( const WideString& str );
        HCC_EXPORT DoxProtectionKind ParseDoxProtectionKind( const WideString& str, DoxProtectionKind defaultResult );
        HCC_EXPORT bool TryParseDoxProtectionKind( const WideString& str, DoxProtectionKind& value );

        inline DoxProtectionKind ParseDoxProtectionKind( const AnsiString& str )
        {
            return ParseDoxProtectionKind( ToWideString( str ) );
        }
        inline DoxProtectionKind ParseDoxProtectionKind( const AnsiString& str, DoxProtectionKind defaultResult )
        {
            return ParseDoxProtectionKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxProtectionKind( const AnsiString& str, DoxProtectionKind& value )
        {
            return TryParseDoxProtectionKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxProtectionKind& value )
    {
        return Doxygen::TryParseDoxProtectionKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxProtectionKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxProtectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxProtectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxProtectionKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxRefQualifierKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxRefQualifierKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxRefQualifierKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxRefQualifierKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxRefQualifierKind ParseDoxRefQualifierKind( const WideString& str );
        HCC_EXPORT DoxRefQualifierKind ParseDoxRefQualifierKind( const WideString& str, DoxRefQualifierKind defaultResult );
        HCC_EXPORT bool TryParseDoxRefQualifierKind( const WideString& str, DoxRefQualifierKind& value );

        inline DoxRefQualifierKind ParseDoxRefQualifierKind( const AnsiString& str )
        {
            return ParseDoxRefQualifierKind( ToWideString( str ) );
        }
        inline DoxRefQualifierKind ParseDoxRefQualifierKind( const AnsiString& str, DoxRefQualifierKind defaultResult )
        {
            return ParseDoxRefQualifierKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxRefQualifierKind( const AnsiString& str, DoxRefQualifierKind& value )
        {
            return TryParseDoxRefQualifierKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxRefQualifierKind& value )
    {
        return Doxygen::TryParseDoxRefQualifierKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxRefQualifierKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxRefQualifierKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefQualifierKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefQualifierKind( str );
    }


    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxLanguage value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxLanguage value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxLanguage value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxLanguage value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxLanguage ParseDoxLanguage( const WideString& str );
        HCC_EXPORT DoxLanguage ParseDoxLanguage( const WideString& str, DoxLanguage defaultResult );
        HCC_EXPORT bool TryParseDoxLanguage( const WideString& str, DoxLanguage& value );

        inline DoxLanguage ParseDoxLanguage( const AnsiString& str )
        {
            return ParseDoxLanguage( ToWideString( str ) );
        }
        inline DoxLanguage ParseDoxLanguage( const AnsiString& str, DoxLanguage defaultResult )
        {
            return ParseDoxLanguage( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxLanguage( const AnsiString& str, DoxLanguage& value )
        {
            return TryParseDoxLanguage( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxLanguage& value )
    {
        return Doxygen::TryParseDoxLanguage( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxLanguage, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxLanguage( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxLanguage, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxLanguage( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxVirtualKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxVirtualKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxVirtualKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxVirtualKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxVirtualKind ParseDoxVirtualKind( const WideString& str );
        HCC_EXPORT DoxVirtualKind ParseDoxVirtualKind( const WideString& str, DoxVirtualKind defaultResult );
        HCC_EXPORT bool TryParseDoxVirtualKind( const WideString& str, DoxVirtualKind& value );

        inline DoxVirtualKind ParseDoxVirtualKind( const AnsiString& str )
        {
            return ParseDoxVirtualKind( ToWideString( str ) );
        }
        inline DoxVirtualKind ParseDoxVirtualKind( const AnsiString& str, DoxVirtualKind defaultResult )
        {
            return ParseDoxVirtualKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxVirtualKind( const AnsiString& str, DoxVirtualKind& value )
        {
            return TryParseDoxVirtualKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxVirtualKind& value )
    {
        return Doxygen::TryParseDoxVirtualKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxVirtualKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxVirtualKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVirtualKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVirtualKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCompoundKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCompoundKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxCompoundKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxCompoundKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCompoundKind ParseDoxCompoundKind( const WideString& str );
        HCC_EXPORT DoxCompoundKind ParseDoxCompoundKind( const WideString& str, DoxCompoundKind defaultResult );
        HCC_EXPORT bool TryParseDoxCompoundKind( const WideString& str, DoxCompoundKind& value );

        inline DoxCompoundKind ParseDoxCompoundKind( const AnsiString& str )
        {
            return ParseDoxCompoundKind( ToWideString( str ) );
        }
        inline DoxCompoundKind ParseDoxCompoundKind( const AnsiString& str, DoxCompoundKind defaultResult )
        {
            return ParseDoxCompoundKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxCompoundKind( const AnsiString& str, DoxCompoundKind& value )
        {
            return TryParseDoxCompoundKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxCompoundKind& value )
    {
        return Doxygen::TryParseDoxCompoundKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCompoundKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxCompoundKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCompoundKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCompoundKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxSectionKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxSectionKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxSectionKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxSectionKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxSectionKind ParseDoxSectionKind( const WideString& str );
        HCC_EXPORT DoxSectionKind ParseDoxSectionKind( const WideString& str, DoxSectionKind defaultResult );
        HCC_EXPORT bool TryParseDoxSectionKind( const WideString& str, DoxSectionKind& value );

        inline DoxSectionKind ParseDoxSectionKind( const AnsiString& str )
        {
            return ParseDoxSectionKind( ToWideString( str ) );
        }
        inline DoxSectionKind ParseDoxSectionKind( const AnsiString& str, DoxSectionKind defaultResult )
        {
            return ParseDoxSectionKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxSectionKind( const AnsiString& str, DoxSectionKind& value )
        {
            return TryParseDoxSectionKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxSectionKind& value )
    {
        return Doxygen::TryParseDoxSectionKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxSectionKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxSectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSectionKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxHighlightClass value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxHighlightClass value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxHighlightClass value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxHighlightClass value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxHighlightClass ParseDoxHighlightClass( const WideString& str );
        HCC_EXPORT DoxHighlightClass ParseDoxHighlightClass( const WideString& str, DoxHighlightClass defaultResult );
        HCC_EXPORT bool TryParseDoxHighlightClass( const WideString& str, DoxHighlightClass& value );

        inline DoxHighlightClass ParseDoxHighlightClass( const AnsiString& str )
        {
            return ParseDoxHighlightClass( ToWideString( str ) );
        }
        inline DoxHighlightClass ParseDoxHighlightClass( const AnsiString& str, DoxHighlightClass defaultResult )
        {
            return ParseDoxHighlightClass( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxHighlightClass( const AnsiString& str, DoxHighlightClass& value )
        {
            return TryParseDoxHighlightClass( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxHighlightClass& value )
    {
        return Doxygen::TryParseDoxHighlightClass( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxHighlightClass, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxHighlightClass( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxHighlightClass, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxHighlightClass( str );
    }
    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxSimpleSectKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxSimpleSectKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxSimpleSectKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxSimpleSectKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxSimpleSectKind ParseDoxSimpleSectKind( const WideString& str );
        HCC_EXPORT DoxSimpleSectKind ParseDoxSimpleSectKind( const WideString& str, DoxSimpleSectKind defaultResult );
        HCC_EXPORT bool TryParseDoxSimpleSectKind( const WideString& str, DoxSimpleSectKind& value );

        inline DoxSimpleSectKind ParseDoxSimpleSectKind( const AnsiString& str )
        {
            return ParseDoxSimpleSectKind( ToWideString( str ) );
        }
        inline DoxSimpleSectKind ParseDoxSimpleSectKind( const AnsiString& str, DoxSimpleSectKind defaultResult )
        {
            return ParseDoxSimpleSectKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxSimpleSectKind( const AnsiString& str, DoxSimpleSectKind& value )
        {
            return TryParseDoxSimpleSectKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxSimpleSectKind& value )
    {
        return Doxygen::TryParseDoxSimpleSectKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxSimpleSectKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxSimpleSectKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSimpleSectKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSimpleSectKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCheck value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCheck value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxCheck value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxCheck value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCheck ParseDoxCheck( const WideString& str );
        HCC_EXPORT DoxCheck ParseDoxCheck( const WideString& str, DoxCheck defaultResult );
        HCC_EXPORT bool TryParseDoxCheck( const WideString& str, DoxCheck& value );

        inline DoxCheck ParseDoxCheck( const AnsiString& str )
        {
            return ParseDoxCheck( ToWideString( str ) );
        }
        inline DoxCheck ParseDoxCheck( const AnsiString& str, DoxCheck defaultResult )
        {
            return ParseDoxCheck( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxCheck( const AnsiString& str, DoxCheck& value )
        {
            return TryParseDoxCheck( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxCheck& value )
    {
        return Doxygen::TryParseDoxCheck( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCheck, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxCheck( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCheck, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCheck( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxImageKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxImageKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxImageKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxImageKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxImageKind ParseDoxImageKind( const WideString& str );
        HCC_EXPORT DoxImageKind ParseDoxImageKind( const WideString& str, DoxImageKind defaultResult );
        HCC_EXPORT bool TryParseDoxImageKind( const WideString& str, DoxImageKind& value );

        inline DoxImageKind ParseDoxImageKind( const AnsiString& str )
        {
            return ParseDoxImageKind( ToWideString( str ) );
        }
        inline DoxImageKind ParseDoxImageKind( const AnsiString& str, DoxImageKind defaultResult )
        {
            return ParseDoxImageKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxImageKind( const AnsiString& str, DoxImageKind& value )
        {
            return TryParseDoxImageKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxImageKind& value )
    {
        return Doxygen::TryParseDoxImageKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxImageKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxImageKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxImageKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxImageKind( str );
    }



    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxPlantumlEngine value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxPlantumlEngine value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxPlantumlEngine value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxPlantumlEngine value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxPlantumlEngine ParseDoxPlantumlEngine( const WideString& str );
        HCC_EXPORT DoxPlantumlEngine ParseDoxPlantumlEngine( const WideString& str, DoxPlantumlEngine defaultResult );
        HCC_EXPORT bool TryParseDoxPlantumlEngine( const WideString& str, DoxPlantumlEngine& value );

        inline DoxPlantumlEngine ParseDoxPlantumlEngine( const AnsiString& str )
        {
            return ParseDoxPlantumlEngine( ToWideString( str ) );
        }
        inline DoxPlantumlEngine ParseDoxPlantumlEngine( const AnsiString& str, DoxPlantumlEngine defaultResult )
        {
            return ParseDoxPlantumlEngine( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxPlantumlEngine( const AnsiString& str, DoxPlantumlEngine& value )
        {
            return TryParseDoxPlantumlEngine( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxPlantumlEngine& value )
    {
        return Doxygen::TryParseDoxPlantumlEngine( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxPlantumlEngine, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxPlantumlEngine( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxPlantumlEngine, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxPlantumlEngine( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxParamListKind value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxParamListKind value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxParamListKind value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxParamListKind value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxParamListKind ParseDoxParamListKind( const WideString& str );
        HCC_EXPORT DoxParamListKind ParseDoxParamListKind( const WideString& str, DoxParamListKind defaultResult );
        HCC_EXPORT bool TryParseDoxParamListKind( const WideString& str, DoxParamListKind& value );

        inline DoxParamListKind ParseDoxParamListKind( const AnsiString& str )
        {
            return ParseDoxParamListKind( ToWideString( str ) );
        }
        inline DoxParamListKind ParseDoxParamListKind( const AnsiString& str, DoxParamListKind defaultResult )
        {
            return ParseDoxParamListKind( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxParamListKind( const AnsiString& str, DoxParamListKind& value )
        {
            return TryParseDoxParamListKind( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxParamListKind& value )
    {
        return Doxygen::TryParseDoxParamListKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxParamListKind, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxParamListKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamListKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamListKind( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxParamDir value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxParamDir value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxParamDir value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxParamDir value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxParamDir ParseDoxParamDir( const WideString& str );
        HCC_EXPORT DoxParamDir ParseDoxParamDir( const WideString& str, DoxParamDir defaultResult );
        HCC_EXPORT bool TryParseDoxParamDir( const WideString& str, DoxParamDir& value );

        inline DoxParamDir ParseDoxParamDir( const AnsiString& str )
        {
            return ParseDoxParamDir( ToWideString( str ) );
        }
        inline DoxParamDir ParseDoxParamDir( const AnsiString& str, DoxParamDir defaultResult )
        {
            return ParseDoxParamDir( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxParamDir( const AnsiString& str, DoxParamDir& value )
        {
            return TryParseDoxParamDir( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxParamDir& value )
    {
        return Doxygen::TryParseDoxParamDir( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxParamDir, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxParamDir( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamDir, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamDir( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxAccessor value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxAccessor value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxAccessor value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxAccessor value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxAccessor ParseDoxAccessor( const WideString& str );
        HCC_EXPORT DoxAccessor ParseDoxAccessor( const WideString& str, DoxAccessor defaultResult );
        HCC_EXPORT bool TryParseDoxAccessor( const WideString& str, DoxAccessor& value );

        inline DoxAccessor ParseDoxAccessor( const AnsiString& str )
        {
            return ParseDoxAccessor( ToWideString( str ) );
        }
        inline DoxAccessor ParseDoxAccessor( const AnsiString& str, DoxAccessor defaultResult )
        {
            return ParseDoxAccessor( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxAccessor( const AnsiString& str, DoxAccessor& value )
        {
            return TryParseDoxAccessor( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxAccessor& value )
    {
        return Doxygen::TryParseDoxAccessor( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxAccessor, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxAccessor( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAccessor, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAccessor( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxAlign value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxAlign value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxAlign value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxAlign value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxAlign ParseDoxAlign( const WideString& str );
        HCC_EXPORT DoxAlign ParseDoxAlign( const WideString& str, DoxAlign defaultResult );
        HCC_EXPORT bool TryParseDoxAlign( const WideString& str, DoxAlign& value );

        inline DoxAlign ParseDoxAlign( const AnsiString& str )
        {
            return ParseDoxAlign( ToWideString( str ) );
        }
        inline DoxAlign ParseDoxAlign( const AnsiString& str, DoxAlign defaultResult )
        {
            return ParseDoxAlign( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxAlign( const AnsiString& str, DoxAlign& value )
        {
            return TryParseDoxAlign( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxAlign& value )
    {
        return Doxygen::TryParseDoxAlign( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxAlign, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAlign( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxVerticalAlign value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxVerticalAlign value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxVerticalAlign value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxVerticalAlign value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxVerticalAlign ParseDoxVerticalAlign( const WideString& str );
        HCC_EXPORT DoxVerticalAlign ParseDoxVerticalAlign( const WideString& str, DoxVerticalAlign defaultResult );
        HCC_EXPORT bool TryParseDoxVerticalAlign( const WideString& str, DoxVerticalAlign& value );

        inline DoxVerticalAlign ParseDoxVerticalAlign( const AnsiString& str )
        {
            return ParseDoxVerticalAlign( ToWideString( str ) );
        }
        inline DoxVerticalAlign ParseDoxVerticalAlign( const AnsiString& str, DoxVerticalAlign defaultResult )
        {
            return ParseDoxVerticalAlign( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxVerticalAlign( const AnsiString& str, DoxVerticalAlign& value )
        {
            return TryParseDoxVerticalAlign( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxVerticalAlign& value )
    {
        return Doxygen::TryParseDoxVerticalAlign( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxVerticalAlign, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxVerticalAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVerticalAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVerticalAlign( str );
    }

    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxOlType value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxOlType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxOlType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxOlType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxOlType ParseDoxOlType( const WideString& str );
        HCC_EXPORT DoxOlType ParseDoxOlType( const WideString& str, DoxOlType defaultResult );
        HCC_EXPORT bool TryParseDoxOlType( const WideString& str, DoxOlType& value );

        inline DoxOlType ParseDoxOlType( const AnsiString& str )
        {
            return ParseDoxOlType( ToWideString( str ) );
        }
        inline DoxOlType ParseDoxOlType( const AnsiString& str, DoxOlType defaultResult )
        {
            return ParseDoxOlType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxOlType( const AnsiString& str, DoxOlType& value )
        {
            return TryParseDoxOlType( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxOlType& value )
    {
        return Doxygen::TryParseDoxOlType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxOlType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Doxygen::ParseDoxOlType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxOlType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxOlType( str );
    }


}

#endif
