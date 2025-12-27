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

public class DmExecDmsWorkersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_dms_workers]";
    public const string TableName = "dm_exec_dms_workers";
    public const string ShortName = "dedw";
    public const string Sql = """
        SELECT
          dedw.[execution_id],
          dedw.[step_index],
          dedw.[dms_step_index],
          dedw.[compute_node_id],
          dedw.[distribution_id],
          dedw.[Type],
          dedw.[Status],
          dedw.[bytes_per_sec],
          dedw.[bytes_processed],
          dedw.[rows_processed],
          dedw.[start_time],
          dedw.[end_time],
          dedw.[total_elapsed_time],
          dedw.[cpu_time],
          dedw.[query_time],
          dedw.[buffers_available],
          dedw.[dms_cpid],
          dedw.[sql_spid],
          dedw.[error_id],
          dedw.[source_info],
          dedw.[destination_info],
          dedw.[Command],
          dedw.[compute_pool_id]
        FROM
          [sys].[dm_exec_dms_workers] dedw
        """;

    public const int EXECUTIONID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int DMSSTEPINDEX_FIELD_ID = 2;
    public const int COMPUTENODEID_FIELD_ID = 3;
    public const int DISTRIBUTIONID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int STATUS_FIELD_ID = 6;
    public const int BYTESPERSEC_FIELD_ID = 7;
    public const int BYTESPROCESSED_FIELD_ID = 8;
    public const int ROWSPROCESSED_FIELD_ID = 9;
    public const int STARTTIME_FIELD_ID = 10;
    public const int ENDTIME_FIELD_ID = 11;
    public const int TOTALELAPSEDTIME_FIELD_ID = 12;
    public const int CPUTIME_FIELD_ID = 13;
    public const int QUERYTIME_FIELD_ID = 14;
    public const int BUFFERSAVAILABLE_FIELD_ID = 15;
    public const int DMSCPID_FIELD_ID = 16;
    public const int SQLSPID_FIELD_ID = 17;
    public const int ERRORID_FIELD_ID = 18;
    public const int SOURCEINFO_FIELD_ID = 19;
    public const int DESTINATIONINFO_FIELD_ID = 20;
    public const int COMMAND_FIELD_ID = 21;
    public const int COMPUTEPOOLID_FIELD_ID = 22;


    public DmExecDmsWorkersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecDmsWorkersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecDmsWorkersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? DmsStepIndex
    {
        get
        {
            return base.GetNullableInt32(DMSSTEPINDEX_FIELD_ID);
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

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? Status
    {
        get
        {
            return base.GetNullableString(STATUS_FIELD_ID);
        }
    }

    public long? BytesPerSec
    {
        get
        {
            return base.GetNullableInt64(BYTESPERSEC_FIELD_ID);
        }
    }

    public long? BytesProcessed
    {
        get
        {
            return base.GetNullableInt64(BYTESPROCESSED_FIELD_ID);
        }
    }

    public long? RowsProcessed
    {
        get
        {
            return base.GetNullableInt64(ROWSPROCESSED_FIELD_ID);
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

    public long? CpuTime
    {
        get
        {
            return base.GetNullableInt64(CPUTIME_FIELD_ID);
        }
    }

    public int? QueryTime
    {
        get
        {
            return base.GetNullableInt32(QUERYTIME_FIELD_ID);
        }
    }

    public int? BuffersAvailable
    {
        get
        {
            return base.GetNullableInt32(BUFFERSAVAILABLE_FIELD_ID);
        }
    }

    public int? DmsCpid
    {
        get
        {
            return base.GetNullableInt32(DMSCPID_FIELD_ID);
        }
    }

    public int? SqlSpid
    {
        get
        {
            return base.GetNullableInt32(SQLSPID_FIELD_ID);
        }
    }

    public string? ErrorId
    {
        get
        {
            return base.GetNullableString(ERRORID_FIELD_ID);
        }
    }

    public string? SourceInfo
    {
        get
        {
            return base.GetNullableString(SOURCEINFO_FIELD_ID);
        }
    }

    public string? DestinationInfo
    {
        get
        {
            return base.GetNullableString(DESTINATIONINFO_FIELD_ID);
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


    public Types.DmExecDmsWorkersDataType ToDataObject()
    {
        return new Types.DmExecDmsWorkersDataType(ExecutionId,
            StepIndex,
            DmsStepIndex,
            ComputeNodeId,
            DistributionId,
            Type,
            Status,
            BytesPerSec,
            BytesProcessed,
            RowsProcessed,
            StartTime,
            EndTime,
            TotalElapsedTime,
            CpuTime,
            QueryTime,
            BuffersAvailable,
            DmsCpid,
            SqlSpid,
            ErrorId,
            SourceInfo,
            DestinationInfo,
            Command,
            ComputePoolId);
    }

    public List<Types.DmExecDmsWorkersDataType> ToList()
    {
        var list = new List<Types.DmExecDmsWorkersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
