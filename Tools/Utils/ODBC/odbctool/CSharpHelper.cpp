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

#include "Generator.h"
#include "SqlServerHelper.h"
#include "CSharpHelper.h"
#include "HCCStringBuilder.h"

namespace Harlinn::ODBC::Tool
{
    WideString CSharpHelper::GetBaseType( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
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
                {L"abstract"},
                {L"as"},
                {L"base"},
                {L"bool"},
                {L"break"},
                {L"byte"},
                {L"case"},
                {L"catch"},
                {L"char"},
                {L"checked"},
                {L"class"},
                {L"const"},
                {L"continue"},
                {L"decimal"},
                {L"default"},
                {L"delegate"},
                {L"do"},
                {L"double"},
                {L"else"},
                {L"enum"},
                {L"event"},
                {L"explicit"},
                {L"extern"},
                {L"false"},
                {L"finally"},
                {L"fixed"},
                {L"float"},
                {L"for"},
                {L"foreach"},
                {L"goto"},
                {L"if"},
                {L"implicit"},
                {L"in"},
                {L"int"},
                {L"interface"},
                {L"internal"},
                {L"is"},
                {L"lock"},
                {L"long"},
                {L"namespace"},
                {L"new"},
                {L"null"},
                {L"object"},
                {L"operator"},
                {L"out"},
                {L"override"},
                {L"params"},
                {L"private"},
                {L"protected"},
                {L"public"},
                {L"readonly"},
                {L"ref"},
                {L"return"},
                {L"sbyte"},
                {L"sealed"},
                {L"short"},
                {L"sizeof"},
                {L"stackalloc"},
                {L"static"},
                {L"string"},
                {L"struct"},
                {L"switch"},
                {L"this"},
                {L"throw"},
                {L"true"},
                {L"try"},
                {L"typeof"},
                {L"uint"},
                {L"ulong"},
                {L"unchecked"},
                {L"unsafe"},
                {L"ushort"},
                {L"using"},
                {L"virtual"},
                {L"void"},
                {L"volatile"},
                {L"while"},
                {L"add"},
                {L"allows"},
                {L"alias"},
                {L"and"},
                {L"ascending"},
                {L"args"},
                {L"async"},
                {L"await"},
                {L"by"},
                {L"descending"},
                {L"dynamic"},
                {L"equals"},
                {L"file"},
                {L"from"},
                {L"get"},
                {L"global"},
                {L"group"},
                {L"init"},
                {L"into"},
                {L"join"},
                {L"let"},
                {L"nameof"},
                {L"nint"},
                {L"not"},
                {L"notnull"},
                {L"nuint"},
                {L"on"},
                {L"or"},
                {L"orderby"},
                {L"partial"},
                {L"record"},
                {L"remove"},
                {L"required"},
                {L"scoped"},
                {L"select"},
                {L"set"},
                {L"unmanaged"},
                {L"value"},
                {L"var"},
                {L"when"},
                {L"where"},
                {L"with"},
                { L"yield"}
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
        WideString result = L"<Unknown>";
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
        WideString result = L"Write";
        auto memberType = member.Type( );
        if ( memberType == MemberInfoType::Binary )
        {
            result = L"WriteArray";
        }
        return result;
    }
    WideString CSharpHelper::GetSerializationReadFunction( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
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

    WideString CSharpHelper::GetDataReaderGetFunctionName( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
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
    

    WideString CSharpHelper::GetDataTypeBaseConstructorCallArguments( const ClassInfo& classInfo )
    {
        if ( classInfo.IsTopLevel( ) )
        {
            return L"objectState, id";
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
    WideString CSharpHelper::GetUpdateFunctionName( const ClassInfo& classInfo )
    {
        return Format( L"Update{}", classInfo.Name( ) );
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
        WideString result = L"<Unknown>";
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

}