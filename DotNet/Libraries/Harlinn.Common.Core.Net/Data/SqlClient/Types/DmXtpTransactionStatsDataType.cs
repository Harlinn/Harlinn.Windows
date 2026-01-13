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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmXtpTransactionStatsDataType
{
    readonly long _totalCount = 0;
    readonly long _readOnlyCount = 0;
    readonly long _totalAborts = 0;
    readonly long _systemAborts = 0;
    readonly long _validationFailures = 0;
    readonly long _dependenciesTaken = 0;
    readonly long _dependenciesFailed = 0;
    readonly long _savepointCreate = 0;
    readonly long _savepointRollbacks = 0;
    readonly long _savepointRefreshes = 0;
    readonly long _logBytesWritten = 0;
    readonly long _logIoCount = 0;
    readonly long _phantomScansStarted = 0;
    readonly long _phantomScansRetries = 0;
    readonly long _phantomRowsTouched = 0;
    readonly long _phantomRowsExpiring = 0;
    readonly long _phantomRowsExpired = 0;
    readonly long _phantomRowsExpiredRemoved = 0;
    readonly long _scansStarted = 0;
    readonly long _scansRetried = 0;
    readonly long _rowsReturned = 0;
    readonly long _rowsTouched = 0;
    readonly long _rowsExpiring = 0;
    readonly long _rowsExpired = 0;
    readonly long _rowsExpiredRemoved = 0;
    readonly long _rowInsertAttempts = 0;
    readonly long _rowUpdateAttempts = 0;
    readonly long _rowDeleteAttempts = 0;
    readonly long _writeConflicts = 0;
    readonly long _uniqueConstraintViolations = 0;
    readonly long _dropTableMemoryAttempts = 0;
    readonly long _dropTableMemoryFailures = 0;

    public DmXtpTransactionStatsDataType( )
    {
    }

    public DmXtpTransactionStatsDataType(long totalCount,
        long readOnlyCount,
        long totalAborts,
        long systemAborts,
        long validationFailures,
        long dependenciesTaken,
        long dependenciesFailed,
        long savepointCreate,
        long savepointRollbacks,
        long savepointRefreshes,
        long logBytesWritten,
        long logIoCount,
        long phantomScansStarted,
        long phantomScansRetries,
        long phantomRowsTouched,
        long phantomRowsExpiring,
        long phantomRowsExpired,
        long phantomRowsExpiredRemoved,
        long scansStarted,
        long scansRetried,
        long rowsReturned,
        long rowsTouched,
        long rowsExpiring,
        long rowsExpired,
        long rowsExpiredRemoved,
        long rowInsertAttempts,
        long rowUpdateAttempts,
        long rowDeleteAttempts,
        long writeConflicts,
        long uniqueConstraintViolations,
        long dropTableMemoryAttempts,
        long dropTableMemoryFailures)
    {
        _totalCount = totalCount;
        _readOnlyCount = readOnlyCount;
        _totalAborts = totalAborts;
        _systemAborts = systemAborts;
        _validationFailures = validationFailures;
        _dependenciesTaken = dependenciesTaken;
        _dependenciesFailed = dependenciesFailed;
        _savepointCreate = savepointCreate;
        _savepointRollbacks = savepointRollbacks;
        _savepointRefreshes = savepointRefreshes;
        _logBytesWritten = logBytesWritten;
        _logIoCount = logIoCount;
        _phantomScansStarted = phantomScansStarted;
        _phantomScansRetries = phantomScansRetries;
        _phantomRowsTouched = phantomRowsTouched;
        _phantomRowsExpiring = phantomRowsExpiring;
        _phantomRowsExpired = phantomRowsExpired;
        _phantomRowsExpiredRemoved = phantomRowsExpiredRemoved;
        _scansStarted = scansStarted;
        _scansRetried = scansRetried;
        _rowsReturned = rowsReturned;
        _rowsTouched = rowsTouched;
        _rowsExpiring = rowsExpiring;
        _rowsExpired = rowsExpired;
        _rowsExpiredRemoved = rowsExpiredRemoved;
        _rowInsertAttempts = rowInsertAttempts;
        _rowUpdateAttempts = rowUpdateAttempts;
        _rowDeleteAttempts = rowDeleteAttempts;
        _writeConflicts = writeConflicts;
        _uniqueConstraintViolations = uniqueConstraintViolations;
        _dropTableMemoryAttempts = dropTableMemoryAttempts;
        _dropTableMemoryFailures = dropTableMemoryFailures;
    }

    public long TotalCount => _totalCount;
    public long ReadOnlyCount => _readOnlyCount;
    public long TotalAborts => _totalAborts;
    public long SystemAborts => _systemAborts;
    public long ValidationFailures => _validationFailures;
    public long DependenciesTaken => _dependenciesTaken;
    public long DependenciesFailed => _dependenciesFailed;
    public long SavepointCreate => _savepointCreate;
    public long SavepointRollbacks => _savepointRollbacks;
    public long SavepointRefreshes => _savepointRefreshes;
    public long LogBytesWritten => _logBytesWritten;
    public long LogIoCount => _logIoCount;
    public long PhantomScansStarted => _phantomScansStarted;
    public long PhantomScansRetries => _phantomScansRetries;
    public long PhantomRowsTouched => _phantomRowsTouched;
    public long PhantomRowsExpiring => _phantomRowsExpiring;
    public long PhantomRowsExpired => _phantomRowsExpired;
    public long PhantomRowsExpiredRemoved => _phantomRowsExpiredRemoved;
    public long ScansStarted => _scansStarted;
    public long ScansRetried => _scansRetried;
    public long RowsReturned => _rowsReturned;
    public long RowsTouched => _rowsTouched;
    public long RowsExpiring => _rowsExpiring;
    public long RowsExpired => _rowsExpired;
    public long RowsExpiredRemoved => _rowsExpiredRemoved;
    public long RowInsertAttempts => _rowInsertAttempts;
    public long RowUpdateAttempts => _rowUpdateAttempts;
    public long RowDeleteAttempts => _rowDeleteAttempts;
    public long WriteConflicts => _writeConflicts;
    public long UniqueConstraintViolations => _uniqueConstraintViolations;
    public long DropTableMemoryAttempts => _dropTableMemoryAttempts;
    public long DropTableMemoryFailures => _dropTableMemoryFailures;
}
