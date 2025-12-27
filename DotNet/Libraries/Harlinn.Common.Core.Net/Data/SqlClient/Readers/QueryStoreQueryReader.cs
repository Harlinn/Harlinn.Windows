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

public class QueryStoreQueryReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_query]";
    public const string TableName = "query_store_query";
    public const string ShortName = "qsq";
    public const string Sql = """
        SELECT
          qsq.[query_id],
          qsq.[query_text_id],
          qsq.[context_settings_id],
          qsq.[object_id],
          qsq.[batch_sql_handle],
          qsq.[query_hash],
          qsq.[is_internal_query],
          qsq.[query_parameterization_type],
          qsq.[query_parameterization_type_desc],
          qsq.[initial_compile_start_time],
          qsq.[last_compile_start_time],
          qsq.[last_execution_time],
          qsq.[last_compile_batch_sql_handle],
          qsq.[last_compile_batch_offset_start],
          qsq.[last_compile_batch_offset_end],
          qsq.[count_compiles],
          qsq.[avg_compile_duration],
          qsq.[last_compile_duration],
          qsq.[avg_bind_duration],
          qsq.[last_bind_duration],
          qsq.[avg_bind_cpu_time],
          qsq.[last_bind_cpu_time],
          qsq.[avg_optimize_duration],
          qsq.[last_optimize_duration],
          qsq.[avg_optimize_cpu_time],
          qsq.[last_optimize_cpu_time],
          qsq.[avg_compile_memory_kb],
          qsq.[last_compile_memory_kb],
          qsq.[max_compile_memory_kb],
          qsq.[is_clouddb_internal_query]
        FROM
          [sys].[query_store_query] qsq
        """;

    public const int QUERYID_FIELD_ID = 0;
    public const int QUERYTEXTID_FIELD_ID = 1;
    public const int CONTEXTSETTINGSID_FIELD_ID = 2;
    public const int OBJECTID_FIELD_ID = 3;
    public const int BATCHSQLHANDLE_FIELD_ID = 4;
    public const int QUERYHASH_FIELD_ID = 5;
    public const int ISINTERNALQUERY_FIELD_ID = 6;
    public const int QUERYPARAMETERIZATIONTYPE_FIELD_ID = 7;
    public const int QUERYPARAMETERIZATIONTYPEDESC_FIELD_ID = 8;
    public const int INITIALCOMPILESTARTTIME_FIELD_ID = 9;
    public const int LASTCOMPILESTARTTIME_FIELD_ID = 10;
    public const int LASTEXECUTIONTIME_FIELD_ID = 11;
    public const int LASTCOMPILEBATCHSQLHANDLE_FIELD_ID = 12;
    public const int LASTCOMPILEBATCHOFFSETSTART_FIELD_ID = 13;
    public const int LASTCOMPILEBATCHOFFSETEND_FIELD_ID = 14;
    public const int COUNTCOMPILES_FIELD_ID = 15;
    public const int AVGCOMPILEDURATION_FIELD_ID = 16;
    public const int LASTCOMPILEDURATION_FIELD_ID = 17;
    public const int AVGBINDDURATION_FIELD_ID = 18;
    public const int LASTBINDDURATION_FIELD_ID = 19;
    public const int AVGBINDCPUTIME_FIELD_ID = 20;
    public const int LASTBINDCPUTIME_FIELD_ID = 21;
    public const int AVGOPTIMIZEDURATION_FIELD_ID = 22;
    public const int LASTOPTIMIZEDURATION_FIELD_ID = 23;
    public const int AVGOPTIMIZECPUTIME_FIELD_ID = 24;
    public const int LASTOPTIMIZECPUTIME_FIELD_ID = 25;
    public const int AVGCOMPILEMEMORYKB_FIELD_ID = 26;
    public const int LASTCOMPILEMEMORYKB_FIELD_ID = 27;
    public const int MAXCOMPILEMEMORYKB_FIELD_ID = 28;
    public const int ISCLOUDDBINTERNALQUERY_FIELD_ID = 29;


    public QueryStoreQueryReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStoreQueryReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStoreQueryReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long QueryId
    {
        get
        {
            return base.GetInt64(QUERYID_FIELD_ID);
        }
    }

    public long QueryTextId
    {
        get
        {
            return base.GetInt64(QUERYTEXTID_FIELD_ID);
        }
    }

    public long ContextSettingsId
    {
        get
        {
            return base.GetInt64(CONTEXTSETTINGSID_FIELD_ID);
        }
    }

    public long? ObjectId
    {
        get
        {
            return base.GetNullableInt64(OBJECTID_FIELD_ID);
        }
    }

    public byte[]? BatchSqlHandle
    {
        get
        {
            return base.GetNullableBinary(BATCHSQLHANDLE_FIELD_ID);
        }
    }

    public byte[] QueryHash
    {
        get
        {
            return base.GetBinary(QUERYHASH_FIELD_ID);
        }
    }

    public bool IsInternalQuery
    {
        get
        {
            return base.GetBoolean(ISINTERNALQUERY_FIELD_ID);
        }
    }

    public byte QueryParameterizationType
    {
        get
        {
            return base.GetByte(QUERYPARAMETERIZATIONTYPE_FIELD_ID);
        }
    }

    public string? QueryParameterizationTypeDesc
    {
        get
        {
            return base.GetNullableString(QUERYPARAMETERIZATIONTYPEDESC_FIELD_ID);
        }
    }

    public DateTime InitialCompileStartTime
    {
        get
        {
            return base.GetDateTime(INITIALCOMPILESTARTTIME_FIELD_ID);
        }
    }

    public DateTime? LastCompileStartTime
    {
        get
        {
            return base.GetNullableDateTime(LASTCOMPILESTARTTIME_FIELD_ID);
        }
    }

    public DateTime? LastExecutionTime
    {
        get
        {
            return base.GetNullableDateTime(LASTEXECUTIONTIME_FIELD_ID);
        }
    }

    public byte[]? LastCompileBatchSqlHandle
    {
        get
        {
            return base.GetNullableBinary(LASTCOMPILEBATCHSQLHANDLE_FIELD_ID);
        }
    }

    public long? LastCompileBatchOffsetStart
    {
        get
        {
            return base.GetNullableInt64(LASTCOMPILEBATCHOFFSETSTART_FIELD_ID);
        }
    }

    public long? LastCompileBatchOffsetEnd
    {
        get
        {
            return base.GetNullableInt64(LASTCOMPILEBATCHOFFSETEND_FIELD_ID);
        }
    }

    public long? CountCompiles
    {
        get
        {
            return base.GetNullableInt64(COUNTCOMPILES_FIELD_ID);
        }
    }

    public double? AvgCompileDuration
    {
        get
        {
            return base.GetNullableDouble(AVGCOMPILEDURATION_FIELD_ID);
        }
    }

    public long? LastCompileDuration
    {
        get
        {
            return base.GetNullableInt64(LASTCOMPILEDURATION_FIELD_ID);
        }
    }

    public double? AvgBindDuration
    {
        get
        {
            return base.GetNullableDouble(AVGBINDDURATION_FIELD_ID);
        }
    }

    public long? LastBindDuration
    {
        get
        {
            return base.GetNullableInt64(LASTBINDDURATION_FIELD_ID);
        }
    }

    public double? AvgBindCpuTime
    {
        get
        {
            return base.GetNullableDouble(AVGBINDCPUTIME_FIELD_ID);
        }
    }

    public long? LastBindCpuTime
    {
        get
        {
            return base.GetNullableInt64(LASTBINDCPUTIME_FIELD_ID);
        }
    }

    public double? AvgOptimizeDuration
    {
        get
        {
            return base.GetNullableDouble(AVGOPTIMIZEDURATION_FIELD_ID);
        }
    }

    public long? LastOptimizeDuration
    {
        get
        {
            return base.GetNullableInt64(LASTOPTIMIZEDURATION_FIELD_ID);
        }
    }

    public double? AvgOptimizeCpuTime
    {
        get
        {
            return base.GetNullableDouble(AVGOPTIMIZECPUTIME_FIELD_ID);
        }
    }

    public long? LastOptimizeCpuTime
    {
        get
        {
            return base.GetNullableInt64(LASTOPTIMIZECPUTIME_FIELD_ID);
        }
    }

    public double? AvgCompileMemoryKb
    {
        get
        {
            return base.GetNullableDouble(AVGCOMPILEMEMORYKB_FIELD_ID);
        }
    }

    public long? LastCompileMemoryKb
    {
        get
        {
            return base.GetNullableInt64(LASTCOMPILEMEMORYKB_FIELD_ID);
        }
    }

    public long? MaxCompileMemoryKb
    {
        get
        {
            return base.GetNullableInt64(MAXCOMPILEMEMORYKB_FIELD_ID);
        }
    }

    public bool? IsClouddbInternalQuery
    {
        get
        {
            return base.GetNullableBoolean(ISCLOUDDBINTERNALQUERY_FIELD_ID);
        }
    }


    public Types.QueryStoreQueryDataType ToDataObject()
    {
        return new Types.QueryStoreQueryDataType(QueryId,
            QueryTextId,
            ContextSettingsId,
            ObjectId,
            BatchSqlHandle,
            QueryHash,
            IsInternalQuery,
            QueryParameterizationType,
            QueryParameterizationTypeDesc,
            InitialCompileStartTime,
            LastCompileStartTime,
            LastExecutionTime,
            LastCompileBatchSqlHandle,
            LastCompileBatchOffsetStart,
            LastCompileBatchOffsetEnd,
            CountCompiles,
            AvgCompileDuration,
            LastCompileDuration,
            AvgBindDuration,
            LastBindDuration,
            AvgBindCpuTime,
            LastBindCpuTime,
            AvgOptimizeDuration,
            LastOptimizeDuration,
            AvgOptimizeCpuTime,
            LastOptimizeCpuTime,
            AvgCompileMemoryKb,
            LastCompileMemoryKb,
            MaxCompileMemoryKb,
            IsClouddbInternalQuery);
    }

    public List<Types.QueryStoreQueryDataType> ToList()
    {
        var list = new List<Types.QueryStoreQueryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
