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

#include "SqlServerHelper.h"
#include "CppHelper.h"
#include "EnumInfo.h"

#include <HCCStringBuilder.h>

namespace Harlinn::ODBC::Tool
{
    WideString SqlServerHelper::GetColumnName( const MemberInfo& member )
    {
        return Format( L"[{}]", member.Name( ) );
    }

    WideString SqlServerHelper::GetColumnType( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case MemberInfoType::Boolean:
            {
                result = L"[bit]";
            }
            break;
            case MemberInfoType::SByte:
            {
                result = L"[numeric](3,0)";
            }
            break;
            case MemberInfoType::Byte:
            {
                result = L"[tinyint]";
            }
            break;
            case MemberInfoType::Int16:
            {
                result = L"[smallint]";
            }
            break;
            case MemberInfoType::UInt16:
            {
                result = L"[numeric](5,0)";
            }
            break;
            case MemberInfoType::Int32:
            {
                result = L"[int]";
            }
            break;
            case MemberInfoType::UInt32:
            {
                result = L"[numeric](10,0)";
            }
            break;
            case MemberInfoType::Int64:
            {
                result = L"[bigint]";
            }
            break;
            case MemberInfoType::UInt64:
            {
                result = L"[numeric](20,0)";
            }
            break;
            case MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto valueType = enumType->ValueType( );
                    switch ( valueType )
                    {
                        case MemberInfoType::Boolean:
                        {
                            result = L"[bit]";
                        }
                        break;
                        case MemberInfoType::SByte:
                        {
                            result = L"[numeric](3,0)";
                        }
                        break;
                        case MemberInfoType::Byte:
                        {
                            result = L"[tinyint]";
                        }
                        break;
                        case MemberInfoType::Int16:
                        {
                            result = L"[smallint]";
                        }
                        break;
                        case MemberInfoType::UInt16:
                        {
                            result = L"[numeric](5,0)";
                        }
                        break;
                        case MemberInfoType::Int32:
                        {
                            result = L"[int]";
                        }
                        break;
                        case MemberInfoType::UInt32:
                        {
                            result = L"[numeric](10,0)";
                        }
                        break;
                        case MemberInfoType::Int64:
                        {
                            result = L"[bigint]";
                        }
                        break;
                        case MemberInfoType::UInt64:
                        {
                            result = L"[numeric](20,0)";
                        }
                        break;
                    }
                }
                else
                {
                    result = L"[int]";
                }

            }
            break;
            case MemberInfoType::Single:
            {
                result = L"[float](24)";
            }
            break;
            case MemberInfoType::Double:
            {
                result = L"[float](53)";
            }
            break;
            case MemberInfoType::Currency:
            {
                result = L"[bigint]";
            }
            break;
            case MemberInfoType::DateTime:
            {
                result = L"[bigint]";
            }
            break;
            case MemberInfoType::TimeSpan:
            {
                result = L"[bigint]";
            }
            break;
            case MemberInfoType::Guid:
            {
                result = L"[uniqueidentifier]";
            }
            break;
            case MemberInfoType::String:
            {
                const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( member );
                if ( stringMemberInfo.Size( ) == 0 || stringMemberInfo.Size( ) > 4000 )
                {
                    result = L"[nvarchar](max)";
                }
                else
                {
                    result = Format( L"[nvarchar]({})", stringMemberInfo.Size( ) );
                }
            }
            break;
            case MemberInfoType::Binary:
            {
                const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( member );
                if ( binaryMemberInfo.Size( ) == 0 || binaryMemberInfo.Size( ) > 8000 )
                {
                    result = L"[varbinary](max)";
                }
                else
                {
                    result = Format( L"[varbinary]({})", binaryMemberInfo.Size( ) );
                }
            }
            break;
            case MemberInfoType::RowVersion:
            {
                result = L"[bigint]";
            }
            break;
            case MemberInfoType::Reference:
            {
                const auto& referenceMemberInfo = static_cast< const ReferenceMemberInfo& >( member );
                auto referencedType = referenceMemberInfo.ReferencedType( );
                auto primaryKey = referencedType->PrimaryKey( );
                result = GetColumnType( *primaryKey );
            }
            break;
            case MemberInfoType::TimeSeries:
            {
                const auto& timeSeriesMemberInfo = static_cast< const TimeSeriesMemberInfo& >( member );
                auto referencedType = timeSeriesMemberInfo.ReferencedType( );
                auto primaryKey = referencedType->PrimaryKey( );
                result = GetColumnType( *primaryKey );
            }
            break;
        }

        return result;
    }

    WideString SqlServerHelper::GetTableName( const ClassInfo& classInfo )
    {
        return classInfo.Name( );
    }

    WideString SqlServerHelper::GetShortName( const ClassInfo& classInfo )
    {
        WideString result;
        auto name = classInfo.Name( ).FirstToUpper();
        auto length = name.Length( );
        const auto* ptr = name.c_str( );

        for ( size_t i = 0; i < length; i++ )
        {
            if ( iswupper( ptr[ i ] ) )
            {
                result += ptr[ i ];
            }
        }
        return result;
    }


    WideString SqlServerHelper::GetViewName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"View";
    }


    WideString SqlServerHelper::GetIndexName( const IndexInfo& indexInfo )
    {
        auto classInfo = indexInfo.Owner( );
        const auto& tableName = classInfo->Name( );

        StringBuilder<wchar_t> sb;
        if ( indexInfo.Unique( ) )
        {
            sb.Append( L"UNQ_{}_", tableName );
        }
        else
        {
            sb.Append( L"IDX_{}_", tableName );
        }
        const auto& members = indexInfo.Fields( );
        auto count = members.size( );
        for ( size_t i = 0; i < count; i++ )
        {
            const auto& member = members[ i ];
            if ( i < count - 1 )
            {
                sb.Append( L"{}_", member->Name( ) );
            }
            else
            {
                sb.Append( member->Name( ) );
            }
        }
        return sb.ToString( );
    }

    WideString SqlServerHelper::GetColumnNames( const IndexInfo& indexInfo )
    {
        StringBuilder<wchar_t> sb;
        const auto& members = indexInfo.Fields( );
        auto count = members.size( );
        for ( size_t i = 0; i < count; i++ )
        {
            const auto& member = members[ i ];
            if ( i < count - 1 )
            {
                sb.Append( L"[{}],", member->Name( ) );
            }
            else
            {
                sb.Append( L"[{}]", member->Name( ) );
            }
        }
        return sb.ToString( );
    }


    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetColumnsForSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& members = classInfo.PersistentMembers( );
        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) )
            {
                result.emplace_back( member );
            }
        }

        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }
        return result;
    }


    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetUnboundColumnsForSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& members = classInfo.PersistentMembers( );
        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetOwnColumnsForSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& members = classInfo.OwnPersistentMembers( );
        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) )
            {
                result.emplace_back( member );
            }
        }

        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetOwnUnboundColumnsForSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& members = classInfo.OwnPersistentMembers( );
        for ( const auto& member : members )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }
        return result;
    }


    WideString SqlServerHelper::GetColumnNamesForSelect( const ClassInfo& classInfo )
    {
        auto members = GetColumnsForSelect( classInfo );
        StringBuilder<wchar_t> sb;
        auto count = members.size( );
        for ( size_t i = 0; i < count; i++ )
        {
            const auto& member = members[ i ];
            if ( i < count - 1 )
            {
                sb.Append( L"[{}],", member->Name( ) );
            }
            else
            {
                sb.Append( L"[{}]", member->Name( ) );
            }
        }
        return sb.ToString( );
    }

    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetColumnsForComplexSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            if ( CppHelper::IsBindable( *member ) )
            {
                result.emplace_back( member );
            }
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                if ( CppHelper::IsBindable( *member ) )
                {
                    result.emplace_back( member );
                }
            }
        }

        for ( const auto& member : viewMembers )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }

        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                if ( CppHelper::IsBindable( *member ) == false )
                {
                    result.emplace_back( member );
                }
            }
        }
        return result;
    }
    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetBindableColumnsForComplexSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            if ( CppHelper::IsBindable( *member ) )
            {
                result.emplace_back( member );
            }
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                if ( CppHelper::IsBindable( *member ) )
                {
                    result.emplace_back( member );
                }
            }
        }
        return result;
    }
    std::vector<std::shared_ptr<MemberInfo>> SqlServerHelper::GetUnboundColumnsForComplexSelect( const ClassInfo& classInfo )
    {
        std::vector<std::shared_ptr<MemberInfo>> result;
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            if ( CppHelper::IsBindable( *member ) == false )
            {
                result.emplace_back( member );
            }
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                if ( CppHelper::IsBindable( *member ) == false )
                {
                    result.emplace_back( member );
                }
            }
        }
        return result;
    }


    WideString SqlServerHelper::GetInsertProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Insert";
    }
    WideString SqlServerHelper::GetInsertTriggerName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"InsertTrigger";
    }

    WideString SqlServerHelper::GetUpdateProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Update";
    }
    WideString SqlServerHelper::GetDeleteProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Delete";
    }
}