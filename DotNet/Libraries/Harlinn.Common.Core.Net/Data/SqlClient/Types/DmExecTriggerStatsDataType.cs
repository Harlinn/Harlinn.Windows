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

public class DmExecTriggerStatsDataType
{
    readonly int _databaseId = 0;
    readonly int _objectId = 0;
    readonly string? _type;
    readonly string? _typeDesc;
    readonly byte[] _sqlHandle = Array.Empty<byte>();
    readonly byte[] _planHandle = Array.Empty<byte>();
    readonly DateTime? _cachedTime;
    readonly DateTime? _lastExecutionTime;
    readonly long _executionCount = 0;
    readonly long _totalWorkerTime = 0;
    readonly long _lastWorkerTime = 0;
    readonly long _minWorkerTime = 0;
    readonly long _maxWorkerTime = 0;
    readonly long _totalPhysicalReads = 0;
    readonly long _lastPhysicalReads = 0;
    readonly long _minPhysicalReads = 0;
    readonly long _maxPhysicalReads = 0;
    readonly long _totalLogicalWrites = 0;
    readonly long _lastLogicalWrites = 0;
    readonly long _minLogicalWrites = 0;
    readonly long _maxLogicalWrites = 0;
    readonly long _totalLogicalReads = 0;
    readonly long _lastLogicalReads = 0;
    readonly long _minLogicalReads = 0;
    readonly long _maxLogicalReads = 0;
    readonly long _totalElapsedTime = 0;
    readonly long _lastElapsedTime = 0;
    readonly long _minElapsedTime = 0;
    readonly long _maxElapsedTime = 0;
    readonly long? _totalSpills;
    readonly long? _lastSpills;
    readonly long? _minSpills;
    readonly long? _maxSpills;
    readonly long _totalNumPhysicalReads = 0;
    readonly long _lastNumPhysicalReads = 0;
    readonly long _minNumPhysicalReads = 0;
    readonly long _maxNumPhysicalReads = 0;
    readonly long _totalPageServerReads = 0;
    readonly long _lastPageServerReads = 0;
    readonly long _minPageServerReads = 0;
    readonly long _maxPageServerReads = 0;
    readonly long _totalNumPageServerReads = 0;
    readonly long _lastNumPageServerReads = 0;
    readonly long _minNumPageServerReads = 0;
    readonly long _maxNumPageServerReads = 0;

    public DmExecTriggerStatsDataType( )
    {
    }

    public DmExecTriggerStatsDataType(int databaseId,
        int objectId,
        string? type,
        string? typeDesc,
        byte[] sqlHandle,
        byte[] planHandle,
        DateTime? cachedTime,
        DateTime? lastExecutionTime,
        long executionCount,
        long totalWorkerTime,
        long lastWorkerTime,
        long minWorkerTime,
        long maxWorkerTime,
        long totalPhysicalReads,
        long lastPhysicalReads,
        long minPhysicalReads,
        long maxPhysicalReads,
        long totalLogicalWrites,
        long lastLogicalWrites,
        long minLogicalWrites,
        long maxLogicalWrites,
        long totalLogicalReads,
        long lastLogicalReads,
        long minLogicalReads,
        long maxLogicalReads,
        long totalElapsedTime,
        long lastElapsedTime,
        long minElapsedTime,
        long maxElapsedTime,
        long? totalSpills,
        long? lastSpills,
        long? minSpills,
        long? maxSpills,
        long totalNumPhysicalReads,
        long lastNumPhysicalReads,
        long minNumPhysicalReads,
        long maxNumPhysicalReads,
        long totalPageServerReads,
        long lastPageServerReads,
        long minPageServerReads,
        long maxPageServerReads,
        long totalNumPageServerReads,
        long lastNumPageServerReads,
        long minNumPageServerReads,
        long maxNumPageServerReads)
    {
        _databaseId = databaseId;
        _objectId = objectId;
        _type = type;
        _typeDesc = typeDesc;
        _sqlHandle = sqlHandle;
        _planHandle = planHandle;
        _cachedTime = cachedTime;
        _lastExecutionTime = lastExecutionTime;
        _executionCount = executionCount;
        _totalWorkerTime = totalWorkerTime;
        _lastWorkerTime = lastWorkerTime;
        _minWorkerTime = minWorkerTime;
        _maxWorkerTime = maxWorkerTime;
        _totalPhysicalReads = totalPhysicalReads;
        _lastPhysicalReads = lastPhysicalReads;
        _minPhysicalReads = minPhysicalReads;
        _maxPhysicalReads = maxPhysicalReads;
        _totalLogicalWrites = totalLogicalWrites;
        _lastLogicalWrites = lastLogicalWrites;
        _minLogicalWrites = minLogicalWrites;
        _maxLogicalWrites = maxLogicalWrites;
        _totalLogicalReads = totalLogicalReads;
        _lastLogicalReads = lastLogicalReads;
        _minLogicalReads = minLogicalReads;
        _maxLogicalReads = maxLogicalReads;
        _totalElapsedTime = totalElapsedTime;
        _lastElapsedTime = lastElapsedTime;
        _minElapsedTime = minElapsedTime;
        _maxElapsedTime = maxElapsedTime;
        _totalSpills = totalSpills;
        _lastSpills = lastSpills;
        _minSpills = minSpills;
        _maxSpills = maxSpills;
        _totalNumPhysicalReads = totalNumPhysicalReads;
        _lastNumPhysicalReads = lastNumPhysicalReads;
        _minNumPhysicalReads = minNumPhysicalReads;
        _maxNumPhysicalReads = maxNumPhysicalReads;
        _totalPageServerReads = totalPageServerReads;
        _lastPageServerReads = lastPageServerReads;
        _minPageServerReads = minPageServerReads;
        _maxPageServerReads = maxPageServerReads;
        _totalNumPageServerReads = totalNumPageServerReads;
        _lastNumPageServerReads = lastNumPageServerReads;
        _minNumPageServerReads = minNumPageServerReads;
        _maxNumPageServerReads = maxNumPageServerReads;
    }

    public int DatabaseId => _databaseId;
    public int ObjectId => _objectId;
    public string? Type => _type;
    public string? TypeDesc => _typeDesc;
    public byte[] SqlHandle => _sqlHandle;
    public byte[] PlanHandle => _planHandle;
    public DateTime? CachedTime => _cachedTime;
    public DateTime? LastExecutionTime => _lastExecutionTime;
    public long ExecutionCount => _executionCount;
    public long TotalWorkerTime => _totalWorkerTime;
    public long LastWorkerTime => _lastWorkerTime;
    public long MinWorkerTime => _minWorkerTime;
    public long MaxWorkerTime => _maxWorkerTime;
    public long TotalPhysicalReads => _totalPhysicalReads;
    public long LastPhysicalReads => _lastPhysicalReads;
    public long MinPhysicalReads => _minPhysicalReads;
    public long MaxPhysicalReads => _maxPhysicalReads;
    public long TotalLogicalWrites => _totalLogicalWrites;
    public long LastLogicalWrites => _lastLogicalWrites;
    public long MinLogicalWrites => _minLogicalWrites;
    public long MaxLogicalWrites => _maxLogicalWrites;
    public long TotalLogicalReads => _totalLogicalReads;
    public long LastLogicalReads => _lastLogicalReads;
    public long MinLogicalReads => _minLogicalReads;
    public long MaxLogicalReads => _maxLogicalReads;
    public long TotalElapsedTime => _totalElapsedTime;
    public long LastElapsedTime => _lastElapsedTime;
    public long MinElapsedTime => _minElapsedTime;
    public long MaxElapsedTime => _maxElapsedTime;
    public long? TotalSpills => _totalSpills;
    public long? LastSpills => _lastSpills;
    public long? MinSpills => _minSpills;
    public long? MaxSpills => _maxSpills;
    public long TotalNumPhysicalReads => _totalNumPhysicalReads;
    public long LastNumPhysicalReads => _lastNumPhysicalReads;
    public long MinNumPhysicalReads => _minNumPhysicalReads;
    public long MaxNumPhysicalReads => _maxNumPhysicalReads;
    public long TotalPageServerReads => _totalPageServerReads;
    public long LastPageServerReads => _lastPageServerReads;
    public long MinPageServerReads => _minPageServerReads;
    public long MaxPageServerReads => _maxPageServerReads;
    public long TotalNumPageServerReads => _totalNumPageServerReads;
    public long LastNumPageServerReads => _lastNumPageServerReads;
    public long MinNumPageServerReads => _minNumPageServerReads;
    public long MaxNumPageServerReads => _maxNumPageServerReads;
}
