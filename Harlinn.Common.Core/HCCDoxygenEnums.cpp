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
                Add(L"define", MemberKind::Define);
                Add(L"property", MemberKind::Property);
                Add(L"event", MemberKind::Event);
                Add(L"variable", MemberKind::Variable);
                Add(L"typedef", MemberKind::Typedef);
                Add(L"enum", MemberKind::Enum);
                Add(L"enumvalue", MemberKind::Enumvalue);
                Add(L"function", MemberKind::Function);
                Add(L"signal", MemberKind::Signal);
                Add(L"prototype", MemberKind::Prototype);
                Add(L"friend", MemberKind::Friend);
                Add(L"dcop", MemberKind::DCop);
                Add( L"slot", MemberKind::Slot);
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
                Add(L"include", DoxGraphRelation::Include);
                Add(L"usage", DoxGraphRelation::Usage);
                Add(L"template-instance", DoxGraphRelation::TemplateInstance);
                Add(L"public-inheritance", DoxGraphRelation::PublicInheritance);
                Add(L"protected-inheritance", DoxGraphRelation::ProtectedInheritance);
                Add(L"private-inheritance", DoxGraphRelation::PrivateInheritance);
                Add( L"type-constraint", DoxGraphRelation::TypeConstraint );
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
                Add( L"compound", DoxRefKind::Compound);
                Add( L"member", DoxRefKind::Member );
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
                Add( L"define", DoxMemberKind::Define);
                Add( L"property", DoxMemberKind::Property);
                Add( L"event", DoxMemberKind::Event);
                Add( L"variable", DoxMemberKind::Variable);
                Add( L"typedef", DoxMemberKind::Typedef);
                Add( L"enum", DoxMemberKind::Enum);
                Add( L"function", DoxMemberKind::Function);
                Add( L"signal", DoxMemberKind::Signal);
                Add( L"prototype", DoxMemberKind::Prototype);
                Add( L"friend", DoxMemberKind::Friend);
                Add( L"dcop", DoxMemberKind::DCop);
                Add( L"slot", DoxMemberKind::Slot);
                Add( L"interface", DoxMemberKind::Interface);
                Add( L"service", DoxMemberKind::Service );
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
                Add( L"public", DoxProtectionKind::Public);
                Add( L"protected", DoxProtectionKind::Protected);
                Add( L"private", DoxProtectionKind::Private);
                Add( L"package", DoxProtectionKind::Package );
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
                Add( L"lvalue", DoxRefQualifierKind::LValue );
                Add( L"rvalue", DoxRefQualifierKind::RValue );
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
                Add( L"Unknown", DoxLanguage::Unknown );
                Add( L"IDL", DoxLanguage::IDL );
                Add( L"Java", DoxLanguage::Java );
                Add( L"C#", DoxLanguage::CSharp );
                Add( L"D", DoxLanguage::D );
                Add( L"PHP", DoxLanguage::PHP );
                Add( L"Objective-C", DoxLanguage::ObjectiveC );
                Add( L"C++", DoxLanguage::Cpp );
                Add( L"JavaScript", DoxLanguage::JavaScript );
                Add( L"Python", DoxLanguage::Python );
                Add( L"Fortran", DoxLanguage::Fortran );
                Add( L"VHDL", DoxLanguage::VHDL );
                Add( L"XML", DoxLanguage::XML );
                Add( L"SQL", DoxLanguage::SQL );
                Add( L"Markdown", DoxLanguage::Markdown );
                Add( L"Slice", DoxLanguage::Slice );
                Add( L"Lex", DoxLanguage::Lex );
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
                Add( L"non-virtual", DoxVirtualKind::NonVirtual );
                Add( L"virtual", DoxVirtualKind::Virtual );
                Add( L"pure-virtual", DoxVirtualKind::PureVirtual );
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
                Add( L"class", DoxCompoundKind::Class );
                Add( L"struct", DoxCompoundKind::Struct );
                Add( L"union", DoxCompoundKind::Union );
                Add( L"interface", DoxCompoundKind::Interface );
                Add( L"protocol", DoxCompoundKind::Protocol );
                Add( L"category", DoxCompoundKind::Category );
                Add( L"exception", DoxCompoundKind::Exception );
                Add( L"service", DoxCompoundKind::Service );
                Add( L"singleton", DoxCompoundKind::Singleton );
                Add( L"module", DoxCompoundKind::Module );
                Add( L"type", DoxCompoundKind::Type );
                Add( L"file", DoxCompoundKind::File );
                Add( L"namespace", DoxCompoundKind::Namespace );
                Add( L"group", DoxCompoundKind::Group );
                Add( L"page", DoxCompoundKind::Page );
                Add( L"example", DoxCompoundKind::Example );
                Add( L"dir", DoxCompoundKind::Dir );
                Add( L"concept", DoxCompoundKind::Concept );
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
                Add( L"user-defined", DoxSectionKind::UserDefined );
                Add( L"public-type", DoxSectionKind::PublicType );
                Add( L"public-func", DoxSectionKind::PublicFunc );
                Add( L"public-attrib", DoxSectionKind::PublicAttrib );
                Add( L"public-slot", DoxSectionKind::PublicSlot );
                Add( L"signal", DoxSectionKind::Signal );
                Add( L"dcop-func", DoxSectionKind::DcopFunc );
                Add( L"property", DoxSectionKind::Property );
                Add( L"event", DoxSectionKind::Event );
                Add( L"public-static-func", DoxSectionKind::PublicStaticFunc );
                Add( L"public-static-attrib", DoxSectionKind::PublicStaticAttrib );
                Add( L"protected-type", DoxSectionKind::ProtectedType );
                Add( L"protected-func", DoxSectionKind::ProtectedFunc );
                Add( L"protected-attrib", DoxSectionKind::ProtectedAttrib );
                Add( L"protected-slot", DoxSectionKind::ProtectedSlot );
                Add( L"protected-static-func", DoxSectionKind::ProtectedStaticFunc );
                Add( L"protected-static-attrib", DoxSectionKind::ProtectedStaticAttrib );
                Add( L"package-type", DoxSectionKind::PackageType );
                Add( L"package-func", DoxSectionKind::PackageFunc );
                Add( L"package-attrib", DoxSectionKind::PackageAttrib );
                Add( L"package-static-func", DoxSectionKind::PackageStaticFunc );
                Add( L"package-static-attrib", DoxSectionKind::PackageStaticAttrib );
                Add( L"private-type", DoxSectionKind::PrivateType );
                Add( L"private-func", DoxSectionKind::PrivateFunc );
                Add( L"private-attrib", DoxSectionKind::PrivateAttrib );
                Add( L"private-slot", DoxSectionKind::PrivateSlot );
                Add( L"private-static-func", DoxSectionKind::PrivateStaticFunc );
                Add( L"private-static-attrib", DoxSectionKind::PrivateStaticAttrib );
                Add( L"friend", DoxSectionKind::Friend );
                Add( L"related", DoxSectionKind::Related );
                Add( L"define", DoxSectionKind::Define );
                Add( L"prototype", DoxSectionKind::Prototype );
                Add( L"typedef", DoxSectionKind::Typedef );
                Add( L"enum", DoxSectionKind::Enum );
                Add( L"func", DoxSectionKind::Func );
                Add( L"var", DoxSectionKind::Var );
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
                Add(L"comment", DoxHighlightClass::Comment );
                Add(L"normal", DoxHighlightClass::Normal );
                Add(L"preprocessor", DoxHighlightClass::Preprocessor );
                Add(L"keyword", DoxHighlightClass::Keyword );
                Add(L"keywordtype", DoxHighlightClass::KeywordType );
                Add(L"keywordflow", DoxHighlightClass::KeywordFlow );
                Add(L"stringliteral", DoxHighlightClass::StringLiteral );
                Add(L"xmlcdata", DoxHighlightClass::XmlCData );
                Add(L"charliteral", DoxHighlightClass::CharLiteral );
                Add(L"vhdlkeyword", DoxHighlightClass::VhdlKeyword );
                Add(L"vhdllogic", DoxHighlightClass::VhdlLogic );
                Add(L"vhdlchar", DoxHighlightClass::VhdlChar );
                Add( L"vhdldigit", DoxHighlightClass::VhdlDigit );
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
                Add( L"see", DoxSimpleSectKind::See );
                Add( L"return", DoxSimpleSectKind::Return );
                Add( L"author", DoxSimpleSectKind::Author );
                Add( L"authors", DoxSimpleSectKind::Authors );
                Add( L"version", DoxSimpleSectKind::Version );
                Add( L"since", DoxSimpleSectKind::Since );
                Add( L"date", DoxSimpleSectKind::Date );
                Add( L"note", DoxSimpleSectKind::Note );
                Add( L"warning", DoxSimpleSectKind::Warning );
                Add( L"pre", DoxSimpleSectKind::Pre );
                Add( L"post", DoxSimpleSectKind::Post );
                Add( L"copyright", DoxSimpleSectKind::Copyright );
                Add( L"invariant", DoxSimpleSectKind::Invariant );
                Add( L"remark", DoxSimpleSectKind::Remark );
                Add( L"attention", DoxSimpleSectKind::Attention );
                Add( L"important", DoxSimpleSectKind::Important );
                Add( L"par", DoxSimpleSectKind::Par );
                Add( L"rcs", DoxSimpleSectKind::Rcs );
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
                Add( L"checked", DoxCheck::Checked );
                Add( L"unchecked", DoxCheck::Unchecked );
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
                Add( L"html", DoxImageKind::Html );
                Add( L"latex", DoxImageKind::Latex );
                Add( L"docbook", DoxImageKind::Docbook );
                Add( L"rtf", DoxImageKind::Rtf );
                Add( L"xml", DoxImageKind::Xml );
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
                Add( L"uml", DoxPlantumlEngine::Uml );
                Add( L"bpm", DoxPlantumlEngine::Bpm );
                Add( L"wire", DoxPlantumlEngine::Wire );
                Add( L"dot", DoxPlantumlEngine::Dot );
                Add( L"ditaa", DoxPlantumlEngine::Ditaa );
                Add( L"salt", DoxPlantumlEngine::Salt );
                Add( L"math", DoxPlantumlEngine::Math );
                Add( L"latex", DoxPlantumlEngine::Latex );
                Add( L"gantt", DoxPlantumlEngine::Gantt );
                Add( L"mindmap", DoxPlantumlEngine::Mindmap );
                Add( L"wbs", DoxPlantumlEngine::Wbs );
                Add( L"yaml", DoxPlantumlEngine::Yaml );
                Add( L"creole", DoxPlantumlEngine::Creole );
                Add( L"json", DoxPlantumlEngine::Json );
                Add( L"flow", DoxPlantumlEngine::Flow );
                Add( L"board", DoxPlantumlEngine::Board );
                Add( L"git", DoxPlantumlEngine::Git );
                Add( L"hcl", DoxPlantumlEngine::Hcl );
                Add( L"regex", DoxPlantumlEngine::Regex );
                Add( L"ebnf", DoxPlantumlEngine::Ebnf );
                Add( L"files", DoxPlantumlEngine::Files );
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
                Add( L"param", DoxParamListKind::Param );
                Add( L"retval", DoxParamListKind::Retval );
                Add( L"exception", DoxParamListKind::Exception );
                Add( L"templateparam", DoxParamListKind::TemplateParam );
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
                Add( L"in", DoxParamDir::In );
                Add( L"out", DoxParamDir::Out );
                Add( L"inout", DoxParamDir::InOut );
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
                Add( L"retain", DoxAccessor::Retain );
                Add( L"copy", DoxAccessor::Copy );
                Add( L"assign", DoxAccessor::Assign );
                Add( L"weak", DoxAccessor::Weak );
                Add( L"strong", DoxAccessor::Strong );
                Add( L"unretained", DoxAccessor::Unretained );
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
                Add( L"left", DoxAlign::Left );
                Add( L"right", DoxAlign::Right );
                Add( L"center", DoxAlign::Center );
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
                Add( L"bottom", DoxVerticalAlign::Bottom );
                Add( L"top", DoxVerticalAlign::Top );
                Add( L"middle", DoxVerticalAlign::Middle );
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
                Add( L"1", DoxOlType::Numbered);
                Add( L"a", DoxOlType::a);
                Add( L"A", DoxOlType::A);
                Add( L"i", DoxOlType::i);
                Add( L"I", DoxOlType::I);
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




}
