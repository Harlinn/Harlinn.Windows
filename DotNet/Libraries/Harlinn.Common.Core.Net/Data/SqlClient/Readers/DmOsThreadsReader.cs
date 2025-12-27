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

public class DmOsThreadsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_threads]";
    public const string TableName = "dm_os_threads";
    public const string ShortName = "dot";
    public const string Sql = """
        SELECT
          dot.[thread_address],
          dot.[started_by_sqlservr],
          dot.[os_thread_id],
          dot.[Status],
          dot.[instruction_address],
          dot.[creation_time],
          dot.[kernel_time],
          dot.[usermode_time],
          dot.[stack_base_address],
          dot.[stack_end_address],
          dot.[stack_bytes_committed],
          dot.[stack_bytes_used],
          dot.[Affinity],
          dot.[Priority],
          dot.[Locale],
          dot.[Token],
          dot.[is_impersonating],
          dot.[is_waiting_on_loader_lock],
          dot.[fiber_data],
          dot.[thread_handle],
          dot.[event_handle],
          dot.[scheduler_address],
          dot.[worker_address],
          dot.[fiber_context_address],
          dot.[self_address],
          dot.[processor_group]
        FROM
          [sys].[dm_os_threads] dot
        """;

    public const int THREADADDRESS_FIELD_ID = 0;
    public const int STARTEDBYSQLSERVR_FIELD_ID = 1;
    public const int OSTHREADID_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;
    public const int INSTRUCTIONADDRESS_FIELD_ID = 4;
    public const int CREATIONTIME_FIELD_ID = 5;
    public const int KERNELTIME_FIELD_ID = 6;
    public const int USERMODETIME_FIELD_ID = 7;
    public const int STACKBASEADDRESS_FIELD_ID = 8;
    public const int STACKENDADDRESS_FIELD_ID = 9;
    public const int STACKBYTESCOMMITTED_FIELD_ID = 10;
    public const int STACKBYTESUSED_FIELD_ID = 11;
    public const int AFFINITY_FIELD_ID = 12;
    public const int PRIORITY_FIELD_ID = 13;
    public const int LOCALE_FIELD_ID = 14;
    public const int TOKEN_FIELD_ID = 15;
    public const int ISIMPERSONATING_FIELD_ID = 16;
    public const int ISWAITINGONLOADERLOCK_FIELD_ID = 17;
    public const int FIBERDATA_FIELD_ID = 18;
    public const int THREADHANDLE_FIELD_ID = 19;
    public const int EVENTHANDLE_FIELD_ID = 20;
    public const int SCHEDULERADDRESS_FIELD_ID = 21;
    public const int WORKERADDRESS_FIELD_ID = 22;
    public const int FIBERCONTEXTADDRESS_FIELD_ID = 23;
    public const int SELFADDRESS_FIELD_ID = 24;
    public const int PROCESSORGROUP_FIELD_ID = 25;


    public DmOsThreadsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsThreadsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsThreadsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] ThreadAddress
    {
        get
        {
            return base.GetBinary(THREADADDRESS_FIELD_ID);
        }
    }

    public bool StartedBySqlservr
    {
        get
        {
            return base.GetBoolean(STARTEDBYSQLSERVR_FIELD_ID);
        }
    }

    public int OsThreadId
    {
        get
        {
            return base.GetInt32(OSTHREADID_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public byte[]? InstructionAddress
    {
        get
        {
            return base.GetNullableBinary(INSTRUCTIONADDRESS_FIELD_ID);
        }
    }

    public DateTime? CreationTime
    {
        get
        {
            return base.GetNullableDateTime(CREATIONTIME_FIELD_ID);
        }
    }

    public long? KernelTime
    {
        get
        {
            return base.GetNullableInt64(KERNELTIME_FIELD_ID);
        }
    }

    public long? UsermodeTime
    {
        get
        {
            return base.GetNullableInt64(USERMODETIME_FIELD_ID);
        }
    }

    public byte[] StackBaseAddress
    {
        get
        {
            return base.GetBinary(STACKBASEADDRESS_FIELD_ID);
        }
    }

    public byte[]? StackEndAddress
    {
        get
        {
            return base.GetNullableBinary(STACKENDADDRESS_FIELD_ID);
        }
    }

    public int StackBytesCommitted
    {
        get
        {
            return base.GetInt32(STACKBYTESCOMMITTED_FIELD_ID);
        }
    }

    public int? StackBytesUsed
    {
        get
        {
            return base.GetNullableInt32(STACKBYTESUSED_FIELD_ID);
        }
    }

    public long Affinity
    {
        get
        {
            return base.GetInt64(AFFINITY_FIELD_ID);
        }
    }

    public int? Priority
    {
        get
        {
            return base.GetNullableInt32(PRIORITY_FIELD_ID);
        }
    }

    public int? Locale
    {
        get
        {
            return base.GetNullableInt32(LOCALE_FIELD_ID);
        }
    }

    public byte[]? Token
    {
        get
        {
            return base.GetNullableBinary(TOKEN_FIELD_ID);
        }
    }

    public int? IsImpersonating
    {
        get
        {
            return base.GetNullableInt32(ISIMPERSONATING_FIELD_ID);
        }
    }

    public int? IsWaitingOnLoaderLock
    {
        get
        {
            return base.GetNullableInt32(ISWAITINGONLOADERLOCK_FIELD_ID);
        }
    }

    public byte[]? FiberData
    {
        get
        {
            return base.GetNullableBinary(FIBERDATA_FIELD_ID);
        }
    }

    public byte[]? ThreadHandle
    {
        get
        {
            return base.GetNullableBinary(THREADHANDLE_FIELD_ID);
        }
    }

    public byte[]? EventHandle
    {
        get
        {
            return base.GetNullableBinary(EVENTHANDLE_FIELD_ID);
        }
    }

    public byte[]? SchedulerAddress
    {
        get
        {
            return base.GetNullableBinary(SCHEDULERADDRESS_FIELD_ID);
        }
    }

    public byte[]? WorkerAddress
    {
        get
        {
            return base.GetNullableBinary(WORKERADDRESS_FIELD_ID);
        }
    }

    public byte[]? FiberContextAddress
    {
        get
        {
            return base.GetNullableBinary(FIBERCONTEXTADDRESS_FIELD_ID);
        }
    }

    public byte[]? SelfAddress
    {
        get
        {
            return base.GetNullableBinary(SELFADDRESS_FIELD_ID);
        }
    }

    public short ProcessorGroup
    {
        get
        {
            return base.GetInt16(PROCESSORGROUP_FIELD_ID);
        }
    }


    public Types.DmOsThreadsDataType ToDataObject()
    {
        return new Types.DmOsThreadsDataType(ThreadAddress,
            StartedBySqlservr,
            OsThreadId,
            Status,
            InstructionAddress,
            CreationTime,
            KernelTime,
            UsermodeTime,
            StackBaseAddress,
            StackEndAddress,
            StackBytesCommitted,
            StackBytesUsed,
            Affinity,
            Priority,
            Locale,
            Token,
            IsImpersonating,
            IsWaitingOnLoaderLock,
            FiberData,
            ThreadHandle,
            EventHandle,
            SchedulerAddress,
            WorkerAddress,
            FiberContextAddress,
            SelfAddress,
            ProcessorGroup);
    }

    public List<Types.DmOsThreadsDataType> ToList()
    {
        var list = new List<Types.DmOsThreadsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
