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

public class DmExecDistributedRequestStepsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_distributed_request_steps]";
    public const string TableName = "dm_exec_distributed_request_steps";
    public const string ShortName = "dedrs";
    public const string Sql = """
        SELECT
          dedrs.[execution_id],
          dedrs.[step_index],
          dedrs.[operation_type],
          dedrs.[distribution_type],
          dedrs.[location_type],
          dedrs.[Status],
          dedrs.[error_id],
          dedrs.[start_time],
          dedrs.[end_time],
          dedrs.[total_elapsed_time],
          dedrs.[row_count],
          dedrs.[Command],
          dedrs.[compute_pool_id]
        FROM
          [sys].[dm_exec_distributed_request_steps] dedrs
        """;

    public const int EXECUTIONID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int OPERATIONTYPE_FIELD_ID = 2;
    public const int DISTRIBUTIONTYPE_FIELD_ID = 3;
    public const int LOCATIONTYPE_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int ERRORID_FIELD_ID = 6;
    public const int STARTTIME_FIELD_ID = 7;
    public const int ENDTIME_FIELD_ID = 8;
    public const int TOTALELAPSEDTIME_FIELD_ID = 9;
    public const int ROWCOUNT_FIELD_ID = 10;
    public const int COMMAND_FIELD_ID = 11;
    public const int COMPUTEPOOLID_FIELD_ID = 12;


    public DmExecDistributedRequestStepsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedRequestStepsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedRequestStepsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ExecutionId
    {
        get
        {
            return base.GetNullableString(EXECUTIONID_FIELD_ID);
        }
    }

    public int? StepIndex
    {
        get
        {
            return base.GetNullableInt32(STEPINDEX_FIELD_ID);
        }
    }

    public string? OperationType
    {
        get
        {
            return base.GetNullableString(OPERATIONTYPE_FIELD_ID);
        }
    }

    public string? DistributionType
    {
        get
        {
            return base.GetNullableString(DISTRIBUTIONTYPE_FIELD_ID);
        }
    }

    public string? LocationType
    {
        get
        {
            return base.GetNullableString(LOCATIONTYPE_FIELD_ID);
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

    public long? RowCount
    {
        get
        {
            return base.GetNullableInt64(ROWCOUNT_FIELD_ID);
        }
    }

    public string? Command
    {
        get
        {
            return base.GetNullableString(COMMAND_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecDistributedRequestStepsDataType ToDataObject()
    {
        return new Types.DmExecDistributedRequestStepsDataType(ExecutionId,
            StepIndex,
            OperationType,
            DistributionType,
            LocationType,
            Status,
            ErrorId,
            StartTime,
            EndTime,
            TotalElapsedTime,
            RowCount,
            Command,
            ComputePoolId);
    }

    public List<Types.DmExecDistributedRequestStepsDataType> ToList()
    {
        var list = new List<Types.DmExecDistributedRequestStepsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
