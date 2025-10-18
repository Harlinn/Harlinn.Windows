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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Java/JavaHelper.h"

#include "HCCStringBuilder.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    WideString JavaHelper::GetNotNullableBaseType(const MemberInfo& member)
    {
        WideString result(L"<unknown>");
        auto memberInfoType = member.Type();
        switch (memberInfoType)
        {
        case MemberInfoType::Boolean:
        {
            result = L"boolean";
        }
        break;
        case MemberInfoType::SByte:
        {
            result = L"byte";
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
            result = L"short";
        }
        break;
        case MemberInfoType::Int32:
        {
            result = L"int";
        }
        break;
        case MemberInfoType::UInt32:
        {
            result = L"int";
        }
        break;
        case MemberInfoType::Int64:
        {
            result = L"long";
        }
        break;
        case MemberInfoType::UInt64:
        {
            result = L"long";
        }
        break;
        case MemberInfoType::Enum:
        {
            const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>(member);

            auto enumType = enumMemberInfo.EnumType();

            auto valueType = enumType->ValueType( );
            switch ( valueType )
            {
                case MemberInfoType::SByte:
                    result = L"byte";
                    break;
                case MemberInfoType::Byte:
                    result = L"byte";
                    break;
                case MemberInfoType::Int16:
                    result = L"short";
                    break;
                case MemberInfoType::UInt16:
                    result = L"short";
                    break;
                case MemberInfoType::Int32:
                    result = L"int";
                    break;
                case MemberInfoType::UInt32:
                    result = L"int";
                    break;
                case MemberInfoType::Int64:
                    result = L"long";
                    break;
                case MemberInfoType::UInt64:
                    result = L"long";
                    break;
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
            result = L"String";
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

    WideString JavaHelper::GetBaseType(const MemberInfo& member)
    {
        WideString result(L"<unknown>");
        auto memberInfoType = member.Type();
        switch (memberInfoType)
        {
        case MemberInfoType::Boolean:
        {
            result = member.Nullable() ? L"Boolean" : L"boolean";
        }
        break;
        case MemberInfoType::SByte:
        {
            result = member.Nullable() ? L"Byte" : L"byte";
        }
        break;
        case MemberInfoType::Byte:
        {
            result = member.Nullable() ? L"Byte" : L"byte";
        }
        break;
        case MemberInfoType::Int16:
        {
            result = member.Nullable() ? L"Short" : L"short";
        }
        break;
        case MemberInfoType::UInt16:
        {
            result = member.Nullable() ? L"Short" : L"short";
        }
        break;
        case MemberInfoType::Int32:
        {
            result = member.Nullable() ? L"Integer" : L"int";
        }
        break;
        case MemberInfoType::UInt32:
        {
            result = member.Nullable() ? L"Integer" : L"int";
        }
        break;
        case MemberInfoType::Int64:
        {
            result = member.Nullable() ? L"Long" : L"long";
        }
        break;
        case MemberInfoType::UInt64:
        {
            result = member.Nullable() ? L"Long" : L"long";
        }
        break;
        case MemberInfoType::Enum:
        {
            result = JavaHelper::GetUnderlyingType( member );
        }
        break;
        case MemberInfoType::Single:
        {
            result = member.Nullable() ? L"Float" : L"float";
        }
        break;
        case MemberInfoType::Double:
        {
            result = member.Nullable() ? L"Double" : L"double";
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
            result = L"String";
        }
        break;
        case MemberInfoType::Binary:
        {
            result = L"byte[]";
        }
        break;
        case MemberInfoType::RowVersion:
        {
            result = member.Nullable() ? L"Long" : L"long";
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

    WideString JavaHelper::GetDefaultValue(const MemberInfo& member)
    {
        WideString result;
        auto memberInfoType = member.Type();
        switch (memberInfoType)
        {
        case MemberInfoType::Boolean:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"false";
            }
        }
        break;
        case MemberInfoType::SByte:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::Byte:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::Int16:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::UInt16:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::Int32:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::UInt32:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::Int64:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::UInt64:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0";
            }
        }
        break;
        case MemberInfoType::Enum:
        {
            const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>(member);
            auto enumType = enumMemberInfo.EnumType();
            if (enumType)
            {
                auto enumName = enumType->Name();
                auto defaultValue = enumType->Default();
                if (defaultValue)
                {
                    result = Format(L"{}.{}", enumName, defaultValue->Name());
                }
            }
        }
        break;
        case MemberInfoType::Single:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0.0f";
            }
        }
        break;
        case MemberInfoType::Double:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"0.0";
            }
        }
        break;
        case MemberInfoType::Currency:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new Currency()";
            }
        }
        break;
        case MemberInfoType::DateTime:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new DateTime()";
            }
        }
        break;
        case MemberInfoType::TimeSpan:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new TimeSpan()";
            }
        }
        break;
        case MemberInfoType::Guid:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new Guid()";
            }
        }
        break;
        case MemberInfoType::String:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"\"\"";
            }
        }
        break;
        case MemberInfoType::Binary:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new byte[0]";
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
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new Guid()";
            }
        }
        break;
        case MemberInfoType::TimeSeries:
        {
            if (member.Nullable())
            {
                result = L"null";
            }
            else
            {
                result = L"new Guid()";
            }
        }
        break;
        }

        return result;
    }

    WideString JavaHelper::GetUnderlyingType(const EnumInfo& enumInfo)
    {
        WideString result(L"int");
        auto valueType = enumInfo.ValueType();
        switch (valueType)
        {
        case MemberInfoType::SByte:
        {
            result = L"byte";
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
            result = L"short";
        }
        break;
        case MemberInfoType::Int32:
        {
            result = L"int";
        }
        break;
        case MemberInfoType::UInt32:
        {
            result = L"int";
        }
        break;
        case MemberInfoType::Int64:
        {
            result = L"long";
        }
        break;
        case MemberInfoType::UInt64:
        {
            result = L"long";
        }
        break;
        }
        return result;
    }

    WideString JavaHelper::GetUnderlyingType(const MemberInfo& member)
    {
        const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>(member);
        auto enumInfo = enumMemberInfo.EnumType();
        WideString result(L"int");
        auto valueType = enumInfo->ValueType();
        switch (valueType)
        {
            case MemberInfoType::SByte:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Byte";
                }
                else
                {
                    result = L"byte";
                }
            }
            break;
            case MemberInfoType::Byte:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Byte";
                }
                else
                {
                    result = L"byte";
                }
            }
            break;
            case MemberInfoType::Int16:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Short";
                }
                else
                {
                    result = L"short";
                }
            }
            break;
            case MemberInfoType::UInt16:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Short";
                }
                else
                {
                    result = L"short";
                }
            }
            break;
            case MemberInfoType::Int32:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Integer";
                }
                else
                {
                    result = L"int";
                }
            }
            break;
            case MemberInfoType::UInt32:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Integer";
                }
                else
                {
                    result = L"int";
                }
            }
            break;
            case MemberInfoType::Int64:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Long";
                }
                else
                {
                    result = L"long";
                }
            }
            break;
            case MemberInfoType::UInt64:
            {
                if (enumMemberInfo.Nullable())
                {
                    result = L"Long";
                }
                else
                {
                    result = L"long";
                }
            }
            break;
        }
        return result;
    }

    WideString JavaHelper::GetToIntMethodName(const EnumInfo& enumInfo)
    {
        WideString result(L"int");
        auto valueType = enumInfo.ValueType();
        switch (valueType)
        {
            case MemberInfoType::SByte:
            case MemberInfoType::Byte:
            {
                result = L"toByte";
            }
            break;
            
            case MemberInfoType::Int16:
            case MemberInfoType::UInt16:
            {
                result = L"toShort";
            }
            break;
            case MemberInfoType::Int32:
            case MemberInfoType::UInt32:
            {
                result = L"toInt";
            }
            break;
            case MemberInfoType::Int64:
            case MemberInfoType::UInt64:
            {
                result = L"toLong";
            }
            break;
        }
        return result;
    }

    WideString JavaHelper::GetEquals( const MemberInfo& member, const WideString& first, const WideString& second )
    {
        WideString memberFunction;
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableBoolean" : L"equalsBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableInt8" : L"equalsInt8";
            }
            break;
            case MemberInfoType::Byte:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableUInt8" : L"equalsUInt8";
            }
            break;
            case MemberInfoType::Int16:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableInt16" : L"equalsInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableUInt16" : L"equalsUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableInt32" : L"equalsInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableUInt32" : L"equalsUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableInt64" : L"equalsInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableUInt64" : L"equalsUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto valueType = enumType->ValueType( );
                    switch ( valueType )
                    {
                        case MemberInfoType::SByte:
                            memberFunction = member.Nullable( ) ? L"equalsNullableInt8" : L"equalsInt8";
                            break;
                        case MemberInfoType::Byte:
                            memberFunction = member.Nullable( ) ? L"equalsNullableUInt8" : L"equalsUInt8";
                            break;
                        case MemberInfoType::Int16:
                            memberFunction = member.Nullable( ) ? L"equalsNullableInt16" : L"equalsInt16";
                            break;
                        case MemberInfoType::UInt16:
                            memberFunction = member.Nullable( ) ? L"equalsNullableUInt16" : L"equalsUInt16";
                            break;
                        case MemberInfoType::Int32:
                            memberFunction = member.Nullable( ) ? L"equalsNullableInt32" : L"equalsInt32";
                            break;
                        case MemberInfoType::UInt32:
                            memberFunction = member.Nullable( ) ? L"equalsNullableUInt32" : L"equalsUInt32";
                            break;
                        case MemberInfoType::Int64:
                            memberFunction = member.Nullable( ) ? L"equalsNullableInt64" : L"equalsInt64";
                            break;
                        case MemberInfoType::UInt64:
                            memberFunction = member.Nullable( ) ? L"equalsNullableUInt64" : L"equalsUInt64";
                            break;
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableSingle" : L"equalsSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableDouble" : L"equalsDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableCurrency" : L"equalsCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableDateTime" : L"equalsDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableTimeSpan" : L"equalsTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableGuid" : L"equalsGuid";
            }
            break;
            case MemberInfoType::String:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableString" : L"equalsString";
            }
            break;
            case MemberInfoType::Binary:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableUInt8Array" : L"equalsUInt8Array";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableInt64" : L"equalsInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableGuid" : L"equalsGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                memberFunction = member.Nullable( ) ? L"equalsNullableGuid" : L"equalsGuid";
            }
            break;
        }
        auto result = Format( L"Comparer.{}( {}, {} )", memberFunction, first, second );
        return result;
    }
    WideString JavaHelper::GetCompareTo( const MemberInfo& member, const WideString& first, const WideString& second )
    {
        WideString memberFunction;
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableBoolean" : L"compareBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableInt8" : L"compareInt8";
            }
            break;
            case MemberInfoType::Byte:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableUInt8" : L"compareUInt8";
            }
            break;
            case MemberInfoType::Int16:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableInt16" : L"compareInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableUInt16" : L"compareUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableInt32" : L"compareInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableUInt32" : L"compareUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableInt64" : L"compareInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableUInt64" : L"compareUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto valueType = enumType->ValueType( );
                    switch ( valueType )
                    {
                        case MemberInfoType::SByte:
                            memberFunction = member.Nullable( ) ? L"compareNullableInt8" : L"compareInt8";
                            break;
                        case MemberInfoType::Byte:
                            memberFunction = member.Nullable( ) ? L"compareNullableUInt8" : L"compareUInt8";
                            break;
                        case MemberInfoType::Int16:
                            memberFunction = member.Nullable( ) ? L"compareNullableInt16" : L"compareInt16";
                            break;
                        case MemberInfoType::UInt16:
                            memberFunction = member.Nullable( ) ? L"compareNullableUInt16" : L"compareUInt16";
                            break;
                        case MemberInfoType::Int32:
                            memberFunction = member.Nullable( ) ? L"compareNullableInt32" : L"compareInt32";
                            break;
                        case MemberInfoType::UInt32:
                            memberFunction = member.Nullable( ) ? L"compareNullableUInt32" : L"compareUInt32";
                            break;
                        case MemberInfoType::Int64:
                            memberFunction = member.Nullable( ) ? L"compareNullableInt64" : L"compareInt64";
                            break;
                        case MemberInfoType::UInt64:
                            memberFunction = member.Nullable( ) ? L"compareNullableUInt64" : L"compareUInt64";
                            break;
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableSingle" : L"compareSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableDouble" : L"compareDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableCurrency" : L"compareCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableDateTime" : L"compareDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableTimeSpan" : L"compareTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableGuid" : L"compareGuid";
            }
            break;
            case MemberInfoType::String:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableString" : L"compareString";
            }
            break;
            case MemberInfoType::Binary:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableUInt8Array" : L"compareUInt8Array";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableInt64" : L"compareInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableGuid" : L"compareGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                memberFunction = member.Nullable( ) ? L"compareNullableGuid" : L"compareGuid";
            }
            break;
        }
        auto result = Format(L"Comparer.{}( {}, {} )", memberFunction, first, second );
        return result;
    }
    WideString JavaHelper::GetDeepCopy( const MemberInfo& member, const WideString& source, const WideString& destination )
    {
        auto memberInfoType = member.Type( );
        if ( memberInfoType == MemberInfoType::Binary )
        {
            return Format( L"{} = {} != null ? {}.clone() : {};", destination, source, source, source );
        }
        else
        {
            return Format( L"{} = {}", destination, source );
        }
    }



    WideString JavaHelper::GetInputArgumentType(const MemberInfo& member)
    {
        WideString result = GetBaseType(member);
        return result;
    }

    namespace
    {
        bool IsJavaKeyword(const WideString& word)
        {
            static const std::unordered_set<WideString> keywords =
            {
                {WideString(L"abstract")},
                {WideString(L"assert")},
                {WideString(L"boolean")},
                {WideString(L"break")},
                {WideString(L"byte")},
                {WideString(L"case")},
                {WideString(L"catch")},
                {WideString(L"char")},
                {WideString(L"class")},
                {WideString(L"const")},
                {WideString(L"default")},
                {WideString(L"do")},
                {WideString(L"double")},
                {WideString(L"else")},
                {WideString(L"enum")},
                {WideString(L"extends")},
                {WideString(L"exports")},
                {WideString(L"extends")},
                {WideString(L"false")},
                {WideString(L"final")},
                {WideString(L"float")},
                {WideString(L"for")},
                {WideString(L"goto")},
                {WideString(L"if")},
                {WideString(L"import")},
                {WideString(L"instanceof")},
                {WideString(L"int")},
                {WideString(L"interface")},
                {WideString(L"long")},
                {WideString(L"native")},
                {WideString(L"module")},
                {WideString(L"new")},
                {WideString(L"non-sealed")},
                {WideString(L"null")},
                {WideString(L"open")},
                {WideString(L"opens")},
                {WideString(L"package")},
                {WideString(L"permits")},
                {WideString(L"private")},
                {WideString(L"protected")},
                {WideString(L"provides")},
                {WideString(L"public")},
                {WideString(L"record")},
                {WideString(L"requires")},
                {WideString(L"return")},
                {WideString(L"sealed")},
                {WideString(L"short")},
                {WideString(L"static")},
                {WideString(L"strictfp")},
                {WideString(L"super")},
                {WideString(L"switch")},
                {WideString(L"this")},
                {WideString(L"throw")},
                {WideString(L"throws")},
                {WideString(L"to")},
                {WideString(L"transitive")},
                {WideString(L"transient")},
                {WideString(L"true")},
                {WideString(L"try")},
                {WideString(L"uses")},
                {WideString(L"var")},
                {WideString(L"when")},
                {WideString(L"with")},
                {WideString(L"void")},
                {WideString(L"volatile")},
                {WideString(L"while")},
                {WideString(L"yield")}
            };
            return keywords.contains(word);
        }
    }

    WideString JavaHelper::GetInputArgumentName(const MemberInfo& member)
    {
        auto result = member.Name().FirstToLower();
        if (IsJavaKeyword(result))
        {
            return Format(L"{}__", result);
        }
        return result;
    }

    WideString JavaHelper::GetDataTypeBaseClassName(const ClassInfo& classInfo)
    {
        WideString result(L"<Unknown>");
        if (classInfo.IsTopLevel())
        {
            auto primaryKey = classInfo.PrimaryKey();
            if (primaryKey)
            {
                auto primaryKeyType = primaryKey->Type();
                switch (primaryKeyType)
                {
                case MemberInfoType::Int64:
                    result = L"AbstractDataObjectWithInt64Key";
                    break;
                case MemberInfoType::Guid:
                    result = L"AbstractDataObjectWithGuidKey";
                    break;
                }
            }
        }
        else
        {
            auto baseClass = classInfo.BaseClass();
            result = GetDataType(*baseClass);
        }
        return result;
    }

    WideString JavaHelper::GetDataType(const ClassInfo& classInfo)
    {
        return Format(L"{}Object", classInfo.Name().FirstToUpper());
    }

    WideString JavaHelper::GetEntityTypeBaseClassName(const ClassInfo& classInfo)
    {
        WideString result(L"<Unknown>");
        if (classInfo.IsTopLevel())
        {
            auto primaryKey = classInfo.PrimaryKey();
            if (primaryKey)
            {
                auto primaryKeyType = primaryKey->Type();
                switch (primaryKeyType)
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
            auto baseClass = classInfo.BaseClass();
            result = GetEntityType(*baseClass);
        }
        return result;
    }
    WideString JavaHelper::GetEntityType(const ClassInfo& classInfo)
    {
        return Format(L"{}Entity", classInfo.Name().FirstToUpper());
    }
    WideString JavaHelper::GetEntityCollectionType(const ClassInfo& classInfo)
    {
        return Format(L"{}EntityCollection", classInfo.Name().FirstToUpper());
    }

    WideString JavaHelper::GetUpdateNode(const ClassInfo& classInfo)
    {
        return Format(L"{}UpdateNode", classInfo.Name().FirstToUpper());
    }

    WideString JavaHelper::GetTestDataObjectFactory( )
    {
        return L"TestDataObjectFactory";
    }

    WideString JavaHelper::GetMemberFieldType(const MemberInfo& member)
    {
        WideString result = GetBaseType(member);
        return result;
    }
    WideString JavaHelper::GetMemberFieldName(const MemberInfo& member)
    {
        return Format(L"_{}", member.Name().FirstToLower());
    }

    bool JavaHelper::MemberFieldRequiresDefaultValue(const MemberInfo& member)
    {
        auto memberType = member.Type();
        if (member.Nullable() == false && (memberType <= MemberInfoType::Double || memberType == MemberInfoType::RowVersion || memberType == MemberInfoType::String || memberType == MemberInfoType::Binary))
        {
            return true;
        }
        return false;
    }

    WideString JavaHelper::GetSerializationWriteFunction(const MemberInfo& member)
    {
        WideString result( L"<unknown>" );
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable( ) ? L"writeNullableBoolean" : L"writeBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"writeNullableInt8" : L"writeInt8";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"writeNullableUInt8" : L"writeUInt8";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"writeNullableInt16" : L"writeInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"writeNullableUInt16" : L"writeUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"writeNullableInt32" : L"writeInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"writeNullableUInt32" : L"writeUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"writeNullableInt64" : L"writeInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"writeNullableUInt64" : L"writeUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto valueType = enumType->ValueType( );
                    switch ( valueType )
                    {
                        case MemberInfoType::SByte:
                            result = member.Nullable( ) ? L"writeNullableInt8" : L"writeInt8";
                            break;
                        case MemberInfoType::Byte:
                            result = member.Nullable( ) ? L"writeNullableUInt8" : L"writeUInt8";
                            break;
                        case MemberInfoType::Int16:
                            result = member.Nullable( ) ? L"writeNullableInt16" : L"writeInt16";
                            break;
                        case MemberInfoType::UInt16:
                            result = member.Nullable( ) ? L"writeNullableUInt16" : L"writeUInt16";
                            break;
                        case MemberInfoType::Int32:
                            result = member.Nullable( ) ? L"writeNullableInt32" : L"writeInt32";
                            break;
                        case MemberInfoType::UInt32:
                            result = member.Nullable( ) ? L"writeNullableUInt32" : L"writeUInt32";
                            break;
                        case MemberInfoType::Int64:
                            result = member.Nullable( ) ? L"writeNullableInt64" : L"writeInt64";
                            break;
                        case MemberInfoType::UInt64:
                            result = member.Nullable( ) ? L"writeNullableUInt64" : L"writeUInt64";
                            break;
                    }
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"writeNullableSingle" : L"writeSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"writeNullableDouble" : L"writeDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"writeNullableCurrency" : L"writeCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"writeNullableDateTime" : L"writeDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"writeNullableTimeSpan" : L"writeTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"writeNullableGuid" : L"writeGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = member.Nullable( ) ? L"writeNullableStringUtf8" : L"writeStringUtf8";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = member.Nullable( ) ? L"writeNullableUInt8Array" : L"writeUInt8Array";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"writeNullableInt64" : L"writeInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"writeNullableGuid" : L"writeGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"writeNullableGuid" : L"writeGuid";
            }
            break;
        }
        return result;
    }
    WideString JavaHelper::GetSerializationReadFunction(const MemberInfo& member)
    {
        WideString result(L"<unknown>");
        auto memberInfoType = member.Type();
        switch (memberInfoType)
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable() ? L"readNullableBoolean" : L"readBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable() ? L"readNullableInt8" : L"readInt8";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable() ? L"readNullableUInt8" : L"readUInt8";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable() ? L"readNullableInt16" : L"readInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable() ? L"readNullableUInt16" : L"readUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable() ? L"readNullableInt32" : L"readInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable() ? L"readNullableUInt32" : L"readUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable() ? L"readNullableInt64" : L"readInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable() ? L"readNullableUInt64" : L"readUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>(member);
                auto enumType = enumMemberInfo.EnumType();

                auto valueType = enumType->ValueType( );
                switch ( valueType )
                {
                    case MemberInfoType::SByte:
                        result = member.Nullable( ) ? L"readNullableInt8" : L"readInt8";
                        break;
                    case MemberInfoType::Byte:
                        result = member.Nullable( ) ? L"readNullableUInt8" : L"readUInt8";
                        break;
                    case MemberInfoType::Int16:
                        result = member.Nullable( ) ? L"readNullableInt16" : L"readInt16";
                        break;
                    case MemberInfoType::UInt16:
                        result = member.Nullable( ) ? L"readNullableUInt16" : L"readUInt16";
                        break;
                    case MemberInfoType::Int32:
                        result = member.Nullable( ) ? L"readNullableInt32" : L"readInt32";
                        break;
                    case MemberInfoType::UInt32:
                        result = member.Nullable( ) ? L"readNullableUInt32" : L"readUInt32";
                        break;
                    case MemberInfoType::Int64:
                        result = member.Nullable( ) ? L"readNullableInt64" : L"readInt64";
                        break;
                    case MemberInfoType::UInt64:
                        result = member.Nullable( ) ? L"readNullableUInt64" : L"readUInt64";
                        break;
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable() ? L"readNullableSingle" : L"readSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable() ? L"readNullableDouble" : L"readDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable() ? L"readNullableCurrency" : L"readCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable() ? L"readNullableDateTime" : L"readDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable() ? L"readNullableTimeSpan" : L"readTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable() ? L"readNullableGuid" : L"readGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = member.Nullable( ) ? L"readNullableString" : L"readString";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = member.Nullable( ) ? L"readNullableUInt8Array" : L"readUInt8Array";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable() ? L"readNullableInt64" : L"readInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable() ? L"readNullableGuid" : L"readGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable() ? L"readNullableGuid" : L"readGuid";
            }
            break;
        }
        return result;
    }

    WideString JavaHelper::GetSimpleDataReaderName(const ClassInfo& classInfo)
    {
        return Format(L"Simple{}DataReader", classInfo.Name().FirstToUpper());
    }

    WideString JavaHelper::GetComplexDataReaderName(const ClassInfo& classInfo)
    {
        return Format(L"Complex{}DataReader", classInfo.Name().FirstToUpper());
    }

    WideString JavaHelper::GetDataReaderName(const ClassInfo& classInfo)
    {
        if (RequiresComplexReader(classInfo))
        {
            return GetComplexDataReaderName(classInfo);
        }
        else
        {
            return GetSimpleDataReaderName(classInfo);
        }
    }

    WideString JavaHelper::GetDataReaderGetFunctionName(const MemberInfo& member)
    {
        WideString result(L"<unknown>");
        auto memberInfoType = member.Type();
        switch (memberInfoType)
        {
        case MemberInfoType::Boolean:
        {
            result = member.Nullable() ? L"getNullableBoolean" : L"getBoolean";
        }
        break;
        case MemberInfoType::SByte:
        {
            result = member.Nullable() ? L"getNullableInt8" : L"getInt8";
        }
        break;
        case MemberInfoType::Byte:
        {
            result = member.Nullable() ? L"getNullableUInt8" : L"getUInt8";
        }
        break;
        case MemberInfoType::Int16:
        {
            result = member.Nullable() ? L"getNullableInt16" : L"getInt16";
        }
        break;
        case MemberInfoType::UInt16:
        {
            result = member.Nullable() ? L"getNullableUInt16" : L"getUInt16";
        }
        break;
        case MemberInfoType::Int32:
        {
            result = member.Nullable() ? L"getNullableInt32" : L"getInt32";
        }
        break;
        case MemberInfoType::UInt32:
        {
            result = member.Nullable() ? L"getNullableUInt32" : L"getUInt32";
        }
        break;
        case MemberInfoType::Int64:
        {
            result = member.Nullable() ? L"getNullableInt64" : L"getInt64";
        }
        break;
        case MemberInfoType::UInt64:
        {
            result = member.Nullable() ? L"getNullableUInt64" : L"getUInt64";
        }
        break;
        case MemberInfoType::Enum:
        {
            const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>( member );
            auto enumType = enumMemberInfo.EnumType( );

            auto valueType = enumType->ValueType( );
            switch ( valueType )
            {
                case MemberInfoType::SByte:
                    result = member.Nullable( ) ? L"getNullableInt8" : L"getInt8";
                    break;
                case MemberInfoType::Byte:
                    result = member.Nullable( ) ? L"getNullableUInt8" : L"getUInt8";
                    break;
                case MemberInfoType::Int16:
                    result = member.Nullable( ) ? L"getNullableInt16" : L"getInt16";
                    break;
                case MemberInfoType::UInt16:
                    result = member.Nullable( ) ? L"getNullableUInt16" : L"getUInt16";
                    break;
                case MemberInfoType::Int32:
                    result = member.Nullable( ) ? L"getNullableInt32" : L"getInt32";
                    break;
                case MemberInfoType::UInt32:
                    result = member.Nullable( ) ? L"getNullableUInt32" : L"getUInt32";
                    break;
                case MemberInfoType::Int64:
                    result = member.Nullable( ) ? L"getNullableInt64" : L"getInt64";
                    break;
                case MemberInfoType::UInt64:
                    result = member.Nullable( ) ? L"getNullableUInt64" : L"getUInt64";
                    break;
            }
        }
        break;
        case MemberInfoType::Single:
        {
            result = member.Nullable() ? L"getNullableSingle" : L"getSingle";
        }
        break;
        case MemberInfoType::Double:
        {
            result = member.Nullable() ? L"getNullableDouble" : L"getDouble";
        }
        break;
        case MemberInfoType::Currency:
        {
            result = member.Nullable() ? L"getNullableCurrency" : L"getCurrency";
        }
        break;
        case MemberInfoType::DateTime:
        {
            result = member.Nullable() ? L"getNullableDateTimeFromLong" : L"getDateTimeFromLong";
        }
        break;
        case MemberInfoType::TimeSpan:
        {
            result = member.Nullable() ? L"getNullableTimeSpan" : L"getTimeSpan";
        }
        break;
        case MemberInfoType::Guid:
        {
            result = member.Nullable() ? L"getNullableGuid" : L"getGuid";
        }
        break;
        case MemberInfoType::String:
        {
            result = member.Nullable() ? L"getNullableString" : L"getString";
        }
        break;
        case MemberInfoType::Binary:
        {
            result = member.Nullable() ? L"getNullableBinary" : L"getBinary";
        }
        break;
        case MemberInfoType::RowVersion:
        {
            result = member.Nullable() ? L"getNullableInt64" : L"getInt64";
        }
        break;
        case MemberInfoType::Reference:
        {
            result = member.Nullable() ? L"getNullableGuid" : L"getGuid";
        }
        break;
        case MemberInfoType::TimeSeries:
        {
            result = member.Nullable() ? L"getNullableGuid" : L"getGuid";
        }
        break;
        }
        return result;
    }


    WideString JavaHelper::GetDataTypeConstructorArguments(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        auto memberCount = members.size();
        StringBuilder<wchar_t> sb;

        auto primaryKey = classInfo.PrimaryKey();
        if (primaryKey->Type() == MemberInfoType::Guid)
        {
            sb.Append(L"byte objectState, Guid id");
        }
        else if (primaryKey->Type() == MemberInfoType::Int64)
        {
            sb.Append(L"byte objectState, long id");
        }

        for (size_t i = 0; i < memberCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto argumentType = GetInputArgumentType(member);
                auto argumentName = GetInputArgumentName(member);
                sb.Append(L", {} {}", argumentType, argumentName);
            }
        }
        return sb.ToString();
    }
    WideString JavaHelper::GetDataTypeConstructorCallArguments(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        auto memberCount = members.size();
        StringBuilder<wchar_t> sb;

        sb.Append(L"objectState, id");

        for (size_t i = 0; i < memberCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto argumentName = GetInputArgumentName(member);
                sb.Append(L", {}", argumentName);
            }
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetDataTypeConstructorCallPropertiesArguments(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        auto memberCount = members.size();
        StringBuilder<wchar_t> sb;

        sb.Append(L"ObjectState.Stored, Id");

        for (size_t i = 0; i < memberCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto argumentName = member.Name().FirstToUpper();
                sb.Append(L", {}", argumentName);
            }
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetDataTypeConstructorCallComplexReaderPropertiesArguments(const ClassInfo& classInfo, const ClassInfo& derivedOrSelfClassInfo)
    {
        const auto& members = derivedOrSelfClassInfo.PersistentMembers();
        auto memberCount = members.size();
        StringBuilder<wchar_t> sb;

        sb.Append(L"ObjectState.Stored, Id");

        for (size_t i = 0; i < memberCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {

                if (classInfo.IsViewMember(member))
                {
                    auto argumentName = member.Name().FirstToUpper();
                    sb.Append(L", {}", argumentName);
                }
                else
                {
                    auto owner = member.Owner();
                    auto argumentName = owner->Name().FirstToUpper() + member.Name().FirstToUpper();
                    sb.Append(L", {}", argumentName);
                }
            }
        }
        return sb.ToString();
    }


    WideString JavaHelper::GetDataTypeBaseConstructorCallArguments(const ClassInfo& classInfo)
    {
        if (classInfo.IsTopLevel())
        {
            return WideString(L"objectState, id");
        }
        else
        {
            auto baseClass = classInfo.BaseClass();
            return GetDataTypeConstructorCallArguments(*baseClass);
        }
    }

    WideString JavaHelper::GetInsertFunctionName(const ClassInfo& classInfo)
    {
        return Format(L"insert{}", classInfo.Name());
    }
    WideString JavaHelper::GetInsertFunctionName1(const ClassInfo& classInfo)
    {
        return Format(L"insert1{}", classInfo.Name());
    }

    WideString JavaHelper::GetUpdateFunctionName(const ClassInfo& classInfo)
    {
        return Format(L"update{}", classInfo.Name());
    }
    WideString JavaHelper::GetUpdateFunctionName1(const ClassInfo& classInfo)
    {
        return Format(L"update1{}", classInfo.Name());
    }
    WideString JavaHelper::GetUpdateFunctionName2(const ClassInfo& classInfo)
    {
        return Format(L"update2{}", classInfo.Name());
    }
    WideString JavaHelper::GetDeleteFunctionName(const ClassInfo& classInfo)
    {
        return Format(L"delete{}", classInfo.Name());
    }

    WideString JavaHelper::GetInsertFunctionParameters(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);


        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                if (memberType != MemberInfoType::RowVersion)
                {
                    auto variableName = GetInputArgumentName(member);
                    auto variableType = GetInputArgumentType(member);

                    parameters.Append(L", {} {}", variableType, variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetInsertFunctionParameterPlaceholders( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> placeholders;

        placeholders.Append( L"?" );


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    placeholders.Append( L", ?" );
                }
            }
        }
        return placeholders.ToString( );
    }

    WideString JavaHelper::GetInsertFunctionCallParameters(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                if (memberType != MemberInfoType::RowVersion)
                {
                    auto variableName = GetInputArgumentName(member);
                    auto variableType = GetInputArgumentType(member);

                    parameters.Append(L", {}", variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetInsertFunctionParameters1(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);


        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                if (memberType != MemberInfoType::RowVersion)
                {
                    auto variableName = GetInputArgumentName(member);
                    auto variableType = GetInputArgumentType(member);

                    parameters.Append(L", {} {}", variableType, variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetInsertFunctionParameterPlaceholders1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> placeholders;

        placeholders.Append( L"?" );


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    placeholders.Append( L", ?" );
                }
            }
        }
        return placeholders.ToString( );
    }

    WideString JavaHelper::GetInsertFunctionCallParameters1(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                if (memberType != MemberInfoType::RowVersion)
                {
                    auto variableName = GetInputArgumentName(member);
                    auto variableType = GetInputArgumentType(member);

                    parameters.Append(L", {}", variableName);
                }
            }
        }
        return parameters.ToString();
    }


    WideString JavaHelper::GetUpdateFunctionParameters(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                auto variableName = GetInputArgumentName(member);
                auto variableType = GetInputArgumentType(member);

                if (memberType == MemberInfoType::RowVersion)
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
                else
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetUpdateFunctionParameterPlaceholders( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"?" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameters.Append( L", ?" );
            }
        }
        return parameters.ToString( );
    }

    WideString JavaHelper::GetUpdateFunctionCallParameters(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembers();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto variableName = GetInputArgumentName(member);
                parameters.Append( L", {}", variableName );
            }
        }
        return parameters.ToString();
    }

    


    WideString JavaHelper::GetUpdateFunctionParameters1(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                auto variableName = GetInputArgumentName(member);
                auto variableType = GetInputArgumentType(member);

                if (memberType == MemberInfoType::RowVersion)
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
                else
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetUpdateFunctionParameterPlaceholders1( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"?" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameters.Append( L", ?" );
            }
        }
        return parameters.ToString( );
    }

    WideString JavaHelper::GetUpdateFunctionCallParameters1(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.PersistentMembersExceptNullableReferences();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto variableName = GetInputArgumentName(member);
                auto memberType = member.Type();

                if (memberType == MemberInfoType::RowVersion)
                {
                    parameters.Append(L", {}", variableName);
                }
                else
                {
                    parameters.Append(L", {}", variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetUpdateFunctionParameters2(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.Update2Members();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto memberType = member.Type();
                auto variableName = GetInputArgumentName(member);
                auto variableType = GetInputArgumentType(member);

                if (memberType == MemberInfoType::RowVersion)
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
                else
                {
                    parameters.Append(L", {} {}", variableType, variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetUpdateFunctionParameterPlaceholders2( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.Update2Members( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"?" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameters.Append( L", ?" );
            }
        }
        return parameters.ToString( );
    }


    WideString JavaHelper::GetUpdateFunctionCallParameters2(const ClassInfo& classInfo)
    {
        const auto& members = classInfo.Update2Members();
        size_t membersCount = members.size();
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);

        for (size_t i = 0; i < membersCount; i++)
        {
            const auto& member = *members[i];
            if (member.PrimaryKey() == false)
            {
                auto variableName = GetInputArgumentName(member);
                auto memberType = member.Type();

                if (memberType == MemberInfoType::RowVersion)
                {
                    parameters.Append(L", {}", variableName);
                }
                else
                {
                    parameters.Append(L", {}", variableName);
                }
            }
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetDeleteFunctionParameters(const ClassInfo& classInfo)
    {
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);
        auto primaryKeyArgumentType = GetBaseType(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{} {}", primaryKeyArgumentType, primaryKeyName);
        auto rowVersion = classInfo.RowVersion();
        if (rowVersion)
        {
            auto rowVersionName = GetInputArgumentName(*rowVersion);
            parameters.Append(L", long {}", rowVersionName);
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetDeleteFunctionParameterPlaceholders( const ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> parameters;

        parameters.Append( L"?" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            parameters.Append( L", ?" );
        }
        return parameters.ToString( );
    }

    WideString JavaHelper::GetDeleteFunctionCallParameters(const ClassInfo& classInfo)
    {
        auto primaryKey = classInfo.PrimaryKey();
        auto primaryKeyName = GetInputArgumentName(*primaryKey);

        StringBuilder<wchar_t> parameters;

        parameters.Append(L"{}", primaryKeyName);
        auto rowVersion = classInfo.RowVersion();
        if (rowVersion)
        {
            auto rowVersionName = GetInputArgumentName(*rowVersion);
            parameters.Append(L", {}", rowVersionName);
        }
        return parameters.ToString();
    }

    WideString JavaHelper::GetSqlCommandParametersAddFunctionName(const MemberInfo& member)
    {
        WideString result(L"<Unknown>");
        auto memberType = member.Type();
        switch (memberType)
        {
            case MemberInfoType::Boolean:
            {
                result = member.Nullable()? L"setNullableBoolean" : L"setBoolean";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = member.Nullable( ) ? L"setNullableInt8" : L"setInt8";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = member.Nullable( ) ? L"setNullableUInt8" : L"setUInt8";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = member.Nullable( ) ? L"setNullableInt16" : L"setInt16";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = member.Nullable( ) ? L"setNullableUInt16" : L"setUInt16";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = member.Nullable( ) ? L"setNullableInt32" : L"setInt32";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = member.Nullable( ) ? L"setNullableUInt32" : L"setUInt32";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = member.Nullable( ) ? L"setNullableInt64" : L"setInt64";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = member.Nullable( ) ? L"setNullableUInt64" : L"setUInt64";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast<const EnumMemberInfo&>( member );
                auto enumType = enumMemberInfo.EnumType( );

                auto valueType = enumType->ValueType( );
                switch ( valueType )
                {
                    case MemberInfoType::SByte:
                        result = member.Nullable( ) ? L"setNullableInt8" : L"setInt8";
                        break;
                    case MemberInfoType::Byte:
                        result = member.Nullable( ) ? L"setNullableUInt8" : L"setUInt8";
                        break;
                    case MemberInfoType::Int16:
                        result = member.Nullable( ) ? L"setNullableInt16" : L"setInt16";
                        break;
                    case MemberInfoType::UInt16:
                        result = member.Nullable( ) ? L"setNullableUInt16" : L"setUInt16";
                        break;
                    case MemberInfoType::Int32:
                        result = member.Nullable( ) ? L"setNullableInt32" : L"setInt32";
                        break;
                    case MemberInfoType::UInt32:
                        result = member.Nullable( ) ? L"setNullableUInt32" : L"setUInt32";
                        break;
                    case MemberInfoType::Int64:
                        result = member.Nullable( ) ? L"setNullableInt64" : L"setInt64";
                        break;
                    case MemberInfoType::UInt64:
                        result = member.Nullable( ) ? L"setNullableUInt64" : L"setUInt64";
                        break;
                }
            }
            break;
            case MemberInfoType::Single:
            {
                result = member.Nullable( ) ? L"setNullableSingle" : L"setSingle";
            }
            break;
            case MemberInfoType::Double:
            {
                result = member.Nullable( ) ? L"setNullableDouble" : L"setDouble";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = member.Nullable( ) ? L"setNullableCurrency" : L"setCurrency";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = member.Nullable( ) ? L"setLongFromNullableDateTime" : L"setLongFromDateTime";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = member.Nullable( ) ? L"setNullableTimeSpan" : L"setTimeSpan";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = member.Nullable( ) ? L"setNullableGuid" : L"setGuid";
            }
            break;
            case MemberInfoType::String:
            {
                result = member.Nullable( ) ? L"setNullableString" : L"setString";
            }
            break;
            case MemberInfoType::Binary:
            {
                result = member.Nullable( ) ? L"setNullableBinary" : L"setBinary";
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = member.Nullable( ) ? L"setNullableInt64" : L"setInt64";
            }
            break;
            case MemberInfoType::Reference:
            {
                result = member.Nullable( ) ? L"setNullableGuid" : L"setGuid";
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                result = member.Nullable( ) ? L"setNullableGuid" : L"setGuid";
            }
            break;
        }
        return result;
    }

    WideString JavaHelper::GetByIdFunctionName(const ClassInfo& classInfo)
    {
        auto result = Format(L"get{}ById", classInfo.Name());
        return result;
    }
    WideString JavaHelper::GetAllFunctionName(const ClassInfo& classInfo)
    {
        auto result = Format(L"get{}Collection", classInfo.Name());
        return result;
    }
    WideString JavaHelper::GetByIndexFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        if (indexMemberCount > 1)
        {
            for (size_t i = indexDepth; i < indexMemberCount; i++)
            {
                const auto& indexMember = *indexMembers[i];
                if (i < (indexMemberCount - 1))
                {
                    sb.Append(indexMember.Name());
                }
                else
                {
                    auto s = Format(L"And{}", indexMember.Name());
                    sb.Append(s);
                }
            }
        }
        else
        {
            sb.Append(indexMembers[0]->Name());
        }
        if (indexInfo.Unique() && indexMemberCount == indexMembers.size())
        {
            auto result = Format(L"get{}By{}", classInfo.Name(), sb.ToString());
            return result;
        }
        else
        {
            auto result = Format(L"get{}CollectionBy{}", classInfo.Name(), sb.ToString());
            return result;
        }
    }

    WideString JavaHelper::GetByNullableIndexFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        if (indexMemberCount > 1)
        {
            for (size_t i = 0; i < indexMemberCount; i++)
            {
                const auto& indexMember = *indexMembers[i];
                if (i < (indexMemberCount - 1))
                {
                    if (indexMember.Nullable())
                    {
                        sb.Append(indexMember.Name() + L"IsNull");
                    }
                    else
                    {
                        sb.Append(indexMember.Name());
                    }
                }
                else
                {
                    if (indexMember.Nullable())
                    {
                        auto s = Format(L"And{}IsNull", indexMember.Name());
                        sb.Append(s);
                    }
                    else
                    {
                        auto s = Format(L"And{}", indexMember.Name());
                        sb.Append(s);
                    }
                }
            }
        }
        else
        {
            if (indexMembers[0]->Nullable())
            {
                sb.Append(indexMembers[0]->Name() + L"IsNull");
            }
            else
            {
                sb.Append(indexMembers[0]->Name());
            }
        }
        auto result = Format(L"qet{}CollectionBy{}", classInfo.Name(), sb.ToString());
        return result;
    }


    WideString JavaHelper::GetByIndexFunctionParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        for (size_t i = 0; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterType = GetInputArgumentType(indexMember);
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{} {}, ", parameterType, parameterName);
            }
            else
            {
                sb.Append(L"{} {}", parameterType, parameterName);
            }
        }
        return sb.ToString();
    }
    WideString JavaHelper::GetByIndexFunctionCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        for (size_t i = 0; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{}, ", parameterName);
            }
            else
            {
                sb.Append(L"{}", parameterName);
            }
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetByNullableIndexFunctionParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        auto indexMembers = indexInfo.RequiredFields(indexMemberCount);
        indexMemberCount--;
        StringBuilder<wchar_t> sb;
        for (size_t i = 0; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterType = GetInputArgumentType(indexMember);
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{} {}, ", parameterType, parameterName);
            }
            else
            {
                sb.Append(L"{} {}", parameterType, parameterName);
            }
        }
        return sb.ToString();
    }
    WideString JavaHelper::GetByNullableIndexFunctionCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        auto indexMembers = indexInfo.RequiredFields(indexMemberCount);
        indexMemberCount--;
        StringBuilder<wchar_t> sb;
        for (size_t i = 0; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{}, ", parameterName);
            }
            else
            {
                sb.Append(L"{}", parameterName);
            }
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetByIndexFunctionName(const WideString& lastFieldPrefix, const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        if (indexMemberCount > (indexDepth + 1))
        {
            StringBuilder<wchar_t> sb;
            for (size_t i = indexDepth; i < indexMemberCount; i++)
            {
                const auto& indexMember = *indexMembers[i];
                if (i < (indexMemberCount - 1))
                {
                    sb.Append(indexMember.Name());
                }
                else
                {
                    auto s = Format(L"{}{}", lastFieldPrefix, indexMember.Name());
                    sb.Append(s);
                }
            }
            if (indexInfo.Unique() && indexMemberCount == indexMembers.size())
            {
                auto result = Format(L"get{}By{}", classInfo.Name(), sb.ToString());
                return result;
            }
            else
            {
                auto result = Format(L"get{}CollectionBy{}", classInfo.Name(), sb.ToString());
                return result;
            }
        }
        else
        {
            if (indexInfo.Unique() && indexMemberCount == indexMembers.size())
            {
                auto result = Format(L"get{}{}{}", classInfo.Name(), lastFieldPrefix, indexMembers[0]->Name());
                return result;
            }
            else
            {
                auto result = Format(L"get{}Collection{}{}", classInfo.Name(), lastFieldPrefix, indexMembers[0]->Name());
                return result;
            }
        }
    }
    WideString JavaHelper::GetByIndexAtFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        return GetByIndexFunctionName(WideString(L"At"), classInfo, indexInfo, indexDepth, indexMemberCount);
    }
    WideString JavaHelper::GetByIndexFromFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        return GetByIndexFunctionName(WideString(L"From"), classInfo, indexInfo, indexDepth, indexMemberCount);
    }
    WideString JavaHelper::GetByIndexUntilFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        return GetByIndexFunctionName(WideString(L"Until"), classInfo, indexInfo, indexDepth, indexMemberCount);
    }
    WideString JavaHelper::GetByIndexOverFunctionName(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        return GetByIndexFunctionName(WideString(L"Over"), classInfo, indexInfo, indexDepth, indexMemberCount);
    }

    WideString JavaHelper::GetByIndexFunctionOverParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        for (size_t i = indexDepth; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterType = GetNotNullableBaseType(indexMember);
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{} {}, ", parameterType, parameterName);
            }
            else
            {
                parameterName = parameterName.FirstToUpper();
                sb.Append(L"{} from{}, ", parameterType, parameterName);
                sb.Append(L"{} until{}", parameterType, parameterName);
            }
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetByIndexFunctionOverCallParameters(const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexDepth, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        StringBuilder<wchar_t> sb;
        for (size_t i = indexDepth; i < indexMemberCount; i++)
        {
            const auto& indexMember = *indexMembers[i];
            auto parameterName = GetInputArgumentName(indexMember);
            if (i < (indexMemberCount - 1))
            {
                sb.Append(L"{}, ", parameterName);
            }
            else
            {
                parameterName = parameterName.FirstToUpper();
                sb.Append(L"from{}, ", parameterName);
                sb.Append(L"until{}", parameterName);
            }
        }
        return sb.ToString();
    }


    bool JavaHelper::IsUnique(const IndexInfo& indexInfo, size_t indexMemberCount)
    {
        const auto& indexMembers = indexInfo.Fields();
        if (indexInfo.Unique() && indexMemberCount == indexMembers.size())
        {
            return true;
        }
        return false;
    }

    bool JavaHelper::RequiresComplexReader(const ClassInfo& classInfo)
    {
        return classInfo.DerivedClasses().size() > 0;
    }

    WideString JavaHelper::GetEntityIndexClassName(const IndexInfo& indexInfo)
    {
        auto owner = indexInfo.Owner();
        const auto& indexMembers = indexInfo.Fields();
        auto indexMemberCount = indexMembers.size();
        StringBuilder<wchar_t> sb;
        sb.Append(L"{}By", owner->Name());
        if (indexMemberCount > 1)
        {
            for (size_t i = 0; i < indexMemberCount; i++)
            {
                const auto& indexMember = *indexMembers[i];
                auto fieldName = indexMember.Name().FirstToUpper();
                if (i < (indexMemberCount - 1))
                {
                    sb.Append(L"{}", fieldName);
                }
                else
                {
                    sb.Append(L"And{}EntityIndex", fieldName);
                }
            }
        }
        else
        {
            const auto& indexMember = *indexMembers[0];
            auto fieldName = indexMember.Name().FirstToUpper();
            sb.Append(L"{}EntityIndex", fieldName);
        }
        return sb.ToString();
    }

    WideString JavaHelper::GetEntityNullableIndexClassName(const IndexInfo& indexInfo)
    {
        auto owner = indexInfo.Owner();
        const auto& indexMembers = indexInfo.Fields();
        auto indexMemberCount = indexMembers.size();
        StringBuilder<wchar_t> sb;
        sb.Append(L"{}By", owner->Name());
        if (indexMemberCount > 1)
        {
            for (size_t i = 0; i < indexMemberCount; i++)
            {
                const auto& indexMember = *indexMembers[i];
                auto fieldName = indexMember.Name().FirstToUpper();
                if (i < (indexMemberCount - 1))
                {
                    if (indexMember.Nullable())
                    {
                        sb.Append(L"{}IsNull", fieldName);
                    }
                    else
                    {
                        sb.Append(L"{}", fieldName);
                    }
                }
                else
                {
                    if (indexMember.Nullable())
                    {
                        sb.Append(L"And{}IsNullEntityIndex", fieldName);
                    }
                    else
                    {
                        sb.Append(L"And{}EntityIndex", fieldName);
                    }
                }
            }
        }
        else
        {
            const auto& indexMember = *indexMembers[0];
            auto fieldName = indexMember.Name().FirstToUpper();
            if (indexMember.Nullable())
            {
                sb.Append(L"{}IsNullEntityIndex", fieldName);
            }
            else
            {
                sb.Append(L"{}EntityIndex", fieldName);
            }
        }
        return sb.ToString();
    }



}