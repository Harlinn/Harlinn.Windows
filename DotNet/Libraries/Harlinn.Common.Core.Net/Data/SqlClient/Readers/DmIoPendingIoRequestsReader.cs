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

public class DmIoPendingIoRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_io_pending_io_requests]";
    public const string TableName = "dm_io_pending_io_requests";
    public const string ShortName = "dipir";
    public const string Sql = """
        SELECT
          dipir.[io_completion_request_address],
          dipir.[io_type],
          dipir.[io_pending_ms_ticks],
          dipir.[io_pending],
          dipir.[io_completion_routine_address],
          dipir.[io_user_data_address],
          dipir.[scheduler_address],
          dipir.[io_handle],
          dipir.[io_offset],
          dipir.[io_handle_path]
        FROM
          [sys].[dm_io_pending_io_requests] dipir
        """;

    public const int IOCOMPLETIONREQUESTADDRESS_FIELD_ID = 0;
    public const int IOTYPE_FIELD_ID = 1;
    public const int IOPENDINGMSTICKS_FIELD_ID = 2;
    public const int IOPENDING_FIELD_ID = 3;
    public const int IOCOMPLETIONROUTINEADDRESS_FIELD_ID = 4;
    public const int IOUSERDATAADDRESS_FIELD_ID = 5;
    public const int SCHEDULERADDRESS_FIELD_ID = 6;
    public const int IOHANDLE_FIELD_ID = 7;
    public const int IOOFFSET_FIELD_ID = 8;
    public const int IOHANDLEPATH_FIELD_ID = 9;


    public DmIoPendingIoRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmIoPendingIoRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmIoPendingIoRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] IoCompletionRequestAddress
    {
        get
        {
            return base.GetBinary(IOCOMPLETIONREQUESTADDRESS_FIELD_ID);
        }
    }

    public string IoType
    {
        get
        {
            return base.GetString(IOTYPE_FIELD_ID);
        }
    }

    public long IoPendingMsTicks
    {
        get
        {
            return base.GetInt64(IOPENDINGMSTICKS_FIELD_ID);
        }
    }

    public int IoPending
    {
        get
        {
            return base.GetInt32(IOPENDING_FIELD_ID);
        }
    }

    public byte[]? IoCompletionRoutineAddress
    {
        get
        {
            return base.GetNullableBinary(IOCOMPLETIONROUTINEADDRESS_FIELD_ID);
        }
    }

    public byte[]? IoUserDataAddress
    {
        get
        {
            return base.GetNullableBinary(IOUSERDATAADDRESS_FIELD_ID);
        }
    }

    public byte[] SchedulerAddress
    {
        get
        {
            return base.GetBinary(SCHEDULERADDRESS_FIELD_ID);
        }
    }

    public byte[]? IoHandle
    {
        get
        {
            return base.GetNullableBinary(IOHANDLE_FIELD_ID);
        }
    }

    public long IoOffset
    {
        get
        {
            return base.GetInt64(IOOFFSET_FIELD_ID);
        }
    }

    public string? IoHandlePath
    {
        get
        {
            return base.GetNullableString(IOHANDLEPATH_FIELD_ID);
        }
    }


    public Types.DmIoPendingIoRequestsDataType ToDataObject()
    {
        return new Types.DmIoPendingIoRequestsDataType(IoCompletionRequestAddress,
            IoType,
            IoPendingMsTicks,
            IoPending,
            IoCompletionRoutineAddress,
            IoUserDataAddress,
            SchedulerAddress,
            IoHandle,
            IoOffset,
            IoHandlePath);
    }

    public List<Types.DmIoPendingIoRequestsDataType> ToList()
    {
        var list = new List<Types.DmIoPendingIoRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
