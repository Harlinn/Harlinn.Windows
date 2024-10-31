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

#include <HCCXml.h>


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
    class SpType;
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

    /////////////////////////////////


    class DocBaseType : std::enable_shared_from_this<DocBaseType>
    {
    public:
        using XmlNode = Xml::Dom::Node;
        using XmlNodeType = Xml::Dom::NodeType;
        using XmlElement = Xml::Dom::Element;
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
        HCC_EXPORT explicit DocEmojiType( const XmlElement& xmlElement );

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
        HCC_EXPORT explicit TableOfContentsKindType( const XmlElement& xmlElement );


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
        HCC_EXPORT explicit TableOfContentsType( const XmlElement& xmlElement );

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
        HCC_EXPORT explicit DocEmptyType( const XmlElement& xmlElement );
    };

    class DocParBlockType : public Internal::DocBase<Doxygen::DoxType::DocParBlockType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParBlockType>;

        DocParBlockType( ) = default;
        HCC_EXPORT explicit DocParBlockType( const XmlElement& xmlElement );
    };

    class DocBlockQuoteType : public Internal::DocBase<Doxygen::DoxType::DocBlockQuoteType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocBlockQuoteType>;

        DocBlockQuoteType( ) = default;
        HCC_EXPORT explicit DocBlockQuoteType( const XmlElement& xmlElement );
    };

    class DocDetailsType : public Internal::DocBase<Doxygen::DoxType::DocDetailsType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocDetailsType>;

        DocDetailsType( ) = default;
        HCC_EXPORT explicit DocDetailsType( const XmlElement& xmlElement );

    };


    class DocCopyType : public Internal::DocBase<Doxygen::DoxType::DocCopyType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCopyType>;

        DocCopyType( ) = default;
        HCC_EXPORT explicit DocCopyType( const XmlElement& xmlElement );

    };

    class DocXRefSectType : public Internal::DocBase<Doxygen::DoxType::DocXRefSectType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocXRefSectType>;

        DocXRefSectType( ) = default;
        HCC_EXPORT explicit DocXRefSectType( const XmlElement& xmlElement );

    };

    class DocParamName : public Internal::DocBase<Doxygen::DoxType::DocParamName>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamName>;

        DocParamName( ) = default;
        HCC_EXPORT explicit DocParamName( const XmlElement& xmlElement );
    };

    class DocParamType : public Internal::DocBase<Doxygen::DoxType::DocParamType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamType>;

        DocParamType( ) = default;
        HCC_EXPORT explicit DocParamType( const XmlElement& xmlElement );
    };

    class DocParamNameList : public Internal::DocBase<Doxygen::DoxType::DocParamNameList>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamNameList>;

        DocParamNameList( ) = default;
        HCC_EXPORT explicit DocParamNameList( const XmlElement& xmlElement );
    };

    class DocParamListItem : public Internal::DocBase<Doxygen::DoxType::DocParamListItem>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamListItem>;

        DocParamListItem( ) = default;
        HCC_EXPORT explicit DocParamListItem( const XmlElement& xmlElement );
    };

    class DocParamListType : public Internal::DocBase<Doxygen::DoxType::DocParamListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParamListType>;

        DocParamListType( ) = default;
        HCC_EXPORT explicit DocParamListType( const XmlElement& xmlElement );
    };

    class DocLanguageType : public Internal::DocBase<Doxygen::DoxType::DocLanguageType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocLanguageType>;

        DocLanguageType( ) = default;
        HCC_EXPORT explicit DocLanguageType( const XmlElement& xmlElement );
    };


    class DocTocListType : public Internal::DocBase<Doxygen::DoxType::DocTocListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTocListType>;

        DocTocListType( ) = default;
        HCC_EXPORT explicit DocTocListType( const XmlElement& xmlElement );
    };

    class DocTocItemType : public Internal::DocBase<Doxygen::DoxType::DocTocItemType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTocItemType>;

        DocTocItemType( ) = default;
        HCC_EXPORT explicit DocTocItemType( const XmlElement& xmlElement );
    };

    class DocPlantumlType : public Internal::DocBase<Doxygen::DoxType::DocPlantumlType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocPlantumlType>;

        DocPlantumlType( ) = default;
        HCC_EXPORT explicit DocPlantumlType( const XmlElement& xmlElement );
    };

    class DocImageFileType : public Internal::DocBase<Doxygen::DoxType::DocImageFileType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocImageFileType>;

        DocImageFileType( ) = default;
        HCC_EXPORT explicit DocImageFileType( const XmlElement& xmlElement );
    };

    class DocDotMscType : public Internal::DocBase<Doxygen::DoxType::DocDotMscType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocDotMscType>;

        DocDotMscType( ) = default;
        HCC_EXPORT explicit DocDotMscType( const XmlElement& xmlElement );
    };

    class DocImageType : public Internal::DocBase<Doxygen::DoxType::DocImageType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocImageType>;

        DocImageType( ) = default;
        HCC_EXPORT explicit DocImageType( const XmlElement& xmlElement );

    };


    class DocHeadingType : public Internal::DocBase<Doxygen::DoxType::DocHeadingType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHeadingType>;

        DocHeadingType( ) = default;
        HCC_EXPORT explicit DocHeadingType( const XmlElement& xmlElement );

    };

    class DocCaptionType : public Internal::DocBase<Doxygen::DoxType::DocCaptionType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCaptionType>;

        DocCaptionType( ) = default;
        HCC_EXPORT explicit DocCaptionType( const XmlElement& xmlElement );
    };

    class DocEntryType : public Internal::DocBase<Doxygen::DoxType::DocEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocEntryType>;

        DocEntryType( ) = default;
        HCC_EXPORT explicit DocEntryType( const XmlElement& xmlElement );
    };

    class DocRowType : public Internal::DocBase<Doxygen::DoxType::DocRowType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRowType>;

        DocRowType( ) = default;
        HCC_EXPORT explicit DocRowType( const XmlElement& xmlElement );
    };

    class DocTableType : public Internal::DocBase<Doxygen::DoxType::DocTableType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTableType>;

        DocTableType( ) = default;
        HCC_EXPORT explicit DocTableType( const XmlElement& xmlElement );
    };

    class DocRefTextType : public Internal::DocBase<Doxygen::DoxType::DocRefTextType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRefTextType>;

        DocRefTextType( ) = default;
        HCC_EXPORT explicit DocRefTextType( const XmlElement& xmlElement );
    };

    class DocVariableListType : public Internal::DocBase<Doxygen::DoxType::DocVariableListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListType>;

        DocVariableListType( ) = default;
        HCC_EXPORT explicit DocVariableListType( const XmlElement& xmlElement );
    };

    class DocVariableListGroup : public Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>;

        DocVariableListGroup( ) = default;
        HCC_EXPORT explicit DocVariableListGroup( const XmlElement& xmlElement );
    };

    class DocVarListEntryType : public Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>;

        DocVarListEntryType( ) = default;
        HCC_EXPORT explicit DocVarListEntryType( const XmlElement& xmlElement );
    };

    class DocSimpleSectType : public Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>;

        DocSimpleSectType( ) = default;
        HCC_EXPORT explicit DocSimpleSectType( const XmlElement& xmlElement );
    };

    class DocListItemType : public Internal::DocBase<Doxygen::DoxType::DocListItemType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListItemType>;

        DocListItemType( ) = default;
        HCC_EXPORT explicit DocListItemType( const XmlElement& xmlElement );
    };

    class DocListType : public Internal::DocBase<Doxygen::DoxType::DocListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListType>;

        DocListType( ) = default;
        HCC_EXPORT explicit DocListType( const XmlElement& xmlElement );
    };

    class DocIndexEntryType : public Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>;

        DocIndexEntryType( ) = default;
        HCC_EXPORT explicit DocIndexEntryType( const XmlElement& xmlElement );
    };

    class DocFormulaType : public Internal::DocBase<Doxygen::DoxType::DocFormulaType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocFormulaType>;

        DocFormulaType( ) = default;
        HCC_EXPORT explicit DocFormulaType( const XmlElement& xmlElement );
    };

    class DocAnchorType : public Internal::DocBase<Doxygen::DoxType::DocAnchorType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocAnchorType>;

        DocAnchorType( ) = default;
        HCC_EXPORT explicit DocAnchorType( const XmlElement& xmlElement );

    };

    class DocURLLink : public Internal::DocBase<Doxygen::DoxType::DocURLLink>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocURLLink>;

        DocURLLink( ) = default;
        HCC_EXPORT explicit DocURLLink( const XmlElement& xmlElement );
    };

    class DocMarkupType : public Internal::DocBase<Doxygen::DoxType::DocMarkupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocMarkupType>;

        DocMarkupType( ) = default;
        HCC_EXPORT explicit DocMarkupType( const XmlElement& xmlElement );
    };


    class DocParaType : public Internal::DocBase<Doxygen::DoxType::DocParaType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParaType>;

        DocParaType( ) = default;
        HCC_EXPORT explicit DocParaType( const XmlElement& xmlElement );
    };

    class DocCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocCmdGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCmdGroup>;

        DocCmdGroup( ) = default;
        HCC_EXPORT explicit DocCmdGroup( const XmlElement& xmlElement );
    };

    class DocSummaryType : public Internal::DocBase<Doxygen::DoxType::DocSummaryType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSummaryType>;

        DocSummaryType( ) = default;
        HCC_EXPORT explicit DocSummaryType( const XmlElement& xmlElement );
    };

    class DocTitleType : public Internal::DocBase<Doxygen::DoxType::DocTitleType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleType>;

        DocTitleType( ) = default;
        HCC_EXPORT explicit DocTitleType( const XmlElement& xmlElement );
    };

    class DocTitleCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>;

        DocTitleCmdGroup( ) = default;
        HCC_EXPORT explicit DocTitleCmdGroup( const XmlElement& xmlElement );
    };

    class DocInternalS6Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS6Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS6Type>;

        DocInternalS6Type( ) = default;
        HCC_EXPORT explicit DocInternalS6Type( const XmlElement& xmlElement );
    };

    class DocInternalS5Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS5Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS5Type>;

        DocInternalS5Type( ) = default;
        HCC_EXPORT explicit DocInternalS5Type( const XmlElement& xmlElement );
    };

    class DocInternalS4Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS4Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS4Type>;

        DocInternalS4Type( ) = default;
        HCC_EXPORT explicit DocInternalS4Type( const XmlElement& xmlElement );
    };

    class DocInternalS3Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS3Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS3Type>;

        DocInternalS3Type( ) = default;
        HCC_EXPORT explicit DocInternalS3Type( const XmlElement& xmlElement );
    };

    class DocInternalS2Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS2Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS2Type>;

        DocInternalS2Type( ) = default;
        HCC_EXPORT explicit DocInternalS2Type( const XmlElement& xmlElement );
    };

    class DocInternalS1Type : public Internal::DocBase<Doxygen::DoxType::DocInternalS1Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalS1Type>;

        DocInternalS1Type( ) = default;
        HCC_EXPORT explicit DocInternalS1Type( const XmlElement& xmlElement );
    };


    class DocInternalType : public Internal::DocBase<Doxygen::DoxType::DocInternalType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocInternalType>;

        DocInternalType( ) = default;
        HCC_EXPORT explicit DocInternalType( const XmlElement& xmlElement );
    };

    class DocSect6Type : public Internal::DocBase<Doxygen::DoxType::DocSect6Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect6Type>;

        DocSect6Type( ) = default;
        HCC_EXPORT explicit DocSect6Type( const XmlElement& xmlElement );
    };


    class DocSect5Type : public Internal::DocBase<Doxygen::DoxType::DocSect5Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect5Type>;

        DocSect5Type( ) = default;
        HCC_EXPORT explicit DocSect5Type( const XmlElement& xmlElement );
    };

    class DocSect4Type : public Internal::DocBase<Doxygen::DoxType::DocSect4Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect4Type>;

        DocSect4Type( ) = default;
        HCC_EXPORT explicit DocSect4Type( const XmlElement& xmlElement );
    };

    class DocSect3Type : public Internal::DocBase<Doxygen::DoxType::DocSect3Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect3Type>;

        DocSect3Type( ) = default;
        HCC_EXPORT explicit DocSect3Type( const XmlElement& xmlElement );
    };

    class DocSect2Type : public Internal::DocBase<Doxygen::DoxType::DocSect2Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect2Type>;

        DocSect2Type( ) = default;
        HCC_EXPORT explicit DocSect2Type( const XmlElement& xmlElement );
    };

    class DocSect1Type : public Internal::DocBase<Doxygen::DoxType::DocSect1Type>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSect1Type>;

        DocSect1Type( ) = default;
        HCC_EXPORT explicit DocSect1Type( const XmlElement& xmlElement );
    };

    class LocationType : public Internal::DocBase<Doxygen::DoxType::LocationType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LocationType>;

        LocationType( ) = default;
        HCC_EXPORT explicit LocationType( const XmlElement& xmlElement );
    };

    class ReferenceType : public Internal::DocBase<Doxygen::DoxType::ReferenceType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReferenceType>;

        ReferenceType( ) = default;
        HCC_EXPORT explicit ReferenceType( const XmlElement& xmlElement );
    };

    class SpType : public Internal::DocBase<Doxygen::DoxType::SpType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SpType>;

        SpType( ) = default;
        HCC_EXPORT explicit SpType( const XmlElement& xmlElement );
    };

    class HighlightType : public Internal::DocBase<Doxygen::DoxType::HighlightType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::HighlightType>;
        
        HighlightType( ) = default;
        HCC_EXPORT explicit HighlightType( const XmlElement& xmlElement );
    };

    class CodeLineType : public Internal::DocBase<Doxygen::DoxType::CodeLineType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CodeLineType>;

        CodeLineType( ) = default;
        HCC_EXPORT explicit CodeLineType( const XmlElement& xmlElement );
    };

    class ListingType : public Internal::DocBase<Doxygen::DoxType::ListingType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ListingType>;

        ListingType( ) = default;
        HCC_EXPORT explicit ListingType( const XmlElement& xmlElement );
    };

    class LinkType : public Internal::DocBase<Doxygen::DoxType::LinkType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LinkType>;

        LinkType( ) = default;
        HCC_EXPORT explicit LinkType( const XmlElement& xmlElement );
    };

    class ChildNodeType : public Internal::DocBase<Doxygen::DoxType::ChildNodeType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ChildNodeType>;

        ChildNodeType( ) = default;
        HCC_EXPORT explicit ChildNodeType( const XmlElement& xmlElement );
    };

    class NodeType : public Internal::DocBase<Doxygen::DoxType::NodeType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::NodeType>;

        NodeType( ) = default;
        HCC_EXPORT explicit NodeType( const XmlElement& xmlElement );
    };

    class GraphType : public Internal::DocBase<Doxygen::DoxType::GraphType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::GraphType>;

        GraphType( ) = default;
        HCC_EXPORT explicit GraphType( const XmlElement& xmlElement );
    };

    class LinkedTextType : public Internal::DocBase<Doxygen::DoxType::LinkedTextType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LinkedTextType>;

        LinkedTextType( ) = default;
        HCC_EXPORT explicit LinkedTextType( const XmlElement& xmlElement );
    };

    class ParamType : public Internal::DocBase<Doxygen::DoxType::ParamType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ParamType>;

        ParamType( ) = default;
        HCC_EXPORT explicit ParamType( const XmlElement& xmlElement );
    };


    class TemplateParamListType : public Internal::DocBase<Doxygen::DoxType::TemplateParamListType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TemplateParamListType>;

        TemplateParamListType( ) = default;
        HCC_EXPORT explicit TemplateParamListType( const XmlElement& xmlElement );
    };

    class EnumvalueType : public Internal::DocBase<Doxygen::DoxType::EnumvalueType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::EnumvalueType>;

        EnumvalueType( ) = default;
        HCC_EXPORT explicit EnumvalueType( const XmlElement& xmlElement );
    };

    class DescriptionType : public Internal::DocBase<Doxygen::DoxType::DescriptionType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DescriptionType>;

        DescriptionType( ) = default;
        HCC_EXPORT explicit DescriptionType( const XmlElement& xmlElement );
    };


    class MemberDefType : public Internal::DocBase<Doxygen::DoxType::MemberDefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberDefType>;

        MemberDefType( ) = default;
        HCC_EXPORT explicit MemberDefType( const XmlElement& xmlElement );
    };

    class SectionDefType : public Internal::DocBase<Doxygen::DoxType::SectionDefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SectionDefType>;

        SectionDefType( ) = default;
        HCC_EXPORT explicit SectionDefType( const XmlElement& xmlElement );
    };

    class MemberType : public Internal::DocBase<Doxygen::DoxType::MemberType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberType>;

        MemberType( ) = default;
        HCC_EXPORT explicit MemberType( const XmlElement& xmlElement );
    };

    class RefTextType : public Internal::DocBase<Doxygen::DoxType::RefTextType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefTextType>;

        RefTextType( ) = default;
        HCC_EXPORT explicit RefTextType( const XmlElement& xmlElement );
    };

    class RefType : public Internal::DocBase<Doxygen::DoxType::RefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefType>;

        RefType( ) = default;
        HCC_EXPORT explicit RefType( const XmlElement& xmlElement );
    };


    class ExportType : public Internal::DocBase<Doxygen::DoxType::ExportType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ExportType>;

        ExportType( ) = default;
        HCC_EXPORT explicit ExportType( const XmlElement& xmlElement );
    };

    class ExportsType : public Internal::DocBase<Doxygen::DoxType::ExportsType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ExportsType>;

        ExportsType( ) = default;
        HCC_EXPORT explicit ExportsType( const XmlElement& xmlElement );
    };

    class IncType : public Internal::DocBase<Doxygen::DoxType::IncType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::IncType>;

        IncType( ) = default;
        HCC_EXPORT explicit IncType( const XmlElement& xmlElement );
    };

    class ReimplementType : public Internal::DocBase<Doxygen::DoxType::ReimplementType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReimplementType>;

        ReimplementType( ) = default;
        HCC_EXPORT explicit ReimplementType( const XmlElement& xmlElement );
    };


    class CompoundRefType : public Internal::DocBase<Doxygen::DoxType::CompoundRefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CompoundRefType>;

        CompoundRefType( ) = default;
        HCC_EXPORT explicit CompoundRefType( const XmlElement& xmlElement );
    };


    class DocHtmlOnlyType : public Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>;

        DocHtmlOnlyType( ) = default;
        HCC_EXPORT explicit DocHtmlOnlyType( const XmlElement& xmlElement );
    };


    class MemberRefType : public Internal::DocBase<Doxygen::DoxType::MemberRefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberRefType>;

        MemberRefType( ) = default;
        HCC_EXPORT explicit MemberRefType( const XmlElement& xmlElement );
    };


    class ListOfAllMembersType : public Internal::DocBase<Doxygen::DoxType::ListOfAllMembersType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ListOfAllMembersType>;

        ListOfAllMembersType( ) = default;
        HCC_EXPORT explicit ListOfAllMembersType( const XmlElement& xmlElement );
    };


    class CompoundDefType : public Internal::DocBase<Doxygen::DoxType::CompoundDefType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CompoundDefType>;

        CompoundDefType( ) = default;
        HCC_EXPORT explicit CompoundDefType( const XmlElement& xmlElement );
    };

    class Document : public Internal::DocBase<Doxygen::DoxType::Document>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::Document>;

        Document( ) = default;
        HCC_EXPORT explicit Document( const XmlElement& xmlElement );
    };

    class DocumentCollection : public Internal::DocBase<Doxygen::DoxType::DocumentCollection>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocumentCollection>;

        DocumentCollection( ) = default;
        HCC_EXPORT explicit DocumentCollection( const XmlElement& xmlElement );

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
