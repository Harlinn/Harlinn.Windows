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

public class DmExecBackgroundJobQueueStatsDataType
{
    readonly int _queueMaxLen = 0;
    readonly int _enqueuedCount = 0;
    readonly int _startedCount = 0;
    readonly int _endedCount = 0;
    readonly int _failedLockCount = 0;
    readonly int _failedOtherCount = 0;
    readonly int _failedGiveupCount = 0;
    readonly int _enqueueFailedFullCount = 0;
    readonly int _enqueueFailedDuplicateCount = 0;
    readonly int _elapsedAvgMs = 0;
    readonly int _elapsedMaxMs = 0;

    public DmExecBackgroundJobQueueStatsDataType( )
    {
    }

    public DmExecBackgroundJobQueueStatsDataType(int queueMaxLen,
        int enqueuedCount,
        int startedCount,
        int endedCount,
        int failedLockCount,
        int failedOtherCount,
        int failedGiveupCount,
        int enqueueFailedFullCount,
        int enqueueFailedDuplicateCount,
        int elapsedAvgMs,
        int elapsedMaxMs)
    {
        _queueMaxLen = queueMaxLen;
        _enqueuedCount = enqueuedCount;
        _startedCount = startedCount;
        _endedCount = endedCount;
        _failedLockCount = failedLockCount;
        _failedOtherCount = failedOtherCount;
        _failedGiveupCount = failedGiveupCount;
        _enqueueFailedFullCount = enqueueFailedFullCount;
        _enqueueFailedDuplicateCount = enqueueFailedDuplicateCount;
        _elapsedAvgMs = elapsedAvgMs;
        _elapsedMaxMs = elapsedMaxMs;
    }

    public int QueueMaxLen => _queueMaxLen;
    public int EnqueuedCount => _enqueuedCount;
    public int StartedCount => _startedCount;
    public int EndedCount => _endedCount;
    public int FailedLockCount => _failedLockCount;
    public int FailedOtherCount => _failedOtherCount;
    public int FailedGiveupCount => _failedGiveupCount;
    public int EnqueueFailedFullCount => _enqueueFailedFullCount;
    public int EnqueueFailedDuplicateCount => _enqueueFailedDuplicateCount;
    public int ElapsedAvgMs => _elapsedAvgMs;
    public int ElapsedMaxMs => _elapsedMaxMs;
}
