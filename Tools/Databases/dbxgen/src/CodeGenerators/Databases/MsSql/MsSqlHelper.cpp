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

#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"
#include "CodeGenerators/Cpp/CppHelper.h"
#include "Metadata/EnumInfo.h"

#include <HCCStringBuilder.h>

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp;

    WideString MsSqlHelper::GetColumnName( const MemberInfo& member )
    {
        return Format( L"[{}]", member.Name( ) );
    }

    WideString MsSqlHelper::GetColumnType( const MemberInfo& member )
    {
        WideString result = L"<unknown>";
        auto memberInfoType = member.Type( );
        switch ( memberInfoType )
        {
            case Metadata::MemberInfoType::Boolean:
            {
                result = L"[bit]";
            }
            break;
            case Metadata::MemberInfoType::SByte:
            {
                result = L"[numeric](3,0)";
            }
            break;
            case Metadata::MemberInfoType::Byte:
            {
                result = L"[tinyint]";
            }
            break;
            case Metadata::MemberInfoType::Int16:
            {
                result = L"[smallint]";
            }
            break;
            case Metadata::MemberInfoType::UInt16:
            {
                result = L"[numeric](5,0)";
            }
            break;
            case Metadata::MemberInfoType::Int32:
            {
                result = L"[int]";
            }
            break;
            case Metadata::MemberInfoType::UInt32:
            {
                result = L"[numeric](10,0)";
            }
            break;
            case Metadata::MemberInfoType::Int64:
            {
                result = L"[bigint]";
            }
            break;
            case Metadata::MemberInfoType::UInt64:
            {
                result = L"[numeric](20,0)";
            }
            break;
            case Metadata::MemberInfoType::Enum:
            {
                const auto& enumMemberInfo = static_cast< const Metadata::EnumMemberInfo& >( member );
                auto enumType = enumMemberInfo.EnumType( );
                if ( enumType )
                {
                    auto valueType = enumType->ValueType( );
                    switch ( valueType )
                    {
                        case Metadata::MemberInfoType::Boolean:
                        {
                            result = L"[bit]";
                        }
                        break;
                        case Metadata::MemberInfoType::SByte:
                        {
                            result = L"[numeric](3,0)";
                        }
                        break;
                        case Metadata::MemberInfoType::Byte:
                        {
                            result = L"[tinyint]";
                        }
                        break;
                        case Metadata::MemberInfoType::Int16:
                        {
                            result = L"[smallint]";
                        }
                        break;
                        case Metadata::MemberInfoType::UInt16:
                        {
                            result = L"[numeric](5,0)";
                        }
                        break;
                        case Metadata::MemberInfoType::Int32:
                        {
                            result = L"[int]";
                        }
                        break;
                        case Metadata::MemberInfoType::UInt32:
                        {
                            result = L"[numeric](10,0)";
                        }
                        break;
                        case Metadata::MemberInfoType::Int64:
                        {
                            result = L"[bigint]";
                        }
                        break;
                        case Metadata::MemberInfoType::UInt64:
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
            case Metadata::MemberInfoType::Single:
            {
                result = L"[float](24)";
            }
            break;
            case Metadata::MemberInfoType::Double:
            {
                result = L"[float](53)";
            }
            break;
            case Metadata::MemberInfoType::Currency:
            {
                result = L"[bigint]";
            }
            break;
            case Metadata::MemberInfoType::DateTime:
            {
                result = L"[bigint]";
            }
            break;
            case Metadata::MemberInfoType::TimeSpan:
            {
                result = L"[bigint]";
            }
            break;
            case Metadata::MemberInfoType::Guid:
            {
                result = L"[uniqueidentifier]";
            }
            break;
            case Metadata::MemberInfoType::String:
            {
                const auto& stringMemberInfo = static_cast< const Metadata::StringMemberInfo& >( member );
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
            case Metadata::MemberInfoType::Binary:
            {
                const auto& binaryMemberInfo = static_cast< const Metadata::BinaryMemberInfo& >( member );
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
            case Metadata::MemberInfoType::RowVersion:
            {
                result = L"[bigint]";
            }
            break;
            case Metadata::MemberInfoType::Reference:
            {
                const auto& referenceMemberInfo = static_cast< const Metadata::ReferenceMemberInfo& >( member );
                auto referencedType = referenceMemberInfo.ReferencedType( );
                auto primaryKey = referencedType->PrimaryKey( );
                result = GetColumnType( *primaryKey );
            }
            break;
            case Metadata::MemberInfoType::TimeSeries:
            {
                const auto& timeSeriesMemberInfo = static_cast< const Metadata::TimeSeriesMemberInfo& >( member );
                auto referencedType = timeSeriesMemberInfo.ReferencedType( );
                auto primaryKey = referencedType->PrimaryKey( );
                result = GetColumnType( *primaryKey );
            }
            break;
        }

        return result;
    }

    WideString MsSqlHelper::GetTableName( const ClassInfo& classInfo )
    {
        return classInfo.Name( );
    }

    WideString MsSqlHelper::GetShortName( const ClassInfo& classInfo )
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


    WideString MsSqlHelper::GetViewName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"View";
    }


    WideString MsSqlHelper::GetIndexName( const IndexInfo& indexInfo )
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

    WideString MsSqlHelper::GetColumnNames( const IndexInfo& indexInfo )
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


    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetColumnsForSelect( const ClassInfo& classInfo )
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


    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetUnboundColumnsForSelect( const ClassInfo& classInfo )
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

    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetOwnColumnsForSelect( const ClassInfo& classInfo )
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

    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetOwnUnboundColumnsForSelect( const ClassInfo& classInfo )
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


    WideString MsSqlHelper::GetColumnNamesForSelect( const ClassInfo& classInfo )
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

    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetColumnsForComplexSelect( const ClassInfo& classInfo )
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
    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetBindableColumnsForComplexSelect( const ClassInfo& classInfo )
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
    std::vector<std::shared_ptr<Metadata::MemberInfo>> MsSqlHelper::GetUnboundColumnsForComplexSelect( const ClassInfo& classInfo )
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


    WideString MsSqlHelper::GetInsertProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Insert";
    }
    WideString MsSqlHelper::GetInsertProcedureName1( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Insert1";
    }
    WideString MsSqlHelper::GetInsertTriggerName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"InsertTrigger";
    }

    WideString MsSqlHelper::GetUpdateProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Update";
    }
    WideString MsSqlHelper::GetUpdateProcedureName1( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Update1";
    }
    WideString MsSqlHelper::GetUpdateProcedureName2( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Update2";
    }
    WideString MsSqlHelper::GetDeleteProcedureName( const ClassInfo& classInfo )
    {
        return classInfo.Name( ) + L"Delete";
    }
}