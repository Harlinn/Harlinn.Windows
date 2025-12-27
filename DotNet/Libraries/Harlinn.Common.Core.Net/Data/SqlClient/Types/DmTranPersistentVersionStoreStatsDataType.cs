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

public class DmTranPersistentVersionStoreStatsDataType
{
    readonly int _databaseId = 0;
    readonly short _pvsFilegroupId = 0;
    readonly long _persistentVersionStoreSizeKb = 0;
    readonly long _onlineIndexVersionStoreSizeKb = 0;
    readonly long _currentAbortedTransactionCount = 0;
    readonly long _oldestActiveTransactionId = 0;
    readonly long _oldestAbortedTransactionId = 0;
    readonly long _minTransactionTimestamp = 0;
    readonly long _onlineIndexMinTransactionTimestamp = 0;
    readonly long _secondaryLowWaterMark = 0;
    readonly DateTime? _offrowVersionCleanerStartTime;
    readonly DateTime? _offrowVersionCleanerEndTime;
    readonly DateTime? _abortedVersionCleanerStartTime;
    readonly DateTime? _abortedVersionCleanerEndTime;
    readonly long _pvsOffRowPageSkippedLowWaterMark = 0;
    readonly long _pvsOffRowPageSkippedTransactionNotCleaned = 0;
    readonly long _pvsOffRowPageSkippedOldestActiveXdesid = 0;
    readonly long _pvsOffRowPageSkippedMinUsefulXts = 0;
    readonly long _pvsOffRowPageSkippedOldestSnapshot = 0;

    public DmTranPersistentVersionStoreStatsDataType( )
    {
    }

    public DmTranPersistentVersionStoreStatsDataType(int databaseId,
        short pvsFilegroupId,
        long persistentVersionStoreSizeKb,
        long onlineIndexVersionStoreSizeKb,
        long currentAbortedTransactionCount,
        long oldestActiveTransactionId,
        long oldestAbortedTransactionId,
        long minTransactionTimestamp,
        long onlineIndexMinTransactionTimestamp,
        long secondaryLowWaterMark,
        DateTime? offrowVersionCleanerStartTime,
        DateTime? offrowVersionCleanerEndTime,
        DateTime? abortedVersionCleanerStartTime,
        DateTime? abortedVersionCleanerEndTime,
        long pvsOffRowPageSkippedLowWaterMark,
        long pvsOffRowPageSkippedTransactionNotCleaned,
        long pvsOffRowPageSkippedOldestActiveXdesid,
        long pvsOffRowPageSkippedMinUsefulXts,
        long pvsOffRowPageSkippedOldestSnapshot)
    {
        _databaseId = databaseId;
        _pvsFilegroupId = pvsFilegroupId;
        _persistentVersionStoreSizeKb = persistentVersionStoreSizeKb;
        _onlineIndexVersionStoreSizeKb = onlineIndexVersionStoreSizeKb;
        _currentAbortedTransactionCount = currentAbortedTransactionCount;
        _oldestActiveTransactionId = oldestActiveTransactionId;
        _oldestAbortedTransactionId = oldestAbortedTransactionId;
        _minTransactionTimestamp = minTransactionTimestamp;
        _onlineIndexMinTransactionTimestamp = onlineIndexMinTransactionTimestamp;
        _secondaryLowWaterMark = secondaryLowWaterMark;
        _offrowVersionCleanerStartTime = offrowVersionCleanerStartTime;
        _offrowVersionCleanerEndTime = offrowVersionCleanerEndTime;
        _abortedVersionCleanerStartTime = abortedVersionCleanerStartTime;
        _abortedVersionCleanerEndTime = abortedVersionCleanerEndTime;
        _pvsOffRowPageSkippedLowWaterMark = pvsOffRowPageSkippedLowWaterMark;
        _pvsOffRowPageSkippedTransactionNotCleaned = pvsOffRowPageSkippedTransactionNotCleaned;
        _pvsOffRowPageSkippedOldestActiveXdesid = pvsOffRowPageSkippedOldestActiveXdesid;
        _pvsOffRowPageSkippedMinUsefulXts = pvsOffRowPageSkippedMinUsefulXts;
        _pvsOffRowPageSkippedOldestSnapshot = pvsOffRowPageSkippedOldestSnapshot;
    }

    public int DatabaseId => _databaseId;
    public short PvsFilegroupId => _pvsFilegroupId;
    public long PersistentVersionStoreSizeKb => _persistentVersionStoreSizeKb;
    public long OnlineIndexVersionStoreSizeKb => _onlineIndexVersionStoreSizeKb;
    public long CurrentAbortedTransactionCount => _currentAbortedTransactionCount;
    public long OldestActiveTransactionId => _oldestActiveTransactionId;
    public long OldestAbortedTransactionId => _oldestAbortedTransactionId;
    public long MinTransactionTimestamp => _minTransactionTimestamp;
    public long OnlineIndexMinTransactionTimestamp => _onlineIndexMinTransactionTimestamp;
    public long SecondaryLowWaterMark => _secondaryLowWaterMark;
    public DateTime? OffrowVersionCleanerStartTime => _offrowVersionCleanerStartTime;
    public DateTime? OffrowVersionCleanerEndTime => _offrowVersionCleanerEndTime;
    public DateTime? AbortedVersionCleanerStartTime => _abortedVersionCleanerStartTime;
    public DateTime? AbortedVersionCleanerEndTime => _abortedVersionCleanerEndTime;
    public long PvsOffRowPageSkippedLowWaterMark => _pvsOffRowPageSkippedLowWaterMark;
    public long PvsOffRowPageSkippedTransactionNotCleaned => _pvsOffRowPageSkippedTransactionNotCleaned;
    public long PvsOffRowPageSkippedOldestActiveXdesid => _pvsOffRowPageSkippedOldestActiveXdesid;
    public long PvsOffRowPageSkippedMinUsefulXts => _pvsOffRowPageSkippedMinUsefulXts;
    public long PvsOffRowPageSkippedOldestSnapshot => _pvsOffRowPageSkippedOldestSnapshot;
}
