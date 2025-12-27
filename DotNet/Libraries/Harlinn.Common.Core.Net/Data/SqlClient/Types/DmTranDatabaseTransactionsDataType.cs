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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmTranDatabaseTransactionsDataType
{
    readonly long _transactionId = 0;
    readonly int _databaseId = 0;
    readonly DateTime? _databaseTransactionBeginTime;
    readonly int _databaseTransactionType = 0;
    readonly int _databaseTransactionState = 0;
    readonly int _databaseTransactionStatus = 0;
    readonly int _databaseTransactionStatus2 = 0;
    readonly long _databaseTransactionLogRecordCount = 0;
    readonly int _databaseTransactionReplicateRecordCount = 0;
    readonly long _databaseTransactionLogBytesUsed = 0;
    readonly long _databaseTransactionLogBytesReserved = 0;
    readonly int _databaseTransactionLogBytesUsedSystem = 0;
    readonly int _databaseTransactionLogBytesReservedSystem = 0;
    readonly object? _databaseTransactionBeginLsn;
    readonly object? _databaseTransactionLastLsn;
    readonly object? _databaseTransactionMostRecentSavepointLsn;
    readonly object? _databaseTransactionCommitLsn;
    readonly object? _databaseTransactionLastRollbackLsn;
    readonly object? _databaseTransactionNextUndoLsn;

    public DmTranDatabaseTransactionsDataType( )
    {
    }

    public DmTranDatabaseTransactionsDataType(long transactionId,
        int databaseId,
        DateTime? databaseTransactionBeginTime,
        int databaseTransactionType,
        int databaseTransactionState,
        int databaseTransactionStatus,
        int databaseTransactionStatus2,
        long databaseTransactionLogRecordCount,
        int databaseTransactionReplicateRecordCount,
        long databaseTransactionLogBytesUsed,
        long databaseTransactionLogBytesReserved,
        int databaseTransactionLogBytesUsedSystem,
        int databaseTransactionLogBytesReservedSystem,
        object? databaseTransactionBeginLsn,
        object? databaseTransactionLastLsn,
        object? databaseTransactionMostRecentSavepointLsn,
        object? databaseTransactionCommitLsn,
        object? databaseTransactionLastRollbackLsn,
        object? databaseTransactionNextUndoLsn)
    {
        _transactionId = transactionId;
        _databaseId = databaseId;
        _databaseTransactionBeginTime = databaseTransactionBeginTime;
        _databaseTransactionType = databaseTransactionType;
        _databaseTransactionState = databaseTransactionState;
        _databaseTransactionStatus = databaseTransactionStatus;
        _databaseTransactionStatus2 = databaseTransactionStatus2;
        _databaseTransactionLogRecordCount = databaseTransactionLogRecordCount;
        _databaseTransactionReplicateRecordCount = databaseTransactionReplicateRecordCount;
        _databaseTransactionLogBytesUsed = databaseTransactionLogBytesUsed;
        _databaseTransactionLogBytesReserved = databaseTransactionLogBytesReserved;
        _databaseTransactionLogBytesUsedSystem = databaseTransactionLogBytesUsedSystem;
        _databaseTransactionLogBytesReservedSystem = databaseTransactionLogBytesReservedSystem;
        _databaseTransactionBeginLsn = databaseTransactionBeginLsn;
        _databaseTransactionLastLsn = databaseTransactionLastLsn;
        _databaseTransactionMostRecentSavepointLsn = databaseTransactionMostRecentSavepointLsn;
        _databaseTransactionCommitLsn = databaseTransactionCommitLsn;
        _databaseTransactionLastRollbackLsn = databaseTransactionLastRollbackLsn;
        _databaseTransactionNextUndoLsn = databaseTransactionNextUndoLsn;
    }

    public long TransactionId => _transactionId;
    public int DatabaseId => _databaseId;
    public DateTime? DatabaseTransactionBeginTime => _databaseTransactionBeginTime;
    public int DatabaseTransactionType => _databaseTransactionType;
    public int DatabaseTransactionState => _databaseTransactionState;
    public int DatabaseTransactionStatus => _databaseTransactionStatus;
    public int DatabaseTransactionStatus2 => _databaseTransactionStatus2;
    public long DatabaseTransactionLogRecordCount => _databaseTransactionLogRecordCount;
    public int DatabaseTransactionReplicateRecordCount => _databaseTransactionReplicateRecordCount;
    public long DatabaseTransactionLogBytesUsed => _databaseTransactionLogBytesUsed;
    public long DatabaseTransactionLogBytesReserved => _databaseTransactionLogBytesReserved;
    public int DatabaseTransactionLogBytesUsedSystem => _databaseTransactionLogBytesUsedSystem;
    public int DatabaseTransactionLogBytesReservedSystem => _databaseTransactionLogBytesReservedSystem;
    public object? DatabaseTransactionBeginLsn => _databaseTransactionBeginLsn;
    public object? DatabaseTransactionLastLsn => _databaseTransactionLastLsn;
    public object? DatabaseTransactionMostRecentSavepointLsn => _databaseTransactionMostRecentSavepointLsn;
    public object? DatabaseTransactionCommitLsn => _databaseTransactionCommitLsn;
    public object? DatabaseTransactionLastRollbackLsn => _databaseTransactionLastRollbackLsn;
    public object? DatabaseTransactionNextUndoLsn => _databaseTransactionNextUndoLsn;
}
