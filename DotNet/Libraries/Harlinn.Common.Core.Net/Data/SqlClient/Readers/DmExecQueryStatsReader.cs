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

public class DmExecQueryStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_stats]";
    public const string TableName = "dm_exec_query_stats";
    public const string ShortName = "deqs";
    public const string Sql = """
        SELECT
          deqs.[sql_handle],
          deqs.[statement_start_offset],
          deqs.[statement_end_offset],
          deqs.[plan_generation_num],
          deqs.[plan_handle],
          deqs.[creation_time],
          deqs.[last_execution_time],
          deqs.[execution_count],
          deqs.[total_worker_time],
          deqs.[last_worker_time],
          deqs.[min_worker_time],
          deqs.[max_worker_time],
          deqs.[total_physical_reads],
          deqs.[last_physical_reads],
          deqs.[min_physical_reads],
          deqs.[max_physical_reads],
          deqs.[total_logical_writes],
          deqs.[last_logical_writes],
          deqs.[min_logical_writes],
          deqs.[max_logical_writes],
          deqs.[total_logical_reads],
          deqs.[last_logical_reads],
          deqs.[min_logical_reads],
          deqs.[max_logical_reads],
          deqs.[total_clr_time],
          deqs.[last_clr_time],
          deqs.[min_clr_time],
          deqs.[max_clr_time],
          deqs.[total_elapsed_time],
          deqs.[last_elapsed_time],
          deqs.[min_elapsed_time],
          deqs.[max_elapsed_time],
          deqs.[query_hash],
          deqs.[query_plan_hash],
          deqs.[total_rows],
          deqs.[last_rows],
          deqs.[min_rows],
          deqs.[max_rows],
          deqs.[statement_sql_handle],
          deqs.[statement_context_id],
          deqs.[total_dop],
          deqs.[last_dop],
          deqs.[min_dop],
          deqs.[max_dop],
          deqs.[total_grant_kb],
          deqs.[last_grant_kb],
          deqs.[min_grant_kb],
          deqs.[max_grant_kb],
          deqs.[total_used_grant_kb],
          deqs.[last_used_grant_kb],
          deqs.[min_used_grant_kb],
          deqs.[max_used_grant_kb],
          deqs.[total_ideal_grant_kb],
          deqs.[last_ideal_grant_kb],
          deqs.[min_ideal_grant_kb],
          deqs.[max_ideal_grant_kb],
          deqs.[total_reserved_threads],
          deqs.[last_reserved_threads],
          deqs.[min_reserved_threads],
          deqs.[max_reserved_threads],
          deqs.[total_used_threads],
          deqs.[last_used_threads],
          deqs.[min_used_threads],
          deqs.[max_used_threads],
          deqs.[total_columnstore_segment_reads],
          deqs.[last_columnstore_segment_reads],
          deqs.[min_columnstore_segment_reads],
          deqs.[max_columnstore_segment_reads],
          deqs.[total_columnstore_segment_skips],
          deqs.[last_columnstore_segment_skips],
          deqs.[min_columnstore_segment_skips],
          deqs.[max_columnstore_segment_skips],
          deqs.[total_spills],
          deqs.[last_spills],
          deqs.[min_spills],
          deqs.[max_spills],
          deqs.[total_num_physical_reads],
          deqs.[last_num_physical_reads],
          deqs.[min_num_physical_reads],
          deqs.[max_num_physical_reads],
          deqs.[total_page_server_reads],
          deqs.[last_page_server_reads],
          deqs.[min_page_server_reads],
          deqs.[max_page_server_reads],
          deqs.[total_num_page_server_reads],
          deqs.[last_num_page_server_reads],
          deqs.[min_num_page_server_reads],
          deqs.[max_num_page_server_reads]
        FROM
          [sys].[dm_exec_query_stats] deqs
        """;

    public const int SQLHANDLE_FIELD_ID = 0;
    public const int STATEMENTSTARTOFFSET_FIELD_ID = 1;
    public const int STATEMENTENDOFFSET_FIELD_ID = 2;
    public const int PLANGENERATIONNUM_FIELD_ID = 3;
    public const int PLANHANDLE_FIELD_ID = 4;
    public const int CREATIONTIME_FIELD_ID = 5;
    public const int LASTEXECUTIONTIME_FIELD_ID = 6;
    public const int EXECUTIONCOUNT_FIELD_ID = 7;
    public const int TOTALWORKERTIME_FIELD_ID = 8;
    public const int LASTWORKERTIME_FIELD_ID = 9;
    public const int MINWORKERTIME_FIELD_ID = 10;
    public const int MAXWORKERTIME_FIELD_ID = 11;
    public const int TOTALPHYSICALREADS_FIELD_ID = 12;
    public const int LASTPHYSICALREADS_FIELD_ID = 13;
    public const int MINPHYSICALREADS_FIELD_ID = 14;
    public const int MAXPHYSICALREADS_FIELD_ID = 15;
    public const int TOTALLOGICALWRITES_FIELD_ID = 16;
    public const int LASTLOGICALWRITES_FIELD_ID = 17;
    public const int MINLOGICALWRITES_FIELD_ID = 18;
    public const int MAXLOGICALWRITES_FIELD_ID = 19;
    public const int TOTALLOGICALREADS_FIELD_ID = 20;
    public const int LASTLOGICALREADS_FIELD_ID = 21;
    public const int MINLOGICALREADS_FIELD_ID = 22;
    public const int MAXLOGICALREADS_FIELD_ID = 23;
    public const int TOTALCLRTIME_FIELD_ID = 24;
    public const int LASTCLRTIME_FIELD_ID = 25;
    public const int MINCLRTIME_FIELD_ID = 26;
    public const int MAXCLRTIME_FIELD_ID = 27;
    public const int TOTALELAPSEDTIME_FIELD_ID = 28;
    public const int LASTELAPSEDTIME_FIELD_ID = 29;
    public const int MINELAPSEDTIME_FIELD_ID = 30;
    public const int MAXELAPSEDTIME_FIELD_ID = 31;
    public const int QUERYHASH_FIELD_ID = 32;
    public const int QUERYPLANHASH_FIELD_ID = 33;
    public const int TOTALROWS_FIELD_ID = 34;
    public const int LASTROWS_FIELD_ID = 35;
    public const int MINROWS_FIELD_ID = 36;
    public const int MAXROWS_FIELD_ID = 37;
    public const int STATEMENTSQLHANDLE_FIELD_ID = 38;
    public const int STATEMENTCONTEXTID_FIELD_ID = 39;
    public const int TOTALDOP_FIELD_ID = 40;
    public const int LASTDOP_FIELD_ID = 41;
    public const int MINDOP_FIELD_ID = 42;
    public const int MAXDOP_FIELD_ID = 43;
    public const int TOTALGRANTKB_FIELD_ID = 44;
    public const int LASTGRANTKB_FIELD_ID = 45;
    public const int MINGRANTKB_FIELD_ID = 46;
    public const int MAXGRANTKB_FIELD_ID = 47;
    public const int TOTALUSEDGRANTKB_FIELD_ID = 48;
    public const int LASTUSEDGRANTKB_FIELD_ID = 49;
    public const int MINUSEDGRANTKB_FIELD_ID = 50;
    public const int MAXUSEDGRANTKB_FIELD_ID = 51;
    public const int TOTALIDEALGRANTKB_FIELD_ID = 52;
    public const int LASTIDEALGRANTKB_FIELD_ID = 53;
    public const int MINIDEALGRANTKB_FIELD_ID = 54;
    public const int MAXIDEALGRANTKB_FIELD_ID = 55;
    public const int TOTALRESERVEDTHREADS_FIELD_ID = 56;
    public const int LASTRESERVEDTHREADS_FIELD_ID = 57;
    public const int MINRESERVEDTHREADS_FIELD_ID = 58;
    public const int MAXRESERVEDTHREADS_FIELD_ID = 59;
    public const int TOTALUSEDTHREADS_FIELD_ID = 60;
    public const int LASTUSEDTHREADS_FIELD_ID = 61;
    public const int MINUSEDTHREADS_FIELD_ID = 62;
    public const int MAXUSEDTHREADS_FIELD_ID = 63;
    public const int TOTALCOLUMNSTORESEGMENTREADS_FIELD_ID = 64;
    public const int LASTCOLUMNSTORESEGMENTREADS_FIELD_ID = 65;
    public const int MINCOLUMNSTORESEGMENTREADS_FIELD_ID = 66;
    public const int MAXCOLUMNSTORESEGMENTREADS_FIELD_ID = 67;
    public const int TOTALCOLUMNSTORESEGMENTSKIPS_FIELD_ID = 68;
    public const int LASTCOLUMNSTORESEGMENTSKIPS_FIELD_ID = 69;
    public const int MINCOLUMNSTORESEGMENTSKIPS_FIELD_ID = 70;
    public const int MAXCOLUMNSTORESEGMENTSKIPS_FIELD_ID = 71;
    public const int TOTALSPILLS_FIELD_ID = 72;
    public const int LASTSPILLS_FIELD_ID = 73;
    public const int MINSPILLS_FIELD_ID = 74;
    public const int MAXSPILLS_FIELD_ID = 75;
    public const int TOTALNUMPHYSICALREADS_FIELD_ID = 76;
    public const int LASTNUMPHYSICALREADS_FIELD_ID = 77;
    public const int MINNUMPHYSICALREADS_FIELD_ID = 78;
    public const int MAXNUMPHYSICALREADS_FIELD_ID = 79;
    public const int TOTALPAGESERVERREADS_FIELD_ID = 80;
    public const int LASTPAGESERVERREADS_FIELD_ID = 81;
    public const int MINPAGESERVERREADS_FIELD_ID = 82;
    public const int MAXPAGESERVERREADS_FIELD_ID = 83;
    public const int TOTALNUMPAGESERVERREADS_FIELD_ID = 84;
    public const int LASTNUMPAGESERVERREADS_FIELD_ID = 85;
    public const int MINNUMPAGESERVERREADS_FIELD_ID = 86;
    public const int MAXNUMPAGESERVERREADS_FIELD_ID = 87;


    public DmExecQueryStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] SqlHandle
    {
        get
        {
            return base.GetBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public int StatementStartOffset
    {
        get
        {
            return base.GetInt32(STATEMENTSTARTOFFSET_FIELD_ID);
        }
    }

    public int StatementEndOffset
    {
        get
        {
            return base.GetInt32(STATEMENTENDOFFSET_FIELD_ID);
        }
    }

    public long? PlanGenerationNum
    {
        get
        {
            return base.GetNullableInt64(PLANGENERATIONNUM_FIELD_ID);
        }
    }

    public byte[] PlanHandle
    {
        get
        {
            return base.GetBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public DateTime? CreationTime
    {
        get
        {
            return base.GetNullableDateTime(CREATIONTIME_FIELD_ID);
        }
    }

    public DateTime? LastExecutionTime
    {
        get
        {
            return base.GetNullableDateTime(LASTEXECUTIONTIME_FIELD_ID);
        }
    }

    public long ExecutionCount
    {
        get
        {
            return base.GetInt64(EXECUTIONCOUNT_FIELD_ID);
        }
    }

    public long TotalWorkerTime
    {
        get
        {
            return base.GetInt64(TOTALWORKERTIME_FIELD_ID);
        }
    }

    public long LastWorkerTime
    {
        get
        {
            return base.GetInt64(LASTWORKERTIME_FIELD_ID);
        }
    }

    public long MinWorkerTime
    {
        get
        {
            return base.GetInt64(MINWORKERTIME_FIELD_ID);
        }
    }

    public long MaxWorkerTime
    {
        get
        {
            return base.GetInt64(MAXWORKERTIME_FIELD_ID);
        }
    }

    public long TotalPhysicalReads
    {
        get
        {
            return base.GetInt64(TOTALPHYSICALREADS_FIELD_ID);
        }
    }

    public long LastPhysicalReads
    {
        get
        {
            return base.GetInt64(LASTPHYSICALREADS_FIELD_ID);
        }
    }

    public long MinPhysicalReads
    {
        get
        {
            return base.GetInt64(MINPHYSICALREADS_FIELD_ID);
        }
    }

    public long MaxPhysicalReads
    {
        get
        {
            return base.GetInt64(MAXPHYSICALREADS_FIELD_ID);
        }
    }

    public long TotalLogicalWrites
    {
        get
        {
            return base.GetInt64(TOTALLOGICALWRITES_FIELD_ID);
        }
    }

    public long LastLogicalWrites
    {
        get
        {
            return base.GetInt64(LASTLOGICALWRITES_FIELD_ID);
        }
    }

    public long MinLogicalWrites
    {
        get
        {
            return base.GetInt64(MINLOGICALWRITES_FIELD_ID);
        }
    }

    public long MaxLogicalWrites
    {
        get
        {
            return base.GetInt64(MAXLOGICALWRITES_FIELD_ID);
        }
    }

    public long TotalLogicalReads
    {
        get
        {
            return base.GetInt64(TOTALLOGICALREADS_FIELD_ID);
        }
    }

    public long LastLogicalReads
    {
        get
        {
            return base.GetInt64(LASTLOGICALREADS_FIELD_ID);
        }
    }

    public long MinLogicalReads
    {
        get
        {
            return base.GetInt64(MINLOGICALREADS_FIELD_ID);
        }
    }

    public long MaxLogicalReads
    {
        get
        {
            return base.GetInt64(MAXLOGICALREADS_FIELD_ID);
        }
    }

    public long TotalClrTime
    {
        get
        {
            return base.GetInt64(TOTALCLRTIME_FIELD_ID);
        }
    }

    public long LastClrTime
    {
        get
        {
            return base.GetInt64(LASTCLRTIME_FIELD_ID);
        }
    }

    public long MinClrTime
    {
        get
        {
            return base.GetInt64(MINCLRTIME_FIELD_ID);
        }
    }

    public long MaxClrTime
    {
        get
        {
            return base.GetInt64(MAXCLRTIME_FIELD_ID);
        }
    }

    public long TotalElapsedTime
    {
        get
        {
            return base.GetInt64(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public long LastElapsedTime
    {
        get
        {
            return base.GetInt64(LASTELAPSEDTIME_FIELD_ID);
        }
    }

    public long MinElapsedTime
    {
        get
        {
            return base.GetInt64(MINELAPSEDTIME_FIELD_ID);
        }
    }

    public long MaxElapsedTime
    {
        get
        {
            return base.GetInt64(MAXELAPSEDTIME_FIELD_ID);
        }
    }

    public byte[]? QueryHash
    {
        get
        {
            return base.GetNullableBinary(QUERYHASH_FIELD_ID);
        }
    }

    public byte[]? QueryPlanHash
    {
        get
        {
            return base.GetNullableBinary(QUERYPLANHASH_FIELD_ID);
        }
    }

    public long? TotalRows
    {
        get
        {
            return base.GetNullableInt64(TOTALROWS_FIELD_ID);
        }
    }

    public long? LastRows
    {
        get
        {
            return base.GetNullableInt64(LASTROWS_FIELD_ID);
        }
    }

    public long? MinRows
    {
        get
        {
            return base.GetNullableInt64(MINROWS_FIELD_ID);
        }
    }

    public long? MaxRows
    {
        get
        {
            return base.GetNullableInt64(MAXROWS_FIELD_ID);
        }
    }

    public byte[]? StatementSqlHandle
    {
        get
        {
            return base.GetNullableBinary(STATEMENTSQLHANDLE_FIELD_ID);
        }
    }

    public long? StatementContextId
    {
        get
        {
            return base.GetNullableInt64(STATEMENTCONTEXTID_FIELD_ID);
        }
    }

    public long? TotalDop
    {
        get
        {
            return base.GetNullableInt64(TOTALDOP_FIELD_ID);
        }
    }

    public long? LastDop
    {
        get
        {
            return base.GetNullableInt64(LASTDOP_FIELD_ID);
        }
    }

    public long? MinDop
    {
        get
        {
            return base.GetNullableInt64(MINDOP_FIELD_ID);
        }
    }

    public long? MaxDop
    {
        get
        {
            return base.GetNullableInt64(MAXDOP_FIELD_ID);
        }
    }

    public long? TotalGrantKb
    {
        get
        {
            return base.GetNullableInt64(TOTALGRANTKB_FIELD_ID);
        }
    }

    public long? LastGrantKb
    {
        get
        {
            return base.GetNullableInt64(LASTGRANTKB_FIELD_ID);
        }
    }

    public long? MinGrantKb
    {
        get
        {
            return base.GetNullableInt64(MINGRANTKB_FIELD_ID);
        }
    }

    public long? MaxGrantKb
    {
        get
        {
            return base.GetNullableInt64(MAXGRANTKB_FIELD_ID);
        }
    }

    public long? TotalUsedGrantKb
    {
        get
        {
            return base.GetNullableInt64(TOTALUSEDGRANTKB_FIELD_ID);
        }
    }

    public long? LastUsedGrantKb
    {
        get
        {
            return base.GetNullableInt64(LASTUSEDGRANTKB_FIELD_ID);
        }
    }

    public long? MinUsedGrantKb
    {
        get
        {
            return base.GetNullableInt64(MINUSEDGRANTKB_FIELD_ID);
        }
    }

    public long? MaxUsedGrantKb
    {
        get
        {
            return base.GetNullableInt64(MAXUSEDGRANTKB_FIELD_ID);
        }
    }

    public long? TotalIdealGrantKb
    {
        get
        {
            return base.GetNullableInt64(TOTALIDEALGRANTKB_FIELD_ID);
        }
    }

    public long? LastIdealGrantKb
    {
        get
        {
            return base.GetNullableInt64(LASTIDEALGRANTKB_FIELD_ID);
        }
    }

    public long? MinIdealGrantKb
    {
        get
        {
            return base.GetNullableInt64(MINIDEALGRANTKB_FIELD_ID);
        }
    }

    public long? MaxIdealGrantKb
    {
        get
        {
            return base.GetNullableInt64(MAXIDEALGRANTKB_FIELD_ID);
        }
    }

    public long? TotalReservedThreads
    {
        get
        {
            return base.GetNullableInt64(TOTALRESERVEDTHREADS_FIELD_ID);
        }
    }

    public long? LastReservedThreads
    {
        get
        {
            return base.GetNullableInt64(LASTRESERVEDTHREADS_FIELD_ID);
        }
    }

    public long? MinReservedThreads
    {
        get
        {
            return base.GetNullableInt64(MINRESERVEDTHREADS_FIELD_ID);
        }
    }

    public long? MaxReservedThreads
    {
        get
        {
            return base.GetNullableInt64(MAXRESERVEDTHREADS_FIELD_ID);
        }
    }

    public long? TotalUsedThreads
    {
        get
        {
            return base.GetNullableInt64(TOTALUSEDTHREADS_FIELD_ID);
        }
    }

    public long? LastUsedThreads
    {
        get
        {
            return base.GetNullableInt64(LASTUSEDTHREADS_FIELD_ID);
        }
    }

    public long? MinUsedThreads
    {
        get
        {
            return base.GetNullableInt64(MINUSEDTHREADS_FIELD_ID);
        }
    }

    public long? MaxUsedThreads
    {
        get
        {
            return base.GetNullableInt64(MAXUSEDTHREADS_FIELD_ID);
        }
    }

    public long? TotalColumnstoreSegmentReads
    {
        get
        {
            return base.GetNullableInt64(TOTALCOLUMNSTORESEGMENTREADS_FIELD_ID);
        }
    }

    public long? LastColumnstoreSegmentReads
    {
        get
        {
            return base.GetNullableInt64(LASTCOLUMNSTORESEGMENTREADS_FIELD_ID);
        }
    }

    public long? MinColumnstoreSegmentReads
    {
        get
        {
            return base.GetNullableInt64(MINCOLUMNSTORESEGMENTREADS_FIELD_ID);
        }
    }

    public long? MaxColumnstoreSegmentReads
    {
        get
        {
            return base.GetNullableInt64(MAXCOLUMNSTORESEGMENTREADS_FIELD_ID);
        }
    }

    public long? TotalColumnstoreSegmentSkips
    {
        get
        {
            return base.GetNullableInt64(TOTALCOLUMNSTORESEGMENTSKIPS_FIELD_ID);
        }
    }

    public long? LastColumnstoreSegmentSkips
    {
        get
        {
            return base.GetNullableInt64(LASTCOLUMNSTORESEGMENTSKIPS_FIELD_ID);
        }
    }

    public long? MinColumnstoreSegmentSkips
    {
        get
        {
            return base.GetNullableInt64(MINCOLUMNSTORESEGMENTSKIPS_FIELD_ID);
        }
    }

    public long? MaxColumnstoreSegmentSkips
    {
        get
        {
            return base.GetNullableInt64(MAXCOLUMNSTORESEGMENTSKIPS_FIELD_ID);
        }
    }

    public long? TotalSpills
    {
        get
        {
            return base.GetNullableInt64(TOTALSPILLS_FIELD_ID);
        }
    }

    public long? LastSpills
    {
        get
        {
            return base.GetNullableInt64(LASTSPILLS_FIELD_ID);
        }
    }

    public long? MinSpills
    {
        get
        {
            return base.GetNullableInt64(MINSPILLS_FIELD_ID);
        }
    }

    public long? MaxSpills
    {
        get
        {
            return base.GetNullableInt64(MAXSPILLS_FIELD_ID);
        }
    }

    public long TotalNumPhysicalReads
    {
        get
        {
            return base.GetInt64(TOTALNUMPHYSICALREADS_FIELD_ID);
        }
    }

    public long LastNumPhysicalReads
    {
        get
        {
            return base.GetInt64(LASTNUMPHYSICALREADS_FIELD_ID);
        }
    }

    public long MinNumPhysicalReads
    {
        get
        {
            return base.GetInt64(MINNUMPHYSICALREADS_FIELD_ID);
        }
    }

    public long MaxNumPhysicalReads
    {
        get
        {
            return base.GetInt64(MAXNUMPHYSICALREADS_FIELD_ID);
        }
    }

    public long TotalPageServerReads
    {
        get
        {
            return base.GetInt64(TOTALPAGESERVERREADS_FIELD_ID);
        }
    }

    public long LastPageServerReads
    {
        get
        {
            return base.GetInt64(LASTPAGESERVERREADS_FIELD_ID);
        }
    }

    public long MinPageServerReads
    {
        get
        {
            return base.GetInt64(MINPAGESERVERREADS_FIELD_ID);
        }
    }

    public long MaxPageServerReads
    {
        get
        {
            return base.GetInt64(MAXPAGESERVERREADS_FIELD_ID);
        }
    }

    public long TotalNumPageServerReads
    {
        get
        {
            return base.GetInt64(TOTALNUMPAGESERVERREADS_FIELD_ID);
        }
    }

    public long LastNumPageServerReads
    {
        get
        {
            return base.GetInt64(LASTNUMPAGESERVERREADS_FIELD_ID);
        }
    }

    public long MinNumPageServerReads
    {
        get
        {
            return base.GetInt64(MINNUMPAGESERVERREADS_FIELD_ID);
        }
    }

    public long MaxNumPageServerReads
    {
        get
        {
            return base.GetInt64(MAXNUMPAGESERVERREADS_FIELD_ID);
        }
    }


    public Types.DmExecQueryStatsDataType ToDataObject()
    {
        return new Types.DmExecQueryStatsDataType(SqlHandle,
            StatementStartOffset,
            StatementEndOffset,
            PlanGenerationNum,
            PlanHandle,
            CreationTime,
            LastExecutionTime,
            ExecutionCount,
            TotalWorkerTime,
            LastWorkerTime,
            MinWorkerTime,
            MaxWorkerTime,
            TotalPhysicalReads,
            LastPhysicalReads,
            MinPhysicalReads,
            MaxPhysicalReads,
            TotalLogicalWrites,
            LastLogicalWrites,
            MinLogicalWrites,
            MaxLogicalWrites,
            TotalLogicalReads,
            LastLogicalReads,
            MinLogicalReads,
            MaxLogicalReads,
            TotalClrTime,
            LastClrTime,
            MinClrTime,
            MaxClrTime,
            TotalElapsedTime,
            LastElapsedTime,
            MinElapsedTime,
            MaxElapsedTime,
            QueryHash,
            QueryPlanHash,
            TotalRows,
            LastRows,
            MinRows,
            MaxRows,
            StatementSqlHandle,
            StatementContextId,
            TotalDop,
            LastDop,
            MinDop,
            MaxDop,
            TotalGrantKb,
            LastGrantKb,
            MinGrantKb,
            MaxGrantKb,
            TotalUsedGrantKb,
            LastUsedGrantKb,
            MinUsedGrantKb,
            MaxUsedGrantKb,
            TotalIdealGrantKb,
            LastIdealGrantKb,
            MinIdealGrantKb,
            MaxIdealGrantKb,
            TotalReservedThreads,
            LastReservedThreads,
            MinReservedThreads,
            MaxReservedThreads,
            TotalUsedThreads,
            LastUsedThreads,
            MinUsedThreads,
            MaxUsedThreads,
            TotalColumnstoreSegmentReads,
            LastColumnstoreSegmentReads,
            MinColumnstoreSegmentReads,
            MaxColumnstoreSegmentReads,
            TotalColumnstoreSegmentSkips,
            LastColumnstoreSegmentSkips,
            MinColumnstoreSegmentSkips,
            MaxColumnstoreSegmentSkips,
            TotalSpills,
            LastSpills,
            MinSpills,
            MaxSpills,
            TotalNumPhysicalReads,
            LastNumPhysicalReads,
            MinNumPhysicalReads,
            MaxNumPhysicalReads,
            TotalPageServerReads,
            LastPageServerReads,
            MinPageServerReads,
            MaxPageServerReads,
            TotalNumPageServerReads,
            LastNumPageServerReads,
            MinNumPageServerReads,
            MaxNumPageServerReads);
    }

    public List<Types.DmExecQueryStatsDataType> ToList()
    {
        var list = new List<Types.DmExecQueryStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
