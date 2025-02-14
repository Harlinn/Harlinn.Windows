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
#include "CodeGenerators/Cpp/CppHelper.h"

#include <HCCStringBuilder.h>

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    WideString CppHelper::GetHeaderGuard( const WideString& filename )
    {
        IO::SplitPath<WideString> splitPath( filename );
        auto name = splitPath.Name( ).ToUpper();
        auto extension = splitPath.Extension( );
        if ( extension )
        {
            extension = extension.SubString( 1 ).ToUpper( );
        }
        auto directory = splitPath.Directory( );
        if ( directory )
        {
            directory.SetLength( directory.Length() - 1 );
        }
        auto index = directory.LastIndexOf( L'\\' );
        if ( index == WideString::npos )
        {
            index = directory.LastIndexOf( L'/' );
        }
        if ( index == WideString::npos )
        {
            return Format( L"{}_{}_", name, extension );
        }
        else
        {
            directory = directory.SubString( index + 1 ).ToUpper();
            return Format( L"{}_{}_{}_", directory, name, extension );
        }
    }


    WideString CppHelper::GetNotNullableBaseType( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"bool";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"SByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"Byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"Int16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"UInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"Int32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"UInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"Int64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"UInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    result = Format( L"Types::{}", enumType->Name( ) );
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = L"float";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"double";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = L"Currency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"DateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"TimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"Guid";
            }
            break;
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBWideString<{}>", stringMemberInfo.Size( ) );
                }
                else
                {
                    result = L"WideString";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( IsBindable( member ) )
                {
                    const auto& binaryMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBBinary<{}>", binaryMemberInfo.Size( ) );
                }
                else
                {
                    result = L"Binary";
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"Int64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"Guid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"Guid";
            }
            break;
        }

        return result;
    }

    WideString CppHelper::GetBaseType( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable( ) ? L"DBBoolean " : L"bool";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"DBSByte" : L"SByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"DBByte" : L"Byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"DBInt16" : L"Int16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"DBUInt16" : L"UInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"DBInt32" : L"Int32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"DBUInt32" : L"UInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"DBInt64" : L"Int64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"DBUInt64" : L"UInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    if ( member.Nullable( ) )
                    {
                        result = Format( L"DBEnum<Types::{}>", enumType->Name( ) );
                    }
                    else
                    {
                        result = Format( L"Types::{}", enumType->Name( ) );
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"DBSingle" : L"float";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"DBDouble" : L"double";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"DBCurrency" : L"Currency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"DBDateTime" : L"DateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"DBTimeSpan" : L"TimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"DBGuid" : L"Guid";
            }
            break;
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBWideString<{}>", stringMemberInfo.Size( ) );
                }
                else
                {
                    result = member.Nullable( ) ? L"DBWideString" : L"WideString";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( IsBindable( member ) )
                {
                    const auto& binaryMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBBinary<{}>", binaryMemberInfo.Size( ) );
                }
                else
                {
                    result = member.Nullable( ) ? L"DBBinary" : L"Binary";
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"DBInt64" : L"Int64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"DBGuid" : L"Guid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"DBGuid" : L"Guid";
            }
            break;
        }

        return result;
    }

    WideString CppHelper::GetDefaultValue( const MemberInfo& member )
    {
        WideString result;
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"false";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto enumName = enumType->Name( );
                    auto defaultValue = enumType->Default( );
                    if ( defaultValue )
                    {
                        result = Format( L"Types::{}::{}", enumName, defaultValue->Name() );
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = L"0.0f";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"0.0";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::String:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"{}";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"{}";
            }
            break;
        }

        return result;
    }

    bool CppHelper::IsByReference( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        return memberType > MemberInfoType::Double && memberType != MemberInfoType::RowVersion;
    }


    WideString CppHelper::GetInputArgumentType( const MemberInfo& member )
    {
        WideString result;
        if ( member.Nullable( ) )
        {
            result = Format(L"const {}&", GetBaseType( member ));
        }
        else
        {
            auto memberInfoType = member.Type( );
            switch ( memberInfoType )
            {
                case MemberInfoType::Currency:
                {
                    result = L"const Currency&";
                }
                break;
                case MemberInfoType::DateTime:
                {
                    result = L"const DateTime&";
                }
                break;
                case MemberInfoType::TimeSpan:
                {
                    result = L"const TimeSpan&";
                }
                break;
                case MemberInfoType::Guid:
                {
                    result = L"const Guid&";
                }
                break;
                case MemberInfoType::String:
                {
                    if ( IsBindable( member ) )
                    {
                        const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                        result = Format( L"const FixedDBWideString<{}>&", stringMemberInfo.Size( ) );
                    }
                    else
                    {
                        if ( member.Nullable( ) )
                        {
                            result = L"const DBWideString&";
                        }
                        else
                        {
                            result = L"const WideString&";
                        }
                    }
                }
                break;
                case MemberInfoType::Binary:
                {
                    if ( IsBindable( member ) )
                    {
                        const auto& binaryMemberInfo = static_cast< const StringMemberInfo& >( member );
                        result = Format( L"const FixedDBBinary<{}>&", binaryMemberInfo.Size( ) );
                    }
                    else
                    {
                        if ( member.Nullable( ) )
                        {
                            result = L"const DBBinary&";
                        }
                        else
                        {
                            result = L"const Binary&";
                        }
                    }
                }
                break;
                case MemberInfoType::Reference:
                {
                    result = L"const Guid&";
                }
                break;
                case MemberInfoType::RowVersion:
                {
                    result = L"Int64&";
                }
                break;
                case MemberInfoType::TimeSeries:
                {
                    result = L"const Guid&";
                }
                break;
                default:
                {
                    result = GetBaseType( member );
                }
                break;
            }
        }
        return result;
    }

    namespace
    {
        bool IsCppKeyword( const WideString& word )
        {
            static const std::unordered_set<WideString> keywords = 
            {
                {WideString(L"alignas")},
                {WideString(L"alignof")},
                {WideString(L"and")},
                {WideString(L"and_eq")},
                {WideString(L"asm")},
                {WideString(L"atomic_cancel")},
                {WideString(L"atomic_commit")},
                {WideString(L"atomic_noexcept")},
                {WideString(L"auto")},
                {WideString(L"bitand")},
                {WideString(L"bitor")},
                {WideString(L"bool")},
                {WideString(L"break")},
                {WideString(L"case")},
                {WideString(L"catch")},
                {WideString(L"char")},
                {WideString(L"char8_t")},
                {WideString(L"char16_t")},
                {WideString(L"char32_t")},
                {WideString(L"class")},
                {WideString(L"compl")},
                {WideString(L"concept")},
                {WideString(L"const")},
                {WideString(L"consteval")},
                {WideString(L"constexpr")},
                {WideString(L"constinit")},
                {WideString(L"const_cast")},
                {WideString(L"continue")},
                {WideString(L"co_await")},
                {WideString(L"co_return")},
                {WideString(L"co_yield")},
                {WideString(L"decltype")},
                {WideString(L"default")},
                {WideString(L"delete")},
                {WideString(L"do")},
                {WideString(L"double")},
                {WideString(L"dynamic_cast")},
                {WideString(L"else")},
                {WideString(L"enum")},
                {WideString(L"explicit")},
                {WideString(L"export")},
                {WideString(L"extern")},
                {WideString(L"false")},
                {WideString(L"float")},
                {WideString(L"for")},
                {WideString(L"friend")},
                {WideString(L"goto")},
                {WideString(L"if")},
                {WideString(L"inline")},
                {WideString(L"int")},
                {WideString(L"long")},
                {WideString(L"mutable")},
                {WideString(L"namespace")},
                {WideString(L"new")},
                {WideString(L"noexcept")},
                {WideString(L"not")},
                {WideString(L"not_eq")},
                {WideString(L"nullptr")},
                {WideString(L"operator")},
                {WideString(L"or")},
                {WideString(L"or_eq")},
                {WideString(L"private")},
                {WideString(L"protected")},
                {WideString(L"public")},
                {WideString(L"reflexpr")},
                {WideString(L"register")},
                {WideString(L"reinterpret_cast")},
                {WideString(L"requires")},
                {WideString(L"return")},
                {WideString(L"short")},
                {WideString(L"signed")},
                {WideString(L"sizeof")},
                {WideString(L"static")},
                {WideString(L"static_assert")},
                {WideString(L"static_cast")},
                {WideString(L"struct")},
                {WideString(L"switch")},
                {WideString(L"synchronized")},
                {WideString(L"template")},
                {WideString(L"this")},
                {WideString(L"thread_local")},
                {WideString(L"throw")},
                {WideString(L"true")},
                {WideString(L"try")},
                {WideString(L"typedef")},
                {WideString(L"typeid")},
                {WideString(L"typename")},
                {WideString(L"union")},
                {WideString(L"unsigned")},
                {WideString(L"using")},
                {WideString(L"virtual")},
                {WideString(L"void")},
                {WideString(L"volatile")},
                {WideString(L"wchar_t")},
                {WideString(L"while")},
                {WideString(L"xor")},
                {WideString(L"xor_eq")}
            };
            return keywords.contains( word );
        }
    }


    WideString CppHelper::GetInputArgumentName( const MemberInfo& member )
    {
        auto result = member.Name( ).FirstToLower( );
        if ( IsCppKeyword( result ) )
        {
            return Format( L"{}__", result );
        }
        return result;
    }

    WideString CppHelper::GetBindParameterFunctionName( const MemberInfo& member )
    {
        WideString result;
        auto memberType = member.Type( );
        switch ( memberType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"BindBooleanParameter";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"BindSByteParameter";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"BindByteParameter";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"BindInt16Parameter";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"BindUInt16Parameter";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"BindInt32Parameter";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"BindUInt32Parameter";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"BindInt64Parameter";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"BindUInt64Parameter";
            }
            break;
            case MemberInfoType::Enum:
            {
                result = L"BindEnumParameter";
            }
            break;
            case MemberInfoType::Single:
            {
                result = L"BindSingleParameter";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"BindDoubleParameter";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"BindDateTimeParameter";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"BindTimeSpanParameter";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"BindGuidParameter";
            }
            break;
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    result = L"BindFixedDBWideStringParameter";
                }
                else
                {
                    result = L"BindStringParameter";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( IsBindable( member ) )
                {
                    result = L"BindFixedDBBinaryParameter";
                }
                else
                {
                    result = L"BindBinaryParameter";
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"BindInt64Parameter";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"BindGuidParameter";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"BindGuidParameter";
            }
            break;
        }
        return result;
    }


    WideString CppHelper::GetMemberFieldType( const MemberInfo& member )
    {
        WideString result = GetBaseType( member );
        return result;
    }

    WideString CppHelper::GetMemberNullableFieldType( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"DBBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"DBSByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"DBByte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"DBInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"DBUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"DBInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"DBUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"DBInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"DBUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    result = Format( L"DBEnum<Types::{}>", enumType->Name( ) );
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = L"DBSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"DBDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = L"DBCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"DBDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"DBTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"DBGuid";
            }
            break;
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBWideString<{}>", stringMemberInfo.Size( ) );
                }
                else
                {
                    result = L"DBWideString";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( IsBindable( member ) )
                {
                    const auto& binaryMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"FixedDBBinary<{}>", binaryMemberInfo.Size( ) );
                }
                else
                {
                    result = L"DBBinary";
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"DBInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"DBGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"DBGuid";
            }
            break;
        }

        return result;
    }

    WideString CppHelper::GetDataMemberFieldType( const MemberInfo& member )
    {
        WideString result = GetBaseType( member );
        return result;
    }


    WideString CppHelper::GetMemberFieldName( const MemberInfo& member )
    {
        return Format(L"{}_", member.Name().FirstToLower() );
    }

    WideString CppHelper::GetLongMemberFieldName( const MemberInfo& member )
    {
        auto owner = member.Owner( );
        auto shortName = owner->ShortName( ).ToLower();
        return Format( L"{}{}_", shortName, member.Name( ).FirstToUpper( ) );
    }

    WideString CppHelper::GetMemberAccessorName( const MemberInfo& member )
    {
        return member.Name( ).FirstToUpper( );
    }
    WideString CppHelper::GetMemberAccessorReturnType( const MemberInfo& member )
    {
        WideString result;
        auto memberInfoType = member.Type( );
        auto baseType = GetBaseType( member );
        if ( member.Nullable( ) == false && ( memberInfoType <= MemberInfoType::Double || memberInfoType == MemberInfoType::RowVersion ))
        {
            result = baseType;
        }
        else
        {
            result = Format( L"const {}&", baseType );
        }

        return result;
    }
    WideString CppHelper::GetMemberSetterName( const MemberInfo& member )
    {
        return Format( L"Set{}", member.Name( ).FirstToUpper( ) );
    }

    
    bool CppHelper::IsBindable( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        auto result = true;
        switch ( memberType )
        {
            case MemberInfoType::String:
            {
                const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                result = ( stringMemberInfo.Size( ) == 0 || stringMemberInfo.Size( ) > 260 ) ? false : true;
            }
            break;
            case MemberInfoType::Binary:
            {
                const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( member );
                result = ( binaryMemberInfo.Size( ) == 0 || binaryMemberInfo.Size( ) > 512 ) ? false : true;
            }
            break;
        }
        return result;
    }


    bool CppHelper::RequiresIndicator( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
        {
            return IsBindable( member ) == false;
        }
        return false;
    }
    WideString CppHelper::GetMemberIndicatorName( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
        {
            if ( member.Nullable( ) )
            {
                return Format( L"{}LengthOrNullIndicator_", member.Name( ).FirstToLower( ) );
            }
            else
            {
                return Format( L"{}Length_", member.Name( ).FirstToLower( ) );
            }
        }

        return Format( L"{}NullIndicator_", member.Name( ).FirstToLower( ) );
    }

    bool CppHelper::MemberFieldRequiresDefaultValue( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( member.Nullable() == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::RowVersion ) )
        {
            return true;
        }
        return false;
    }

    WideString CppHelper::GetColumnDataType( const ClassInfo& classInfo )
    {
        return Format( L"{}ColumnData", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CppHelper::GetComplexColumnDataType( const ClassInfo& classInfo )
    {
        return Format( L"Complex{}ColumnData", classInfo.Name( ).FirstToUpper( ) );
    }


    WideString CppHelper::GetDataType( const ClassInfo& classInfo )
    {
        return Format( L"{}Object", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CppHelper::GetSimpleTestValue( const ClassInfo& classInfo, const MemberInfo& member )
    {
        WideString result;
        auto hashValue = classInfo.Name( ).Hash( );
        auto memberType = member.Type( );
        switch ( memberType )
        {
            case MemberInfoType::Boolean:
            {
                result = hashValue % 1 ? L"true" : L"false";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = Format(L"{}", static_cast< SByte >( hashValue ) );
            }
            break;
            case MemberInfoType::Byte:
            {
                result = Format( L"{}", static_cast< Byte >( hashValue ) );
            }
            break;
            case MemberInfoType::Int16:
            {
                result = Format( L"{}", static_cast< Int16 >( hashValue ) );
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = Format( L"{}", static_cast< UInt16 >( hashValue ) );
            }
            break;
            case MemberInfoType::Int32:
            {
                result = Format( L"{}L", static_cast< Int32 >( hashValue ) );
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = Format( L"{}UL", static_cast< UInt32 >( hashValue ) );
            }
            break;
            case MemberInfoType::Int64:
            {
                result = Format( L"{}LL", static_cast< Int64 >( hashValue ) );
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = Format( L"{}ULL", static_cast< UInt64 >( hashValue ) );
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    const auto& enumValues = enumType->Values( );
                    const auto& enumValue = enumValues[ hashValue % enumValues.size( ) ];
                    result = Format( L"{}::{}", enumType->Name( ), enumValue->Name() );
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = Format( L"{}f", static_cast< float >( hashValue ) / 1000.0f );
            }
            break;
            case MemberInfoType::Double:
            {
                result = Format( L"{}", static_cast< double >( hashValue ) / 1000.0 );
            }
            break;
            case MemberInfoType::Currency:
            {
                result = Format( L"Currency({})", static_cast< Int64 >( hashValue ) );
            }
            break;
            case MemberInfoType::DateTime:
            {
                DateTime dateTime( DateTime::Now( ).Ticks( ) % DateTime::TicksPerDay );
                result = Format( L"DateTime( {}, {}, {}, {}, {}, {} )", dateTime.Year(), dateTime.Month(), dateTime.Day(), dateTime.Hour(), dateTime.Minute(), dateTime.Second() );
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                TimeSpan timeSpan( static_cast< Int64 >( hashValue ) % TimeSpan::TicksPerDay );
                result = Format( L"TimeSpan( {}LL )", timeSpan.Ticks() );
            }
            break;
            case MemberInfoType::Guid:
            {
                Guid guid( static_cast< UInt64 >( hashValue ), ReverseBits( static_cast< UInt64 >( hashValue ) ) );
                result = Format( L"Guid( L\"{}\" )", guid.ToWideString() );
            }
            break;
            case MemberInfoType::String:
            {
                const auto& stringMember = static_cast< const StringMemberInfo& >( member );
                if ( IsBindable( member ) )
                {
                    if ( stringMember.Size( ) )
                    {
                        auto text = member.Name( ).SubString( 0, stringMember.Size( ) );
                        result = Format( L"L\"{}\"", text );
                    }
                    else
                    {
                        result = Format( L"L\"{}\"", member.Name( ) );
                    }
                }
                else
                {
                    if ( stringMember.Size( ) )
                    {
                        auto text = member.Name( ).SubString( 0, stringMember.Size( ) );
                        result = Format( L"WideString(L\"{}\")", text );
                    }
                    else
                    {
                        result = Format( L"WideString(L\"{}\")", member.Name( ) );
                    }
                }
            }
            break;

            case MemberInfoType::Binary:
            {
                const auto& binaryMember = static_cast< const BinaryMemberInfo& >( member );
                if ( binaryMember.Size( ) )
                {
                    StringBuilder<wchar_t> sb;
                    auto text = member.Name( ).SubString( 0, binaryMember.Size( ) );
                    for ( const auto& c : text )
                    {
                        sb.Append( L"\'{}\',", c );
                    }
                    auto bytes = sb.ToString( );
                    bytes.SetLength( bytes.Length( ) - 1 );

                    result = Format( L"Binary{{ {{{}}} }}", bytes );
                }
                else
                {
                    StringBuilder<wchar_t> sb;
                    auto text = member.Name( );
                    for ( const auto& c : text )
                    {
                        sb.Append( L"\'{}\',", c );
                    }
                    auto bytes = sb.ToString( );
                    bytes.SetLength( bytes.Length( ) - 1 );

                    result = Format( L"Binary{{ {{{}}} }}", bytes );
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = Format( L"{}LL", static_cast< Int64 >( hashValue ) );
            }
            break;
            case MemberInfoType::Reference:
            {
                Guid guid( static_cast< UInt64 >( hashValue ), ReverseBits( static_cast< UInt64 >( hashValue ) ) );
                result = Format( L"Guid( L\"{}\" )", guid.ToWideString( ) );
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                Guid guid( static_cast< UInt64 >( hashValue ), ReverseBits( static_cast< UInt64 >( hashValue ) ) );
                result = Format( L"Guid( L\"{}\" )", guid.ToWideString( ) );
            }
            break;
        }
        return result;
    }

    WideString CppHelper::GetInsertFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Insert{}", classInfo.Name( ) );
    }
    WideString CppHelper::GetInsertFunctionName1( const ClassInfo& classInfo )
    {
        return Format( L"Insert1{}", classInfo.Name( ) );
    }

    WideString CppHelper::GetUpdateFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Update{}", classInfo.Name( ) );
    }

    WideString CppHelper::GetUpdateFunctionName1( const ClassInfo& classInfo )
    {
        return Format( L"Update1{}", classInfo.Name( ) );
    }
    WideString CppHelper::GetUpdateFunctionName2( const ClassInfo& classInfo )
    {
        return Format( L"Update2{}", classInfo.Name( ) );
    }

    WideString CppHelper::GetDeleteFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Delete{}", classInfo.Name( ) );
    }

    WideString CppHelper::GetInsertFunctionParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}& {}", primaryKeyArgumentType, primaryKeyName  );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    auto variableName = GetInputArgumentName( member );
                    auto variableType = GetInputArgumentType( member );

                    parameters.Append( L", {} {}", variableType, variableName );
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CppHelper::GetInsertFunctionCallParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    auto variableName = GetInputArgumentName( member );
                    auto variableType = GetInputArgumentType( member );

                    parameters.Append( L", {}", variableName );
                }
            }
        }
        return parameters.ToString( );
    }

    WideString CppHelper::GetInsertFunctionParameterMarkers( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> markers;

        markers.Append( L"?" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    markers.Append( L", ?" );
                }
            }
        }
        return markers.ToString( );
    }

    WideString CppHelper::GetInsertFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetInsertFunctionParameters( classInfo, members );
    }


    WideString CppHelper::GetInsertFunctionParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetInsertFunctionParameters( classInfo, members );
    }

    WideString CppHelper::GetInsertFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetInsertFunctionCallParameters( classInfo, members );
    }

    WideString CppHelper::GetInsertFunctionCallParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetInsertFunctionCallParameters( classInfo, members );
    }

    WideString CppHelper::GetInsertFunctionParameterMarkers( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetInsertFunctionParameterMarkers( classInfo, members );
    }

    WideString CppHelper::GetInsertFunctionParameterMarkers1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetInsertFunctionParameterMarkers( classInfo, members );
    }


    WideString CppHelper::GetUpdateFunctionParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"const {}& {}", primaryKeyArgumentType, primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                parameters.Append( L", {} {}", variableType, variableName );
            }
        }
        return parameters.ToString( );
    }
    WideString CppHelper::GetUpdateFunctionCallParameters( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                parameters.Append( L", {}", variableName );
            }
        }
        return parameters.ToString( );
    }

    WideString CppHelper::GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo, const std::vector<std::shared_ptr<MemberInfo>>& members )
    {
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> markers;

        markers.Append( L"?" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {

                markers.Append( L", ?" );
            }
        }
        return markers.ToString( );
    }


    WideString CppHelper::GetUpdateFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetUpdateFunctionParameters( classInfo, members );
    }

    WideString CppHelper::GetUpdateFunctionParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetUpdateFunctionParameters( classInfo, members );
    }

    WideString CppHelper::GetUpdateFunctionParameters2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        return GetUpdateFunctionParameters( classInfo, members );
    }

    WideString CppHelper::GetUpdateFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetUpdateFunctionCallParameters( classInfo, members );
    }
    WideString CppHelper::GetUpdateFunctionCallParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetUpdateFunctionCallParameters( classInfo, members );
    }
    WideString CppHelper::GetUpdateFunctionCallParameters2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        return GetUpdateFunctionCallParameters( classInfo, members );
    }

    WideString CppHelper::GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetUpdateFunctionParameterMarkers( classInfo, members );
    }
    WideString CppHelper::GetUpdateFunctionParameterMarkers1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        return GetUpdateFunctionParameterMarkers( classInfo, members );
    }
    WideString CppHelper::GetUpdateFunctionParameterMarkers2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        return GetUpdateFunctionParameterMarkers( classInfo, members );
    }


    WideString CppHelper::GetDeleteFunctionParameters( const ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"const {}& {}", primaryKeyArgumentType, primaryKeyName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionName = GetInputArgumentName( *rowVersion );
            parameters.Append( L", Int64 {}", rowVersionName );
        }
        return parameters.ToString( );
    }
    WideString CppHelper::GetDeleteFunctionCallParameters( const ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionName = GetInputArgumentName( *rowVersion );
            parameters.Append( L", {}", rowVersionName );
        }
        return parameters.ToString( );
    }

    WideString CppHelper::GetDeleteFunctionParameterMarkers( const ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> markers;

        markers.Append( L"?, ?" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionName = GetInputArgumentName( *rowVersion );
            markers.Append( L", ?", rowVersionName );
        }
        return markers.ToString( );
    }

    WideString CppHelper::GetByIdFunctionName( const ClassInfo& classInfo )
    {
        auto result = Format( L"Get{}ById", classInfo.Name( ) );
        return result;
    }
    WideString CppHelper::GetAllFunctionName( const ClassInfo& classInfo )
    {
        auto result = Format( L"Get{}Collection", classInfo.Name( ) );
        return result;
    }
    WideString CppHelper::GetByIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        if ( indexMemberCount > 1 )
        {
            for ( size_t i = indexDepth; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                if ( i < ( indexMemberCount - 1 ) )
                {
                    sb.Append( indexMember.Name( ) );
                }
                else
                {
                    auto s = Format( L"And{}", indexMember.Name( ) );
                    sb.Append( s );
                }
            }
        }
        else
        {
            sb.Append( indexMembers[ 0 ]->Name( ) );
        }
        if ( indexInfo.Unique( ) && indexMemberCount == indexMembers.size( ) )
        {
            auto result = Format( L"Get{}By{}", classInfo.Name( ), sb.ToString( ) );
            return result;
        }
        else
        {
            auto result = Format( L"Get{}CollectionBy{}", classInfo.Name( ), sb.ToString( ) );
            return result;
        }
    }

    WideString CppHelper::GetByNullableIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        if ( indexMemberCount > 1 )
        {
            for ( size_t i = 0; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                if ( i < ( indexMemberCount - 1 ) )
                {
                    if ( indexMember.Nullable( ) )
                    {
                        sb.Append( indexMember.Name( ) + L"IsNull" );
                    }
                    else
                    {
                        sb.Append( indexMember.Name( ) );
                    }
                }
                else
                {
                    if ( indexMember.Nullable( ) )
                    {
                        auto s = Format( L"And{}IsNull", indexMember.Name( ) );
                        sb.Append( s );
                    }
                    else
                    {
                        auto s = Format( L"And{}", indexMember.Name( ) );
                        sb.Append( s );
                    }
                }
            }
        }
        else
        {
            if ( indexMembers[ 0 ]->Nullable( ) )
            {
                sb.Append( indexMembers[ 0 ]->Name( ) + L"IsNull" );
            }
            else
            {
                sb.Append( indexMembers[ 0 ]->Name( ) );
            }
        }
        auto result = Format( L"Get{}CollectionBy{}", classInfo.Name( ), sb.ToString( ) );
        return result;
    }


    WideString CppHelper::GetByIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterType = GetInputArgumentType( indexMember );
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{} {}, ", parameterType, parameterName );
            }
            else
            {
                sb.Append( L"{} {}", parameterType, parameterName );
            }
        }
        return sb.ToString( );
    }
    WideString CppHelper::GetByIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{}, ", parameterName );
            }
            else
            {
                sb.Append( L"{}", parameterName );
            }
        }
        return sb.ToString( );
    }

    WideString CppHelper::GetByNullableIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto indexMembers = indexInfo.RequiredFields( indexMemberCount );
        indexMemberCount--;
        StringBuilder<wchar_t> sb;
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterType = GetInputArgumentType( indexMember );
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{} {}, ", parameterType, parameterName );
            }
            else
            {
                sb.Append( L"{} {}", parameterType, parameterName );
            }
        }
        return sb.ToString( );
    }
    WideString CppHelper::GetByNullableIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto indexMembers = indexInfo.RequiredFields( indexMemberCount );
        indexMemberCount--;
        StringBuilder<wchar_t> sb;
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{}, ", parameterName );
            }
            else
            {
                sb.Append( L"{}", parameterName );
            }
        }
        return sb.ToString( );
    }

    WideString CppHelper::GetByIndexFunctionName( const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        if ( indexMemberCount > ( indexDepth + 1 ) )
        {
            StringBuilder<wchar_t> sb;
            for ( size_t i = indexDepth; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                if ( i < ( indexMemberCount - 1 ) )
                {
                    sb.Append( indexMember.Name( ) );
                }
                else
                {
                    auto s = Format( L"{}{}", lastFieldPrefix, indexMember.Name( ) );
                    sb.Append( s );
                }
            }
            if ( indexInfo.Unique( ) && indexMemberCount == indexMembers.size( ) )
            {
                auto result = Format( L"Get{}By{}", classInfo.Name( ), sb.ToString( ) );
                return result;
            }
            else
            {
                auto result = Format( L"Get{}CollectionBy{}", classInfo.Name( ), sb.ToString( ) );
                return result;
            }
        }
        else
        {
            if ( indexInfo.Unique( ) && indexMemberCount == indexMembers.size( ) )
            {
                auto result = Format( L"Get{}{}{}", classInfo.Name( ), lastFieldPrefix, indexMembers[ 0 ]->Name( ) );
                return result;
            }
            else
            {
                auto result = Format( L"Get{}Collection{}{}", classInfo.Name( ), lastFieldPrefix, indexMembers[ 0 ]->Name( ) );
                return result;
            }
        }
    }
    WideString CppHelper::GetByIndexAtFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString(L"At"), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CppHelper::GetByIndexFromFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"From" ), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CppHelper::GetByIndexUntilFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"Until" ), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CppHelper::GetByIndexOverFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"Over" ), classInfo, indexInfo, indexDepth, indexMemberCount );
    }

    WideString CppHelper::GetByIndexFunctionOverParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        for ( size_t i = indexDepth; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterType = GetNotNullableBaseType( indexMember );
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{} {}, ", parameterType, parameterName );
            }
            else
            {
                parameterName = parameterName.FirstToUpper( );
                sb.Append( L"{} from{}, ", parameterType, parameterName );
                sb.Append( L"{} until{}", parameterType, parameterName );
            }
        }
        return sb.ToString( );
    }

    WideString CppHelper::GetByIndexFunctionOverCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        for ( size_t i = indexDepth; i < indexMemberCount; i++ )
        {
            const auto& indexMember = *indexMembers[ i ];
            auto parameterName = GetInputArgumentName( indexMember );
            if ( i < ( indexMemberCount - 1 ) )
            {
                sb.Append( L"{}, ", parameterName );
            }
            else
            {
                parameterName = parameterName.FirstToUpper( );
                sb.Append( L"from{}, ", parameterName );
                sb.Append( L"until{}", parameterName );
            }
        }
        return sb.ToString( );
    }


    bool CppHelper::IsUnique( const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        if ( indexInfo.Unique( ) && indexMemberCount == indexMembers.size( ) )
        {
            return true;
        }
        return false;
    }

    bool CppHelper::RequiresComplexReader( const ClassInfo& classInfo )
    {
        return classInfo.DerivedClasses( ).size( ) > 0;
    }


}