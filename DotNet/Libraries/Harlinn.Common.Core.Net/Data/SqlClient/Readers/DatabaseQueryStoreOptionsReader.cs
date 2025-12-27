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

public class DatabaseQueryStoreOptionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_query_store_options]";
    public const string TableName = "database_query_store_options";
    public const string ShortName = "dqso";
    public const string Sql = """
        SELECT
          dqso.[desired_state],
          dqso.[desired_state_desc],
          dqso.[actual_state],
          dqso.[actual_state_desc],
          dqso.[readonly_reason],
          dqso.[current_storage_size_mb],
          dqso.[flush_interval_seconds],
          dqso.[interval_length_minutes],
          dqso.[max_storage_size_mb],
          dqso.[stale_query_threshold_days],
          dqso.[max_plans_per_query],
          dqso.[query_capture_mode],
          dqso.[query_capture_mode_desc],
          dqso.[capture_policy_execution_count],
          dqso.[capture_policy_total_compile_cpu_time_ms],
          dqso.[capture_policy_total_execution_cpu_time_ms],
          dqso.[capture_policy_stale_threshold_hours],
          dqso.[size_based_cleanup_mode],
          dqso.[size_based_cleanup_mode_desc],
          dqso.[wait_stats_capture_mode],
          dqso.[wait_stats_capture_mode_desc],
          dqso.[actual_state_additional_info]
        FROM
          [sys].[database_query_store_options] dqso
        """;

    public const int DESIREDSTATE_FIELD_ID = 0;
    public const int DESIREDSTATEDESC_FIELD_ID = 1;
    public const int ACTUALSTATE_FIELD_ID = 2;
    public const int ACTUALSTATEDESC_FIELD_ID = 3;
    public const int READONLYREASON_FIELD_ID = 4;
    public const int CURRENTSTORAGESIZEMB_FIELD_ID = 5;
    public const int FLUSHINTERVALSECONDS_FIELD_ID = 6;
    public const int INTERVALLENGTHMINUTES_FIELD_ID = 7;
    public const int MAXSTORAGESIZEMB_FIELD_ID = 8;
    public const int STALEQUERYTHRESHOLDDAYS_FIELD_ID = 9;
    public const int MAXPLANSPERQUERY_FIELD_ID = 10;
    public const int QUERYCAPTUREMODE_FIELD_ID = 11;
    public const int QUERYCAPTUREMODEDESC_FIELD_ID = 12;
    public const int CAPTUREPOLICYEXECUTIONCOUNT_FIELD_ID = 13;
    public const int CAPTUREPOLICYTOTALCOMPILECPUTIMEMS_FIELD_ID = 14;
    public const int CAPTUREPOLICYTOTALEXECUTIONCPUTIMEMS_FIELD_ID = 15;
    public const int CAPTUREPOLICYSTALETHRESHOLDHOURS_FIELD_ID = 16;
    public const int SIZEBASEDCLEANUPMODE_FIELD_ID = 17;
    public const int SIZEBASEDCLEANUPMODEDESC_FIELD_ID = 18;
    public const int WAITSTATSCAPTUREMODE_FIELD_ID = 19;
    public const int WAITSTATSCAPTUREMODEDESC_FIELD_ID = 20;
    public const int ACTUALSTATEADDITIONALINFO_FIELD_ID = 21;


    public DatabaseQueryStoreOptionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseQueryStoreOptionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseQueryStoreOptionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short DesiredState
    {
        get
        {
            return base.GetInt16(DESIREDSTATE_FIELD_ID);
        }
    }

    public string? DesiredStateDesc
    {
        get
        {
            return base.GetNullableString(DESIREDSTATEDESC_FIELD_ID);
        }
    }

    public short ActualState
    {
        get
        {
            return base.GetInt16(ACTUALSTATE_FIELD_ID);
        }
    }

    public string? ActualStateDesc
    {
        get
        {
            return base.GetNullableString(ACTUALSTATEDESC_FIELD_ID);
        }
    }

    public int? ReadonlyReason
    {
        get
        {
            return base.GetNullableInt32(READONLYREASON_FIELD_ID);
        }
    }

    public long? CurrentStorageSizeMb
    {
        get
        {
            return base.GetNullableInt64(CURRENTSTORAGESIZEMB_FIELD_ID);
        }
    }

    public long? FlushIntervalSeconds
    {
        get
        {
            return base.GetNullableInt64(FLUSHINTERVALSECONDS_FIELD_ID);
        }
    }

    public long? IntervalLengthMinutes
    {
        get
        {
            return base.GetNullableInt64(INTERVALLENGTHMINUTES_FIELD_ID);
        }
    }

    public long? MaxStorageSizeMb
    {
        get
        {
            return base.GetNullableInt64(MAXSTORAGESIZEMB_FIELD_ID);
        }
    }

    public long? StaleQueryThresholdDays
    {
        get
        {
            return base.GetNullableInt64(STALEQUERYTHRESHOLDDAYS_FIELD_ID);
        }
    }

    public long? MaxPlansPerQuery
    {
        get
        {
            return base.GetNullableInt64(MAXPLANSPERQUERY_FIELD_ID);
        }
    }

    public short QueryCaptureMode
    {
        get
        {
            return base.GetInt16(QUERYCAPTUREMODE_FIELD_ID);
        }
    }

    public string? QueryCaptureModeDesc
    {
        get
        {
            return base.GetNullableString(QUERYCAPTUREMODEDESC_FIELD_ID);
        }
    }

    public int? CapturePolicyExecutionCount
    {
        get
        {
            return base.GetNullableInt32(CAPTUREPOLICYEXECUTIONCOUNT_FIELD_ID);
        }
    }

    public long? CapturePolicyTotalCompileCpuTimeMs
    {
        get
        {
            return base.GetNullableInt64(CAPTUREPOLICYTOTALCOMPILECPUTIMEMS_FIELD_ID);
        }
    }

    public long? CapturePolicyTotalExecutionCpuTimeMs
    {
        get
        {
            return base.GetNullableInt64(CAPTUREPOLICYTOTALEXECUTIONCPUTIMEMS_FIELD_ID);
        }
    }

    public int? CapturePolicyStaleThresholdHours
    {
        get
        {
            return base.GetNullableInt32(CAPTUREPOLICYSTALETHRESHOLDHOURS_FIELD_ID);
        }
    }

    public short SizeBasedCleanupMode
    {
        get
        {
            return base.GetInt16(SIZEBASEDCLEANUPMODE_FIELD_ID);
        }
    }

    public string? SizeBasedCleanupModeDesc
    {
        get
        {
            return base.GetNullableString(SIZEBASEDCLEANUPMODEDESC_FIELD_ID);
        }
    }

    public short WaitStatsCaptureMode
    {
        get
        {
            return base.GetInt16(WAITSTATSCAPTUREMODE_FIELD_ID);
        }
    }

    public string? WaitStatsCaptureModeDesc
    {
        get
        {
            return base.GetNullableString(WAITSTATSCAPTUREMODEDESC_FIELD_ID);
        }
    }

    public string? ActualStateAdditionalInfo
    {
        get
        {
            return base.GetNullableString(ACTUALSTATEADDITIONALINFO_FIELD_ID);
        }
    }


    public Types.DatabaseQueryStoreOptionsDataType ToDataObject()
    {
        return new Types.DatabaseQueryStoreOptionsDataType(DesiredState,
            DesiredStateDesc,
            ActualState,
            ActualStateDesc,
            ReadonlyReason,
            CurrentStorageSizeMb,
            FlushIntervalSeconds,
            IntervalLengthMinutes,
            MaxStorageSizeMb,
            StaleQueryThresholdDays,
            MaxPlansPerQuery,
            QueryCaptureMode,
            QueryCaptureModeDesc,
            CapturePolicyExecutionCount,
            CapturePolicyTotalCompileCpuTimeMs,
            CapturePolicyTotalExecutionCpuTimeMs,
            CapturePolicyStaleThresholdHours,
            SizeBasedCleanupMode,
            SizeBasedCleanupModeDesc,
            WaitStatsCaptureMode,
            WaitStatsCaptureModeDesc,
            ActualStateAdditionalInfo);
    }

    public List<Types.DatabaseQueryStoreOptionsDataType> ToList()
    {
        var list = new List<Types.DatabaseQueryStoreOptionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
