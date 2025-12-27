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

public class DmXtpGcStatsDataType
{
    readonly long _rowsExamined = 0;
    readonly long _rowsNoSweepNeeded = 0;
    readonly long _rowsFirstInBucket = 0;
    readonly long _rowsFirstInBucketRemoved = 0;
    readonly long _rowsMarkedForUnlink = 0;
    readonly long _parallelAssistCount = 0;
    readonly long _idleWorkerCount = 0;
    readonly long _sweepScansStarted = 0;
    readonly long _sweepScanRetries = 0;
    readonly long _sweepRowsTouched = 0;
    readonly long _sweepRowsExpiring = 0;
    readonly long _sweepRowsExpired = 0;
    readonly long _sweepRowsExpiredRemoved = 0;

    public DmXtpGcStatsDataType( )
    {
    }

    public DmXtpGcStatsDataType(long rowsExamined,
        long rowsNoSweepNeeded,
        long rowsFirstInBucket,
        long rowsFirstInBucketRemoved,
        long rowsMarkedForUnlink,
        long parallelAssistCount,
        long idleWorkerCount,
        long sweepScansStarted,
        long sweepScanRetries,
        long sweepRowsTouched,
        long sweepRowsExpiring,
        long sweepRowsExpired,
        long sweepRowsExpiredRemoved)
    {
        _rowsExamined = rowsExamined;
        _rowsNoSweepNeeded = rowsNoSweepNeeded;
        _rowsFirstInBucket = rowsFirstInBucket;
        _rowsFirstInBucketRemoved = rowsFirstInBucketRemoved;
        _rowsMarkedForUnlink = rowsMarkedForUnlink;
        _parallelAssistCount = parallelAssistCount;
        _idleWorkerCount = idleWorkerCount;
        _sweepScansStarted = sweepScansStarted;
        _sweepScanRetries = sweepScanRetries;
        _sweepRowsTouched = sweepRowsTouched;
        _sweepRowsExpiring = sweepRowsExpiring;
        _sweepRowsExpired = sweepRowsExpired;
        _sweepRowsExpiredRemoved = sweepRowsExpiredRemoved;
    }

    public long RowsExamined => _rowsExamined;
    public long RowsNoSweepNeeded => _rowsNoSweepNeeded;
    public long RowsFirstInBucket => _rowsFirstInBucket;
    public long RowsFirstInBucketRemoved => _rowsFirstInBucketRemoved;
    public long RowsMarkedForUnlink => _rowsMarkedForUnlink;
    public long ParallelAssistCount => _parallelAssistCount;
    public long IdleWorkerCount => _idleWorkerCount;
    public long SweepScansStarted => _sweepScansStarted;
    public long SweepScanRetries => _sweepScanRetries;
    public long SweepRowsTouched => _sweepRowsTouched;
    public long SweepRowsExpiring => _sweepRowsExpiring;
    public long SweepRowsExpired => _sweepRowsExpired;
    public long SweepRowsExpiredRemoved => _sweepRowsExpiredRemoved;
}
