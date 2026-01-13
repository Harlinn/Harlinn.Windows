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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{

    public class ForeignKeyReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT fk.[name]
            ,fk.[object_id]
            ,fk.[principal_id]
            ,fk.[schema_id]
            ,fk.[parent_object_id]
            ,fk.[type]
            ,fk.[type_desc]
            ,fk.[create_date]
            ,fk.[modify_date]
            ,fk.[is_ms_shipped]
            ,fk.[is_published]
            ,fk.[is_schema_published]
            ,fk.[referenced_object_id]
            ,fk.[key_index_id]
            ,fk.[is_disabled]
            ,fk.[is_not_for_replication]
            ,fk.[is_not_trusted]
            ,fk.[delete_referential_action]
            ,fk.[delete_referential_action_desc]
            ,fk.[update_referential_action]
            ,fk.[update_referential_action_desc]
            ,fk.[is_system_named]
            , t.[name] AS [table_name]
            , s.[name] AS [schema_name]
            , rt.[name] AS [referenced_table_name]
            , rs.[name] AS [referenced_schema_name]
        FROM [sys].[foreign_keys] fk
        INNER JOIN sys.tables t ON fk.[parent_object_id] = t.object_id
        INNER JOIN sys.schemas s ON t.schema_id = s.schema_id
        INNER JOIN sys.tables rt ON fk.referenced_object_id = rt.object_id
        INNER JOIN sys.schemas rs ON rt.schema_id = rs.schema_id
        """;

        public const int NameOrdinal = 0;
        public const int ObjectIdOrdinal = 1;
        public const int PrincipalIdOrdinal = 2;
        public const int SchemaIdOrdinal = 3;
        public const int ParentObjectIdOrdinal = 4;
        public const int TypeOrdinal = 5;
        public const int TypeDescOrdinal = 6;
        public const int CreateDateOrdinal = 7;
        public const int ModifyDateOrdinal = 8;
        public const int IsMsShippedOrdinal = 9;
        public const int IsPublishedOrdinal = 10;
        public const int IsSchemaPublishedOrdinal = 11;
        public const int ReferencedObjectIdOrdinal = 12;
        public const int KeyIndexIdOrdinal = 13;
        public const int IsDisabledOrdinal = 14;
        public const int IsNotForReplicationOrdinal = 15;
        public const int IsNotTrustedOrdinal = 16;
        public const int DeleteReferentialActionOrdinal = 17;
        public const int DeleteReferentialActionDescOrdinal = 18;
        public const int UpdateReferentialActionOrdinal = 19;
        public const int UpdateReferentialActionDescOrdinal = 20;
        public const int IsSystemNamedOrdinal = 21;
        public const int TableNameOrdinal = 22;
        public const int SchemaNameOrdinal = 23;
        public const int ReferencedTableNameOrdinal = 24;
        public const int ReferencedSchemaNameOrdinal = 25;

        public ForeignKeyReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true) 
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ForeignKeyReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ForeignKeyReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        public int? GetPrincipalId()
        {
            return base.GetNullableInt32(PrincipalIdOrdinal);
        }

        public int GetSchemaId()
        {
            return base.GetInt32(SchemaIdOrdinal);
        }

        public int GetParentObjectId()
        {
            return base.GetInt32(ParentObjectIdOrdinal);
        }

        public string GetSchemaObjectType()
        {
            return base.GetString(TypeOrdinal);
        }

        public string GetSchemaObjectTypeDesc()
        {
            return base.GetString(TypeDescOrdinal);
        }

        public DateTime GetCreateDate()
        {
            return base.GetDateTime(CreateDateOrdinal);
        }

        public DateTime GetModifyDate()
        {
            return base.GetDateTime(ModifyDateOrdinal);
        }

        public bool GetIsMsShipped()
        {
            return base.GetBoolean(IsMsShippedOrdinal);
        }

        public bool GetIsPublished()
        {
            return base.GetBoolean(IsPublishedOrdinal);
        }

        public bool GetIsSchemaPublished()
        {
            return base.GetBoolean(IsSchemaPublishedOrdinal);
        }

        public int GetReferencedObjectId()
        {
            return base.GetInt32(ReferencedObjectIdOrdinal);
        }

        public int GetKeyIndexId()
        {
            return base.GetInt32(KeyIndexIdOrdinal);
        }

        public bool GetIsDisabled()
        {
            return base.GetBoolean(IsDisabledOrdinal);
        }

        public bool GetIsNotForReplication()
        {
            return base.GetBoolean(IsNotForReplicationOrdinal);
        }

        public bool GetIsNotTrusted()
        {
            return base.GetBoolean(IsNotTrustedOrdinal);
        }

        public sbyte GetDeleteReferentialAction()
        {
            return base.GetSByte(DeleteReferentialActionOrdinal);
        }

        public string GetDeleteReferentialActionDesc()
        {
            return base.GetString(DeleteReferentialActionDescOrdinal);
        }

        public sbyte GetUpdateReferentialAction()
        {
            return base.GetSByte(UpdateReferentialActionOrdinal);
        }

        public string GetUpdateReferentialActionDesc()
        {
            return base.GetString(UpdateReferentialActionDescOrdinal);
        }

        public bool GetIsSystemNamed()
        {
            return base.GetBoolean(IsSystemNamedOrdinal);
        }

        public string GetTableName()
        {
            return base.GetString(TableNameOrdinal);
        }
        public string GetSchemaName()
        {
            return base.GetString(SchemaNameOrdinal);
        }

        public string GetReferencedTableName()
        {
            return base.GetString(ReferencedTableNameOrdinal);
        }

        public string GetReferencedSchemaName()
        {
            return base.GetString(ReferencedSchemaNameOrdinal);
        }

        public Types.ForeignKey GetForeignKey()
        {
            return new Types.ForeignKey(
                GetName(),
                GetObjectId(),
                GetPrincipalId(),
                GetSchemaId(),
                GetParentObjectId(),
                GetSchemaObjectType(),
                GetSchemaObjectTypeDesc(),
                GetCreateDate(),
                GetModifyDate(),
                GetIsMsShipped(),
                GetIsPublished(),
                GetIsSchemaPublished(),
                GetReferencedObjectId(),
                GetKeyIndexId(),
                GetIsDisabled(),
                GetIsNotForReplication(),
                GetIsNotTrusted(),
                GetDeleteReferentialAction(),
                GetDeleteReferentialActionDesc(),
                GetUpdateReferentialAction(),
                GetUpdateReferentialActionDesc(),
                GetIsSystemNamed(),
                GetTableName(),
                GetSchemaName(),
                GetReferencedTableName(),
                GetReferencedSchemaName());
        }

        public IReadOnlyList<Types.ForeignKey> GetForeignKeys()
        {
            var foreignKeys = new List<Types.ForeignKey>();
            while (Read())
            {
                foreignKeys.Add(GetForeignKey());
            }
            return foreignKeys;
        }

    }

}
