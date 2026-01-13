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

public class DmExecSessionWaitStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_session_wait_stats]";
    public const string TableName = "dm_exec_session_wait_stats";
    public const string ShortName = "desws";
    public const string Sql = """
        SELECT
          desws.[session_id],
          desws.[wait_type],
          desws.[waiting_tasks_count],
          desws.[wait_time_ms],
          desws.[max_wait_time_ms],
          desws.[signal_wait_time_ms]
        FROM
          [sys].[dm_exec_session_wait_stats] desws
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int WAITTYPE_FIELD_ID = 1;
    public const int WAITINGTASKSCOUNT_FIELD_ID = 2;
    public const int WAITTIMEMS_FIELD_ID = 3;
    public const int MAXWAITTIMEMS_FIELD_ID = 4;
    public const int SIGNALWAITTIMEMS_FIELD_ID = 5;


    public DmExecSessionWaitStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecSessionWaitStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecSessionWaitStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short SessionId
    {
        get
        {
            return base.GetInt16(SESSIONID_FIELD_ID);
        }
    }

    public string WaitType
    {
        get
        {
            return base.GetString(WAITTYPE_FIELD_ID);
        }
    }

    public long WaitingTasksCount
    {
        get
        {
            return base.GetInt64(WAITINGTASKSCOUNT_FIELD_ID);
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

    public long SignalWaitTimeMs
    {
        get
        {
            return base.GetInt64(SIGNALWAITTIMEMS_FIELD_ID);
        }
    }


    public Types.DmExecSessionWaitStatsDataType ToDataObject()
    {
        return new Types.DmExecSessionWaitStatsDataType(SessionId,
            WaitType,
            WaitingTasksCount,
            WaitTimeMs,
            MaxWaitTimeMs,
            SignalWaitTimeMs);
    }

    public List<Types.DmExecSessionWaitStatsDataType> ToList()
    {
        var list = new List<Types.DmExecSessionWaitStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
