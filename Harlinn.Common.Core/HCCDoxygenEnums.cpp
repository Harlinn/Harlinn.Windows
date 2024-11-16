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
#include "HCCFlags.h"

namespace Harlinn::Common::Core
{

    /////////
    namespace
    {
        using MemberKind = Doxygen::MemberKind;
        class MemberKindConverter : public Enum<MemberKind>
        {
        public:
            using Base = Enum<MemberKind>;
            MemberKindConverter( )
            {
                Add( WideString(L"define"), MemberKind::Define);
                Add( WideString(L"property"), MemberKind::Property);
                Add( WideString(L"event"), MemberKind::Event);
                Add( WideString(L"variable"), MemberKind::Variable);
                Add( WideString(L"typedef"), MemberKind::Typedef);
                Add( WideString(L"enum"), MemberKind::Enum);
                Add( WideString(L"enumvalue"), MemberKind::Enumvalue);
                Add( WideString(L"function"), MemberKind::Function);
                Add( WideString(L"signal"), MemberKind::Signal);
                Add( WideString(L"prototype"), MemberKind::Prototype);
                Add( WideString(L"friend"), MemberKind::Friend);
                Add( WideString(L"dcop"), MemberKind::DCop);
                Add( WideString(L"slot"), MemberKind::Slot);
            }
        };

        MemberKindConverter staticMemberKindConverter;
    }

    WideString ToWideString( MemberKind value )
    {
        return staticMemberKindConverter.ToString( value );
    }
    WideString ToWideString( MemberKind value, const WideString& defaultResult )
    {
        return staticMemberKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        MemberKind ParseMemberKind( const WideString& str )
        {
            return staticMemberKindConverter.Parse( str );
        }

        MemberKind ParseMemberKind( const WideString& str, MemberKind defaultResult )
        {
            return staticMemberKindConverter.Parse( str, defaultResult );
        }

        bool TryParseMemberKind( const WideString& str, MemberKind& value )
        {
            return staticMemberKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxGraphRelation = Doxygen::DoxGraphRelation;
        class DoxGraphRelationConverter : public Enum<DoxGraphRelation>
        {
        public:
            using Base = Enum<DoxGraphRelation>;
            DoxGraphRelationConverter( )
            {
                Add( WideString(L"include"), DoxGraphRelation::Include);
                Add( WideString(L"usage"), DoxGraphRelation::Usage);
                Add( WideString(L"template-instance"), DoxGraphRelation::TemplateInstance);
                Add( WideString(L"public-inheritance"), DoxGraphRelation::PublicInheritance);
                Add( WideString(L"protected-inheritance"), DoxGraphRelation::ProtectedInheritance);
                Add( WideString(L"private-inheritance"), DoxGraphRelation::PrivateInheritance);
                Add( WideString(L"type-constraint"), DoxGraphRelation::TypeConstraint );
            }
        };

        DoxGraphRelationConverter staticDoxGraphRelationConverter;
    }

    WideString ToWideString( DoxGraphRelation value )
    {
        return staticDoxGraphRelationConverter.ToString( value );
    }
    WideString ToWideString( DoxGraphRelation value, const WideString& defaultResult )
    {
        return staticDoxGraphRelationConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxGraphRelation ParseDoxGraphRelation( const WideString& str )
        {
            return staticDoxGraphRelationConverter.Parse( str );
        }

        DoxGraphRelation ParseDoxGraphRelation( const WideString& str, DoxGraphRelation defaultResult )
        {
            return staticDoxGraphRelationConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxGraphRelation( const WideString& str, DoxGraphRelation& value )
        {
            return staticDoxGraphRelationConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxRefKind = Doxygen::DoxRefKind;
        class DoxRefKindConverter : public Enum<DoxRefKind>
        {
        public:
            using Base = Enum<DoxRefKind>;
            DoxRefKindConverter( )
            {
                Add( WideString(L"compound"), DoxRefKind::Compound);
                Add( WideString(L"member"), DoxRefKind::Member );
            }
        };

        DoxRefKindConverter staticDoxRefKindConverter;
    }

    WideString ToWideString( DoxRefKind value )
    {
        return staticDoxRefKindConverter.ToString( value );
    }
    WideString ToWideString( DoxRefKind value, const WideString& defaultResult )
    {
        return staticDoxRefKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxRefKind ParseDoxRefKind( const WideString& str )
        {
            return staticDoxRefKindConverter.Parse( str );
        }

        DoxRefKind ParseDoxRefKind( const WideString& str, DoxRefKind defaultResult )
        {
            return staticDoxRefKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxRefKind( const WideString& str, DoxRefKind& value )
        {
            return staticDoxRefKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxMemberKind = Doxygen::DoxMemberKind;
        class DoxMemberKindConverter : public Enum<DoxMemberKind>
        {
        public:
            using Base = Enum<DoxMemberKind>;
            DoxMemberKindConverter( )
            {
                Add( WideString(L"define"), DoxMemberKind::Define);
                Add( WideString(L"property"), DoxMemberKind::Property);
                Add( WideString(L"event"), DoxMemberKind::Event);
                Add( WideString(L"variable"), DoxMemberKind::Variable);
                Add( WideString(L"typedef"), DoxMemberKind::Typedef);
                Add( WideString(L"enum"), DoxMemberKind::Enum);
                Add( WideString(L"function"), DoxMemberKind::Function);
                Add( WideString(L"signal"), DoxMemberKind::Signal);
                Add( WideString(L"prototype"), DoxMemberKind::Prototype);
                Add( WideString(L"friend"), DoxMemberKind::Friend);
                Add( WideString(L"dcop"), DoxMemberKind::DCop);
                Add( WideString(L"slot"), DoxMemberKind::Slot);
                Add( WideString(L"interface"), DoxMemberKind::Interface);
                Add( WideString(L"service"), DoxMemberKind::Service );
            }
        };

        DoxMemberKindConverter staticDoxMemberKindConverter;
    }

    WideString ToWideString( DoxMemberKind value )
    {
        return staticDoxMemberKindConverter.ToString( value );
    }
    WideString ToWideString( DoxMemberKind value, const WideString& defaultResult )
    {
        return staticDoxMemberKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxMemberKind ParseDoxMemberKind( const WideString& str )
        {
            return staticDoxMemberKindConverter.Parse( str );
        }

        DoxMemberKind ParseDoxMemberKind( const WideString& str, DoxMemberKind defaultResult )
        {
            return staticDoxMemberKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxMemberKind( const WideString& str, DoxMemberKind& value )
        {
            return staticDoxMemberKindConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxProtectionKind = Doxygen::DoxProtectionKind;
        class DoxProtectionKindConverter : public Enum<DoxProtectionKind>
        {
        public:
            using Base = Enum<DoxProtectionKind>;
            DoxProtectionKindConverter( )
            {
                Add( WideString(L"public"), DoxProtectionKind::Public);
                Add( WideString(L"protected"), DoxProtectionKind::Protected);
                Add( WideString(L"private"), DoxProtectionKind::Private);
                Add( WideString(L"package"), DoxProtectionKind::Package );
            }
        };

        DoxProtectionKindConverter staticDoxProtectionKindConverter;
    }

    WideString ToWideString( DoxProtectionKind value )
    {
        return staticDoxProtectionKindConverter.ToString( value );
    }
    WideString ToWideString( DoxProtectionKind value, const WideString& defaultResult )
    {
        return staticDoxProtectionKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxProtectionKind ParseDoxProtectionKind( const WideString& str )
        {
            return staticDoxProtectionKindConverter.Parse( str );
        }

        DoxProtectionKind ParseDoxProtectionKind( const WideString& str, DoxProtectionKind defaultResult )
        {
            return staticDoxProtectionKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxProtectionKind( const WideString& str, DoxProtectionKind& value )
        {
            return staticDoxProtectionKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxRefQualifierKind = Doxygen::DoxRefQualifierKind;
        class DoxRefQualifierKindConverter : public Enum<DoxRefQualifierKind>
        {
        public:
            using Base = Enum<DoxRefQualifierKind>;
            DoxRefQualifierKindConverter( )
            {
                Add( WideString(L"lvalue"), DoxRefQualifierKind::LValue );
                Add( WideString(L"rvalue"), DoxRefQualifierKind::RValue );
            }
        };

        DoxRefQualifierKindConverter staticDoxRefQualifierKindConverter;
    }

    WideString ToWideString( DoxRefQualifierKind value )
    {
        return staticDoxRefQualifierKindConverter.ToString( value );
    }
    WideString ToWideString( DoxRefQualifierKind value, const WideString& defaultResult )
    {
        return staticDoxRefQualifierKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxRefQualifierKind ParseDoxRefQualifierKind( const WideString& str )
        {
            return staticDoxRefQualifierKindConverter.Parse( str );
        }

        DoxRefQualifierKind ParseDoxRefQualifierKind( const WideString& str, DoxRefQualifierKind defaultResult )
        {
            return staticDoxRefQualifierKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxRefQualifierKind( const WideString& str, DoxRefQualifierKind& value )
        {
            return staticDoxRefQualifierKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxLanguage = Doxygen::DoxLanguage;
        class DoxLanguageConverter : public Enum<DoxLanguage>
        {
        public:
            using Base = Enum<DoxLanguage>;
            DoxLanguageConverter( )
            {
                Add( WideString(L"Unknown"), DoxLanguage::Unknown );
                Add( WideString(L"IDL"), DoxLanguage::IDL );
                Add( WideString(L"Java"), DoxLanguage::Java );
                Add( WideString(L"C#"), DoxLanguage::CSharp );
                Add( WideString(L"D"), DoxLanguage::D );
                Add( WideString(L"PHP"), DoxLanguage::PHP );
                Add( WideString(L"Objective-C"), DoxLanguage::ObjectiveC );
                Add( WideString(L"C++"), DoxLanguage::Cpp );
                Add( WideString(L"JavaScript"), DoxLanguage::JavaScript );
                Add( WideString(L"Python"), DoxLanguage::Python );
                Add( WideString(L"Fortran"), DoxLanguage::Fortran );
                Add( WideString(L"VHDL"), DoxLanguage::VHDL );
                Add( WideString(L"XML"), DoxLanguage::XML );
                Add( WideString(L"SQL"), DoxLanguage::SQL );
                Add( WideString(L"Markdown"), DoxLanguage::Markdown );
                Add( WideString(L"Slice"), DoxLanguage::Slice );
                Add( WideString(L"Lex"), DoxLanguage::Lex );
            }
        };

        DoxLanguageConverter staticDoxLanguageConverter;
    }

    WideString ToWideString( DoxLanguage value )
    {
        return staticDoxLanguageConverter.ToString( value );
    }
    WideString ToWideString( DoxLanguage value, const WideString& defaultResult )
    {
        return staticDoxLanguageConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxLanguage ParseDoxLanguage( const WideString& str )
        {
            return staticDoxLanguageConverter.Parse( str );
        }

        DoxLanguage ParseDoxLanguage( const WideString& str, DoxLanguage defaultResult )
        {
            return staticDoxLanguageConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxLanguage( const WideString& str, DoxLanguage& value )
        {
            return staticDoxLanguageConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxVirtualKind = Doxygen::DoxVirtualKind;
        class DoxVirtualKindConverter : public Enum<DoxVirtualKind>
        {
        public:
            using Base = Enum<DoxVirtualKind>;
            DoxVirtualKindConverter( )
            {
                Add( WideString(L"non-virtual"), DoxVirtualKind::NonVirtual );
                Add( WideString(L"virtual"), DoxVirtualKind::Virtual );
                Add( WideString(L"pure-virtual"), DoxVirtualKind::PureVirtual );
            }
        };

        DoxVirtualKindConverter staticDoxVirtualKindConverter;
    }

    WideString ToWideString( DoxVirtualKind value )
    {
        return staticDoxVirtualKindConverter.ToString( value );
    }
    WideString ToWideString( DoxVirtualKind value, const WideString& defaultResult )
    {
        return staticDoxVirtualKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxVirtualKind ParseDoxVirtualKind( const WideString& str )
        {
            return staticDoxVirtualKindConverter.Parse( str );
        }

        DoxVirtualKind ParseDoxVirtualKind( const WideString& str, DoxVirtualKind defaultResult )
        {
            return staticDoxVirtualKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxVirtualKind( const WideString& str, DoxVirtualKind& value )
        {
            return staticDoxVirtualKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxCompoundKind = Doxygen::DoxCompoundKind;
        class DoxCompoundKindConverter : public Enum<DoxCompoundKind>
        {
        public:
            using Base = Enum<DoxCompoundKind>;
            DoxCompoundKindConverter( )
            {
                Add( WideString(L"class"), DoxCompoundKind::Class );
                Add( WideString(L"struct"), DoxCompoundKind::Struct );
                Add( WideString(L"union"), DoxCompoundKind::Union );
                Add( WideString(L"interface"), DoxCompoundKind::Interface );
                Add( WideString(L"protocol"), DoxCompoundKind::Protocol );
                Add( WideString(L"category"), DoxCompoundKind::Category );
                Add( WideString(L"exception"), DoxCompoundKind::Exception );
                Add( WideString(L"service"), DoxCompoundKind::Service );
                Add( WideString(L"singleton"), DoxCompoundKind::Singleton );
                Add( WideString(L"module"), DoxCompoundKind::Module );
                Add( WideString(L"type"), DoxCompoundKind::Type );
                Add( WideString(L"file"), DoxCompoundKind::File );
                Add( WideString(L"namespace"), DoxCompoundKind::Namespace );
                Add( WideString(L"group"), DoxCompoundKind::Group );
                Add( WideString(L"page"), DoxCompoundKind::Page );
                Add( WideString(L"example"), DoxCompoundKind::Example );
                Add( WideString(L"dir"), DoxCompoundKind::Dir );
                Add( WideString(L"concept"), DoxCompoundKind::Concept );
            }
        };

        DoxCompoundKindConverter staticDoxCompoundKindConverter;
    }

    WideString ToWideString( DoxCompoundKind value )
    {
        return staticDoxCompoundKindConverter.ToString( value );
    }
    WideString ToWideString( DoxCompoundKind value, const WideString& defaultResult )
    {
        return staticDoxCompoundKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCompoundKind ParseDoxCompoundKind( const WideString& str )
        {
            return staticDoxCompoundKindConverter.Parse( str );
        }

        DoxCompoundKind ParseDoxCompoundKind( const WideString& str, DoxCompoundKind defaultResult )
        {
            return staticDoxCompoundKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCompoundKind( const WideString& str, DoxCompoundKind& value )
        {
            return staticDoxCompoundKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxSectionKind = Doxygen::DoxSectionKind;
        class DoxSectionKindConverter : public Enum<DoxSectionKind>
        {
        public:
            using Base = Enum<DoxSectionKind>;
            DoxSectionKindConverter( )
            {
                Add( WideString(L"user-defined"), DoxSectionKind::UserDefined );
                Add( WideString(L"public-type"), DoxSectionKind::PublicType );
                Add( WideString(L"public-func"), DoxSectionKind::PublicFunc );
                Add( WideString(L"public-attrib"), DoxSectionKind::PublicAttrib );
                Add( WideString(L"public-slot"), DoxSectionKind::PublicSlot );
                Add( WideString(L"signal"), DoxSectionKind::Signal );
                Add( WideString(L"dcop-func"), DoxSectionKind::DcopFunc );
                Add( WideString(L"property"), DoxSectionKind::Property );
                Add( WideString(L"event"), DoxSectionKind::Event );
                Add( WideString(L"public-static-func"), DoxSectionKind::PublicStaticFunc );
                Add( WideString(L"public-static-attrib"), DoxSectionKind::PublicStaticAttrib );
                Add( WideString(L"protected-type"), DoxSectionKind::ProtectedType );
                Add( WideString(L"protected-func"), DoxSectionKind::ProtectedFunc );
                Add( WideString(L"protected-attrib"), DoxSectionKind::ProtectedAttrib );
                Add( WideString(L"protected-slot"), DoxSectionKind::ProtectedSlot );
                Add( WideString(L"protected-static-func"), DoxSectionKind::ProtectedStaticFunc );
                Add( WideString(L"protected-static-attrib"), DoxSectionKind::ProtectedStaticAttrib );
                Add( WideString(L"package-type"), DoxSectionKind::PackageType );
                Add( WideString(L"package-func"), DoxSectionKind::PackageFunc );
                Add( WideString(L"package-attrib"), DoxSectionKind::PackageAttrib );
                Add( WideString(L"package-static-func"), DoxSectionKind::PackageStaticFunc );
                Add( WideString(L"package-static-attrib"), DoxSectionKind::PackageStaticAttrib );
                Add( WideString(L"private-type"), DoxSectionKind::PrivateType );
                Add( WideString(L"private-func"), DoxSectionKind::PrivateFunc );
                Add( WideString(L"private-attrib"), DoxSectionKind::PrivateAttrib );
                Add( WideString(L"private-slot"), DoxSectionKind::PrivateSlot );
                Add( WideString(L"private-static-func"), DoxSectionKind::PrivateStaticFunc );
                Add( WideString(L"private-static-attrib"), DoxSectionKind::PrivateStaticAttrib );
                Add( WideString(L"friend"), DoxSectionKind::Friend );
                Add( WideString(L"related"), DoxSectionKind::Related );
                Add( WideString(L"define"), DoxSectionKind::Define );
                Add( WideString(L"prototype"), DoxSectionKind::Prototype );
                Add( WideString(L"typedef"), DoxSectionKind::Typedef );
                Add( WideString(L"enum"), DoxSectionKind::Enum );
                Add( WideString(L"func"), DoxSectionKind::Func );
                Add( WideString(L"var"), DoxSectionKind::Var );
            }
        };

        DoxSectionKindConverter staticDoxSectionKindConverter;
    }

    WideString ToWideString( DoxSectionKind value )
    {
        return staticDoxSectionKindConverter.ToString( value );
    }
    WideString ToWideString( DoxSectionKind value, const WideString& defaultResult )
    {
        return staticDoxSectionKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxSectionKind ParseDoxSectionKind( const WideString& str )
        {
            return staticDoxSectionKindConverter.Parse( str );
        }

        DoxSectionKind ParseDoxSectionKind( const WideString& str, DoxSectionKind defaultResult )
        {
            return staticDoxSectionKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxSectionKind( const WideString& str, DoxSectionKind& value )
        {
            return staticDoxSectionKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxHighlightClass = Doxygen::DoxHighlightClass;
        class DoxHighlightClassConverter : public Enum<DoxHighlightClass>
        {
        public:
            using Base = Enum<DoxHighlightClass>;
            DoxHighlightClassConverter( )
            {
                Add( WideString(L"comment"), DoxHighlightClass::Comment );
                Add( WideString(L"normal"), DoxHighlightClass::Normal );
                Add( WideString(L"preprocessor"), DoxHighlightClass::Preprocessor );
                Add( WideString(L"keyword"), DoxHighlightClass::Keyword );
                Add( WideString(L"keywordtype"), DoxHighlightClass::KeywordType );
                Add( WideString(L"keywordflow"), DoxHighlightClass::KeywordFlow );
                Add( WideString(L"stringliteral"), DoxHighlightClass::StringLiteral );
                Add( WideString(L"xmlcdata"), DoxHighlightClass::XmlCData );
                Add( WideString(L"charliteral"), DoxHighlightClass::CharLiteral );
                Add( WideString(L"vhdlkeyword"), DoxHighlightClass::VhdlKeyword );
                Add( WideString(L"vhdllogic"), DoxHighlightClass::VhdlLogic );
                Add( WideString(L"vhdlchar"), DoxHighlightClass::VhdlChar );
                Add( WideString(L"vhdldigit"), DoxHighlightClass::VhdlDigit );
            }
        };

        DoxHighlightClassConverter staticDoxHighlightClassConverter;
    }

    WideString ToWideString( DoxHighlightClass value )
    {
        return staticDoxHighlightClassConverter.ToString( value );
    }
    WideString ToWideString( DoxHighlightClass value, const WideString& defaultResult )
    {
        return staticDoxHighlightClassConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxHighlightClass ParseDoxHighlightClass( const WideString& str )
        {
            return staticDoxHighlightClassConverter.Parse( str );
        }

        DoxHighlightClass ParseDoxHighlightClass( const WideString& str, DoxHighlightClass defaultResult )
        {
            return staticDoxHighlightClassConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxHighlightClass( const WideString& str, DoxHighlightClass& value )
        {
            return staticDoxHighlightClassConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxSimpleSectKind = Doxygen::DoxSimpleSectKind;
        class DoxSimpleSectKindConverter : public Enum<DoxSimpleSectKind>
        {
        public:
            using Base = Enum<DoxSimpleSectKind>;
            DoxSimpleSectKindConverter( )
            {
                Add( WideString(L"see"), DoxSimpleSectKind::See );
                Add( WideString(L"return"), DoxSimpleSectKind::Return );
                Add( WideString(L"author"), DoxSimpleSectKind::Author );
                Add( WideString(L"authors"), DoxSimpleSectKind::Authors );
                Add( WideString(L"version"), DoxSimpleSectKind::Version );
                Add( WideString(L"since"), DoxSimpleSectKind::Since );
                Add( WideString(L"date"), DoxSimpleSectKind::Date );
                Add( WideString(L"note"), DoxSimpleSectKind::Note );
                Add( WideString(L"warning"), DoxSimpleSectKind::Warning );
                Add( WideString(L"pre"), DoxSimpleSectKind::Pre );
                Add( WideString(L"post"), DoxSimpleSectKind::Post );
                Add( WideString(L"copyright"), DoxSimpleSectKind::Copyright );
                Add( WideString(L"invariant"), DoxSimpleSectKind::Invariant );
                Add( WideString(L"remark"), DoxSimpleSectKind::Remark );
                Add( WideString(L"attention"), DoxSimpleSectKind::Attention );
                Add( WideString(L"important"), DoxSimpleSectKind::Important );
                Add( WideString(L"par"), DoxSimpleSectKind::Par );
                Add( WideString(L"rcs"), DoxSimpleSectKind::Rcs );
            }
        };

        DoxSimpleSectKindConverter staticDoxSimpleSectKindConverter;
    }

    WideString ToWideString( DoxSimpleSectKind value )
    {
        return staticDoxSimpleSectKindConverter.ToString( value );
    }
    WideString ToWideString( DoxSimpleSectKind value, const WideString& defaultResult )
    {
        return staticDoxSimpleSectKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxSimpleSectKind ParseDoxSimpleSectKind( const WideString& str )
        {
            return staticDoxSimpleSectKindConverter.Parse( str );
        }

        DoxSimpleSectKind ParseDoxSimpleSectKind( const WideString& str, DoxSimpleSectKind defaultResult )
        {
            return staticDoxSimpleSectKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxSimpleSectKind( const WideString& str, DoxSimpleSectKind& value )
        {
            return staticDoxSimpleSectKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxCheck = Doxygen::DoxCheck;
        class DoxCheckConverter : public Enum<DoxCheck>
        {
        public:
            using Base = Enum<DoxCheck>;
            DoxCheckConverter( )
            {
                Add( WideString(L"checked"), DoxCheck::Checked );
                Add( WideString(L"unchecked"), DoxCheck::Unchecked );
            }
        };

        DoxCheckConverter staticDoxCheckConverter;
    }

    WideString ToWideString( DoxCheck value )
    {
        return staticDoxCheckConverter.ToString( value );
    }
    WideString ToWideString( DoxCheck value, const WideString& defaultResult )
    {
        return staticDoxCheckConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCheck ParseDoxCheck( const WideString& str )
        {
            return staticDoxCheckConverter.Parse( str );
        }

        DoxCheck ParseDoxCheck( const WideString& str, DoxCheck defaultResult )
        {
            return staticDoxCheckConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCheck( const WideString& str, DoxCheck& value )
        {
            return staticDoxCheckConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxImageKind = Doxygen::DoxImageKind;
        class DoxImageKindConverter : public Enum<DoxImageKind>
        {
        public:
            using Base = Enum<DoxImageKind>;
            DoxImageKindConverter( )
            {
                Add( WideString(L"html"), DoxImageKind::Html );
                Add( WideString(L"latex"), DoxImageKind::Latex );
                Add( WideString(L"docbook"), DoxImageKind::Docbook );
                Add( WideString(L"rtf"), DoxImageKind::Rtf );
                Add( WideString(L"xml"), DoxImageKind::Xml );
            }
        };

        DoxImageKindConverter staticDoxImageKindConverter;
    }

    WideString ToWideString( DoxImageKind value )
    {
        return staticDoxImageKindConverter.ToString( value );
    }
    WideString ToWideString( DoxImageKind value, const WideString& defaultResult )
    {
        return staticDoxImageKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxImageKind ParseDoxImageKind( const WideString& str )
        {
            return staticDoxImageKindConverter.Parse( str );
        }

        DoxImageKind ParseDoxImageKind( const WideString& str, DoxImageKind defaultResult )
        {
            return staticDoxImageKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxImageKind( const WideString& str, DoxImageKind& value )
        {
            return staticDoxImageKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxPlantumlEngine = Doxygen::DoxPlantumlEngine;
        class DoxPlantumlEngineConverter : public Enum<DoxPlantumlEngine>
        {
        public:
            using Base = Enum<DoxPlantumlEngine>;
            DoxPlantumlEngineConverter( )
            {
                Add( WideString(L"uml"), DoxPlantumlEngine::Uml );
                Add( WideString(L"bpm"), DoxPlantumlEngine::Bpm );
                Add( WideString(L"wire"), DoxPlantumlEngine::Wire );
                Add( WideString(L"dot"), DoxPlantumlEngine::Dot );
                Add( WideString(L"ditaa"), DoxPlantumlEngine::Ditaa );
                Add( WideString(L"salt"), DoxPlantumlEngine::Salt );
                Add( WideString(L"math"), DoxPlantumlEngine::Math );
                Add( WideString(L"latex"), DoxPlantumlEngine::Latex );
                Add( WideString(L"gantt"), DoxPlantumlEngine::Gantt );
                Add( WideString(L"mindmap"), DoxPlantumlEngine::Mindmap );
                Add( WideString(L"wbs"), DoxPlantumlEngine::Wbs );
                Add( WideString(L"yaml"), DoxPlantumlEngine::Yaml );
                Add( WideString(L"creole"), DoxPlantumlEngine::Creole );
                Add( WideString(L"json"), DoxPlantumlEngine::Json );
                Add( WideString(L"flow"), DoxPlantumlEngine::Flow );
                Add( WideString(L"board"), DoxPlantumlEngine::Board );
                Add( WideString(L"git"), DoxPlantumlEngine::Git );
                Add( WideString(L"hcl"), DoxPlantumlEngine::Hcl );
                Add( WideString(L"regex"), DoxPlantumlEngine::Regex );
                Add( WideString(L"ebnf"), DoxPlantumlEngine::Ebnf );
                Add( WideString(L"files"), DoxPlantumlEngine::Files );
            }
        };

        DoxPlantumlEngineConverter staticDoxPlantumlEngineConverter;
    }

    WideString ToWideString( DoxPlantumlEngine value )
    {
        return staticDoxPlantumlEngineConverter.ToString( value );
    }
    WideString ToWideString( DoxPlantumlEngine value, const WideString& defaultResult )
    {
        return staticDoxPlantumlEngineConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxPlantumlEngine ParseDoxPlantumlEngine( const WideString& str )
        {
            return staticDoxPlantumlEngineConverter.Parse( str );
        }

        DoxPlantumlEngine ParseDoxPlantumlEngine( const WideString& str, DoxPlantumlEngine defaultResult )
        {
            return staticDoxPlantumlEngineConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxPlantumlEngine( const WideString& str, DoxPlantumlEngine& value )
        {
            return staticDoxPlantumlEngineConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxParamListKind = Doxygen::DoxParamListKind;
        class DoxParamListKindConverter : public Enum<DoxParamListKind>
        {
        public:
            using Base = Enum<DoxParamListKind>;
            DoxParamListKindConverter( )
            {
                Add( WideString(L"param"), DoxParamListKind::Param );
                Add( WideString(L"retval"), DoxParamListKind::Retval );
                Add( WideString(L"exception"), DoxParamListKind::Exception );
                Add( WideString(L"templateparam"), DoxParamListKind::TemplateParam );
            }
        };

        DoxParamListKindConverter staticDoxParamListKindConverter;
    }

    WideString ToWideString( DoxParamListKind value )
    {
        return staticDoxParamListKindConverter.ToString( value );
    }
    WideString ToWideString( DoxParamListKind value, const WideString& defaultResult )
    {
        return staticDoxParamListKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxParamListKind ParseDoxParamListKind( const WideString& str )
        {
            return staticDoxParamListKindConverter.Parse( str );
        }

        DoxParamListKind ParseDoxParamListKind( const WideString& str, DoxParamListKind defaultResult )
        {
            return staticDoxParamListKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxParamListKind( const WideString& str, DoxParamListKind& value )
        {
            return staticDoxParamListKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxParamDir = Doxygen::DoxParamDir;
        class DoxParamDirConverter : public Enum<DoxParamDir>
        {
        public:
            using Base = Enum<DoxParamDir>;
            DoxParamDirConverter( )
            {
                Add( WideString(L"in"), DoxParamDir::In );
                Add( WideString(L"out"), DoxParamDir::Out );
                Add( WideString(L"inout"), DoxParamDir::InOut );
            }
        };

        DoxParamDirConverter staticDoxParamDirConverter;
    }

    WideString ToWideString( DoxParamDir value )
    {
        return staticDoxParamDirConverter.ToString( value );
    }
    WideString ToWideString( DoxParamDir value, const WideString& defaultResult )
    {
        return staticDoxParamDirConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxParamDir ParseDoxParamDir( const WideString& str )
        {
            return staticDoxParamDirConverter.Parse( str );
        }

        DoxParamDir ParseDoxParamDir( const WideString& str, DoxParamDir defaultResult )
        {
            return staticDoxParamDirConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxParamDir( const WideString& str, DoxParamDir& value )
        {
            return staticDoxParamDirConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxAccessor = Doxygen::DoxAccessor;
        class DoxAccessorConverter : public Enum<DoxAccessor>
        {
        public:
            using Base = Enum<DoxAccessor>;
            DoxAccessorConverter( )
            {
                Add( WideString(L"retain"), DoxAccessor::Retain );
                Add( WideString(L"copy"), DoxAccessor::Copy );
                Add( WideString(L"assign"), DoxAccessor::Assign );
                Add( WideString(L"weak"), DoxAccessor::Weak );
                Add( WideString(L"strong"), DoxAccessor::Strong );
                Add( WideString(L"unretained"), DoxAccessor::Unretained );
            }
        };

        DoxAccessorConverter staticDoxAccessorConverter;
    }

    WideString ToWideString( DoxAccessor value )
    {
        return staticDoxAccessorConverter.ToString( value );
    }
    WideString ToWideString( DoxAccessor value, const WideString& defaultResult )
    {
        return staticDoxAccessorConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxAccessor ParseDoxAccessor( const WideString& str )
        {
            return staticDoxAccessorConverter.Parse( str );
        }

        DoxAccessor ParseDoxAccessor( const WideString& str, DoxAccessor defaultResult )
        {
            return staticDoxAccessorConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxAccessor( const WideString& str, DoxAccessor& value )
        {
            return staticDoxAccessorConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxAlign = Doxygen::DoxAlign;
        class DoxAlignConverter : public Enum<DoxAlign>
        {
        public:
            using Base = Enum<DoxAlign>;
            DoxAlignConverter( )
            {
                Add( WideString(L"left"), DoxAlign::Left );
                Add( WideString(L"right"), DoxAlign::Right );
                Add( WideString(L"center"), DoxAlign::Center );
            }
        };

        DoxAlignConverter staticDoxAlignConverter;
    }

    WideString ToWideString( DoxAlign value )
    {
        return staticDoxAlignConverter.ToString( value );
    }
    WideString ToWideString( DoxAlign value, const WideString& defaultResult )
    {
        return staticDoxAlignConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxAlign ParseDoxAlign( const WideString& str )
        {
            return staticDoxAlignConverter.Parse( str );
        }

        DoxAlign ParseDoxAlign( const WideString& str, DoxAlign defaultResult )
        {
            return staticDoxAlignConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxAlign( const WideString& str, DoxAlign& value )
        {
            return staticDoxAlignConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxVerticalAlign = Doxygen::DoxVerticalAlign;
        class DoxVerticalAlignConverter : public Enum<DoxVerticalAlign>
        {
        public:
            using Base = Enum<DoxVerticalAlign>;
            DoxVerticalAlignConverter( )
            {
                Add( WideString(L"bottom"), DoxVerticalAlign::Bottom );
                Add( WideString(L"top"), DoxVerticalAlign::Top );
                Add( WideString(L"middle"), DoxVerticalAlign::Middle );
            }
        };

        DoxVerticalAlignConverter staticDoxVerticalAlignConverter;
    }

    WideString ToWideString( DoxVerticalAlign value )
    {
        return staticDoxVerticalAlignConverter.ToString( value );
    }
    WideString ToWideString( DoxVerticalAlign value, const WideString& defaultResult )
    {
        return staticDoxVerticalAlignConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxVerticalAlign ParseDoxVerticalAlign( const WideString& str )
        {
            return staticDoxVerticalAlignConverter.Parse( str );
        }

        DoxVerticalAlign ParseDoxVerticalAlign( const WideString& str, DoxVerticalAlign defaultResult )
        {
            return staticDoxVerticalAlignConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxVerticalAlign( const WideString& str, DoxVerticalAlign& value )
        {
            return staticDoxVerticalAlignConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxOlType = Doxygen::DoxOlType;
        class DoxOlTypeConverter : public Enum<DoxOlType>
        {
        public:
            using Base = Enum<DoxOlType>;
            DoxOlTypeConverter( )
            {
                Add( WideString(L"1"), DoxOlType::Numbered);
                Add( WideString(L"a"), DoxOlType::a);
                Add( WideString(L"A"), DoxOlType::A);
                Add( WideString(L"i"), DoxOlType::i);
                Add( WideString(L"I"), DoxOlType::I);
            }
        };

        DoxOlTypeConverter staticDoxOlTypeConverter;
    }

    WideString ToWideString( DoxOlType value )
    {
        return staticDoxOlTypeConverter.ToString( value );
    }
    WideString ToWideString( DoxOlType value, const WideString& defaultResult )
    {
        return staticDoxOlTypeConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxOlType ParseDoxOlType( const WideString& str )
        {
            return staticDoxOlTypeConverter.Parse( str );
        }

        DoxOlType ParseDoxOlType( const WideString& str, DoxOlType defaultResult )
        {
            return staticDoxOlTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxOlType( const WideString& str, DoxOlType& value )
        {
            return staticDoxOlTypeConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxCmdGroupType = Doxygen::DoxCmdGroupType;
        class DoxCmdGroupTypeConverter : public Enum<DoxCmdGroupType>
        {
        public:
            using Base = Enum<DoxCmdGroupType>;
            DoxCmdGroupTypeConverter( )
            {
                Add( WideString(L"ulink"), DoxCmdGroupType::ulink );
                Add( WideString(L"bold"), DoxCmdGroupType::bold );
                Add( WideString(L"s"), DoxCmdGroupType::s );
                Add( WideString(L"strike"), DoxCmdGroupType::strike );
                Add( WideString(L"underline"), DoxCmdGroupType::underline );
                Add( WideString(L"emphasis"), DoxCmdGroupType::emphasis );
                Add( WideString(L"computeroutput"), DoxCmdGroupType::computeroutput );
                Add( WideString(L"subscript"), DoxCmdGroupType::subscript );
                Add( WideString(L"superscript"), DoxCmdGroupType::superscript );
                Add( WideString(L"center"), DoxCmdGroupType::center );
                Add( WideString(L"small"), DoxCmdGroupType::Small );
                Add( WideString(L"cite"), DoxCmdGroupType::cite );
                Add( WideString(L"del"), DoxCmdGroupType::del );
                Add( WideString(L"ins"), DoxCmdGroupType::ins );
                Add( WideString(L"htmlonly"), DoxCmdGroupType::htmlonly );
                Add( WideString(L"manonly"), DoxCmdGroupType::manonly );
                Add( WideString(L"xmlonly"), DoxCmdGroupType::xmlonly );
                Add( WideString(L"rtfonly"), DoxCmdGroupType::rtfonly );
                Add( WideString(L"latexonly"), DoxCmdGroupType::latexonly );
                Add( WideString(L"docbookonly"), DoxCmdGroupType::docbookonly );
                Add( WideString(L"image"), DoxCmdGroupType::image );
                Add( WideString(L"dot"), DoxCmdGroupType::dot );
                Add( WideString(L"msc"), DoxCmdGroupType::msc );
                Add( WideString(L"plantuml"), DoxCmdGroupType::plantuml );
                Add( WideString(L"anchor"), DoxCmdGroupType::anchor );
                Add( WideString(L"formula"), DoxCmdGroupType::formula );
                Add( WideString(L"ref"), DoxCmdGroupType::ref );
                Add( WideString(L"emoji"), DoxCmdGroupType::emoji );
                Add( WideString(L"linebreak"), DoxCmdGroupType::linebreak );
                Add( WideString(L"nonbreakablespace"), DoxCmdGroupType::nonbreakablespace );
                Add( WideString(L"iexcl"), DoxCmdGroupType::iexcl );
                Add( WideString(L"cent"), DoxCmdGroupType::cent );
                Add( WideString(L"pound"), DoxCmdGroupType::pound );
                Add( WideString(L"curren"), DoxCmdGroupType::curren );
                Add( WideString(L"yen"), DoxCmdGroupType::yen );
                Add( WideString(L"brvbar"), DoxCmdGroupType::brvbar );
                Add( WideString(L"sect"), DoxCmdGroupType::sect );
                Add( WideString(L"umlaut"), DoxCmdGroupType::umlaut );
                Add( WideString(L"copy"), DoxCmdGroupType::copy );
                Add( WideString(L"ordf"), DoxCmdGroupType::ordf );
                Add( WideString(L"laquo"), DoxCmdGroupType::laquo );
                Add( WideString(L"not"), DoxCmdGroupType::Not );
                Add( WideString(L"shy"), DoxCmdGroupType::shy );
                Add( WideString(L"registered"), DoxCmdGroupType::registered );
                Add( WideString(L"macr"), DoxCmdGroupType::macr );
                Add( WideString(L"deg"), DoxCmdGroupType::deg );
                Add( WideString(L"plusmn"), DoxCmdGroupType::plusmn );
                Add( WideString(L"sup2"), DoxCmdGroupType::sup2 );
                Add( WideString(L"sup3"), DoxCmdGroupType::sup3 );
                Add( WideString(L"acute"), DoxCmdGroupType::acute );
                Add( WideString(L"micro"), DoxCmdGroupType::micro );
                Add( WideString(L"para"), DoxCmdGroupType::para );
                Add( WideString(L"middot"), DoxCmdGroupType::middot );
                Add( WideString(L"cedil"), DoxCmdGroupType::cedil );
                Add( WideString(L"sup1"), DoxCmdGroupType::sup1 );
                Add( WideString(L"ordm"), DoxCmdGroupType::ordm );
                Add( WideString(L"raquo"), DoxCmdGroupType::raquo );
                Add( WideString(L"frac14"), DoxCmdGroupType::frac14 );
                Add( WideString(L"frac12"), DoxCmdGroupType::frac12 );
                Add( WideString(L"frac34"), DoxCmdGroupType::frac34 );
                Add( WideString(L"iquest"), DoxCmdGroupType::iquest );
                Add( WideString(L"Agrave"), DoxCmdGroupType::Agrave );
                Add( WideString(L"Aacute"), DoxCmdGroupType::Aacute );
                Add( WideString(L"Acirc"), DoxCmdGroupType::Acirc );
                Add( WideString(L"Atilde"), DoxCmdGroupType::Atilde );
                Add( WideString(L"Aumlaut"), DoxCmdGroupType::Aumlaut );
                Add( WideString(L"Aring"), DoxCmdGroupType::Aring );
                Add( WideString(L"AElig"), DoxCmdGroupType::AElig );
                Add( WideString(L"Ccedil"), DoxCmdGroupType::Ccedil );
                Add( WideString(L"Egrave"), DoxCmdGroupType::Egrave );
                Add( WideString(L"Eacute"), DoxCmdGroupType::Eacute );
                Add( WideString(L"Ecirc"), DoxCmdGroupType::Ecirc );
                Add( WideString(L"Eumlaut"), DoxCmdGroupType::Eumlaut );
                Add( WideString(L"Igrave"), DoxCmdGroupType::Igrave );
                Add( WideString(L"Iacute"), DoxCmdGroupType::Iacute );
                Add( WideString(L"Icirc"), DoxCmdGroupType::Icirc );
                Add( WideString(L"Iumlaut"), DoxCmdGroupType::Iumlaut );
                Add( WideString(L"ETH"), DoxCmdGroupType::ETH );
                Add( WideString(L"Ntilde"), DoxCmdGroupType::Ntilde );
                Add( WideString(L"Ograve"), DoxCmdGroupType::Ograve );
                Add( WideString(L"Oacute"), DoxCmdGroupType::Oacute );
                Add( WideString(L"Ocirc"), DoxCmdGroupType::Ocirc );
                Add( WideString(L"Otilde"), DoxCmdGroupType::Otilde );
                Add( WideString(L"Oumlaut"), DoxCmdGroupType::Oumlaut );
                Add( WideString(L"times"), DoxCmdGroupType::times );
                Add( WideString(L"Oslash"), DoxCmdGroupType::Oslash );
                Add( WideString(L"Ugrave"), DoxCmdGroupType::Ugrave );
                Add( WideString(L"Uacute"), DoxCmdGroupType::Uacute );
                Add( WideString(L"Ucirc"), DoxCmdGroupType::Ucirc );
                Add( WideString(L"Uumlaut"), DoxCmdGroupType::Uumlaut );
                Add( WideString(L"Yacute"), DoxCmdGroupType::Yacute );
                Add( WideString(L"THORN"), DoxCmdGroupType::THORN );
                Add( WideString(L"szlig"), DoxCmdGroupType::szlig );
                Add( WideString(L"agrave"), DoxCmdGroupType::agrave );
                Add( WideString(L"aacute"), DoxCmdGroupType::aacute );
                Add( WideString(L"acirc"), DoxCmdGroupType::acirc );
                Add( WideString(L"atilde"), DoxCmdGroupType::atilde );
                Add( WideString(L"aumlaut"), DoxCmdGroupType::aumlaut );
                Add( WideString(L"aring"), DoxCmdGroupType::aring );
                Add( WideString(L"aelig"), DoxCmdGroupType::aelig );
                Add( WideString(L"ccedil"), DoxCmdGroupType::ccedil );
                Add( WideString(L"egrave"), DoxCmdGroupType::egrave );
                Add( WideString(L"eacute"), DoxCmdGroupType::eacute );
                Add( WideString(L"ecirc"), DoxCmdGroupType::ecirc );
                Add( WideString(L"eumlaut"), DoxCmdGroupType::eumlaut );
                Add( WideString(L"igrave"), DoxCmdGroupType::igrave );
                Add( WideString(L"iacute"), DoxCmdGroupType::iacute );
                Add( WideString(L"icirc"), DoxCmdGroupType::icirc );
                Add( WideString(L"iumlaut"), DoxCmdGroupType::iumlaut );
                Add( WideString(L"eth"), DoxCmdGroupType::eth );
                Add( WideString(L"ntilde"), DoxCmdGroupType::ntilde );
                Add( WideString(L"ograve"), DoxCmdGroupType::ograve );
                Add( WideString(L"oacute"), DoxCmdGroupType::oacute );
                Add( WideString(L"ocirc"), DoxCmdGroupType::ocirc );
                Add( WideString(L"otilde"), DoxCmdGroupType::otilde );
                Add( WideString(L"oumlaut"), DoxCmdGroupType::oumlaut );
                Add( WideString(L"divide"), DoxCmdGroupType::divide );
                Add( WideString(L"oslash"), DoxCmdGroupType::oslash );
                Add( WideString(L"ugrave"), DoxCmdGroupType::ugrave );
                Add( WideString(L"uacute"), DoxCmdGroupType::uacute );
                Add( WideString(L"ucirc"), DoxCmdGroupType::ucirc );
                Add( WideString(L"uumlaut"), DoxCmdGroupType::uumlaut );
                Add( WideString(L"yacute"), DoxCmdGroupType::yacute );
                Add( WideString(L"thorn"), DoxCmdGroupType::thorn );
                Add( WideString(L"yumlaut"), DoxCmdGroupType::yumlaut );
                Add( WideString(L"fnof"), DoxCmdGroupType::fnof );
                Add( WideString(L"Alpha"), DoxCmdGroupType::Alpha );
                Add( WideString(L"Beta"), DoxCmdGroupType::Beta );
                Add( WideString(L"Gamma"), DoxCmdGroupType::Gamma );
                Add( WideString(L"Delta"), DoxCmdGroupType::Delta );
                Add( WideString(L"Epsilon"), DoxCmdGroupType::Epsilon );
                Add( WideString(L"Zeta"), DoxCmdGroupType::Zeta );
                Add( WideString(L"Eta"), DoxCmdGroupType::Eta );
                Add( WideString(L"Theta"), DoxCmdGroupType::Theta );
                Add( WideString(L"Iota"), DoxCmdGroupType::Iota );
                Add( WideString(L"Kappa"), DoxCmdGroupType::Kappa );
                Add( WideString(L"Lambda"), DoxCmdGroupType::Lambda );
                Add( WideString(L"Mu"), DoxCmdGroupType::Mu );
                Add( WideString(L"Nu"), DoxCmdGroupType::Nu );
                Add( WideString(L"Xi"), DoxCmdGroupType::Xi );
                Add( WideString(L"Omicron"), DoxCmdGroupType::Omicron );
                Add( WideString(L"Pi"), DoxCmdGroupType::Pi );
                Add( WideString(L"Rho"), DoxCmdGroupType::Rho );
                Add( WideString(L"Sigma"), DoxCmdGroupType::Sigma );
                Add( WideString(L"Tau"), DoxCmdGroupType::Tau );
                Add( WideString(L"Upsilon"), DoxCmdGroupType::Upsilon );
                Add( WideString(L"Phi"), DoxCmdGroupType::Phi );
                Add( WideString(L"Chi"), DoxCmdGroupType::Chi );
                Add( WideString(L"Psi"), DoxCmdGroupType::Psi );
                Add( WideString(L"Omega"), DoxCmdGroupType::Omega );
                Add( WideString(L"alpha"), DoxCmdGroupType::alpha );
                Add( WideString(L"beta"), DoxCmdGroupType::beta );
                Add( WideString(L"gamma"), DoxCmdGroupType::gamma );
                Add( WideString(L"delta"), DoxCmdGroupType::delta );
                Add( WideString(L"epsilon"), DoxCmdGroupType::epsilon );
                Add( WideString(L"zeta"), DoxCmdGroupType::zeta );
                Add( WideString(L"eta"), DoxCmdGroupType::eta );
                Add( WideString(L"theta"), DoxCmdGroupType::theta );
                Add( WideString(L"iota"), DoxCmdGroupType::iota );
                Add( WideString(L"kappa"), DoxCmdGroupType::kappa );
                Add( WideString(L"lambda"), DoxCmdGroupType::lambda );
                Add( WideString(L"mu"), DoxCmdGroupType::mu );
                Add( WideString(L"nu"), DoxCmdGroupType::nu );
                Add( WideString(L"xi"), DoxCmdGroupType::xi );
                Add( WideString(L"omicron"), DoxCmdGroupType::omicron );
                Add( WideString(L"pi"), DoxCmdGroupType::pi );
                Add( WideString(L"rho"), DoxCmdGroupType::rho );
                Add( WideString(L"sigmaf"), DoxCmdGroupType::sigmaf );
                Add( WideString(L"sigma"), DoxCmdGroupType::sigma );
                Add( WideString(L"tau"), DoxCmdGroupType::tau );
                Add( WideString(L"upsilon"), DoxCmdGroupType::upsilon );
                Add( WideString(L"phi"), DoxCmdGroupType::phi );
                Add( WideString(L"chi"), DoxCmdGroupType::chi );
                Add( WideString(L"psi"), DoxCmdGroupType::psi );
                Add( WideString(L"omega"), DoxCmdGroupType::omega );
                Add( WideString(L"thetasym"), DoxCmdGroupType::thetasym );
                Add( WideString(L"upsih"), DoxCmdGroupType::upsih );
                Add( WideString(L"piv"), DoxCmdGroupType::piv );
                Add( WideString(L"bull"), DoxCmdGroupType::bull );
                Add( WideString(L"hellip"), DoxCmdGroupType::hellip );
                Add( WideString(L"prime"), DoxCmdGroupType::prime );
                Add( WideString(L"Prime"), DoxCmdGroupType::Prime );
                Add( WideString(L"oline"), DoxCmdGroupType::oline );
                Add( WideString(L"frasl"), DoxCmdGroupType::frasl );
                Add( WideString(L"weierp"), DoxCmdGroupType::weierp );
                Add( WideString(L"imaginary"), DoxCmdGroupType::imaginary );
                Add( WideString(L"real"), DoxCmdGroupType::real );
                Add( WideString(L"trademark"), DoxCmdGroupType::trademark );
                Add( WideString(L"alefsym"), DoxCmdGroupType::alefsym );
                Add( WideString(L"larr"), DoxCmdGroupType::larr );
                Add( WideString(L"uarr"), DoxCmdGroupType::uarr );
                Add( WideString(L"rarr"), DoxCmdGroupType::rarr );
                Add( WideString(L"darr"), DoxCmdGroupType::darr );
                Add( WideString(L"harr"), DoxCmdGroupType::harr );
                Add( WideString(L"crarr"), DoxCmdGroupType::crarr );
                Add( WideString(L"lArr"), DoxCmdGroupType::lArr );
                Add( WideString(L"uArr"), DoxCmdGroupType::uArr );
                Add( WideString(L"rArr"), DoxCmdGroupType::rArr );
                Add( WideString(L"dArr"), DoxCmdGroupType::dArr );
                Add( WideString(L"hArr"), DoxCmdGroupType::hArr );
                Add( WideString(L"forall"), DoxCmdGroupType::forall );
                Add( WideString(L"part"), DoxCmdGroupType::part );
                Add( WideString(L"exist"), DoxCmdGroupType::exist );
                Add( WideString(L"empty"), DoxCmdGroupType::empty );
                Add( WideString(L"nabla"), DoxCmdGroupType::nabla );
                Add( WideString(L"isin"), DoxCmdGroupType::isin );
                Add( WideString(L"notin"), DoxCmdGroupType::notin );
                Add( WideString(L"ni"), DoxCmdGroupType::ni );
                Add( WideString(L"prod"), DoxCmdGroupType::prod );
                Add( WideString(L"sum"), DoxCmdGroupType::sum );
                Add( WideString(L"minus"), DoxCmdGroupType::minus );
                Add( WideString(L"lowast"), DoxCmdGroupType::lowast );
                Add( WideString(L"radic"), DoxCmdGroupType::radic );
                Add( WideString(L"prop"), DoxCmdGroupType::prop );
                Add( WideString(L"infin"), DoxCmdGroupType::infin );
                Add( WideString(L"ang"), DoxCmdGroupType::ang );
                Add( WideString(L"and"), DoxCmdGroupType::And );
                Add( WideString(L"or "), DoxCmdGroupType::Or  );
                Add( WideString(L"cap"), DoxCmdGroupType::cap );
                Add( WideString(L"cup"), DoxCmdGroupType::cup );
                Add( WideString(L"int"), DoxCmdGroupType::Int );
                Add( WideString(L"there4"), DoxCmdGroupType::there4 );
                Add( WideString(L"sim"), DoxCmdGroupType::sim );
                Add( WideString(L"cong"), DoxCmdGroupType::cong );
                Add( WideString(L"asymp"), DoxCmdGroupType::asymp );
                Add( WideString(L"ne"), DoxCmdGroupType::ne );
                Add( WideString(L"equiv"), DoxCmdGroupType::equiv );
                Add( WideString(L"le"), DoxCmdGroupType::le );
                Add( WideString(L"ge"), DoxCmdGroupType::ge );
                Add( WideString(L"sub"), DoxCmdGroupType::sub );
                Add( WideString(L"sup"), DoxCmdGroupType::sup );
                Add( WideString(L"nsub"), DoxCmdGroupType::nsub );
                Add( WideString(L"sube"), DoxCmdGroupType::sube );
                Add( WideString(L"supe"), DoxCmdGroupType::supe );
                Add( WideString(L"oplus"), DoxCmdGroupType::oplus );
                Add( WideString(L"otimes"), DoxCmdGroupType::otimes );
                Add( WideString(L"perp"), DoxCmdGroupType::perp );
                Add( WideString(L"sdot"), DoxCmdGroupType::sdot );
                Add( WideString(L"lceil"), DoxCmdGroupType::lceil );
                Add( WideString(L"rceil"), DoxCmdGroupType::rceil );
                Add( WideString(L"lfloor"), DoxCmdGroupType::lfloor );
                Add( WideString(L"rfloor"), DoxCmdGroupType::rfloor );
                Add( WideString(L"lang"), DoxCmdGroupType::lang );
                Add( WideString(L"rang"), DoxCmdGroupType::rang );
                Add( WideString(L"loz"), DoxCmdGroupType::loz );
                Add( WideString(L"spades"), DoxCmdGroupType::spades );
                Add( WideString(L"clubs"), DoxCmdGroupType::clubs );
                Add( WideString(L"hearts"), DoxCmdGroupType::hearts );
                Add( WideString(L"diams"), DoxCmdGroupType::diams );
                Add( WideString(L"OElig"), DoxCmdGroupType::OElig );
                Add( WideString(L"oelig"), DoxCmdGroupType::oelig );
                Add( WideString(L"Scaron"), DoxCmdGroupType::Scaron );
                Add( WideString(L"scaron"), DoxCmdGroupType::scaron );
                Add( WideString(L"Yumlaut"), DoxCmdGroupType::Yumlaut );
                Add( WideString(L"circ"), DoxCmdGroupType::circ );
                Add( WideString(L"tilde"), DoxCmdGroupType::tilde );
                Add( WideString(L"ensp"), DoxCmdGroupType::ensp );
                Add( WideString(L"emsp"), DoxCmdGroupType::emsp );
                Add( WideString(L"thinsp"), DoxCmdGroupType::thinsp );
                Add( WideString(L"zwnj"), DoxCmdGroupType::zwnj );
                Add( WideString(L"zwj"), DoxCmdGroupType::zwj );
                Add( WideString(L"lrm"), DoxCmdGroupType::lrm );
                Add( WideString(L"rlm"), DoxCmdGroupType::rlm );
                Add( WideString(L"ndash"), DoxCmdGroupType::ndash );
                Add( WideString(L"mdash"), DoxCmdGroupType::mdash );
                Add( WideString(L"lsquo"), DoxCmdGroupType::lsquo );
                Add( WideString(L"rsquo"), DoxCmdGroupType::rsquo );
                Add( WideString(L"sbquo"), DoxCmdGroupType::sbquo );
                Add( WideString(L"ldquo"), DoxCmdGroupType::ldquo );
                Add( WideString(L"rdquo"), DoxCmdGroupType::rdquo );
                Add( WideString(L"bdquo"), DoxCmdGroupType::bdquo );
                Add( WideString(L"dagger"), DoxCmdGroupType::dagger );
                Add( WideString(L"Dagger"), DoxCmdGroupType::Dagger );
                Add( WideString(L"permil"), DoxCmdGroupType::permil );
                Add( WideString(L"lsaquo"), DoxCmdGroupType::lsaquo );
                Add( WideString(L"rsaquo"), DoxCmdGroupType::rsaquo );
                Add( WideString(L"euro"), DoxCmdGroupType::euro );
                Add( WideString(L"tm"), DoxCmdGroupType::tm );
                Add( WideString(L"hruler"), DoxCmdGroupType::hruler );
                Add( WideString(L"preformatted"), DoxCmdGroupType::preformatted );
                Add( WideString(L"programlisting"), DoxCmdGroupType::programlisting );
                Add( WideString(L"verbatim"), DoxCmdGroupType::verbatim );
                Add( WideString(L"javadocliteral"), DoxCmdGroupType::javadocliteral );
                Add( WideString(L"javadoccode"), DoxCmdGroupType::javadoccode );
                Add( WideString(L"indexentry"), DoxCmdGroupType::indexentry );
                Add( WideString(L"orderedlist"), DoxCmdGroupType::orderedlist );
                Add( WideString(L"itemizedlist"), DoxCmdGroupType::itemizedlist );
                Add( WideString(L"simplesect"), DoxCmdGroupType::simplesect );
                Add( WideString(L"title"), DoxCmdGroupType::title );
                Add( WideString(L"variablelist"), DoxCmdGroupType::variablelist );
                Add( WideString(L"table"), DoxCmdGroupType::table );
                Add( WideString(L"heading"), DoxCmdGroupType::heading );
                Add( WideString(L"dotfile"), DoxCmdGroupType::dotfile );
                Add( WideString(L"mscfile"), DoxCmdGroupType::mscfile );
                Add( WideString(L"diafile"), DoxCmdGroupType::diafile );
                Add( WideString(L"toclist"), DoxCmdGroupType::toclist );
                Add( WideString(L"language"), DoxCmdGroupType::language );
                Add( WideString(L"parameterlist"), DoxCmdGroupType::parameterlist );
                Add( WideString(L"xrefsect"), DoxCmdGroupType::xrefsect );
                Add( WideString(L"copydoc"), DoxCmdGroupType::copydoc );
                Add( WideString(L"details"), DoxCmdGroupType::details );
                Add( WideString(L"blockquote"), DoxCmdGroupType::blockquote );
                Add( WideString(L"parblock"), DoxCmdGroupType::parblock );
            }
        };

        DoxCmdGroupTypeConverter staticDoxCmdGroupTypeConverter;
    }

    WideString ToWideString( DoxCmdGroupType value )
    {
        return staticDoxCmdGroupTypeConverter.ToString( value );
    }
    WideString ToWideString( DoxCmdGroupType value, const WideString& defaultResult )
    {
        return staticDoxCmdGroupTypeConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCmdGroupType ParseDoxCmdGroupType( const WideString& str )
        {
            return staticDoxCmdGroupTypeConverter.Parse( str );
        }

        DoxCmdGroupType ParseDoxCmdGroupType( const WideString& str, DoxCmdGroupType defaultResult )
        {
            return staticDoxCmdGroupTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCmdGroupType( const WideString& str, DoxCmdGroupType& value )
        {
            return staticDoxCmdGroupTypeConverter.TryParse( str, value );
        }
    }




}
