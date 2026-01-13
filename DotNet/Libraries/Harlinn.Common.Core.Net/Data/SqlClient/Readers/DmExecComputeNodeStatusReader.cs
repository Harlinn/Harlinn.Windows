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

public class DmExecComputeNodeStatusReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_compute_node_status]";
    public const string TableName = "dm_exec_compute_node_status";
    public const string ShortName = "decns";
    public const string Sql = """
        SELECT
          decns.[compute_node_id],
          decns.[process_id],
          decns.[process_name],
          decns.[allocated_memory],
          decns.[available_memory],
          decns.[process_cpu_usage],
          decns.[total_cpu_usage],
          decns.[thread_count],
          decns.[handle_count],
          decns.[total_elapsed_time],
          decns.[is_available],
          decns.[sent_time],
          decns.[received_time],
          decns.[error_id],
          decns.[compute_pool_id]
        FROM
          [sys].[dm_exec_compute_node_status] decns
        """;

    public const int COMPUTENODEID_FIELD_ID = 0;
    public const int PROCESSID_FIELD_ID = 1;
    public const int PROCESSNAME_FIELD_ID = 2;
    public const int ALLOCATEDMEMORY_FIELD_ID = 3;
    public const int AVAILABLEMEMORY_FIELD_ID = 4;
    public const int PROCESSCPUUSAGE_FIELD_ID = 5;
    public const int TOTALCPUUSAGE_FIELD_ID = 6;
    public const int THREADCOUNT_FIELD_ID = 7;
    public const int HANDLECOUNT_FIELD_ID = 8;
    public const int TOTALELAPSEDTIME_FIELD_ID = 9;
    public const int ISAVAILABLE_FIELD_ID = 10;
    public const int SENTTIME_FIELD_ID = 11;
    public const int RECEIVEDTIME_FIELD_ID = 12;
    public const int ERRORID_FIELD_ID = 13;
    public const int COMPUTEPOOLID_FIELD_ID = 14;


    public DmExecComputeNodeStatusReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodeStatusReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodeStatusReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public int? ProcessId
    {
        get
        {
            return base.GetNullableInt32(PROCESSID_FIELD_ID);
        }
    }

    public string? ProcessName
    {
        get
        {
            return base.GetNullableString(PROCESSNAME_FIELD_ID);
        }
    }

    public long? AllocatedMemory
    {
        get
        {
            return base.GetNullableInt64(ALLOCATEDMEMORY_FIELD_ID);
        }
    }

    public long? AvailableMemory
    {
        get
        {
            return base.GetNullableInt64(AVAILABLEMEMORY_FIELD_ID);
        }
    }

    public long? ProcessCpuUsage
    {
        get
        {
            return base.GetNullableInt64(PROCESSCPUUSAGE_FIELD_ID);
        }
    }

    public long? TotalCpuUsage
    {
        get
        {
            return base.GetNullableInt64(TOTALCPUUSAGE_FIELD_ID);
        }
    }

    public long? ThreadCount
    {
        get
        {
            return base.GetNullableInt64(THREADCOUNT_FIELD_ID);
        }
    }

    public long? HandleCount
    {
        get
        {
            return base.GetNullableInt64(HANDLECOUNT_FIELD_ID);
        }
    }

    public long? TotalElapsedTime
    {
        get
        {
            return base.GetNullableInt64(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public bool? IsAvailable
    {
        get
        {
            return base.GetNullableBoolean(ISAVAILABLE_FIELD_ID);
        }
    }

    public DateTime? SentTime
    {
        get
        {
            return base.GetNullableDateTime(SENTTIME_FIELD_ID);
        }
    }

    public DateTime? ReceivedTime
    {
        get
        {
            return base.GetNullableDateTime(RECEIVEDTIME_FIELD_ID);
        }
    }

    public string? ErrorId
    {
        get
        {
            return base.GetNullableString(ERRORID_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecComputeNodeStatusDataType ToDataObject()
    {
        return new Types.DmExecComputeNodeStatusDataType(ComputeNodeId,
            ProcessId,
            ProcessName,
            AllocatedMemory,
            AvailableMemory,
            ProcessCpuUsage,
            TotalCpuUsage,
            ThreadCount,
            HandleCount,
            TotalElapsedTime,
            IsAvailable,
            SentTime,
            ReceivedTime,
            ErrorId,
            ComputePoolId);
    }

    public List<Types.DmExecComputeNodeStatusDataType> ToList()
    {
        var list = new List<Types.DmExecComputeNodeStatusDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
