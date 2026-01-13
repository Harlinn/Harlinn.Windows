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

public class DmCdcLogScanSessionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cdc_log_scan_sessions]";
    public const string TableName = "dm_cdc_log_scan_sessions";
    public const string ShortName = "dclss";
    public const string Sql = """
        SELECT
          dclss.[session_id],
          dclss.[start_time],
          dclss.[end_time],
          dclss.[Duration],
          dclss.[scan_phase],
          dclss.[error_count],
          dclss.[start_lsn],
          dclss.[current_lsn],
          dclss.[end_lsn],
          dclss.[tran_count],
          dclss.[last_commit_lsn],
          dclss.[last_commit_time],
          dclss.[log_record_count],
          dclss.[schema_change_count],
          dclss.[command_count],
          dclss.[first_begin_cdc_lsn],
          dclss.[last_commit_cdc_lsn],
          dclss.[last_commit_cdc_time],
          dclss.[Latency],
          dclss.[empty_scan_count],
          dclss.[failed_sessions_count]
        FROM
          [sys].[dm_cdc_log_scan_sessions] dclss
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int STARTTIME_FIELD_ID = 1;
    public const int ENDTIME_FIELD_ID = 2;
    public const int DURATION_FIELD_ID = 3;
    public const int SCANPHASE_FIELD_ID = 4;
    public const int ERRORCOUNT_FIELD_ID = 5;
    public const int STARTLSN_FIELD_ID = 6;
    public const int CURRENTLSN_FIELD_ID = 7;
    public const int ENDLSN_FIELD_ID = 8;
    public const int TRANCOUNT_FIELD_ID = 9;
    public const int LASTCOMMITLSN_FIELD_ID = 10;
    public const int LASTCOMMITTIME_FIELD_ID = 11;
    public const int LOGRECORDCOUNT_FIELD_ID = 12;
    public const int SCHEMACHANGECOUNT_FIELD_ID = 13;
    public const int COMMANDCOUNT_FIELD_ID = 14;
    public const int FIRSTBEGINCDCLSN_FIELD_ID = 15;
    public const int LASTCOMMITCDCLSN_FIELD_ID = 16;
    public const int LASTCOMMITCDCTIME_FIELD_ID = 17;
    public const int LATENCY_FIELD_ID = 18;
    public const int EMPTYSCANCOUNT_FIELD_ID = 19;
    public const int FAILEDSESSIONSCOUNT_FIELD_ID = 20;


    public DmCdcLogScanSessionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmCdcLogScanSessionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmCdcLogScanSessionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? SessionId
    {
        get
        {
            return base.GetNullableInt32(SESSIONID_FIELD_ID);
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

    public int? Duration
    {
        get
        {
            return base.GetNullableInt32(DURATION_FIELD_ID);
        }
    }

    public string? ScanPhase
    {
        get
        {
            return base.GetNullableString(SCANPHASE_FIELD_ID);
        }
    }

    public int? ErrorCount
    {
        get
        {
            return base.GetNullableInt32(ERRORCOUNT_FIELD_ID);
        }
    }

    public string? StartLsn
    {
        get
        {
            return base.GetNullableString(STARTLSN_FIELD_ID);
        }
    }

    public string? CurrentLsn
    {
        get
        {
            return base.GetNullableString(CURRENTLSN_FIELD_ID);
        }
    }

    public string? EndLsn
    {
        get
        {
            return base.GetNullableString(ENDLSN_FIELD_ID);
        }
    }

    public long? TranCount
    {
        get
        {
            return base.GetNullableInt64(TRANCOUNT_FIELD_ID);
        }
    }

    public string? LastCommitLsn
    {
        get
        {
            return base.GetNullableString(LASTCOMMITLSN_FIELD_ID);
        }
    }

    public DateTime? LastCommitTime
    {
        get
        {
            return base.GetNullableDateTime(LASTCOMMITTIME_FIELD_ID);
        }
    }

    public long? LogRecordCount
    {
        get
        {
            return base.GetNullableInt64(LOGRECORDCOUNT_FIELD_ID);
        }
    }

    public int? SchemaChangeCount
    {
        get
        {
            return base.GetNullableInt32(SCHEMACHANGECOUNT_FIELD_ID);
        }
    }

    public long? CommandCount
    {
        get
        {
            return base.GetNullableInt64(COMMANDCOUNT_FIELD_ID);
        }
    }

    public string? FirstBeginCdcLsn
    {
        get
        {
            return base.GetNullableString(FIRSTBEGINCDCLSN_FIELD_ID);
        }
    }

    public string? LastCommitCdcLsn
    {
        get
        {
            return base.GetNullableString(LASTCOMMITCDCLSN_FIELD_ID);
        }
    }

    public DateTime? LastCommitCdcTime
    {
        get
        {
            return base.GetNullableDateTime(LASTCOMMITCDCTIME_FIELD_ID);
        }
    }

    public int? Latency
    {
        get
        {
            return base.GetNullableInt32(LATENCY_FIELD_ID);
        }
    }

    public int? EmptyScanCount
    {
        get
        {
            return base.GetNullableInt32(EMPTYSCANCOUNT_FIELD_ID);
        }
    }

    public int? FailedSessionsCount
    {
        get
        {
            return base.GetNullableInt32(FAILEDSESSIONSCOUNT_FIELD_ID);
        }
    }


    public Types.DmCdcLogScanSessionsDataType ToDataObject()
    {
        return new Types.DmCdcLogScanSessionsDataType(SessionId,
            StartTime,
            EndTime,
            Duration,
            ScanPhase,
            ErrorCount,
            StartLsn,
            CurrentLsn,
            EndLsn,
            TranCount,
            LastCommitLsn,
            LastCommitTime,
            LogRecordCount,
            SchemaChangeCount,
            CommandCount,
            FirstBeginCdcLsn,
            LastCommitCdcLsn,
            LastCommitCdcTime,
            Latency,
            EmptyScanCount,
            FailedSessionsCount);
    }

    public List<Types.DmCdcLogScanSessionsDataType> ToList()
    {
        var list = new List<Types.DmCdcLogScanSessionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
