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

public class DmDbXtpCheckpointStatsDataType
{
    readonly object? _lastLsnProcessed;
    readonly object? _endOfLogLsn;
    readonly long? _bytesToEndOfLog;
    readonly long? _logConsumptionRate;
    readonly long? _activeScanTimeInMs;
    readonly long? _totalWaitTimeInMs;
    readonly long? _waitsForIoCount;
    readonly long? _ioWaitTimeInMs;
    readonly long? _waitsForNewLogCount;
    readonly long? _newLogWaitTimeInMs;
    readonly long? _idleAttemptsCount;
    readonly long? _txSegmentsDispatchedCount;
    readonly long? _segmentBytesDispatched;
    readonly long? _bytesSerialized;
    readonly long? _serializerUserTimeInMs;
    readonly long? _serializerKernelTimeInMs;
    readonly long? _xtpLogBytesConsumed;
    readonly long? _checkpointsClosed;
    readonly long? _lastClosedCheckpointTs;
    readonly object? _hardenedRecoveryLsn;
    readonly Guid? _hardenedRootFileGuid;
    readonly long? _hardenedRootFileWatermark;
    readonly object? _hardenedTruncationLsn;
    readonly long? _logBytesSinceLastClose;
    readonly long? _timeSinceLastCloseInMs;
    readonly long? _currentCheckpointId;
    readonly long? _currentCheckpointSegmentCount;
    readonly object? _recoveryLsnCandidate;
    readonly long? _outstandingCheckpointCount;
    readonly long? _closingCheckpointId;
    readonly long? _recoveryCheckpointId;
    readonly long? _recoveryCheckpointTs;
    readonly object? _bootstrapRecoveryLsn;
    readonly Guid? _bootstrapRootFileGuid;
    readonly long? _internalErrorCode;
    readonly long? _tailCachePageCount;
    readonly long? _tailCacheMaxPageCount;
    readonly object? _tailCacheMinNeededLsn;
    readonly long? _mergeOutstandingMerges;
    readonly long? _mergeStatsNumberOfMerges;
    readonly long? _mergeStatsLogBlocksMerged;
    readonly long? _mergeStatsBytesMerged;
    readonly long? _mergeStatsUserTime;
    readonly long? _mergeStatsKernelTime;
    readonly long? _bytesOfLargeDataSerialized;

    public DmDbXtpCheckpointStatsDataType( )
    {
    }

    public DmDbXtpCheckpointStatsDataType(object? lastLsnProcessed,
        object? endOfLogLsn,
        long? bytesToEndOfLog,
        long? logConsumptionRate,
        long? activeScanTimeInMs,
        long? totalWaitTimeInMs,
        long? waitsForIoCount,
        long? ioWaitTimeInMs,
        long? waitsForNewLogCount,
        long? newLogWaitTimeInMs,
        long? idleAttemptsCount,
        long? txSegmentsDispatchedCount,
        long? segmentBytesDispatched,
        long? bytesSerialized,
        long? serializerUserTimeInMs,
        long? serializerKernelTimeInMs,
        long? xtpLogBytesConsumed,
        long? checkpointsClosed,
        long? lastClosedCheckpointTs,
        object? hardenedRecoveryLsn,
        Guid? hardenedRootFileGuid,
        long? hardenedRootFileWatermark,
        object? hardenedTruncationLsn,
        long? logBytesSinceLastClose,
        long? timeSinceLastCloseInMs,
        long? currentCheckpointId,
        long? currentCheckpointSegmentCount,
        object? recoveryLsnCandidate,
        long? outstandingCheckpointCount,
        long? closingCheckpointId,
        long? recoveryCheckpointId,
        long? recoveryCheckpointTs,
        object? bootstrapRecoveryLsn,
        Guid? bootstrapRootFileGuid,
        long? internalErrorCode,
        long? tailCachePageCount,
        long? tailCacheMaxPageCount,
        object? tailCacheMinNeededLsn,
        long? mergeOutstandingMerges,
        long? mergeStatsNumberOfMerges,
        long? mergeStatsLogBlocksMerged,
        long? mergeStatsBytesMerged,
        long? mergeStatsUserTime,
        long? mergeStatsKernelTime,
        long? bytesOfLargeDataSerialized)
    {
        _lastLsnProcessed = lastLsnProcessed;
        _endOfLogLsn = endOfLogLsn;
        _bytesToEndOfLog = bytesToEndOfLog;
        _logConsumptionRate = logConsumptionRate;
        _activeScanTimeInMs = activeScanTimeInMs;
        _totalWaitTimeInMs = totalWaitTimeInMs;
        _waitsForIoCount = waitsForIoCount;
        _ioWaitTimeInMs = ioWaitTimeInMs;
        _waitsForNewLogCount = waitsForNewLogCount;
        _newLogWaitTimeInMs = newLogWaitTimeInMs;
        _idleAttemptsCount = idleAttemptsCount;
        _txSegmentsDispatchedCount = txSegmentsDispatchedCount;
        _segmentBytesDispatched = segmentBytesDispatched;
        _bytesSerialized = bytesSerialized;
        _serializerUserTimeInMs = serializerUserTimeInMs;
        _serializerKernelTimeInMs = serializerKernelTimeInMs;
        _xtpLogBytesConsumed = xtpLogBytesConsumed;
        _checkpointsClosed = checkpointsClosed;
        _lastClosedCheckpointTs = lastClosedCheckpointTs;
        _hardenedRecoveryLsn = hardenedRecoveryLsn;
        _hardenedRootFileGuid = hardenedRootFileGuid;
        _hardenedRootFileWatermark = hardenedRootFileWatermark;
        _hardenedTruncationLsn = hardenedTruncationLsn;
        _logBytesSinceLastClose = logBytesSinceLastClose;
        _timeSinceLastCloseInMs = timeSinceLastCloseInMs;
        _currentCheckpointId = currentCheckpointId;
        _currentCheckpointSegmentCount = currentCheckpointSegmentCount;
        _recoveryLsnCandidate = recoveryLsnCandidate;
        _outstandingCheckpointCount = outstandingCheckpointCount;
        _closingCheckpointId = closingCheckpointId;
        _recoveryCheckpointId = recoveryCheckpointId;
        _recoveryCheckpointTs = recoveryCheckpointTs;
        _bootstrapRecoveryLsn = bootstrapRecoveryLsn;
        _bootstrapRootFileGuid = bootstrapRootFileGuid;
        _internalErrorCode = internalErrorCode;
        _tailCachePageCount = tailCachePageCount;
        _tailCacheMaxPageCount = tailCacheMaxPageCount;
        _tailCacheMinNeededLsn = tailCacheMinNeededLsn;
        _mergeOutstandingMerges = mergeOutstandingMerges;
        _mergeStatsNumberOfMerges = mergeStatsNumberOfMerges;
        _mergeStatsLogBlocksMerged = mergeStatsLogBlocksMerged;
        _mergeStatsBytesMerged = mergeStatsBytesMerged;
        _mergeStatsUserTime = mergeStatsUserTime;
        _mergeStatsKernelTime = mergeStatsKernelTime;
        _bytesOfLargeDataSerialized = bytesOfLargeDataSerialized;
    }

    public object? LastLsnProcessed => _lastLsnProcessed;
    public object? EndOfLogLsn => _endOfLogLsn;
    public long? BytesToEndOfLog => _bytesToEndOfLog;
    public long? LogConsumptionRate => _logConsumptionRate;
    public long? ActiveScanTimeInMs => _activeScanTimeInMs;
    public long? TotalWaitTimeInMs => _totalWaitTimeInMs;
    public long? WaitsForIoCount => _waitsForIoCount;
    public long? IoWaitTimeInMs => _ioWaitTimeInMs;
    public long? WaitsForNewLogCount => _waitsForNewLogCount;
    public long? NewLogWaitTimeInMs => _newLogWaitTimeInMs;
    public long? IdleAttemptsCount => _idleAttemptsCount;
    public long? TxSegmentsDispatchedCount => _txSegmentsDispatchedCount;
    public long? SegmentBytesDispatched => _segmentBytesDispatched;
    public long? BytesSerialized => _bytesSerialized;
    public long? SerializerUserTimeInMs => _serializerUserTimeInMs;
    public long? SerializerKernelTimeInMs => _serializerKernelTimeInMs;
    public long? XtpLogBytesConsumed => _xtpLogBytesConsumed;
    public long? CheckpointsClosed => _checkpointsClosed;
    public long? LastClosedCheckpointTs => _lastClosedCheckpointTs;
    public object? HardenedRecoveryLsn => _hardenedRecoveryLsn;
    public Guid? HardenedRootFileGuid => _hardenedRootFileGuid;
    public long? HardenedRootFileWatermark => _hardenedRootFileWatermark;
    public object? HardenedTruncationLsn => _hardenedTruncationLsn;
    public long? LogBytesSinceLastClose => _logBytesSinceLastClose;
    public long? TimeSinceLastCloseInMs => _timeSinceLastCloseInMs;
    public long? CurrentCheckpointId => _currentCheckpointId;
    public long? CurrentCheckpointSegmentCount => _currentCheckpointSegmentCount;
    public object? RecoveryLsnCandidate => _recoveryLsnCandidate;
    public long? OutstandingCheckpointCount => _outstandingCheckpointCount;
    public long? ClosingCheckpointId => _closingCheckpointId;
    public long? RecoveryCheckpointId => _recoveryCheckpointId;
    public long? RecoveryCheckpointTs => _recoveryCheckpointTs;
    public object? BootstrapRecoveryLsn => _bootstrapRecoveryLsn;
    public Guid? BootstrapRootFileGuid => _bootstrapRootFileGuid;
    public long? InternalErrorCode => _internalErrorCode;
    public long? TailCachePageCount => _tailCachePageCount;
    public long? TailCacheMaxPageCount => _tailCacheMaxPageCount;
    public object? TailCacheMinNeededLsn => _tailCacheMinNeededLsn;
    public long? MergeOutstandingMerges => _mergeOutstandingMerges;
    public long? MergeStatsNumberOfMerges => _mergeStatsNumberOfMerges;
    public long? MergeStatsLogBlocksMerged => _mergeStatsLogBlocksMerged;
    public long? MergeStatsBytesMerged => _mergeStatsBytesMerged;
    public long? MergeStatsUserTime => _mergeStatsUserTime;
    public long? MergeStatsKernelTime => _mergeStatsKernelTime;
    public long? BytesOfLargeDataSerialized => _bytesOfLargeDataSerialized;
}
