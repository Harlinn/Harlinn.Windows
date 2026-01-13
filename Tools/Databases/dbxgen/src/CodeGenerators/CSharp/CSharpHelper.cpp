/*
   Copyright 2024-2026 Espen Harlinn

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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/CSharp/CSharpHelper.h"

#include "HCCStringBuilder.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    WideString CSharpHelper::GetNotNullableBaseType( const MemberInfo& member )
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
                result = L"sbyte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"short";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"ushort";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"int";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"uint";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"long";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"ulong";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    result = Format( L"Types.{}", enumType->Name( ) );
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
                result = L"string";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"byte[]";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"long";
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

    WideString CSharpHelper::GetBaseType( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable( ) ? L"bool?" : L"bool";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"sbyte?" : L"sbyte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"byte?" : L"byte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"short?" : L"short";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"ushort?" : L"ushort";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"int?" : L"int";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"uint?" : L"uint";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"long?" : L"long";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"ulong?" : L"ulong";
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
                        result = Format( L"Types.{}?", enumType->Name( ) );
                    }
                    else
                    {
                        result = Format( L"Types.{}", enumType->Name( ) );
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"float?" : L"float";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"double?" : L"double";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"Currency?" : L"Currency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"DateTime?" : L"DateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"TimeSpan?" : L"TimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"Guid?" : L"Guid";
            }
            break;
            case MemberInfoType::String:
            {
                result = member.Nullable( ) ? L"string?" : L"string";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = member.Nullable( ) ? L"byte[]?" : L"byte[]";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"long?" : L"long";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"Guid?" : L"Guid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"Guid?" : L"Guid";
            }
            break;
        }

        return result;
    }

    WideString CSharpHelper::GetDefaultValue( const MemberInfo& member )
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
                        result = Format( L"Types.{}.{}", enumName, defaultValue->Name( ) );
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
                result = L"default";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"default";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"default";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"default";
            }
            break;
            case MemberInfoType::String:
            {
                if ( member.Nullable( ) )
                {
                    result = L"default";
                }
                else
                {
                    result = L"string.Empty";
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                if ( member.Nullable( ) )
                {
                    result = L"default";
                }
                else
                {
                    result = L"Array.Empty<byte>()";
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"0";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"default";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"default";
            }
            break;
        }

        return result;
    }

    WideString CSharpHelper::GetInputArgumentType( const MemberInfo& member )
    {
        WideString result = GetBaseType( member );
        return result;
    }

    namespace
    {
        bool IsCSharpKeyword( const WideString& word )
        {
            static const std::unordered_set<WideString> keywords =
            {
                {WideString(L"abstract")},
                {WideString(L"as")},
                {WideString(L"base")},
                {WideString(L"bool")},
                {WideString(L"break")},
                {WideString(L"byte")},
                {WideString(L"case")},
                {WideString(L"catch")},
                {WideString(L"char")},
                {WideString(L"checked")},
                {WideString(L"class")},
                {WideString(L"const")},
                {WideString(L"continue")},
                {WideString(L"decimal")},
                {WideString(L"default")},
                {WideString(L"delegate")},
                {WideString(L"do")},
                {WideString(L"double")},
                {WideString(L"else")},
                {WideString(L"enum")},
                {WideString(L"event")},
                {WideString(L"explicit")},
                {WideString(L"extern")},
                {WideString(L"false")},
                {WideString(L"finally")},
                {WideString(L"fixed")},
                {WideString(L"float")},
                {WideString(L"for")},
                {WideString(L"foreach")},
                {WideString(L"goto")},
                {WideString(L"if")},
                {WideString(L"implicit")},
                {WideString(L"in")},
                {WideString(L"int")},
                {WideString(L"interface")},
                {WideString(L"internal")},
                {WideString(L"is")},
                {WideString(L"lock")},
                {WideString(L"long")},
                {WideString(L"namespace")},
                {WideString(L"new")},
                {WideString(L"null")},
                {WideString(L"object")},
                {WideString(L"operator")},
                {WideString(L"out")},
                {WideString(L"override")},
                {WideString(L"params")},
                {WideString(L"private")},
                {WideString(L"protected")},
                {WideString(L"public")},
                {WideString(L"readonly")},
                {WideString(L"ref")},
                {WideString(L"return")},
                {WideString(L"sbyte")},
                {WideString(L"sealed")},
                {WideString(L"short")},
                {WideString(L"sizeof")},
                {WideString(L"stackalloc")},
                {WideString(L"static")},
                {WideString(L"string")},
                {WideString(L"struct")},
                {WideString(L"switch")},
                {WideString(L"this")},
                {WideString(L"throw")},
                {WideString(L"true")},
                {WideString(L"try")},
                {WideString(L"typeof")},
                {WideString(L"uint")},
                {WideString(L"ulong")},
                {WideString(L"unchecked")},
                {WideString(L"unsafe")},
                {WideString(L"ushort")},
                {WideString(L"using")},
                {WideString(L"virtual")},
                {WideString(L"void")},
                {WideString(L"volatile")},
                {WideString(L"while")},
                {WideString(L"add")},
                {WideString(L"allows")},
                {WideString(L"alias")},
                {WideString(L"and")},
                {WideString(L"ascending")},
                {WideString(L"args")},
                {WideString(L"async")},
                {WideString(L"await")},
                {WideString(L"by")},
                {WideString(L"descending")},
                {WideString(L"dynamic")},
                {WideString(L"equals")},
                {WideString(L"file")},
                {WideString(L"from")},
                {WideString(L"get")},
                {WideString(L"global")},
                {WideString(L"group")},
                {WideString(L"init")},
                {WideString(L"into")},
                {WideString(L"join")},
                {WideString(L"let")},
                {WideString(L"nameof")},
                {WideString(L"nint")},
                {WideString(L"not")},
                {WideString(L"notnull")},
                {WideString(L"nuint")},
                {WideString(L"on")},
                {WideString(L"or")},
                {WideString(L"orderby")},
                {WideString(L"partial")},
                {WideString(L"record")},
                {WideString(L"remove")},
                {WideString(L"required")},
                {WideString(L"scoped")},
                {WideString(L"select")},
                {WideString(L"set")},
                {WideString(L"unmanaged")},
                {WideString(L"value")},
                {WideString(L"var")},
                {WideString(L"when")},
                {WideString(L"where")},
                {WideString(L"with")},
                {WideString(L"yield")}
            };
            return keywords.contains( word );
        }
    }

    WideString CSharpHelper::GetInputArgumentName( const MemberInfo& member )
    {
        auto result = member.Name( ).FirstToLower( );
        if ( IsCSharpKeyword( result ) )
        {
            return Format( L"{}__", result );
        }
        return result;
    }

    WideString CSharpHelper::GetDataTypeBaseClassName( const ClassInfo& classInfo )
    {
        WideString result( L"<Unknown>" );
        if ( classInfo.IsTopLevel( ) )
        {
            auto primaryKey = classInfo.PrimaryKey( );
            if ( primaryKey )
            {
                auto primaryKeyType = primaryKey->Type( );
                switch ( primaryKeyType )
                {
                    case MemberInfoType::Int64:
                        result = L"BaseDataInt64<Kind>";
                        break;
                    case MemberInfoType::Guid:
                        result = L"BaseDataGuid<Kind>";
                        break;
                }
            }
        }
        else
        {
            auto baseClass = classInfo.BaseClass( );
            result = GetDataType( *baseClass );
        }
        return result;
    }

    WideString CSharpHelper::GetDataType( const ClassInfo& classInfo )
    {
        return Format( L"{}Object", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CSharpHelper::GetEntityTypeBaseClassName( const ClassInfo& classInfo )
    {
        WideString result( L"<Unknown>" );
        if ( classInfo.IsTopLevel( ) )
        {
            auto primaryKey = classInfo.PrimaryKey( );
            if ( primaryKey )
            {
                auto primaryKeyType = primaryKey->Type( );
                switch ( primaryKeyType )
                {
                    case MemberInfoType::Int64:
                        result = L"<not implemented>";
                        break;
                    case MemberInfoType::Guid:
                        result = L"BaseEntity<Kind>";
                        break;
                }
            }
        }
        else
        {
            auto baseClass = classInfo.BaseClass( );
            result = GetEntityType( *baseClass );
        }
        return result;
    }
    WideString CSharpHelper::GetEntityType( const ClassInfo& classInfo )
    {
        return Format( L"{}Entity", classInfo.Name( ).FirstToUpper( ) );
    }
    WideString CSharpHelper::GetEntityCollectionType( const ClassInfo& classInfo )
    {
        return Format( L"{}EntityCollection", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CSharpHelper::GetUpdateNode( const ClassInfo& classInfo )
    {
        return Format( L"{}UpdateNode", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CSharpHelper::GetMemberFieldType( const MemberInfo& member )
    {
        WideString result = GetBaseType( member );
        return result;
    }
    WideString CSharpHelper::GetMemberFieldName( const MemberInfo& member )
    {
        return Format( L"_{}", member.Name( ).FirstToLower( ) );
    }

    bool CSharpHelper::MemberFieldRequiresDefaultValue( const MemberInfo& member )
    {
        auto memberType = member.Type( );
        if ( member.Nullable( ) == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::RowVersion || memberType == MemberInfoType::String || memberType == MemberInfoType::Binary ) )
        {
            return true;
        }
        return false;
    }

    WideString CSharpHelper::GetSerializationWriteFunction( const MemberInfo& member )
    {
        WideString result( L"Write" );
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::Binary )
        {
            result = L"WriteArray";
        }
        return result;
    }
    WideString CSharpHelper::GetSerializationReadFunction( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable( ) ? L"ReadNullableBoolean" : L"ReadBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"ReadNullableSByte" : L"ReadSByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"ReadNullableByte" : L"ReadByte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"ReadNullableInt16" : L"ReadInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"ReadNullableUInt16" : L"ReadUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"ReadNullableInt32" : L"ReadInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"ReadNullableUInt32" : L"ReadUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"ReadNullableInt64" : L"ReadInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"ReadNullableUInt64" : L"ReadUInt64";
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
                        result = Format( L"ReadNullableEnum<Types.{}>", enumType->Name( ) );
                    }
                    else
                    {
                        result = Format( L"ReadEnum<Types.{}>", enumType->Name( ) );
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"ReadNullableSingle" : L"ReadSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"ReadNullableDouble" : L"ReadDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"ReadNullableCurrency" : L"ReadCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"ReadNullableDateTime" : L"ReadDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"ReadNullableTimeSpan" : L"ReadTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"ReadNullableGuid" : L"ReadGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = L"ReadString";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"ReadByteArray";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"ReadNullableInt64" : L"ReadInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"ReadNullableGuid" : L"ReadGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"ReadNullableGuid" : L"ReadGuid";
            }
            break;
        }
        return result;
    }

    WideString CSharpHelper::GetSimpleDataReaderName( const ClassInfo& classInfo )
    {
        return Format( L"Simple{}DataReader", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CSharpHelper::GetComplexDataReaderName( const ClassInfo& classInfo )
    {
        return Format( L"Complex{}DataReader", classInfo.Name( ).FirstToUpper( ) );
    }

    WideString CSharpHelper::GetDataReaderName( const ClassInfo& classInfo )
    {
        if ( RequiresComplexReader( classInfo ) )
        {
            return GetComplexDataReaderName( classInfo );
        }
        else
        {
            return GetSimpleDataReaderName( classInfo );
        }
    }

    WideString CSharpHelper::GetDataReaderGetFunctionName( const MemberInfo& member )
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable( ) ? L"GetNullableBoolean" : L"GetBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"GetNullableSByte" : L"GetSByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"GetNullableByte" : L"GetByte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"GetNullableInt16" : L"GetInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"GetNullableUInt16" : L"GetUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"GetNullableInt32" : L"GetInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"GetNullableUInt32" : L"GetUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"GetNullableInt64" : L"GetInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"GetNullableUInt64" : L"GetUInt64";
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
                        result = Format( L"GetNullableEnum<Types.{}>", enumType->Name( ) );
                    }
                    else
                    {
                        result = Format( L"GetEnum<Types.{}>", enumType->Name( ) );
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"GetNullableFloat" : L"GetFloat";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"GetNullableDouble" : L"GetDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"GetNullableInt64" : L"GetInt64";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"GetNullableInt64" : L"GetInt64";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"GetNullableInt64" : L"GetInt64";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"GetNullableGuid" : L"GetGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = member.Nullable( ) ? L"GetNullableString" : L"GetString";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = member.Nullable( ) ? L"GetNullableBytes" : L"GetBytes";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"GetNullableInt64" : L"GetInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"GetNullableGuid" : L"GetGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"GetNullableGuid" : L"GetGuid";
            }
            break;
        }
        return result;
    }


    WideString CSharpHelper::GetDataTypeConstructorArguments( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );
        StringBuilder<wchar_t> sb;

        auto primaryKey = classInfo.PrimaryKey( );
        if ( primaryKey->Type( ) == MemberInfoType::Guid )
        {
            sb.Append( L"ObjectState objectState, Guid id" );
        }
        else if ( primaryKey->Type( ) == MemberInfoType::Int64 )
        {
            sb.Append( L"ObjectState objectState, long id" );
        }

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto argumentType = GetInputArgumentType( member );
                auto argumentName = GetInputArgumentName( member );
                sb.Append( L", {} {}", argumentType, argumentName );
            }
        }
        return sb.ToString( );
    }
    WideString CSharpHelper::GetDataTypeConstructorCallArguments( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );
        StringBuilder<wchar_t> sb;

        sb.Append( L"objectState, id" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto argumentName = GetInputArgumentName( member );
                sb.Append( L", {}", argumentName );
            }
        }
        return sb.ToString( );
    }

    WideString CSharpHelper::GetDataTypeConstructorCallPropertiesArguments( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );
        StringBuilder<wchar_t> sb;

        sb.Append( L"ObjectState.Stored, Id" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto argumentName = member.Name().FirstToUpper( );
                sb.Append( L", {}", argumentName );
            }
        }
        return sb.ToString( );
    }

    WideString CSharpHelper::GetDataTypeConstructorCallComplexReaderPropertiesArguments( const ClassInfo& classInfo, const ClassInfo& derivedOrSelfClassInfo )
    {
        const auto& members = derivedOrSelfClassInfo.PersistentMembers( );
        auto memberCount = members.size( );
        StringBuilder<wchar_t> sb;

        sb.Append( L"ObjectState.Stored, Id" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                
                if ( classInfo.IsViewMember( member ) )
                {
                    auto argumentName = member.Name( ).FirstToUpper( );
                    sb.Append( L", {}", argumentName );
                }
                else
                {
                    auto owner = member.Owner( );
                    auto argumentName = owner->Name( ).FirstToUpper( ) + member.Name( ).FirstToUpper( );
                    sb.Append( L", {}", argumentName );
                }
            }
        }
        return sb.ToString( );
    }
    

    WideString CSharpHelper::GetDataTypeBaseConstructorCallArguments( const ClassInfo& classInfo )
    {
        if ( classInfo.IsTopLevel( ) )
        {
            return WideString(L"objectState, id");
        }
        else
        {
            auto baseClass = classInfo.BaseClass( );
            return GetDataTypeConstructorCallArguments( *baseClass );
        }
    }

    WideString CSharpHelper::GetInsertFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Insert{}", classInfo.Name( ) );
    }
    WideString CSharpHelper::GetInsertFunctionName1( const ClassInfo& classInfo )
    {
        return Format( L"Insert1{}", classInfo.Name( ) );
    }

    WideString CSharpHelper::GetUpdateFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Update{}", classInfo.Name( ) );
    }
    WideString CSharpHelper::GetUpdateFunctionName1( const ClassInfo& classInfo )
    {
        return Format( L"Update1{}", classInfo.Name( ) );
    }
    WideString CSharpHelper::GetUpdateFunctionName2( const ClassInfo& classInfo )
    {
        return Format( L"Update2{}", classInfo.Name( ) );
    }
    WideString CSharpHelper::GetDeleteFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Delete{}", classInfo.Name( ) );
    }

    WideString CSharpHelper::GetInsertFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"ref {} {}", primaryKeyArgumentType, primaryKeyName );


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
    WideString CSharpHelper::GetInsertFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"ref {}", primaryKeyName );

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

    WideString CSharpHelper::GetInsertFunctionParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"ref {} {}", primaryKeyArgumentType, primaryKeyName );


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
    WideString CSharpHelper::GetInsertFunctionCallParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"ref {}", primaryKeyName );

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


    WideString CSharpHelper::GetUpdateFunctionParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{} {}", primaryKeyArgumentType, primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {} {}", variableType, variableName );
                }
                else
                {
                    parameters.Append( L", {} {}", variableType, variableName );
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CSharpHelper::GetUpdateFunctionCallParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto memberType = member.Type( );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {}", variableName );
                }
                else
                {
                    parameters.Append( L", {}", variableName );
                }
            }
        }
        return parameters.ToString( );
    }


    WideString CSharpHelper::GetUpdateFunctionParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{} {}", primaryKeyArgumentType, primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {} {}", variableType, variableName );
                }
                else
                {
                    parameters.Append( L", {} {}", variableType, variableName );
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CSharpHelper::GetUpdateFunctionCallParameters1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto memberType = member.Type( );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {}", variableName );
                }
                else
                {
                    parameters.Append( L", {}", variableName );
                }
            }
        }
        return parameters.ToString( );
    }

    WideString CSharpHelper::GetUpdateFunctionParameters2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{} {}", primaryKeyArgumentType, primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = GetInputArgumentName( member );
                auto variableType = GetInputArgumentType( member );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {} {}", variableType, variableName );
                }
                else
                {
                    parameters.Append( L", {} {}", variableType, variableName );
                }
            }
        }
        return parameters.ToString( );
    }
    WideString CSharpHelper::GetUpdateFunctionCallParameters2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{}", primaryKeyName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto variableName = GetInputArgumentName( member );
                auto memberType = member.Type( );

                if ( memberType == MemberInfoType::RowVersion )
                {
                    parameters.Append( L", ref {}", variableName );
                }
                else
                {
                    parameters.Append( L", {}", variableName );
                }
            }
        }
        return parameters.ToString( );
    }

    WideString CSharpHelper::GetDeleteFunctionParameters( const ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );
        auto primaryKeyArgumentType = GetBaseType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"{} {}", primaryKeyArgumentType, primaryKeyName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionName = GetInputArgumentName( *rowVersion );
            parameters.Append( L", long {}", rowVersionName );
        }
        return parameters.ToString( );
    }
    WideString CSharpHelper::GetDeleteFunctionCallParameters( const ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = GetInputArgumentName( *primaryKey );

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

    WideString CSharpHelper::GetSqlCommandParametersAddFunctionName( const MemberInfo& member )
    {
        WideString result( L"<Unknown>" );
        auto memberType = member.Type( );
        switch ( memberType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"AddBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"AddSByte";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"AddByte";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"AddInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"AddUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"AddInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"AddUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"AddInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"AddUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                result = L"AddEnum";
            }
            break;
            case MemberInfoType::Single:
            {
                result = L"AddSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"AddDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = L"AddCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"AddDateTimeAsInt64";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"AddTimeSpanAsInt64";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"AddGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = L"AddNVarChar";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = L"AddBinary";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"AddInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = L"AddReference";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = L"AddReference";
            }
            break;
        }
        return result;
    }

    WideString CSharpHelper::GetByIdFunctionName( const ClassInfo& classInfo )
    {
        auto result = Format( L"Get{}ById", classInfo.Name() );
        return result;
    }
    WideString CSharpHelper::GetAllFunctionName( const ClassInfo& classInfo )
    {
        auto result = Format( L"Get{}Collection", classInfo.Name( ) );
        return result;
    }
    WideString CSharpHelper::GetByIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        StringBuilder<wchar_t> sb;
        if ( indexMemberCount > 1 )
        {
            for ( size_t i = indexDepth; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                if ( i < ( indexMemberCount - 1) )
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
            sb.Append( indexMembers[0]->Name() );
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

    WideString CSharpHelper::GetByNullableIndexFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
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


    WideString CSharpHelper::GetByIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
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
    WideString CSharpHelper::GetByIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
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

    WideString CSharpHelper::GetByNullableIndexFunctionParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
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
    WideString CSharpHelper::GetByNullableIndexFunctionCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
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

    WideString CSharpHelper::GetByIndexFunctionName( const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        if ( indexMemberCount > ( indexDepth + 1) )
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
    WideString CSharpHelper::GetByIndexAtFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString(L"At"), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CSharpHelper::GetByIndexFromFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"From"), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CSharpHelper::GetByIndexUntilFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"Until"), classInfo, indexInfo, indexDepth, indexMemberCount );
    }
    WideString CSharpHelper::GetByIndexOverFunctionName( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
    {
        return GetByIndexFunctionName( WideString( L"Over" ), classInfo, indexInfo, indexDepth, indexMemberCount );
    }

    WideString CSharpHelper::GetByIndexFunctionOverParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
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

    WideString CSharpHelper::GetByIndexFunctionOverCallParameters( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount )
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


    bool CSharpHelper::IsUnique( const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& indexMembers = indexInfo.Fields( );
        if ( indexInfo.Unique( ) && indexMemberCount == indexMembers.size( ) )
        {
            return true;
        }
        return false;
    }

    bool CSharpHelper::RequiresComplexReader( const ClassInfo& classInfo )
    {
        return classInfo.DerivedClasses( ).size( ) > 0;
    }

    WideString CSharpHelper::GetEntityIndexClassName( const IndexInfo& indexInfo )
    {
        auto owner = indexInfo.Owner( );
        const auto& indexMembers = indexInfo.Fields( );
        auto indexMemberCount = indexMembers.size( );
        StringBuilder<wchar_t> sb;
        sb.Append( L"{}By", owner->Name( ) );
        if ( indexMemberCount > 1 )
        {
            for ( size_t i = 0; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                auto fieldName = indexMember.Name( ).FirstToUpper();
                if ( i < ( indexMemberCount - 1 ) )
                {
                    sb.Append( L"{}", fieldName );
                }
                else
                {
                    sb.Append( L"And{}EntityIndex", fieldName );
                }
            }
        }
        else
        {
            const auto& indexMember = *indexMembers[ 0 ];
            auto fieldName = indexMember.Name( ).FirstToUpper( );
            sb.Append( L"{}EntityIndex", fieldName );
        }
        return sb.ToString( );
    }

    WideString CSharpHelper::GetEntityNullableIndexClassName( const IndexInfo& indexInfo )
    {
        auto owner = indexInfo.Owner( );
        const auto& indexMembers = indexInfo.Fields( );
        auto indexMemberCount = indexMembers.size( );
        StringBuilder<wchar_t> sb;
        sb.Append( L"{}By", owner->Name( ) );
        if ( indexMemberCount > 1 )
        {
            for ( size_t i = 0; i < indexMemberCount; i++ )
            {
                const auto& indexMember = *indexMembers[ i ];
                auto fieldName = indexMember.Name( ).FirstToUpper( );
                if ( i < ( indexMemberCount - 1 ) )
                {
                    if ( indexMember.Nullable( ) )
                    {
                        sb.Append( L"{}IsNull", fieldName );
                    }
                    else
                    {
                        sb.Append( L"{}", fieldName );
                    }
                }
                else
                {
                    if ( indexMember.Nullable( ) )
                    {
                        sb.Append( L"And{}IsNullEntityIndex", fieldName );
                    }
                    else
                    {
                        sb.Append( L"And{}EntityIndex", fieldName );
                    }
                }
            }
        }
        else
        {
            const auto& indexMember = *indexMembers[ 0 ];
            auto fieldName = indexMember.Name( ).FirstToUpper( );
            if ( indexMember.Nullable( ) )
            {
                sb.Append( L"{}IsNullEntityIndex", fieldName );
            }
            else
            {
                sb.Append( L"{}EntityIndex", fieldName );
            }
        }
        return sb.ToString( );
    }



}