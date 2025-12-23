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
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class SqlModulesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT sm.[object_id]
                ,sm.[definition]
                ,sm.[uses_ansi_nulls]
                ,sm.[uses_quoted_identifier]
                ,sm.[is_schema_bound]
                ,sm.[uses_database_collation]
                ,sm.[is_recompiled]
                ,sm.[null_on_null_input]
                ,sm.[execute_as_principal_id]
                ,sm.[uses_native_compilation]
                ,sm.[inline_type]
            FROM [sys].[sql_modules] sm
            """;

        public const int ObjectIdOrdinal = 0;
        public const int DefinitionOrdinal = 1;
        public const int UsesAnsiNullsOrdinal = 2;
        public const int UsesQuotedIdentifierOrdinal = 3;
        public const int IsSchemaBoundOrdinal = 4;
        public const int UsesDatabaseCollationOrdinal = 5;
        public const int IsRecompiledOrdinal = 6;
        public const int NullOnNullInputOrdinal = 7;
        public const int ExecuteAsPrincipalIdOrdinal = 8;
        public const int UsesNativeCompilationOrdinal = 9;
        public const int InlineTypeOrdinal = 10;

        public SqlModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public SqlModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public SqlModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        
        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        public string? GetDefinition()
        {
            return GetNullableString(DefinitionOrdinal);
        }

        public bool GetUsesAnsiNulls()
        {
            return GetBoolean(UsesAnsiNullsOrdinal);
        }

        public bool GetUsesQuotedIdentifier()
        {
            return GetBoolean(UsesQuotedIdentifierOrdinal);
        }

        public bool GetIsSchemaBound()
        {
            return GetBoolean(IsSchemaBoundOrdinal);
        }

        public bool GetUsesDatabaseCollation()
        {
            return GetBoolean(UsesDatabaseCollationOrdinal);
        }

        public bool GetIsRecompiled()
        {
            return GetBoolean(IsRecompiledOrdinal);
        }

        public bool GetNullOnNullInput()
        {
            return GetBoolean(NullOnNullInputOrdinal);
        }

        public int? GetExecuteAsPrincipalId()
        {
            if (IsDBNull(ExecuteAsPrincipalIdOrdinal))
            {
                return null;
            }
            return GetInt32(ExecuteAsPrincipalIdOrdinal);
        }

        public bool GetUsesNativeCompilation()
        {
            return GetBoolean(UsesNativeCompilationOrdinal);
        }

        public bool GetInlineType()
        {
            return GetBoolean(InlineTypeOrdinal);
        }


        
        public SqlModule GetSqlModule()
        {
            var objectId = GetObjectId();
            var definition = GetDefinition();
            var usesAnsiNulls = GetUsesAnsiNulls();
            var usesQuotedIdentifier = GetUsesQuotedIdentifier();
            var isSchemaBound = GetIsSchemaBound();
            var usesDatabaseCollation = GetUsesDatabaseCollation();
            var isRecompiled = GetIsRecompiled();
            var nullOnNullInput = GetNullOnNullInput();
            var executeAsPrincipalId = GetExecuteAsPrincipalId();
            var usesNativeCompilation = GetUsesNativeCompilation();
            var inlineType = GetInlineType();
            return new SqlModule(objectId, definition, usesAnsiNulls, usesQuotedIdentifier, isSchemaBound, usesDatabaseCollation, isRecompiled, nullOnNullInput, executeAsPrincipalId, usesNativeCompilation, inlineType);
        }
        
        public IReadOnlyList<SqlModule> GetSqlModules()
        {
            var modules = new List<SqlModule>();
            while (Read())
            {
                modules.Add(GetSqlModule());
            }
            return modules;
        }
        

    }


}
