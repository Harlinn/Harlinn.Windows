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

public class DmTranPersistentVersionStoreStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_persistent_version_store_stats]";
    public const string TableName = "dm_tran_persistent_version_store_stats";
    public const string ShortName = "dtpvss";
    public const string Sql = """
        SELECT
          dtpvss.[database_id],
          dtpvss.[pvs_filegroup_id],
          dtpvss.[persistent_version_store_size_kb],
          dtpvss.[online_index_version_store_size_kb],
          dtpvss.[current_aborted_transaction_count],
          dtpvss.[oldest_active_transaction_id],
          dtpvss.[oldest_aborted_transaction_id],
          dtpvss.[min_transaction_timestamp],
          dtpvss.[online_index_min_transaction_timestamp],
          dtpvss.[secondary_low_water_mark],
          dtpvss.[offrow_version_cleaner_start_time],
          dtpvss.[offrow_version_cleaner_end_time],
          dtpvss.[aborted_version_cleaner_start_time],
          dtpvss.[aborted_version_cleaner_end_time],
          dtpvss.[pvs_off_row_page_skipped_low_water_mark],
          dtpvss.[pvs_off_row_page_skipped_transaction_not_cleaned],
          dtpvss.[pvs_off_row_page_skipped_oldest_active_xdesid],
          dtpvss.[pvs_off_row_page_skipped_min_useful_xts],
          dtpvss.[pvs_off_row_page_skipped_oldest_snapshot]
        FROM
          [sys].[dm_tran_persistent_version_store_stats] dtpvss
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int PVSFILEGROUPID_FIELD_ID = 1;
    public const int PERSISTENTVERSIONSTORESIZEKB_FIELD_ID = 2;
    public const int ONLINEINDEXVERSIONSTORESIZEKB_FIELD_ID = 3;
    public const int CURRENTABORTEDTRANSACTIONCOUNT_FIELD_ID = 4;
    public const int OLDESTACTIVETRANSACTIONID_FIELD_ID = 5;
    public const int OLDESTABORTEDTRANSACTIONID_FIELD_ID = 6;
    public const int MINTRANSACTIONTIMESTAMP_FIELD_ID = 7;
    public const int ONLINEINDEXMINTRANSACTIONTIMESTAMP_FIELD_ID = 8;
    public const int SECONDARYLOWWATERMARK_FIELD_ID = 9;
    public const int OFFROWVERSIONCLEANERSTARTTIME_FIELD_ID = 10;
    public const int OFFROWVERSIONCLEANERENDTIME_FIELD_ID = 11;
    public const int ABORTEDVERSIONCLEANERSTARTTIME_FIELD_ID = 12;
    public const int ABORTEDVERSIONCLEANERENDTIME_FIELD_ID = 13;
    public const int PVSOFFROWPAGESKIPPEDLOWWATERMARK_FIELD_ID = 14;
    public const int PVSOFFROWPAGESKIPPEDTRANSACTIONNOTCLEANED_FIELD_ID = 15;
    public const int PVSOFFROWPAGESKIPPEDOLDESTACTIVEXDESID_FIELD_ID = 16;
    public const int PVSOFFROWPAGESKIPPEDMINUSEFULXTS_FIELD_ID = 17;
    public const int PVSOFFROWPAGESKIPPEDOLDESTSNAPSHOT_FIELD_ID = 18;


    public DmTranPersistentVersionStoreStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranPersistentVersionStoreStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranPersistentVersionStoreStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short PvsFilegroupId
    {
        get
        {
            return base.GetInt16(PVSFILEGROUPID_FIELD_ID);
        }
    }

    public long PersistentVersionStoreSizeKb
    {
        get
        {
            return base.GetInt64(PERSISTENTVERSIONSTORESIZEKB_FIELD_ID);
        }
    }

    public long OnlineIndexVersionStoreSizeKb
    {
        get
        {
            return base.GetInt64(ONLINEINDEXVERSIONSTORESIZEKB_FIELD_ID);
        }
    }

    public long CurrentAbortedTransactionCount
    {
        get
        {
            return base.GetInt64(CURRENTABORTEDTRANSACTIONCOUNT_FIELD_ID);
        }
    }

    public long OldestActiveTransactionId
    {
        get
        {
            return base.GetInt64(OLDESTACTIVETRANSACTIONID_FIELD_ID);
        }
    }

    public long OldestAbortedTransactionId
    {
        get
        {
            return base.GetInt64(OLDESTABORTEDTRANSACTIONID_FIELD_ID);
        }
    }

    public long MinTransactionTimestamp
    {
        get
        {
            return base.GetInt64(MINTRANSACTIONTIMESTAMP_FIELD_ID);
        }
    }

    public long OnlineIndexMinTransactionTimestamp
    {
        get
        {
            return base.GetInt64(ONLINEINDEXMINTRANSACTIONTIMESTAMP_FIELD_ID);
        }
    }

    public long SecondaryLowWaterMark
    {
        get
        {
            return base.GetInt64(SECONDARYLOWWATERMARK_FIELD_ID);
        }
    }

    public DateTime? OffrowVersionCleanerStartTime
    {
        get
        {
            return base.GetNullableDateTime(OFFROWVERSIONCLEANERSTARTTIME_FIELD_ID);
        }
    }

    public DateTime? OffrowVersionCleanerEndTime
    {
        get
        {
            return base.GetNullableDateTime(OFFROWVERSIONCLEANERENDTIME_FIELD_ID);
        }
    }

    public DateTime? AbortedVersionCleanerStartTime
    {
        get
        {
            return base.GetNullableDateTime(ABORTEDVERSIONCLEANERSTARTTIME_FIELD_ID);
        }
    }

    public DateTime? AbortedVersionCleanerEndTime
    {
        get
        {
            return base.GetNullableDateTime(ABORTEDVERSIONCLEANERENDTIME_FIELD_ID);
        }
    }

    public long PvsOffRowPageSkippedLowWaterMark
    {
        get
        {
            return base.GetInt64(PVSOFFROWPAGESKIPPEDLOWWATERMARK_FIELD_ID);
        }
    }

    public long PvsOffRowPageSkippedTransactionNotCleaned
    {
        get
        {
            return base.GetInt64(PVSOFFROWPAGESKIPPEDTRANSACTIONNOTCLEANED_FIELD_ID);
        }
    }

    public long PvsOffRowPageSkippedOldestActiveXdesid
    {
        get
        {
            return base.GetInt64(PVSOFFROWPAGESKIPPEDOLDESTACTIVEXDESID_FIELD_ID);
        }
    }

    public long PvsOffRowPageSkippedMinUsefulXts
    {
        get
        {
            return base.GetInt64(PVSOFFROWPAGESKIPPEDMINUSEFULXTS_FIELD_ID);
        }
    }

    public long PvsOffRowPageSkippedOldestSnapshot
    {
        get
        {
            return base.GetInt64(PVSOFFROWPAGESKIPPEDOLDESTSNAPSHOT_FIELD_ID);
        }
    }


    public Types.DmTranPersistentVersionStoreStatsDataType ToDataObject()
    {
        return new Types.DmTranPersistentVersionStoreStatsDataType(DatabaseId,
            PvsFilegroupId,
            PersistentVersionStoreSizeKb,
            OnlineIndexVersionStoreSizeKb,
            CurrentAbortedTransactionCount,
            OldestActiveTransactionId,
            OldestAbortedTransactionId,
            MinTransactionTimestamp,
            OnlineIndexMinTransactionTimestamp,
            SecondaryLowWaterMark,
            OffrowVersionCleanerStartTime,
            OffrowVersionCleanerEndTime,
            AbortedVersionCleanerStartTime,
            AbortedVersionCleanerEndTime,
            PvsOffRowPageSkippedLowWaterMark,
            PvsOffRowPageSkippedTransactionNotCleaned,
            PvsOffRowPageSkippedOldestActiveXdesid,
            PvsOffRowPageSkippedMinUsefulXts,
            PvsOffRowPageSkippedOldestSnapshot);
    }

    public List<Types.DmTranPersistentVersionStoreStatsDataType> ToList()
    {
        var list = new List<Types.DmTranPersistentVersionStoreStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
