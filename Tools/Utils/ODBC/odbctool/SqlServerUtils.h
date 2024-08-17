#pragma once
#ifndef SQLSERVERUTILS_H_
#define SQLSERVERUTILS_H_

#include "ClassInfo.h"
#include <HCCStringBuilder.h>

namespace Harlinn::ODBC::Tool
{
    class SqlServerHelper
    {
    public:
        static WideString GetColumnName( const MemberInfo& member )
        {
            return Format( L"[{}]", member.Name( ) );
        }

        static WideString GetColumnType( const MemberInfo& member )
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

        static WideString GetTableName( const ClassInfo& classInfo )
        {
            return classInfo.Name( );
        }

        static WideString GetViewName( const ClassInfo& classInfo )
        {
            return classInfo.Name( ) + L"View";
        }


        static WideString GetIndexName( const IndexInfo& indexInfo )
        {
            auto classInfo = indexInfo.Owner( );
            const auto& tableName = classInfo->Name( );

            StringBuilder<wchar_t> sb;
            if ( indexInfo.Unique() )
            {
                sb.Append( L"UNQ_{}_", tableName );
            }
            else
            {
                sb.Append( L"IDX_{}_", tableName );
            }
            const auto& members = indexInfo.Fields( );
            auto count = members.size();
            for ( size_t i = 0; i < count; i++ )
            {
                const auto& member = members[ i ];
                if ( i < count - 1 )
                {
                    sb.Append( L"{}_", member->Name() );
                }
                else
                {
                    sb.Append( member->Name() );
                }
            }
            return sb.ToString( );
        }

        static WideString GetColumnNames( const IndexInfo& indexInfo )
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

        static WideString GetInsertProcedureName( const ClassInfo& classInfo )
        {
            return classInfo.Name() + L"Insert";
        }
        static WideString GetInsertTriggerName( const ClassInfo& classInfo )
        {
            return classInfo.Name( ) + L"InsertTrigger";
        }

        static WideString GetUpdateProcedureName( const ClassInfo& classInfo )
        {
            return classInfo.Name( ) + L"Update";
        }
        static WideString GetDeleteProcedureName( const ClassInfo& classInfo )
        {
            return classInfo.Name( ) + L"Delete";
        }



    };
}

#endif
