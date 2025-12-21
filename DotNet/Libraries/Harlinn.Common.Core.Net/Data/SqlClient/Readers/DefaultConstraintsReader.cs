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
    public class DefaultConstraintsReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT [name]
            ,[object_id]
            ,[principal_id]
            ,[schema_id]
            ,[parent_object_id]
            ,[type]
            ,[type_desc]
            ,[create_date]
            ,[modify_date]
            ,[is_ms_shipped]
            ,[is_published]
            ,[is_schema_published]
            ,[parent_column_id]
            ,[definition]
            ,[is_system_named]
        FROM [sys].[default_constraints]
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
        public const int ParentColumnIdOrdinal = 12;
        public const int DefinitionOrdinal = 13;
        public const int IsSystemNamedOrdinal = 14;

        public DefaultConstraintsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public DefaultConstraintsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public DefaultConstraintsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

        public int GetParentColumnId()
        {
            return base.GetInt32(ParentColumnIdOrdinal);
        }

        public string GetDefinition()
        {
            return base.GetString(DefinitionOrdinal);
        }

        public bool GetIsSystemNamed()
        {
            return base.GetBoolean(IsSystemNamedOrdinal);
        }

        public DefaultConstraint GetDefaultConstraint()
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
            var parentColumnId = GetParentColumnId();
            var definition = GetDefinition();
            var isSystemNamed = GetIsSystemNamed();
            return new DefaultConstraint(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished, parentColumnId, definition, isSystemNamed);
        }

        public IReadOnlyList<SchemaObject> GetSchemaObjects()
        {
            var schemaObjects = new List<SchemaObject>();
            while (Read())
            {
                schemaObjects.Add(GetDefaultConstraint());
            }
            return schemaObjects;
        }
    }

}
