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

public class DmExecDistributedSqlRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_distributed_sql_requests]";
    public const string TableName = "dm_exec_distributed_sql_requests";
    public const string ShortName = "dedsr";
    public const string Sql = """
        SELECT
          dedsr.[execution_id],
          dedsr.[step_index],
          dedsr.[compute_node_id],
          dedsr.[distribution_id],
          dedsr.[Status],
          dedsr.[error_id],
          dedsr.[start_time],
          dedsr.[end_time],
          dedsr.[total_elapsed_time],
          dedsr.[row_count],
          dedsr.[Spid],
          dedsr.[Command],
          dedsr.[compute_pool_id]
        FROM
          [sys].[dm_exec_distributed_sql_requests] dedsr
        """;

    public const int EXECUTIONID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int COMPUTENODEID_FIELD_ID = 2;
    public const int DISTRIBUTIONID_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int ERRORID_FIELD_ID = 5;
    public const int STARTTIME_FIELD_ID = 6;
    public const int ENDTIME_FIELD_ID = 7;
    public const int TOTALELAPSEDTIME_FIELD_ID = 8;
    public const int ROWCOUNT_FIELD_ID = 9;
    public const int SPID_FIELD_ID = 10;
    public const int COMMAND_FIELD_ID = 11;
    public const int COMPUTEPOOLID_FIELD_ID = 12;


    public DmExecDistributedSqlRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedSqlRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecDistributedSqlRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public int? DistributionId
    {
        get
        {
            return base.GetNullableInt32(DISTRIBUTIONID_FIELD_ID);
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

    public int? Spid
    {
        get
        {
            return base.GetNullableInt32(SPID_FIELD_ID);
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


    public Types.DmExecDistributedSqlRequestsDataType ToDataObject()
    {
        return new Types.DmExecDistributedSqlRequestsDataType(ExecutionId,
            StepIndex,
            ComputeNodeId,
            DistributionId,
            Status,
            ErrorId,
            StartTime,
            EndTime,
            TotalElapsedTime,
            RowCount,
            Spid,
            Command,
            ComputePoolId);
    }

    public List<Types.DmExecDistributedSqlRequestsDataType> ToList()
    {
        var list = new List<Types.DmExecDistributedSqlRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
