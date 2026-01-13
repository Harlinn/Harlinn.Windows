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

public class DmXtpTransactionStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xtp_transaction_stats]";
    public const string TableName = "dm_xtp_transaction_stats";
    public const string ShortName = "dxts";
    public const string Sql = """
        SELECT
          dxts.[total_count],
          dxts.[read_only_count],
          dxts.[total_aborts],
          dxts.[system_aborts],
          dxts.[validation_failures],
          dxts.[dependencies_taken],
          dxts.[dependencies_failed],
          dxts.[savepoint_create],
          dxts.[savepoint_rollbacks],
          dxts.[savepoint_refreshes],
          dxts.[log_bytes_written],
          dxts.[log_IO_count],
          dxts.[phantom_scans_started],
          dxts.[phantom_scans_retries],
          dxts.[phantom_rows_touched],
          dxts.[phantom_rows_expiring],
          dxts.[phantom_rows_expired],
          dxts.[phantom_rows_expired_removed],
          dxts.[scans_started],
          dxts.[scans_retried],
          dxts.[rows_returned],
          dxts.[rows_touched],
          dxts.[rows_expiring],
          dxts.[rows_expired],
          dxts.[rows_expired_removed],
          dxts.[row_insert_attempts],
          dxts.[row_update_attempts],
          dxts.[row_delete_attempts],
          dxts.[write_conflicts],
          dxts.[unique_constraint_violations],
          dxts.[drop_table_memory_attempts],
          dxts.[drop_table_memory_failures]
        FROM
          [sys].[dm_xtp_transaction_stats] dxts
        """;

    public const int TOTALCOUNT_FIELD_ID = 0;
    public const int READONLYCOUNT_FIELD_ID = 1;
    public const int TOTALABORTS_FIELD_ID = 2;
    public const int SYSTEMABORTS_FIELD_ID = 3;
    public const int VALIDATIONFAILURES_FIELD_ID = 4;
    public const int DEPENDENCIESTAKEN_FIELD_ID = 5;
    public const int DEPENDENCIESFAILED_FIELD_ID = 6;
    public const int SAVEPOINTCREATE_FIELD_ID = 7;
    public const int SAVEPOINTROLLBACKS_FIELD_ID = 8;
    public const int SAVEPOINTREFRESHES_FIELD_ID = 9;
    public const int LOGBYTESWRITTEN_FIELD_ID = 10;
    public const int LOGIOCOUNT_FIELD_ID = 11;
    public const int PHANTOMSCANSSTARTED_FIELD_ID = 12;
    public const int PHANTOMSCANSRETRIES_FIELD_ID = 13;
    public const int PHANTOMROWSTOUCHED_FIELD_ID = 14;
    public const int PHANTOMROWSEXPIRING_FIELD_ID = 15;
    public const int PHANTOMROWSEXPIRED_FIELD_ID = 16;
    public const int PHANTOMROWSEXPIREDREMOVED_FIELD_ID = 17;
    public const int SCANSSTARTED_FIELD_ID = 18;
    public const int SCANSRETRIED_FIELD_ID = 19;
    public const int ROWSRETURNED_FIELD_ID = 20;
    public const int ROWSTOUCHED_FIELD_ID = 21;
    public const int ROWSEXPIRING_FIELD_ID = 22;
    public const int ROWSEXPIRED_FIELD_ID = 23;
    public const int ROWSEXPIREDREMOVED_FIELD_ID = 24;
    public const int ROWINSERTATTEMPTS_FIELD_ID = 25;
    public const int ROWUPDATEATTEMPTS_FIELD_ID = 26;
    public const int ROWDELETEATTEMPTS_FIELD_ID = 27;
    public const int WRITECONFLICTS_FIELD_ID = 28;
    public const int UNIQUECONSTRAINTVIOLATIONS_FIELD_ID = 29;
    public const int DROPTABLEMEMORYATTEMPTS_FIELD_ID = 30;
    public const int DROPTABLEMEMORYFAILURES_FIELD_ID = 31;


    public DmXtpTransactionStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXtpTransactionStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXtpTransactionStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long TotalCount
    {
        get
        {
            return base.GetInt64(TOTALCOUNT_FIELD_ID);
        }
    }

    public long ReadOnlyCount
    {
        get
        {
            return base.GetInt64(READONLYCOUNT_FIELD_ID);
        }
    }

    public long TotalAborts
    {
        get
        {
            return base.GetInt64(TOTALABORTS_FIELD_ID);
        }
    }

    public long SystemAborts
    {
        get
        {
            return base.GetInt64(SYSTEMABORTS_FIELD_ID);
        }
    }

    public long ValidationFailures
    {
        get
        {
            return base.GetInt64(VALIDATIONFAILURES_FIELD_ID);
        }
    }

    public long DependenciesTaken
    {
        get
        {
            return base.GetInt64(DEPENDENCIESTAKEN_FIELD_ID);
        }
    }

    public long DependenciesFailed
    {
        get
        {
            return base.GetInt64(DEPENDENCIESFAILED_FIELD_ID);
        }
    }

    public long SavepointCreate
    {
        get
        {
            return base.GetInt64(SAVEPOINTCREATE_FIELD_ID);
        }
    }

    public long SavepointRollbacks
    {
        get
        {
            return base.GetInt64(SAVEPOINTROLLBACKS_FIELD_ID);
        }
    }

    public long SavepointRefreshes
    {
        get
        {
            return base.GetInt64(SAVEPOINTREFRESHES_FIELD_ID);
        }
    }

    public long LogBytesWritten
    {
        get
        {
            return base.GetInt64(LOGBYTESWRITTEN_FIELD_ID);
        }
    }

    public long LogIoCount
    {
        get
        {
            return base.GetInt64(LOGIOCOUNT_FIELD_ID);
        }
    }

    public long PhantomScansStarted
    {
        get
        {
            return base.GetInt64(PHANTOMSCANSSTARTED_FIELD_ID);
        }
    }

    public long PhantomScansRetries
    {
        get
        {
            return base.GetInt64(PHANTOMSCANSRETRIES_FIELD_ID);
        }
    }

    public long PhantomRowsTouched
    {
        get
        {
            return base.GetInt64(PHANTOMROWSTOUCHED_FIELD_ID);
        }
    }

    public long PhantomRowsExpiring
    {
        get
        {
            return base.GetInt64(PHANTOMROWSEXPIRING_FIELD_ID);
        }
    }

    public long PhantomRowsExpired
    {
        get
        {
            return base.GetInt64(PHANTOMROWSEXPIRED_FIELD_ID);
        }
    }

    public long PhantomRowsExpiredRemoved
    {
        get
        {
            return base.GetInt64(PHANTOMROWSEXPIREDREMOVED_FIELD_ID);
        }
    }

    public long ScansStarted
    {
        get
        {
            return base.GetInt64(SCANSSTARTED_FIELD_ID);
        }
    }

    public long ScansRetried
    {
        get
        {
            return base.GetInt64(SCANSRETRIED_FIELD_ID);
        }
    }

    public long RowsReturned
    {
        get
        {
            return base.GetInt64(ROWSRETURNED_FIELD_ID);
        }
    }

    public long RowsTouched
    {
        get
        {
            return base.GetInt64(ROWSTOUCHED_FIELD_ID);
        }
    }

    public long RowsExpiring
    {
        get
        {
            return base.GetInt64(ROWSEXPIRING_FIELD_ID);
        }
    }

    public long RowsExpired
    {
        get
        {
            return base.GetInt64(ROWSEXPIRED_FIELD_ID);
        }
    }

    public long RowsExpiredRemoved
    {
        get
        {
            return base.GetInt64(ROWSEXPIREDREMOVED_FIELD_ID);
        }
    }

    public long RowInsertAttempts
    {
        get
        {
            return base.GetInt64(ROWINSERTATTEMPTS_FIELD_ID);
        }
    }

    public long RowUpdateAttempts
    {
        get
        {
            return base.GetInt64(ROWUPDATEATTEMPTS_FIELD_ID);
        }
    }

    public long RowDeleteAttempts
    {
        get
        {
            return base.GetInt64(ROWDELETEATTEMPTS_FIELD_ID);
        }
    }

    public long WriteConflicts
    {
        get
        {
            return base.GetInt64(WRITECONFLICTS_FIELD_ID);
        }
    }

    public long UniqueConstraintViolations
    {
        get
        {
            return base.GetInt64(UNIQUECONSTRAINTVIOLATIONS_FIELD_ID);
        }
    }

    public long DropTableMemoryAttempts
    {
        get
        {
            return base.GetInt64(DROPTABLEMEMORYATTEMPTS_FIELD_ID);
        }
    }

    public long DropTableMemoryFailures
    {
        get
        {
            return base.GetInt64(DROPTABLEMEMORYFAILURES_FIELD_ID);
        }
    }


    public Types.DmXtpTransactionStatsDataType ToDataObject()
    {
        return new Types.DmXtpTransactionStatsDataType(TotalCount,
            ReadOnlyCount,
            TotalAborts,
            SystemAborts,
            ValidationFailures,
            DependenciesTaken,
            DependenciesFailed,
            SavepointCreate,
            SavepointRollbacks,
            SavepointRefreshes,
            LogBytesWritten,
            LogIoCount,
            PhantomScansStarted,
            PhantomScansRetries,
            PhantomRowsTouched,
            PhantomRowsExpiring,
            PhantomRowsExpired,
            PhantomRowsExpiredRemoved,
            ScansStarted,
            ScansRetried,
            RowsReturned,
            RowsTouched,
            RowsExpiring,
            RowsExpired,
            RowsExpiredRemoved,
            RowInsertAttempts,
            RowUpdateAttempts,
            RowDeleteAttempts,
            WriteConflicts,
            UniqueConstraintViolations,
            DropTableMemoryAttempts,
            DropTableMemoryFailures);
    }

    public List<Types.DmXtpTransactionStatsDataType> ToList()
    {
        var list = new List<Types.DmXtpTransactionStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
