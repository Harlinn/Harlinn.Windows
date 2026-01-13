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

public class QueryStorePlanReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_plan]";
    public const string TableName = "query_store_plan";
    public const string ShortName = "qsp";
    public const string Sql = """
        SELECT
          qsp.[plan_id],
          qsp.[query_id],
          qsp.[plan_group_id],
          qsp.[engine_version],
          qsp.[compatibility_level],
          qsp.[query_plan_hash],
          qsp.[query_plan],
          qsp.[is_online_index_plan],
          qsp.[is_trivial_plan],
          qsp.[is_parallel_plan],
          qsp.[is_forced_plan],
          qsp.[is_natively_compiled],
          qsp.[force_failure_count],
          qsp.[last_force_failure_reason],
          qsp.[last_force_failure_reason_desc],
          qsp.[count_compiles],
          qsp.[initial_compile_start_time],
          qsp.[last_compile_start_time],
          qsp.[last_execution_time],
          qsp.[avg_compile_duration],
          qsp.[last_compile_duration],
          qsp.[plan_forcing_type],
          qsp.[plan_forcing_type_desc]
        FROM
          [sys].[query_store_plan] qsp
        """;

    public const int PLANID_FIELD_ID = 0;
    public const int QUERYID_FIELD_ID = 1;
    public const int PLANGROUPID_FIELD_ID = 2;
    public const int ENGINEVERSION_FIELD_ID = 3;
    public const int COMPATIBILITYLEVEL_FIELD_ID = 4;
    public const int QUERYPLANHASH_FIELD_ID = 5;
    public const int QUERYPLAN_FIELD_ID = 6;
    public const int ISONLINEINDEXPLAN_FIELD_ID = 7;
    public const int ISTRIVIALPLAN_FIELD_ID = 8;
    public const int ISPARALLELPLAN_FIELD_ID = 9;
    public const int ISFORCEDPLAN_FIELD_ID = 10;
    public const int ISNATIVELYCOMPILED_FIELD_ID = 11;
    public const int FORCEFAILURECOUNT_FIELD_ID = 12;
    public const int LASTFORCEFAILUREREASON_FIELD_ID = 13;
    public const int LASTFORCEFAILUREREASONDESC_FIELD_ID = 14;
    public const int COUNTCOMPILES_FIELD_ID = 15;
    public const int INITIALCOMPILESTARTTIME_FIELD_ID = 16;
    public const int LASTCOMPILESTARTTIME_FIELD_ID = 17;
    public const int LASTEXECUTIONTIME_FIELD_ID = 18;
    public const int AVGCOMPILEDURATION_FIELD_ID = 19;
    public const int LASTCOMPILEDURATION_FIELD_ID = 20;
    public const int PLANFORCINGTYPE_FIELD_ID = 21;
    public const int PLANFORCINGTYPEDESC_FIELD_ID = 22;


    public QueryStorePlanReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStorePlanReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStorePlanReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long PlanId
    {
        get
        {
            return base.GetInt64(PLANID_FIELD_ID);
        }
    }

    public long QueryId
    {
        get
        {
            return base.GetInt64(QUERYID_FIELD_ID);
        }
    }

    public long? PlanGroupId
    {
        get
        {
            return base.GetNullableInt64(PLANGROUPID_FIELD_ID);
        }
    }

    public string? EngineVersion
    {
        get
        {
            return base.GetNullableString(ENGINEVERSION_FIELD_ID);
        }
    }

    public short CompatibilityLevel
    {
        get
        {
            return base.GetInt16(COMPATIBILITYLEVEL_FIELD_ID);
        }
    }

    public byte[] QueryPlanHash
    {
        get
        {
            return base.GetBinary(QUERYPLANHASH_FIELD_ID);
        }
    }

    public string? QueryPlan
    {
        get
        {
            return base.GetNullableString(QUERYPLAN_FIELD_ID);
        }
    }

    public bool IsOnlineIndexPlan
    {
        get
        {
            return base.GetBoolean(ISONLINEINDEXPLAN_FIELD_ID);
        }
    }

    public bool IsTrivialPlan
    {
        get
        {
            return base.GetBoolean(ISTRIVIALPLAN_FIELD_ID);
        }
    }

    public bool IsParallelPlan
    {
        get
        {
            return base.GetBoolean(ISPARALLELPLAN_FIELD_ID);
        }
    }

    public bool IsForcedPlan
    {
        get
        {
            return base.GetBoolean(ISFORCEDPLAN_FIELD_ID);
        }
    }

    public bool IsNativelyCompiled
    {
        get
        {
            return base.GetBoolean(ISNATIVELYCOMPILED_FIELD_ID);
        }
    }

    public long ForceFailureCount
    {
        get
        {
            return base.GetInt64(FORCEFAILURECOUNT_FIELD_ID);
        }
    }

    public int LastForceFailureReason
    {
        get
        {
            return base.GetInt32(LASTFORCEFAILUREREASON_FIELD_ID);
        }
    }

    public string? LastForceFailureReasonDesc
    {
        get
        {
            return base.GetNullableString(LASTFORCEFAILUREREASONDESC_FIELD_ID);
        }
    }

    public long? CountCompiles
    {
        get
        {
            return base.GetNullableInt64(COUNTCOMPILES_FIELD_ID);
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

    public int PlanForcingType
    {
        get
        {
            return base.GetInt32(PLANFORCINGTYPE_FIELD_ID);
        }
    }

    public string? PlanForcingTypeDesc
    {
        get
        {
            return base.GetNullableString(PLANFORCINGTYPEDESC_FIELD_ID);
        }
    }


    public Types.QueryStorePlanDataType ToDataObject()
    {
        return new Types.QueryStorePlanDataType(PlanId,
            QueryId,
            PlanGroupId,
            EngineVersion,
            CompatibilityLevel,
            QueryPlanHash,
            QueryPlan,
            IsOnlineIndexPlan,
            IsTrivialPlan,
            IsParallelPlan,
            IsForcedPlan,
            IsNativelyCompiled,
            ForceFailureCount,
            LastForceFailureReason,
            LastForceFailureReasonDesc,
            CountCompiles,
            InitialCompileStartTime,
            LastCompileStartTime,
            LastExecutionTime,
            AvgCompileDuration,
            LastCompileDuration,
            PlanForcingType,
            PlanForcingTypeDesc);
    }

    public List<Types.QueryStorePlanDataType> ToList()
    {
        var list = new List<Types.QueryStorePlanDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
