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

public class AllSqlModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[all_sql_modules]";
    public const string TableName = "all_sql_modules";
    public const string ShortName = "asm";
    public const string Sql = """
        SELECT
          asm.[object_id],
          asm.[Definition],
          asm.[uses_ansi_nulls],
          asm.[uses_quoted_identifier],
          asm.[is_schema_bound],
          asm.[uses_database_collation],
          asm.[is_recompiled],
          asm.[null_on_null_input],
          asm.[execute_as_principal_id],
          asm.[uses_native_compilation],
          asm.[inline_type],
          asm.[is_inlineable]
        FROM
          [sys].[all_sql_modules] asm
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


    public AllSqlModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AllSqlModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AllSqlModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool? UsesAnsiNulls
    {
        get
        {
            return base.GetNullableBoolean(USESANSINULLS_FIELD_ID);
        }
    }

    public bool? UsesQuotedIdentifier
    {
        get
        {
            return base.GetNullableBoolean(USESQUOTEDIDENTIFIER_FIELD_ID);
        }
    }

    public bool? IsSchemaBound
    {
        get
        {
            return base.GetNullableBoolean(ISSCHEMABOUND_FIELD_ID);
        }
    }

    public bool? UsesDatabaseCollation
    {
        get
        {
            return base.GetNullableBoolean(USESDATABASECOLLATION_FIELD_ID);
        }
    }

    public bool? IsRecompiled
    {
        get
        {
            return base.GetNullableBoolean(ISRECOMPILED_FIELD_ID);
        }
    }

    public bool? NullOnNullInput
    {
        get
        {
            return base.GetNullableBoolean(NULLONNULLINPUT_FIELD_ID);
        }
    }

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }

    public bool? UsesNativeCompilation
    {
        get
        {
            return base.GetNullableBoolean(USESNATIVECOMPILATION_FIELD_ID);
        }
    }

    public bool? InlineType
    {
        get
        {
            return base.GetNullableBoolean(INLINETYPE_FIELD_ID);
        }
    }

    public bool? IsInlineable
    {
        get
        {
            return base.GetNullableBoolean(ISINLINEABLE_FIELD_ID);
        }
    }


    public Types.AllSqlModulesDataType ToDataObject()
    {
        return new Types.AllSqlModulesDataType(ObjectId,
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

    public List<Types.AllSqlModulesDataType> ToList()
    {
        var list = new List<Types.AllSqlModulesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
