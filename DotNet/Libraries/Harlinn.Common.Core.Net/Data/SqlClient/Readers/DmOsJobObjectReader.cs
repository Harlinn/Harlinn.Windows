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

public class DmOsJobObjectReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_job_object]";
    public const string TableName = "dm_os_job_object";
    public const string ShortName = "dojo";
    public const string Sql = """
        SELECT
          dojo.[cpu_rate],
          dojo.[cpu_affinity_mask],
          dojo.[cpu_affinity_group],
          dojo.[memory_limit_mb],
          dojo.[process_memory_limit_mb],
          dojo.[workingset_limit_mb],
          dojo.[non_sos_mem_gap_mb],
          dojo.[low_mem_signal_threshold_mb],
          dojo.[total_user_time],
          dojo.[total_kernel_time],
          dojo.[write_operation_count],
          dojo.[read_operation_count],
          dojo.[peak_process_memory_used_mb],
          dojo.[peak_job_memory_used_mb],
          dojo.[process_physical_affinity]
        FROM
          [sys].[dm_os_job_object] dojo
        """;

    public const int CPURATE_FIELD_ID = 0;
    public const int CPUAFFINITYMASK_FIELD_ID = 1;
    public const int CPUAFFINITYGROUP_FIELD_ID = 2;
    public const int MEMORYLIMITMB_FIELD_ID = 3;
    public const int PROCESSMEMORYLIMITMB_FIELD_ID = 4;
    public const int WORKINGSETLIMITMB_FIELD_ID = 5;
    public const int NONSOSMEMGAPMB_FIELD_ID = 6;
    public const int LOWMEMSIGNALTHRESHOLDMB_FIELD_ID = 7;
    public const int TOTALUSERTIME_FIELD_ID = 8;
    public const int TOTALKERNELTIME_FIELD_ID = 9;
    public const int WRITEOPERATIONCOUNT_FIELD_ID = 10;
    public const int READOPERATIONCOUNT_FIELD_ID = 11;
    public const int PEAKPROCESSMEMORYUSEDMB_FIELD_ID = 12;
    public const int PEAKJOBMEMORYUSEDMB_FIELD_ID = 13;
    public const int PROCESSPHYSICALAFFINITY_FIELD_ID = 14;


    public DmOsJobObjectReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsJobObjectReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsJobObjectReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? CpuRate
    {
        get
        {
            return base.GetNullableInt32(CPURATE_FIELD_ID);
        }
    }

    public long? CpuAffinityMask
    {
        get
        {
            return base.GetNullableInt64(CPUAFFINITYMASK_FIELD_ID);
        }
    }

    public int? CpuAffinityGroup
    {
        get
        {
            return base.GetNullableInt32(CPUAFFINITYGROUP_FIELD_ID);
        }
    }

    public long? MemoryLimitMb
    {
        get
        {
            return base.GetNullableInt64(MEMORYLIMITMB_FIELD_ID);
        }
    }

    public long? ProcessMemoryLimitMb
    {
        get
        {
            return base.GetNullableInt64(PROCESSMEMORYLIMITMB_FIELD_ID);
        }
    }

    public long? WorkingsetLimitMb
    {
        get
        {
            return base.GetNullableInt64(WORKINGSETLIMITMB_FIELD_ID);
        }
    }

    public long? NonSosMemGapMb
    {
        get
        {
            return base.GetNullableInt64(NONSOSMEMGAPMB_FIELD_ID);
        }
    }

    public long? LowMemSignalThresholdMb
    {
        get
        {
            return base.GetNullableInt64(LOWMEMSIGNALTHRESHOLDMB_FIELD_ID);
        }
    }

    public long? TotalUserTime
    {
        get
        {
            return base.GetNullableInt64(TOTALUSERTIME_FIELD_ID);
        }
    }

    public long? TotalKernelTime
    {
        get
        {
            return base.GetNullableInt64(TOTALKERNELTIME_FIELD_ID);
        }
    }

    public long? WriteOperationCount
    {
        get
        {
            return base.GetNullableInt64(WRITEOPERATIONCOUNT_FIELD_ID);
        }
    }

    public long? ReadOperationCount
    {
        get
        {
            return base.GetNullableInt64(READOPERATIONCOUNT_FIELD_ID);
        }
    }

    public long? PeakProcessMemoryUsedMb
    {
        get
        {
            return base.GetNullableInt64(PEAKPROCESSMEMORYUSEDMB_FIELD_ID);
        }
    }

    public long? PeakJobMemoryUsedMb
    {
        get
        {
            return base.GetNullableInt64(PEAKJOBMEMORYUSEDMB_FIELD_ID);
        }
    }

    public string ProcessPhysicalAffinity
    {
        get
        {
            return base.GetString(PROCESSPHYSICALAFFINITY_FIELD_ID);
        }
    }


    public Types.DmOsJobObjectDataType ToDataObject()
    {
        return new Types.DmOsJobObjectDataType(CpuRate,
            CpuAffinityMask,
            CpuAffinityGroup,
            MemoryLimitMb,
            ProcessMemoryLimitMb,
            WorkingsetLimitMb,
            NonSosMemGapMb,
            LowMemSignalThresholdMb,
            TotalUserTime,
            TotalKernelTime,
            WriteOperationCount,
            ReadOperationCount,
            PeakProcessMemoryUsedMb,
            PeakJobMemoryUsedMb,
            ProcessPhysicalAffinity);
    }

    public List<Types.DmOsJobObjectDataType> ToList()
    {
        var list = new List<Types.DmOsJobObjectDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
