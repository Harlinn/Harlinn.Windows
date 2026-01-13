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

public class DmDbXtpCheckpointStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_checkpoint_stats]";
    public const string TableName = "dm_db_xtp_checkpoint_stats";
    public const string ShortName = "ddxcs";
    public const string Sql = """
        SELECT
          ddxcs.[last_lsn_processed],
          ddxcs.[end_of_log_lsn],
          ddxcs.[bytes_to_end_of_log],
          ddxcs.[log_consumption_rate],
          ddxcs.[active_scan_time_in_ms],
          ddxcs.[total_wait_time_in_ms],
          ddxcs.[waits_for_io_count],
          ddxcs.[io_wait_time_in_ms],
          ddxcs.[waits_for_new_log_count],
          ddxcs.[new_log_wait_time_in_ms],
          ddxcs.[idle_attempts_count],
          ddxcs.[tx_segments_dispatched_count],
          ddxcs.[segment_bytes_dispatched],
          ddxcs.[bytes_serialized],
          ddxcs.[serializer_user_time_in_ms],
          ddxcs.[serializer_kernel_time_in_ms],
          ddxcs.[xtp_log_bytes_consumed],
          ddxcs.[checkpoints_closed],
          ddxcs.[last_closed_checkpoint_ts],
          ddxcs.[hardened_recovery_lsn],
          ddxcs.[hardened_root_file_guid],
          ddxcs.[hardened_root_file_watermark],
          ddxcs.[hardened_truncation_lsn],
          ddxcs.[log_bytes_since_last_close],
          ddxcs.[time_since_last_close_in_ms],
          ddxcs.[current_checkpoint_id],
          ddxcs.[current_checkpoint_segment_count],
          ddxcs.[recovery_lsn_candidate],
          ddxcs.[outstanding_checkpoint_count],
          ddxcs.[closing_checkpoint_id],
          ddxcs.[recovery_checkpoint_id],
          ddxcs.[recovery_checkpoint_ts],
          ddxcs.[bootstrap_recovery_lsn],
          ddxcs.[bootstrap_root_file_guid],
          ddxcs.[internal_error_code],
          ddxcs.[tail_cache_page_count],
          ddxcs.[tail_cache_max_page_count],
          ddxcs.[tail_cache_min_needed_lsn],
          ddxcs.[merge_outstanding_merges],
          ddxcs.[merge_stats_number_of_merges],
          ddxcs.[merge_stats_log_blocks_merged],
          ddxcs.[merge_stats_bytes_merged],
          ddxcs.[merge_stats_user_time],
          ddxcs.[merge_stats_kernel_time],
          ddxcs.[bytes_of_large_data_serialized]
        FROM
          [sys].[dm_db_xtp_checkpoint_stats] ddxcs
        """;

    public const int LASTLSNPROCESSED_FIELD_ID = 0;
    public const int ENDOFLOGLSN_FIELD_ID = 1;
    public const int BYTESTOENDOFLOG_FIELD_ID = 2;
    public const int LOGCONSUMPTIONRATE_FIELD_ID = 3;
    public const int ACTIVESCANTIMEINMS_FIELD_ID = 4;
    public const int TOTALWAITTIMEINMS_FIELD_ID = 5;
    public const int WAITSFORIOCOUNT_FIELD_ID = 6;
    public const int IOWAITTIMEINMS_FIELD_ID = 7;
    public const int WAITSFORNEWLOGCOUNT_FIELD_ID = 8;
    public const int NEWLOGWAITTIMEINMS_FIELD_ID = 9;
    public const int IDLEATTEMPTSCOUNT_FIELD_ID = 10;
    public const int TXSEGMENTSDISPATCHEDCOUNT_FIELD_ID = 11;
    public const int SEGMENTBYTESDISPATCHED_FIELD_ID = 12;
    public const int BYTESSERIALIZED_FIELD_ID = 13;
    public const int SERIALIZERUSERTIMEINMS_FIELD_ID = 14;
    public const int SERIALIZERKERNELTIMEINMS_FIELD_ID = 15;
    public const int XTPLOGBYTESCONSUMED_FIELD_ID = 16;
    public const int CHECKPOINTSCLOSED_FIELD_ID = 17;
    public const int LASTCLOSEDCHECKPOINTTS_FIELD_ID = 18;
    public const int HARDENEDRECOVERYLSN_FIELD_ID = 19;
    public const int HARDENEDROOTFILEGUID_FIELD_ID = 20;
    public const int HARDENEDROOTFILEWATERMARK_FIELD_ID = 21;
    public const int HARDENEDTRUNCATIONLSN_FIELD_ID = 22;
    public const int LOGBYTESSINCELASTCLOSE_FIELD_ID = 23;
    public const int TIMESINCELASTCLOSEINMS_FIELD_ID = 24;
    public const int CURRENTCHECKPOINTID_FIELD_ID = 25;
    public const int CURRENTCHECKPOINTSEGMENTCOUNT_FIELD_ID = 26;
    public const int RECOVERYLSNCANDIDATE_FIELD_ID = 27;
    public const int OUTSTANDINGCHECKPOINTCOUNT_FIELD_ID = 28;
    public const int CLOSINGCHECKPOINTID_FIELD_ID = 29;
    public const int RECOVERYCHECKPOINTID_FIELD_ID = 30;
    public const int RECOVERYCHECKPOINTTS_FIELD_ID = 31;
    public const int BOOTSTRAPRECOVERYLSN_FIELD_ID = 32;
    public const int BOOTSTRAPROOTFILEGUID_FIELD_ID = 33;
    public const int INTERNALERRORCODE_FIELD_ID = 34;
    public const int TAILCACHEPAGECOUNT_FIELD_ID = 35;
    public const int TAILCACHEMAXPAGECOUNT_FIELD_ID = 36;
    public const int TAILCACHEMINNEEDEDLSN_FIELD_ID = 37;
    public const int MERGEOUTSTANDINGMERGES_FIELD_ID = 38;
    public const int MERGESTATSNUMBEROFMERGES_FIELD_ID = 39;
    public const int MERGESTATSLOGBLOCKSMERGED_FIELD_ID = 40;
    public const int MERGESTATSBYTESMERGED_FIELD_ID = 41;
    public const int MERGESTATSUSERTIME_FIELD_ID = 42;
    public const int MERGESTATSKERNELTIME_FIELD_ID = 43;
    public const int BYTESOFLARGEDATASERIALIZED_FIELD_ID = 44;


    public DmDbXtpCheckpointStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public decimal? LastLsnProcessed
    {
        get
        {
            return base.GetNullableDecimal(LASTLSNPROCESSED_FIELD_ID);
        }
    }

    public decimal? EndOfLogLsn
    {
        get
        {
            return base.GetNullableDecimal(ENDOFLOGLSN_FIELD_ID);
        }
    }

    public long? BytesToEndOfLog
    {
        get
        {
            return base.GetNullableInt64(BYTESTOENDOFLOG_FIELD_ID);
        }
    }

    public long? LogConsumptionRate
    {
        get
        {
            return base.GetNullableInt64(LOGCONSUMPTIONRATE_FIELD_ID);
        }
    }

    public long? ActiveScanTimeInMs
    {
        get
        {
            return base.GetNullableInt64(ACTIVESCANTIMEINMS_FIELD_ID);
        }
    }

    public long? TotalWaitTimeInMs
    {
        get
        {
            return base.GetNullableInt64(TOTALWAITTIMEINMS_FIELD_ID);
        }
    }

    public long? WaitsForIoCount
    {
        get
        {
            return base.GetNullableInt64(WAITSFORIOCOUNT_FIELD_ID);
        }
    }

    public long? IoWaitTimeInMs
    {
        get
        {
            return base.GetNullableInt64(IOWAITTIMEINMS_FIELD_ID);
        }
    }

    public long? WaitsForNewLogCount
    {
        get
        {
            return base.GetNullableInt64(WAITSFORNEWLOGCOUNT_FIELD_ID);
        }
    }

    public long? NewLogWaitTimeInMs
    {
        get
        {
            return base.GetNullableInt64(NEWLOGWAITTIMEINMS_FIELD_ID);
        }
    }

    public long? IdleAttemptsCount
    {
        get
        {
            return base.GetNullableInt64(IDLEATTEMPTSCOUNT_FIELD_ID);
        }
    }

    public long? TxSegmentsDispatchedCount
    {
        get
        {
            return base.GetNullableInt64(TXSEGMENTSDISPATCHEDCOUNT_FIELD_ID);
        }
    }

    public long? SegmentBytesDispatched
    {
        get
        {
            return base.GetNullableInt64(SEGMENTBYTESDISPATCHED_FIELD_ID);
        }
    }

    public long? BytesSerialized
    {
        get
        {
            return base.GetNullableInt64(BYTESSERIALIZED_FIELD_ID);
        }
    }

    public long? SerializerUserTimeInMs
    {
        get
        {
            return base.GetNullableInt64(SERIALIZERUSERTIMEINMS_FIELD_ID);
        }
    }

    public long? SerializerKernelTimeInMs
    {
        get
        {
            return base.GetNullableInt64(SERIALIZERKERNELTIMEINMS_FIELD_ID);
        }
    }

    public long? XtpLogBytesConsumed
    {
        get
        {
            return base.GetNullableInt64(XTPLOGBYTESCONSUMED_FIELD_ID);
        }
    }

    public long? CheckpointsClosed
    {
        get
        {
            return base.GetNullableInt64(CHECKPOINTSCLOSED_FIELD_ID);
        }
    }

    public long? LastClosedCheckpointTs
    {
        get
        {
            return base.GetNullableInt64(LASTCLOSEDCHECKPOINTTS_FIELD_ID);
        }
    }

    public decimal? HardenedRecoveryLsn
    {
        get
        {
            return base.GetNullableDecimal(HARDENEDRECOVERYLSN_FIELD_ID);
        }
    }

    public Guid? HardenedRootFileGuid
    {
        get
        {
            return base.GetNullableGuid(HARDENEDROOTFILEGUID_FIELD_ID);
        }
    }

    public long? HardenedRootFileWatermark
    {
        get
        {
            return base.GetNullableInt64(HARDENEDROOTFILEWATERMARK_FIELD_ID);
        }
    }

    public decimal? HardenedTruncationLsn
    {
        get
        {
            return base.GetNullableDecimal(HARDENEDTRUNCATIONLSN_FIELD_ID);
        }
    }

    public long? LogBytesSinceLastClose
    {
        get
        {
            return base.GetNullableInt64(LOGBYTESSINCELASTCLOSE_FIELD_ID);
        }
    }

    public long? TimeSinceLastCloseInMs
    {
        get
        {
            return base.GetNullableInt64(TIMESINCELASTCLOSEINMS_FIELD_ID);
        }
    }

    public long? CurrentCheckpointId
    {
        get
        {
            return base.GetNullableInt64(CURRENTCHECKPOINTID_FIELD_ID);
        }
    }

    public long? CurrentCheckpointSegmentCount
    {
        get
        {
            return base.GetNullableInt64(CURRENTCHECKPOINTSEGMENTCOUNT_FIELD_ID);
        }
    }

    public decimal? RecoveryLsnCandidate
    {
        get
        {
            return base.GetNullableDecimal(RECOVERYLSNCANDIDATE_FIELD_ID);
        }
    }

    public long? OutstandingCheckpointCount
    {
        get
        {
            return base.GetNullableInt64(OUTSTANDINGCHECKPOINTCOUNT_FIELD_ID);
        }
    }

    public long? ClosingCheckpointId
    {
        get
        {
            return base.GetNullableInt64(CLOSINGCHECKPOINTID_FIELD_ID);
        }
    }

    public long? RecoveryCheckpointId
    {
        get
        {
            return base.GetNullableInt64(RECOVERYCHECKPOINTID_FIELD_ID);
        }
    }

    public long? RecoveryCheckpointTs
    {
        get
        {
            return base.GetNullableInt64(RECOVERYCHECKPOINTTS_FIELD_ID);
        }
    }

    public decimal? BootstrapRecoveryLsn
    {
        get
        {
            return base.GetNullableDecimal(BOOTSTRAPRECOVERYLSN_FIELD_ID);
        }
    }

    public Guid? BootstrapRootFileGuid
    {
        get
        {
            return base.GetNullableGuid(BOOTSTRAPROOTFILEGUID_FIELD_ID);
        }
    }

    public long? InternalErrorCode
    {
        get
        {
            return base.GetNullableInt64(INTERNALERRORCODE_FIELD_ID);
        }
    }

    public long? TailCachePageCount
    {
        get
        {
            return base.GetNullableInt64(TAILCACHEPAGECOUNT_FIELD_ID);
        }
    }

    public long? TailCacheMaxPageCount
    {
        get
        {
            return base.GetNullableInt64(TAILCACHEMAXPAGECOUNT_FIELD_ID);
        }
    }

    public decimal? TailCacheMinNeededLsn
    {
        get
        {
            return base.GetNullableDecimal(TAILCACHEMINNEEDEDLSN_FIELD_ID);
        }
    }

    public long? MergeOutstandingMerges
    {
        get
        {
            return base.GetNullableInt64(MERGEOUTSTANDINGMERGES_FIELD_ID);
        }
    }

    public long? MergeStatsNumberOfMerges
    {
        get
        {
            return base.GetNullableInt64(MERGESTATSNUMBEROFMERGES_FIELD_ID);
        }
    }

    public long? MergeStatsLogBlocksMerged
    {
        get
        {
            return base.GetNullableInt64(MERGESTATSLOGBLOCKSMERGED_FIELD_ID);
        }
    }

    public long? MergeStatsBytesMerged
    {
        get
        {
            return base.GetNullableInt64(MERGESTATSBYTESMERGED_FIELD_ID);
        }
    }

    public long? MergeStatsUserTime
    {
        get
        {
            return base.GetNullableInt64(MERGESTATSUSERTIME_FIELD_ID);
        }
    }

    public long? MergeStatsKernelTime
    {
        get
        {
            return base.GetNullableInt64(MERGESTATSKERNELTIME_FIELD_ID);
        }
    }

    public long? BytesOfLargeDataSerialized
    {
        get
        {
            return base.GetNullableInt64(BYTESOFLARGEDATASERIALIZED_FIELD_ID);
        }
    }


    public Types.DmDbXtpCheckpointStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpCheckpointStatsDataType(LastLsnProcessed,
            EndOfLogLsn,
            BytesToEndOfLog,
            LogConsumptionRate,
            ActiveScanTimeInMs,
            TotalWaitTimeInMs,
            WaitsForIoCount,
            IoWaitTimeInMs,
            WaitsForNewLogCount,
            NewLogWaitTimeInMs,
            IdleAttemptsCount,
            TxSegmentsDispatchedCount,
            SegmentBytesDispatched,
            BytesSerialized,
            SerializerUserTimeInMs,
            SerializerKernelTimeInMs,
            XtpLogBytesConsumed,
            CheckpointsClosed,
            LastClosedCheckpointTs,
            HardenedRecoveryLsn,
            HardenedRootFileGuid,
            HardenedRootFileWatermark,
            HardenedTruncationLsn,
            LogBytesSinceLastClose,
            TimeSinceLastCloseInMs,
            CurrentCheckpointId,
            CurrentCheckpointSegmentCount,
            RecoveryLsnCandidate,
            OutstandingCheckpointCount,
            ClosingCheckpointId,
            RecoveryCheckpointId,
            RecoveryCheckpointTs,
            BootstrapRecoveryLsn,
            BootstrapRootFileGuid,
            InternalErrorCode,
            TailCachePageCount,
            TailCacheMaxPageCount,
            TailCacheMinNeededLsn,
            MergeOutstandingMerges,
            MergeStatsNumberOfMerges,
            MergeStatsLogBlocksMerged,
            MergeStatsBytesMerged,
            MergeStatsUserTime,
            MergeStatsKernelTime,
            BytesOfLargeDataSerialized);
    }

    public List<Types.DmDbXtpCheckpointStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpCheckpointStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
