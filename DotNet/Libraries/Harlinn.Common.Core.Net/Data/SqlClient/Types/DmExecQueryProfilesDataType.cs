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

public class DmExecQueryProfilesDataType
{
    readonly short? _sessionId;
    readonly int? _requestId;
    readonly byte[]? _sqlHandle;
    readonly byte[]? _planHandle;
    readonly string? _physicalOperatorName;
    readonly int? _nodeId;
    readonly int? _threadId;
    readonly byte[] _taskAddress = Array.Empty<byte>();
    readonly long? _rowCount;
    readonly long? _rewindCount;
    readonly long? _rebindCount;
    readonly long? _endOfScanCount;
    readonly long? _estimateRowCount;
    readonly long? _firstActiveTime;
    readonly long? _lastActiveTime;
    readonly long? _openTime;
    readonly long? _firstRowTime;
    readonly long? _lastRowTime;
    readonly long? _closeTime;
    readonly long? _elapsedTimeMs;
    readonly long? _cpuTimeMs;
    readonly short? _databaseId;
    readonly int? _objectId;
    readonly int? _indexId;
    readonly long? _scanCount;
    readonly long? _logicalReadCount;
    readonly long? _physicalReadCount;
    readonly long? _readAheadCount;
    readonly long? _writePageCount;
    readonly long? _lobLogicalReadCount;
    readonly long? _lobPhysicalReadCount;
    readonly long? _lobReadAheadCount;
    readonly int? _segmentReadCount;
    readonly int? _segmentSkipCount;
    readonly long? _actualReadRowCount;
    readonly long? _estimatedReadRowCount;
    readonly long? _pageServerReadCount;
    readonly long? _pageServerReadAheadCount;
    readonly long? _lobPageServerReadCount;
    readonly long? _lobPageServerReadAheadCount;

    public DmExecQueryProfilesDataType( )
    {
    }

    public DmExecQueryProfilesDataType(short? sessionId,
        int? requestId,
        byte[]? sqlHandle,
        byte[]? planHandle,
        string? physicalOperatorName,
        int? nodeId,
        int? threadId,
        byte[] taskAddress,
        long? rowCount,
        long? rewindCount,
        long? rebindCount,
        long? endOfScanCount,
        long? estimateRowCount,
        long? firstActiveTime,
        long? lastActiveTime,
        long? openTime,
        long? firstRowTime,
        long? lastRowTime,
        long? closeTime,
        long? elapsedTimeMs,
        long? cpuTimeMs,
        short? databaseId,
        int? objectId,
        int? indexId,
        long? scanCount,
        long? logicalReadCount,
        long? physicalReadCount,
        long? readAheadCount,
        long? writePageCount,
        long? lobLogicalReadCount,
        long? lobPhysicalReadCount,
        long? lobReadAheadCount,
        int? segmentReadCount,
        int? segmentSkipCount,
        long? actualReadRowCount,
        long? estimatedReadRowCount,
        long? pageServerReadCount,
        long? pageServerReadAheadCount,
        long? lobPageServerReadCount,
        long? lobPageServerReadAheadCount)
    {
        _sessionId = sessionId;
        _requestId = requestId;
        _sqlHandle = sqlHandle;
        _planHandle = planHandle;
        _physicalOperatorName = physicalOperatorName;
        _nodeId = nodeId;
        _threadId = threadId;
        _taskAddress = taskAddress;
        _rowCount = rowCount;
        _rewindCount = rewindCount;
        _rebindCount = rebindCount;
        _endOfScanCount = endOfScanCount;
        _estimateRowCount = estimateRowCount;
        _firstActiveTime = firstActiveTime;
        _lastActiveTime = lastActiveTime;
        _openTime = openTime;
        _firstRowTime = firstRowTime;
        _lastRowTime = lastRowTime;
        _closeTime = closeTime;
        _elapsedTimeMs = elapsedTimeMs;
        _cpuTimeMs = cpuTimeMs;
        _databaseId = databaseId;
        _objectId = objectId;
        _indexId = indexId;
        _scanCount = scanCount;
        _logicalReadCount = logicalReadCount;
        _physicalReadCount = physicalReadCount;
        _readAheadCount = readAheadCount;
        _writePageCount = writePageCount;
        _lobLogicalReadCount = lobLogicalReadCount;
        _lobPhysicalReadCount = lobPhysicalReadCount;
        _lobReadAheadCount = lobReadAheadCount;
        _segmentReadCount = segmentReadCount;
        _segmentSkipCount = segmentSkipCount;
        _actualReadRowCount = actualReadRowCount;
        _estimatedReadRowCount = estimatedReadRowCount;
        _pageServerReadCount = pageServerReadCount;
        _pageServerReadAheadCount = pageServerReadAheadCount;
        _lobPageServerReadCount = lobPageServerReadCount;
        _lobPageServerReadAheadCount = lobPageServerReadAheadCount;
    }

    public short? SessionId => _sessionId;
    public int? RequestId => _requestId;
    public byte[]? SqlHandle => _sqlHandle;
    public byte[]? PlanHandle => _planHandle;
    public string? PhysicalOperatorName => _physicalOperatorName;
    public int? NodeId => _nodeId;
    public int? ThreadId => _threadId;
    public byte[] TaskAddress => _taskAddress;
    public long? RowCount => _rowCount;
    public long? RewindCount => _rewindCount;
    public long? RebindCount => _rebindCount;
    public long? EndOfScanCount => _endOfScanCount;
    public long? EstimateRowCount => _estimateRowCount;
    public long? FirstActiveTime => _firstActiveTime;
    public long? LastActiveTime => _lastActiveTime;
    public long? OpenTime => _openTime;
    public long? FirstRowTime => _firstRowTime;
    public long? LastRowTime => _lastRowTime;
    public long? CloseTime => _closeTime;
    public long? ElapsedTimeMs => _elapsedTimeMs;
    public long? CpuTimeMs => _cpuTimeMs;
    public short? DatabaseId => _databaseId;
    public int? ObjectId => _objectId;
    public int? IndexId => _indexId;
    public long? ScanCount => _scanCount;
    public long? LogicalReadCount => _logicalReadCount;
    public long? PhysicalReadCount => _physicalReadCount;
    public long? ReadAheadCount => _readAheadCount;
    public long? WritePageCount => _writePageCount;
    public long? LobLogicalReadCount => _lobLogicalReadCount;
    public long? LobPhysicalReadCount => _lobPhysicalReadCount;
    public long? LobReadAheadCount => _lobReadAheadCount;
    public int? SegmentReadCount => _segmentReadCount;
    public int? SegmentSkipCount => _segmentSkipCount;
    public long? ActualReadRowCount => _actualReadRowCount;
    public long? EstimatedReadRowCount => _estimatedReadRowCount;
    public long? PageServerReadCount => _pageServerReadCount;
    public long? PageServerReadAheadCount => _pageServerReadAheadCount;
    public long? LobPageServerReadCount => _lobPageServerReadCount;
    public long? LobPageServerReadAheadCount => _lobPageServerReadAheadCount;
}
