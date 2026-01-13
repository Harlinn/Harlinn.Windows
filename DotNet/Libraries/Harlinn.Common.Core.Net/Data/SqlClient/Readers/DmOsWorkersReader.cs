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

public class DmOsWorkersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_workers]";
    public const string TableName = "dm_os_workers";
    public const string ShortName = "dow";
    public const string Sql = """
        SELECT
          dow.[worker_address],
          dow.[Status],
          dow.[is_preemptive],
          dow.[is_fiber],
          dow.[is_sick],
          dow.[is_in_cc_exception],
          dow.[is_fatal_exception],
          dow.[is_inside_catch],
          dow.[is_in_polling_io_completion_routine],
          dow.[context_switch_count],
          dow.[pending_io_count],
          dow.[pending_io_byte_count],
          dow.[pending_io_byte_average],
          dow.[wait_started_ms_ticks],
          dow.[wait_resumed_ms_ticks],
          dow.[task_bound_ms_ticks],
          dow.[worker_created_ms_ticks],
          dow.[exception_num],
          dow.[exception_severity],
          dow.[exception_address],
          dow.[Affinity],
          dow.[State],
          dow.[start_quantum],
          dow.[end_quantum],
          dow.[last_wait_type],
          dow.[return_code],
          dow.[quantum_used],
          dow.[max_quantum],
          dow.[boost_count],
          dow.[tasks_processed_count],
          dow.[fiber_address],
          dow.[task_address],
          dow.[memory_object_address],
          dow.[thread_address],
          dow.[signal_worker_address],
          dow.[scheduler_address],
          dow.[processor_group],
          dow.[worker_migration_count]
        FROM
          [sys].[dm_os_workers] dow
        """;

    public const int WORKERADDRESS_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int ISPREEMPTIVE_FIELD_ID = 2;
    public const int ISFIBER_FIELD_ID = 3;
    public const int ISSICK_FIELD_ID = 4;
    public const int ISINCCEXCEPTION_FIELD_ID = 5;
    public const int ISFATALEXCEPTION_FIELD_ID = 6;
    public const int ISINSIDECATCH_FIELD_ID = 7;
    public const int ISINPOLLINGIOCOMPLETIONROUTINE_FIELD_ID = 8;
    public const int CONTEXTSWITCHCOUNT_FIELD_ID = 9;
    public const int PENDINGIOCOUNT_FIELD_ID = 10;
    public const int PENDINGIOBYTECOUNT_FIELD_ID = 11;
    public const int PENDINGIOBYTEAVERAGE_FIELD_ID = 12;
    public const int WAITSTARTEDMSTICKS_FIELD_ID = 13;
    public const int WAITRESUMEDMSTICKS_FIELD_ID = 14;
    public const int TASKBOUNDMSTICKS_FIELD_ID = 15;
    public const int WORKERCREATEDMSTICKS_FIELD_ID = 16;
    public const int EXCEPTIONNUM_FIELD_ID = 17;
    public const int EXCEPTIONSEVERITY_FIELD_ID = 18;
    public const int EXCEPTIONADDRESS_FIELD_ID = 19;
    public const int AFFINITY_FIELD_ID = 20;
    public const int STATE_FIELD_ID = 21;
    public const int STARTQUANTUM_FIELD_ID = 22;
    public const int ENDQUANTUM_FIELD_ID = 23;
    public const int LASTWAITTYPE_FIELD_ID = 24;
    public const int RETURNCODE_FIELD_ID = 25;
    public const int QUANTUMUSED_FIELD_ID = 26;
    public const int MAXQUANTUM_FIELD_ID = 27;
    public const int BOOSTCOUNT_FIELD_ID = 28;
    public const int TASKSPROCESSEDCOUNT_FIELD_ID = 29;
    public const int FIBERADDRESS_FIELD_ID = 30;
    public const int TASKADDRESS_FIELD_ID = 31;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 32;
    public const int THREADADDRESS_FIELD_ID = 33;
    public const int SIGNALWORKERADDRESS_FIELD_ID = 34;
    public const int SCHEDULERADDRESS_FIELD_ID = 35;
    public const int PROCESSORGROUP_FIELD_ID = 36;
    public const int WORKERMIGRATIONCOUNT_FIELD_ID = 37;


    public DmOsWorkersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsWorkersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsWorkersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] WorkerAddress
    {
        get
        {
            return base.GetBinary(WORKERADDRESS_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public bool? IsPreemptive
    {
        get
        {
            return base.GetNullableBoolean(ISPREEMPTIVE_FIELD_ID);
        }
    }

    public bool? IsFiber
    {
        get
        {
            return base.GetNullableBoolean(ISFIBER_FIELD_ID);
        }
    }

    public bool? IsSick
    {
        get
        {
            return base.GetNullableBoolean(ISSICK_FIELD_ID);
        }
    }

    public bool? IsInCcException
    {
        get
        {
            return base.GetNullableBoolean(ISINCCEXCEPTION_FIELD_ID);
        }
    }

    public bool? IsFatalException
    {
        get
        {
            return base.GetNullableBoolean(ISFATALEXCEPTION_FIELD_ID);
        }
    }

    public bool? IsInsideCatch
    {
        get
        {
            return base.GetNullableBoolean(ISINSIDECATCH_FIELD_ID);
        }
    }

    public bool? IsInPollingIoCompletionRoutine
    {
        get
        {
            return base.GetNullableBoolean(ISINPOLLINGIOCOMPLETIONROUTINE_FIELD_ID);
        }
    }

    public int ContextSwitchCount
    {
        get
        {
            return base.GetInt32(CONTEXTSWITCHCOUNT_FIELD_ID);
        }
    }

    public int PendingIoCount
    {
        get
        {
            return base.GetInt32(PENDINGIOCOUNT_FIELD_ID);
        }
    }

    public long PendingIoByteCount
    {
        get
        {
            return base.GetInt64(PENDINGIOBYTECOUNT_FIELD_ID);
        }
    }

    public int PendingIoByteAverage
    {
        get
        {
            return base.GetInt32(PENDINGIOBYTEAVERAGE_FIELD_ID);
        }
    }

    public long WaitStartedMsTicks
    {
        get
        {
            return base.GetInt64(WAITSTARTEDMSTICKS_FIELD_ID);
        }
    }

    public long WaitResumedMsTicks
    {
        get
        {
            return base.GetInt64(WAITRESUMEDMSTICKS_FIELD_ID);
        }
    }

    public long TaskBoundMsTicks
    {
        get
        {
            return base.GetInt64(TASKBOUNDMSTICKS_FIELD_ID);
        }
    }

    public long WorkerCreatedMsTicks
    {
        get
        {
            return base.GetInt64(WORKERCREATEDMSTICKS_FIELD_ID);
        }
    }

    public int ExceptionNum
    {
        get
        {
            return base.GetInt32(EXCEPTIONNUM_FIELD_ID);
        }
    }

    public int ExceptionSeverity
    {
        get
        {
            return base.GetInt32(EXCEPTIONSEVERITY_FIELD_ID);
        }
    }

    public byte[]? ExceptionAddress
    {
        get
        {
            return base.GetNullableBinary(EXCEPTIONADDRESS_FIELD_ID);
        }
    }

    public long Affinity
    {
        get
        {
            return base.GetInt64(AFFINITY_FIELD_ID);
        }
    }

    public string? State
    {
        get
        {
            return base.GetNullableString(STATE_FIELD_ID);
        }
    }

    public long StartQuantum
    {
        get
        {
            return base.GetInt64(STARTQUANTUM_FIELD_ID);
        }
    }

    public long EndQuantum
    {
        get
        {
            return base.GetInt64(ENDQUANTUM_FIELD_ID);
        }
    }

    public string? LastWaitType
    {
        get
        {
            return base.GetNullableString(LASTWAITTYPE_FIELD_ID);
        }
    }

    public int ReturnCode
    {
        get
        {
            return base.GetInt32(RETURNCODE_FIELD_ID);
        }
    }

    public long QuantumUsed
    {
        get
        {
            return base.GetInt64(QUANTUMUSED_FIELD_ID);
        }
    }

    public long MaxQuantum
    {
        get
        {
            return base.GetInt64(MAXQUANTUM_FIELD_ID);
        }
    }

    public int BoostCount
    {
        get
        {
            return base.GetInt32(BOOSTCOUNT_FIELD_ID);
        }
    }

    public int TasksProcessedCount
    {
        get
        {
            return base.GetInt32(TASKSPROCESSEDCOUNT_FIELD_ID);
        }
    }

    public byte[]? FiberAddress
    {
        get
        {
            return base.GetNullableBinary(FIBERADDRESS_FIELD_ID);
        }
    }

    public byte[]? TaskAddress
    {
        get
        {
            return base.GetNullableBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public byte[]? ThreadAddress
    {
        get
        {
            return base.GetNullableBinary(THREADADDRESS_FIELD_ID);
        }
    }

    public byte[]? SignalWorkerAddress
    {
        get
        {
            return base.GetNullableBinary(SIGNALWORKERADDRESS_FIELD_ID);
        }
    }

    public byte[]? SchedulerAddress
    {
        get
        {
            return base.GetNullableBinary(SCHEDULERADDRESS_FIELD_ID);
        }
    }

    public short ProcessorGroup
    {
        get
        {
            return base.GetInt16(PROCESSORGROUP_FIELD_ID);
        }
    }

    public int WorkerMigrationCount
    {
        get
        {
            return base.GetInt32(WORKERMIGRATIONCOUNT_FIELD_ID);
        }
    }


    public Types.DmOsWorkersDataType ToDataObject()
    {
        return new Types.DmOsWorkersDataType(WorkerAddress,
            Status,
            IsPreemptive,
            IsFiber,
            IsSick,
            IsInCcException,
            IsFatalException,
            IsInsideCatch,
            IsInPollingIoCompletionRoutine,
            ContextSwitchCount,
            PendingIoCount,
            PendingIoByteCount,
            PendingIoByteAverage,
            WaitStartedMsTicks,
            WaitResumedMsTicks,
            TaskBoundMsTicks,
            WorkerCreatedMsTicks,
            ExceptionNum,
            ExceptionSeverity,
            ExceptionAddress,
            Affinity,
            State,
            StartQuantum,
            EndQuantum,
            LastWaitType,
            ReturnCode,
            QuantumUsed,
            MaxQuantum,
            BoostCount,
            TasksProcessedCount,
            FiberAddress,
            TaskAddress,
            MemoryObjectAddress,
            ThreadAddress,
            SignalWorkerAddress,
            SchedulerAddress,
            ProcessorGroup,
            WorkerMigrationCount);
    }

    public List<Types.DmOsWorkersDataType> ToList()
    {
        var list = new List<Types.DmOsWorkersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
