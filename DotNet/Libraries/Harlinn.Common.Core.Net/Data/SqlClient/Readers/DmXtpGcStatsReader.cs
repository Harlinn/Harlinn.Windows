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

public class DmXtpGcStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xtp_gc_stats]";
    public const string TableName = "dm_xtp_gc_stats";
    public const string ShortName = "dxgs";
    public const string Sql = """
        SELECT
          dxgs.[rows_examined],
          dxgs.[rows_no_sweep_needed],
          dxgs.[rows_first_in_bucket],
          dxgs.[rows_first_in_bucket_removed],
          dxgs.[rows_marked_for_unlink],
          dxgs.[parallel_assist_count],
          dxgs.[idle_worker_count],
          dxgs.[sweep_scans_started],
          dxgs.[sweep_scan_retries],
          dxgs.[sweep_rows_touched],
          dxgs.[sweep_rows_expiring],
          dxgs.[sweep_rows_expired],
          dxgs.[sweep_rows_expired_removed]
        FROM
          [sys].[dm_xtp_gc_stats] dxgs
        """;

    public const int ROWSEXAMINED_FIELD_ID = 0;
    public const int ROWSNOSWEEPNEEDED_FIELD_ID = 1;
    public const int ROWSFIRSTINBUCKET_FIELD_ID = 2;
    public const int ROWSFIRSTINBUCKETREMOVED_FIELD_ID = 3;
    public const int ROWSMARKEDFORUNLINK_FIELD_ID = 4;
    public const int PARALLELASSISTCOUNT_FIELD_ID = 5;
    public const int IDLEWORKERCOUNT_FIELD_ID = 6;
    public const int SWEEPSCANSSTARTED_FIELD_ID = 7;
    public const int SWEEPSCANRETRIES_FIELD_ID = 8;
    public const int SWEEPROWSTOUCHED_FIELD_ID = 9;
    public const int SWEEPROWSEXPIRING_FIELD_ID = 10;
    public const int SWEEPROWSEXPIRED_FIELD_ID = 11;
    public const int SWEEPROWSEXPIREDREMOVED_FIELD_ID = 12;


    public DmXtpGcStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXtpGcStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXtpGcStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long RowsExamined
    {
        get
        {
            return base.GetInt64(ROWSEXAMINED_FIELD_ID);
        }
    }

    public long RowsNoSweepNeeded
    {
        get
        {
            return base.GetInt64(ROWSNOSWEEPNEEDED_FIELD_ID);
        }
    }

    public long RowsFirstInBucket
    {
        get
        {
            return base.GetInt64(ROWSFIRSTINBUCKET_FIELD_ID);
        }
    }

    public long RowsFirstInBucketRemoved
    {
        get
        {
            return base.GetInt64(ROWSFIRSTINBUCKETREMOVED_FIELD_ID);
        }
    }

    public long RowsMarkedForUnlink
    {
        get
        {
            return base.GetInt64(ROWSMARKEDFORUNLINK_FIELD_ID);
        }
    }

    public long ParallelAssistCount
    {
        get
        {
            return base.GetInt64(PARALLELASSISTCOUNT_FIELD_ID);
        }
    }

    public long IdleWorkerCount
    {
        get
        {
            return base.GetInt64(IDLEWORKERCOUNT_FIELD_ID);
        }
    }

    public long SweepScansStarted
    {
        get
        {
            return base.GetInt64(SWEEPSCANSSTARTED_FIELD_ID);
        }
    }

    public long SweepScanRetries
    {
        get
        {
            return base.GetInt64(SWEEPSCANRETRIES_FIELD_ID);
        }
    }

    public long SweepRowsTouched
    {
        get
        {
            return base.GetInt64(SWEEPROWSTOUCHED_FIELD_ID);
        }
    }

    public long SweepRowsExpiring
    {
        get
        {
            return base.GetInt64(SWEEPROWSEXPIRING_FIELD_ID);
        }
    }

    public long SweepRowsExpired
    {
        get
        {
            return base.GetInt64(SWEEPROWSEXPIRED_FIELD_ID);
        }
    }

    public long SweepRowsExpiredRemoved
    {
        get
        {
            return base.GetInt64(SWEEPROWSEXPIREDREMOVED_FIELD_ID);
        }
    }


    public Types.DmXtpGcStatsDataType ToDataObject()
    {
        return new Types.DmXtpGcStatsDataType(RowsExamined,
            RowsNoSweepNeeded,
            RowsFirstInBucket,
            RowsFirstInBucketRemoved,
            RowsMarkedForUnlink,
            ParallelAssistCount,
            IdleWorkerCount,
            SweepScansStarted,
            SweepScanRetries,
            SweepRowsTouched,
            SweepRowsExpiring,
            SweepRowsExpired,
            SweepRowsExpiredRemoved);
    }

    public List<Types.DmXtpGcStatsDataType> ToList()
    {
        var list = new List<Types.DmXtpGcStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
