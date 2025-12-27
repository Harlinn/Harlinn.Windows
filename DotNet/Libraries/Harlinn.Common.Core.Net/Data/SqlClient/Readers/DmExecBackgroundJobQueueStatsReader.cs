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

public class DmExecBackgroundJobQueueStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_background_job_queue_stats]";
    public const string TableName = "dm_exec_background_job_queue_stats";
    public const string ShortName = "debjqs";
    public const string Sql = """
        SELECT
          debjqs.[queue_max_len],
          debjqs.[enqueued_count],
          debjqs.[started_count],
          debjqs.[ended_count],
          debjqs.[failed_lock_count],
          debjqs.[failed_other_count],
          debjqs.[failed_giveup_count],
          debjqs.[enqueue_failed_full_count],
          debjqs.[enqueue_failed_duplicate_count],
          debjqs.[elapsed_avg_ms],
          debjqs.[elapsed_max_ms]
        FROM
          [sys].[dm_exec_background_job_queue_stats] debjqs
        """;

    public const int QUEUEMAXLEN_FIELD_ID = 0;
    public const int ENQUEUEDCOUNT_FIELD_ID = 1;
    public const int STARTEDCOUNT_FIELD_ID = 2;
    public const int ENDEDCOUNT_FIELD_ID = 3;
    public const int FAILEDLOCKCOUNT_FIELD_ID = 4;
    public const int FAILEDOTHERCOUNT_FIELD_ID = 5;
    public const int FAILEDGIVEUPCOUNT_FIELD_ID = 6;
    public const int ENQUEUEFAILEDFULLCOUNT_FIELD_ID = 7;
    public const int ENQUEUEFAILEDDUPLICATECOUNT_FIELD_ID = 8;
    public const int ELAPSEDAVGMS_FIELD_ID = 9;
    public const int ELAPSEDMAXMS_FIELD_ID = 10;


    public DmExecBackgroundJobQueueStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecBackgroundJobQueueStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecBackgroundJobQueueStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int QueueMaxLen
    {
        get
        {
            return base.GetInt32(QUEUEMAXLEN_FIELD_ID);
        }
    }

    public int EnqueuedCount
    {
        get
        {
            return base.GetInt32(ENQUEUEDCOUNT_FIELD_ID);
        }
    }

    public int StartedCount
    {
        get
        {
            return base.GetInt32(STARTEDCOUNT_FIELD_ID);
        }
    }

    public int EndedCount
    {
        get
        {
            return base.GetInt32(ENDEDCOUNT_FIELD_ID);
        }
    }

    public int FailedLockCount
    {
        get
        {
            return base.GetInt32(FAILEDLOCKCOUNT_FIELD_ID);
        }
    }

    public int FailedOtherCount
    {
        get
        {
            return base.GetInt32(FAILEDOTHERCOUNT_FIELD_ID);
        }
    }

    public int FailedGiveupCount
    {
        get
        {
            return base.GetInt32(FAILEDGIVEUPCOUNT_FIELD_ID);
        }
    }

    public int EnqueueFailedFullCount
    {
        get
        {
            return base.GetInt32(ENQUEUEFAILEDFULLCOUNT_FIELD_ID);
        }
    }

    public int EnqueueFailedDuplicateCount
    {
        get
        {
            return base.GetInt32(ENQUEUEFAILEDDUPLICATECOUNT_FIELD_ID);
        }
    }

    public int ElapsedAvgMs
    {
        get
        {
            return base.GetInt32(ELAPSEDAVGMS_FIELD_ID);
        }
    }

    public int ElapsedMaxMs
    {
        get
        {
            return base.GetInt32(ELAPSEDMAXMS_FIELD_ID);
        }
    }


    public Types.DmExecBackgroundJobQueueStatsDataType ToDataObject()
    {
        return new Types.DmExecBackgroundJobQueueStatsDataType(QueueMaxLen,
            EnqueuedCount,
            StartedCount,
            EndedCount,
            FailedLockCount,
            FailedOtherCount,
            FailedGiveupCount,
            EnqueueFailedFullCount,
            EnqueueFailedDuplicateCount,
            ElapsedAvgMs,
            ElapsedMaxMs);
    }

    public List<Types.DmExecBackgroundJobQueueStatsDataType> ToList()
    {
        var list = new List<Types.DmExecBackgroundJobQueueStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
