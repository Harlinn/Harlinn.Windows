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

public class DmExecExternalWorkReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_external_work]";
    public const string TableName = "dm_exec_external_work";
    public const string ShortName = "deew";
    public const string Sql = """
        SELECT
          deew.[execution_id],
          deew.[step_index],
          deew.[dms_step_index],
          deew.[work_id],
          deew.[compute_node_id],
          deew.[Type],
          deew.[input_name],
          deew.[read_location],
          deew.[read_command],
          deew.[bytes_processed],
          deew.[Length],
          deew.[start_time],
          deew.[end_time],
          deew.[total_elapsed_time],
          deew.[Status],
          deew.[compute_pool_id]
        FROM
          [sys].[dm_exec_external_work] deew
        """;

    public const int EXECUTIONID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int DMSSTEPINDEX_FIELD_ID = 2;
    public const int WORKID_FIELD_ID = 3;
    public const int COMPUTENODEID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int INPUTNAME_FIELD_ID = 6;
    public const int READLOCATION_FIELD_ID = 7;
    public const int READCOMMAND_FIELD_ID = 8;
    public const int BYTESPROCESSED_FIELD_ID = 9;
    public const int LENGTH_FIELD_ID = 10;
    public const int STARTTIME_FIELD_ID = 11;
    public const int ENDTIME_FIELD_ID = 12;
    public const int TOTALELAPSEDTIME_FIELD_ID = 13;
    public const int STATUS_FIELD_ID = 14;
    public const int COMPUTEPOOLID_FIELD_ID = 15;


    public DmExecExternalWorkReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecExternalWorkReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecExternalWorkReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? WorkId
    {
        get
        {
            return base.GetNullableInt32(WORKID_FIELD_ID);
        }
    }

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? InputName
    {
        get
        {
            return base.GetNullableString(INPUTNAME_FIELD_ID);
        }
    }

    public long? ReadLocation
    {
        get
        {
            return base.GetNullableInt64(READLOCATION_FIELD_ID);
        }
    }

    public string? ReadCommand
    {
        get
        {
            return base.GetNullableString(READCOMMAND_FIELD_ID);
        }
    }

    public long? BytesProcessed
    {
        get
        {
            return base.GetNullableInt64(BYTESPROCESSED_FIELD_ID);
        }
    }

    public long? Length
    {
        get
        {
            return base.GetNullableInt64(LENGTH_FIELD_ID);
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

    public string? Status
    {
        get
        {
            return base.GetNullableString(STATUS_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecExternalWorkDataType ToDataObject()
    {
        return new Types.DmExecExternalWorkDataType(ExecutionId,
            StepIndex,
            DmsStepIndex,
            WorkId,
            ComputeNodeId,
            Type,
            InputName,
            ReadLocation,
            ReadCommand,
            BytesProcessed,
            Length,
            StartTime,
            EndTime,
            TotalElapsedTime,
            Status,
            ComputePoolId);
    }

    public List<Types.DmExecExternalWorkDataType> ToList()
    {
        var list = new List<Types.DmExecExternalWorkDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
