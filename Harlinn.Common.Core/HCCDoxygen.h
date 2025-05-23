#pragma once
#ifndef HCCDOXYGEN_H_
#define HCCDOXYGEN_H_

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
    template<typename Ch = char>
    class XmlParser;
}

namespace Harlinn::Common::Core::Doxygen
{
    namespace Structure
    {
        class TypeSystem;
    }
    

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
        TextType,
        TitleType,
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
     
    class TextType;
    class TitleType;
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

    using TextTypePtr = std::shared_ptr<TextType>;
    using TitleTypePtr = std::shared_ptr<TitleType>;
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
    using SpTypePtr = std::shared_ptr<SpType>;
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


    enum class DoxCmdGroupType
    {
        Unknown,
        ulink,//DocURLLink
        bold,//DocMarkupType 
        s,//DocMarkupType
        strike,//DocMarkupType
        underline,//DocMarkupType
        emphasis,//DocMarkupType
        computeroutput,//DocMarkupType
        subscript,//DocMarkupType
        superscript,//DocMarkupType
        center,//DocMarkupType
        Small,//DocMarkupType
        cite,//DocMarkupType
        del,//DocMarkupType
        ins,//DocMarkupType
        htmlonly,//DocHtmlOnlyType
        manonly,//TextType
        xmlonly,//TextType
        rtfonly,//TextType
        latexonly,//TextType
        docbookonly,//TextType
        image,//DocImageType
        dot,//DocDotMscType
        msc,//DocDotMscType
        plantuml,//DocPlantumlType
        anchor,//DocAnchorType
        formula,//DocFormulaType
        ref,//DocRefTextType
        emoji,//DocEmojiType
        linebreak,
        nonbreakablespace,
        iexcl,
        cent,
        pound,
        curren,
        yen,
        brvbar,
        sect,
        umlaut,
        copy,
        ordf,
        laquo,
        Not,
        shy,
        registered,
        macr,
        deg,
        plusmn,
        sup2,
        sup3,
        acute,
        micro,
        para,
        middot,
        cedil,
        sup1,
        ordm,
        raquo,
        frac14,
        frac12,
        frac34,
        iquest,
        Agrave,
        Aacute,
        Acirc,
        Atilde,
        Aumlaut,
        Aring,
        AElig,
        Ccedil,
        Egrave,
        Eacute,
        Ecirc,
        Eumlaut,
        Igrave,
        Iacute,
        Icirc,
        Iumlaut,
        ETH,
        Ntilde,
        Ograve,
        Oacute,
        Ocirc,
        Otilde,
        Oumlaut,
        times,
        Oslash,
        Ugrave,
        Uacute,
        Ucirc,
        Uumlaut,
        Yacute,
        THORN,
        szlig,
        agrave,
        aacute,
        acirc,
        atilde,
        aumlaut,
        aring,
        aelig,
        ccedil,
        egrave,
        eacute,
        ecirc,
        eumlaut,
        igrave,
        iacute,
        icirc,
        iumlaut,
        eth,
        ntilde,
        ograve,
        oacute,
        ocirc,
        otilde,
        oumlaut,
        divide,
        oslash,
        ugrave,
        uacute,
        ucirc,
        uumlaut,
        yacute,
        thorn,
        yumlaut,
        fnof,
        Alpha,
        Beta,
        Gamma,
        Delta,
        Epsilon,
        Zeta,
        Eta,
        Theta,
        Iota,
        Kappa,
        Lambda,
        Mu,
        Nu,
        Xi,
        Omicron,
        Pi,
        Rho,
        Sigma,
        Tau,
        Upsilon,
        Phi,
        Chi,
        Psi,
        Omega,
        alpha,
        beta,
        gamma,
        delta,
        epsilon,
        zeta,
        eta,
        theta,
        iota,
        kappa,
        lambda,
        mu,
        nu,
        xi,
        omicron,
        pi,
        rho,
        sigmaf,
        sigma,
        tau,
        upsilon,
        phi,
        chi,
        psi,
        omega,
        thetasym,
        upsih,
        piv,
        bull,
        hellip,
        prime,
        Prime,
        oline,
        frasl,
        weierp,
        imaginary,
        real,
        trademark,
        alefsym,
        larr,
        uarr,
        rarr,
        darr,
        harr,
        crarr,
        lArr,
        uArr,
        rArr,
        dArr,
        hArr,
        forall,
        part,
        exist,
        empty,
        nabla,
        isin,
        notin,
        ni,
        prod,
        sum,
        minus,
        lowast,
        radic,
        prop,
        infin,
        ang,
        And,
        Or ,
        cap,
        cup,
        Int,
        there4,
        sim,
        cong,
        asymp,
        ne,
        equiv,
        le,
        ge,
        sub,
        sup,
        nsub,
        sube,
        supe,
        oplus,
        otimes,
        perp,
        sdot,
        lceil,
        rceil,
        lfloor,
        rfloor,
        lang,
        rang,
        loz,
        spades,
        clubs,
        hearts,
        diams,
        OElig,
        oelig,
        Scaron,
        scaron,
        Yumlaut,
        circ,
        tilde,
        ensp,
        emsp,
        thinsp,
        zwnj,
        zwj,
        lrm,
        rlm,
        ndash,
        mdash,
        lsquo,
        rsquo,
        sbquo,
        ldquo,
        rdquo,
        bdquo,
        dagger,
        Dagger,
        permil,
        lsaquo,
        rsaquo,
        euro,
        tm,
        hruler,
        preformatted,//DocMarkupType
        programlisting,//ListingType
        verbatim,//TextType
        javadocliteral,//TextType
        javadoccode,//TextType
        indexentry,//DocIndexEntryType
        orderedlist,//DocListType
        itemizedlist,//DocListType
        simplesect,//DocSimpleSectType
        title,//DocTitleType
        variablelist,//DocVariableListType
        table,//DocTableType
        heading,//DocHeadingType
        dotfile,//DocImageFileType
        mscfile,//DocImageFileType
        diafile,//DocImageFileType
        toclist,//DocTocListType
        language,//DocLanguageType
        parameterlist,//DocParamListType
        xrefsect,//DocXRefSectType
        copydoc,//DocCopyType
        details,//DocDetailsType
        blockquote,//DocBlockQuoteType
        parblock, //DocParBlockType
        text // TextType

    };

    

    /////////////////////////////////

    class DocBaseType : std::enable_shared_from_this<DocBaseType>
    {
    public:
        using XmlNode = RapidXml::XmlNode<>;
        
        virtual ~DocBaseType( ) = default;
        virtual Doxygen::DoxType DoxType( ) const = 0;

    };

    using DocBaseTypePtr = std::shared_ptr<DocBaseType>;

    struct DocCmdGroupType
    {
        DoxCmdGroupType Type{};
        DocBaseTypePtr Value;
    };

    HCC_EXPORT bool TryParseCmdGroupType( const RapidXml::XmlNode<>& xmlNode, DocCmdGroupType& result );
    HCC_EXPORT bool TryParseTextOrCmdGroupType( const RapidXml::XmlNode<>& xmlNode, DocCmdGroupType& result );

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

    class TextType : public Internal::DocBase<Doxygen::DoxType::TextType>
    {
        WideString text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TextType>;

        TextType( ) = default;
        explicit TextType( const WideString& text )
            : text_( text )
        { }
        HCC_EXPORT explicit TextType( const XmlNode& xmlNode );

        const WideString& Text( ) const
        {
            return text_;
        }
    };

    class TitleType : public Internal::DocBase<Doxygen::DoxType::TitleType>
    {
        WideString text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TitleType>;

        TitleType( ) = default;
        HCC_EXPORT explicit TitleType( const XmlNode& xmlNode );

        const WideString& Text( ) const
        {
            return text_;
        }

    };

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

    class DocRefTextType : public Internal::DocBase<Doxygen::DoxType::DocRefTextType>, public std::vector<DocCmdGroupType>
    {
        WideString refId_;
        DoxRefKind kindRef_{};
        WideString external_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRefTextType>;

        DocRefTextType( ) = default;
        HCC_EXPORT explicit DocRefTextType( const XmlNode& xmlNode );

        const WideString& RefId() const { return refId_; }
        DoxRefKind KindRef() const { return kindRef_; }
        const WideString& External( ) const { return external_; }

    };

    class DocVariableListType : public Internal::DocBase<Doxygen::DoxType::DocVariableListType>, public std::vector<DocVariableListGroupPtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListType>;

        DocVariableListType( ) = default;
        HCC_EXPORT explicit DocVariableListType( const XmlNode& xmlNode );
    };

    class DocVariableListGroup : public Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>
    {
        DocVarListEntryTypePtr varListEntry_;
        DocListItemTypePtr listItem_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListGroup>;

        DocVariableListGroup( ) = default;
        HCC_EXPORT explicit DocVariableListGroup( const XmlNode& xmlNode );

        const DocVarListEntryTypePtr& VarListEntry( ) const { return varListEntry_; }
        const DocListItemTypePtr& ListItem( ) const { return listItem_; }

    };

    class DocVarListEntryType : public Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>
    {
        DocTitleTypePtr term_;

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVarListEntryType>;

        DocVarListEntryType( ) = default;
        HCC_EXPORT explicit DocVarListEntryType( const XmlNode& xmlNode );

        const DocTitleTypePtr& Term( ) const { return term_; }
    };

    class DocSimpleSectType : public Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>, public std::vector<DocParaTypePtr>
    {
        DoxSimpleSectKind kind_;
        DocTitleTypePtr title_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSimpleSectType>;

        DocSimpleSectType( ) = default;
        HCC_EXPORT explicit DocSimpleSectType( const XmlNode& xmlNode );

        DoxSimpleSectKind kind() const { return kind_; }
        const DocTitleTypePtr& title( ) const { return title_; }

    };

    class DocListItemType : public Internal::DocBase<Doxygen::DoxType::DocListItemType>, public std::vector<DocParaTypePtr>
    {
        DoxCheck override_;
        Int32 value_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListItemType>;

        DocListItemType( ) = default;
        HCC_EXPORT explicit DocListItemType( const XmlNode& xmlNode );

        DoxCheck Override() const { return override_; }
        Int32 Value( ) const { return value_; }

    };

    class DocListType : public Internal::DocBase<Doxygen::DoxType::DocListType>, public std::vector<DocListItemTypePtr>
    {
        DoxOlType type_;
        Int32 start_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocListType>;

        DocListType( ) = default;
        HCC_EXPORT explicit DocListType( const XmlNode& xmlNode );

        DoxOlType Type() const { return type_; }
        Int32 Start( ) const { return start_; }

    };

    class DocIndexEntryType : public Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>
    {
        WideString primary_;
        WideString secondary_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>;

        DocIndexEntryType( ) = default;
        HCC_EXPORT explicit DocIndexEntryType( const XmlNode& xmlNode );

        const WideString& Primary( ) const { return primary_; }
        const WideString& Secondary( ) const { return secondary_; }

    };

    class DocFormulaType : public Internal::DocBase<Doxygen::DoxType::DocFormulaType>
    {
        WideString id_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocFormulaType>;

        DocFormulaType( ) = default;
        HCC_EXPORT explicit DocFormulaType( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Content( ) const { return content_; }
    };

    class DocAnchorType : public Internal::DocBase<Doxygen::DoxType::DocAnchorType>
    {
        WideString id_;
        WideString content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocAnchorType>;

        DocAnchorType( ) = default;
        HCC_EXPORT explicit DocAnchorType( const XmlNode& xmlNode );

        const WideString& Id( ) const { return id_; }
        const WideString& Content( ) const { return content_; }
    };

    class DocURLLink : public Internal::DocBase<Doxygen::DoxType::DocURLLink>, public std::vector<DocCmdGroupType>
    {
        WideString url_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocURLLink>;

        DocURLLink( ) = default;
        HCC_EXPORT explicit DocURLLink( const XmlNode& xmlNode );

        const WideString& Url( ) const { return url_; }
    };

    class DocMarkupType : public Internal::DocBase<Doxygen::DoxType::DocMarkupType>, public std::vector<DocCmdGroupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocMarkupType>;

        DocMarkupType( ) = default;
        HCC_EXPORT explicit DocMarkupType( const XmlNode& xmlNode );
    };


    class DocParaType : public Internal::DocBase<Doxygen::DoxType::DocParaType>, public std::vector<DocCmdGroupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocParaType>;

        DocParaType( ) = default;
        HCC_EXPORT explicit DocParaType( const XmlNode& xmlNode );
    };
    /*
    class DocCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocCmdGroup>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCmdGroup>;

        DocCmdGroup( ) = default;
        HCC_EXPORT explicit DocCmdGroup( const XmlNode& xmlNode );
    };
    */

    class DocSummaryType : public Internal::DocBase<Doxygen::DoxType::DocSummaryType>, public std::vector<DocCmdGroupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocSummaryType>;

        DocSummaryType( ) = default;
        HCC_EXPORT explicit DocSummaryType( const XmlNode& xmlNode );
    };

    class DocTitleType : public Internal::DocBase<Doxygen::DoxType::DocTitleType>, public std::vector<DocCmdGroupType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleType>;

        DocTitleType( ) = default;
        HCC_EXPORT explicit DocTitleType( const XmlNode& xmlNode );
    };

    /*
    class DocTitleCmdGroup : public Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>
    {

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocTitleCmdGroup>;

        DocTitleCmdGroup( ) = default;
        HCC_EXPORT explicit DocTitleCmdGroup( const XmlNode& xmlNode );
    };
    */
    namespace Internal
    {
        template<Doxygen::DoxType doxType>
        class DocInternalSectionBaseType : public DocBase<doxType>, public std::vector<DocBaseTypePtr>
        {
        public:
            using Base = DocBase<doxType>;
            using Base::XmlNode;
            using BaseVector = std::vector<DocBaseTypePtr>;
            using BaseVector::emplace_back;
            using ParaType = DocParaType;

            using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
        protected:
            WideString id_;
            TitleTypePtr title_;
            ParaTypeVector para_;
        public:
            DocInternalSectionBaseType( ) = default;
            HCC_EXPORT explicit DocInternalSectionBaseType( const XmlNode& xmlNode );

            const WideString& Id( ) const { return id_; }
            const TitleTypePtr& Title( ) const { return title_; }
            const ParaTypeVector& Para( ) const { return para_; }
        };

        template<Doxygen::DoxType doxType, typename SubSectT>
        class DocInternalSectionType : public DocInternalSectionBaseType<doxType>
        {
        public:
            using Base = DocInternalSectionBaseType<doxType>;
            using XmlNode = typename Base::XmlNode;
            using ParaType = typename Base::ParaType;
            using SubSectType = SubSectT;

            using ParaTypeVector = typename Base::ParaTypeVector;
            using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
        protected:
            using BaseVector = typename Base::BaseVector;
            using BaseVector::emplace_back;
            using Base::id_;
            using Base::title_;
            using Base::para_;
        private:
            SubSectTypeVector subSections_;
        public:
            DocInternalSectionType( ) = default;
            HCC_EXPORT explicit DocInternalSectionType( const XmlNode& xmlNode, std::string_view subSectionElementName );

            const SubSectTypeVector& SubSections( ) const { return subSections_; }
        };
    }


    class DocInternalS6Type : public Internal::DocInternalSectionBaseType<Doxygen::DoxType::DocInternalS6Type>
    {
    public:
        using Base = Internal::DocInternalSectionBaseType<Doxygen::DoxType::DocInternalS6Type>;

        DocInternalS6Type( ) = default;
        HCC_EXPORT explicit DocInternalS6Type( const XmlNode& xmlNode );
    };

    class DocInternalS5Type : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS5Type, DocInternalS6Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS5Type, DocInternalS6Type>;

        DocInternalS5Type( ) = default;
        HCC_EXPORT explicit DocInternalS5Type( const XmlNode& xmlNode );
    };

    class DocInternalS4Type : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS4Type, DocInternalS5Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS4Type, DocInternalS5Type>;

        DocInternalS4Type( ) = default;
        HCC_EXPORT explicit DocInternalS4Type( const XmlNode& xmlNode );
    };

    class DocInternalS3Type : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS3Type, DocInternalS4Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS3Type, DocInternalS4Type>;

        DocInternalS3Type( ) = default;
        HCC_EXPORT explicit DocInternalS3Type( const XmlNode& xmlNode );
    };

    class DocInternalS2Type : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS2Type, DocInternalS3Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS2Type, DocInternalS3Type>;

        DocInternalS2Type( ) = default;
        HCC_EXPORT explicit DocInternalS2Type( const XmlNode& xmlNode );
    };

    class DocInternalS1Type : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS1Type, DocInternalS2Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalS1Type, DocInternalS2Type>;

        DocInternalS1Type( ) = default;
        HCC_EXPORT explicit DocInternalS1Type( const XmlNode& xmlNode );
    };

    class DocInternalType : public Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalType, DocInternalS1Type>
    {
    public:
        using Base = Internal::DocInternalSectionType<Doxygen::DoxType::DocInternalType, DocInternalS1Type>;

        DocInternalType( ) = default;
        HCC_EXPORT explicit DocInternalType( const XmlNode& xmlNode );
    };

    namespace Internal
    {
        template<Doxygen::DoxType doxType, typename InternalT>
        class DocSectionBaseType : public DocBase<doxType>, public std::vector<DocBaseTypePtr>
        {
        public:
            using Base = DocBase<doxType>;
            using Base::XmlNode;
            using BaseVector = std::vector<DocBaseTypePtr>;
            using BaseVector::emplace_back;
            using ParaType = DocParaType;
            using InternalType = InternalT;

            using ParaTypeVector = std::vector<std::shared_ptr<ParaType>>;
            using InternalTypeVector = std::vector<std::shared_ptr<InternalType>>;
        protected:
            WideString id_;
            TitleTypePtr title_;
            ParaTypeVector para_;
            InternalTypeVector internal_;
        public:
            DocSectionBaseType( ) = default;
            HCC_EXPORT explicit DocSectionBaseType( const XmlNode& xmlNode );

            const WideString& Id( ) const { return id_; }
            const TitleTypePtr& Title( ) const { return title_; }
            const ParaTypeVector& Para( ) const { return para_; }
            const InternalTypeVector& Internal( ) const { return internal_; }
        };

        template<Doxygen::DoxType doxType, typename InternalT, typename SubSectT  >
        class DocSectionType : public DocSectionBaseType<doxType, InternalT>
        {
        public:
            using Base = DocSectionBaseType<doxType, InternalT>;
            using XmlNode = typename Base::XmlNode;
            using ParaType = typename Base::ParaType;
            using InternalType = typename Base::InternalType;
            using SubSectType = SubSectT;

            using ParaTypeVector = typename Base::ParaTypeVector;
            using InternalTypeVector = typename Base::InternalTypeVector;
            using SubSectTypeVector = std::vector<std::shared_ptr<SubSectType>>;
        protected:
            using BaseVector = typename Base::BaseVector;
            using BaseVector::emplace_back;
            using Base::id_;
            using Base::title_;
            using Base::para_;
            using Base::internal_;
        private:
            SubSectTypeVector subSections_;
        public:
            DocSectionType( ) = default;
            HCC_EXPORT explicit DocSectionType( const XmlNode& xmlNode, std::string_view subSectionElementName);

            const SubSectTypeVector& SubSections( ) const { return subSections_; }
        };
    }

    class DocSect6Type : public Internal::DocSectionBaseType<Doxygen::DoxType::DocSect6Type, DocInternalS6Type>
    {
    public:
        using Base = Internal::DocSectionBaseType<Doxygen::DoxType::DocSect6Type, DocInternalS6Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect6Type( ) = default;
        HCC_EXPORT explicit DocSect6Type( const XmlNode& xmlNode );
    };

    class DocSect5Type : public Internal::DocSectionType<Doxygen::DoxType::DocSect5Type, DocInternalS5Type, DocSect6Type>
    {
    public:
        using Base = Internal::DocSectionType<Doxygen::DoxType::DocSect5Type, DocInternalS5Type, DocSect6Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect5Type( ) = default;
        HCC_EXPORT explicit DocSect5Type( const XmlNode& xmlNode );
    };

    class DocSect4Type : public Internal::DocSectionType<Doxygen::DoxType::DocSect4Type, DocInternalS4Type, DocSect5Type>
    {
    public:
        using Base = Internal::DocSectionType<Doxygen::DoxType::DocSect4Type, DocInternalS4Type, DocSect5Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect4Type( ) = default;
        HCC_EXPORT explicit DocSect4Type( const XmlNode& xmlNode );
    };

    class DocSect3Type : public Internal::DocSectionType<Doxygen::DoxType::DocSect3Type, DocInternalS3Type, DocSect4Type>
    {
    public:
        using Base = Internal::DocSectionType<Doxygen::DoxType::DocSect3Type, DocInternalS3Type, DocSect4Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect3Type( ) = default;
        HCC_EXPORT explicit DocSect3Type( const XmlNode& xmlNode );
    };

    class DocSect2Type : public Internal::DocSectionType<Doxygen::DoxType::DocSect2Type, DocInternalS2Type, DocSect3Type>
    {
    public:
        using Base = Internal::DocSectionType<Doxygen::DoxType::DocSect2Type, DocInternalS2Type, DocSect3Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect2Type( ) = default;
        HCC_EXPORT explicit DocSect2Type( const XmlNode& xmlNode );
    };

    class DocSect1Type : public Internal::DocSectionType<Doxygen::DoxType::DocSect1Type, DocInternalS1Type, DocSect2Type>
    {
    public:
        using Base = Internal::DocSectionType<Doxygen::DoxType::DocSect1Type, DocInternalS1Type, DocSect2Type>;
        using XmlNode = typename Base::XmlNode;

        DocSect1Type( ) = default;
        HCC_EXPORT explicit DocSect1Type( const XmlNode& xmlNode );
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
        WideString text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReferenceType>;

        ReferenceType( ) = default;
        HCC_EXPORT explicit ReferenceType( const XmlNode& xmlNode );

        const WideString& RefId( ) const { return refId_; }

        const WideString& CompoundRef( ) const { return compoundRef_; }
        Int32 StartLine( ) const { return startLine_; }
        Int32 Endline( ) const { return endline_; }
        const WideString& Text( ) const { return text_; }
    };
    
    class SpType : public Internal::DocBase<Doxygen::DoxType::SpType>
    {
        Int32 value_;
        WideString text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SpType>;

        SpType( ) = default;
        HCC_EXPORT explicit SpType( const XmlNode& xmlNode );

        Int32 Value( ) const { return value_; }
        const WideString& Text( ) const { return text_; }

    };
    
    class HighlightType : public Internal::DocBase<Doxygen::DoxType::HighlightType>, public std::vector<DocBaseTypePtr>
    {
    private:
        DoxHighlightClass class_;
        std::vector<RefTextTypePtr> ref_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::HighlightType>;
        
        HighlightType( ) = default;
        HCC_EXPORT explicit HighlightType( const XmlNode& xmlNode );

        DoxHighlightClass Class( ) const { return class_; }
        const std::vector<RefTextTypePtr>& Ref( ) const { return ref_; }
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

    class LinkedTextType : public Internal::DocBase<Doxygen::DoxType::LinkedTextType>, public std::vector<DocBaseTypePtr>
    {
        std::vector<RefTextTypePtr> ref_;
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

    class DescriptionType : public Internal::DocBase<Doxygen::DoxType::DescriptionType>, public std::vector<DocBaseTypePtr>
    {
        TitleTypePtr title_;
        std::vector<DocParaTypePtr> para_;
        std::vector<DocInternalTypePtr> internal_;
        std::vector<DocSect1TypePtr> sect1_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DescriptionType>;

        DescriptionType( ) = default;
        HCC_EXPORT explicit DescriptionType( const XmlNode& xmlNode );

        const TitleTypePtr& Title( ) const { return title_; }
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
        const std::vector<SectionDefTypePtr>& SectionDef() const { return sectiondef_; }
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

        HCC_EXPORT std::unique_ptr<Structure::TypeSystem> TypeSystem( ) const;

    };

    namespace Structure
    {

        enum class MemberType
        {
            Unknown,
            Namespace,
            Struct,
            Class,
            Union,
            Interface,
            Module,
            Concept,
            Function,
            Enum,
            Define,
            Property,
            Event,
            Variable,
            Typedef,
            Signal,
            Prototype,
            Friend,
            DCop,
            Slot,
            InterfaceReference,
            Service


        };

        class Member;
        class Container;
        class Namespace;
        class Struct;
        class Class;
        class Union;
        class Interface;
        class Enum;
        class Concept;
        class Function;
        class Module;
        class Define;
        class Property;
        class Event;
        class Variable;
        class Typedef;
        class Signal;
        class Prototype;
        class Friend;
        class DCop;
        class Slot;
        class InterfaceReference;
        class Service;

        class TypeSystem
        {
            std::vector<std::unique_ptr<Member>> all_;
            std::unordered_map<WideStringView, Member*> allTypes_;
            std::unordered_map<WideStringView, Member*> allTypesByQualifiedName_;
            std::unordered_map<WideStringView, Namespace*> allNamespaces_;
            std::unordered_map<WideStringView, Namespace*> allNamespacesByQualifiedName_;
            Namespace* global_ = nullptr;
        public:
            HCC_EXPORT TypeSystem( );
            HCC_EXPORT ~TypeSystem( );

            const std::unordered_map<WideStringView, Member*>& AllTypes( ) const { return allTypes_; }
            const std::unordered_map<WideStringView, Member*>& AllTypesByQualifiedName( ) const { return allTypesByQualifiedName_; }
            const std::unordered_map<WideStringView, Namespace*>& AllNamespaces( ) const { return allNamespaces_; }
            const std::unordered_map<WideStringView, Namespace*>& AllNamespacesByQualifiedName( ) const { allNamespacesByQualifiedName_; }

            Member* FindTypeById( const WideString& id ) const
            {
                auto it = allTypes_.find( id );
                if ( it != allTypes_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

            Member* FindTypeByQualifiedName( const WideString& qualifiedName ) const
            {
                auto it = allTypesByQualifiedName_.find( qualifiedName );
                if ( it != allTypesByQualifiedName_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

            Namespace* FindNamespaceById( const WideString& id ) const
            {
                auto it = allNamespaces_.find( id );
                if ( it != allNamespaces_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

            Namespace* FindNamespaceByQualifiedName( const WideString& qualifiedName ) const
            {
                auto it = allNamespacesByQualifiedName_.find( qualifiedName );
                if ( it != allNamespacesByQualifiedName_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

            HCC_EXPORT void Process( const DocumentCollection& documentCollection );

            Namespace* GlobalNamespace( ) const { return global_; }


        private:
            HCC_EXPORT void ScanSections( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container );
        public:
            HCC_EXPORT Namespace* AddNamespace( const Doxygen::CompoundDefTypePtr& compoundDef );
            HCC_EXPORT Struct* AddStruct( const Doxygen::CompoundDefTypePtr& compoundDef );
            HCC_EXPORT Class* AddClass( const Doxygen::CompoundDefTypePtr& compoundDef );
            HCC_EXPORT Union* AddUnion( const Doxygen::CompoundDefTypePtr& compoundDef );
            HCC_EXPORT Interface* AddInterface( const Doxygen::CompoundDefTypePtr& compoundDef );
            
            HCC_EXPORT Concept* AddConcept( const Doxygen::CompoundDefTypePtr& compoundDef );
            
            HCC_EXPORT Module* AddModule( const Doxygen::CompoundDefTypePtr& compoundDef );
            HCC_EXPORT Member* AddCompoundDef( const Doxygen::CompoundDefTypePtr& compoundDef );

            HCC_EXPORT Function* AddFunction( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Enum* AddEnum( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Define* AddDefine( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Property* AddProperty( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Event* AddEvent( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Variable* AddVariable( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Typedef* AddTypedef( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Signal* AddSignal( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Prototype* AddPrototype( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Friend* AddFriend( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT DCop* AddDCop( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Slot* AddSlot( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Service* AddService( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT InterfaceReference* AddInterfaceReference( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
            HCC_EXPORT Member* AddMemberDef( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );

            template<typename MemberDefT>
            MemberDefT* AddMemberDef( const WideString& qualifiedName, const WideString& name, const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef );
        };


        class Member 
        {
            Structure::TypeSystem* typeSystem_ = nullptr;
            Container* owner_ = nullptr;
            WideString name_;
            WideString qualifiedName_;
        public:

            explicit Member( Structure::TypeSystem* typeSystem )
                : typeSystem_( typeSystem )
            { }
            virtual ~Member( ) = default;
            virtual Structure::MemberType MemberType( ) const = 0;

            Structure::TypeSystem* TypeSystem( ) const { return typeSystem_; }
            Container* Owner( ) const { return owner_; }
            void SetOwner( Container* owner )
            {
                owner_ = owner;
            }

            const WideString& Name( ) const { return name_; }
            void SetName( const WideString& name )
            {
                name_ = name;
            }
            const WideString& QualifiedName( ) const { return qualifiedName_; }
            void SetQualifiedName( const WideString& qualifiedName )
            {
                qualifiedName_ = qualifiedName;
            }



        };

        class Container : public Member
        {
            std::vector<Member*> members_;
            std::unordered_map<WideString,Member*> membersByName_;
        public:
            using Base = Member;
            explicit Container( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            { }

            const std::vector<Member*>& Members( ) const { return members_; }
            const std::unordered_map<WideString, Member*>& MembersByName( ) const { return membersByName_; }

            virtual void Add( Member* member )
            {
                assert( member != nullptr );
                if ( !membersByName_.contains( member->Name( ) ) )
                {
                    membersByName_.emplace( member->Name( ), member );
                    members_.emplace_back( member );
                }
            }

        };

        class TypeContainer : public Container
        {
            Doxygen::CompoundDefTypePtr compoundDef_;
        public:
            using Base = Container;
            explicit TypeContainer( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }


            const Doxygen::CompoundDefTypePtr& CompoundDef( ) const
            {
                return compoundDef_;
            }
            void Assign( const Doxygen::CompoundDefTypePtr& compoundDef )
            {
                compoundDef_ = compoundDef;
            }

            DoxLanguage Language( ) const
            {
                if ( compoundDef_ )
                {
                    return compoundDef_->Language();
                }
                return {};
            }

        };

        class MemberDef : public Member
        {
            Doxygen::CompoundDefTypePtr compoundDef_;
            Doxygen::SectionDefTypePtr sectionDef_;
            Doxygen::MemberDefTypePtr memberDef_;
        public:
            using Base = Member;
            explicit MemberDef( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }


            const Doxygen::CompoundDefTypePtr& CompoundDef( ) const
            {
                return compoundDef_;
            }

            const Doxygen::SectionDefTypePtr& SectionDef( ) const { return sectionDef_; }
            const Doxygen::MemberDefTypePtr& SemberDef( ) const { return memberDef_; }

            void Assign( const Doxygen::CompoundDefTypePtr& compoundDef, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
            {
                compoundDef_ = compoundDef;
                sectionDef_ = sectionDef;
                memberDef_ = memberDef;
            }

        };


        


        namespace Internal
        {
            template<typename BaseT,Structure::MemberType memberType>
            class Base : public BaseT
            {
            public:
                static constexpr Structure::MemberType MEMBERTYPE = memberType;

                Base( Structure::TypeSystem* typeSystem )
                    : BaseT( typeSystem )
                { }

                template<typename T>
                    requires std::is_constructible_v<BaseT, Structure::TypeSystem*,const T&>
                Base( Structure::TypeSystem* typeSystem, const T& arg )
                    : BaseT( typeSystem, arg )
                {
                }

                virtual Structure::MemberType MemberType( ) const override
                {
                    return MEMBERTYPE;
                }
            };

            template<Structure::MemberType memberType>
            using MemberBase = Base<Member, memberType>;

            template<Structure::MemberType memberType>
            using ContainerBase = Base<Container, memberType>;

            template<Structure::MemberType memberType>
            using TypeContainerBase = Base<TypeContainer, memberType>;

            template<Structure::MemberType memberType>
            using MemberDefBase = Base<MemberDef, memberType>;
            
        }

        class Namespace : public Internal::TypeContainerBase<Structure::MemberType::Namespace>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Namespace>;

            explicit Namespace( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

        };

        class Struct : public Internal::TypeContainerBase<Structure::MemberType::Struct>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Struct>;

            explicit Struct( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

        };

        class Class : public Internal::TypeContainerBase<Structure::MemberType::Class>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Class>;

            explicit Class( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

        };

        class Union : public Internal::TypeContainerBase<Structure::MemberType::Union>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Union>;

            explicit Union( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

        };

        class Interface : public Internal::TypeContainerBase<Structure::MemberType::Interface>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Interface>;

            explicit Interface( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }
        };

        class Enum : public Internal::ContainerBase<Structure::MemberType::Enum>
        {
            Doxygen::CompoundDefTypePtr compoundDef_;
            Doxygen::SectionDefTypePtr sectionDef_;
            Doxygen::MemberDefTypePtr memberDef_;
        public:
            using Base = Internal::ContainerBase<Structure::MemberType::Enum>;

            explicit Enum( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

            const Doxygen::CompoundDefTypePtr& CompoundDef( ) const
            {
                return compoundDef_;
            }

            const Doxygen::SectionDefTypePtr& SectionDef( ) const { return sectionDef_; }
            const Doxygen::MemberDefTypePtr& SemberDef( ) const { return memberDef_; }

            void Assign( const Doxygen::CompoundDefTypePtr& compoundDef, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
            {
                compoundDef_ = compoundDef;
                sectionDef_ = sectionDef;
                memberDef_ = memberDef;
            }

        };

        class Concept : public Internal::TypeContainerBase<Structure::MemberType::Concept>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Concept>;

            explicit Concept( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

        };

        class Module : public Internal::TypeContainerBase<Structure::MemberType::Module>
        {
        public:
            using Base = Internal::TypeContainerBase<Structure::MemberType::Module>;

            explicit Module( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

        };

        class Function : public Internal::MemberDefBase<Structure::MemberType::Function>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Function>;

            explicit Function( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsMemberFunction( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

        };

        class Define : public Internal::MemberDefBase<Structure::MemberType::Define>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Define>;

            explicit Define( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };

        class Property : public Internal::MemberDefBase<Structure::MemberType::Property>
        {
        public:
            

            using Base = Internal::MemberDefBase<Structure::MemberType::Property>;

            explicit Property( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class Event : public Internal::MemberDefBase<Structure::MemberType::Event>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Event>;

            explicit Event( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class Variable : public Internal::MemberDefBase<Structure::MemberType::Variable>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Variable>;

            explicit Variable( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsMemberVariable( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }
        };
        class Typedef : public Internal::MemberDefBase<Structure::MemberType::Typedef>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Typedef>;

            explicit Typedef( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }

            bool IsNested( )
            {
                auto owner = Owner( );
                return owner != nullptr && owner->MemberType( ) != Structure::MemberType::Namespace;
            }

        };
        class Signal : public Internal::MemberDefBase<Structure::MemberType::Signal>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Signal>;

            explicit Signal( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class Prototype : public Internal::MemberDefBase<Structure::MemberType::Prototype>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Prototype>;

            explicit Prototype( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class Friend : public Internal::MemberDefBase<Structure::MemberType::Friend>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Friend>;

            explicit Friend( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class DCop : public Internal::MemberDefBase<Structure::MemberType::DCop>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::DCop>;

            explicit DCop( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class Slot : public Internal::MemberDefBase<Structure::MemberType::Slot>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Slot>;

            explicit Slot( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        class InterfaceReference : public Internal::MemberDefBase<Structure::MemberType::InterfaceReference>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::InterfaceReference>;

            explicit InterfaceReference( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };

        class Service : public Internal::MemberDefBase<Structure::MemberType::Service>
        {
        public:
            using Base = Internal::MemberDefBase<Structure::MemberType::Service>;

            explicit Service( Structure::TypeSystem* typeSystem )
                : Base( typeSystem )
            {
            }
        };
        

        
        template<typename MemberDefT>
        inline MemberDefT* TypeSystem::AddMemberDef( const WideString& qualifiedName, const WideString& name, const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
        {
            auto memberDefT = std::make_unique<MemberDefT>( this );
            auto result = memberDefT.get( );
            all_.emplace_back( std::move( memberDefT ) );
            result->SetQualifiedName( qualifiedName );
            result->SetName( name );
            result->SetOwner( container );
            container->Add( result );
            result->Assign( compoundDef, sectionDef, memberDef );
            return result;
        }

    }


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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::MemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseMemberKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxGraphRelation( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxGraphRelation, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxGraphRelation( BasicString<CharT>(str) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxRefKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxMemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxMemberKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxProtectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxProtectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxProtectionKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxRefQualifierKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefQualifierKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefQualifierKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxLanguage( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxLanguage, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxLanguage( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxVirtualKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVirtualKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVirtualKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCompoundKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCompoundKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCompoundKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxSectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSectionKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxHighlightClass( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxHighlightClass, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxHighlightClass( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxSimpleSectKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSimpleSectKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSimpleSectKind( BasicString<CharT>(str) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCheck( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCheck, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCheck( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxImageKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxImageKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxImageKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxPlantumlEngine( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxPlantumlEngine, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxPlantumlEngine( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxParamListKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamListKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamListKind( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxParamDir( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamDir, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamDir( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxAccessor( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAccessor, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAccessor( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAlign( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxVerticalAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVerticalAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVerticalAlign( BasicString<CharT>( str ) );
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
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxOlType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxOlType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxOlType( BasicString<CharT>( str ) );
    }


    /////////
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCmdGroupType value );
    HCC_EXPORT WideString ToWideString( Doxygen::DoxCmdGroupType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Doxygen::DoxCmdGroupType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Doxygen::DoxCmdGroupType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCmdGroupType ParseDoxCmdGroupType( const WideString& str );
        HCC_EXPORT DoxCmdGroupType ParseDoxCmdGroupType( const WideString& str, DoxCmdGroupType defaultResult );
        HCC_EXPORT bool TryParseDoxCmdGroupType( const WideString& str, DoxCmdGroupType& value );

        inline DoxCmdGroupType ParseDoxCmdGroupType( const AnsiString& str )
        {
            return ParseDoxCmdGroupType( ToWideString( str ) );
        }
        inline DoxCmdGroupType ParseDoxCmdGroupType( const AnsiString& str, DoxCmdGroupType defaultResult )
        {
            return ParseDoxCmdGroupType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDoxCmdGroupType( const AnsiString& str, DoxCmdGroupType& value )
        {
            return TryParseDoxCmdGroupType( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Doxygen::DoxCmdGroupType& value )
    {
        return Doxygen::TryParseDoxCmdGroupType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCmdGroupType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCmdGroupType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCmdGroupType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCmdGroupType( BasicString<CharT>( str ) );
    }





}

#endif
