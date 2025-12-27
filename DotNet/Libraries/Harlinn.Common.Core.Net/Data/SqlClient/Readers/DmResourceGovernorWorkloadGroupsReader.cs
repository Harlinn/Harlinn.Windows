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

public class DmResourceGovernorWorkloadGroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_workload_groups]";
    public const string TableName = "dm_resource_governor_workload_groups";
    public const string ShortName = "drgwg";
    public const string Sql = """
        SELECT
          drgwg.[group_id],
          drgwg.[Name],
          drgwg.[pool_id],
          drgwg.[external_pool_id],
          drgwg.[statistics_start_time],
          drgwg.[total_request_count],
          drgwg.[total_queued_request_count],
          drgwg.[active_request_count],
          drgwg.[queued_request_count],
          drgwg.[total_cpu_limit_violation_count],
          drgwg.[total_cpu_usage_ms],
          drgwg.[max_request_cpu_time_ms],
          drgwg.[blocked_task_count],
          drgwg.[total_lock_wait_count],
          drgwg.[total_lock_wait_time_ms],
          drgwg.[total_query_optimization_count],
          drgwg.[total_suboptimal_plan_generation_count],
          drgwg.[total_reduced_memgrant_count],
          drgwg.[max_request_grant_memory_kb],
          drgwg.[active_parallel_thread_count],
          drgwg.[Importance],
          drgwg.[request_max_memory_grant_percent],
          drgwg.[request_max_cpu_time_sec],
          drgwg.[request_memory_grant_timeout_sec],
          drgwg.[group_max_requests],
          drgwg.[max_dop],
          drgwg.[effective_max_dop],
          drgwg.[total_cpu_usage_preemptive_ms],
          drgwg.[request_max_memory_grant_percent_numeric]
        FROM
          [sys].[dm_resource_governor_workload_groups] drgwg
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int POOLID_FIELD_ID = 2;
    public const int EXTERNALPOOLID_FIELD_ID = 3;
    public const int STATISTICSSTARTTIME_FIELD_ID = 4;
    public const int TOTALREQUESTCOUNT_FIELD_ID = 5;
    public const int TOTALQUEUEDREQUESTCOUNT_FIELD_ID = 6;
    public const int ACTIVEREQUESTCOUNT_FIELD_ID = 7;
    public const int QUEUEDREQUESTCOUNT_FIELD_ID = 8;
    public const int TOTALCPULIMITVIOLATIONCOUNT_FIELD_ID = 9;
    public const int TOTALCPUUSAGEMS_FIELD_ID = 10;
    public const int MAXREQUESTCPUTIMEMS_FIELD_ID = 11;
    public const int BLOCKEDTASKCOUNT_FIELD_ID = 12;
    public const int TOTALLOCKWAITCOUNT_FIELD_ID = 13;
    public const int TOTALLOCKWAITTIMEMS_FIELD_ID = 14;
    public const int TOTALQUERYOPTIMIZATIONCOUNT_FIELD_ID = 15;
    public const int TOTALSUBOPTIMALPLANGENERATIONCOUNT_FIELD_ID = 16;
    public const int TOTALREDUCEDMEMGRANTCOUNT_FIELD_ID = 17;
    public const int MAXREQUESTGRANTMEMORYKB_FIELD_ID = 18;
    public const int ACTIVEPARALLELTHREADCOUNT_FIELD_ID = 19;
    public const int IMPORTANCE_FIELD_ID = 20;
    public const int REQUESTMAXMEMORYGRANTPERCENT_FIELD_ID = 21;
    public const int REQUESTMAXCPUTIMESEC_FIELD_ID = 22;
    public const int REQUESTMEMORYGRANTTIMEOUTSEC_FIELD_ID = 23;
    public const int GROUPMAXREQUESTS_FIELD_ID = 24;
    public const int MAXDOP_FIELD_ID = 25;
    public const int EFFECTIVEMAXDOP_FIELD_ID = 26;
    public const int TOTALCPUUSAGEPREEMPTIVEMS_FIELD_ID = 27;
    public const int REQUESTMAXMEMORYGRANTPERCENTNUMERIC_FIELD_ID = 28;


    public DmResourceGovernorWorkloadGroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorWorkloadGroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorWorkloadGroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int GroupId
    {
        get
        {
            return base.GetInt32(GROUPID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public int? ExternalPoolId
    {
        get
        {
            return base.GetNullableInt32(EXTERNALPOOLID_FIELD_ID);
        }
    }

    public DateTime StatisticsStartTime
    {
        get
        {
            return base.GetDateTime(STATISTICSSTARTTIME_FIELD_ID);
        }
    }

    public long TotalRequestCount
    {
        get
        {
            return base.GetInt64(TOTALREQUESTCOUNT_FIELD_ID);
        }
    }

    public long TotalQueuedRequestCount
    {
        get
        {
            return base.GetInt64(TOTALQUEUEDREQUESTCOUNT_FIELD_ID);
        }
    }

    public int ActiveRequestCount
    {
        get
        {
            return base.GetInt32(ACTIVEREQUESTCOUNT_FIELD_ID);
        }
    }

    public int QueuedRequestCount
    {
        get
        {
            return base.GetInt32(QUEUEDREQUESTCOUNT_FIELD_ID);
        }
    }

    public long TotalCpuLimitViolationCount
    {
        get
        {
            return base.GetInt64(TOTALCPULIMITVIOLATIONCOUNT_FIELD_ID);
        }
    }

    public long TotalCpuUsageMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSAGEMS_FIELD_ID);
        }
    }

    public long MaxRequestCpuTimeMs
    {
        get
        {
            return base.GetInt64(MAXREQUESTCPUTIMEMS_FIELD_ID);
        }
    }

    public int BlockedTaskCount
    {
        get
        {
            return base.GetInt32(BLOCKEDTASKCOUNT_FIELD_ID);
        }
    }

    public long TotalLockWaitCount
    {
        get
        {
            return base.GetInt64(TOTALLOCKWAITCOUNT_FIELD_ID);
        }
    }

    public long TotalLockWaitTimeMs
    {
        get
        {
            return base.GetInt64(TOTALLOCKWAITTIMEMS_FIELD_ID);
        }
    }

    public long TotalQueryOptimizationCount
    {
        get
        {
            return base.GetInt64(TOTALQUERYOPTIMIZATIONCOUNT_FIELD_ID);
        }
    }

    public long TotalSuboptimalPlanGenerationCount
    {
        get
        {
            return base.GetInt64(TOTALSUBOPTIMALPLANGENERATIONCOUNT_FIELD_ID);
        }
    }

    public long TotalReducedMemgrantCount
    {
        get
        {
            return base.GetInt64(TOTALREDUCEDMEMGRANTCOUNT_FIELD_ID);
        }
    }

    public long MaxRequestGrantMemoryKb
    {
        get
        {
            return base.GetInt64(MAXREQUESTGRANTMEMORYKB_FIELD_ID);
        }
    }

    public long ActiveParallelThreadCount
    {
        get
        {
            return base.GetInt64(ACTIVEPARALLELTHREADCOUNT_FIELD_ID);
        }
    }

    public string Importance
    {
        get
        {
            return base.GetString(IMPORTANCE_FIELD_ID);
        }
    }

    public int RequestMaxMemoryGrantPercent
    {
        get
        {
            return base.GetInt32(REQUESTMAXMEMORYGRANTPERCENT_FIELD_ID);
        }
    }

    public int RequestMaxCpuTimeSec
    {
        get
        {
            return base.GetInt32(REQUESTMAXCPUTIMESEC_FIELD_ID);
        }
    }

    public int RequestMemoryGrantTimeoutSec
    {
        get
        {
            return base.GetInt32(REQUESTMEMORYGRANTTIMEOUTSEC_FIELD_ID);
        }
    }

    public int GroupMaxRequests
    {
        get
        {
            return base.GetInt32(GROUPMAXREQUESTS_FIELD_ID);
        }
    }

    public int MaxDop
    {
        get
        {
            return base.GetInt32(MAXDOP_FIELD_ID);
        }
    }

    public int EffectiveMaxDop
    {
        get
        {
            return base.GetInt32(EFFECTIVEMAXDOP_FIELD_ID);
        }
    }

    public long TotalCpuUsagePreemptiveMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSAGEPREEMPTIVEMS_FIELD_ID);
        }
    }

    public double RequestMaxMemoryGrantPercentNumeric
    {
        get
        {
            return base.GetDouble(REQUESTMAXMEMORYGRANTPERCENTNUMERIC_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorWorkloadGroupsDataType ToDataObject()
    {
        return new Types.DmResourceGovernorWorkloadGroupsDataType(GroupId,
            Name,
            PoolId,
            ExternalPoolId,
            StatisticsStartTime,
            TotalRequestCount,
            TotalQueuedRequestCount,
            ActiveRequestCount,
            QueuedRequestCount,
            TotalCpuLimitViolationCount,
            TotalCpuUsageMs,
            MaxRequestCpuTimeMs,
            BlockedTaskCount,
            TotalLockWaitCount,
            TotalLockWaitTimeMs,
            TotalQueryOptimizationCount,
            TotalSuboptimalPlanGenerationCount,
            TotalReducedMemgrantCount,
            MaxRequestGrantMemoryKb,
            ActiveParallelThreadCount,
            Importance,
            RequestMaxMemoryGrantPercent,
            RequestMaxCpuTimeSec,
            RequestMemoryGrantTimeoutSec,
            GroupMaxRequests,
            MaxDop,
            EffectiveMaxDop,
            TotalCpuUsagePreemptiveMs,
            RequestMaxMemoryGrantPercentNumeric);
    }

    public List<Types.DmResourceGovernorWorkloadGroupsDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorWorkloadGroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
