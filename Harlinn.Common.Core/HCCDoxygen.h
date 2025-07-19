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

#include <HCCDef.h>
#include <HCCString.h>
#include <HCCStringBuilder.h>

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

    using DoxVersionNumber = std::string;

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
        //DocVariableListGroup,
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
        //DocCmdGroup,
        DocSummaryType,
        DocTitleType,
        //DocTitleCmdGroup,
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
    //class DocVariableListGroup;
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
    //class DocCmdGroup;
    class DocSummaryType;
    class DocTitleType;
    //class DocTitleCmdGroup;
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
    //using DocVariableListGroupPtr = std::shared_ptr<DocVariableListGroup>;
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
    //using DocCmdGroupPtr = std::shared_ptr<DocCmdGroup>;
    using DocSummaryTypePtr = std::shared_ptr<DocSummaryType>;
    using DocTitleTypePtr = std::shared_ptr<DocTitleType>;
    //using DocTitleCmdGroupPtr = std::shared_ptr<DocTitleCmdGroup>;
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
        std::string text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TextType>;

        TextType( ) = default;
        explicit TextType( const std::string& text )
            : text_( text )
        { }
        HCC_EXPORT explicit TextType( const XmlNode& xmlNode );

        const std::string& Text( ) const
        {
            return text_;
        }
    };

    class TitleType : public Internal::DocBase<Doxygen::DoxType::TitleType>
    {
        std::string text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TitleType>;

        TitleType( ) = default;
        HCC_EXPORT explicit TitleType( const XmlNode& xmlNode );

        const std::string& Text( ) const
        {
            return text_;
        }

    };

    class DocEmojiType : public Internal::DocBase<Doxygen::DoxType::DocEmojiType>
    {
        std::string name_;
        std::string unicode_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocEmojiType>;
        DocEmojiType( ) = default;
        HCC_EXPORT explicit DocEmojiType( const XmlNode& xmlNode );

        const std::string& Name( ) const
        {
            return name_;
        }
        const std::string& Unicode( ) const
        {
            return unicode_;
        }

    };

    class TableOfContentsKindType : public Internal::DocBase<Doxygen::DoxType::TableOfContentsKindType>
    {
        std::string name_;
        std::string reference_;
        std::vector<std::shared_ptr<TableOfContentsType>> tableOfContents_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::TableOfContentsKindType>;
        TableOfContentsKindType( ) = default;
        HCC_EXPORT explicit TableOfContentsKindType( const XmlNode& xmlNode );


        const std::string& Name( ) const
        {
            return name_;
        }

        const std::string& Reference( ) const
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


    class DocEmptyType : public Internal::DocBase<DoxType::DocEmptyType>
    {
    public:
        using Base = Internal::DocBase<DoxType::DocEmptyType>;

        DocEmptyType( ) = default;
        HCC_EXPORT explicit DocEmptyType( const XmlNode& xmlNode );
    };

    class DocParBlockType : public Internal::DocBase<DoxType::DocParBlockType>, public std::vector<DocParaTypePtr>
    {
    public:
        using Base = Internal::DocBase<DoxType::DocParBlockType>;

        DocParBlockType( ) = default;
        HCC_EXPORT explicit DocParBlockType( const XmlNode& xmlNode );
    };

    class DocBlockQuoteType : public Internal::DocBase<DoxType::DocBlockQuoteType>, public std::vector<DocParaTypePtr>
    {
    public:
        using Base = Internal::DocBase<DoxType::DocBlockQuoteType>;

        DocBlockQuoteType( ) = default;
        HCC_EXPORT explicit DocBlockQuoteType( const XmlNode& xmlNode );
    };

    class DocDetailsType : public Internal::DocBase<DoxType::DocDetailsType>, public std::vector<DocParaTypePtr>
    {
        DocSummaryTypePtr summary_;
    public:
        using Base = Internal::DocBase<DoxType::DocDetailsType>;

        DocDetailsType( ) = default;
        HCC_EXPORT explicit DocDetailsType( const XmlNode& xmlNode );

        const DocSummaryTypePtr& Summary( ) const { return summary_; }

    };


    class DocCopyType : public Internal::DocBase<DoxType::DocCopyType>, public std::vector<DocParaTypePtr>
    {
        std::string link_;
        std::vector<DocSect1TypePtr> sect1_;
        std::vector<DocInternalTypePtr> internal_;
    public:
        using Base = Internal::DocBase<DoxType::DocCopyType>;

        DocCopyType( ) = default;
        HCC_EXPORT explicit DocCopyType( const XmlNode& xmlNode );

        const std::string& Link( ) const { return link_; }
        const std::vector<DocSect1TypePtr>& Sect1( ) const { return sect1_; }
        const std::vector<DocInternalTypePtr>& Internal( ) const { return internal_; }

    };

    class DocXRefSectType : public Internal::DocBase<Doxygen::DoxType::DocXRefSectType>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocXRefSectType>;

        DocXRefSectType( ) = default;
        HCC_EXPORT explicit DocXRefSectType( const XmlNode& xmlNode );

    };

    /// <summary>
    /// A sequence of TextType or RefTextType objects
    /// </summary>
    class DocParamName : public Internal::DocBase<DoxType::DocParamName>, public std::vector<DocBaseTypePtr>
    {
        std::optional<DoxParamDir> direction_;
        /// <summary>
        ///  `ref_` is also stored in the vector
        /// </summary>
        RefTextTypePtr ref_;
    public:
        using Base = Internal::DocBase<DoxType::DocParamName>;

        DocParamName( ) = default;
        HCC_EXPORT explicit DocParamName( const XmlNode& xmlNode );

        const std::optional<DoxParamDir>& Direction( ) const { return direction_; }
        const RefTextTypePtr& Ref( ) const { return ref_; }
    };

    class DocParamType : public Internal::DocBase<DoxType::DocParamType>, public std::vector<DocBaseTypePtr>
    {
        /// <summary>
        ///  `ref_` is also stored in the vector
        /// </summary>
        RefTextTypePtr ref_;
    public:
        using Base = Internal::DocBase<DoxType::DocParamType>;

        DocParamType( ) = default;
        HCC_EXPORT explicit DocParamType( const XmlNode& xmlNode );

        const RefTextTypePtr& Ref( ) const { return ref_; }

    };

    

    class DocParamNameList : public Internal::DocBase<DoxType::DocParamNameList>, public std::vector<DocBaseTypePtr>
    {

    public:
        using Base = Internal::DocBase<DoxType::DocParamNameList>;

        DocParamNameList( ) = default;
        HCC_EXPORT explicit DocParamNameList( const XmlNode& xmlNode );
    };

    class DocParamListItem : public Internal::DocBase<DoxType::DocParamListItem>, public std::vector<DocParamNameListPtr>
    {
        DescriptionTypePtr parameterDescription_;
    public:
        using Base = Internal::DocBase<DoxType::DocParamListItem>;

        DocParamListItem( ) = default;
        HCC_EXPORT explicit DocParamListItem( const XmlNode& xmlNode );

        const DescriptionTypePtr& ParameterDescription( ) const { return parameterDescription_; }

    };

    class DocParamListType : public Internal::DocBase<DoxType::DocParamListType>, public std::vector<DocParamListItemPtr>
    {
        DoxParamListKind kind_;
    public:
        using Base = Internal::DocBase<DoxType::DocParamListType>;

        DocParamListType( ) = default;
        HCC_EXPORT explicit DocParamListType( const XmlNode& xmlNode );

        DoxParamListKind kind( ) const { return kind_; }

    };

    class DocLanguageType : public Internal::DocBase<DoxType::DocLanguageType>, public std::vector<DocParaTypePtr>
    {
        std::string langid_;
    public:
        using Base = Internal::DocBase<DoxType::DocLanguageType>;

        DocLanguageType( ) = default;
        HCC_EXPORT explicit DocLanguageType( const XmlNode& xmlNode );

        const std::string& LangId( ) const { return langid_; }
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


    class DocHeadingType : public Internal::DocBase<Doxygen::DoxType::DocHeadingType>, public std::vector<DocCmdGroupType>
    {
        int level_ = 0;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHeadingType>;

        DocHeadingType( ) = default;
        HCC_EXPORT explicit DocHeadingType( const XmlNode& xmlNode );

        int Level( ) const
        {
            return level_;
        }


    };

    class DocCaptionType : public Internal::DocBase<Doxygen::DoxType::DocCaptionType>, public std::vector<DocCmdGroupType>
    {
        std::string id_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocCaptionType>;

        DocCaptionType( ) = default;
        HCC_EXPORT explicit DocCaptionType( const XmlNode& xmlNode );

        const std::string& Id( ) const { return id_; }

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
        std::string refId_;
        DoxRefKind kindRef_{};
        std::string external_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocRefTextType>;

        DocRefTextType( ) = default;
        HCC_EXPORT explicit DocRefTextType( const XmlNode& xmlNode );

        const std::string& RefId() const { return refId_; }
        DoxRefKind KindRef() const { return kindRef_; }
        const std::string& External( ) const { return external_; }

    };

    class DocVariableListType : public Internal::DocBase<Doxygen::DoxType::DocVariableListType>, public std::vector<DocBaseTypePtr>
    {
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocVariableListType>;

        DocVariableListType( ) = default;
        HCC_EXPORT explicit DocVariableListType( const XmlNode& xmlNode );
    };

    /*
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
    */

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
        std::string primary_;
        std::string secondary_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocIndexEntryType>;

        DocIndexEntryType( ) = default;
        HCC_EXPORT explicit DocIndexEntryType( const XmlNode& xmlNode );

        const std::string& Primary( ) const { return primary_; }
        const std::string& Secondary( ) const { return secondary_; }

    };

    class DocFormulaType : public Internal::DocBase<Doxygen::DoxType::DocFormulaType>
    {
        std::string id_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocFormulaType>;

        DocFormulaType( ) = default;
        HCC_EXPORT explicit DocFormulaType( const XmlNode& xmlNode );

        const std::string& Id( ) const { return id_; }
        const std::string& Content( ) const { return content_; }
    };

    class DocAnchorType : public Internal::DocBase<Doxygen::DoxType::DocAnchorType>
    {
        std::string id_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocAnchorType>;

        DocAnchorType( ) = default;
        HCC_EXPORT explicit DocAnchorType( const XmlNode& xmlNode );

        const std::string& Id( ) const { return id_; }
        const std::string& Content( ) const { return content_; }
    };

    class DocURLLink : public Internal::DocBase<Doxygen::DoxType::DocURLLink>, public std::vector<DocCmdGroupType>
    {
        std::string url_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocURLLink>;

        DocURLLink( ) = default;
        HCC_EXPORT explicit DocURLLink( const XmlNode& xmlNode );

        const std::string& Url( ) const { return url_; }
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
            std::string id_;
            TitleTypePtr title_;
            ParaTypeVector para_;
        public:
            DocInternalSectionBaseType( ) = default;
            HCC_EXPORT explicit DocInternalSectionBaseType( const XmlNode& xmlNode );

            const std::string& Id( ) const { return id_; }
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
            std::string id_;
            TitleTypePtr title_;
            ParaTypeVector para_;
            InternalTypeVector internal_;
        public:
            DocSectionBaseType( ) = default;
            HCC_EXPORT explicit DocSectionBaseType( const XmlNode& xmlNode );

            const std::string& Id( ) const { return id_; }
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
        std::string file_;
        Int32 line_ = 0;
        Int32 column_ = 0;
        std::string declFile_;
        Int32 declLine_ = 0;
        Int32 declColumn_ = 0;
        std::string bodyFile_;
        Int32 bodyStart_ = 0;
        Int32 bodyEnd_ = 0;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LocationType>;

        LocationType( ) = default;
        HCC_EXPORT explicit LocationType( const XmlNode& xmlNode );

        const std::string& File( ) const { return file_; }
        Int32 Line( ) const { return line_; }
        Int32 Column( ) const { return column_; }
        const std::string& DeclFile( ) const { return declFile_; }
        Int32 DeclLine( ) const { return declLine_; }
        Int32 DeclColumn( ) const { return declColumn_; }
        const std::string& BodyFile( ) const { return bodyFile_; }
        Int32 BodyStart( ) const { return bodyStart_; }
        Int32 BodyEnd( ) const { return bodyEnd_; }

    };

    class ReferenceType : public Internal::DocBase<Doxygen::DoxType::ReferenceType>
    {
        std::string refId_;
        std::string compoundRef_;
        Int32 startLine_ = 0;
        Int32 endline_ = 0;
        std::string text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReferenceType>;

        ReferenceType( ) = default;
        HCC_EXPORT explicit ReferenceType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }

        const std::string& CompoundRef( ) const { return compoundRef_; }
        Int32 StartLine( ) const { return startLine_; }
        Int32 Endline( ) const { return endline_; }
        const std::string& Text( ) const { return text_; }
    };
    
    class SpType : public Internal::DocBase<Doxygen::DoxType::SpType>
    {
        Int32 value_;
        std::string text_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SpType>;

        SpType( ) = default;
        HCC_EXPORT explicit SpType( const XmlNode& xmlNode );

        Int32 Value( ) const { return value_; }
        const std::string& Text( ) const { return text_; }

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
        std::string refId_;
        DoxRefKind refKind_{};
        bool external_{};
        std::vector<HighlightTypePtr> highlight_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CodeLineType>;

        CodeLineType( ) = default;
        HCC_EXPORT explicit CodeLineType( const XmlNode& xmlNode );

        Int32 LineNo( ) const { return lineno_; }
        const std::string& RefId( ) const { return refId_; }
        DoxRefKind RefKind( ) const { return refKind_; }
        bool External( ) const { return external_; }
        const std::vector<HighlightTypePtr>& Highlight( ) const { return highlight_; }

    };

    class ListingType : public Internal::DocBase<Doxygen::DoxType::ListingType>, public std::vector<CodeLineTypePtr>
    {
        std::string fileName_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ListingType>;

        ListingType( ) = default;
        HCC_EXPORT explicit ListingType( const XmlNode& xmlNode );

        const std::string& fileName( ) const { return fileName_; }

    };

    class LinkType : public Internal::DocBase<Doxygen::DoxType::LinkType>
    {
        std::string refId_;
        std::string external_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::LinkType>;

        LinkType( ) = default;
        HCC_EXPORT explicit LinkType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }
        const std::string& External( ) const { return external_; }
    };

    class ChildNodeType : public Internal::DocBase<Doxygen::DoxType::ChildNodeType>
    {
        std::string refId_;
        std::vector<std::string> edgeLabel_;
        DoxGraphRelation relation_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ChildNodeType>;

        ChildNodeType( ) = default;
        HCC_EXPORT explicit ChildNodeType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }
        const std::vector<std::string>& EdgeLabel( ) const { return edgeLabel_; }
        DoxGraphRelation Relation( ) const { return relation_; }
    };

    class NodeType : public Internal::DocBase<Doxygen::DoxType::NodeType>
    {
        std::string id_;
        std::string label_;
        LinkTypePtr link_;
        std::vector<ChildNodeTypePtr> childNode_;

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::NodeType>;

        NodeType( ) = default;
        HCC_EXPORT explicit NodeType( const XmlNode& xmlNode );

        const std::string& Id( ) const { return id_; }
        const std::string& Label( ) const { return label_; }
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

        const std::vector<RefTextTypePtr>& Ref( ) const { return ref_; }
    };

    class ParamType : public Internal::DocBase<Doxygen::DoxType::ParamType>
    {
        std::string attributes_;
        LinkedTextTypePtr type_;
        std::string declName_;
        std::string defName_;
        std::string array_;
        LinkedTextTypePtr defVal_;
        LinkedTextTypePtr typeConstraint_;
        DescriptionTypePtr briefDescription_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ParamType>;

        ParamType( ) = default;
        HCC_EXPORT explicit ParamType( const XmlNode& xmlNode );

        const std::string& Attributes( ) const { return attributes_; }
        const LinkedTextTypePtr& Type( ) const { return type_; }
        const std::string& DeclName( ) const { return declName_; }
        const std::string& DefName( ) const { return defName_; }
        const std::string& Array( ) const { return array_; }
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
        std::string id_;
        DoxProtectionKind prot_;
        std::string name_;
        LinkedTextTypePtr initializer_;
        DescriptionTypePtr briefDescription_;
        DescriptionTypePtr detailedDescription_;

    public:
        using Base = Internal::DocBase<Doxygen::DoxType::EnumvalueType>;

        EnumvalueType( ) = default;
        HCC_EXPORT explicit EnumvalueType( const XmlNode& xmlNode );

        const std::string& Id( ) const { return id_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        const std::string& Name( ) const { return name_; }
        const LinkedTextTypePtr& Initializer( ) const { return initializer_; }
        const DescriptionTypePtr& BriefDescription( ) const { return briefDescription_; }
        const DescriptionTypePtr& DetailedDescription( ) const { return detailedDescription_; }

    };

    class DescriptionType : public Internal::DocBase<DoxType::DescriptionType>, public std::vector<DocBaseTypePtr>
    {
        TitleTypePtr title_;
        std::vector<DocInternalTypePtr> internal_;
        std::vector<DocSect1TypePtr> sect1_;
    public:
        using Base = Internal::DocBase<DoxType::DescriptionType>;

        DescriptionType( ) = default;
        HCC_EXPORT explicit DescriptionType( const XmlNode& xmlNode );

        const TitleTypePtr& Title( ) const { return title_; }
        const std::vector<DocInternalTypePtr>& Internal( ) const { return internal_; }
        const std::vector<DocSect1TypePtr>& Sect1( ) const { return sect1_; }
        
    };


    class MemberDefType : public Internal::DocBase<Doxygen::DoxType::MemberDefType>
    {
        DoxMemberKind kind_{};
        std::string id_;
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
        std::string noexceptExpression_;
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
        std::string definition_;
        std::string argsString_;
        std::string name_;
        std::string qualifiedName_;
        std::string read_;
        std::string write_;
        std::string bitField_;
        std::vector<ReimplementTypePtr> reimplements_;
        std::vector<ReimplementTypePtr> reimplementedBy_;
        std::string qualifier_;
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
        const std::string& Id( ) const { return id_; }
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
        const std::string& NoexceptExpression( ) const { return noexceptExpression_; }
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
        const std::string& Definition( ) const { return definition_; }
        const std::string& ArgsString( ) const { return argsString_; }
        const std::string& Name( ) const { return name_; }
        const std::string& QualifiedName( ) const { return qualifiedName_; }
        const std::string& Read( ) const { return read_; }
        const std::string& Write( ) const { return write_; }
        const std::string& BitField( ) const { return bitField_; }
        const std::vector<ReimplementTypePtr>& Reimplements( ) const { return reimplements_; }
        const std::vector<ReimplementTypePtr>& ReimplementedBy( ) const { return reimplementedBy_; }
        const std::string& Qualifier( ) const { return qualifier_; }
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
        std::string header_;
        DescriptionTypePtr description_;
        std::vector<MemberDefTypePtr> memberDef_;
        std::vector<MemberTypePtr> member_;
        DoxSectionKind kind_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::SectionDefType>;

        SectionDefType( ) = default;
        HCC_EXPORT explicit SectionDefType( const XmlNode& xmlNode );

        const std::string& Header( ) const { return header_; }
        const DescriptionTypePtr& Description( ) const { return description_; }
        const std::vector<MemberDefTypePtr>& MemberDef( ) const { return memberDef_; }
        const std::vector<MemberTypePtr>& Member( ) const { return member_; }
        DoxSectionKind Kind( ) const { return kind_; }

    };

    class MemberType : public Internal::DocBase<Doxygen::DoxType::MemberType>
    {
        std::string name_;
        std::string refId_;
        MemberKind kind_{};
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberType>;

        MemberType( ) = default;
        HCC_EXPORT explicit MemberType( const XmlNode& xmlNode );


        const std::string& Name( ) const { return name_; }
        const std::string& RefId( ) const { return refId_; }
        MemberKind kind( ) const { return kind_; }
    };

    class RefTextType : public Internal::DocBase<Doxygen::DoxType::RefTextType>
    {
        std::string refId_;
        DoxRefKind kindRef_{};
        std::string external_;
        std::string tooltip_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefTextType>;

        RefTextType( ) = default;
        HCC_EXPORT explicit RefTextType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }
        DoxRefKind KindRef( ) const { return kindRef_; }
        const std::string& External( ) const { return external_; }
        const std::string& Tooltip( ) const { return tooltip_; }
        const std::string& Content( ) const { content_; }

    };

    class RefType : public Internal::DocBase<Doxygen::DoxType::RefType>
    {
        std::string refId_;
        DoxProtectionKind prot_{};
        bool inline_ = false;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::RefType>;

        RefType( ) = default;
        HCC_EXPORT explicit RefType( const XmlNode& xmlNode );
        RefType( const std::string& refId, DoxProtectionKind prot, const std::string& content, bool isInline = false )
            : refId_( refId ), prot_( prot ), inline_( isInline ), content_( content )
        { }

        RefType( const CompoundDefType& compoundDefType );

        const std::string& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        bool Inline( ) const { return inline_; }

        const std::string& Content( ) const
        {
            return content_;
        }
    };


    class ExportType : public Internal::DocBase<Doxygen::DoxType::ExportType>
    {
        std::string refId_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ExportType>;

        ExportType( ) = default;
        HCC_EXPORT explicit ExportType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }

        const std::string& Content( ) const
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
        std::string refId_;
        bool local_ = false;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::IncType>;

        IncType( ) = default;
        HCC_EXPORT explicit IncType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }
        bool Local( ) const { return local_; }

        const std::string& Content( ) const
        {
            return content_;
        }
    };

    class ReimplementType : public Internal::DocBase<Doxygen::DoxType::ReimplementType>
    {
        std::string refId_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::ReimplementType>;

        ReimplementType( ) = default;
        HCC_EXPORT explicit ReimplementType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }

        const std::string& Content( ) const
        {
            return content_;
        }
    };


    class CompoundRefType : public Internal::DocBase<Doxygen::DoxType::CompoundRefType>
    {
        std::string refId_;
        DoxProtectionKind prot_{};
        DoxVirtualKind virt_{};
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::CompoundRefType>;

        CompoundRefType( ) = default;
        HCC_EXPORT explicit CompoundRefType( const XmlNode& xmlNode );

        const std::string& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        DoxVirtualKind Virt( ) const { return virt_; }

        const std::string& Content( ) const
        {
            return content_;
        }
    };


    class DocHtmlOnlyType : public Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>
    {
        std::string block_;
        std::string content_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::DocHtmlOnlyType>;

        DocHtmlOnlyType( ) = default;
        HCC_EXPORT explicit DocHtmlOnlyType( const XmlNode& xmlNode );

        const std::string& Block( ) const
        {
            return block_;
        }

        const std::string& Content( ) const
        {
            return content_;
        }

    };


    class MemberRefType : public Internal::DocBase<Doxygen::DoxType::MemberRefType>
    {
        std::string name_;
        std::string scope_;
        std::string refId_;
        DoxProtectionKind prot_{};
        DoxVirtualKind virt_{};
        std::string ambiguityScope_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::MemberRefType>;

        MemberRefType( ) = default;
        HCC_EXPORT explicit MemberRefType( const XmlNode& xmlNode );

        const std::string& Name( ) const { return name_; }
        const std::string& Scope( ) const { return scope_; }
        const std::string& RefId( ) const { return refId_; }
        DoxProtectionKind Prot( ) const { return prot_; }
        DoxVirtualKind Virt( ) const { return virt_; }
        const std::string& AmbiguityScope( ) const { return ambiguityScope_; }

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
        std::string id_;
        DoxCompoundKind kind_{};
        DoxLanguage language_{};
        DoxProtectionKind prot_{};
        bool final_{};
        bool inline_{};
        bool sealed_{};
        bool abstract_{};
        std::string compoundName_;
        std::string title_;
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
        std::vector<std::string> qualifier_;
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

        CompoundDefType( const std::string& id, DoxCompoundKind kind, const std::string& compoundName, DoxLanguage language )
            : id_(id), kind_(kind), compoundName_( compoundName ), language_( language )
        { }


        const std::string& Id() const { return id_; }
        DoxCompoundKind Kind( ) const { return kind_; }
        DoxLanguage Language( ) const { return language_; }
        DoxProtectionKind Prot() const { return prot_; }
        bool Final() const { return final_; }
        bool Inline() const { return inline_; }
        bool Sealed() const { return sealed_; }
        bool Abstract() const { return abstract_; }
        const std::string& CompoundName() const { return compoundName_; }
        const std::string& Title() const { return title_; }
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
        void AddInnerClass( const CompoundDefTypePtr& compoundDefType )
        {
            innerClass_.emplace_back( std::make_shared<RefType>( *compoundDefType ) );
        }
        const std::vector<RefTypePtr>& InnerConcept() const { return innerConcept_; }
        void AddInnerConcept( const CompoundDefTypePtr& compoundDefType )
        {
            innerConcept_.emplace_back( std::make_shared<RefType>( *compoundDefType ) );
        }
        const std::vector<RefTypePtr>& InnerNamespace() const { return innerNamespace_; }
        void AddInnerNamespace( const CompoundDefTypePtr& compoundDefType )
        {
            innerNamespace_.emplace_back( std::make_shared<RefType>( *compoundDefType ) );
        }
        const std::vector<RefTypePtr>& InnerPage() const { return innerPage_; }
        const std::vector<RefTypePtr>& InnerGroup() const { return innerGroup_; }
        const std::vector<std::string>& Qualifier() const { return qualifier_; }
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

        bool HasChildren( ) const
        {
            return innerClass_.size() != 0 || innerConcept_.size( ) != 0 || innerNamespace_.size( ) != 0;
        }

    };

    inline RefType::RefType( const CompoundDefType& compoundDefType )
        : refId_( compoundDefType.Id() ), prot_( compoundDefType.Prot() ), inline_( compoundDefType.Inline() ), content_( compoundDefType.CompoundName( ) )
    { }


    class Document : public Internal::DocBase<Doxygen::DoxType::Document>, public std::vector<CompoundDefTypePtr>
    {
        std::wstring name_;
    public:
        using Base = Internal::DocBase<Doxygen::DoxType::Document>;

        Document( ) = default;
        HCC_EXPORT explicit Document( const std::wstring& name, const XmlNode& xmlNode );
    };

    class DocumentCollection : public std::unordered_map<std::wstring, DocumentPtr>
    {
         
    public:
        using Base = std::unordered_map<std::string, DocumentPtr>;

        HCC_EXPORT explicit DocumentCollection( );

        HCC_EXPORT void AddDirectory( const std::wstring& directoryName );
        HCC_EXPORT void AddFile( const std::wstring& filename );

        void AddDirectory( const std::string& directoryName )
        {
            AddDirectory( to_wstring( directoryName ) );
        }
        void AddFile( const std::string& filename )
        {
            AddFile( to_wstring( filename ) );
        }

        HCC_EXPORT std::unique_ptr<Structure::TypeSystem> TypeSystem( ) const;

    };

    namespace Structure
    {
        class BaseDef;
        class CompoundDef;

        class ClassCompoundDef;
        class StructCompoundDef;
        class UnionCompoundDef;
        class InterfaceCompoundDef;
        class ProtocolCompoundDef;
        class CategoryCompoundDef;
        class ExceptionCompoundDef;
        class ServiceCompoundDef;
        class SingletonCompoundDef;
        class ModuleCompoundDef;
        class TypeCompoundDef;
        class FileCompoundDef;
        class NamespaceCompoundDef;
        class GroupCompoundDef;
        class PageCompoundDef;
        class ExampleCompoundDef;
        class DirCompoundDef;
        class ConceptCompoundDef;

        class MemberDef;
        class DefineMemberDef;
        class PropertyMemberDef;
        class EventMemberDef;
        class VariableMemberDef;
        class TypedefMemberDef;
        class EnumMemberDef;
        class FunctionMemberDef;
        class SignalMemberDef;
        class PrototypeMemberDef;
        class FriendMemberDef;
        class DCopMemberDef;
        class SlotMemberDef;
        class InterfaceMemberDef;
        class ServiceMemberDef;

        class MemberDefKey
        {
            std::string_view compoundDefId_;
            std::string_view memberDefId_;
        public:
            MemberDefKey( ) = default;
            explicit MemberDefKey( const std::string_view& memberDefId )
                : memberDefId_( memberDefId )
            {
            }
            explicit MemberDefKey( const std::string_view& compoundDefId, const std::string_view& memberDefId )
                : compoundDefId_( compoundDefId ), memberDefId_( memberDefId )
            {
            }

            auto operator<=>( const MemberDefKey& ) const = default;

            size_t Hash( ) const
            {
                XXH64Hasher hasher;
                hasher.Add( compoundDefId_ );
                hasher.Add( memberDefId_ );
                return hasher.Digest( );
            }

            const std::string_view& CompoundDefId( ) const
            {
                return compoundDefId_;
            }
            const std::string_view& MemberDefId( ) const
            {
                return memberDefId_;
            }

        };
    }
}

namespace std
{
    template<> struct hash<Harlinn::Common::Core::Doxygen::Structure::MemberDefKey>
    {
        std::size_t operator()( const Harlinn::Common::Core::Doxygen::Structure::MemberDefKey& key ) const noexcept
        {
            return key.Hash( );
        }
    };
}

namespace Harlinn::Common::Core::Doxygen
{
    namespace Structure
    {

        struct Identifier
        {

        };

        struct Template
        {

        };



        class TypeSystem
        {
            friend class CompoundDef;
            std::vector<std::unique_ptr<BaseDef>> _all;

            std::unordered_map<std::string_view, CompoundDef*> allCompoundDefs_;
            std::unordered_map<MemberDefKey, MemberDef*> allMemberDefs_;
            std::unordered_map<std::string_view, CompoundDef*> rootCompoundDefs_;
            std::multimap<std::string_view, NamespaceCompoundDef*> namespaceMap_;
            std::vector<NamespaceCompoundDef*> namespaces_;
        public:
            HCC_EXPORT TypeSystem( );
            HCC_EXPORT ~TypeSystem( );
            HCC_EXPORT void Process( const DocumentCollection& documentCollection );

            const std::unordered_map<std::string_view, CompoundDef*>& AllCompoundDefs( ) const { return allCompoundDefs_; }
            const std::unordered_map<MemberDefKey, MemberDef*>& AllMemberDefs( ) const { return allMemberDefs_; }
            const std::unordered_map<std::string_view, CompoundDef*>& RootCompoundDefs( ) const { return rootCompoundDefs_; }

            const std::multimap<std::string_view, NamespaceCompoundDef*>& NamespaceMap( ) const { return namespaceMap_; }
            const std::vector<NamespaceCompoundDef*>& Namespaces( ) const { return namespaces_; }
        private:
            void ScanSections( const CompoundDefTypePtr& compoundDefTypePtr, CompoundDef* compoundDef );
            
            static bool ParentNamespaceName( std::string_view compoundName, std::string& parentCompoundName );
            CompoundDef* FindCompoundDefByName( const std::string_view& compoundName );
            NamespaceCompoundDef* FindNamespace( const std::string_view& compoundName );
            //NamespaceCompoundDef* CreateNamespace( const std::string_view& compoundName );
            //void CreateMissingNamespaces( );

        private:
            template<typename T, typename ContainerT, typename DefPtrT>
            T* Add( ContainerT& container, const DefPtrT& defPtr )
            {
                const auto& id = defPtr->Id( );
                auto it = container.find( id );
                if ( it != container.end( ) )
                {
                    return static_cast< T* >( it->second );
                }
                auto ptr = std::make_unique<T>( this, defPtr );
                auto result = ptr.get( );
                _all.emplace_back( std::move( ptr ) );
                container.emplace( id, result );
                return result;
            }

            template<typename T>
            T* AddCompoundDef( const CompoundDefTypePtr& compoundDefPtr )
            {
                return Add<T>( allCompoundDefs_, compoundDefPtr );
            }

            CompoundDef* AddCompoundDef( const CompoundDefTypePtr& compoundDefPtr );

            CompoundDef* AddCompoundDef( const std::string& id, DoxCompoundKind kind, const std::string& compoundName, DoxLanguage language )
            {
                return AddCompoundDef( std::make_shared<CompoundDefType>( id, kind, compoundName, language ) );
            }


            template<typename T>
            T* AddMemberDef(const MemberDefKey& key, const MemberDefTypePtr& memberDef )
            {
                auto it = allMemberDefs_.find( key );
                if ( it != allMemberDefs_.end( ) )
                {
                    return nullptr;
                    //throw std::exception( "Duplicate not allowed." );
                }
                auto ptr = std::make_unique<T>( this, memberDef );
                auto result = ptr.get( );
                _all.emplace_back( std::move( ptr ) );
                allMemberDefs_.emplace( key, result );
                return result;
            }

            MemberDef* AddMemberDef( const MemberDefKey& key, const MemberDefTypePtr& memberDef );

            CompoundDef* FindCompoundDef( const std::string_view& id ) const
            {
                auto it = allCompoundDefs_.find( id );
                if ( it != allCompoundDefs_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

            MemberDef* FindMemberDef( const MemberDefKey& key ) const
            {
                auto it = allMemberDefs_.find( key );
                if ( it != allMemberDefs_.end( ) )
                {
                    return it->second;
                }
                return nullptr;
            }

        };

        class BaseDef
        {
            TypeSystem* typeSystem_{};
            std::string_view id_;
            BaseDef* owner_{};
        public:
            BaseDef( TypeSystem* typeSystem, const std::string_view& id )
                : typeSystem_( typeSystem ), id_( id )
            {
            }
            virtual ~BaseDef( ) = default;

            virtual DoxLanguage Language( ) const = 0;

            TypeSystem* Types( ) const { return typeSystem_; }

            const std::string_view& Id( ) const
            {
                return id_;
            }


            BaseDef* Owner( ) const
            {
                return owner_;
            }

            void SetOwner( BaseDef* owner )
            {
                owner_ = owner;
            }

        };


        



        class Inherit
        {
            CompoundDef* base_{};
            DoxProtectionKind prot_{};
            DoxVirtualKind virt_{};
            std::string_view content_;
        public:
            Inherit( ) = default;
            Inherit( CompoundDef* inherits, DoxProtectionKind prot, DoxVirtualKind virt, std::string_view content )
                : base_( inherits ), prot_( prot ), virt_( virt ), content_( content )
            { }

            CompoundDef* Base( ) const { return base_; }
            DoxProtectionKind Protection( ) const { return prot_; }
            DoxVirtualKind Virtual( ) const { return virt_; }
            std::string_view Content( ) const { return content_; }

        };

        class ChildEntry
        {
            CompoundDef* compoundDef_{};
            DoxProtectionKind prot_{};
            bool inline_ = false;
            std::string_view content_;
        public:
            ChildEntry( CompoundDef* compoundDef, DoxProtectionKind prot, bool isInline, std::string_view content )
                : compoundDef_( compoundDef ), prot_( prot ), inline_( isInline ), content_( content )
            { }

            CompoundDef* CompoundDef( ) const { return compoundDef_; }
            DoxProtectionKind Protection( ) const { return prot_; }
            bool Inline( ) const { return inline_; }
            std::string_view Content( ) const { return content_; }

        };

        class MemberEntry
        {
            MemberDef* memberDef_{};
            std::string_view name_;
            std::string_view scope_;
            DoxProtectionKind prot_{};
            DoxVirtualKind virt_{};
            std::string_view ambiguityScope_;
        public:
            MemberEntry( MemberDef* memberDef, std::string_view name, std::string_view scope, DoxProtectionKind prot, DoxVirtualKind virt, std::string_view ambiguityScope = std::string_view() )
                : memberDef_( memberDef ), name_( name ), scope_( scope ), prot_( prot ), virt_( virt ), ambiguityScope_( ambiguityScope )
            { }

            MemberDef* MemberDef( ) const { return memberDef_; }
            const std::string_view& Name( ) const { return name_; }
            const std::string_view& Scope( ) const { return scope_; }
            DoxProtectionKind Protection( ) const { return prot_; }
            DoxVirtualKind Virtual( ) const { return virt_; }
            const std::string_view& AmbiguityScope( ) const { return ambiguityScope_; }

        };


        class CompoundDef : public BaseDef
        {
            friend class TypeSystem;
            CompoundDefTypePtr compoundDefType_;
            std::vector<Inherit> inherits_;
            std::vector<MemberEntry> members_;
            std::unordered_map<std::string_view, MemberEntry> membersMap_;
            std::vector<ChildEntry> children_;
            std::unordered_map<std::string_view, ChildEntry> childrenMap_;
            std::vector<ChildEntry> references_;
            std::unordered_map<std::string_view, ChildEntry> referenceMap_;
        public:
            using Base = BaseDef;

            CompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType->Id( ) ), compoundDefType_( compoundDefType )
            {
            }

            

            const CompoundDefTypePtr& Def( ) const
            {
                return compoundDefType_;
            }

            const std::vector<Inherit>& Inherits( ) const { return inherits_; }
            const std::vector<MemberEntry>& Members( ) const { return members_; }
            const std::unordered_map<std::string_view, MemberEntry>& MembersById( ) const { return membersMap_; }
            const std::vector<ChildEntry>& Children( ) const { return children_; }
            const std::unordered_map<std::string_view, ChildEntry>& ChildrenById( ) const { return childrenMap_; }

            DoxCompoundKind Kind( ) const
            {
                return compoundDefType_->Kind( );
            }

            DoxLanguage Language( ) const
            {
                auto result = compoundDefType_->Language( );
                if ( result == DoxLanguage::Unknown )
                {
                    auto owner = static_cast< CompoundDef* >( Owner( ) );
                    if ( owner )
                    {
                        result = owner->Language( );
                    }
                }
                return result;
            }

            DoxProtectionKind Protection( ) const 
            { 
                return compoundDefType_->Prot( );
            }

            DoxProtectionKind AccessSpecifier( ) const
            {
                return Protection( );
            }

            bool Final( ) const 
            { 
                return compoundDefType_->Final();
            }
            bool Inline( ) const 
            { 
                return compoundDefType_->Inline( );
            }
            bool Sealed( ) const 
            { 
                return compoundDefType_->Sealed( );
            }
            bool Abstract( ) const 
            { 
                return compoundDefType_->Abstract( );
            }
            const std::string& CompoundName( ) const 
            { 
                return compoundDefType_->CompoundName( );
            }
            const std::string& QualifiedName( ) const
            {
                return CompoundName( );
            }

            std::string CompoundBaseName( ) const
            {
                auto owner = static_cast<CompoundDef*>( Owner( ) );
                if ( owner )
                {
                    const std::string& ownerCompoundName = owner->CompoundName( );
                    auto ownerCompoundNameLength = ownerCompoundName.length( );
                    const std::string& compoundName = CompoundName( );
                    auto index = compoundName.find_first_of( '<', ownerCompoundNameLength );
                    if ( index != std::string::npos )
                    {
                        return compoundName.substr( 0, index );
                    }
                    return compoundName;
                }
                else
                {

                    const std::string& compoundName = CompoundName( );
                    auto index = compoundName.find_first_of( '<' );
                    if ( index != std::string::npos )
                    {
                        return compoundName.substr( 0, index );
                    }
                    return compoundName;
                }
            }

            std::string Name( ) const
            {
                auto owner = static_cast< CompoundDef* >( Owner( ) );
                if ( owner )
                {
                    const std::string& ownerCompoundName = owner->CompoundName( );
                    auto ownerCompoundNameLength = ownerCompoundName.length( );
                    const std::string& compoundName = CompoundName( );
                    
                    if ( ownerCompoundNameLength > compoundName.length( ) + 2 )
                    {
                        auto start = ownerCompoundNameLength;
                        if ( compoundName[ start ] == ':' || compoundName[ start ] == '.' )
                        {
                            start++;
                        }
                        if ( compoundName[ start ] == ':' )
                        {
                            start++;
                        }
                        return compoundName.substr( start );
                    }
                    return compoundName;
                }
                else
                {
                    return CompoundName( );
                }
            }

            std::string NamespaceName( ) const
            {
                auto owner = static_cast< CompoundDef* >( Owner( ) );
                if ( owner )
                {
                    if ( owner->Kind( ) == DoxCompoundKind::Namespace )
                    {
                        return owner->QualifiedName( );
                    }
                    else
                    {
                        return owner->NamespaceName( );
                    }
                }
                return {};
            }




            const std::string& Title( ) const 
            { 
                const std::string& title = compoundDefType_->Title( );
                if ( title.length( ) == 0 )
                {
                    return CompoundName( );
                }
                return title;
            }
            const std::vector<std::string>& Qualifiers( ) const 
            { 
                return compoundDefType_->Qualifier( );
            }
            const TemplateParamListTypePtr& TemplateParamList( ) const 
            { 
                return compoundDefType_->TemplateParamList( );
            }
            
            const LinkedTextTypePtr& RequiresClause( ) const 
            { 
                return compoundDefType_->RequiresClause( );
            }
            const LinkedTextTypePtr& Initializer( ) const 
            { 
                return compoundDefType_->Initializer( );
            }
            const DescriptionTypePtr& BriefDescription( ) const 
            { 
                return compoundDefType_->BriefDescription( );
            }
            const DescriptionTypePtr& DetailedDescription( ) const 
            { 
                return compoundDefType_->DetailedDescription( );
            }
            const ExportsTypePtr& Exports( ) const 
            { 
                return compoundDefType_->Exports( );
            }



        private:
            void Process( );

            void ProcessChildren( const std::vector<RefTypePtr>& children );

        };

        class ClassCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ClassCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class StructCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            StructCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class UnionCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            UnionCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class InterfaceCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            InterfaceCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ProtocolCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ProtocolCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class CategoryCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            CategoryCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ExceptionCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ExceptionCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ServiceCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ServiceCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class SingletonCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            SingletonCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ModuleCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ModuleCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class TypeCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            TypeCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class FileCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            FileCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class NamespaceCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            NamespaceCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class GroupCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            GroupCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class PageCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            PageCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ExampleCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ExampleCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class DirCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            DirCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };
        class ConceptCompoundDef : public CompoundDef
        {
        public:
            using Base = CompoundDef;

            ConceptCompoundDef( TypeSystem* typeSystem, const CompoundDefTypePtr& compoundDefType )
                : Base( typeSystem, compoundDefType )
            {
            }
        };


        inline CompoundDef* TypeSystem::AddCompoundDef( const CompoundDefTypePtr& compoundDefPtr )
        {

            auto kind = compoundDefPtr->Kind( );
            switch ( kind )
            {
                case DoxCompoundKind::Class:
                    return AddCompoundDef<ClassCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Struct:
                    return AddCompoundDef<StructCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Union:
                    return AddCompoundDef<UnionCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Interface:
                    return AddCompoundDef<InterfaceCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Protocol:
                    return AddCompoundDef<ProtocolCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Category:
                    return AddCompoundDef<CategoryCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Exception:
                    return AddCompoundDef<ExceptionCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Service:
                    return AddCompoundDef<ServiceCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Singleton:
                    return AddCompoundDef<SingletonCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Module:
                    return AddCompoundDef<ModuleCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Type:
                    return AddCompoundDef<TypeCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::File:
                    return AddCompoundDef<FileCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Namespace:
                    return AddCompoundDef<NamespaceCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Group:
                    return AddCompoundDef<GroupCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Page:
                    return AddCompoundDef<PageCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Example:
                    return AddCompoundDef<ExampleCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Dir:
                    return AddCompoundDef<DirCompoundDef>( compoundDefPtr );
                    break;
                case DoxCompoundKind::Concept:
                    return AddCompoundDef<ConceptCompoundDef>( compoundDefPtr );
                    break;
            }
            return nullptr;
        }


        class MemberDef : public BaseDef
        {
            MemberDefTypePtr memberDefType_;
        public:
            using Base = BaseDef;

            MemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType->Id( ) ), memberDefType_( memberDefType )
            {
            }

            virtual DoxLanguage Language( ) const override
            {
                auto owner = static_cast< CompoundDef* >( Owner( ) );
                if ( owner )
                {
                    return owner->Language( );
                }
                return DoxLanguage::Unknown;
            }

            const MemberDefTypePtr& Def( ) const
            {
                return memberDefType_;
            }

            DoxMemberKind Kind( ) const 
            { 
                return memberDefType_->Kind( );
            }
            const std::string& Id( ) const 
            {
                return memberDefType_->Id( );
            }
            DoxProtectionKind Protection( ) const 
            { 
                return memberDefType_->Prot( );
            }
            bool Static( ) const 
            { 
                return memberDefType_->Static( );
            }
            bool Extern( ) const 
            { 
                return memberDefType_->Extern( );
            }
            
            bool Const( ) const 
            { 
                return memberDefType_->Const( );
            }
            bool Explicit( ) const 
            { 
                return memberDefType_->Explicit( );
            }
            bool Inline( ) const 
            { 
                return memberDefType_->Inline( );
            }
            DoxRefQualifierKind RefQual( ) const 
            { 
                return memberDefType_->RefQual( );
            }
            DoxVirtualKind Virtual( ) const 
            { 
                return memberDefType_->Virt( );
            }
            bool Volatile( ) const 
            { 
                return memberDefType_->Volatile( );
            }
            bool Mutable( ) const 
            { 
                return memberDefType_->Mutable( );
            }
            bool NoExcept( ) const 
            { 
                return memberDefType_->NoExcept( );
            }
            const std::string& NoexceptExpression( ) const 
            { 
                return memberDefType_->NoexceptExpression( );
            }
            bool Nodiscard( ) const 
            { 
                return memberDefType_->Nodiscard( );
            }
            bool Constexpr( ) const 
            { 
                return memberDefType_->Constexpr( );
            }
            bool Consteval( ) const 
            { 
                return memberDefType_->Consteval( );
            }
            bool Constinit( ) const 
            { 
                return memberDefType_->Constinit( );
            }
            bool Readable( ) const 
            { 
                return memberDefType_->Readable( );
            }
            bool Writable( ) const 
            { 
                return memberDefType_->Writable( );
            }
            bool InitOnly( ) const 
            { 
                return memberDefType_->InitOnly( );
            }
            bool Settable( ) const 
            { 
                return memberDefType_->Settable( );
            }
            bool PrivateSettable( ) const 
            { 
                return memberDefType_->PrivateSettable( );
            }
            bool ProtectedSettable( ) const 
            { 
                return memberDefType_->ProtectedSettable( );
            }
            bool Gettable( ) const 
            { 
                return memberDefType_->Gettable( );
            }
            bool PrivateGettable( ) const 
            { 
                return memberDefType_->PrivateGettable( );
            }
            bool ProtectedGettable( ) const 
            { 
                return memberDefType_->ProtectedGettable( );
            }
            bool Final( ) const 
            { 
                return memberDefType_->Final( );
            }
            bool Sealed( ) const 
            { 
                return memberDefType_->Sealed( );
            }
            bool New( ) const 
            { 
                return memberDefType_->New( );
            }
            bool Add( ) const 
            { 
                return memberDefType_->Add( );
            }
            bool Remove( ) const 
            { 
                return memberDefType_->Remove( );
            }
            bool Raise( ) const 
            { 
                return memberDefType_->Raise( );
            }
            bool Optional( ) const 
            { 
                return memberDefType_->Optional( );
            }
            bool Required( ) const 
            { 
                return memberDefType_->Required( );
            }
            bool Accessor( ) const 
            { 
                return memberDefType_->Accessor( );
            }
            bool Attribute( ) const 
            { 
                return memberDefType_->Attribute( );
            }
            bool Property( ) const 
            { 
                return memberDefType_->Property( );
            }
            bool Readonly( ) const 
            { 
                return memberDefType_->Readonly( );
            }
            bool Bound( ) const 
            { 
                return memberDefType_->Bound( );
            }
            bool Removable( ) const 
            { 
                return memberDefType_->Removable( );
            }
            bool Constrained( ) const 
            { 
                return memberDefType_->Constrained( );
            }
            bool Transient( ) const 
            { 
                return memberDefType_->Transient( );
            }
            bool MaybeVoid( ) const 
            { 
                return memberDefType_->MaybeVoid( );
            }
            bool MaybeDefault( ) const 
            { 
                return memberDefType_->MaybeDefault( );
            }
            bool MaybeAmbiguous( ) const 
            { 
                return memberDefType_->MaybeAmbiguous( );
            }

            const TemplateParamListTypePtr& TemplateParameterList( ) const 
            { 
                return memberDefType_->TemplateParamList( );
            }
            const LinkedTextTypePtr& Type( ) const 
            { 
                return memberDefType_->Type( );
            }
            const std::string& Definition( ) const 
            { 
                return memberDefType_->Definition( );
            }
            const std::string& ArgsString( ) const 
            { 
                return memberDefType_->ArgsString( );
            }
            const std::string& Name( ) const 
            { 
                return memberDefType_->Name( );
            }
            const std::string& QualifiedName( ) const 
            { 
                return memberDefType_->QualifiedName( );
            }
            const std::string& Read( ) const 
            { 
                return memberDefType_->Read( );
            }
            const std::string& Write( ) const 
            { 
                return memberDefType_->Write( );
            }
            const std::string& BitField( ) const 
            { 
                return memberDefType_->BitField( );
            }
            const std::vector<ReimplementTypePtr>& Reimplements( ) const 
            { 
                return memberDefType_->Reimplements( );
            }

            const std::vector<ReimplementTypePtr>& ReimplementedBy( ) const 
            { 
                return memberDefType_->ReimplementedBy( );
            }
            const std::string& Qualifier( ) const 
            { 
                return memberDefType_->Qualifier( );
            }
            const std::vector<ParamTypePtr>& Parameters( ) const 
            { 
                return memberDefType_->Param( );
            }
            const std::vector<EnumvalueTypePtr>& Enumvalues( ) const 
            { 
                return memberDefType_->Enumvalue( );
            }
            const LinkedTextTypePtr& RequiresClause( ) const 
            { 
                return memberDefType_->RequiresClause( );
            }
            const LinkedTextTypePtr& Initializer( ) const 
            { 
                return memberDefType_->Initializer( );
            }
            const LinkedTextTypePtr& Exceptions( ) const 
            { 
                return memberDefType_->Exceptions( );
            }
            const DescriptionTypePtr& BriefDescription( ) const 
            { 
                return memberDefType_->BriefDescription( );
            }
            const DescriptionTypePtr& DetailedDescription( ) const 
            { 
                return memberDefType_->DetailedDescription( );
            }
            const DescriptionTypePtr& InbodyDescription( ) const 
            { 
                return memberDefType_->InbodyDescription( );
            }
            const LocationTypePtr& Location( ) const 
            { 
                return memberDefType_->Location( );
            }
            const std::vector<ReferenceTypePtr>& References( ) const 
            { 
                return memberDefType_->References( );
            }
            const std::vector<ReferenceTypePtr>& ReferencedBy( ) const 
            { 
                return memberDefType_->ReferencedBy( );
            }

        };

        class DefineMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            DefineMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class PropertyMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            PropertyMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class EventMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            EventMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class VariableMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            VariableMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class TypedefMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            TypedefMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class EnumMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            EnumMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };



        class FunctionMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            FunctionMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class SignalMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            SignalMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class PrototypeMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            PrototypeMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class FriendMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            FriendMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class DCopMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            DCopMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class SlotMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            SlotMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class InterfaceMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            InterfaceMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };
        class ServiceMemberDef : public MemberDef
        {
        public:
            using Base = MemberDef;

            ServiceMemberDef( TypeSystem* typeSystem, const MemberDefTypePtr& memberDefType )
                : Base( typeSystem, memberDefType )
            {
            }
        };

        inline MemberDef* TypeSystem::AddMemberDef( const MemberDefKey& key, const MemberDefTypePtr& memberDef )
        {
            auto kind = memberDef->Kind( );
            switch ( kind )
            {
                case DoxMemberKind::Define:
                    return AddMemberDef<DefineMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Property:
                    return AddMemberDef<PropertyMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Event:
                    return AddMemberDef<EventMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Variable:
                    return AddMemberDef<VariableMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Typedef:
                    return AddMemberDef<TypedefMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Enum:
                    return AddMemberDef<EnumMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Function:
                    return AddMemberDef<FunctionMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Signal:
                    return AddMemberDef<SignalMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Prototype:
                    return AddMemberDef<PrototypeMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Friend:
                    return AddMemberDef<FriendMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::DCop:
                    return AddMemberDef<DCopMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Slot:
                    return AddMemberDef<SlotMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Interface:
                    return AddMemberDef<InterfaceMemberDef>( key, memberDef );
                    break;
                case DoxMemberKind::Service:
                    return AddMemberDef<ServiceMemberDef>( key, memberDef );
                    break;
            }
            return nullptr;
        }

    }


}


namespace Harlinn::Common::Core
{
    HCC_EXPORT std::string to_string( Doxygen::MemberKind value );
    HCC_EXPORT std::string to_string( Doxygen::MemberKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::MemberKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::MemberKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT MemberKind ParseMemberKind( const std::string& str );
        HCC_EXPORT MemberKind ParseMemberKind( const std::string& str, MemberKind defaultResult );
        HCC_EXPORT bool TryParseMemberKind( const std::string& str, MemberKind& value );

        inline MemberKind ParseMemberKind( const std::wstring& str )
        {
            return ParseMemberKind( to_string( str ) );
        }
        inline MemberKind ParseMemberKind( const std::wstring& str, MemberKind defaultResult )
        {
            return ParseMemberKind( to_string( str ), defaultResult );
        }
        inline bool TryParseMemberKind( const std::wstring& str, MemberKind& value )
        {
            return TryParseMemberKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::MemberKind& value )
    {
        return Doxygen::TryParseMemberKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::MemberKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::MemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseMemberKind( std::basic_string<CharT>( str ) );
    }


    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxGraphRelation value );
    HCC_EXPORT std::string to_string( Doxygen::DoxGraphRelation value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxGraphRelation value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxGraphRelation value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxGraphRelation ParseDoxGraphRelation( const std::string& str );
        HCC_EXPORT DoxGraphRelation ParseDoxGraphRelation( const std::string& str, DoxGraphRelation defaultResult );
        HCC_EXPORT bool TryParseDoxGraphRelation( const std::string& str, DoxGraphRelation& value );

        inline DoxGraphRelation ParseDoxGraphRelation( const std::wstring& str )
        {
            return ParseDoxGraphRelation( to_string( str ) );
        }
        inline DoxGraphRelation ParseDoxGraphRelation( const std::wstring& str, DoxGraphRelation defaultResult )
        {
            return ParseDoxGraphRelation( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxGraphRelation( const std::wstring& str, DoxGraphRelation& value )
        {
            return TryParseDoxGraphRelation( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxGraphRelation& value )
    {
        return Doxygen::TryParseDoxGraphRelation( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxGraphRelation, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxGraphRelation( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxGraphRelation, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxGraphRelation( std::basic_string<CharT>(str) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxRefKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxRefKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxRefKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxRefKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxRefKind ParseDoxRefKind( const std::string& str );
        HCC_EXPORT DoxRefKind ParseDoxRefKind( const std::string& str, DoxRefKind defaultResult );
        HCC_EXPORT bool TryParseDoxRefKind( const std::string& str, DoxRefKind& value );

        inline DoxRefKind ParseDoxRefKind( const std::wstring& str )
        {
            return ParseDoxRefKind( to_string( str ) );
        }
        inline DoxRefKind ParseDoxRefKind( const std::wstring& str, DoxRefKind defaultResult )
        {
            return ParseDoxRefKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxRefKind( const std::wstring& str, DoxRefKind& value )
        {
            return TryParseDoxRefKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxRefKind& value )
    {
        return Doxygen::TryParseDoxRefKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxRefKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxRefKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxMemberKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxMemberKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxMemberKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxMemberKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxMemberKind ParseDoxMemberKind( const std::string& str );
        HCC_EXPORT DoxMemberKind ParseDoxMemberKind( const std::string& str, DoxMemberKind defaultResult );
        HCC_EXPORT bool TryParseDoxMemberKind( const std::string& str, DoxMemberKind& value );

        inline DoxMemberKind ParseDoxMemberKind( const std::wstring& str )
        {
            return ParseDoxMemberKind( to_string( str ) );
        }
        inline DoxMemberKind ParseDoxMemberKind( const std::wstring& str, DoxMemberKind defaultResult )
        {
            return ParseDoxMemberKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxMemberKind( const std::wstring& str, DoxMemberKind& value )
        {
            return TryParseDoxMemberKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxMemberKind& value )
    {
        return Doxygen::TryParseDoxMemberKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxMemberKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxMemberKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxMemberKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxMemberKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxProtectionKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxProtectionKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxProtectionKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxProtectionKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxProtectionKind ParseDoxProtectionKind( const std::string& str );
        HCC_EXPORT DoxProtectionKind ParseDoxProtectionKind( const std::string& str, DoxProtectionKind defaultResult );
        HCC_EXPORT bool TryParseDoxProtectionKind( const std::string& str, DoxProtectionKind& value );

        inline DoxProtectionKind ParseDoxProtectionKind( const std::wstring& str )
        {
            return ParseDoxProtectionKind( to_string( str ) );
        }
        inline DoxProtectionKind ParseDoxProtectionKind( const std::wstring& str, DoxProtectionKind defaultResult )
        {
            return ParseDoxProtectionKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxProtectionKind( const std::wstring& str, DoxProtectionKind& value )
        {
            return TryParseDoxProtectionKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxProtectionKind& value )
    {
        return Doxygen::TryParseDoxProtectionKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxProtectionKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxProtectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxProtectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxProtectionKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxRefQualifierKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxRefQualifierKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxRefQualifierKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxRefQualifierKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxRefQualifierKind ParseDoxRefQualifierKind( const std::string& str );
        HCC_EXPORT DoxRefQualifierKind ParseDoxRefQualifierKind( const std::string& str, DoxRefQualifierKind defaultResult );
        HCC_EXPORT bool TryParseDoxRefQualifierKind( const std::string& str, DoxRefQualifierKind& value );

        inline DoxRefQualifierKind ParseDoxRefQualifierKind( const std::wstring& str )
        {
            return ParseDoxRefQualifierKind( to_string( str ) );
        }
        inline DoxRefQualifierKind ParseDoxRefQualifierKind( const std::wstring& str, DoxRefQualifierKind defaultResult )
        {
            return ParseDoxRefQualifierKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxRefQualifierKind( const std::wstring& str, DoxRefQualifierKind& value )
        {
            return TryParseDoxRefQualifierKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxRefQualifierKind& value )
    {
        return Doxygen::TryParseDoxRefQualifierKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxRefQualifierKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxRefQualifierKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxRefQualifierKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxRefQualifierKind( std::basic_string<CharT>( str ) );
    }


    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxLanguage value );
    HCC_EXPORT std::string to_string( Doxygen::DoxLanguage value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxLanguage value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxLanguage value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxLanguage ParseDoxLanguage( const std::string& str );
        HCC_EXPORT DoxLanguage ParseDoxLanguage( const std::string& str, DoxLanguage defaultResult );
        HCC_EXPORT bool TryParseDoxLanguage( const std::string& str, DoxLanguage& value );

        inline DoxLanguage ParseDoxLanguage( const std::wstring& str )
        {
            return ParseDoxLanguage( to_string( str ) );
        }
        inline DoxLanguage ParseDoxLanguage( const std::wstring& str, DoxLanguage defaultResult )
        {
            return ParseDoxLanguage( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxLanguage( const std::wstring& str, DoxLanguage& value )
        {
            return TryParseDoxLanguage( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxLanguage& value )
    {
        return Doxygen::TryParseDoxLanguage( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxLanguage, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxLanguage( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxLanguage, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxLanguage( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxVirtualKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxVirtualKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxVirtualKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxVirtualKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxVirtualKind ParseDoxVirtualKind( const std::string& str );
        HCC_EXPORT DoxVirtualKind ParseDoxVirtualKind( const std::string& str, DoxVirtualKind defaultResult );
        HCC_EXPORT bool TryParseDoxVirtualKind( const std::string& str, DoxVirtualKind& value );

        inline DoxVirtualKind ParseDoxVirtualKind( const std::wstring& str )
        {
            return ParseDoxVirtualKind( to_string( str ) );
        }
        inline DoxVirtualKind ParseDoxVirtualKind( const std::wstring& str, DoxVirtualKind defaultResult )
        {
            return ParseDoxVirtualKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxVirtualKind( const std::wstring& str, DoxVirtualKind& value )
        {
            return TryParseDoxVirtualKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxVirtualKind& value )
    {
        return Doxygen::TryParseDoxVirtualKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxVirtualKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxVirtualKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVirtualKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVirtualKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxCompoundKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxCompoundKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxCompoundKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxCompoundKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCompoundKind ParseDoxCompoundKind( const std::string& str );
        HCC_EXPORT DoxCompoundKind ParseDoxCompoundKind( const std::string& str, DoxCompoundKind defaultResult );
        HCC_EXPORT bool TryParseDoxCompoundKind( const std::string& str, DoxCompoundKind& value );

        inline DoxCompoundKind ParseDoxCompoundKind( const std::wstring& str )
        {
            return ParseDoxCompoundKind( to_string( str ) );
        }
        inline DoxCompoundKind ParseDoxCompoundKind( const std::wstring& str, DoxCompoundKind defaultResult )
        {
            return ParseDoxCompoundKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxCompoundKind( const std::wstring& str, DoxCompoundKind& value )
        {
            return TryParseDoxCompoundKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxCompoundKind& value )
    {
        return Doxygen::TryParseDoxCompoundKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCompoundKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCompoundKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCompoundKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCompoundKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxSectionKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxSectionKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxSectionKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxSectionKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxSectionKind ParseDoxSectionKind( const std::string& str );
        HCC_EXPORT DoxSectionKind ParseDoxSectionKind( const std::string& str, DoxSectionKind defaultResult );
        HCC_EXPORT bool TryParseDoxSectionKind( const std::string& str, DoxSectionKind& value );

        inline DoxSectionKind ParseDoxSectionKind( const std::wstring& str )
        {
            return ParseDoxSectionKind( to_string( str ) );
        }
        inline DoxSectionKind ParseDoxSectionKind( const std::wstring& str, DoxSectionKind defaultResult )
        {
            return ParseDoxSectionKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxSectionKind( const std::wstring& str, DoxSectionKind& value )
        {
            return TryParseDoxSectionKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxSectionKind& value )
    {
        return Doxygen::TryParseDoxSectionKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxSectionKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxSectionKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSectionKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSectionKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxHighlightClass value );
    HCC_EXPORT std::string to_string( Doxygen::DoxHighlightClass value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxHighlightClass value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxHighlightClass value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxHighlightClass ParseDoxHighlightClass( const std::string& str );
        HCC_EXPORT DoxHighlightClass ParseDoxHighlightClass( const std::string& str, DoxHighlightClass defaultResult );
        HCC_EXPORT bool TryParseDoxHighlightClass( const std::string& str, DoxHighlightClass& value );

        inline DoxHighlightClass ParseDoxHighlightClass( const std::wstring& str )
        {
            return ParseDoxHighlightClass( to_string( str ) );
        }
        inline DoxHighlightClass ParseDoxHighlightClass( const std::wstring& str, DoxHighlightClass defaultResult )
        {
            return ParseDoxHighlightClass( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxHighlightClass( const std::wstring& str, DoxHighlightClass& value )
        {
            return TryParseDoxHighlightClass( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxHighlightClass& value )
    {
        return Doxygen::TryParseDoxHighlightClass( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxHighlightClass, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxHighlightClass( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxHighlightClass, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxHighlightClass( std::basic_string<CharT>( str ) );
    }
    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxSimpleSectKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxSimpleSectKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxSimpleSectKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxSimpleSectKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxSimpleSectKind ParseDoxSimpleSectKind( const std::string& str );
        HCC_EXPORT DoxSimpleSectKind ParseDoxSimpleSectKind( const std::string& str, DoxSimpleSectKind defaultResult );
        HCC_EXPORT bool TryParseDoxSimpleSectKind( const std::string& str, DoxSimpleSectKind& value );

        inline DoxSimpleSectKind ParseDoxSimpleSectKind( const std::wstring& str )
        {
            return ParseDoxSimpleSectKind( to_string( str ) );
        }
        inline DoxSimpleSectKind ParseDoxSimpleSectKind( const std::wstring& str, DoxSimpleSectKind defaultResult )
        {
            return ParseDoxSimpleSectKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxSimpleSectKind( const std::wstring& str, DoxSimpleSectKind& value )
        {
            return TryParseDoxSimpleSectKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxSimpleSectKind& value )
    {
        return Doxygen::TryParseDoxSimpleSectKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxSimpleSectKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxSimpleSectKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxSimpleSectKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxSimpleSectKind( std::basic_string<CharT>(str) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxCheck value );
    HCC_EXPORT std::string to_string( Doxygen::DoxCheck value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxCheck value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxCheck value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCheck ParseDoxCheck( const std::string& str );
        HCC_EXPORT DoxCheck ParseDoxCheck( const std::string& str, DoxCheck defaultResult );
        HCC_EXPORT bool TryParseDoxCheck( const std::string& str, DoxCheck& value );

        inline DoxCheck ParseDoxCheck( const std::wstring& str )
        {
            return ParseDoxCheck( to_string( str ) );
        }
        inline DoxCheck ParseDoxCheck( const std::wstring& str, DoxCheck defaultResult )
        {
            return ParseDoxCheck( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxCheck( const std::wstring& str, DoxCheck& value )
        {
            return TryParseDoxCheck( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxCheck& value )
    {
        return Doxygen::TryParseDoxCheck( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCheck, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCheck( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCheck, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCheck( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxImageKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxImageKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxImageKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxImageKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxImageKind ParseDoxImageKind( const std::string& str );
        HCC_EXPORT DoxImageKind ParseDoxImageKind( const std::string& str, DoxImageKind defaultResult );
        HCC_EXPORT bool TryParseDoxImageKind( const std::string& str, DoxImageKind& value );

        inline DoxImageKind ParseDoxImageKind( const std::wstring& str )
        {
            return ParseDoxImageKind( to_string( str ) );
        }
        inline DoxImageKind ParseDoxImageKind( const std::wstring& str, DoxImageKind defaultResult )
        {
            return ParseDoxImageKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxImageKind( const std::wstring& str, DoxImageKind& value )
        {
            return TryParseDoxImageKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxImageKind& value )
    {
        return Doxygen::TryParseDoxImageKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxImageKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxImageKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxImageKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxImageKind( std::basic_string<CharT>( str ) );
    }



    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxPlantumlEngine value );
    HCC_EXPORT std::string to_string( Doxygen::DoxPlantumlEngine value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxPlantumlEngine value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxPlantumlEngine value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxPlantumlEngine ParseDoxPlantumlEngine( const std::string& str );
        HCC_EXPORT DoxPlantumlEngine ParseDoxPlantumlEngine( const std::string& str, DoxPlantumlEngine defaultResult );
        HCC_EXPORT bool TryParseDoxPlantumlEngine( const std::string& str, DoxPlantumlEngine& value );

        inline DoxPlantumlEngine ParseDoxPlantumlEngine( const std::wstring& str )
        {
            return ParseDoxPlantumlEngine( to_string( str ) );
        }
        inline DoxPlantumlEngine ParseDoxPlantumlEngine( const std::wstring& str, DoxPlantumlEngine defaultResult )
        {
            return ParseDoxPlantumlEngine( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxPlantumlEngine( const std::wstring& str, DoxPlantumlEngine& value )
        {
            return TryParseDoxPlantumlEngine( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxPlantumlEngine& value )
    {
        return Doxygen::TryParseDoxPlantumlEngine( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxPlantumlEngine, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxPlantumlEngine( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxPlantumlEngine, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxPlantumlEngine( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxParamListKind value );
    HCC_EXPORT std::string to_string( Doxygen::DoxParamListKind value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxParamListKind value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxParamListKind value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxParamListKind ParseDoxParamListKind( const std::string& str );
        HCC_EXPORT DoxParamListKind ParseDoxParamListKind( const std::string& str, DoxParamListKind defaultResult );
        HCC_EXPORT bool TryParseDoxParamListKind( const std::string& str, DoxParamListKind& value );

        inline DoxParamListKind ParseDoxParamListKind( const std::wstring& str )
        {
            return ParseDoxParamListKind( to_string( str ) );
        }
        inline DoxParamListKind ParseDoxParamListKind( const std::wstring& str, DoxParamListKind defaultResult )
        {
            return ParseDoxParamListKind( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxParamListKind( const std::wstring& str, DoxParamListKind& value )
        {
            return TryParseDoxParamListKind( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxParamListKind& value )
    {
        return Doxygen::TryParseDoxParamListKind( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxParamListKind, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxParamListKind( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamListKind, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamListKind( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxParamDir value );
    HCC_EXPORT std::string to_string( Doxygen::DoxParamDir value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxParamDir value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxParamDir value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxParamDir ParseDoxParamDir( const std::string& str );
        HCC_EXPORT DoxParamDir ParseDoxParamDir( const std::string& str, DoxParamDir defaultResult );
        HCC_EXPORT bool TryParseDoxParamDir( const std::string& str, DoxParamDir& value );

        inline DoxParamDir ParseDoxParamDir( const std::wstring& str )
        {
            return ParseDoxParamDir( to_string( str ) );
        }
        inline DoxParamDir ParseDoxParamDir( const std::wstring& str, DoxParamDir defaultResult )
        {
            return ParseDoxParamDir( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxParamDir( const std::wstring& str, DoxParamDir& value )
        {
            return TryParseDoxParamDir( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxParamDir& value )
    {
        return Doxygen::TryParseDoxParamDir( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxParamDir, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxParamDir( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxParamDir, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxParamDir( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxAccessor value );
    HCC_EXPORT std::string to_string( Doxygen::DoxAccessor value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxAccessor value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxAccessor value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxAccessor ParseDoxAccessor( const std::string& str );
        HCC_EXPORT DoxAccessor ParseDoxAccessor( const std::string& str, DoxAccessor defaultResult );
        HCC_EXPORT bool TryParseDoxAccessor( const std::string& str, DoxAccessor& value );

        inline DoxAccessor ParseDoxAccessor( const std::wstring& str )
        {
            return ParseDoxAccessor( to_string( str ) );
        }
        inline DoxAccessor ParseDoxAccessor( const std::wstring& str, DoxAccessor defaultResult )
        {
            return ParseDoxAccessor( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxAccessor( const std::wstring& str, DoxAccessor& value )
        {
            return TryParseDoxAccessor( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxAccessor& value )
    {
        return Doxygen::TryParseDoxAccessor( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxAccessor, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxAccessor( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAccessor, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAccessor( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxAlign value );
    HCC_EXPORT std::string to_string( Doxygen::DoxAlign value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxAlign value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxAlign value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxAlign ParseDoxAlign( const std::string& str );
        HCC_EXPORT DoxAlign ParseDoxAlign( const std::string& str, DoxAlign defaultResult );
        HCC_EXPORT bool TryParseDoxAlign( const std::string& str, DoxAlign& value );

        inline DoxAlign ParseDoxAlign( const std::wstring& str )
        {
            return ParseDoxAlign( to_string( str ) );
        }
        inline DoxAlign ParseDoxAlign( const std::wstring& str, DoxAlign defaultResult )
        {
            return ParseDoxAlign( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxAlign( const std::wstring& str, DoxAlign& value )
        {
            return TryParseDoxAlign( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxAlign& value )
    {
        return Doxygen::TryParseDoxAlign( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxAlign, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxAlign( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxVerticalAlign value );
    HCC_EXPORT std::string to_string( Doxygen::DoxVerticalAlign value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxVerticalAlign value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxVerticalAlign value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxVerticalAlign ParseDoxVerticalAlign( const std::string& str );
        HCC_EXPORT DoxVerticalAlign ParseDoxVerticalAlign( const std::string& str, DoxVerticalAlign defaultResult );
        HCC_EXPORT bool TryParseDoxVerticalAlign( const std::string& str, DoxVerticalAlign& value );

        inline DoxVerticalAlign ParseDoxVerticalAlign( const std::wstring& str )
        {
            return ParseDoxVerticalAlign( to_string( str ) );
        }
        inline DoxVerticalAlign ParseDoxVerticalAlign( const std::wstring& str, DoxVerticalAlign defaultResult )
        {
            return ParseDoxVerticalAlign( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxVerticalAlign( const std::wstring& str, DoxVerticalAlign& value )
        {
            return TryParseDoxVerticalAlign( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxVerticalAlign& value )
    {
        return Doxygen::TryParseDoxVerticalAlign( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxVerticalAlign, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxVerticalAlign( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxVerticalAlign, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxVerticalAlign( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxOlType value );
    HCC_EXPORT std::string to_string( Doxygen::DoxOlType value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxOlType value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxOlType value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxOlType ParseDoxOlType( const std::string& str );
        HCC_EXPORT DoxOlType ParseDoxOlType( const std::string& str, DoxOlType defaultResult );
        HCC_EXPORT bool TryParseDoxOlType( const std::string& str, DoxOlType& value );

        inline DoxOlType ParseDoxOlType( const std::wstring& str )
        {
            return ParseDoxOlType( to_string( str ) );
        }
        inline DoxOlType ParseDoxOlType( const std::wstring& str, DoxOlType defaultResult )
        {
            return ParseDoxOlType( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxOlType( const std::wstring& str, DoxOlType& value )
        {
            return TryParseDoxOlType( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxOlType& value )
    {
        return Doxygen::TryParseDoxOlType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxOlType, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxOlType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxOlType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxOlType( std::basic_string<CharT>( str ) );
    }


    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxCmdGroupType value );
    HCC_EXPORT std::string to_string( Doxygen::DoxCmdGroupType value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxCmdGroupType value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxCmdGroupType value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxCmdGroupType ParseDoxCmdGroupType( const std::string& str );
        HCC_EXPORT DoxCmdGroupType ParseDoxCmdGroupType( const std::string& str, DoxCmdGroupType defaultResult );
        HCC_EXPORT bool TryParseDoxCmdGroupType( const std::string& str, DoxCmdGroupType& value );

        inline DoxCmdGroupType ParseDoxCmdGroupType( const std::wstring& str )
        {
            return ParseDoxCmdGroupType( to_string( str ) );
        }
        inline DoxCmdGroupType ParseDoxCmdGroupType( const std::wstring& str, DoxCmdGroupType defaultResult )
        {
            return ParseDoxCmdGroupType( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxCmdGroupType( const std::wstring& str, DoxCmdGroupType& value )
        {
            return TryParseDoxCmdGroupType( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxCmdGroupType& value )
    {
        return Doxygen::TryParseDoxCmdGroupType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxCmdGroupType, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxCmdGroupType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxCmdGroupType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxCmdGroupType( std::basic_string<CharT>( str ) );
    }

    /////////
    HCC_EXPORT std::string to_string( Doxygen::DoxType value );
    HCC_EXPORT std::string to_string( Doxygen::DoxType value, const std::string& defaultResult );

    inline std::wstring to_wstring( Doxygen::DoxType value )
    {
        return to_wstring( to_string( value ) );
    }
    inline std::wstring to_wstring( Doxygen::DoxType value, const std::wstring& defaultResult )
    {
        return to_wstring( to_string( value, to_string( defaultResult ) ) );
    }

    namespace Doxygen
    {
        HCC_EXPORT DoxType ParseDoxType( const std::string& str );
        HCC_EXPORT DoxType ParseDoxType( const std::string& str, DoxType defaultResult );
        HCC_EXPORT bool TryParseDoxType( const std::string& str, DoxType& value );

        inline DoxType ParseDoxType( const std::wstring& str )
        {
            return ParseDoxType( to_string( str ) );
        }
        inline DoxType ParseDoxType( const std::wstring& str, DoxType defaultResult )
        {
            return ParseDoxType( to_string( str ), defaultResult );
        }
        inline bool TryParseDoxType( const std::wstring& str, DoxType& value )
        {
            return TryParseDoxType( to_string( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring>
    inline bool TryParse( const StringT& str, Doxygen::DoxType& value )
    {
        return Doxygen::TryParseDoxType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Doxygen::DoxType, T> && ( std::is_same_v<StringT, std::string> || std::is_same_v<StringT, std::wstring> )
    inline T Parse( const StringT& str )
    {
        return Doxygen::ParseDoxType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Doxygen::DoxType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Doxygen::ParseDoxType( std::basic_string<CharT>( str ) );
    }

}


#endif
