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

public class DmTranDatabaseTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_database_transactions]";
    public const string TableName = "dm_tran_database_transactions";
    public const string ShortName = "dtdt";
    public const string Sql = """
        SELECT
          dtdt.[transaction_id],
          dtdt.[database_id],
          dtdt.[database_transaction_begin_time],
          dtdt.[database_transaction_type],
          dtdt.[database_transaction_state],
          dtdt.[database_transaction_status],
          dtdt.[database_transaction_status2],
          dtdt.[database_transaction_log_record_count],
          dtdt.[database_transaction_replicate_record_count],
          dtdt.[database_transaction_log_bytes_used],
          dtdt.[database_transaction_log_bytes_reserved],
          dtdt.[database_transaction_log_bytes_used_system],
          dtdt.[database_transaction_log_bytes_reserved_system],
          dtdt.[database_transaction_begin_lsn],
          dtdt.[database_transaction_last_lsn],
          dtdt.[database_transaction_most_recent_savepoint_lsn],
          dtdt.[database_transaction_commit_lsn],
          dtdt.[database_transaction_last_rollback_lsn],
          dtdt.[database_transaction_next_undo_lsn]
        FROM
          [sys].[dm_tran_database_transactions] dtdt
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int DATABASETRANSACTIONBEGINTIME_FIELD_ID = 2;
    public const int DATABASETRANSACTIONTYPE_FIELD_ID = 3;
    public const int DATABASETRANSACTIONSTATE_FIELD_ID = 4;
    public const int DATABASETRANSACTIONSTATUS_FIELD_ID = 5;
    public const int DATABASETRANSACTIONSTATUS2_FIELD_ID = 6;
    public const int DATABASETRANSACTIONLOGRECORDCOUNT_FIELD_ID = 7;
    public const int DATABASETRANSACTIONREPLICATERECORDCOUNT_FIELD_ID = 8;
    public const int DATABASETRANSACTIONLOGBYTESUSED_FIELD_ID = 9;
    public const int DATABASETRANSACTIONLOGBYTESRESERVED_FIELD_ID = 10;
    public const int DATABASETRANSACTIONLOGBYTESUSEDSYSTEM_FIELD_ID = 11;
    public const int DATABASETRANSACTIONLOGBYTESRESERVEDSYSTEM_FIELD_ID = 12;
    public const int DATABASETRANSACTIONBEGINLSN_FIELD_ID = 13;
    public const int DATABASETRANSACTIONLASTLSN_FIELD_ID = 14;
    public const int DATABASETRANSACTIONMOSTRECENTSAVEPOINTLSN_FIELD_ID = 15;
    public const int DATABASETRANSACTIONCOMMITLSN_FIELD_ID = 16;
    public const int DATABASETRANSACTIONLASTROLLBACKLSN_FIELD_ID = 17;
    public const int DATABASETRANSACTIONNEXTUNDOLSN_FIELD_ID = 18;


    public DmTranDatabaseTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranDatabaseTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranDatabaseTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long TransactionId
    {
        get
        {
            return base.GetInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public DateTime? DatabaseTransactionBeginTime
    {
        get
        {
            return base.GetNullableDateTime(DATABASETRANSACTIONBEGINTIME_FIELD_ID);
        }
    }

    public int DatabaseTransactionType
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONTYPE_FIELD_ID);
        }
    }

    public int DatabaseTransactionState
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONSTATE_FIELD_ID);
        }
    }

    public int DatabaseTransactionStatus
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONSTATUS_FIELD_ID);
        }
    }

    public int DatabaseTransactionStatus2
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONSTATUS2_FIELD_ID);
        }
    }

    public long DatabaseTransactionLogRecordCount
    {
        get
        {
            return base.GetInt64(DATABASETRANSACTIONLOGRECORDCOUNT_FIELD_ID);
        }
    }

    public int DatabaseTransactionReplicateRecordCount
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONREPLICATERECORDCOUNT_FIELD_ID);
        }
    }

    public long DatabaseTransactionLogBytesUsed
    {
        get
        {
            return base.GetInt64(DATABASETRANSACTIONLOGBYTESUSED_FIELD_ID);
        }
    }

    public long DatabaseTransactionLogBytesReserved
    {
        get
        {
            return base.GetInt64(DATABASETRANSACTIONLOGBYTESRESERVED_FIELD_ID);
        }
    }

    public int DatabaseTransactionLogBytesUsedSystem
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONLOGBYTESUSEDSYSTEM_FIELD_ID);
        }
    }

    public int DatabaseTransactionLogBytesReservedSystem
    {
        get
        {
            return base.GetInt32(DATABASETRANSACTIONLOGBYTESRESERVEDSYSTEM_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionBeginLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONBEGINLSN_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionLastLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONLASTLSN_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionMostRecentSavepointLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONMOSTRECENTSAVEPOINTLSN_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionCommitLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONCOMMITLSN_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionLastRollbackLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONLASTROLLBACKLSN_FIELD_ID);
        }
    }

    public decimal? DatabaseTransactionNextUndoLsn
    {
        get
        {
            return base.GetNullableDecimal(DATABASETRANSACTIONNEXTUNDOLSN_FIELD_ID);
        }
    }


    public Types.DmTranDatabaseTransactionsDataType ToDataObject()
    {
        return new Types.DmTranDatabaseTransactionsDataType(TransactionId,
            DatabaseId,
            DatabaseTransactionBeginTime,
            DatabaseTransactionType,
            DatabaseTransactionState,
            DatabaseTransactionStatus,
            DatabaseTransactionStatus2,
            DatabaseTransactionLogRecordCount,
            DatabaseTransactionReplicateRecordCount,
            DatabaseTransactionLogBytesUsed,
            DatabaseTransactionLogBytesReserved,
            DatabaseTransactionLogBytesUsedSystem,
            DatabaseTransactionLogBytesReservedSystem,
            DatabaseTransactionBeginLsn,
            DatabaseTransactionLastLsn,
            DatabaseTransactionMostRecentSavepointLsn,
            DatabaseTransactionCommitLsn,
            DatabaseTransactionLastRollbackLsn,
            DatabaseTransactionNextUndoLsn);
    }

    public List<Types.DmTranDatabaseTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranDatabaseTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
