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
#include "CppHelper.h"
#include <HCCStringBuilder.h>

namespace Harlinn::ODBC::Tool
{
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


    WideString CppHelper::GetBaseType( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable()? L"DBBoolean ": L"bool";
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
                {L"alignas"},
                {L"alignof"},
                {L"and"},
                {L"and_eq"},
                {L"asm"},
                {L"atomic_cancel"},
                {L"atomic_commit"},
                {L"atomic_noexcept"},
                {L"auto"},
                {L"bitand"},
                {L"bitor"},
                {L"bool"},
                {L"break"},
                {L"case"},
                {L"catch"},
                {L"char"},
                {L"char8_t"},
                {L"char16_t"},
                {L"char32_t"},
                {L"class"},
                {L"compl"},
                {L"concept"},
                {L"const"},
                {L"consteval"},
                {L"constexpr"},
                {L"constinit"},
                {L"const_cast"},
                {L"continue"},
                {L"co_await"},
                {L"co_return"},
                {L"co_yield"},
                {L"decltype"},
                {L"default"},
                {L"delete"},
                {L"do"},
                {L"double"},
                {L"dynamic_cast"},
                {L"else"},
                {L"enum"},
                {L"explicit"},
                {L"export"},
                {L"extern"},
                {L"false"},
                {L"float"},
                {L"for"},
                {L"friend"},
                {L"goto"},
                {L"if"},
                {L"inline"},
                {L"int"},
                {L"long"},
                {L"mutable"},
                {L"namespace"},
                {L"new"},
                {L"noexcept"},
                {L"not"},
                {L"not_eq"},
                {L"nullptr"},
                {L"operator"},
                {L"or"},
                {L"or_eq"},
                {L"private"},
                {L"protected"},
                {L"public"},
                {L"reflexpr"},
                {L"register"},
                {L"reinterpret_cast"},
                {L"requires"},
                {L"return"},
                {L"short"},
                {L"signed"},
                {L"sizeof"},
                {L"static"},
                {L"static_assert"},
                {L"static_cast"},
                {L"struct"},
                {L"switch"},
                {L"synchronized"},
                {L"template"},
                {L"this"},
                {L"thread_local"},
                {L"throw"},
                {L"true"},
                {L"try"},
                {L"typedef"},
                {L"typeid"},
                {L"typename"},
                {L"union"},
                {L"unsigned"},
                {L"using"},
                {L"virtual"},
                {L"void"},
                {L"volatile"},
                {L"wchar_t"},
                {L"while"},
                {L"xor"},
                {L"xor_eq"}
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
                    result = L"BindWideStringParameter";
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
        WideString result = L"<unknown>";
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
                result = Format( L"Guid( L\"{}\" )", guid.ToString() );
            }
            break;
            case MemberInfoType::String:
            {
                const auto& stringMember = static_cast< const StringMemberInfo& >( member );
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

                    result = Format( L"{{ {{{}}} }}", bytes );
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

                    result = Format( L"{{ {{{}}} }}", bytes );
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
                result = Format( L"Guid( L\"{}\" )", guid.ToString( ) );
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                Guid guid( static_cast< UInt64 >( hashValue ), ReverseBits( static_cast< UInt64 >( hashValue ) ) );
                result = Format( L"Guid( L\"{}\" )", guid.ToString( ) );
            }
            break;
        }
        return result;
    }

    WideString CppHelper::GetInsertFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Insert{}", classInfo.Name( ) );
    }
    WideString CppHelper::GetUpdateFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Update{}", classInfo.Name( ) );
    }
    WideString CppHelper::GetDeleteFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Delete{}", classInfo.Name( ) );
    }

    WideString CppHelper::GetInsertFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}& {}", primaryKeyArgumentType, primaryKeyName  );

        if ( membersCount > 0 )
        {
            parameters.Append( L"," );
        }


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

                    if ( i < ( membersCount - 1 ) )
                    {
                        parameters.Append( L" {} {},", variableType, variableName );
                    }
                    else
                    {
                        parameters.Append( L" {} {}", variableType, variableName );
                    }
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CppHelper::GetInsertFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        if ( membersCount > 0 )
        {
            parameters.Append( L"," );
        }


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

                    if ( i < ( membersCount - 1 ) )
                    {
                        parameters.Append( L" {},", variableName );
                    }
                    else
                    {
                        parameters.Append( L" {}", variableName );
                    }
                }
            }
        }
        return parameters.ToString( );
    }

    WideString CppHelper::GetInsertFunctionParameterMarkers( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> markers;

        markers.Append( L"?" );

        if ( membersCount > 0 )
        {
            markers.Append( L"," );
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    if ( i < ( membersCount - 1 ) )
                    {
                        markers.Append( L" ?," );
                    }
                    else
                    {
                        markers.Append( L" ?" );
                    }
                }
            }
        }
        return markers.ToString( );
    }


    WideString CppHelper::GetUpdateFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"const {}& {}", primaryKeyArgumentType, primaryKeyName );

        if ( membersCount > 0 )
        {
            parameters.Append( L"," );
        }


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                if ( i < ( membersCount - 1 ) )
                {
                    parameters.Append( L" {} {},", variableType, variableName );
                }
                else
                {
                    parameters.Append( L" {} {}", variableType, variableName );
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CppHelper::GetUpdateFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        if ( membersCount > 0 )
        {
            parameters.Append( L"," );
        }


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                if ( i < ( membersCount - 1 ) )
                {
                    parameters.Append( L" {},", variableName );
                }
                else
                {
                    parameters.Append( L" {}", variableName );
                }
            }
        }
        return parameters.ToString( );
    }

    WideString CppHelper::GetUpdateFunctionParameterMarkers( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> markers;

        markers.Append( L"?" );

        if ( membersCount > 0 )
        {
            markers.Append( L"," );
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {

                if ( i < ( membersCount - 1 ) )
                {
                    markers.Append( L" ?," );
                }
                else
                {
                    markers.Append( L" ?" );
                }
            }
        }
        return markers.ToString( );
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


}