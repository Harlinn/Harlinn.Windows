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
#include "HCCFlags.h"

namespace Harlinn::Common::Core
{

    /////////
    namespace
    {
        using MemberKind = Doxygen::MemberKind;
        class MemberKindConverter : public Enum<MemberKind,std::string>
        {
        public:
            using Base = Enum<MemberKind>;
            MemberKindConverter( )
            {
                Add( std::string("define"), MemberKind::Define);
                Add( std::string("property"), MemberKind::Property);
                Add( std::string("event"), MemberKind::Event);
                Add( std::string("variable"), MemberKind::Variable);
                Add( std::string("typedef"), MemberKind::Typedef);
                Add( std::string("enum"), MemberKind::Enum);
                Add( std::string("enumvalue"), MemberKind::Enumvalue);
                Add( std::string("function"), MemberKind::Function);
                Add( std::string("signal"), MemberKind::Signal);
                Add( std::string("prototype"), MemberKind::Prototype);
                Add( std::string("friend"), MemberKind::Friend);
                Add( std::string("dcop"), MemberKind::DCop);
                Add( std::string("slot"), MemberKind::Slot);
            }
        };

        MemberKindConverter staticMemberKindConverter;
    }

    std::string to_string( MemberKind value )
    {
        return staticMemberKindConverter.ToString( value );
    }
    std::string to_string( MemberKind value, const std::string& defaultResult )
    {
        return staticMemberKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        MemberKind ParseMemberKind( const std::string& str )
        {
            return staticMemberKindConverter.Parse( str );
        }

        MemberKind ParseMemberKind( const std::string& str, MemberKind defaultResult )
        {
            return staticMemberKindConverter.Parse( str, defaultResult );
        }

        bool TryParseMemberKind( const std::string& str, MemberKind& value )
        {
            return staticMemberKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxGraphRelation = Doxygen::DoxGraphRelation;
        class DoxGraphRelationConverter : public Enum<DoxGraphRelation, std::string>
        {
        public:
            using Base = Enum<DoxGraphRelation>;
            DoxGraphRelationConverter( )
            {
                Add( std::string("include"), DoxGraphRelation::Include);
                Add( std::string("usage"), DoxGraphRelation::Usage);
                Add( std::string("template-instance"), DoxGraphRelation::TemplateInstance);
                Add( std::string("public-inheritance"), DoxGraphRelation::PublicInheritance);
                Add( std::string("protected-inheritance"), DoxGraphRelation::ProtectedInheritance);
                Add( std::string("private-inheritance"), DoxGraphRelation::PrivateInheritance);
                Add( std::string("type-constraint"), DoxGraphRelation::TypeConstraint );
            }
        };

        DoxGraphRelationConverter staticDoxGraphRelationConverter;
    }

    std::string to_string( DoxGraphRelation value )
    {
        return staticDoxGraphRelationConverter.ToString( value );
    }
    std::string to_string( DoxGraphRelation value, const std::string& defaultResult )
    {
        return staticDoxGraphRelationConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxGraphRelation ParseDoxGraphRelation( const std::string& str )
        {
            return staticDoxGraphRelationConverter.Parse( str );
        }

        DoxGraphRelation ParseDoxGraphRelation( const std::string& str, DoxGraphRelation defaultResult )
        {
            return staticDoxGraphRelationConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxGraphRelation( const std::string& str, DoxGraphRelation& value )
        {
            return staticDoxGraphRelationConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxRefKind = Doxygen::DoxRefKind;
        class DoxRefKindConverter : public Enum<DoxRefKind, std::string>
        {
        public:
            using Base = Enum<DoxRefKind>;
            DoxRefKindConverter( )
            {
                Add( std::string("compound"), DoxRefKind::Compound);
                Add( std::string("member"), DoxRefKind::Member );
            }
        };

        DoxRefKindConverter staticDoxRefKindConverter;
    }

    std::string to_string( DoxRefKind value )
    {
        return staticDoxRefKindConverter.ToString( value );
    }
    std::string to_string( DoxRefKind value, const std::string& defaultResult )
    {
        return staticDoxRefKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxRefKind ParseDoxRefKind( const std::string& str )
        {
            return staticDoxRefKindConverter.Parse( str );
        }

        DoxRefKind ParseDoxRefKind( const std::string& str, DoxRefKind defaultResult )
        {
            return staticDoxRefKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxRefKind( const std::string& str, DoxRefKind& value )
        {
            return staticDoxRefKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxMemberKind = Doxygen::DoxMemberKind;
        class DoxMemberKindConverter : public Enum<DoxMemberKind, std::string>
        {
        public:
            using Base = Enum<DoxMemberKind>;
            DoxMemberKindConverter( )
            {
                Add( std::string("define"), DoxMemberKind::Define);
                Add( std::string("property"), DoxMemberKind::Property);
                Add( std::string("event"), DoxMemberKind::Event);
                Add( std::string("variable"), DoxMemberKind::Variable);
                Add( std::string("typedef"), DoxMemberKind::Typedef);
                Add( std::string("enum"), DoxMemberKind::Enum);
                Add( std::string("function"), DoxMemberKind::Function);
                Add( std::string("signal"), DoxMemberKind::Signal);
                Add( std::string("prototype"), DoxMemberKind::Prototype);
                Add( std::string("friend"), DoxMemberKind::Friend);
                Add( std::string("dcop"), DoxMemberKind::DCop);
                Add( std::string("slot"), DoxMemberKind::Slot);
                Add( std::string("interface"), DoxMemberKind::Interface);
                Add( std::string("service"), DoxMemberKind::Service );
            }
        };

        DoxMemberKindConverter staticDoxMemberKindConverter;
    }

    std::string to_string( DoxMemberKind value )
    {
        return staticDoxMemberKindConverter.ToString( value );
    }
    std::string to_string( DoxMemberKind value, const std::string& defaultResult )
    {
        return staticDoxMemberKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxMemberKind ParseDoxMemberKind( const std::string& str )
        {
            return staticDoxMemberKindConverter.Parse( str );
        }

        DoxMemberKind ParseDoxMemberKind( const std::string& str, DoxMemberKind defaultResult )
        {
            return staticDoxMemberKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxMemberKind( const std::string& str, DoxMemberKind& value )
        {
            return staticDoxMemberKindConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxProtectionKind = Doxygen::DoxProtectionKind;
        class DoxProtectionKindConverter : public Enum<DoxProtectionKind, std::string>
        {
        public:
            using Base = Enum<DoxProtectionKind>;
            DoxProtectionKindConverter( )
            {
                Add( std::string("public"), DoxProtectionKind::Public);
                Add( std::string("protected"), DoxProtectionKind::Protected);
                Add( std::string("private"), DoxProtectionKind::Private);
                Add( std::string("package"), DoxProtectionKind::Package );
            }
        };

        DoxProtectionKindConverter staticDoxProtectionKindConverter;
    }

    std::string to_string( DoxProtectionKind value )
    {
        return staticDoxProtectionKindConverter.ToString( value );
    }
    std::string to_string( DoxProtectionKind value, const std::string& defaultResult )
    {
        return staticDoxProtectionKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxProtectionKind ParseDoxProtectionKind( const std::string& str )
        {
            return staticDoxProtectionKindConverter.Parse( str );
        }

        DoxProtectionKind ParseDoxProtectionKind( const std::string& str, DoxProtectionKind defaultResult )
        {
            return staticDoxProtectionKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxProtectionKind( const std::string& str, DoxProtectionKind& value )
        {
            return staticDoxProtectionKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxRefQualifierKind = Doxygen::DoxRefQualifierKind;
        class DoxRefQualifierKindConverter : public Enum<DoxRefQualifierKind, std::string>
        {
        public:
            using Base = Enum<DoxRefQualifierKind>;
            DoxRefQualifierKindConverter( )
            {
                Add( std::string("lvalue"), DoxRefQualifierKind::LValue );
                Add( std::string("rvalue"), DoxRefQualifierKind::RValue );
            }
        };

        DoxRefQualifierKindConverter staticDoxRefQualifierKindConverter;
    }

    std::string to_string( DoxRefQualifierKind value )
    {
        return staticDoxRefQualifierKindConverter.ToString( value );
    }
    std::string to_string( DoxRefQualifierKind value, const std::string& defaultResult )
    {
        return staticDoxRefQualifierKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxRefQualifierKind ParseDoxRefQualifierKind( const std::string& str )
        {
            return staticDoxRefQualifierKindConverter.Parse( str );
        }

        DoxRefQualifierKind ParseDoxRefQualifierKind( const std::string& str, DoxRefQualifierKind defaultResult )
        {
            return staticDoxRefQualifierKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxRefQualifierKind( const std::string& str, DoxRefQualifierKind& value )
        {
            return staticDoxRefQualifierKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxLanguage = Doxygen::DoxLanguage;
        class DoxLanguageConverter : public Enum<DoxLanguage, std::string>
        {
        public:
            using Base = Enum<DoxLanguage>;
            DoxLanguageConverter( )
            {
                Add( std::string("Unknown"), DoxLanguage::Unknown );
                Add( std::string("IDL"), DoxLanguage::IDL );
                Add( std::string("Java"), DoxLanguage::Java );
                Add( std::string("C#"), DoxLanguage::CSharp );
                Add( std::string("D"), DoxLanguage::D );
                Add( std::string("PHP"), DoxLanguage::PHP );
                Add( std::string("Objective-C"), DoxLanguage::ObjectiveC );
                Add( std::string("C++"), DoxLanguage::Cpp );
                Add( std::string("JavaScript"), DoxLanguage::JavaScript );
                Add( std::string("Python"), DoxLanguage::Python );
                Add( std::string("Fortran"), DoxLanguage::Fortran );
                Add( std::string("VHDL"), DoxLanguage::VHDL );
                Add( std::string("XML"), DoxLanguage::XML );
                Add( std::string("SQL"), DoxLanguage::SQL );
                Add( std::string("Markdown"), DoxLanguage::Markdown );
                Add( std::string("Slice"), DoxLanguage::Slice );
                Add( std::string("Lex"), DoxLanguage::Lex );
            }
        };

        DoxLanguageConverter staticDoxLanguageConverter;
    }

    std::string to_string( DoxLanguage value )
    {
        return staticDoxLanguageConverter.ToString( value );
    }
    std::string to_string( DoxLanguage value, const std::string& defaultResult )
    {
        return staticDoxLanguageConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxLanguage ParseDoxLanguage( const std::string& str )
        {
            return staticDoxLanguageConverter.Parse( str );
        }

        DoxLanguage ParseDoxLanguage( const std::string& str, DoxLanguage defaultResult )
        {
            return staticDoxLanguageConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxLanguage( const std::string& str, DoxLanguage& value )
        {
            return staticDoxLanguageConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxVirtualKind = Doxygen::DoxVirtualKind;
        class DoxVirtualKindConverter : public Enum<DoxVirtualKind, std::string>
        {
        public:
            using Base = Enum<DoxVirtualKind>;
            DoxVirtualKindConverter( )
            {
                Add( std::string("non-virtual"), DoxVirtualKind::NonVirtual );
                Add( std::string("virtual"), DoxVirtualKind::Virtual );
                Add( std::string("pure-virtual"), DoxVirtualKind::PureVirtual );
            }
        };

        DoxVirtualKindConverter staticDoxVirtualKindConverter;
    }

    std::string to_string( DoxVirtualKind value )
    {
        return staticDoxVirtualKindConverter.ToString( value );
    }
    std::string to_string( DoxVirtualKind value, const std::string& defaultResult )
    {
        return staticDoxVirtualKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxVirtualKind ParseDoxVirtualKind( const std::string& str )
        {
            return staticDoxVirtualKindConverter.Parse( str );
        }

        DoxVirtualKind ParseDoxVirtualKind( const std::string& str, DoxVirtualKind defaultResult )
        {
            return staticDoxVirtualKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxVirtualKind( const std::string& str, DoxVirtualKind& value )
        {
            return staticDoxVirtualKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxCompoundKind = Doxygen::DoxCompoundKind;
        class DoxCompoundKindConverter : public Enum<DoxCompoundKind, std::string>
        {
        public:
            using Base = Enum<DoxCompoundKind>;
            DoxCompoundKindConverter( )
            {
                Add( std::string("class"), DoxCompoundKind::Class );
                Add( std::string("struct"), DoxCompoundKind::Struct );
                Add( std::string("union"), DoxCompoundKind::Union );
                Add( std::string("interface"), DoxCompoundKind::Interface );
                Add( std::string("protocol"), DoxCompoundKind::Protocol );
                Add( std::string("category"), DoxCompoundKind::Category );
                Add( std::string("exception"), DoxCompoundKind::Exception );
                Add( std::string("service"), DoxCompoundKind::Service );
                Add( std::string("singleton"), DoxCompoundKind::Singleton );
                Add( std::string("module"), DoxCompoundKind::Module );
                Add( std::string("type"), DoxCompoundKind::Type );
                Add( std::string("file"), DoxCompoundKind::File );
                Add( std::string("namespace"), DoxCompoundKind::Namespace );
                Add( std::string("group"), DoxCompoundKind::Group );
                Add( std::string("page"), DoxCompoundKind::Page );
                Add( std::string("example"), DoxCompoundKind::Example );
                Add( std::string("dir"), DoxCompoundKind::Dir );
                Add( std::string("concept"), DoxCompoundKind::Concept );
            }
        };

        DoxCompoundKindConverter staticDoxCompoundKindConverter;
    }

    std::string to_string( DoxCompoundKind value )
    {
        return staticDoxCompoundKindConverter.ToString( value );
    }
    std::string to_string( DoxCompoundKind value, const std::string& defaultResult )
    {
        return staticDoxCompoundKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCompoundKind ParseDoxCompoundKind( const std::string& str )
        {
            return staticDoxCompoundKindConverter.Parse( str );
        }

        DoxCompoundKind ParseDoxCompoundKind( const std::string& str, DoxCompoundKind defaultResult )
        {
            return staticDoxCompoundKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCompoundKind( const std::string& str, DoxCompoundKind& value )
        {
            return staticDoxCompoundKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxSectionKind = Doxygen::DoxSectionKind;
        class DoxSectionKindConverter : public Enum<DoxSectionKind, std::string>
        {
        public:
            using Base = Enum<DoxSectionKind>;
            DoxSectionKindConverter( )
            {
                Add( std::string("user-defined"), DoxSectionKind::UserDefined );
                Add( std::string("public-type"), DoxSectionKind::PublicType );
                Add( std::string("public-func"), DoxSectionKind::PublicFunc );
                Add( std::string("public-attrib"), DoxSectionKind::PublicAttrib );
                Add( std::string("public-slot"), DoxSectionKind::PublicSlot );
                Add( std::string("signal"), DoxSectionKind::Signal );
                Add( std::string("dcop-func"), DoxSectionKind::DcopFunc );
                Add( std::string("property"), DoxSectionKind::Property );
                Add( std::string("event"), DoxSectionKind::Event );
                Add( std::string("public-static-func"), DoxSectionKind::PublicStaticFunc );
                Add( std::string("public-static-attrib"), DoxSectionKind::PublicStaticAttrib );
                Add( std::string("protected-type"), DoxSectionKind::ProtectedType );
                Add( std::string("protected-func"), DoxSectionKind::ProtectedFunc );
                Add( std::string("protected-attrib"), DoxSectionKind::ProtectedAttrib );
                Add( std::string("protected-slot"), DoxSectionKind::ProtectedSlot );
                Add( std::string("protected-static-func"), DoxSectionKind::ProtectedStaticFunc );
                Add( std::string("protected-static-attrib"), DoxSectionKind::ProtectedStaticAttrib );
                Add( std::string("package-type"), DoxSectionKind::PackageType );
                Add( std::string("package-func"), DoxSectionKind::PackageFunc );
                Add( std::string("package-attrib"), DoxSectionKind::PackageAttrib );
                Add( std::string("package-static-func"), DoxSectionKind::PackageStaticFunc );
                Add( std::string("package-static-attrib"), DoxSectionKind::PackageStaticAttrib );
                Add( std::string("private-type"), DoxSectionKind::PrivateType );
                Add( std::string("private-func"), DoxSectionKind::PrivateFunc );
                Add( std::string("private-attrib"), DoxSectionKind::PrivateAttrib );
                Add( std::string("private-slot"), DoxSectionKind::PrivateSlot );
                Add( std::string("private-static-func"), DoxSectionKind::PrivateStaticFunc );
                Add( std::string("private-static-attrib"), DoxSectionKind::PrivateStaticAttrib );
                Add( std::string("friend"), DoxSectionKind::Friend );
                Add( std::string("related"), DoxSectionKind::Related );
                Add( std::string("define"), DoxSectionKind::Define );
                Add( std::string("prototype"), DoxSectionKind::Prototype );
                Add( std::string("typedef"), DoxSectionKind::Typedef );
                Add( std::string("enum"), DoxSectionKind::Enum );
                Add( std::string("func"), DoxSectionKind::Func );
                Add( std::string("var"), DoxSectionKind::Var );
            }
        };

        DoxSectionKindConverter staticDoxSectionKindConverter;
    }

    std::string to_string( DoxSectionKind value )
    {
        return staticDoxSectionKindConverter.ToString( value );
    }
    std::string to_string( DoxSectionKind value, const std::string& defaultResult )
    {
        return staticDoxSectionKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxSectionKind ParseDoxSectionKind( const std::string& str )
        {
            return staticDoxSectionKindConverter.Parse( str );
        }

        DoxSectionKind ParseDoxSectionKind( const std::string& str, DoxSectionKind defaultResult )
        {
            return staticDoxSectionKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxSectionKind( const std::string& str, DoxSectionKind& value )
        {
            return staticDoxSectionKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxHighlightClass = Doxygen::DoxHighlightClass;
        class DoxHighlightClassConverter : public Enum<DoxHighlightClass, std::string>
        {
        public:
            using Base = Enum<DoxHighlightClass>;
            DoxHighlightClassConverter( )
            {
                Add( std::string("comment"), DoxHighlightClass::Comment );
                Add( std::string("normal"), DoxHighlightClass::Normal );
                Add( std::string("preprocessor"), DoxHighlightClass::Preprocessor );
                Add( std::string("keyword"), DoxHighlightClass::Keyword );
                Add( std::string("keywordtype"), DoxHighlightClass::KeywordType );
                Add( std::string("keywordflow"), DoxHighlightClass::KeywordFlow );
                Add( std::string("stringliteral"), DoxHighlightClass::StringLiteral );
                Add( std::string("xmlcdata"), DoxHighlightClass::XmlCData );
                Add( std::string("charliteral"), DoxHighlightClass::CharLiteral );
                Add( std::string("vhdlkeyword"), DoxHighlightClass::VhdlKeyword );
                Add( std::string("vhdllogic"), DoxHighlightClass::VhdlLogic );
                Add( std::string("vhdlchar"), DoxHighlightClass::VhdlChar );
                Add( std::string("vhdldigit"), DoxHighlightClass::VhdlDigit );
            }
        };

        DoxHighlightClassConverter staticDoxHighlightClassConverter;
    }

    std::string to_string( DoxHighlightClass value )
    {
        return staticDoxHighlightClassConverter.ToString( value );
    }
    std::string to_string( DoxHighlightClass value, const std::string& defaultResult )
    {
        return staticDoxHighlightClassConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxHighlightClass ParseDoxHighlightClass( const std::string& str )
        {
            return staticDoxHighlightClassConverter.Parse( str );
        }

        DoxHighlightClass ParseDoxHighlightClass( const std::string& str, DoxHighlightClass defaultResult )
        {
            return staticDoxHighlightClassConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxHighlightClass( const std::string& str, DoxHighlightClass& value )
        {
            return staticDoxHighlightClassConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxSimpleSectKind = Doxygen::DoxSimpleSectKind;
        class DoxSimpleSectKindConverter : public Enum<DoxSimpleSectKind, std::string>
        {
        public:
            using Base = Enum<DoxSimpleSectKind>;
            DoxSimpleSectKindConverter( )
            {
                Add( std::string("see"), DoxSimpleSectKind::See );
                Add( std::string("return"), DoxSimpleSectKind::Return );
                Add( std::string("author"), DoxSimpleSectKind::Author );
                Add( std::string("authors"), DoxSimpleSectKind::Authors );
                Add( std::string("version"), DoxSimpleSectKind::Version );
                Add( std::string("since"), DoxSimpleSectKind::Since );
                Add( std::string("date"), DoxSimpleSectKind::Date );
                Add( std::string("note"), DoxSimpleSectKind::Note );
                Add( std::string("warning"), DoxSimpleSectKind::Warning );
                Add( std::string("pre"), DoxSimpleSectKind::Pre );
                Add( std::string("post"), DoxSimpleSectKind::Post );
                Add( std::string("copyright"), DoxSimpleSectKind::Copyright );
                Add( std::string("invariant"), DoxSimpleSectKind::Invariant );
                Add( std::string("remark"), DoxSimpleSectKind::Remark );
                Add( std::string("attention"), DoxSimpleSectKind::Attention );
                Add( std::string("important"), DoxSimpleSectKind::Important );
                Add( std::string("par"), DoxSimpleSectKind::Par );
                Add( std::string("rcs"), DoxSimpleSectKind::Rcs );
            }
        };

        DoxSimpleSectKindConverter staticDoxSimpleSectKindConverter;
    }

    std::string to_string( DoxSimpleSectKind value )
    {
        return staticDoxSimpleSectKindConverter.ToString( value );
    }
    std::string to_string( DoxSimpleSectKind value, const std::string& defaultResult )
    {
        return staticDoxSimpleSectKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxSimpleSectKind ParseDoxSimpleSectKind( const std::string& str )
        {
            return staticDoxSimpleSectKindConverter.Parse( str );
        }

        DoxSimpleSectKind ParseDoxSimpleSectKind( const std::string& str, DoxSimpleSectKind defaultResult )
        {
            return staticDoxSimpleSectKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxSimpleSectKind( const std::string& str, DoxSimpleSectKind& value )
        {
            return staticDoxSimpleSectKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxCheck = Doxygen::DoxCheck;
        class DoxCheckConverter : public Enum<DoxCheck, std::string>
        {
        public:
            using Base = Enum<DoxCheck>;
            DoxCheckConverter( )
            {
                Add( std::string("checked"), DoxCheck::Checked );
                Add( std::string("unchecked"), DoxCheck::Unchecked );
            }
        };

        DoxCheckConverter staticDoxCheckConverter;
    }

    std::string to_string( DoxCheck value )
    {
        return staticDoxCheckConverter.ToString( value );
    }
    std::string to_string( DoxCheck value, const std::string& defaultResult )
    {
        return staticDoxCheckConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCheck ParseDoxCheck( const std::string& str )
        {
            return staticDoxCheckConverter.Parse( str );
        }

        DoxCheck ParseDoxCheck( const std::string& str, DoxCheck defaultResult )
        {
            return staticDoxCheckConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCheck( const std::string& str, DoxCheck& value )
        {
            return staticDoxCheckConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxImageKind = Doxygen::DoxImageKind;
        class DoxImageKindConverter : public Enum<DoxImageKind, std::string>
        {
        public:
            using Base = Enum<DoxImageKind>;
            DoxImageKindConverter( )
            {
                Add( std::string("html"), DoxImageKind::Html );
                Add( std::string("latex"), DoxImageKind::Latex );
                Add( std::string("docbook"), DoxImageKind::Docbook );
                Add( std::string("rtf"), DoxImageKind::Rtf );
                Add( std::string("xml"), DoxImageKind::Xml );
            }
        };

        DoxImageKindConverter staticDoxImageKindConverter;
    }

    std::string to_string( DoxImageKind value )
    {
        return staticDoxImageKindConverter.ToString( value );
    }
    std::string to_string( DoxImageKind value, const std::string& defaultResult )
    {
        return staticDoxImageKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxImageKind ParseDoxImageKind( const std::string& str )
        {
            return staticDoxImageKindConverter.Parse( str );
        }

        DoxImageKind ParseDoxImageKind( const std::string& str, DoxImageKind defaultResult )
        {
            return staticDoxImageKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxImageKind( const std::string& str, DoxImageKind& value )
        {
            return staticDoxImageKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxPlantumlEngine = Doxygen::DoxPlantumlEngine;
        class DoxPlantumlEngineConverter : public Enum<DoxPlantumlEngine, std::string>
        {
        public:
            using Base = Enum<DoxPlantumlEngine>;
            DoxPlantumlEngineConverter( )
            {
                Add( std::string("uml"), DoxPlantumlEngine::Uml );
                Add( std::string("bpm"), DoxPlantumlEngine::Bpm );
                Add( std::string("wire"), DoxPlantumlEngine::Wire );
                Add( std::string("dot"), DoxPlantumlEngine::Dot );
                Add( std::string("ditaa"), DoxPlantumlEngine::Ditaa );
                Add( std::string("salt"), DoxPlantumlEngine::Salt );
                Add( std::string("math"), DoxPlantumlEngine::Math );
                Add( std::string("latex"), DoxPlantumlEngine::Latex );
                Add( std::string("gantt"), DoxPlantumlEngine::Gantt );
                Add( std::string("mindmap"), DoxPlantumlEngine::Mindmap );
                Add( std::string("wbs"), DoxPlantumlEngine::Wbs );
                Add( std::string("yaml"), DoxPlantumlEngine::Yaml );
                Add( std::string("creole"), DoxPlantumlEngine::Creole );
                Add( std::string("json"), DoxPlantumlEngine::Json );
                Add( std::string("flow"), DoxPlantumlEngine::Flow );
                Add( std::string("board"), DoxPlantumlEngine::Board );
                Add( std::string("git"), DoxPlantumlEngine::Git );
                Add( std::string("hcl"), DoxPlantumlEngine::Hcl );
                Add( std::string("regex"), DoxPlantumlEngine::Regex );
                Add( std::string("ebnf"), DoxPlantumlEngine::Ebnf );
                Add( std::string("files"), DoxPlantumlEngine::Files );
            }
        };

        DoxPlantumlEngineConverter staticDoxPlantumlEngineConverter;
    }

    std::string to_string( DoxPlantumlEngine value )
    {
        return staticDoxPlantumlEngineConverter.ToString( value );
    }
    std::string to_string( DoxPlantumlEngine value, const std::string& defaultResult )
    {
        return staticDoxPlantumlEngineConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxPlantumlEngine ParseDoxPlantumlEngine( const std::string& str )
        {
            return staticDoxPlantumlEngineConverter.Parse( str );
        }

        DoxPlantumlEngine ParseDoxPlantumlEngine( const std::string& str, DoxPlantumlEngine defaultResult )
        {
            return staticDoxPlantumlEngineConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxPlantumlEngine( const std::string& str, DoxPlantumlEngine& value )
        {
            return staticDoxPlantumlEngineConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxParamListKind = Doxygen::DoxParamListKind;
        class DoxParamListKindConverter : public Enum<DoxParamListKind, std::string>
        {
        public:
            using Base = Enum<DoxParamListKind>;
            DoxParamListKindConverter( )
            {
                Add( std::string("param"), DoxParamListKind::Param );
                Add( std::string("retval"), DoxParamListKind::Retval );
                Add( std::string("exception"), DoxParamListKind::Exception );
                Add( std::string("templateparam"), DoxParamListKind::TemplateParam );
            }
        };

        DoxParamListKindConverter staticDoxParamListKindConverter;
    }

    std::string to_string( DoxParamListKind value )
    {
        return staticDoxParamListKindConverter.ToString( value );
    }
    std::string to_string( DoxParamListKind value, const std::string& defaultResult )
    {
        return staticDoxParamListKindConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxParamListKind ParseDoxParamListKind( const std::string& str )
        {
            return staticDoxParamListKindConverter.Parse( str );
        }

        DoxParamListKind ParseDoxParamListKind( const std::string& str, DoxParamListKind defaultResult )
        {
            return staticDoxParamListKindConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxParamListKind( const std::string& str, DoxParamListKind& value )
        {
            return staticDoxParamListKindConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxParamDir = Doxygen::DoxParamDir;
        class DoxParamDirConverter : public Enum<DoxParamDir, std::string>
        {
        public:
            using Base = Enum<DoxParamDir>;
            DoxParamDirConverter( )
            {
                Add( std::string("in"), DoxParamDir::In );
                Add( std::string("out"), DoxParamDir::Out );
                Add( std::string("inout"), DoxParamDir::InOut );
            }
        };

        DoxParamDirConverter staticDoxParamDirConverter;
    }

    std::string to_string( DoxParamDir value )
    {
        return staticDoxParamDirConverter.ToString( value );
    }
    std::string to_string( DoxParamDir value, const std::string& defaultResult )
    {
        return staticDoxParamDirConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxParamDir ParseDoxParamDir( const std::string& str )
        {
            return staticDoxParamDirConverter.Parse( str );
        }

        DoxParamDir ParseDoxParamDir( const std::string& str, DoxParamDir defaultResult )
        {
            return staticDoxParamDirConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxParamDir( const std::string& str, DoxParamDir& value )
        {
            return staticDoxParamDirConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxAccessor = Doxygen::DoxAccessor;
        class DoxAccessorConverter : public Enum<DoxAccessor, std::string>
        {
        public:
            using Base = Enum<DoxAccessor>;
            DoxAccessorConverter( )
            {
                Add( std::string("retain"), DoxAccessor::Retain );
                Add( std::string("copy"), DoxAccessor::Copy );
                Add( std::string("assign"), DoxAccessor::Assign );
                Add( std::string("weak"), DoxAccessor::Weak );
                Add( std::string("strong"), DoxAccessor::Strong );
                Add( std::string("unretained"), DoxAccessor::Unretained );
            }
        };

        DoxAccessorConverter staticDoxAccessorConverter;
    }

    std::string to_string( DoxAccessor value )
    {
        return staticDoxAccessorConverter.ToString( value );
    }
    std::string to_string( DoxAccessor value, const std::string& defaultResult )
    {
        return staticDoxAccessorConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxAccessor ParseDoxAccessor( const std::string& str )
        {
            return staticDoxAccessorConverter.Parse( str );
        }

        DoxAccessor ParseDoxAccessor( const std::string& str, DoxAccessor defaultResult )
        {
            return staticDoxAccessorConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxAccessor( const std::string& str, DoxAccessor& value )
        {
            return staticDoxAccessorConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxAlign = Doxygen::DoxAlign;
        class DoxAlignConverter : public Enum<DoxAlign, std::string>
        {
        public:
            using Base = Enum<DoxAlign>;
            DoxAlignConverter( )
            {
                Add( std::string("left"), DoxAlign::Left );
                Add( std::string("right"), DoxAlign::Right );
                Add( std::string("center"), DoxAlign::Center );
            }
        };

        DoxAlignConverter staticDoxAlignConverter;
    }

    std::string to_string( DoxAlign value )
    {
        return staticDoxAlignConverter.ToString( value );
    }
    std::string to_string( DoxAlign value, const std::string& defaultResult )
    {
        return staticDoxAlignConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxAlign ParseDoxAlign( const std::string& str )
        {
            return staticDoxAlignConverter.Parse( str );
        }

        DoxAlign ParseDoxAlign( const std::string& str, DoxAlign defaultResult )
        {
            return staticDoxAlignConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxAlign( const std::string& str, DoxAlign& value )
        {
            return staticDoxAlignConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxVerticalAlign = Doxygen::DoxVerticalAlign;
        class DoxVerticalAlignConverter : public Enum<DoxVerticalAlign, std::string>
        {
        public:
            using Base = Enum<DoxVerticalAlign>;
            DoxVerticalAlignConverter( )
            {
                Add( std::string("bottom"), DoxVerticalAlign::Bottom );
                Add( std::string("top"), DoxVerticalAlign::Top );
                Add( std::string("middle"), DoxVerticalAlign::Middle );
            }
        };

        DoxVerticalAlignConverter staticDoxVerticalAlignConverter;
    }

    std::string to_string( DoxVerticalAlign value )
    {
        return staticDoxVerticalAlignConverter.ToString( value );
    }
    std::string to_string( DoxVerticalAlign value, const std::string& defaultResult )
    {
        return staticDoxVerticalAlignConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxVerticalAlign ParseDoxVerticalAlign( const std::string& str )
        {
            return staticDoxVerticalAlignConverter.Parse( str );
        }

        DoxVerticalAlign ParseDoxVerticalAlign( const std::string& str, DoxVerticalAlign defaultResult )
        {
            return staticDoxVerticalAlignConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxVerticalAlign( const std::string& str, DoxVerticalAlign& value )
        {
            return staticDoxVerticalAlignConverter.TryParse( str, value );
        }
    }

    /////////
    namespace
    {
        using DoxOlType = Doxygen::DoxOlType;
        class DoxOlTypeConverter : public Enum<DoxOlType, std::string>
        {
        public:
            using Base = Enum<DoxOlType>;
            DoxOlTypeConverter( )
            {
                Add( std::string("1"), DoxOlType::Numbered);
                Add( std::string("a"), DoxOlType::a);
                Add( std::string("A"), DoxOlType::A);
                Add( std::string("i"), DoxOlType::i);
                Add( std::string("I"), DoxOlType::I);
            }
        };

        DoxOlTypeConverter staticDoxOlTypeConverter;
    }

    std::string to_string( DoxOlType value )
    {
        return staticDoxOlTypeConverter.ToString( value );
    }
    std::string to_string( DoxOlType value, const std::string& defaultResult )
    {
        return staticDoxOlTypeConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxOlType ParseDoxOlType( const std::string& str )
        {
            return staticDoxOlTypeConverter.Parse( str );
        }

        DoxOlType ParseDoxOlType( const std::string& str, DoxOlType defaultResult )
        {
            return staticDoxOlTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxOlType( const std::string& str, DoxOlType& value )
        {
            return staticDoxOlTypeConverter.TryParse( str, value );
        }
    }


    /////////
    namespace
    {
        using DoxCmdGroupType = Doxygen::DoxCmdGroupType;
        class DoxCmdGroupTypeConverter : public Enum<DoxCmdGroupType, std::string>
        {
        public:
            using Base = Enum<DoxCmdGroupType>;
            DoxCmdGroupTypeConverter( )
            {
                Add( std::string("ulink"), DoxCmdGroupType::ulink );
                Add( std::string("bold"), DoxCmdGroupType::bold );
                Add( std::string("s"), DoxCmdGroupType::s );
                Add( std::string("strike"), DoxCmdGroupType::strike );
                Add( std::string("underline"), DoxCmdGroupType::underline );
                Add( std::string("emphasis"), DoxCmdGroupType::emphasis );
                Add( std::string("computeroutput"), DoxCmdGroupType::computeroutput );
                Add( std::string("subscript"), DoxCmdGroupType::subscript );
                Add( std::string("superscript"), DoxCmdGroupType::superscript );
                Add( std::string("center"), DoxCmdGroupType::center );
                Add( std::string("small"), DoxCmdGroupType::Small );
                Add( std::string("cite"), DoxCmdGroupType::cite );
                Add( std::string("del"), DoxCmdGroupType::del );
                Add( std::string("ins"), DoxCmdGroupType::ins );
                Add( std::string("htmlonly"), DoxCmdGroupType::htmlonly );
                Add( std::string("manonly"), DoxCmdGroupType::manonly );
                Add( std::string("xmlonly"), DoxCmdGroupType::xmlonly );
                Add( std::string("rtfonly"), DoxCmdGroupType::rtfonly );
                Add( std::string("latexonly"), DoxCmdGroupType::latexonly );
                Add( std::string("docbookonly"), DoxCmdGroupType::docbookonly );
                Add( std::string("image"), DoxCmdGroupType::image );
                Add( std::string("dot"), DoxCmdGroupType::dot );
                Add( std::string("msc"), DoxCmdGroupType::msc );
                Add( std::string("plantuml"), DoxCmdGroupType::plantuml );
                Add( std::string("anchor"), DoxCmdGroupType::anchor );
                Add( std::string("formula"), DoxCmdGroupType::formula );
                Add( std::string("ref"), DoxCmdGroupType::ref );
                Add( std::string("emoji"), DoxCmdGroupType::emoji );
                Add( std::string("linebreak"), DoxCmdGroupType::linebreak );
                Add( std::string("nonbreakablespace"), DoxCmdGroupType::nonbreakablespace );
                Add( std::string("iexcl"), DoxCmdGroupType::iexcl );
                Add( std::string("cent"), DoxCmdGroupType::cent );
                Add( std::string("pound"), DoxCmdGroupType::pound );
                Add( std::string("curren"), DoxCmdGroupType::curren );
                Add( std::string("yen"), DoxCmdGroupType::yen );
                Add( std::string("brvbar"), DoxCmdGroupType::brvbar );
                Add( std::string("sect"), DoxCmdGroupType::sect );
                Add( std::string("umlaut"), DoxCmdGroupType::umlaut );
                Add( std::string("copy"), DoxCmdGroupType::copy );
                Add( std::string("ordf"), DoxCmdGroupType::ordf );
                Add( std::string("laquo"), DoxCmdGroupType::laquo );
                Add( std::string("not"), DoxCmdGroupType::Not );
                Add( std::string("shy"), DoxCmdGroupType::shy );
                Add( std::string("registered"), DoxCmdGroupType::registered );
                Add( std::string("macr"), DoxCmdGroupType::macr );
                Add( std::string("deg"), DoxCmdGroupType::deg );
                Add( std::string("plusmn"), DoxCmdGroupType::plusmn );
                Add( std::string("sup2"), DoxCmdGroupType::sup2 );
                Add( std::string("sup3"), DoxCmdGroupType::sup3 );
                Add( std::string("acute"), DoxCmdGroupType::acute );
                Add( std::string("micro"), DoxCmdGroupType::micro );
                Add( std::string("para"), DoxCmdGroupType::para );
                Add( std::string("middot"), DoxCmdGroupType::middot );
                Add( std::string("cedil"), DoxCmdGroupType::cedil );
                Add( std::string("sup1"), DoxCmdGroupType::sup1 );
                Add( std::string("ordm"), DoxCmdGroupType::ordm );
                Add( std::string("raquo"), DoxCmdGroupType::raquo );
                Add( std::string("frac14"), DoxCmdGroupType::frac14 );
                Add( std::string("frac12"), DoxCmdGroupType::frac12 );
                Add( std::string("frac34"), DoxCmdGroupType::frac34 );
                Add( std::string("iquest"), DoxCmdGroupType::iquest );
                Add( std::string("Agrave"), DoxCmdGroupType::Agrave );
                Add( std::string("Aacute"), DoxCmdGroupType::Aacute );
                Add( std::string("Acirc"), DoxCmdGroupType::Acirc );
                Add( std::string("Atilde"), DoxCmdGroupType::Atilde );
                Add( std::string("Aumlaut"), DoxCmdGroupType::Aumlaut );
                Add( std::string("Aring"), DoxCmdGroupType::Aring );
                Add( std::string("AElig"), DoxCmdGroupType::AElig );
                Add( std::string("Ccedil"), DoxCmdGroupType::Ccedil );
                Add( std::string("Egrave"), DoxCmdGroupType::Egrave );
                Add( std::string("Eacute"), DoxCmdGroupType::Eacute );
                Add( std::string("Ecirc"), DoxCmdGroupType::Ecirc );
                Add( std::string("Eumlaut"), DoxCmdGroupType::Eumlaut );
                Add( std::string("Igrave"), DoxCmdGroupType::Igrave );
                Add( std::string("Iacute"), DoxCmdGroupType::Iacute );
                Add( std::string("Icirc"), DoxCmdGroupType::Icirc );
                Add( std::string("Iumlaut"), DoxCmdGroupType::Iumlaut );
                Add( std::string("ETH"), DoxCmdGroupType::ETH );
                Add( std::string("Ntilde"), DoxCmdGroupType::Ntilde );
                Add( std::string("Ograve"), DoxCmdGroupType::Ograve );
                Add( std::string("Oacute"), DoxCmdGroupType::Oacute );
                Add( std::string("Ocirc"), DoxCmdGroupType::Ocirc );
                Add( std::string("Otilde"), DoxCmdGroupType::Otilde );
                Add( std::string("Oumlaut"), DoxCmdGroupType::Oumlaut );
                Add( std::string("times"), DoxCmdGroupType::times );
                Add( std::string("Oslash"), DoxCmdGroupType::Oslash );
                Add( std::string("Ugrave"), DoxCmdGroupType::Ugrave );
                Add( std::string("Uacute"), DoxCmdGroupType::Uacute );
                Add( std::string("Ucirc"), DoxCmdGroupType::Ucirc );
                Add( std::string("Uumlaut"), DoxCmdGroupType::Uumlaut );
                Add( std::string("Yacute"), DoxCmdGroupType::Yacute );
                Add( std::string("THORN"), DoxCmdGroupType::THORN );
                Add( std::string("szlig"), DoxCmdGroupType::szlig );
                Add( std::string("agrave"), DoxCmdGroupType::agrave );
                Add( std::string("aacute"), DoxCmdGroupType::aacute );
                Add( std::string("acirc"), DoxCmdGroupType::acirc );
                Add( std::string("atilde"), DoxCmdGroupType::atilde );
                Add( std::string("aumlaut"), DoxCmdGroupType::aumlaut );
                Add( std::string("aring"), DoxCmdGroupType::aring );
                Add( std::string("aelig"), DoxCmdGroupType::aelig );
                Add( std::string("ccedil"), DoxCmdGroupType::ccedil );
                Add( std::string("egrave"), DoxCmdGroupType::egrave );
                Add( std::string("eacute"), DoxCmdGroupType::eacute );
                Add( std::string("ecirc"), DoxCmdGroupType::ecirc );
                Add( std::string("eumlaut"), DoxCmdGroupType::eumlaut );
                Add( std::string("igrave"), DoxCmdGroupType::igrave );
                Add( std::string("iacute"), DoxCmdGroupType::iacute );
                Add( std::string("icirc"), DoxCmdGroupType::icirc );
                Add( std::string("iumlaut"), DoxCmdGroupType::iumlaut );
                Add( std::string("eth"), DoxCmdGroupType::eth );
                Add( std::string("ntilde"), DoxCmdGroupType::ntilde );
                Add( std::string("ograve"), DoxCmdGroupType::ograve );
                Add( std::string("oacute"), DoxCmdGroupType::oacute );
                Add( std::string("ocirc"), DoxCmdGroupType::ocirc );
                Add( std::string("otilde"), DoxCmdGroupType::otilde );
                Add( std::string("oumlaut"), DoxCmdGroupType::oumlaut );
                Add( std::string("divide"), DoxCmdGroupType::divide );
                Add( std::string("oslash"), DoxCmdGroupType::oslash );
                Add( std::string("ugrave"), DoxCmdGroupType::ugrave );
                Add( std::string("uacute"), DoxCmdGroupType::uacute );
                Add( std::string("ucirc"), DoxCmdGroupType::ucirc );
                Add( std::string("uumlaut"), DoxCmdGroupType::uumlaut );
                Add( std::string("yacute"), DoxCmdGroupType::yacute );
                Add( std::string("thorn"), DoxCmdGroupType::thorn );
                Add( std::string("yumlaut"), DoxCmdGroupType::yumlaut );
                Add( std::string("fnof"), DoxCmdGroupType::fnof );
                Add( std::string("Alpha"), DoxCmdGroupType::Alpha );
                Add( std::string("Beta"), DoxCmdGroupType::Beta );
                Add( std::string("Gamma"), DoxCmdGroupType::Gamma );
                Add( std::string("Delta"), DoxCmdGroupType::Delta );
                Add( std::string("Epsilon"), DoxCmdGroupType::Epsilon );
                Add( std::string("Zeta"), DoxCmdGroupType::Zeta );
                Add( std::string("Eta"), DoxCmdGroupType::Eta );
                Add( std::string("Theta"), DoxCmdGroupType::Theta );
                Add( std::string("Iota"), DoxCmdGroupType::Iota );
                Add( std::string("Kappa"), DoxCmdGroupType::Kappa );
                Add( std::string("Lambda"), DoxCmdGroupType::Lambda );
                Add( std::string("Mu"), DoxCmdGroupType::Mu );
                Add( std::string("Nu"), DoxCmdGroupType::Nu );
                Add( std::string("Xi"), DoxCmdGroupType::Xi );
                Add( std::string("Omicron"), DoxCmdGroupType::Omicron );
                Add( std::string("Pi"), DoxCmdGroupType::Pi );
                Add( std::string("Rho"), DoxCmdGroupType::Rho );
                Add( std::string("Sigma"), DoxCmdGroupType::Sigma );
                Add( std::string("Tau"), DoxCmdGroupType::Tau );
                Add( std::string("Upsilon"), DoxCmdGroupType::Upsilon );
                Add( std::string("Phi"), DoxCmdGroupType::Phi );
                Add( std::string("Chi"), DoxCmdGroupType::Chi );
                Add( std::string("Psi"), DoxCmdGroupType::Psi );
                Add( std::string("Omega"), DoxCmdGroupType::Omega );
                Add( std::string("alpha"), DoxCmdGroupType::alpha );
                Add( std::string("beta"), DoxCmdGroupType::beta );
                Add( std::string("gamma"), DoxCmdGroupType::gamma );
                Add( std::string("delta"), DoxCmdGroupType::delta );
                Add( std::string("epsilon"), DoxCmdGroupType::epsilon );
                Add( std::string("zeta"), DoxCmdGroupType::zeta );
                Add( std::string("eta"), DoxCmdGroupType::eta );
                Add( std::string("theta"), DoxCmdGroupType::theta );
                Add( std::string("iota"), DoxCmdGroupType::iota );
                Add( std::string("kappa"), DoxCmdGroupType::kappa );
                Add( std::string("lambda"), DoxCmdGroupType::lambda );
                Add( std::string("mu"), DoxCmdGroupType::mu );
                Add( std::string("nu"), DoxCmdGroupType::nu );
                Add( std::string("xi"), DoxCmdGroupType::xi );
                Add( std::string("omicron"), DoxCmdGroupType::omicron );
                Add( std::string("pi"), DoxCmdGroupType::pi );
                Add( std::string("rho"), DoxCmdGroupType::rho );
                Add( std::string("sigmaf"), DoxCmdGroupType::sigmaf );
                Add( std::string("sigma"), DoxCmdGroupType::sigma );
                Add( std::string("tau"), DoxCmdGroupType::tau );
                Add( std::string("upsilon"), DoxCmdGroupType::upsilon );
                Add( std::string("phi"), DoxCmdGroupType::phi );
                Add( std::string("chi"), DoxCmdGroupType::chi );
                Add( std::string("psi"), DoxCmdGroupType::psi );
                Add( std::string("omega"), DoxCmdGroupType::omega );
                Add( std::string("thetasym"), DoxCmdGroupType::thetasym );
                Add( std::string("upsih"), DoxCmdGroupType::upsih );
                Add( std::string("piv"), DoxCmdGroupType::piv );
                Add( std::string("bull"), DoxCmdGroupType::bull );
                Add( std::string("hellip"), DoxCmdGroupType::hellip );
                Add( std::string("prime"), DoxCmdGroupType::prime );
                Add( std::string("Prime"), DoxCmdGroupType::Prime );
                Add( std::string("oline"), DoxCmdGroupType::oline );
                Add( std::string("frasl"), DoxCmdGroupType::frasl );
                Add( std::string("weierp"), DoxCmdGroupType::weierp );
                Add( std::string("imaginary"), DoxCmdGroupType::imaginary );
                Add( std::string("real"), DoxCmdGroupType::real );
                Add( std::string("trademark"), DoxCmdGroupType::trademark );
                Add( std::string("alefsym"), DoxCmdGroupType::alefsym );
                Add( std::string("larr"), DoxCmdGroupType::larr );
                Add( std::string("uarr"), DoxCmdGroupType::uarr );
                Add( std::string("rarr"), DoxCmdGroupType::rarr );
                Add( std::string("darr"), DoxCmdGroupType::darr );
                Add( std::string("harr"), DoxCmdGroupType::harr );
                Add( std::string("crarr"), DoxCmdGroupType::crarr );
                Add( std::string("lArr"), DoxCmdGroupType::lArr );
                Add( std::string("uArr"), DoxCmdGroupType::uArr );
                Add( std::string("rArr"), DoxCmdGroupType::rArr );
                Add( std::string("dArr"), DoxCmdGroupType::dArr );
                Add( std::string("hArr"), DoxCmdGroupType::hArr );
                Add( std::string("forall"), DoxCmdGroupType::forall );
                Add( std::string("part"), DoxCmdGroupType::part );
                Add( std::string("exist"), DoxCmdGroupType::exist );
                Add( std::string("empty"), DoxCmdGroupType::empty );
                Add( std::string("nabla"), DoxCmdGroupType::nabla );
                Add( std::string("isin"), DoxCmdGroupType::isin );
                Add( std::string("notin"), DoxCmdGroupType::notin );
                Add( std::string("ni"), DoxCmdGroupType::ni );
                Add( std::string("prod"), DoxCmdGroupType::prod );
                Add( std::string("sum"), DoxCmdGroupType::sum );
                Add( std::string("minus"), DoxCmdGroupType::minus );
                Add( std::string("lowast"), DoxCmdGroupType::lowast );
                Add( std::string("radic"), DoxCmdGroupType::radic );
                Add( std::string("prop"), DoxCmdGroupType::prop );
                Add( std::string("infin"), DoxCmdGroupType::infin );
                Add( std::string("ang"), DoxCmdGroupType::ang );
                Add( std::string("and"), DoxCmdGroupType::And );
                Add( std::string("or "), DoxCmdGroupType::Or  );
                Add( std::string("cap"), DoxCmdGroupType::cap );
                Add( std::string("cup"), DoxCmdGroupType::cup );
                Add( std::string("int"), DoxCmdGroupType::Int );
                Add( std::string("there4"), DoxCmdGroupType::there4 );
                Add( std::string("sim"), DoxCmdGroupType::sim );
                Add( std::string("cong"), DoxCmdGroupType::cong );
                Add( std::string("asymp"), DoxCmdGroupType::asymp );
                Add( std::string("ne"), DoxCmdGroupType::ne );
                Add( std::string("equiv"), DoxCmdGroupType::equiv );
                Add( std::string("le"), DoxCmdGroupType::le );
                Add( std::string("ge"), DoxCmdGroupType::ge );
                Add( std::string("sub"), DoxCmdGroupType::sub );
                Add( std::string("sup"), DoxCmdGroupType::sup );
                Add( std::string("nsub"), DoxCmdGroupType::nsub );
                Add( std::string("sube"), DoxCmdGroupType::sube );
                Add( std::string("supe"), DoxCmdGroupType::supe );
                Add( std::string("oplus"), DoxCmdGroupType::oplus );
                Add( std::string("otimes"), DoxCmdGroupType::otimes );
                Add( std::string("perp"), DoxCmdGroupType::perp );
                Add( std::string("sdot"), DoxCmdGroupType::sdot );
                Add( std::string("lceil"), DoxCmdGroupType::lceil );
                Add( std::string("rceil"), DoxCmdGroupType::rceil );
                Add( std::string("lfloor"), DoxCmdGroupType::lfloor );
                Add( std::string("rfloor"), DoxCmdGroupType::rfloor );
                Add( std::string("lang"), DoxCmdGroupType::lang );
                Add( std::string("rang"), DoxCmdGroupType::rang );
                Add( std::string("loz"), DoxCmdGroupType::loz );
                Add( std::string("spades"), DoxCmdGroupType::spades );
                Add( std::string("clubs"), DoxCmdGroupType::clubs );
                Add( std::string("hearts"), DoxCmdGroupType::hearts );
                Add( std::string("diams"), DoxCmdGroupType::diams );
                Add( std::string("OElig"), DoxCmdGroupType::OElig );
                Add( std::string("oelig"), DoxCmdGroupType::oelig );
                Add( std::string("Scaron"), DoxCmdGroupType::Scaron );
                Add( std::string("scaron"), DoxCmdGroupType::scaron );
                Add( std::string("Yumlaut"), DoxCmdGroupType::Yumlaut );
                Add( std::string("circ"), DoxCmdGroupType::circ );
                Add( std::string("tilde"), DoxCmdGroupType::tilde );
                Add( std::string("ensp"), DoxCmdGroupType::ensp );
                Add( std::string("emsp"), DoxCmdGroupType::emsp );
                Add( std::string("thinsp"), DoxCmdGroupType::thinsp );
                Add( std::string("zwnj"), DoxCmdGroupType::zwnj );
                Add( std::string("zwj"), DoxCmdGroupType::zwj );
                Add( std::string("lrm"), DoxCmdGroupType::lrm );
                Add( std::string("rlm"), DoxCmdGroupType::rlm );
                Add( std::string("ndash"), DoxCmdGroupType::ndash );
                Add( std::string("mdash"), DoxCmdGroupType::mdash );
                Add( std::string("lsquo"), DoxCmdGroupType::lsquo );
                Add( std::string("rsquo"), DoxCmdGroupType::rsquo );
                Add( std::string("sbquo"), DoxCmdGroupType::sbquo );
                Add( std::string("ldquo"), DoxCmdGroupType::ldquo );
                Add( std::string("rdquo"), DoxCmdGroupType::rdquo );
                Add( std::string("bdquo"), DoxCmdGroupType::bdquo );
                Add( std::string("dagger"), DoxCmdGroupType::dagger );
                Add( std::string("Dagger"), DoxCmdGroupType::Dagger );
                Add( std::string("permil"), DoxCmdGroupType::permil );
                Add( std::string("lsaquo"), DoxCmdGroupType::lsaquo );
                Add( std::string("rsaquo"), DoxCmdGroupType::rsaquo );
                Add( std::string("euro"), DoxCmdGroupType::euro );
                Add( std::string("tm"), DoxCmdGroupType::tm );
                Add( std::string("hruler"), DoxCmdGroupType::hruler );
                Add( std::string("preformatted"), DoxCmdGroupType::preformatted );
                Add( std::string("programlisting"), DoxCmdGroupType::programlisting );
                Add( std::string("verbatim"), DoxCmdGroupType::verbatim );
                Add( std::string("javadocliteral"), DoxCmdGroupType::javadocliteral );
                Add( std::string("javadoccode"), DoxCmdGroupType::javadoccode );
                Add( std::string("indexentry"), DoxCmdGroupType::indexentry );
                Add( std::string("orderedlist"), DoxCmdGroupType::orderedlist );
                Add( std::string("itemizedlist"), DoxCmdGroupType::itemizedlist );
                Add( std::string("simplesect"), DoxCmdGroupType::simplesect );
                Add( std::string("title"), DoxCmdGroupType::title );
                Add( std::string("variablelist"), DoxCmdGroupType::variablelist );
                Add( std::string("table"), DoxCmdGroupType::table );
                Add( std::string("heading"), DoxCmdGroupType::heading );
                Add( std::string("dotfile"), DoxCmdGroupType::dotfile );
                Add( std::string("mscfile"), DoxCmdGroupType::mscfile );
                Add( std::string("diafile"), DoxCmdGroupType::diafile );
                Add( std::string("toclist"), DoxCmdGroupType::toclist );
                Add( std::string("language"), DoxCmdGroupType::language );
                Add( std::string("parameterlist"), DoxCmdGroupType::parameterlist );
                Add( std::string("xrefsect"), DoxCmdGroupType::xrefsect );
                Add( std::string("copydoc"), DoxCmdGroupType::copydoc );
                Add( std::string("details"), DoxCmdGroupType::details );
                Add( std::string("blockquote"), DoxCmdGroupType::blockquote );
                Add( std::string("parblock"), DoxCmdGroupType::parblock );
            }
        };

        DoxCmdGroupTypeConverter staticDoxCmdGroupTypeConverter;
    }

    std::string to_string( DoxCmdGroupType value )
    {
        return staticDoxCmdGroupTypeConverter.ToString( value );
    }
    std::string to_string( DoxCmdGroupType value, const std::string& defaultResult )
    {
        return staticDoxCmdGroupTypeConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxCmdGroupType ParseDoxCmdGroupType( const std::string& str )
        {
            return staticDoxCmdGroupTypeConverter.Parse( str );
        }

        DoxCmdGroupType ParseDoxCmdGroupType( const std::string& str, DoxCmdGroupType defaultResult )
        {
            return staticDoxCmdGroupTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxCmdGroupType( const std::string& str, DoxCmdGroupType& value )
        {
            return staticDoxCmdGroupTypeConverter.TryParse( str, value );
        }
    }

    
    /////////
    namespace
    {
        using DoxType = Doxygen::DoxType;
        class DoxTypeConverter : public Enum<DoxType, std::string>
        {
        public:
            using Base = Enum<DoxType>;
            DoxTypeConverter( )
            {
                Add( std::string("Unknown" ), DoxType::Unknown );
                Add( std::string("TextType" ), DoxType::TextType );
                Add( std::string("TitleType" ), DoxType::TitleType );
                Add( std::string("DocEmojiType" ), DoxType::DocEmojiType );
                Add( std::string("TableOfContentsKindType" ), DoxType::TableOfContentsKindType );
                Add( std::string("TableOfContentsType" ), DoxType::TableOfContentsType );
                Add( std::string("DocEmptyType" ), DoxType::DocEmptyType );
                Add( std::string("DocParBlockType" ), DoxType::DocParBlockType );
                Add( std::string("DocBlockQuoteType" ), DoxType::DocBlockQuoteType );
                Add( std::string("DocDetailsType" ), DoxType::DocDetailsType );
                Add( std::string("DocCopyType" ), DoxType::DocCopyType );
                Add( std::string("DocXRefSectType" ), DoxType::DocXRefSectType );
                Add( std::string("DocParamName" ), DoxType::DocParamName );
                Add( std::string("DocParamType" ), DoxType::DocParamType );
                Add( std::string("DocParamNameList" ), DoxType::DocParamNameList );
                Add( std::string("DocParamListItem" ), DoxType::DocParamListItem );
                Add( std::string("DocParamListType" ), DoxType::DocParamListType );
                Add( std::string("DocLanguageType" ), DoxType::DocLanguageType );
                Add( std::string("DocTocListType" ), DoxType::DocTocListType );
                Add( std::string("DocTocItemType" ), DoxType::DocTocItemType );
                Add( std::string("DocPlantumlType" ), DoxType::DocPlantumlType );
                Add( std::string("DocImageFileType" ), DoxType::DocImageFileType );
                Add( std::string("DocDotMscType" ), DoxType::DocDotMscType );
                Add( std::string("DocImageType" ), DoxType::DocImageType );
                Add( std::string("DocHeadingType" ), DoxType::DocHeadingType );
                Add( std::string("DocCaptionType" ), DoxType::DocCaptionType );
                Add( std::string("DocEntryType" ), DoxType::DocEntryType );
                Add( std::string("DocRowType" ), DoxType::DocRowType );
                Add( std::string("DocTableType" ), DoxType::DocTableType );
                Add( std::string("DocRefTextType" ), DoxType::DocRefTextType );
                Add( std::string("DocVariableListType" ), DoxType::DocVariableListType );
                Add( std::string("DocVarListEntryType" ), DoxType::DocVarListEntryType );
                Add( std::string("DocSimpleSectType" ), DoxType::DocSimpleSectType );
                Add( std::string("DocListItemType" ), DoxType::DocListItemType );
                Add( std::string("DocListType" ), DoxType::DocListType );
                Add( std::string("DocIndexEntryType" ), DoxType::DocIndexEntryType );
                Add( std::string("DocFormulaType" ), DoxType::DocFormulaType );
                Add( std::string("DocAnchorType" ), DoxType::DocAnchorType );
                Add( std::string("DocURLLink" ), DoxType::DocURLLink );
                Add( std::string("DocMarkupType" ), DoxType::DocMarkupType );
                Add( std::string("DocParaType" ), DoxType::DocParaType );
                //Add( std::string("DocCmdGroup" ), DoxType::DocCmdGroup );
                Add( std::string("DocSummaryType" ), DoxType::DocSummaryType );
                Add( std::string("DocTitleType" ), DoxType::DocTitleType );
                //Add( std::string("DocTitleCmdGroup" ), DoxType::DocTitleCmdGroup );
                Add( std::string("DocInternalS6Type" ), DoxType::DocInternalS6Type );
                Add( std::string("DocInternalS5Type" ), DoxType::DocInternalS5Type );
                Add( std::string("DocInternalS4Type" ), DoxType::DocInternalS4Type );
                Add( std::string("DocInternalS3Type" ), DoxType::DocInternalS3Type );
                Add( std::string("DocInternalS2Type" ), DoxType::DocInternalS2Type );
                Add( std::string("DocInternalS1Type" ), DoxType::DocInternalS1Type );
                Add( std::string("DocInternalType" ), DoxType::DocInternalType );
                Add( std::string("DocSect6Type" ), DoxType::DocSect6Type );
                Add( std::string("DocSect5Type" ), DoxType::DocSect5Type );
                Add( std::string("DocSect4Type" ), DoxType::DocSect4Type );
                Add( std::string("DocSect3Type" ), DoxType::DocSect3Type );
                Add( std::string("DocSect2Type" ), DoxType::DocSect2Type );
                Add( std::string("DocSect1Type" ), DoxType::DocSect1Type );
                Add( std::string("LocationType" ), DoxType::LocationType );
                Add( std::string("ReferenceType" ), DoxType::ReferenceType );
                Add( std::string("SpType" ), DoxType::SpType );
                Add( std::string("HighlightType" ), DoxType::HighlightType );
                Add( std::string("CodeLineType" ), DoxType::CodeLineType );
                Add( std::string("ListingType" ), DoxType::ListingType );
                Add( std::string("LinkType" ), DoxType::LinkType );
                Add( std::string("ChildNodeType" ), DoxType::ChildNodeType );
                Add( std::string("NodeType" ), DoxType::NodeType );
                Add( std::string("GraphType" ), DoxType::GraphType );
                Add( std::string("LinkedTextType" ), DoxType::LinkedTextType );
                Add( std::string("ParamType" ), DoxType::ParamType );
                Add( std::string("TemplateParamListType" ), DoxType::TemplateParamListType );
                Add( std::string("EnumvalueType" ), DoxType::EnumvalueType );
                Add( std::string("DescriptionType" ), DoxType::DescriptionType );
                Add( std::string("MemberDefType" ), DoxType::MemberDefType );
                Add( std::string("SectionDefType" ), DoxType::SectionDefType );
                Add( std::string("MemberType" ), DoxType::MemberType );
                Add( std::string("RefTextType" ), DoxType::RefTextType );
                Add( std::string("RefType" ), DoxType::RefType );
                Add( std::string("ExportType" ), DoxType::ExportType );
                Add( std::string("ExportsType" ), DoxType::ExportsType );
                Add( std::string("IncType" ), DoxType::IncType );
                Add( std::string("ReimplementType" ), DoxType::ReimplementType );
                Add( std::string("CompoundRefType" ), DoxType::CompoundRefType );
                Add( std::string("DocHtmlOnlyType" ), DoxType::DocHtmlOnlyType );
                Add( std::string("MemberRefType" ), DoxType::MemberRefType );
                Add( std::string("ListOfAllMembersType" ), DoxType::ListOfAllMembersType );
                Add( std::string("CompoundDefType" ), DoxType::CompoundDefType );
                Add( std::string("Document" ), DoxType::Document );
                Add( std::string( "DocumentCollection" ), DoxType::DocumentCollection );
            }
        };

        DoxTypeConverter staticDoxTypeConverter;
    }

    std::string to_string( Doxygen::DoxType value )
    {
        return staticDoxTypeConverter.ToString( value );
    }
    std::string to_string( Doxygen::DoxType value, const std::string& defaultResult )
    {
        return staticDoxTypeConverter.ToString( value, defaultResult );
    }
    namespace Doxygen
    {
        DoxType ParseDoxType( const std::string& str )
        {
            return staticDoxTypeConverter.Parse( str );
        }

        DoxType ParseDoxType( const std::string& str, DoxType defaultResult )
        {
            return staticDoxTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseDoxType( const std::string& str, DoxType& value )
        {
            return staticDoxTypeConverter.TryParse( str, value );
        }
    }

}
