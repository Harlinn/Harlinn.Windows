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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class CheckConstraintsReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT cc.[name]
            ,cc.[object_id]
            ,cc.[principal_id]
            ,cc.[schema_id]
            ,cc.[parent_object_id]
            ,cc.[type]
            ,cc.[type_desc]
            ,cc.[create_date]
            ,cc.[modify_date]
            ,cc.[is_ms_shipped]
            ,cc.[is_published]
            ,cc.[is_schema_published]
            ,cc.[is_disabled]
            ,cc.[is_not_for_replication]
            ,cc.[is_not_trusted]
            ,cc.[parent_column_id]
            ,cc.[definition]
            ,cc.[uses_database_collation]
            ,cc.[is_system_named]
            ,c.[name] AS [column_name]
        FROM [sys].[check_constraints] cc
        JOIN [sys].[columns] c ON cc.[parent_object_id] = c.[object_id] AND cc.[parent_column_id] = c.[column_id]
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
        public const int IsDisabledOrdinal = 12;
        public const int IsNotForReplicationOrdinal = 13;
        public const int IsNotTrustedOrdinal = 14;
        public const int ParentColumnIdOrdinal = 15;
        public const int DefinitionOrdinal = 16;
        public const int UsesDatabaseCollationOrdinal = 17;
        public const int IsSystemNamedOrdinal = 18;
        public const int ColumnNameOrdinal = 19;

        public CheckConstraintsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public CheckConstraintsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public CheckConstraintsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

        public int GetParentColumnId()
        {
            return base.GetInt32(ParentColumnIdOrdinal);
        }

        public string GetDefinition()
        {
            return base.GetString(DefinitionOrdinal);
        }

        public bool GetUsesDatabaseCollation()
        {
            return base.GetBoolean(UsesDatabaseCollationOrdinal);
        }

        public bool GetIsSystemNamed()
        {
            return base.GetBoolean(IsSystemNamedOrdinal);
        }

        public string? GetColumnName()
        {
            if (base.IsDBNull(ColumnNameOrdinal))
            {
                return null;
            }
            return base.GetString(ColumnNameOrdinal);
        }

        public CheckConstraint GetCheckConstraint()
        {
            var name = GetName();
            var objectId = GetObjectId();
            var principalId = GetPrincipalId();
            var schemaId = GetSchemaId();
            var parentObjectId = GetParentObjectId();
            var type = GetSchemaObjectType();
            var typeDesc = GetSchemaObjectTypeDesc();
            var createDate = GetCreateDate();
            var modifyDate = GetModifyDate();
            var isMsShipped = GetIsMsShipped();
            var isPublished = GetIsPublished();
            var isSchemaPublished = GetIsSchemaPublished();
            var isDisabled = GetIsDisabled();
            var isNotForReplication = GetIsNotForReplication();
            var isNotTrusted = GetIsNotTrusted();
            var parentColumnId = GetParentColumnId();
            var definition = GetDefinition();
            var usesDatabaseCollation = GetUsesDatabaseCollation();
            var isSystemNamed = GetIsSystemNamed();
            var columnName = GetColumnName();
            return new CheckConstraint(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished, isDisabled, isNotForReplication, isNotTrusted, parentColumnId, definition, usesDatabaseCollation, isSystemNamed, columnName);
        }

        public IReadOnlyList<CheckConstraint> GetCheckConstraints()
        {
            var checkConstraints = new List<CheckConstraint>();
            while (Read())
            {
                checkConstraints.Add(GetCheckConstraint());
            }
            return checkConstraints;
        }
    }

}
