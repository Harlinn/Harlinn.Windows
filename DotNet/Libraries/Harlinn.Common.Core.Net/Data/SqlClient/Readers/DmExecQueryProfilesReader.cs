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

public class DmExecQueryProfilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_profiles]";
    public const string TableName = "dm_exec_query_profiles";
    public const string ShortName = "deqp";
    public const string Sql = """
        SELECT
          deqp.[session_id],
          deqp.[request_id],
          deqp.[sql_handle],
          deqp.[plan_handle],
          deqp.[physical_operator_name],
          deqp.[node_id],
          deqp.[thread_id],
          deqp.[task_address],
          deqp.[row_count],
          deqp.[rewind_count],
          deqp.[rebind_count],
          deqp.[end_of_scan_count],
          deqp.[estimate_row_count],
          deqp.[first_active_time],
          deqp.[last_active_time],
          deqp.[open_time],
          deqp.[first_row_time],
          deqp.[last_row_time],
          deqp.[close_time],
          deqp.[elapsed_time_ms],
          deqp.[cpu_time_ms],
          deqp.[database_id],
          deqp.[object_id],
          deqp.[index_id],
          deqp.[scan_count],
          deqp.[logical_read_count],
          deqp.[physical_read_count],
          deqp.[read_ahead_count],
          deqp.[write_page_count],
          deqp.[lob_logical_read_count],
          deqp.[lob_physical_read_count],
          deqp.[lob_read_ahead_count],
          deqp.[segment_read_count],
          deqp.[segment_skip_count],
          deqp.[actual_read_row_count],
          deqp.[estimated_read_row_count],
          deqp.[page_server_read_count],
          deqp.[page_server_read_ahead_count],
          deqp.[lob_page_server_read_count],
          deqp.[lob_page_server_read_ahead_count]
        FROM
          [sys].[dm_exec_query_profiles] deqp
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int REQUESTID_FIELD_ID = 1;
    public const int SQLHANDLE_FIELD_ID = 2;
    public const int PLANHANDLE_FIELD_ID = 3;
    public const int PHYSICALOPERATORNAME_FIELD_ID = 4;
    public const int NODEID_FIELD_ID = 5;
    public const int THREADID_FIELD_ID = 6;
    public const int TASKADDRESS_FIELD_ID = 7;
    public const int ROWCOUNT_FIELD_ID = 8;
    public const int REWINDCOUNT_FIELD_ID = 9;
    public const int REBINDCOUNT_FIELD_ID = 10;
    public const int ENDOFSCANCOUNT_FIELD_ID = 11;
    public const int ESTIMATEROWCOUNT_FIELD_ID = 12;
    public const int FIRSTACTIVETIME_FIELD_ID = 13;
    public const int LASTACTIVETIME_FIELD_ID = 14;
    public const int OPENTIME_FIELD_ID = 15;
    public const int FIRSTROWTIME_FIELD_ID = 16;
    public const int LASTROWTIME_FIELD_ID = 17;
    public const int CLOSETIME_FIELD_ID = 18;
    public const int ELAPSEDTIMEMS_FIELD_ID = 19;
    public const int CPUTIMEMS_FIELD_ID = 20;
    public const int DATABASEID_FIELD_ID = 21;
    public const int OBJECTID_FIELD_ID = 22;
    public const int INDEXID_FIELD_ID = 23;
    public const int SCANCOUNT_FIELD_ID = 24;
    public const int LOGICALREADCOUNT_FIELD_ID = 25;
    public const int PHYSICALREADCOUNT_FIELD_ID = 26;
    public const int READAHEADCOUNT_FIELD_ID = 27;
    public const int WRITEPAGECOUNT_FIELD_ID = 28;
    public const int LOBLOGICALREADCOUNT_FIELD_ID = 29;
    public const int LOBPHYSICALREADCOUNT_FIELD_ID = 30;
    public const int LOBREADAHEADCOUNT_FIELD_ID = 31;
    public const int SEGMENTREADCOUNT_FIELD_ID = 32;
    public const int SEGMENTSKIPCOUNT_FIELD_ID = 33;
    public const int ACTUALREADROWCOUNT_FIELD_ID = 34;
    public const int ESTIMATEDREADROWCOUNT_FIELD_ID = 35;
    public const int PAGESERVERREADCOUNT_FIELD_ID = 36;
    public const int PAGESERVERREADAHEADCOUNT_FIELD_ID = 37;
    public const int LOBPAGESERVERREADCOUNT_FIELD_ID = 38;
    public const int LOBPAGESERVERREADAHEADCOUNT_FIELD_ID = 39;


    public DmExecQueryProfilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryProfilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryProfilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
        }
    }

    public int? RequestId
    {
        get
        {
            return base.GetNullableInt32(REQUESTID_FIELD_ID);
        }
    }

    public byte[]? SqlHandle
    {
        get
        {
            return base.GetNullableBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public byte[]? PlanHandle
    {
        get
        {
            return base.GetNullableBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public string? PhysicalOperatorName
    {
        get
        {
            return base.GetNullableString(PHYSICALOPERATORNAME_FIELD_ID);
        }
    }

    public int? NodeId
    {
        get
        {
            return base.GetNullableInt32(NODEID_FIELD_ID);
        }
    }

    public int? ThreadId
    {
        get
        {
            return base.GetNullableInt32(THREADID_FIELD_ID);
        }
    }

    public byte[] TaskAddress
    {
        get
        {
            return base.GetBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public long? RowCount
    {
        get
        {
            return base.GetNullableInt64(ROWCOUNT_FIELD_ID);
        }
    }

    public long? RewindCount
    {
        get
        {
            return base.GetNullableInt64(REWINDCOUNT_FIELD_ID);
        }
    }

    public long? RebindCount
    {
        get
        {
            return base.GetNullableInt64(REBINDCOUNT_FIELD_ID);
        }
    }

    public long? EndOfScanCount
    {
        get
        {
            return base.GetNullableInt64(ENDOFSCANCOUNT_FIELD_ID);
        }
    }

    public long? EstimateRowCount
    {
        get
        {
            return base.GetNullableInt64(ESTIMATEROWCOUNT_FIELD_ID);
        }
    }

    public long? FirstActiveTime
    {
        get
        {
            return base.GetNullableInt64(FIRSTACTIVETIME_FIELD_ID);
        }
    }

    public long? LastActiveTime
    {
        get
        {
            return base.GetNullableInt64(LASTACTIVETIME_FIELD_ID);
        }
    }

    public long? OpenTime
    {
        get
        {
            return base.GetNullableInt64(OPENTIME_FIELD_ID);
        }
    }

    public long? FirstRowTime
    {
        get
        {
            return base.GetNullableInt64(FIRSTROWTIME_FIELD_ID);
        }
    }

    public long? LastRowTime
    {
        get
        {
            return base.GetNullableInt64(LASTROWTIME_FIELD_ID);
        }
    }

    public long? CloseTime
    {
        get
        {
            return base.GetNullableInt64(CLOSETIME_FIELD_ID);
        }
    }

    public long? ElapsedTimeMs
    {
        get
        {
            return base.GetNullableInt64(ELAPSEDTIMEMS_FIELD_ID);
        }
    }

    public long? CpuTimeMs
    {
        get
        {
            return base.GetNullableInt64(CPUTIMEMS_FIELD_ID);
        }
    }

    public short? DatabaseId
    {
        get
        {
            return base.GetNullableInt16(DATABASEID_FIELD_ID);
        }
    }

    public int? ObjectId
    {
        get
        {
            return base.GetNullableInt32(OBJECTID_FIELD_ID);
        }
    }

    public int? IndexId
    {
        get
        {
            return base.GetNullableInt32(INDEXID_FIELD_ID);
        }
    }

    public long? ScanCount
    {
        get
        {
            return base.GetNullableInt64(SCANCOUNT_FIELD_ID);
        }
    }

    public long? LogicalReadCount
    {
        get
        {
            return base.GetNullableInt64(LOGICALREADCOUNT_FIELD_ID);
        }
    }

    public long? PhysicalReadCount
    {
        get
        {
            return base.GetNullableInt64(PHYSICALREADCOUNT_FIELD_ID);
        }
    }

    public long? ReadAheadCount
    {
        get
        {
            return base.GetNullableInt64(READAHEADCOUNT_FIELD_ID);
        }
    }

    public long? WritePageCount
    {
        get
        {
            return base.GetNullableInt64(WRITEPAGECOUNT_FIELD_ID);
        }
    }

    public long? LobLogicalReadCount
    {
        get
        {
            return base.GetNullableInt64(LOBLOGICALREADCOUNT_FIELD_ID);
        }
    }

    public long? LobPhysicalReadCount
    {
        get
        {
            return base.GetNullableInt64(LOBPHYSICALREADCOUNT_FIELD_ID);
        }
    }

    public long? LobReadAheadCount
    {
        get
        {
            return base.GetNullableInt64(LOBREADAHEADCOUNT_FIELD_ID);
        }
    }

    public int? SegmentReadCount
    {
        get
        {
            return base.GetNullableInt32(SEGMENTREADCOUNT_FIELD_ID);
        }
    }

    public int? SegmentSkipCount
    {
        get
        {
            return base.GetNullableInt32(SEGMENTSKIPCOUNT_FIELD_ID);
        }
    }

    public long? ActualReadRowCount
    {
        get
        {
            return base.GetNullableInt64(ACTUALREADROWCOUNT_FIELD_ID);
        }
    }

    public long? EstimatedReadRowCount
    {
        get
        {
            return base.GetNullableInt64(ESTIMATEDREADROWCOUNT_FIELD_ID);
        }
    }

    public long? PageServerReadCount
    {
        get
        {
            return base.GetNullableInt64(PAGESERVERREADCOUNT_FIELD_ID);
        }
    }

    public long? PageServerReadAheadCount
    {
        get
        {
            return base.GetNullableInt64(PAGESERVERREADAHEADCOUNT_FIELD_ID);
        }
    }

    public long? LobPageServerReadCount
    {
        get
        {
            return base.GetNullableInt64(LOBPAGESERVERREADCOUNT_FIELD_ID);
        }
    }

    public long? LobPageServerReadAheadCount
    {
        get
        {
            return base.GetNullableInt64(LOBPAGESERVERREADAHEADCOUNT_FIELD_ID);
        }
    }


    public Types.DmExecQueryProfilesDataType ToDataObject()
    {
        return new Types.DmExecQueryProfilesDataType(SessionId,
            RequestId,
            SqlHandle,
            PlanHandle,
            PhysicalOperatorName,
            NodeId,
            ThreadId,
            TaskAddress,
            RowCount,
            RewindCount,
            RebindCount,
            EndOfScanCount,
            EstimateRowCount,
            FirstActiveTime,
            LastActiveTime,
            OpenTime,
            FirstRowTime,
            LastRowTime,
            CloseTime,
            ElapsedTimeMs,
            CpuTimeMs,
            DatabaseId,
            ObjectId,
            IndexId,
            ScanCount,
            LogicalReadCount,
            PhysicalReadCount,
            ReadAheadCount,
            WritePageCount,
            LobLogicalReadCount,
            LobPhysicalReadCount,
            LobReadAheadCount,
            SegmentReadCount,
            SegmentSkipCount,
            ActualReadRowCount,
            EstimatedReadRowCount,
            PageServerReadCount,
            PageServerReadAheadCount,
            LobPageServerReadCount,
            LobPageServerReadAheadCount);
    }

    public List<Types.DmExecQueryProfilesDataType> ToList()
    {
        var list = new List<Types.DmExecQueryProfilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
