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
    public class KeyConstraintsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT kc.[name]
                  ,kc.[object_id]
                  ,kc.[principal_id]
                  ,kc.[schema_id]
                  ,kc.[parent_object_id]
                  ,kc.[type]
                  ,kc.[type_desc]
                  ,kc.[create_date]
                  ,kc.[modify_date]
                  ,kc.[is_ms_shipped]
                  ,kc.[is_published]
                  ,kc.[is_schema_published]
                  ,kc.[unique_index_id]
                  ,kc.[is_system_named]
                  ,kc.[is_enforced]
                  ,so.[name] AS [TableName]
              FROM [sys].[key_constraints] kc
              LEFT JOIN [sys].[objects] so ON (so.[object_id] = kc.[parent_object_id])
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
        public const int UniqueIndexIdOrdinal = 12;
        public const int IsSystemNamedOrdinal = 13;
        public const int IsEnforcedOrdinal = 14;
        public const int TableNameOrdinal = 15;

        public KeyConstraintsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public KeyConstraintsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public KeyConstraintsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return GetString(NameOrdinal);
        }

        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        public int? GetPrincipalId()
        {
            return GetNullableInt32(PrincipalIdOrdinal);
        }

        public int GetSchemaId()
        {
            return GetInt32(SchemaIdOrdinal);
        }

        public int GetParentObjectId()
        {
            return GetInt32(ParentObjectIdOrdinal);
        }

        public string GetSchemaObjectType()
        {
            return GetString(TypeOrdinal);
        }

        public string GetSchemaObjectTypeDesc()
        {
            return GetString(TypeDescOrdinal);
        }

        public DateTime GetCreateDate()
        {
            return GetDateTime(CreateDateOrdinal);
        }

        public DateTime GetModifyDate()
        {
            return GetDateTime(ModifyDateOrdinal);
        }

        public bool GetIsMsShipped()
        {
            return GetBoolean(IsMsShippedOrdinal);
        }

        public bool GetIsPublished()
        {
            return GetBoolean(IsPublishedOrdinal);
        }

        public bool GetIsSchemaPublished()
        {
            return GetBoolean(IsSchemaPublishedOrdinal);
        }

        public int? GetUniqueIndexId()
        {
            return GetNullableInt32(UniqueIndexIdOrdinal);
        }

        public bool GetIsSystemNamed()
        {
            return GetBoolean(IsSystemNamedOrdinal);
        }

        public bool GetIsEnforced()
        {
            return GetBoolean(IsEnforcedOrdinal);
        }

        public string? GetTableName()
        {
            return GetNullableString(TableNameOrdinal);
        }

        public KeyConstraint GetKeyConstraint()
        {
            return new KeyConstraint(
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
                GetUniqueIndexId(),
                GetIsSystemNamed(),
                GetIsEnforced(),
                GetTableName()
            );
        }

        public IReadOnlyList<KeyConstraint> GetKeyConstraints()
        {
            var list = new List<KeyConstraint>();
            while (Read())
            {
                list.Add(GetKeyConstraint());
            }
            return list;
        }
    }
}