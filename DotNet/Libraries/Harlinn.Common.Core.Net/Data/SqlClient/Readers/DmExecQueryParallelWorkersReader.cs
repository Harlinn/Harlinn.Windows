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

public class DmExecQueryParallelWorkersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_parallel_workers]";
    public const string TableName = "dm_exec_query_parallel_workers";
    public const string ShortName = "deqpw";
    public const string Sql = """
        SELECT
          deqpw.[node_id],
          deqpw.[scheduler_count],
          deqpw.[max_worker_count],
          deqpw.[reserved_worker_count],
          deqpw.[free_worker_count],
          deqpw.[used_worker_count]
        FROM
          [sys].[dm_exec_query_parallel_workers] deqpw
        """;

    public const int NODEID_FIELD_ID = 0;
    public const int SCHEDULERCOUNT_FIELD_ID = 1;
    public const int MAXWORKERCOUNT_FIELD_ID = 2;
    public const int RESERVEDWORKERCOUNT_FIELD_ID = 3;
    public const int FREEWORKERCOUNT_FIELD_ID = 4;
    public const int USEDWORKERCOUNT_FIELD_ID = 5;


    public DmExecQueryParallelWorkersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryParallelWorkersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryParallelWorkersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int NodeId
    {
        get
        {
            return base.GetInt32(NODEID_FIELD_ID);
        }
    }

    public int SchedulerCount
    {
        get
        {
            return base.GetInt32(SCHEDULERCOUNT_FIELD_ID);
        }
    }

    public int MaxWorkerCount
    {
        get
        {
            return base.GetInt32(MAXWORKERCOUNT_FIELD_ID);
        }
    }

    public int ReservedWorkerCount
    {
        get
        {
            return base.GetInt32(RESERVEDWORKERCOUNT_FIELD_ID);
        }
    }

    public int FreeWorkerCount
    {
        get
        {
            return base.GetInt32(FREEWORKERCOUNT_FIELD_ID);
        }
    }

    public int UsedWorkerCount
    {
        get
        {
            return base.GetInt32(USEDWORKERCOUNT_FIELD_ID);
        }
    }


    public Types.DmExecQueryParallelWorkersDataType ToDataObject()
    {
        return new Types.DmExecQueryParallelWorkersDataType(NodeId,
            SchedulerCount,
            MaxWorkerCount,
            ReservedWorkerCount,
            FreeWorkerCount,
            UsedWorkerCount);
    }

    public List<Types.DmExecQueryParallelWorkersDataType> ToList()
    {
        var list = new List<Types.DmExecQueryParallelWorkersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
