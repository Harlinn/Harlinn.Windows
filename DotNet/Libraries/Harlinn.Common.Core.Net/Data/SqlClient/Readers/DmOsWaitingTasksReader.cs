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

public class DmOsWaitingTasksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_waiting_tasks]";
    public const string TableName = "dm_os_waiting_tasks";
    public const string ShortName = "dowt";
    public const string Sql = """
        SELECT
          dowt.[waiting_task_address],
          dowt.[session_id],
          dowt.[exec_context_id],
          dowt.[wait_duration_ms],
          dowt.[wait_type],
          dowt.[resource_address],
          dowt.[blocking_task_address],
          dowt.[blocking_session_id],
          dowt.[blocking_exec_context_id],
          dowt.[resource_description]
        FROM
          [sys].[dm_os_waiting_tasks] dowt
        """;

    public const int WAITINGTASKADDRESS_FIELD_ID = 0;
    public const int SESSIONID_FIELD_ID = 1;
    public const int EXECCONTEXTID_FIELD_ID = 2;
    public const int WAITDURATIONMS_FIELD_ID = 3;
    public const int WAITTYPE_FIELD_ID = 4;
    public const int RESOURCEADDRESS_FIELD_ID = 5;
    public const int BLOCKINGTASKADDRESS_FIELD_ID = 6;
    public const int BLOCKINGSESSIONID_FIELD_ID = 7;
    public const int BLOCKINGEXECCONTEXTID_FIELD_ID = 8;
    public const int RESOURCEDESCRIPTION_FIELD_ID = 9;


    public DmOsWaitingTasksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsWaitingTasksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsWaitingTasksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] WaitingTaskAddress
    {
        get
        {
            return base.GetBinary(WAITINGTASKADDRESS_FIELD_ID);
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

    public long? WaitDurationMs
    {
        get
        {
            return base.GetNullableInt64(WAITDURATIONMS_FIELD_ID);
        }
    }

    public string? WaitType
    {
        get
        {
            return base.GetNullableString(WAITTYPE_FIELD_ID);
        }
    }

    public byte[]? ResourceAddress
    {
        get
        {
            return base.GetNullableBinary(RESOURCEADDRESS_FIELD_ID);
        }
    }

    public byte[]? BlockingTaskAddress
    {
        get
        {
            return base.GetNullableBinary(BLOCKINGTASKADDRESS_FIELD_ID);
        }
    }

    public short? BlockingSessionId
    {
        get
        {
            return base.GetNullableInt16(BLOCKINGSESSIONID_FIELD_ID);
        }
    }

    public int? BlockingExecContextId
    {
        get
        {
            return base.GetNullableInt32(BLOCKINGEXECCONTEXTID_FIELD_ID);
        }
    }

    public string? ResourceDescription
    {
        get
        {
            return base.GetNullableString(RESOURCEDESCRIPTION_FIELD_ID);
        }
    }


    public Types.DmOsWaitingTasksDataType ToDataObject()
    {
        return new Types.DmOsWaitingTasksDataType(WaitingTaskAddress,
            SessionId,
            ExecContextId,
            WaitDurationMs,
            WaitType,
            ResourceAddress,
            BlockingTaskAddress,
            BlockingSessionId,
            BlockingExecContextId,
            ResourceDescription);
    }

    public List<Types.DmOsWaitingTasksDataType> ToList()
    {
        var list = new List<Types.DmOsWaitingTasksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
