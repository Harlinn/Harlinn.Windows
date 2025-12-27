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

public class DmDbExternalScriptExecutionStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_external_script_execution_stats]";
    public const string TableName = "dm_db_external_script_execution_stats";
    public const string ShortName = "ddeses";
    public const string Sql = """
        SELECT
          ddeses.[external_language_id],
          ddeses.[counter_name],
          ddeses.[counter_value]
        FROM
          [sys].[dm_db_external_script_execution_stats] ddeses
        """;

    public const int EXTERNALLANGUAGEID_FIELD_ID = 0;
    public const int COUNTERNAME_FIELD_ID = 1;
    public const int COUNTERVALUE_FIELD_ID = 2;


    public DmDbExternalScriptExecutionStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbExternalScriptExecutionStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbExternalScriptExecutionStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ExternalLanguageId
    {
        get
        {
            return base.GetInt32(EXTERNALLANGUAGEID_FIELD_ID);
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


    public Types.DmDbExternalScriptExecutionStatsDataType ToDataObject()
    {
        return new Types.DmDbExternalScriptExecutionStatsDataType(ExternalLanguageId,
            CounterName,
            CounterValue);
    }

    public List<Types.DmDbExternalScriptExecutionStatsDataType> ToList()
    {
        var list = new List<Types.DmDbExternalScriptExecutionStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
