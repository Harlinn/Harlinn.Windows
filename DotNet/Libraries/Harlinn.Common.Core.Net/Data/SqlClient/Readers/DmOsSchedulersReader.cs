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

public class DmOsSchedulersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_schedulers]";
    public const string TableName = "dm_os_schedulers";
    public const string ShortName = "dos";
    public const string Sql = """
        SELECT
          dos.[scheduler_address],
          dos.[parent_node_id],
          dos.[scheduler_id],
          dos.[cpu_id],
          dos.[Status],
          dos.[is_online],
          dos.[is_idle],
          dos.[preemptive_switches_count],
          dos.[context_switches_count],
          dos.[idle_switches_count],
          dos.[current_tasks_count],
          dos.[runnable_tasks_count],
          dos.[current_workers_count],
          dos.[active_workers_count],
          dos.[work_queue_count],
          dos.[pending_disk_io_count],
          dos.[load_factor],
          dos.[yield_count],
          dos.[last_timer_activity],
          dos.[failed_to_create_worker],
          dos.[active_worker_address],
          dos.[memory_object_address],
          dos.[task_memory_object_address],
          dos.[quantum_length_us],
          dos.[total_cpu_usage_ms],
          dos.[total_cpu_idle_capped_ms],
          dos.[total_scheduler_delay_ms],
          dos.[ideal_workers_limit]
        FROM
          [sys].[dm_os_schedulers] dos
        """;

    public const int SCHEDULERADDRESS_FIELD_ID = 0;
    public const int PARENTNODEID_FIELD_ID = 1;
    public const int SCHEDULERID_FIELD_ID = 2;
    public const int CPUID_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int ISONLINE_FIELD_ID = 5;
    public const int ISIDLE_FIELD_ID = 6;
    public const int PREEMPTIVESWITCHESCOUNT_FIELD_ID = 7;
    public const int CONTEXTSWITCHESCOUNT_FIELD_ID = 8;
    public const int IDLESWITCHESCOUNT_FIELD_ID = 9;
    public const int CURRENTTASKSCOUNT_FIELD_ID = 10;
    public const int RUNNABLETASKSCOUNT_FIELD_ID = 11;
    public const int CURRENTWORKERSCOUNT_FIELD_ID = 12;
    public const int ACTIVEWORKERSCOUNT_FIELD_ID = 13;
    public const int WORKQUEUECOUNT_FIELD_ID = 14;
    public const int PENDINGDISKIOCOUNT_FIELD_ID = 15;
    public const int LOADFACTOR_FIELD_ID = 16;
    public const int YIELDCOUNT_FIELD_ID = 17;
    public const int LASTTIMERACTIVITY_FIELD_ID = 18;
    public const int FAILEDTOCREATEWORKER_FIELD_ID = 19;
    public const int ACTIVEWORKERADDRESS_FIELD_ID = 20;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 21;
    public const int TASKMEMORYOBJECTADDRESS_FIELD_ID = 22;
    public const int QUANTUMLENGTHUS_FIELD_ID = 23;
    public const int TOTALCPUUSAGEMS_FIELD_ID = 24;
    public const int TOTALCPUIDLECAPPEDMS_FIELD_ID = 25;
    public const int TOTALSCHEDULERDELAYMS_FIELD_ID = 26;
    public const int IDEALWORKERSLIMIT_FIELD_ID = 27;


    public DmOsSchedulersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsSchedulersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsSchedulersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] SchedulerAddress
    {
        get
        {
            return base.GetBinary(SCHEDULERADDRESS_FIELD_ID);
        }
    }

    public int ParentNodeId
    {
        get
        {
            return base.GetInt32(PARENTNODEID_FIELD_ID);
        }
    }

    public int SchedulerId
    {
        get
        {
            return base.GetInt32(SCHEDULERID_FIELD_ID);
        }
    }

    public int CpuId
    {
        get
        {
            return base.GetInt32(CPUID_FIELD_ID);
        }
    }

    public string Status
    {
        get
        {
            return base.GetString(STATUS_FIELD_ID);
        }
    }

    public bool IsOnline
    {
        get
        {
            return base.GetBoolean(ISONLINE_FIELD_ID);
        }
    }

    public bool IsIdle
    {
        get
        {
            return base.GetBoolean(ISIDLE_FIELD_ID);
        }
    }

    public int PreemptiveSwitchesCount
    {
        get
        {
            return base.GetInt32(PREEMPTIVESWITCHESCOUNT_FIELD_ID);
        }
    }

    public int ContextSwitchesCount
    {
        get
        {
            return base.GetInt32(CONTEXTSWITCHESCOUNT_FIELD_ID);
        }
    }

    public int IdleSwitchesCount
    {
        get
        {
            return base.GetInt32(IDLESWITCHESCOUNT_FIELD_ID);
        }
    }

    public int CurrentTasksCount
    {
        get
        {
            return base.GetInt32(CURRENTTASKSCOUNT_FIELD_ID);
        }
    }

    public int RunnableTasksCount
    {
        get
        {
            return base.GetInt32(RUNNABLETASKSCOUNT_FIELD_ID);
        }
    }

    public int CurrentWorkersCount
    {
        get
        {
            return base.GetInt32(CURRENTWORKERSCOUNT_FIELD_ID);
        }
    }

    public int ActiveWorkersCount
    {
        get
        {
            return base.GetInt32(ACTIVEWORKERSCOUNT_FIELD_ID);
        }
    }

    public long WorkQueueCount
    {
        get
        {
            return base.GetInt64(WORKQUEUECOUNT_FIELD_ID);
        }
    }

    public int PendingDiskIoCount
    {
        get
        {
            return base.GetInt32(PENDINGDISKIOCOUNT_FIELD_ID);
        }
    }

    public int LoadFactor
    {
        get
        {
            return base.GetInt32(LOADFACTOR_FIELD_ID);
        }
    }

    public int YieldCount
    {
        get
        {
            return base.GetInt32(YIELDCOUNT_FIELD_ID);
        }
    }

    public long LastTimerActivity
    {
        get
        {
            return base.GetInt64(LASTTIMERACTIVITY_FIELD_ID);
        }
    }

    public bool FailedToCreateWorker
    {
        get
        {
            return base.GetBoolean(FAILEDTOCREATEWORKER_FIELD_ID);
        }
    }

    public byte[]? ActiveWorkerAddress
    {
        get
        {
            return base.GetNullableBinary(ACTIVEWORKERADDRESS_FIELD_ID);
        }
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public byte[] TaskMemoryObjectAddress
    {
        get
        {
            return base.GetBinary(TASKMEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public long QuantumLengthUs
    {
        get
        {
            return base.GetInt64(QUANTUMLENGTHUS_FIELD_ID);
        }
    }

    public long TotalCpuUsageMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSAGEMS_FIELD_ID);
        }
    }

    public long? TotalCpuIdleCappedMs
    {
        get
        {
            return base.GetNullableInt64(TOTALCPUIDLECAPPEDMS_FIELD_ID);
        }
    }

    public long TotalSchedulerDelayMs
    {
        get
        {
            return base.GetInt64(TOTALSCHEDULERDELAYMS_FIELD_ID);
        }
    }

    public int IdealWorkersLimit
    {
        get
        {
            return base.GetInt32(IDEALWORKERSLIMIT_FIELD_ID);
        }
    }


    public Types.DmOsSchedulersDataType ToDataObject()
    {
        return new Types.DmOsSchedulersDataType(SchedulerAddress,
            ParentNodeId,
            SchedulerId,
            CpuId,
            Status,
            IsOnline,
            IsIdle,
            PreemptiveSwitchesCount,
            ContextSwitchesCount,
            IdleSwitchesCount,
            CurrentTasksCount,
            RunnableTasksCount,
            CurrentWorkersCount,
            ActiveWorkersCount,
            WorkQueueCount,
            PendingDiskIoCount,
            LoadFactor,
            YieldCount,
            LastTimerActivity,
            FailedToCreateWorker,
            ActiveWorkerAddress,
            MemoryObjectAddress,
            TaskMemoryObjectAddress,
            QuantumLengthUs,
            TotalCpuUsageMs,
            TotalCpuIdleCappedMs,
            TotalSchedulerDelayMs,
            IdealWorkersLimit);
    }

    public List<Types.DmOsSchedulersDataType> ToList()
    {
        var list = new List<Types.DmOsSchedulersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
