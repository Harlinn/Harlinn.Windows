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

public class ServerSqlModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_sql_modules]";
    public const string TableName = "server_sql_modules";
    public const string ShortName = "ssm0";
    public const string Sql = """
        SELECT
          ssm0.[object_id],
          ssm0.[Definition],
          ssm0.[uses_ansi_nulls],
          ssm0.[uses_quoted_identifier],
          ssm0.[execute_as_principal_id]
        FROM
          [sys].[server_sql_modules] ssm0
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int DEFINITION_FIELD_ID = 1;
    public const int USESANSINULLS_FIELD_ID = 2;
    public const int USESQUOTEDIDENTIFIER_FIELD_ID = 3;
    public const int EXECUTEASPRINCIPALID_FIELD_ID = 4;


    public ServerSqlModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerSqlModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerSqlModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }


    public Types.ServerSqlModulesDataType ToDataObject()
    {
        return new Types.ServerSqlModulesDataType(ObjectId,
            Definition,
            UsesAnsiNulls,
            UsesQuotedIdentifier,
            ExecuteAsPrincipalId);
    }

    public List<Types.ServerSqlModulesDataType> ToList()
    {
        var list = new List<Types.ServerSqlModulesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
