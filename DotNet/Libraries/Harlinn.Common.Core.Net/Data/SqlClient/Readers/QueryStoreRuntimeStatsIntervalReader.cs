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

public class QueryStoreRuntimeStatsIntervalReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_runtime_stats_interval]";
    public const string TableName = "query_store_runtime_stats_interval";
    public const string ShortName = "qsrsi";
    public const string Sql = """
        SELECT
          qsrsi.[runtime_stats_interval_id],
          qsrsi.[start_time],
          qsrsi.[end_time],
          qsrsi.[Comment]
        FROM
          [sys].[query_store_runtime_stats_interval] qsrsi
        """;

    public const int RUNTIMESTATSINTERVALID_FIELD_ID = 0;
    public const int STARTTIME_FIELD_ID = 1;
    public const int ENDTIME_FIELD_ID = 2;
    public const int COMMENT_FIELD_ID = 3;


    public QueryStoreRuntimeStatsIntervalReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStoreRuntimeStatsIntervalReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStoreRuntimeStatsIntervalReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long RuntimeStatsIntervalId
    {
        get
        {
            return base.GetInt64(RUNTIMESTATSINTERVALID_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime EndTime
    {
        get
        {
            return base.GetDateTime(ENDTIME_FIELD_ID);
        }
    }

    public string? Comment
    {
        get
        {
            return base.GetNullableString(COMMENT_FIELD_ID);
        }
    }


    public Types.QueryStoreRuntimeStatsIntervalDataType ToDataObject()
    {
        return new Types.QueryStoreRuntimeStatsIntervalDataType(RuntimeStatsIntervalId,
            StartTime,
            EndTime,
            Comment);
    }

    public List<Types.QueryStoreRuntimeStatsIntervalDataType> ToList()
    {
        var list = new List<Types.QueryStoreRuntimeStatsIntervalDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
