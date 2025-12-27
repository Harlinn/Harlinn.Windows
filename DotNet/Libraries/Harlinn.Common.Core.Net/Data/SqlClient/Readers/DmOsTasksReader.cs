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

public class DmOsTasksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_tasks]";
    public const string TableName = "dm_os_tasks";
    public const string ShortName = "dot0";
    public const string Sql = """
        SELECT
          dot0.[task_address],
          dot0.[task_state],
          dot0.[context_switches_count],
          dot0.[pending_io_count],
          dot0.[pending_io_byte_count],
          dot0.[pending_io_byte_average],
          dot0.[scheduler_id],
          dot0.[session_id],
          dot0.[exec_context_id],
          dot0.[request_id],
          dot0.[worker_address],
          dot0.[host_address],
          dot0.[parent_task_address]
        FROM
          [sys].[dm_os_tasks] dot0
        """;

    public const int TASKADDRESS_FIELD_ID = 0;
    public const int TASKSTATE_FIELD_ID = 1;
    public const int CONTEXTSWITCHESCOUNT_FIELD_ID = 2;
    public const int PENDINGIOCOUNT_FIELD_ID = 3;
    public const int PENDINGIOBYTECOUNT_FIELD_ID = 4;
    public const int PENDINGIOBYTEAVERAGE_FIELD_ID = 5;
    public const int SCHEDULERID_FIELD_ID = 6;
    public const int SESSIONID_FIELD_ID = 7;
    public const int EXECCONTEXTID_FIELD_ID = 8;
    public const int REQUESTID_FIELD_ID = 9;
    public const int WORKERADDRESS_FIELD_ID = 10;
    public const int HOSTADDRESS_FIELD_ID = 11;
    public const int PARENTTASKADDRESS_FIELD_ID = 12;


    public DmOsTasksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsTasksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsTasksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] TaskAddress
    {
        get
        {
            return base.GetBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public string? TaskState
    {
        get
        {
            return base.GetNullableString(TASKSTATE_FIELD_ID);
        }
    }

    public int? ContextSwitchesCount
    {
        get
        {
            return base.GetNullableInt32(CONTEXTSWITCHESCOUNT_FIELD_ID);
        }
    }

    public int? PendingIoCount
    {
        get
        {
            return base.GetNullableInt32(PENDINGIOCOUNT_FIELD_ID);
        }
    }

    public long? PendingIoByteCount
    {
        get
        {
            return base.GetNullableInt64(PENDINGIOBYTECOUNT_FIELD_ID);
        }
    }

    public int? PendingIoByteAverage
    {
        get
        {
            return base.GetNullableInt32(PENDINGIOBYTEAVERAGE_FIELD_ID);
        }
    }

    public int SchedulerId
    {
        get
        {
            return base.GetInt32(SCHEDULERID_FIELD_ID);
        }
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
        }
    }

    public int? ExecContextId
    {
        get
        {
            return base.GetNullableInt32(EXECCONTEXTID_FIELD_ID);
        }
    }

    public int? RequestId
    {
        get
        {
            return base.GetNullableInt32(REQUESTID_FIELD_ID);
        }
    }

    public byte[]? WorkerAddress
    {
        get
        {
            return base.GetNullableBinary(WORKERADDRESS_FIELD_ID);
        }
    }

    public byte[] HostAddress
    {
        get
        {
            return base.GetBinary(HOSTADDRESS_FIELD_ID);
        }
    }

    public byte[]? ParentTaskAddress
    {
        get
        {
            return base.GetNullableBinary(PARENTTASKADDRESS_FIELD_ID);
        }
    }


    public Types.DmOsTasksDataType ToDataObject()
    {
        return new Types.DmOsTasksDataType(TaskAddress,
            TaskState,
            ContextSwitchesCount,
            PendingIoCount,
            PendingIoByteCount,
            PendingIoByteAverage,
            SchedulerId,
            SessionId,
            ExecContextId,
            RequestId,
            WorkerAddress,
            HostAddress,
            ParentTaskAddress);
    }

    public List<Types.DmOsTasksDataType> ToList()
    {
        var list = new List<Types.DmOsTasksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
