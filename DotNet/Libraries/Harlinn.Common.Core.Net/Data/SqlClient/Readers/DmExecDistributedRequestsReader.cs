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

public class DmExecDistributedRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_distributed_requests]";
    public const string TableName = "dm_exec_distributed_requests";
    public const string ShortName = "dedr";
    public const string Sql = """
        SELECT
          dedr.[sql_handle],
          dedr.[execution_id],
          dedr.[Status],
          dedr.[error_id],
          dedr.[start_time],
          dedr.[end_time],
          dedr.[total_elapsed_time],
          dedr.[compute_pool_id]
        FROM
          [sys].[dm_exec_distributed_requests] dedr
        """;

    public const int SQLHANDLE_FIELD_ID = 0;
    public const int EXECUTIONID_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int ERRORID_FIELD_ID = 3;
    public const int STARTTIME_FIELD_ID = 4;
    public const int ENDTIME_FIELD_ID = 5;
    public const int TOTALELAPSEDTIME_FIELD_ID = 6;
    public const int COMPUTEPOOLID_FIELD_ID = 7;


    public DmExecDistributedRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? SqlHandle
    {
        get
        {
            return base.GetNullableBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public string? ExecutionId
    {
        get
        {
            return base.GetNullableString(EXECUTIONID_FIELD_ID);
        }
    }

    public string? Status
    {
        get
        {
            return base.GetNullableString(STATUS_FIELD_ID);
        }
    }

    public string? ErrorId
    {
        get
        {
            return base.GetNullableString(ERRORID_FIELD_ID);
        }
    }

    public DateTime? StartTime
    {
        get
        {
            return base.GetNullableDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime? EndTime
    {
        get
        {
            return base.GetNullableDateTime(ENDTIME_FIELD_ID);
        }
    }

    public int? TotalElapsedTime
    {
        get
        {
            return base.GetNullableInt32(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecDistributedRequestsDataType ToDataObject()
    {
        return new Types.DmExecDistributedRequestsDataType(SqlHandle,
            ExecutionId,
            Status,
            ErrorId,
            StartTime,
            EndTime,
            TotalElapsedTime,
            ComputePoolId);
    }

    public List<Types.DmExecDistributedRequestsDataType> ToList()
    {
        var list = new List<Types.DmExecDistributedRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
