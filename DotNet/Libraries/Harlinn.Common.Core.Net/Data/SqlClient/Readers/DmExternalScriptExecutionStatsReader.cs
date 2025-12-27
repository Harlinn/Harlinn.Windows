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

public class DmExternalScriptExecutionStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_external_script_execution_stats]";
    public const string TableName = "dm_external_script_execution_stats";
    public const string ShortName = "deses";
    public const string Sql = """
        SELECT
          deses.[Language],
          deses.[counter_name],
          deses.[counter_value]
        FROM
          [sys].[dm_external_script_execution_stats] deses
        """;

    public const int LANGUAGE_FIELD_ID = 0;
    public const int COUNTERNAME_FIELD_ID = 1;
    public const int COUNTERVALUE_FIELD_ID = 2;


    public DmExternalScriptExecutionStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptExecutionStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptExecutionStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Language
    {
        get
        {
            return base.GetNullableString(LANGUAGE_FIELD_ID);
        }
    }

    public string CounterName
    {
        get
        {
            return base.GetString(COUNTERNAME_FIELD_ID);
        }
    }

    public long CounterValue
    {
        get
        {
            return base.GetInt64(COUNTERVALUE_FIELD_ID);
        }
    }


    public Types.DmExternalScriptExecutionStatsDataType ToDataObject()
    {
        return new Types.DmExternalScriptExecutionStatsDataType(Language,
            CounterName,
            CounterValue);
    }

    public List<Types.DmExternalScriptExecutionStatsDataType> ToList()
    {
        var list = new List<Types.DmExternalScriptExecutionStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
