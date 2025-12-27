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

public class QueryStoreRuntimeStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_runtime_stats]";
    public const string TableName = "query_store_runtime_stats";
    public const string ShortName = "qsrs";
    public const string Sql = """
        SELECT
          qsrs.[runtime_stats_id],
          qsrs.[plan_id],
          qsrs.[runtime_stats_interval_id],
          qsrs.[execution_type],
          qsrs.[execution_type_desc],
          qsrs.[first_execution_time],
          qsrs.[last_execution_time],
          qsrs.[count_executions],
          qsrs.[avg_duration],
          qsrs.[last_duration],
          qsrs.[min_duration],
          qsrs.[max_duration],
          qsrs.[stdev_duration],
          qsrs.[avg_cpu_time],
          qsrs.[last_cpu_time],
          qsrs.[min_cpu_time],
          qsrs.[max_cpu_time],
          qsrs.[stdev_cpu_time],
          qsrs.[avg_logical_io_reads],
          qsrs.[last_logical_io_reads],
          qsrs.[min_logical_io_reads],
          qsrs.[max_logical_io_reads],
          qsrs.[stdev_logical_io_reads],
          qsrs.[avg_logical_io_writes],
          qsrs.[last_logical_io_writes],
          qsrs.[min_logical_io_writes],
          qsrs.[max_logical_io_writes],
          qsrs.[stdev_logical_io_writes],
          qsrs.[avg_physical_io_reads],
          qsrs.[last_physical_io_reads],
          qsrs.[min_physical_io_reads],
          qsrs.[max_physical_io_reads],
          qsrs.[stdev_physical_io_reads],
          qsrs.[avg_clr_time],
          qsrs.[last_clr_time],
          qsrs.[min_clr_time],
          qsrs.[max_clr_time],
          qsrs.[stdev_clr_time],
          qsrs.[avg_dop],
          qsrs.[last_dop],
          qsrs.[min_dop],
          qsrs.[max_dop],
          qsrs.[stdev_dop],
          qsrs.[avg_query_max_used_memory],
          qsrs.[last_query_max_used_memory],
          qsrs.[min_query_max_used_memory],
          qsrs.[max_query_max_used_memory],
          qsrs.[stdev_query_max_used_memory],
          qsrs.[avg_rowcount],
          qsrs.[last_rowcount],
          qsrs.[min_rowcount],
          qsrs.[max_rowcount],
          qsrs.[stdev_rowcount],
          qsrs.[avg_num_physical_io_reads],
          qsrs.[last_num_physical_io_reads],
          qsrs.[min_num_physical_io_reads],
          qsrs.[max_num_physical_io_reads],
          qsrs.[stdev_num_physical_io_reads],
          qsrs.[avg_log_bytes_used],
          qsrs.[last_log_bytes_used],
          qsrs.[min_log_bytes_used],
          qsrs.[max_log_bytes_used],
          qsrs.[stdev_log_bytes_used],
          qsrs.[avg_tempdb_space_used],
          qsrs.[last_tempdb_space_used],
          qsrs.[min_tempdb_space_used],
          qsrs.[max_tempdb_space_used],
          qsrs.[stdev_tempdb_space_used]
        FROM
          [sys].[query_store_runtime_stats] qsrs
        """;

    public const int RUNTIMESTATSID_FIELD_ID = 0;
    public const int PLANID_FIELD_ID = 1;
    public const int RUNTIMESTATSINTERVALID_FIELD_ID = 2;
    public const int EXECUTIONTYPE_FIELD_ID = 3;
    public const int EXECUTIONTYPEDESC_FIELD_ID = 4;
    public const int FIRSTEXECUTIONTIME_FIELD_ID = 5;
    public const int LASTEXECUTIONTIME_FIELD_ID = 6;
    public const int COUNTEXECUTIONS_FIELD_ID = 7;
    public const int AVGDURATION_FIELD_ID = 8;
    public const int LASTDURATION_FIELD_ID = 9;
    public const int MINDURATION_FIELD_ID = 10;
    public const int MAXDURATION_FIELD_ID = 11;
    public const int STDEVDURATION_FIELD_ID = 12;
    public const int AVGCPUTIME_FIELD_ID = 13;
    public const int LASTCPUTIME_FIELD_ID = 14;
    public const int MINCPUTIME_FIELD_ID = 15;
    public const int MAXCPUTIME_FIELD_ID = 16;
    public const int STDEVCPUTIME_FIELD_ID = 17;
    public const int AVGLOGICALIOREADS_FIELD_ID = 18;
    public const int LASTLOGICALIOREADS_FIELD_ID = 19;
    public const int MINLOGICALIOREADS_FIELD_ID = 20;
    public const int MAXLOGICALIOREADS_FIELD_ID = 21;
    public const int STDEVLOGICALIOREADS_FIELD_ID = 22;
    public const int AVGLOGICALIOWRITES_FIELD_ID = 23;
    public const int LASTLOGICALIOWRITES_FIELD_ID = 24;
    public const int MINLOGICALIOWRITES_FIELD_ID = 25;
    public const int MAXLOGICALIOWRITES_FIELD_ID = 26;
    public const int STDEVLOGICALIOWRITES_FIELD_ID = 27;
    public const int AVGPHYSICALIOREADS_FIELD_ID = 28;
    public const int LASTPHYSICALIOREADS_FIELD_ID = 29;
    public const int MINPHYSICALIOREADS_FIELD_ID = 30;
    public const int MAXPHYSICALIOREADS_FIELD_ID = 31;
    public const int STDEVPHYSICALIOREADS_FIELD_ID = 32;
    public const int AVGCLRTIME_FIELD_ID = 33;
    public const int LASTCLRTIME_FIELD_ID = 34;
    public const int MINCLRTIME_FIELD_ID = 35;
    public const int MAXCLRTIME_FIELD_ID = 36;
    public const int STDEVCLRTIME_FIELD_ID = 37;
    public const int AVGDOP_FIELD_ID = 38;
    public const int LASTDOP_FIELD_ID = 39;
    public const int MINDOP_FIELD_ID = 40;
    public const int MAXDOP_FIELD_ID = 41;
    public const int STDEVDOP_FIELD_ID = 42;
    public const int AVGQUERYMAXUSEDMEMORY_FIELD_ID = 43;
    public const int LASTQUERYMAXUSEDMEMORY_FIELD_ID = 44;
    public const int MINQUERYMAXUSEDMEMORY_FIELD_ID = 45;
    public const int MAXQUERYMAXUSEDMEMORY_FIELD_ID = 46;
    public const int STDEVQUERYMAXUSEDMEMORY_FIELD_ID = 47;
    public const int AVGROWCOUNT_FIELD_ID = 48;
    public const int LASTROWCOUNT_FIELD_ID = 49;
    public const int MINROWCOUNT_FIELD_ID = 50;
    public const int MAXROWCOUNT_FIELD_ID = 51;
    public const int STDEVROWCOUNT_FIELD_ID = 52;
    public const int AVGNUMPHYSICALIOREADS_FIELD_ID = 53;
    public const int LASTNUMPHYSICALIOREADS_FIELD_ID = 54;
    public const int MINNUMPHYSICALIOREADS_FIELD_ID = 55;
    public const int MAXNUMPHYSICALIOREADS_FIELD_ID = 56;
    public const int STDEVNUMPHYSICALIOREADS_FIELD_ID = 57;
    public const int AVGLOGBYTESUSED_FIELD_ID = 58;
    public const int LASTLOGBYTESUSED_FIELD_ID = 59;
    public const int MINLOGBYTESUSED_FIELD_ID = 60;
    public const int MAXLOGBYTESUSED_FIELD_ID = 61;
    public const int STDEVLOGBYTESUSED_FIELD_ID = 62;
    public const int AVGTEMPDBSPACEUSED_FIELD_ID = 63;
    public const int LASTTEMPDBSPACEUSED_FIELD_ID = 64;
    public const int MINTEMPDBSPACEUSED_FIELD_ID = 65;
    public const int MAXTEMPDBSPACEUSED_FIELD_ID = 66;
    public const int STDEVTEMPDBSPACEUSED_FIELD_ID = 67;


    public QueryStoreRuntimeStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStoreRuntimeStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStoreRuntimeStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long RuntimeStatsId
    {
        get
        {
            return base.GetInt64(RUNTIMESTATSID_FIELD_ID);
        }
    }

    public long PlanId
    {
        get
        {
            return base.GetInt64(PLANID_FIELD_ID);
        }
    }

    public long RuntimeStatsIntervalId
    {
        get
        {
            return base.GetInt64(RUNTIMESTATSINTERVALID_FIELD_ID);
        }
    }

    public byte ExecutionType
    {
        get
        {
            return base.GetByte(EXECUTIONTYPE_FIELD_ID);
        }
    }

    public string? ExecutionTypeDesc
    {
        get
        {
            return base.GetNullableString(EXECUTIONTYPEDESC_FIELD_ID);
        }
    }

    public DateTime FirstExecutionTime
    {
        get
        {
            return base.GetDateTime(FIRSTEXECUTIONTIME_FIELD_ID);
        }
    }

    public DateTime LastExecutionTime
    {
        get
        {
            return base.GetDateTime(LASTEXECUTIONTIME_FIELD_ID);
        }
    }

    public long CountExecutions
    {
        get
        {
            return base.GetInt64(COUNTEXECUTIONS_FIELD_ID);
        }
    }

    public double? AvgDuration
    {
        get
        {
            return base.GetNullableDouble(AVGDURATION_FIELD_ID);
        }
    }

    public long LastDuration
    {
        get
        {
            return base.GetInt64(LASTDURATION_FIELD_ID);
        }
    }

    public long MinDuration
    {
        get
        {
            return base.GetInt64(MINDURATION_FIELD_ID);
        }
    }

    public long MaxDuration
    {
        get
        {
            return base.GetInt64(MAXDURATION_FIELD_ID);
        }
    }

    public double? StdevDuration
    {
        get
        {
            return base.GetNullableDouble(STDEVDURATION_FIELD_ID);
        }
    }

    public double? AvgCpuTime
    {
        get
        {
            return base.GetNullableDouble(AVGCPUTIME_FIELD_ID);
        }
    }

    public long LastCpuTime
    {
        get
        {
            return base.GetInt64(LASTCPUTIME_FIELD_ID);
        }
    }

    public long MinCpuTime
    {
        get
        {
            return base.GetInt64(MINCPUTIME_FIELD_ID);
        }
    }

    public long MaxCpuTime
    {
        get
        {
            return base.GetInt64(MAXCPUTIME_FIELD_ID);
        }
    }

    public double? StdevCpuTime
    {
        get
        {
            return base.GetNullableDouble(STDEVCPUTIME_FIELD_ID);
        }
    }

    public double? AvgLogicalIoReads
    {
        get
        {
            return base.GetNullableDouble(AVGLOGICALIOREADS_FIELD_ID);
        }
    }

    public long LastLogicalIoReads
    {
        get
        {
            return base.GetInt64(LASTLOGICALIOREADS_FIELD_ID);
        }
    }

    public long MinLogicalIoReads
    {
        get
        {
            return base.GetInt64(MINLOGICALIOREADS_FIELD_ID);
        }
    }

    public long MaxLogicalIoReads
    {
        get
        {
            return base.GetInt64(MAXLOGICALIOREADS_FIELD_ID);
        }
    }

    public double? StdevLogicalIoReads
    {
        get
        {
            return base.GetNullableDouble(STDEVLOGICALIOREADS_FIELD_ID);
        }
    }

    public double? AvgLogicalIoWrites
    {
        get
        {
            return base.GetNullableDouble(AVGLOGICALIOWRITES_FIELD_ID);
        }
    }

    public long LastLogicalIoWrites
    {
        get
        {
            return base.GetInt64(LASTLOGICALIOWRITES_FIELD_ID);
        }
    }

    public long MinLogicalIoWrites
    {
        get
        {
            return base.GetInt64(MINLOGICALIOWRITES_FIELD_ID);
        }
    }

    public long MaxLogicalIoWrites
    {
        get
        {
            return base.GetInt64(MAXLOGICALIOWRITES_FIELD_ID);
        }
    }

    public double? StdevLogicalIoWrites
    {
        get
        {
            return base.GetNullableDouble(STDEVLOGICALIOWRITES_FIELD_ID);
        }
    }

    public double? AvgPhysicalIoReads
    {
        get
        {
            return base.GetNullableDouble(AVGPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long LastPhysicalIoReads
    {
        get
        {
            return base.GetInt64(LASTPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long MinPhysicalIoReads
    {
        get
        {
            return base.GetInt64(MINPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long MaxPhysicalIoReads
    {
        get
        {
            return base.GetInt64(MAXPHYSICALIOREADS_FIELD_ID);
        }
    }

    public double? StdevPhysicalIoReads
    {
        get
        {
            return base.GetNullableDouble(STDEVPHYSICALIOREADS_FIELD_ID);
        }
    }

    public double? AvgClrTime
    {
        get
        {
            return base.GetNullableDouble(AVGCLRTIME_FIELD_ID);
        }
    }

    public long LastClrTime
    {
        get
        {
            return base.GetInt64(LASTCLRTIME_FIELD_ID);
        }
    }

    public long MinClrTime
    {
        get
        {
            return base.GetInt64(MINCLRTIME_FIELD_ID);
        }
    }

    public long MaxClrTime
    {
        get
        {
            return base.GetInt64(MAXCLRTIME_FIELD_ID);
        }
    }

    public double? StdevClrTime
    {
        get
        {
            return base.GetNullableDouble(STDEVCLRTIME_FIELD_ID);
        }
    }

    public double? AvgDop
    {
        get
        {
            return base.GetNullableDouble(AVGDOP_FIELD_ID);
        }
    }

    public long LastDop
    {
        get
        {
            return base.GetInt64(LASTDOP_FIELD_ID);
        }
    }

    public long MinDop
    {
        get
        {
            return base.GetInt64(MINDOP_FIELD_ID);
        }
    }

    public long MaxDop
    {
        get
        {
            return base.GetInt64(MAXDOP_FIELD_ID);
        }
    }

    public double? StdevDop
    {
        get
        {
            return base.GetNullableDouble(STDEVDOP_FIELD_ID);
        }
    }

    public double? AvgQueryMaxUsedMemory
    {
        get
        {
            return base.GetNullableDouble(AVGQUERYMAXUSEDMEMORY_FIELD_ID);
        }
    }

    public long LastQueryMaxUsedMemory
    {
        get
        {
            return base.GetInt64(LASTQUERYMAXUSEDMEMORY_FIELD_ID);
        }
    }

    public long MinQueryMaxUsedMemory
    {
        get
        {
            return base.GetInt64(MINQUERYMAXUSEDMEMORY_FIELD_ID);
        }
    }

    public long MaxQueryMaxUsedMemory
    {
        get
        {
            return base.GetInt64(MAXQUERYMAXUSEDMEMORY_FIELD_ID);
        }
    }

    public double? StdevQueryMaxUsedMemory
    {
        get
        {
            return base.GetNullableDouble(STDEVQUERYMAXUSEDMEMORY_FIELD_ID);
        }
    }

    public double? AvgRowcount
    {
        get
        {
            return base.GetNullableDouble(AVGROWCOUNT_FIELD_ID);
        }
    }

    public long LastRowcount
    {
        get
        {
            return base.GetInt64(LASTROWCOUNT_FIELD_ID);
        }
    }

    public long MinRowcount
    {
        get
        {
            return base.GetInt64(MINROWCOUNT_FIELD_ID);
        }
    }

    public long MaxRowcount
    {
        get
        {
            return base.GetInt64(MAXROWCOUNT_FIELD_ID);
        }
    }

    public double? StdevRowcount
    {
        get
        {
            return base.GetNullableDouble(STDEVROWCOUNT_FIELD_ID);
        }
    }

    public double? AvgNumPhysicalIoReads
    {
        get
        {
            return base.GetNullableDouble(AVGNUMPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long? LastNumPhysicalIoReads
    {
        get
        {
            return base.GetNullableInt64(LASTNUMPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long? MinNumPhysicalIoReads
    {
        get
        {
            return base.GetNullableInt64(MINNUMPHYSICALIOREADS_FIELD_ID);
        }
    }

    public long? MaxNumPhysicalIoReads
    {
        get
        {
            return base.GetNullableInt64(MAXNUMPHYSICALIOREADS_FIELD_ID);
        }
    }

    public double? StdevNumPhysicalIoReads
    {
        get
        {
            return base.GetNullableDouble(STDEVNUMPHYSICALIOREADS_FIELD_ID);
        }
    }

    public double? AvgLogBytesUsed
    {
        get
        {
            return base.GetNullableDouble(AVGLOGBYTESUSED_FIELD_ID);
        }
    }

    public long? LastLogBytesUsed
    {
        get
        {
            return base.GetNullableInt64(LASTLOGBYTESUSED_FIELD_ID);
        }
    }

    public long? MinLogBytesUsed
    {
        get
        {
            return base.GetNullableInt64(MINLOGBYTESUSED_FIELD_ID);
        }
    }

    public long? MaxLogBytesUsed
    {
        get
        {
            return base.GetNullableInt64(MAXLOGBYTESUSED_FIELD_ID);
        }
    }

    public double? StdevLogBytesUsed
    {
        get
        {
            return base.GetNullableDouble(STDEVLOGBYTESUSED_FIELD_ID);
        }
    }

    public double? AvgTempdbSpaceUsed
    {
        get
        {
            return base.GetNullableDouble(AVGTEMPDBSPACEUSED_FIELD_ID);
        }
    }

    public long? LastTempdbSpaceUsed
    {
        get
        {
            return base.GetNullableInt64(LASTTEMPDBSPACEUSED_FIELD_ID);
        }
    }

    public long? MinTempdbSpaceUsed
    {
        get
        {
            return base.GetNullableInt64(MINTEMPDBSPACEUSED_FIELD_ID);
        }
    }

    public long? MaxTempdbSpaceUsed
    {
        get
        {
            return base.GetNullableInt64(MAXTEMPDBSPACEUSED_FIELD_ID);
        }
    }

    public double? StdevTempdbSpaceUsed
    {
        get
        {
            return base.GetNullableDouble(STDEVTEMPDBSPACEUSED_FIELD_ID);
        }
    }


    public Types.QueryStoreRuntimeStatsDataType ToDataObject()
    {
        return new Types.QueryStoreRuntimeStatsDataType(RuntimeStatsId,
            PlanId,
            RuntimeStatsIntervalId,
            ExecutionType,
            ExecutionTypeDesc,
            FirstExecutionTime,
            LastExecutionTime,
            CountExecutions,
            AvgDuration,
            LastDuration,
            MinDuration,
            MaxDuration,
            StdevDuration,
            AvgCpuTime,
            LastCpuTime,
            MinCpuTime,
            MaxCpuTime,
            StdevCpuTime,
            AvgLogicalIoReads,
            LastLogicalIoReads,
            MinLogicalIoReads,
            MaxLogicalIoReads,
            StdevLogicalIoReads,
            AvgLogicalIoWrites,
            LastLogicalIoWrites,
            MinLogicalIoWrites,
            MaxLogicalIoWrites,
            StdevLogicalIoWrites,
            AvgPhysicalIoReads,
            LastPhysicalIoReads,
            MinPhysicalIoReads,
            MaxPhysicalIoReads,
            StdevPhysicalIoReads,
            AvgClrTime,
            LastClrTime,
            MinClrTime,
            MaxClrTime,
            StdevClrTime,
            AvgDop,
            LastDop,
            MinDop,
            MaxDop,
            StdevDop,
            AvgQueryMaxUsedMemory,
            LastQueryMaxUsedMemory,
            MinQueryMaxUsedMemory,
            MaxQueryMaxUsedMemory,
            StdevQueryMaxUsedMemory,
            AvgRowcount,
            LastRowcount,
            MinRowcount,
            MaxRowcount,
            StdevRowcount,
            AvgNumPhysicalIoReads,
            LastNumPhysicalIoReads,
            MinNumPhysicalIoReads,
            MaxNumPhysicalIoReads,
            StdevNumPhysicalIoReads,
            AvgLogBytesUsed,
            LastLogBytesUsed,
            MinLogBytesUsed,
            MaxLogBytesUsed,
            StdevLogBytesUsed,
            AvgTempdbSpaceUsed,
            LastTempdbSpaceUsed,
            MinTempdbSpaceUsed,
            MaxTempdbSpaceUsed,
            StdevTempdbSpaceUsed);
    }

    public List<Types.QueryStoreRuntimeStatsDataType> ToList()
    {
        var list = new List<Types.QueryStoreRuntimeStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
