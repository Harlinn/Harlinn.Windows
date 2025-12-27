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

public class DmExecQueryMemoryGrantsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_memory_grants]";
    public const string TableName = "dm_exec_query_memory_grants";
    public const string ShortName = "deqmg";
    public const string Sql = """
        SELECT
          deqmg.[session_id],
          deqmg.[request_id],
          deqmg.[scheduler_id],
          deqmg.[Dop],
          deqmg.[request_time],
          deqmg.[grant_time],
          deqmg.[requested_memory_kb],
          deqmg.[granted_memory_kb],
          deqmg.[required_memory_kb],
          deqmg.[used_memory_kb],
          deqmg.[max_used_memory_kb],
          deqmg.[query_cost],
          deqmg.[timeout_sec],
          deqmg.[resource_semaphore_id],
          deqmg.[queue_id],
          deqmg.[wait_order],
          deqmg.[is_next_candidate],
          deqmg.[wait_time_ms],
          deqmg.[plan_handle],
          deqmg.[sql_handle],
          deqmg.[group_id],
          deqmg.[pool_id],
          deqmg.[is_small],
          deqmg.[ideal_memory_kb],
          deqmg.[reserved_worker_count],
          deqmg.[used_worker_count],
          deqmg.[max_used_worker_count],
          deqmg.[reserved_node_bitmap]
        FROM
          [sys].[dm_exec_query_memory_grants] deqmg
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int REQUESTID_FIELD_ID = 1;
    public const int SCHEDULERID_FIELD_ID = 2;
    public const int DOP_FIELD_ID = 3;
    public const int REQUESTTIME_FIELD_ID = 4;
    public const int GRANTTIME_FIELD_ID = 5;
    public const int REQUESTEDMEMORYKB_FIELD_ID = 6;
    public const int GRANTEDMEMORYKB_FIELD_ID = 7;
    public const int REQUIREDMEMORYKB_FIELD_ID = 8;
    public const int USEDMEMORYKB_FIELD_ID = 9;
    public const int MAXUSEDMEMORYKB_FIELD_ID = 10;
    public const int QUERYCOST_FIELD_ID = 11;
    public const int TIMEOUTSEC_FIELD_ID = 12;
    public const int RESOURCESEMAPHOREID_FIELD_ID = 13;
    public const int QUEUEID_FIELD_ID = 14;
    public const int WAITORDER_FIELD_ID = 15;
    public const int ISNEXTCANDIDATE_FIELD_ID = 16;
    public const int WAITTIMEMS_FIELD_ID = 17;
    public const int PLANHANDLE_FIELD_ID = 18;
    public const int SQLHANDLE_FIELD_ID = 19;
    public const int GROUPID_FIELD_ID = 20;
    public const int POOLID_FIELD_ID = 21;
    public const int ISSMALL_FIELD_ID = 22;
    public const int IDEALMEMORYKB_FIELD_ID = 23;
    public const int RESERVEDWORKERCOUNT_FIELD_ID = 24;
    public const int USEDWORKERCOUNT_FIELD_ID = 25;
    public const int MAXUSEDWORKERCOUNT_FIELD_ID = 26;
    public const int RESERVEDNODEBITMAP_FIELD_ID = 27;


    public DmExecQueryMemoryGrantsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryMemoryGrantsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryMemoryGrantsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
        }
    }

    public int? RequestId
    {
        get
        {
            return base.GetNullableInt32(REQUESTID_FIELD_ID);
        }
    }

    public int? SchedulerId
    {
        get
        {
            return base.GetNullableInt32(SCHEDULERID_FIELD_ID);
        }
    }

    public short? Dop
    {
        get
        {
            return base.GetNullableInt16(DOP_FIELD_ID);
        }
    }

    public DateTime? RequestTime
    {
        get
        {
            return base.GetNullableDateTime(REQUESTTIME_FIELD_ID);
        }
    }

    public DateTime? GrantTime
    {
        get
        {
            return base.GetNullableDateTime(GRANTTIME_FIELD_ID);
        }
    }

    public long? RequestedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(REQUESTEDMEMORYKB_FIELD_ID);
        }
    }

    public long? GrantedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(GRANTEDMEMORYKB_FIELD_ID);
        }
    }

    public long? RequiredMemoryKb
    {
        get
        {
            return base.GetNullableInt64(REQUIREDMEMORYKB_FIELD_ID);
        }
    }

    public long? UsedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(USEDMEMORYKB_FIELD_ID);
        }
    }

    public long? MaxUsedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(MAXUSEDMEMORYKB_FIELD_ID);
        }
    }

    public double? QueryCost
    {
        get
        {
            return base.GetNullableDouble(QUERYCOST_FIELD_ID);
        }
    }

    public int? TimeoutSec
    {
        get
        {
            return base.GetNullableInt32(TIMEOUTSEC_FIELD_ID);
        }
    }

    public short? ResourceSemaphoreId
    {
        get
        {
            return base.GetNullableInt16(RESOURCESEMAPHOREID_FIELD_ID);
        }
    }

    public short? QueueId
    {
        get
        {
            return base.GetNullableInt16(QUEUEID_FIELD_ID);
        }
    }

    public int? WaitOrder
    {
        get
        {
            return base.GetNullableInt32(WAITORDER_FIELD_ID);
        }
    }

    public bool? IsNextCandidate
    {
        get
        {
            return base.GetNullableBoolean(ISNEXTCANDIDATE_FIELD_ID);
        }
    }

    public long? WaitTimeMs
    {
        get
        {
            return base.GetNullableInt64(WAITTIMEMS_FIELD_ID);
        }
    }

    public byte[]? PlanHandle
    {
        get
        {
            return base.GetNullableBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public byte[]? SqlHandle
    {
        get
        {
            return base.GetNullableBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public int? GroupId
    {
        get
        {
            return base.GetNullableInt32(GROUPID_FIELD_ID);
        }
    }

    public int? PoolId
    {
        get
        {
            return base.GetNullableInt32(POOLID_FIELD_ID);
        }
    }

    public bool? IsSmall
    {
        get
        {
            return base.GetNullableBoolean(ISSMALL_FIELD_ID);
        }
    }

    public long? IdealMemoryKb
    {
        get
        {
            return base.GetNullableInt64(IDEALMEMORYKB_FIELD_ID);
        }
    }

    public int? ReservedWorkerCount
    {
        get
        {
            return base.GetNullableInt32(RESERVEDWORKERCOUNT_FIELD_ID);
        }
    }

    public int? UsedWorkerCount
    {
        get
        {
            return base.GetNullableInt32(USEDWORKERCOUNT_FIELD_ID);
        }
    }

    public int? MaxUsedWorkerCount
    {
        get
        {
            return base.GetNullableInt32(MAXUSEDWORKERCOUNT_FIELD_ID);
        }
    }

    public long? ReservedNodeBitmap
    {
        get
        {
            return base.GetNullableInt64(RESERVEDNODEBITMAP_FIELD_ID);
        }
    }


    public Types.DmExecQueryMemoryGrantsDataType ToDataObject()
    {
        return new Types.DmExecQueryMemoryGrantsDataType(SessionId,
            RequestId,
            SchedulerId,
            Dop,
            RequestTime,
            GrantTime,
            RequestedMemoryKb,
            GrantedMemoryKb,
            RequiredMemoryKb,
            UsedMemoryKb,
            MaxUsedMemoryKb,
            QueryCost,
            TimeoutSec,
            ResourceSemaphoreId,
            QueueId,
            WaitOrder,
            IsNextCandidate,
            WaitTimeMs,
            PlanHandle,
            SqlHandle,
            GroupId,
            PoolId,
            IsSmall,
            IdealMemoryKb,
            ReservedWorkerCount,
            UsedWorkerCount,
            MaxUsedWorkerCount,
            ReservedNodeBitmap);
    }

    public List<Types.DmExecQueryMemoryGrantsDataType> ToList()
    {
        var list = new List<Types.DmExecQueryMemoryGrantsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
