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

public class DmPalWaitStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_pal_wait_stats]";
    public const string TableName = "dm_pal_wait_stats";
    public const string ShortName = "dpws";
    public const string Sql = """
        SELECT
          dpws.[wait_type],
          dpws.[waiting_threads_count],
          dpws.[wait_time_ms],
          dpws.[max_wait_time_ms]
        FROM
          [sys].[dm_pal_wait_stats] dpws
        """;

    public const int WAITTYPE_FIELD_ID = 0;
    public const int WAITINGTHREADSCOUNT_FIELD_ID = 1;
    public const int WAITTIMEMS_FIELD_ID = 2;
    public const int MAXWAITTIMEMS_FIELD_ID = 3;


    public DmPalWaitStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmPalWaitStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmPalWaitStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string WaitType
    {
        get
        {
            return base.GetString(WAITTYPE_FIELD_ID);
        }
    }

    public long WaitingThreadsCount
    {
        get
        {
            return base.GetInt64(WAITINGTHREADSCOUNT_FIELD_ID);
        }
    }

    public long WaitTimeMs
    {
        get
        {
            return base.GetInt64(WAITTIMEMS_FIELD_ID);
        }
    }

    public long MaxWaitTimeMs
    {
        get
        {
            return base.GetInt64(MAXWAITTIMEMS_FIELD_ID);
        }
    }


    public Types.DmPalWaitStatsDataType ToDataObject()
    {
        return new Types.DmPalWaitStatsDataType(WaitType,
            WaitingThreadsCount,
            WaitTimeMs,
            MaxWaitTimeMs);
    }

    public List<Types.DmPalWaitStatsDataType> ToList()
    {
        var list = new List<Types.DmPalWaitStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
