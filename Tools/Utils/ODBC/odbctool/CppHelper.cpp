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

    WideString CppHelper::GetNamespace( const ModelInfo& model, const WideString& filename )
    {
        auto name = model.Name( ).FirstToUpper();
        IO::SplitPath<WideString> splitPath( filename );

        auto directory = splitPath.Directory( );
        if ( directory )
        {
            directory.SetLength( directory.Length( ) - 1 );
        }
        auto index = directory.LastIndexOf( L'\\' );
        if ( index == WideString::npos )
        {
            index = directory.LastIndexOf( L'/' );
        }
        if ( index == WideString::npos )
        {
            return name;
        }
        else
        {
            directory = directory.SubString( index + 1 ).FirstToUpper( );
            return Format( L"{}::{}", name, directory );
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
                    result = Format(L"Data::{}",enumType->Name( ));
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
                result = L"WideString";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"std::vector<Byte>";
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
                        result = Format( L"Data::{}::{}", enumName, defaultValue->Name() );
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
                result = L"const WideString&";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"const std::vector<Byte>&";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"const Guid&";
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
        auto result = Format( L"{}", member.Name( ).FirstToLower( ) );
        if ( IsCppKeyword( result ) )
        {
            return Format( L"{}__", result );
        }
        return result;
    }

    WideString CppHelper::GetMemberFieldType( const MemberInfo& member )
    {
        WideString result;
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                    result = Format( L"std::array<wchar_t,{}>", stringMemberInfo.Size( ) + 1 );
                }
                else
                {
                    result = L"WideString";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if(IsBindable( member ))
                { 
                    const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( member );
                    result = Format(L"std::array<Byte,{}>", binaryMemberInfo.Size() );
                }
                else
                {
                    
                    result = L"std::vector<Byte>";
                }
            }
            break;
            default:
            {
                result = GetBaseType( member );
            }
            break;
        }
        return result;
    }

    WideString CppHelper::GetMemberFieldName( const MemberInfo& member )
    {
        return Format(L"{}_", member.Name().FirstToLower() );
    }

    WideString CppHelper::GetMemberAccessorName( const MemberInfo& member )
    {
        return member.Name( ).FirstToUpper( );
    }
    WideString CppHelper::GetMemberAccessorReturnType( const MemberInfo& member )
    {
        WideString result;
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::String:
            {
                if ( IsBindable( member ) )
                {
                    result = L"std::wstring_view";
                }
                else
                {
                    result = L"const WideString&";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( IsBindable( member ) )
                {
                    result = Format( L"std::span<Byte>");
                }
                else
                {

                    result = L"const std::vector<Byte>&";
                }
            }
            break;
            default:
            {
                result = GetBaseType( member );
            }
            break;
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
        if ( member.Nullable( ) )
        {
            return true;
        }
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
        {
            return true;
        }
        return false;
    }
    WideString CppHelper::GetMemberIndicatorName( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
        {
            return Format( L"{}LengthOrNullIndicator_", member.Name( ).FirstToLower( ) );
        }

        return Format( L"{}NullIndicator_", member.Name( ).FirstToLower( ) );
    }

    bool CppHelper::MemberFieldRequiresDefaultValue( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::RowVersion )
        {
            return true;
        }
        if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
        {
            return IsBindable( member );
        }
        return false;
    }

    WideString CppHelper::GetColumnDataType( const ClassInfo& classInfo )
    {
        return Format( L"{}ColumnData", classInfo.Name( ).FirstToUpper( ) );
    }

}