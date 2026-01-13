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
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class SchemasReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT [name]
                ,[schema_id]
                ,[principal_id]
            FROM [sys].[schemas]
            """;

        public const int NameOrdinal = 0;
        public const int SchemaIdOrdinal = 1;
        public const int PrincipalIdOrdinal = 2;

        public SchemasReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public SchemasReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public SchemasReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        public int GetSchemaId()
        {
            return base.GetInt32(SchemaIdOrdinal);
        }

        public int GetPrincipalId()
        {
            return base.GetInt32(PrincipalIdOrdinal);
        }

        public Schema GetSchema()
        {
            var name = GetName();
            var schemaId = GetSchemaId();
            var principalId = GetPrincipalId();
            return new Schema(name, schemaId, principalId);
        }

        public IReadOnlyList<Schema> GetSchemas()
        {
            var schemas = new List<Schema>();
            while (Read())
            {
                schemas.Add(GetSchema());
            }
            return schemas;
        }
    }

}
