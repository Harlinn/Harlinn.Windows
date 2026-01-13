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
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class SystemSqlModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[system_sql_modules]";
    public const string TableName = "system_sql_modules";
    public const string ShortName = "ssm";
    public const string Sql = """
        SELECT
          ssm.[object_id],
          ssm.[Definition],
          ssm.[uses_ansi_nulls],
          ssm.[uses_quoted_identifier],
          ssm.[is_schema_bound],
          ssm.[uses_database_collation],
          ssm.[is_recompiled],
          ssm.[null_on_null_input],
          ssm.[execute_as_principal_id],
          ssm.[uses_native_compilation],
          ssm.[inline_type],
          ssm.[is_inlineable]
        FROM
          [sys].[system_sql_modules] ssm
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int DEFINITION_FIELD_ID = 1;
    public const int USESANSINULLS_FIELD_ID = 2;
    public const int USESQUOTEDIDENTIFIER_FIELD_ID = 3;
    public const int ISSCHEMABOUND_FIELD_ID = 4;
    public const int USESDATABASECOLLATION_FIELD_ID = 5;
    public const int ISRECOMPILED_FIELD_ID = 6;
    public const int NULLONNULLINPUT_FIELD_ID = 7;
    public const int EXECUTEASPRINCIPALID_FIELD_ID = 8;
    public const int USESNATIVECOMPILATION_FIELD_ID = 9;
    public const int INLINETYPE_FIELD_ID = 10;
    public const int ISINLINEABLE_FIELD_ID = 11;


    public SystemSqlModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystemSqlModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystemSqlModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public string? Definition
    {
        get
        {
            return base.GetNullableString(DEFINITION_FIELD_ID);
        }
    }

    public bool UsesAnsiNulls
    {
        get
        {
            return base.GetBoolean(USESANSINULLS_FIELD_ID);
        }
    }

    public bool UsesQuotedIdentifier
    {
        get
        {
            return base.GetBoolean(USESQUOTEDIDENTIFIER_FIELD_ID);
        }
    }

    public bool IsSchemaBound
    {
        get
        {
            return base.GetBoolean(ISSCHEMABOUND_FIELD_ID);
        }
    }

    public bool UsesDatabaseCollation
    {
        get
        {
            return base.GetBoolean(USESDATABASECOLLATION_FIELD_ID);
        }
    }

    public bool IsRecompiled
    {
        get
        {
            return base.GetBoolean(ISRECOMPILED_FIELD_ID);
        }
    }

    public bool NullOnNullInput
    {
        get
        {
            return base.GetBoolean(NULLONNULLINPUT_FIELD_ID);
        }
    }

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }

    public bool UsesNativeCompilation
    {
        get
        {
            return base.GetBoolean(USESNATIVECOMPILATION_FIELD_ID);
        }
    }

    public bool InlineType
    {
        get
        {
            return base.GetBoolean(INLINETYPE_FIELD_ID);
        }
    }

    public bool IsInlineable
    {
        get
        {
            return base.GetBoolean(ISINLINEABLE_FIELD_ID);
        }
    }


    public Types.SystemSqlModule ToDataObject()
    {
        return new Types.SystemSqlModule(ObjectId,
            Definition,
            UsesAnsiNulls,
            UsesQuotedIdentifier,
            IsSchemaBound,
            UsesDatabaseCollation,
            IsRecompiled,
            NullOnNullInput,
            ExecuteAsPrincipalId,
            UsesNativeCompilation,
            InlineType,
            IsInlineable);
    }

    public List<Types.SystemSqlModule> ToList()
    {
        var list = new List<Types.SystemSqlModule>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
