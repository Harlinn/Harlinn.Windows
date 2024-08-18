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
    WideString CppHelper::GetColumnType( const MemberInfo& member )
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
                    result = enumType->Name( );
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
}