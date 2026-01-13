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

public class QueryStoreQueryDataType
{
    readonly long _queryId = 0;
    readonly long _queryTextId = 0;
    readonly long _contextSettingsId = 0;
    readonly long? _objectId;
    readonly byte[]? _batchSqlHandle;
    readonly byte[] _queryHash = Array.Empty<byte>();
    readonly bool _isInternalQuery = false;
    readonly byte _queryParameterizationType = 0;
    readonly string? _queryParameterizationTypeDesc;
    readonly DateTime _initialCompileStartTime;
    readonly DateTime? _lastCompileStartTime;
    readonly DateTime? _lastExecutionTime;
    readonly byte[]? _lastCompileBatchSqlHandle;
    readonly long? _lastCompileBatchOffsetStart;
    readonly long? _lastCompileBatchOffsetEnd;
    readonly long? _countCompiles;
    readonly double? _avgCompileDuration;
    readonly long? _lastCompileDuration;
    readonly double? _avgBindDuration;
    readonly long? _lastBindDuration;
    readonly double? _avgBindCpuTime;
    readonly long? _lastBindCpuTime;
    readonly double? _avgOptimizeDuration;
    readonly long? _lastOptimizeDuration;
    readonly double? _avgOptimizeCpuTime;
    readonly long? _lastOptimizeCpuTime;
    readonly double? _avgCompileMemoryKb;
    readonly long? _lastCompileMemoryKb;
    readonly long? _maxCompileMemoryKb;
    readonly bool? _isClouddbInternalQuery;

    public QueryStoreQueryDataType( )
    {
    }

    public QueryStoreQueryDataType(long queryId,
        long queryTextId,
        long contextSettingsId,
        long? objectId,
        byte[]? batchSqlHandle,
        byte[] queryHash,
        bool isInternalQuery,
        byte queryParameterizationType,
        string? queryParameterizationTypeDesc,
        DateTime initialCompileStartTime,
        DateTime? lastCompileStartTime,
        DateTime? lastExecutionTime,
        byte[]? lastCompileBatchSqlHandle,
        long? lastCompileBatchOffsetStart,
        long? lastCompileBatchOffsetEnd,
        long? countCompiles,
        double? avgCompileDuration,
        long? lastCompileDuration,
        double? avgBindDuration,
        long? lastBindDuration,
        double? avgBindCpuTime,
        long? lastBindCpuTime,
        double? avgOptimizeDuration,
        long? lastOptimizeDuration,
        double? avgOptimizeCpuTime,
        long? lastOptimizeCpuTime,
        double? avgCompileMemoryKb,
        long? lastCompileMemoryKb,
        long? maxCompileMemoryKb,
        bool? isClouddbInternalQuery)
    {
        _queryId = queryId;
        _queryTextId = queryTextId;
        _contextSettingsId = contextSettingsId;
        _objectId = objectId;
        _batchSqlHandle = batchSqlHandle;
        _queryHash = queryHash;
        _isInternalQuery = isInternalQuery;
        _queryParameterizationType = queryParameterizationType;
        _queryParameterizationTypeDesc = queryParameterizationTypeDesc;
        _initialCompileStartTime = initialCompileStartTime;
        _lastCompileStartTime = lastCompileStartTime;
        _lastExecutionTime = lastExecutionTime;
        _lastCompileBatchSqlHandle = lastCompileBatchSqlHandle;
        _lastCompileBatchOffsetStart = lastCompileBatchOffsetStart;
        _lastCompileBatchOffsetEnd = lastCompileBatchOffsetEnd;
        _countCompiles = countCompiles;
        _avgCompileDuration = avgCompileDuration;
        _lastCompileDuration = lastCompileDuration;
        _avgBindDuration = avgBindDuration;
        _lastBindDuration = lastBindDuration;
        _avgBindCpuTime = avgBindCpuTime;
        _lastBindCpuTime = lastBindCpuTime;
        _avgOptimizeDuration = avgOptimizeDuration;
        _lastOptimizeDuration = lastOptimizeDuration;
        _avgOptimizeCpuTime = avgOptimizeCpuTime;
        _lastOptimizeCpuTime = lastOptimizeCpuTime;
        _avgCompileMemoryKb = avgCompileMemoryKb;
        _lastCompileMemoryKb = lastCompileMemoryKb;
        _maxCompileMemoryKb = maxCompileMemoryKb;
        _isClouddbInternalQuery = isClouddbInternalQuery;
    }

    public long QueryId => _queryId;
    public long QueryTextId => _queryTextId;
    public long ContextSettingsId => _contextSettingsId;
    public long? ObjectId => _objectId;
    public byte[]? BatchSqlHandle => _batchSqlHandle;
    public byte[] QueryHash => _queryHash;
    public bool IsInternalQuery => _isInternalQuery;
    public byte QueryParameterizationType => _queryParameterizationType;
    public string? QueryParameterizationTypeDesc => _queryParameterizationTypeDesc;
    public DateTime InitialCompileStartTime => _initialCompileStartTime;
    public DateTime? LastCompileStartTime => _lastCompileStartTime;
    public DateTime? LastExecutionTime => _lastExecutionTime;
    public byte[]? LastCompileBatchSqlHandle => _lastCompileBatchSqlHandle;
    public long? LastCompileBatchOffsetStart => _lastCompileBatchOffsetStart;
    public long? LastCompileBatchOffsetEnd => _lastCompileBatchOffsetEnd;
    public long? CountCompiles => _countCompiles;
    public double? AvgCompileDuration => _avgCompileDuration;
    public long? LastCompileDuration => _lastCompileDuration;
    public double? AvgBindDuration => _avgBindDuration;
    public long? LastBindDuration => _lastBindDuration;
    public double? AvgBindCpuTime => _avgBindCpuTime;
    public long? LastBindCpuTime => _lastBindCpuTime;
    public double? AvgOptimizeDuration => _avgOptimizeDuration;
    public long? LastOptimizeDuration => _lastOptimizeDuration;
    public double? AvgOptimizeCpuTime => _avgOptimizeCpuTime;
    public long? LastOptimizeCpuTime => _lastOptimizeCpuTime;
    public double? AvgCompileMemoryKb => _avgCompileMemoryKb;
    public long? LastCompileMemoryKb => _lastCompileMemoryKb;
    public long? MaxCompileMemoryKb => _maxCompileMemoryKb;
    public bool? IsClouddbInternalQuery => _isClouddbInternalQuery;
}
