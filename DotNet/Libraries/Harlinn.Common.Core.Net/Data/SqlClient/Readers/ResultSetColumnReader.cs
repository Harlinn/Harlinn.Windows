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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    /// <summary>
    /// Wrapper around the result set returned by <c>sp_describe_first_result_set</c>.
    /// Use the Sql constant to see how to call the stored procedure; when executing you must supply the @tsql parameter.
    /// </summary>
    public class ResultSetColumnReader : DataReaderWrapper
    {
        // Example invocation: EXEC sp_describe_first_result_set @tsql = @tsql;
        public const string Sql = "EXEC sys.sp_describe_first_result_set @tsql = @tsql, @params = NULL, @include_browse_information = 1";

        public const int IsHiddenOrdinal = 0;
        public const int ColumnOrdinalOrdinal = 1;
        public const int NameOrdinal = 2;
        public const int IsNullableOrdinal = 3;
        public const int SystemTypeIdOrdinal = 4;
        public const int SystemTypeNameOrdinal = 5;
        public const int MaxLengthOrdinal = 6;
        public const int PrecisionOrdinal = 7;
        public const int ScaleOrdinal = 8;
        public const int CollationNameOrdinal = 9;
        public const int UserTypeIdOrdinal = 10;
        public const int UserTypeDatabaseOrdinal = 11;
        public const int UserTypeSchemaOrdinal = 12;
        public const int UserTypeNameOrdinal = 13;
        public const int AssemblyQualifiedTypeNameOrdinal = 14;
        public const int XmlCollectionIdOrdinal = 15;
        public const int XmlCollectionDatabaseOrdinal = 16;
        public const int XmlCollectionSchemaOrdinal = 17;
        public const int XmlCollectionNameOrdinal = 18;
        public const int IsXmlDocumentOrdinal = 19;
        public const int IsCaseSensitiveOrdinal = 20;
        public const int IsFixedLengthClrTypeOrdinal = 21;
        public const int SourceServerOrdinal = 22;
        public const int SourceDatabaseOrdinal = 23;
        public const int SourceSchemaOrdinal = 24;
        public const int SourceTableOrdinal = 25;
        public const int SourceColumnOrdinal = 26;
        public const int IsIdentityColumnOrdinal = 27;
        public const int IsPartOfUniqueKeyOrdinal = 28;
        public const int IsUpdateableOrdinal = 29;
        public const int IsComputedColumnOrdinal = 30;
        public const int IsSparseColumnSetOrdinal = 31;
        public const int OrdinalInOrderByListOrdinal = 32;
        public const int OrderByListLengthOrdinal = 33;
        public const int OrderByIsDescendingOrdinal = 34;
        public const int TdsTypeIdOrdinal = 35;
        public const int TdsLengthOrdinal = 36;
        public const int TdsCollationOrdinal = 37;
        public const int TdsCollationSortIdOrdinal = 38;

        public ResultSetColumnReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ResultSetColumnReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ResultSetColumnReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public bool GetIsHidden() => GetBoolean(IsHiddenOrdinal);
        public int GetColumnOrdinal() => GetInt32(ColumnOrdinalOrdinal);
        public string? GetName() => GetNullableString(NameOrdinal);
        public bool GetIsNullable() => GetBoolean(IsNullableOrdinal);
        public int GetSystemTypeId() => GetInt32(SystemTypeIdOrdinal);
        public string? GetSystemTypeName() => GetNullableString(SystemTypeNameOrdinal);
        public short? GetMaxLength() => GetNullableInt16(MaxLengthOrdinal);
        public byte? GetPrecision() => IsDBNull(PrecisionOrdinal) ? null : GetByte(PrecisionOrdinal);
        public byte? GetScale() => GetNullableByte(ScaleOrdinal);
        public string? GetCollationName() => GetNullableString(CollationNameOrdinal);
        public int? GetUserTypeId() => GetNullableInt32(UserTypeIdOrdinal);
        public string? GetUserTypeDatabase() => GetNullableString(UserTypeDatabaseOrdinal);
        public string? GetUserTypeSchema() => GetNullableString(UserTypeSchemaOrdinal);
        public string? GetUserTypeName() => GetNullableString(UserTypeNameOrdinal);
        public string? GetAssemblyQualifiedTypeName() => GetNullableString(AssemblyQualifiedTypeNameOrdinal);
        public int? GetXmlCollectionId() => GetNullableInt32(XmlCollectionIdOrdinal);
        public string? GetXmlCollectionDatabase() => GetNullableString(XmlCollectionDatabaseOrdinal);
        public string? GetXmlCollectionSchema() => GetNullableString(XmlCollectionSchemaOrdinal);
        public string? GetXmlCollectionName() => GetNullableString(XmlCollectionNameOrdinal);
        public bool GetIsXmlDocument() => GetBoolean(IsXmlDocumentOrdinal);
        public bool GetIsCaseSensitive() => GetBoolean(IsCaseSensitiveOrdinal);
        public bool GetIsFixedLengthClrType() => GetBoolean(IsFixedLengthClrTypeOrdinal);
        public string? GetSourceServer() => GetNullableString(SourceServerOrdinal);
        public string? GetSourceDatabase() => GetNullableString(SourceDatabaseOrdinal);
        public string? GetSourceSchema() => GetNullableString(SourceSchemaOrdinal);
        public string? GetSourceTable() => GetNullableString(SourceTableOrdinal);
        public string? GetSourceColumn() => GetNullableString(SourceColumnOrdinal);
        public bool GetIsIdentityColumn() => GetBoolean(IsIdentityColumnOrdinal);
        public bool GetIsPartOfUniqueKey() => GetBoolean(IsPartOfUniqueKeyOrdinal);
        public bool GetIsUpdateable() => GetBoolean(IsUpdateableOrdinal);
        public bool GetIsComputedColumn() => GetBoolean(IsComputedColumnOrdinal);
        public bool GetIsSparseColumnSet() => GetBoolean(IsSparseColumnSetOrdinal);
        public int? GetOrdinalInOrderByList() => GetNullableInt32(OrdinalInOrderByListOrdinal);
        public int? GetOrderByListLength() => GetNullableInt32(OrderByListLengthOrdinal);

        public short? GetOrderByIsDescending() => GetNullableInt16(OrderByIsDescendingOrdinal);
        public int? GetTdsTypeId() => IsDBNull(TdsTypeIdOrdinal) ? null : GetInt32(TdsTypeIdOrdinal);
        public int? GetTdsLength() => GetNullableInt32(TdsLengthOrdinal);
        public int? GetTdsCollation() => GetNullableInt32(TdsCollationOrdinal);
        

        public ResultSetColumn GetColumn()
        {
            bool isHidden = GetIsHidden();
            int columnOrdinal = GetColumnOrdinal();
            string? name = GetName();
            bool isNullable = GetIsNullable();
            int systemTypeId = GetSystemTypeId();
            string? systemTypeName = GetSystemTypeName();
            short? maxLength = GetMaxLength();
            byte? precision = GetPrecision();
            byte? scale = GetScale();
            string? collationName = GetCollationName();
            int? userTypeId = GetUserTypeId();
            string? userTypeDatabase = GetUserTypeDatabase();
            string? userTypeSchema = GetUserTypeSchema();
            string? userTypeName = GetUserTypeName();
            string? assemblyQualifiedTypeName = GetAssemblyQualifiedTypeName();
            int? xmlCollectionId = GetXmlCollectionId();
            string? xmlCollectionDatabase = GetXmlCollectionDatabase();
            string? xmlCollectionSchema = GetXmlCollectionSchema();
            string? xmlCollectionName = GetXmlCollectionName();
            bool isXmlDocument = GetIsXmlDocument();
            bool isCaseSensitive = GetIsCaseSensitive();
            bool isFixedLengthClrType = GetIsFixedLengthClrType();
            string? sourceServer = GetSourceServer();
            string? sourceDatabase = GetSourceDatabase();
            string? sourceSchema = GetSourceSchema();
            string? sourceTable = GetSourceTable();
            string? sourceColumn = GetSourceColumn();
            bool isIdentityColumn = GetIsIdentityColumn();
            bool isPartOfUniqueKey = GetIsPartOfUniqueKey();
            bool isUpdateable = GetIsUpdateable();
            bool isComputedColumn = GetIsComputedColumn();
            bool isSparseColumnSet = GetIsSparseColumnSet();
            int? ordinalInOrderByList = GetOrdinalInOrderByList();
            int? orderByListLength = GetOrderByListLength();
            short? orderByIsDescending = GetOrderByIsDescending();
            int? tdsTypeId = GetTdsTypeId();
            int? tdsLength = GetTdsLength();
            int? tdsCollation = GetTdsCollation();


            return new ResultSetColumn(
                isHidden,
                columnOrdinal,
                name,
                isNullable,
                systemTypeId,
                systemTypeName,
                maxLength,
                precision,
                scale,
                collationName,
                userTypeId,
                userTypeDatabase,
                userTypeSchema,
                userTypeName,
                assemblyQualifiedTypeName,
                xmlCollectionId,
                xmlCollectionDatabase,
                xmlCollectionSchema,
                xmlCollectionName,
                isXmlDocument,
                isCaseSensitive,
                isFixedLengthClrType,
                sourceServer,
                sourceDatabase,
                sourceSchema,
                sourceTable,
                sourceColumn,
                isIdentityColumn,
                isPartOfUniqueKey,
                isUpdateable,
                isComputedColumn,
                isSparseColumnSet,
                ordinalInOrderByList,
                orderByListLength,
                orderByIsDescending,
                tdsTypeId,
                tdsLength,
                tdsCollation);
        }

        public IReadOnlyList<ResultSetColumn> GetColumns()
        {
            var list = new List<ResultSetColumn>();
            while (Read())
            {
                list.Add(GetColumn());
            }
            return list;
        }
    }
}