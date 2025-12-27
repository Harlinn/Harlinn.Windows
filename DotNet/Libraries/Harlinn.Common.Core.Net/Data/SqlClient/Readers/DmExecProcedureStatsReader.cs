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

public class DmExecProcedureStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_procedure_stats]";
    public const string TableName = "dm_exec_procedure_stats";
    public const string ShortName = "deps";
    public const string Sql = """
        SELECT
          deps.[database_id],
          deps.[object_id],
          deps.[Type],
          deps.[type_desc],
          deps.[sql_handle],
          deps.[plan_handle],
          deps.[cached_time],
          deps.[last_execution_time],
          deps.[execution_count],
          deps.[total_worker_time],
          deps.[last_worker_time],
          deps.[min_worker_time],
          deps.[max_worker_time],
          deps.[total_physical_reads],
          deps.[last_physical_reads],
          deps.[min_physical_reads],
          deps.[max_physical_reads],
          deps.[total_logical_writes],
          deps.[last_logical_writes],
          deps.[min_logical_writes],
          deps.[max_logical_writes],
          deps.[total_logical_reads],
          deps.[last_logical_reads],
          deps.[min_logical_reads],
          deps.[max_logical_reads],
          deps.[total_elapsed_time],
          deps.[last_elapsed_time],
          deps.[min_elapsed_time],
          deps.[max_elapsed_time],
          deps.[total_spills],
          deps.[last_spills],
          deps.[min_spills],
          deps.[max_spills],
          deps.[total_num_physical_reads],
          deps.[last_num_physical_reads],
          deps.[min_num_physical_reads],
          deps.[max_num_physical_reads],
          deps.[total_page_server_reads],
          deps.[last_page_server_reads],
          deps.[min_page_server_reads],
          deps.[max_page_server_reads],
          deps.[total_num_page_server_reads],
          deps.[last_num_page_server_reads],
          deps.[min_num_page_server_reads],
          deps.[max_num_page_server_reads]
        FROM
          [sys].[dm_exec_procedure_stats] deps
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int SQLHANDLE_FIELD_ID = 4;
    public const int PLANHANDLE_FIELD_ID = 5;
    public const int CACHEDTIME_FIELD_ID = 6;
    public const int LASTEXECUTIONTIME_FIELD_ID = 7;
    public const int EXECUTIONCOUNT_FIELD_ID = 8;
    public const int TOTALWORKERTIME_FIELD_ID = 9;
    public const int LASTWORKERTIME_FIELD_ID = 10;
    public const int MINWORKERTIME_FIELD_ID = 11;
    public const int MAXWORKERTIME_FIELD_ID = 12;
    public const int TOTALPHYSICALREADS_FIELD_ID = 13;
    public const int LASTPHYSICALREADS_FIELD_ID = 14;
    public const int MINPHYSICALREADS_FIELD_ID = 15;
    public const int MAXPHYSICALREADS_FIELD_ID = 16;
    public const int TOTALLOGICALWRITES_FIELD_ID = 17;
    public const int LASTLOGICALWRITES_FIELD_ID = 18;
    public const int MINLOGICALWRITES_FIELD_ID = 19;
    public const int MAXLOGICALWRITES_FIELD_ID = 20;
    public const int TOTALLOGICALREADS_FIELD_ID = 21;
    public const int LASTLOGICALREADS_FIELD_ID = 22;
    public const int MINLOGICALREADS_FIELD_ID = 23;
    public const int MAXLOGICALREADS_FIELD_ID = 24;
    public const int TOTALELAPSEDTIME_FIELD_ID = 25;
    public const int LASTELAPSEDTIME_FIELD_ID = 26;
    public const int MINELAPSEDTIME_FIELD_ID = 27;
    public const int MAXELAPSEDTIME_FIELD_ID = 28;
    public const int TOTALSPILLS_FIELD_ID = 29;
    public const int LASTSPILLS_FIELD_ID = 30;
    public const int MINSPILLS_FIELD_ID = 31;
    public const int MAXSPILLS_FIELD_ID = 32;
    public const int TOTALNUMPHYSICALREADS_FIELD_ID = 33;
    public const int LASTNUMPHYSICALREADS_FIELD_ID = 34;
    public const int MINNUMPHYSICALREADS_FIELD_ID = 35;
    public const int MAXNUMPHYSICALREADS_FIELD_ID = 36;
    public const int TOTALPAGESERVERREADS_FIELD_ID = 37;
    public const int LASTPAGESERVERREADS_FIELD_ID = 38;
    public const int MINPAGESERVERREADS_FIELD_ID = 39;
    public const int MAXPAGESERVERREADS_FIELD_ID = 40;
    public const int TOTALNUMPAGESERVERREADS_FIELD_ID = 41;
    public const int LASTNUMPAGESERVERREADS_FIELD_ID = 42;
    public const int MINNUMPAGESERVERREADS_FIELD_ID = 43;
    public const int MAXNUMPAGESERVERREADS_FIELD_ID = 44;


    public DmExecProcedureStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecProcedureStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecProcedureStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public byte[] SqlHandle
    {
        get
        {
            return base.GetBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public byte[] PlanHandle
    {
        get
        {
            return base.GetBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public DateTime? CachedTime
    {
        get
        {
            return base.GetNullableDateTime(CACHEDTIME_FIELD_ID);
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


    public Types.DmExecProcedureStatsDataType ToDataObject()
    {
        return new Types.DmExecProcedureStatsDataType(DatabaseId,
            ObjectId,
            Type,
            TypeDesc,
            SqlHandle,
            PlanHandle,
            CachedTime,
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
            TotalElapsedTime,
            LastElapsedTime,
            MinElapsedTime,
            MaxElapsedTime,
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

    public List<Types.DmExecProcedureStatsDataType> ToList()
    {
        var list = new List<Types.DmExecProcedureStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
