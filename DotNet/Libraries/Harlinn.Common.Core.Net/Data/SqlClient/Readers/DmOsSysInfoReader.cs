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

public class DmOsSysInfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_sys_info]";
    public const string TableName = "dm_os_sys_info";
    public const string ShortName = "dosi";
    public const string Sql = """
        SELECT
          dosi.[cpu_ticks],
          dosi.[ms_ticks],
          dosi.[cpu_count],
          dosi.[hyperthread_ratio],
          dosi.[physical_memory_kb],
          dosi.[virtual_memory_kb],
          dosi.[committed_kb],
          dosi.[committed_target_kb],
          dosi.[visible_target_kb],
          dosi.[stack_size_in_bytes],
          dosi.[os_quantum],
          dosi.[os_error_mode],
          dosi.[os_priority_class],
          dosi.[max_workers_count],
          dosi.[scheduler_count],
          dosi.[scheduler_total_count],
          dosi.[deadlock_monitor_serial_number],
          dosi.[sqlserver_start_time_ms_ticks],
          dosi.[sqlserver_start_time],
          dosi.[affinity_type],
          dosi.[affinity_type_desc],
          dosi.[process_kernel_time_ms],
          dosi.[process_user_time_ms],
          dosi.[time_source],
          dosi.[time_source_desc],
          dosi.[virtual_machine_type],
          dosi.[virtual_machine_type_desc],
          dosi.[softnuma_configuration],
          dosi.[softnuma_configuration_desc],
          dosi.[process_physical_affinity],
          dosi.[sql_memory_model],
          dosi.[sql_memory_model_desc],
          dosi.[socket_count],
          dosi.[cores_per_socket],
          dosi.[numa_node_count],
          dosi.[container_type],
          dosi.[container_type_desc]
        FROM
          [sys].[dm_os_sys_info] dosi
        """;

    public const int CPUTICKS_FIELD_ID = 0;
    public const int MSTICKS_FIELD_ID = 1;
    public const int CPUCOUNT_FIELD_ID = 2;
    public const int HYPERTHREADRATIO_FIELD_ID = 3;
    public const int PHYSICALMEMORYKB_FIELD_ID = 4;
    public const int VIRTUALMEMORYKB_FIELD_ID = 5;
    public const int COMMITTEDKB_FIELD_ID = 6;
    public const int COMMITTEDTARGETKB_FIELD_ID = 7;
    public const int VISIBLETARGETKB_FIELD_ID = 8;
    public const int STACKSIZEINBYTES_FIELD_ID = 9;
    public const int OSQUANTUM_FIELD_ID = 10;
    public const int OSERRORMODE_FIELD_ID = 11;
    public const int OSPRIORITYCLASS_FIELD_ID = 12;
    public const int MAXWORKERSCOUNT_FIELD_ID = 13;
    public const int SCHEDULERCOUNT_FIELD_ID = 14;
    public const int SCHEDULERTOTALCOUNT_FIELD_ID = 15;
    public const int DEADLOCKMONITORSERIALNUMBER_FIELD_ID = 16;
    public const int SQLSERVERSTARTTIMEMSTICKS_FIELD_ID = 17;
    public const int SQLSERVERSTARTTIME_FIELD_ID = 18;
    public const int AFFINITYTYPE_FIELD_ID = 19;
    public const int AFFINITYTYPEDESC_FIELD_ID = 20;
    public const int PROCESSKERNELTIMEMS_FIELD_ID = 21;
    public const int PROCESSUSERTIMEMS_FIELD_ID = 22;
    public const int TIMESOURCE_FIELD_ID = 23;
    public const int TIMESOURCEDESC_FIELD_ID = 24;
    public const int VIRTUALMACHINETYPE_FIELD_ID = 25;
    public const int VIRTUALMACHINETYPEDESC_FIELD_ID = 26;
    public const int SOFTNUMACONFIGURATION_FIELD_ID = 27;
    public const int SOFTNUMACONFIGURATIONDESC_FIELD_ID = 28;
    public const int PROCESSPHYSICALAFFINITY_FIELD_ID = 29;
    public const int SQLMEMORYMODEL_FIELD_ID = 30;
    public const int SQLMEMORYMODELDESC_FIELD_ID = 31;
    public const int SOCKETCOUNT_FIELD_ID = 32;
    public const int CORESPERSOCKET_FIELD_ID = 33;
    public const int NUMANODECOUNT_FIELD_ID = 34;
    public const int CONTAINERTYPE_FIELD_ID = 35;
    public const int CONTAINERTYPEDESC_FIELD_ID = 36;


    public DmOsSysInfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsSysInfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsSysInfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long CpuTicks
    {
        get
        {
            return base.GetInt64(CPUTICKS_FIELD_ID);
        }
    }

    public long MsTicks
    {
        get
        {
            return base.GetInt64(MSTICKS_FIELD_ID);
        }
    }

    public int CpuCount
    {
        get
        {
            return base.GetInt32(CPUCOUNT_FIELD_ID);
        }
    }

    public int HyperthreadRatio
    {
        get
        {
            return base.GetInt32(HYPERTHREADRATIO_FIELD_ID);
        }
    }

    public long PhysicalMemoryKb
    {
        get
        {
            return base.GetInt64(PHYSICALMEMORYKB_FIELD_ID);
        }
    }

    public long VirtualMemoryKb
    {
        get
        {
            return base.GetInt64(VIRTUALMEMORYKB_FIELD_ID);
        }
    }

    public long CommittedKb
    {
        get
        {
            return base.GetInt64(COMMITTEDKB_FIELD_ID);
        }
    }

    public long CommittedTargetKb
    {
        get
        {
            return base.GetInt64(COMMITTEDTARGETKB_FIELD_ID);
        }
    }

    public long VisibleTargetKb
    {
        get
        {
            return base.GetInt64(VISIBLETARGETKB_FIELD_ID);
        }
    }

    public int StackSizeInBytes
    {
        get
        {
            return base.GetInt32(STACKSIZEINBYTES_FIELD_ID);
        }
    }

    public long OsQuantum
    {
        get
        {
            return base.GetInt64(OSQUANTUM_FIELD_ID);
        }
    }

    public int OsErrorMode
    {
        get
        {
            return base.GetInt32(OSERRORMODE_FIELD_ID);
        }
    }

    public int? OsPriorityClass
    {
        get
        {
            return base.GetNullableInt32(OSPRIORITYCLASS_FIELD_ID);
        }
    }

    public int MaxWorkersCount
    {
        get
        {
            return base.GetInt32(MAXWORKERSCOUNT_FIELD_ID);
        }
    }

    public int SchedulerCount
    {
        get
        {
            return base.GetInt32(SCHEDULERCOUNT_FIELD_ID);
        }
    }

    public int SchedulerTotalCount
    {
        get
        {
            return base.GetInt32(SCHEDULERTOTALCOUNT_FIELD_ID);
        }
    }

    public int DeadlockMonitorSerialNumber
    {
        get
        {
            return base.GetInt32(DEADLOCKMONITORSERIALNUMBER_FIELD_ID);
        }
    }

    public long SqlserverStartTimeMsTicks
    {
        get
        {
            return base.GetInt64(SQLSERVERSTARTTIMEMSTICKS_FIELD_ID);
        }
    }

    public DateTime SqlserverStartTime
    {
        get
        {
            return base.GetDateTime(SQLSERVERSTARTTIME_FIELD_ID);
        }
    }

    public int AffinityType
    {
        get
        {
            return base.GetInt32(AFFINITYTYPE_FIELD_ID);
        }
    }

    public string AffinityTypeDesc
    {
        get
        {
            return base.GetString(AFFINITYTYPEDESC_FIELD_ID);
        }
    }

    public long ProcessKernelTimeMs
    {
        get
        {
            return base.GetInt64(PROCESSKERNELTIMEMS_FIELD_ID);
        }
    }

    public long ProcessUserTimeMs
    {
        get
        {
            return base.GetInt64(PROCESSUSERTIMEMS_FIELD_ID);
        }
    }

    public int TimeSource
    {
        get
        {
            return base.GetInt32(TIMESOURCE_FIELD_ID);
        }
    }

    public string TimeSourceDesc
    {
        get
        {
            return base.GetString(TIMESOURCEDESC_FIELD_ID);
        }
    }

    public int VirtualMachineType
    {
        get
        {
            return base.GetInt32(VIRTUALMACHINETYPE_FIELD_ID);
        }
    }

    public string VirtualMachineTypeDesc
    {
        get
        {
            return base.GetString(VIRTUALMACHINETYPEDESC_FIELD_ID);
        }
    }

    public int SoftnumaConfiguration
    {
        get
        {
            return base.GetInt32(SOFTNUMACONFIGURATION_FIELD_ID);
        }
    }

    public string SoftnumaConfigurationDesc
    {
        get
        {
            return base.GetString(SOFTNUMACONFIGURATIONDESC_FIELD_ID);
        }
    }

    public string ProcessPhysicalAffinity
    {
        get
        {
            return base.GetString(PROCESSPHYSICALAFFINITY_FIELD_ID);
        }
    }

    public int SqlMemoryModel
    {
        get
        {
            return base.GetInt32(SQLMEMORYMODEL_FIELD_ID);
        }
    }

    public string SqlMemoryModelDesc
    {
        get
        {
            return base.GetString(SQLMEMORYMODELDESC_FIELD_ID);
        }
    }

    public int SocketCount
    {
        get
        {
            return base.GetInt32(SOCKETCOUNT_FIELD_ID);
        }
    }

    public int CoresPerSocket
    {
        get
        {
            return base.GetInt32(CORESPERSOCKET_FIELD_ID);
        }
    }

    public int NumaNodeCount
    {
        get
        {
            return base.GetInt32(NUMANODECOUNT_FIELD_ID);
        }
    }

    public int ContainerType
    {
        get
        {
            return base.GetInt32(CONTAINERTYPE_FIELD_ID);
        }
    }

    public string ContainerTypeDesc
    {
        get
        {
            return base.GetString(CONTAINERTYPEDESC_FIELD_ID);
        }
    }


    public Types.DmOsSysInfoDataType ToDataObject()
    {
        return new Types.DmOsSysInfoDataType(CpuTicks,
            MsTicks,
            CpuCount,
            HyperthreadRatio,
            PhysicalMemoryKb,
            VirtualMemoryKb,
            CommittedKb,
            CommittedTargetKb,
            VisibleTargetKb,
            StackSizeInBytes,
            OsQuantum,
            OsErrorMode,
            OsPriorityClass,
            MaxWorkersCount,
            SchedulerCount,
            SchedulerTotalCount,
            DeadlockMonitorSerialNumber,
            SqlserverStartTimeMsTicks,
            SqlserverStartTime,
            AffinityType,
            AffinityTypeDesc,
            ProcessKernelTimeMs,
            ProcessUserTimeMs,
            TimeSource,
            TimeSourceDesc,
            VirtualMachineType,
            VirtualMachineTypeDesc,
            SoftnumaConfiguration,
            SoftnumaConfigurationDesc,
            ProcessPhysicalAffinity,
            SqlMemoryModel,
            SqlMemoryModelDesc,
            SocketCount,
            CoresPerSocket,
            NumaNodeCount,
            ContainerType,
            ContainerTypeDesc);
    }

    public List<Types.DmOsSysInfoDataType> ToList()
    {
        var list = new List<Types.DmOsSysInfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
