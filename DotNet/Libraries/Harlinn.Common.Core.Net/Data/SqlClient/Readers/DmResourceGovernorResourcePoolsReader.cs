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

public class DmResourceGovernorResourcePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_resource_pools]";
    public const string TableName = "dm_resource_governor_resource_pools";
    public const string ShortName = "drgrp";
    public const string Sql = """
        SELECT
          drgrp.[pool_id],
          drgrp.[Name],
          drgrp.[statistics_start_time],
          drgrp.[total_cpu_usage_ms],
          drgrp.[cache_memory_kb],
          drgrp.[compile_memory_kb],
          drgrp.[used_memgrant_kb],
          drgrp.[total_memgrant_count],
          drgrp.[total_memgrant_timeout_count],
          drgrp.[active_memgrant_count],
          drgrp.[active_memgrant_kb],
          drgrp.[memgrant_waiter_count],
          drgrp.[max_memory_kb],
          drgrp.[used_memory_kb],
          drgrp.[target_memory_kb],
          drgrp.[out_of_memory_count],
          drgrp.[min_cpu_percent],
          drgrp.[max_cpu_percent],
          drgrp.[min_memory_percent],
          drgrp.[max_memory_percent],
          drgrp.[cap_cpu_percent],
          drgrp.[min_iops_per_volume],
          drgrp.[max_iops_per_volume],
          drgrp.[read_io_queued_total],
          drgrp.[read_io_issued_total],
          drgrp.[read_io_completed_total],
          drgrp.[read_io_throttled_total],
          drgrp.[read_bytes_total],
          drgrp.[read_io_stall_total_ms],
          drgrp.[read_io_stall_queued_ms],
          drgrp.[write_io_queued_total],
          drgrp.[write_io_issued_total],
          drgrp.[write_io_completed_total],
          drgrp.[write_io_throttled_total],
          drgrp.[write_bytes_total],
          drgrp.[write_io_stall_total_ms],
          drgrp.[write_io_stall_queued_ms],
          drgrp.[io_issue_violations_total],
          drgrp.[io_issue_delay_total_ms],
          drgrp.[io_issue_ahead_total_ms],
          drgrp.[reserved_io_limited_by_volume_total],
          drgrp.[io_issue_delay_non_throttled_total_ms],
          drgrp.[total_cpu_delayed_ms],
          drgrp.[total_cpu_active_ms],
          drgrp.[total_cpu_violation_delay_ms],
          drgrp.[total_cpu_violation_sec],
          drgrp.[total_cpu_usage_preemptive_ms]
        FROM
          [sys].[dm_resource_governor_resource_pools] drgrp
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int STATISTICSSTARTTIME_FIELD_ID = 2;
    public const int TOTALCPUUSAGEMS_FIELD_ID = 3;
    public const int CACHEMEMORYKB_FIELD_ID = 4;
    public const int COMPILEMEMORYKB_FIELD_ID = 5;
    public const int USEDMEMGRANTKB_FIELD_ID = 6;
    public const int TOTALMEMGRANTCOUNT_FIELD_ID = 7;
    public const int TOTALMEMGRANTTIMEOUTCOUNT_FIELD_ID = 8;
    public const int ACTIVEMEMGRANTCOUNT_FIELD_ID = 9;
    public const int ACTIVEMEMGRANTKB_FIELD_ID = 10;
    public const int MEMGRANTWAITERCOUNT_FIELD_ID = 11;
    public const int MAXMEMORYKB_FIELD_ID = 12;
    public const int USEDMEMORYKB_FIELD_ID = 13;
    public const int TARGETMEMORYKB_FIELD_ID = 14;
    public const int OUTOFMEMORYCOUNT_FIELD_ID = 15;
    public const int MINCPUPERCENT_FIELD_ID = 16;
    public const int MAXCPUPERCENT_FIELD_ID = 17;
    public const int MINMEMORYPERCENT_FIELD_ID = 18;
    public const int MAXMEMORYPERCENT_FIELD_ID = 19;
    public const int CAPCPUPERCENT_FIELD_ID = 20;
    public const int MINIOPSPERVOLUME_FIELD_ID = 21;
    public const int MAXIOPSPERVOLUME_FIELD_ID = 22;
    public const int READIOQUEUEDTOTAL_FIELD_ID = 23;
    public const int READIOISSUEDTOTAL_FIELD_ID = 24;
    public const int READIOCOMPLETEDTOTAL_FIELD_ID = 25;
    public const int READIOTHROTTLEDTOTAL_FIELD_ID = 26;
    public const int READBYTESTOTAL_FIELD_ID = 27;
    public const int READIOSTALLTOTALMS_FIELD_ID = 28;
    public const int READIOSTALLQUEUEDMS_FIELD_ID = 29;
    public const int WRITEIOQUEUEDTOTAL_FIELD_ID = 30;
    public const int WRITEIOISSUEDTOTAL_FIELD_ID = 31;
    public const int WRITEIOCOMPLETEDTOTAL_FIELD_ID = 32;
    public const int WRITEIOTHROTTLEDTOTAL_FIELD_ID = 33;
    public const int WRITEBYTESTOTAL_FIELD_ID = 34;
    public const int WRITEIOSTALLTOTALMS_FIELD_ID = 35;
    public const int WRITEIOSTALLQUEUEDMS_FIELD_ID = 36;
    public const int IOISSUEVIOLATIONSTOTAL_FIELD_ID = 37;
    public const int IOISSUEDELAYTOTALMS_FIELD_ID = 38;
    public const int IOISSUEAHEADTOTALMS_FIELD_ID = 39;
    public const int RESERVEDIOLIMITEDBYVOLUMETOTAL_FIELD_ID = 40;
    public const int IOISSUEDELAYNONTHROTTLEDTOTALMS_FIELD_ID = 41;
    public const int TOTALCPUDELAYEDMS_FIELD_ID = 42;
    public const int TOTALCPUACTIVEMS_FIELD_ID = 43;
    public const int TOTALCPUVIOLATIONDELAYMS_FIELD_ID = 44;
    public const int TOTALCPUVIOLATIONSEC_FIELD_ID = 45;
    public const int TOTALCPUUSAGEPREEMPTIVEMS_FIELD_ID = 46;


    public DmResourceGovernorResourcePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime StatisticsStartTime
    {
        get
        {
            return base.GetDateTime(STATISTICSSTARTTIME_FIELD_ID);
        }
    }

    public long TotalCpuUsageMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSAGEMS_FIELD_ID);
        }
    }

    public long CacheMemoryKb
    {
        get
        {
            return base.GetInt64(CACHEMEMORYKB_FIELD_ID);
        }
    }

    public long CompileMemoryKb
    {
        get
        {
            return base.GetInt64(COMPILEMEMORYKB_FIELD_ID);
        }
    }

    public long UsedMemgrantKb
    {
        get
        {
            return base.GetInt64(USEDMEMGRANTKB_FIELD_ID);
        }
    }

    public long TotalMemgrantCount
    {
        get
        {
            return base.GetInt64(TOTALMEMGRANTCOUNT_FIELD_ID);
        }
    }

    public long TotalMemgrantTimeoutCount
    {
        get
        {
            return base.GetInt64(TOTALMEMGRANTTIMEOUTCOUNT_FIELD_ID);
        }
    }

    public int ActiveMemgrantCount
    {
        get
        {
            return base.GetInt32(ACTIVEMEMGRANTCOUNT_FIELD_ID);
        }
    }

    public long ActiveMemgrantKb
    {
        get
        {
            return base.GetInt64(ACTIVEMEMGRANTKB_FIELD_ID);
        }
    }

    public int MemgrantWaiterCount
    {
        get
        {
            return base.GetInt32(MEMGRANTWAITERCOUNT_FIELD_ID);
        }
    }

    public long MaxMemoryKb
    {
        get
        {
            return base.GetInt64(MAXMEMORYKB_FIELD_ID);
        }
    }

    public long UsedMemoryKb
    {
        get
        {
            return base.GetInt64(USEDMEMORYKB_FIELD_ID);
        }
    }

    public long TargetMemoryKb
    {
        get
        {
            return base.GetInt64(TARGETMEMORYKB_FIELD_ID);
        }
    }

    public long OutOfMemoryCount
    {
        get
        {
            return base.GetInt64(OUTOFMEMORYCOUNT_FIELD_ID);
        }
    }

    public int MinCpuPercent
    {
        get
        {
            return base.GetInt32(MINCPUPERCENT_FIELD_ID);
        }
    }

    public int MaxCpuPercent
    {
        get
        {
            return base.GetInt32(MAXCPUPERCENT_FIELD_ID);
        }
    }

    public int MinMemoryPercent
    {
        get
        {
            return base.GetInt32(MINMEMORYPERCENT_FIELD_ID);
        }
    }

    public int MaxMemoryPercent
    {
        get
        {
            return base.GetInt32(MAXMEMORYPERCENT_FIELD_ID);
        }
    }

    public int CapCpuPercent
    {
        get
        {
            return base.GetInt32(CAPCPUPERCENT_FIELD_ID);
        }
    }

    public int? MinIopsPerVolume
    {
        get
        {
            return base.GetNullableInt32(MINIOPSPERVOLUME_FIELD_ID);
        }
    }

    public int? MaxIopsPerVolume
    {
        get
        {
            return base.GetNullableInt32(MAXIOPSPERVOLUME_FIELD_ID);
        }
    }

    public int? ReadIoQueuedTotal
    {
        get
        {
            return base.GetNullableInt32(READIOQUEUEDTOTAL_FIELD_ID);
        }
    }

    public int? ReadIoIssuedTotal
    {
        get
        {
            return base.GetNullableInt32(READIOISSUEDTOTAL_FIELD_ID);
        }
    }

    public int ReadIoCompletedTotal
    {
        get
        {
            return base.GetInt32(READIOCOMPLETEDTOTAL_FIELD_ID);
        }
    }

    public int? ReadIoThrottledTotal
    {
        get
        {
            return base.GetNullableInt32(READIOTHROTTLEDTOTAL_FIELD_ID);
        }
    }

    public long ReadBytesTotal
    {
        get
        {
            return base.GetInt64(READBYTESTOTAL_FIELD_ID);
        }
    }

    public long ReadIoStallTotalMs
    {
        get
        {
            return base.GetInt64(READIOSTALLTOTALMS_FIELD_ID);
        }
    }

    public long? ReadIoStallQueuedMs
    {
        get
        {
            return base.GetNullableInt64(READIOSTALLQUEUEDMS_FIELD_ID);
        }
    }

    public int? WriteIoQueuedTotal
    {
        get
        {
            return base.GetNullableInt32(WRITEIOQUEUEDTOTAL_FIELD_ID);
        }
    }

    public int? WriteIoIssuedTotal
    {
        get
        {
            return base.GetNullableInt32(WRITEIOISSUEDTOTAL_FIELD_ID);
        }
    }

    public int WriteIoCompletedTotal
    {
        get
        {
            return base.GetInt32(WRITEIOCOMPLETEDTOTAL_FIELD_ID);
        }
    }

    public int? WriteIoThrottledTotal
    {
        get
        {
            return base.GetNullableInt32(WRITEIOTHROTTLEDTOTAL_FIELD_ID);
        }
    }

    public long WriteBytesTotal
    {
        get
        {
            return base.GetInt64(WRITEBYTESTOTAL_FIELD_ID);
        }
    }

    public long WriteIoStallTotalMs
    {
        get
        {
            return base.GetInt64(WRITEIOSTALLTOTALMS_FIELD_ID);
        }
    }

    public long? WriteIoStallQueuedMs
    {
        get
        {
            return base.GetNullableInt64(WRITEIOSTALLQUEUEDMS_FIELD_ID);
        }
    }

    public int? IoIssueViolationsTotal
    {
        get
        {
            return base.GetNullableInt32(IOISSUEVIOLATIONSTOTAL_FIELD_ID);
        }
    }

    public long? IoIssueDelayTotalMs
    {
        get
        {
            return base.GetNullableInt64(IOISSUEDELAYTOTALMS_FIELD_ID);
        }
    }

    public long? IoIssueAheadTotalMs
    {
        get
        {
            return base.GetNullableInt64(IOISSUEAHEADTOTALMS_FIELD_ID);
        }
    }

    public int? ReservedIoLimitedByVolumeTotal
    {
        get
        {
            return base.GetNullableInt32(RESERVEDIOLIMITEDBYVOLUMETOTAL_FIELD_ID);
        }
    }

    public long? IoIssueDelayNonThrottledTotalMs
    {
        get
        {
            return base.GetNullableInt64(IOISSUEDELAYNONTHROTTLEDTOTALMS_FIELD_ID);
        }
    }

    public long TotalCpuDelayedMs
    {
        get
        {
            return base.GetInt64(TOTALCPUDELAYEDMS_FIELD_ID);
        }
    }

    public long TotalCpuActiveMs
    {
        get
        {
            return base.GetInt64(TOTALCPUACTIVEMS_FIELD_ID);
        }
    }

    public long TotalCpuViolationDelayMs
    {
        get
        {
            return base.GetInt64(TOTALCPUVIOLATIONDELAYMS_FIELD_ID);
        }
    }

    public long TotalCpuViolationSec
    {
        get
        {
            return base.GetInt64(TOTALCPUVIOLATIONSEC_FIELD_ID);
        }
    }

    public long TotalCpuUsagePreemptiveMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSAGEPREEMPTIVEMS_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorResourcePoolsDataType ToDataObject()
    {
        return new Types.DmResourceGovernorResourcePoolsDataType(PoolId,
            Name,
            StatisticsStartTime,
            TotalCpuUsageMs,
            CacheMemoryKb,
            CompileMemoryKb,
            UsedMemgrantKb,
            TotalMemgrantCount,
            TotalMemgrantTimeoutCount,
            ActiveMemgrantCount,
            ActiveMemgrantKb,
            MemgrantWaiterCount,
            MaxMemoryKb,
            UsedMemoryKb,
            TargetMemoryKb,
            OutOfMemoryCount,
            MinCpuPercent,
            MaxCpuPercent,
            MinMemoryPercent,
            MaxMemoryPercent,
            CapCpuPercent,
            MinIopsPerVolume,
            MaxIopsPerVolume,
            ReadIoQueuedTotal,
            ReadIoIssuedTotal,
            ReadIoCompletedTotal,
            ReadIoThrottledTotal,
            ReadBytesTotal,
            ReadIoStallTotalMs,
            ReadIoStallQueuedMs,
            WriteIoQueuedTotal,
            WriteIoIssuedTotal,
            WriteIoCompletedTotal,
            WriteIoThrottledTotal,
            WriteBytesTotal,
            WriteIoStallTotalMs,
            WriteIoStallQueuedMs,
            IoIssueViolationsTotal,
            IoIssueDelayTotalMs,
            IoIssueAheadTotalMs,
            ReservedIoLimitedByVolumeTotal,
            IoIssueDelayNonThrottledTotalMs,
            TotalCpuDelayedMs,
            TotalCpuActiveMs,
            TotalCpuViolationDelayMs,
            TotalCpuViolationSec,
            TotalCpuUsagePreemptiveMs);
    }

    public List<Types.DmResourceGovernorResourcePoolsDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorResourcePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
