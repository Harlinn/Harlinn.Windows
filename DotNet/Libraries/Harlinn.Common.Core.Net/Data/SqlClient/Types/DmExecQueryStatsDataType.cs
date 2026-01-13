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

public class DmExecQueryStatsDataType
{
    readonly byte[] _sqlHandle = Array.Empty<byte>();
    readonly int _statementStartOffset = 0;
    readonly int _statementEndOffset = 0;
    readonly long? _planGenerationNum;
    readonly byte[] _planHandle = Array.Empty<byte>();
    readonly DateTime? _creationTime;
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
    readonly long _totalClrTime = 0;
    readonly long _lastClrTime = 0;
    readonly long _minClrTime = 0;
    readonly long _maxClrTime = 0;
    readonly long _totalElapsedTime = 0;
    readonly long _lastElapsedTime = 0;
    readonly long _minElapsedTime = 0;
    readonly long _maxElapsedTime = 0;
    readonly byte[]? _queryHash;
    readonly byte[]? _queryPlanHash;
    readonly long? _totalRows;
    readonly long? _lastRows;
    readonly long? _minRows;
    readonly long? _maxRows;
    readonly byte[]? _statementSqlHandle;
    readonly long? _statementContextId;
    readonly long? _totalDop;
    readonly long? _lastDop;
    readonly long? _minDop;
    readonly long? _maxDop;
    readonly long? _totalGrantKb;
    readonly long? _lastGrantKb;
    readonly long? _minGrantKb;
    readonly long? _maxGrantKb;
    readonly long? _totalUsedGrantKb;
    readonly long? _lastUsedGrantKb;
    readonly long? _minUsedGrantKb;
    readonly long? _maxUsedGrantKb;
    readonly long? _totalIdealGrantKb;
    readonly long? _lastIdealGrantKb;
    readonly long? _minIdealGrantKb;
    readonly long? _maxIdealGrantKb;
    readonly long? _totalReservedThreads;
    readonly long? _lastReservedThreads;
    readonly long? _minReservedThreads;
    readonly long? _maxReservedThreads;
    readonly long? _totalUsedThreads;
    readonly long? _lastUsedThreads;
    readonly long? _minUsedThreads;
    readonly long? _maxUsedThreads;
    readonly long? _totalColumnstoreSegmentReads;
    readonly long? _lastColumnstoreSegmentReads;
    readonly long? _minColumnstoreSegmentReads;
    readonly long? _maxColumnstoreSegmentReads;
    readonly long? _totalColumnstoreSegmentSkips;
    readonly long? _lastColumnstoreSegmentSkips;
    readonly long? _minColumnstoreSegmentSkips;
    readonly long? _maxColumnstoreSegmentSkips;
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

    public DmExecQueryStatsDataType( )
    {
    }

    public DmExecQueryStatsDataType(byte[] sqlHandle,
        int statementStartOffset,
        int statementEndOffset,
        long? planGenerationNum,
        byte[] planHandle,
        DateTime? creationTime,
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
        long totalClrTime,
        long lastClrTime,
        long minClrTime,
        long maxClrTime,
        long totalElapsedTime,
        long lastElapsedTime,
        long minElapsedTime,
        long maxElapsedTime,
        byte[]? queryHash,
        byte[]? queryPlanHash,
        long? totalRows,
        long? lastRows,
        long? minRows,
        long? maxRows,
        byte[]? statementSqlHandle,
        long? statementContextId,
        long? totalDop,
        long? lastDop,
        long? minDop,
        long? maxDop,
        long? totalGrantKb,
        long? lastGrantKb,
        long? minGrantKb,
        long? maxGrantKb,
        long? totalUsedGrantKb,
        long? lastUsedGrantKb,
        long? minUsedGrantKb,
        long? maxUsedGrantKb,
        long? totalIdealGrantKb,
        long? lastIdealGrantKb,
        long? minIdealGrantKb,
        long? maxIdealGrantKb,
        long? totalReservedThreads,
        long? lastReservedThreads,
        long? minReservedThreads,
        long? maxReservedThreads,
        long? totalUsedThreads,
        long? lastUsedThreads,
        long? minUsedThreads,
        long? maxUsedThreads,
        long? totalColumnstoreSegmentReads,
        long? lastColumnstoreSegmentReads,
        long? minColumnstoreSegmentReads,
        long? maxColumnstoreSegmentReads,
        long? totalColumnstoreSegmentSkips,
        long? lastColumnstoreSegmentSkips,
        long? minColumnstoreSegmentSkips,
        long? maxColumnstoreSegmentSkips,
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
        _sqlHandle = sqlHandle;
        _statementStartOffset = statementStartOffset;
        _statementEndOffset = statementEndOffset;
        _planGenerationNum = planGenerationNum;
        _planHandle = planHandle;
        _creationTime = creationTime;
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
        _totalClrTime = totalClrTime;
        _lastClrTime = lastClrTime;
        _minClrTime = minClrTime;
        _maxClrTime = maxClrTime;
        _totalElapsedTime = totalElapsedTime;
        _lastElapsedTime = lastElapsedTime;
        _minElapsedTime = minElapsedTime;
        _maxElapsedTime = maxElapsedTime;
        _queryHash = queryHash;
        _queryPlanHash = queryPlanHash;
        _totalRows = totalRows;
        _lastRows = lastRows;
        _minRows = minRows;
        _maxRows = maxRows;
        _statementSqlHandle = statementSqlHandle;
        _statementContextId = statementContextId;
        _totalDop = totalDop;
        _lastDop = lastDop;
        _minDop = minDop;
        _maxDop = maxDop;
        _totalGrantKb = totalGrantKb;
        _lastGrantKb = lastGrantKb;
        _minGrantKb = minGrantKb;
        _maxGrantKb = maxGrantKb;
        _totalUsedGrantKb = totalUsedGrantKb;
        _lastUsedGrantKb = lastUsedGrantKb;
        _minUsedGrantKb = minUsedGrantKb;
        _maxUsedGrantKb = maxUsedGrantKb;
        _totalIdealGrantKb = totalIdealGrantKb;
        _lastIdealGrantKb = lastIdealGrantKb;
        _minIdealGrantKb = minIdealGrantKb;
        _maxIdealGrantKb = maxIdealGrantKb;
        _totalReservedThreads = totalReservedThreads;
        _lastReservedThreads = lastReservedThreads;
        _minReservedThreads = minReservedThreads;
        _maxReservedThreads = maxReservedThreads;
        _totalUsedThreads = totalUsedThreads;
        _lastUsedThreads = lastUsedThreads;
        _minUsedThreads = minUsedThreads;
        _maxUsedThreads = maxUsedThreads;
        _totalColumnstoreSegmentReads = totalColumnstoreSegmentReads;
        _lastColumnstoreSegmentReads = lastColumnstoreSegmentReads;
        _minColumnstoreSegmentReads = minColumnstoreSegmentReads;
        _maxColumnstoreSegmentReads = maxColumnstoreSegmentReads;
        _totalColumnstoreSegmentSkips = totalColumnstoreSegmentSkips;
        _lastColumnstoreSegmentSkips = lastColumnstoreSegmentSkips;
        _minColumnstoreSegmentSkips = minColumnstoreSegmentSkips;
        _maxColumnstoreSegmentSkips = maxColumnstoreSegmentSkips;
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

    public byte[] SqlHandle => _sqlHandle;
    public int StatementStartOffset => _statementStartOffset;
    public int StatementEndOffset => _statementEndOffset;
    public long? PlanGenerationNum => _planGenerationNum;
    public byte[] PlanHandle => _planHandle;
    public DateTime? CreationTime => _creationTime;
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
    public long TotalClrTime => _totalClrTime;
    public long LastClrTime => _lastClrTime;
    public long MinClrTime => _minClrTime;
    public long MaxClrTime => _maxClrTime;
    public long TotalElapsedTime => _totalElapsedTime;
    public long LastElapsedTime => _lastElapsedTime;
    public long MinElapsedTime => _minElapsedTime;
    public long MaxElapsedTime => _maxElapsedTime;
    public byte[]? QueryHash => _queryHash;
    public byte[]? QueryPlanHash => _queryPlanHash;
    public long? TotalRows => _totalRows;
    public long? LastRows => _lastRows;
    public long? MinRows => _minRows;
    public long? MaxRows => _maxRows;
    public byte[]? StatementSqlHandle => _statementSqlHandle;
    public long? StatementContextId => _statementContextId;
    public long? TotalDop => _totalDop;
    public long? LastDop => _lastDop;
    public long? MinDop => _minDop;
    public long? MaxDop => _maxDop;
    public long? TotalGrantKb => _totalGrantKb;
    public long? LastGrantKb => _lastGrantKb;
    public long? MinGrantKb => _minGrantKb;
    public long? MaxGrantKb => _maxGrantKb;
    public long? TotalUsedGrantKb => _totalUsedGrantKb;
    public long? LastUsedGrantKb => _lastUsedGrantKb;
    public long? MinUsedGrantKb => _minUsedGrantKb;
    public long? MaxUsedGrantKb => _maxUsedGrantKb;
    public long? TotalIdealGrantKb => _totalIdealGrantKb;
    public long? LastIdealGrantKb => _lastIdealGrantKb;
    public long? MinIdealGrantKb => _minIdealGrantKb;
    public long? MaxIdealGrantKb => _maxIdealGrantKb;
    public long? TotalReservedThreads => _totalReservedThreads;
    public long? LastReservedThreads => _lastReservedThreads;
    public long? MinReservedThreads => _minReservedThreads;
    public long? MaxReservedThreads => _maxReservedThreads;
    public long? TotalUsedThreads => _totalUsedThreads;
    public long? LastUsedThreads => _lastUsedThreads;
    public long? MinUsedThreads => _minUsedThreads;
    public long? MaxUsedThreads => _maxUsedThreads;
    public long? TotalColumnstoreSegmentReads => _totalColumnstoreSegmentReads;
    public long? LastColumnstoreSegmentReads => _lastColumnstoreSegmentReads;
    public long? MinColumnstoreSegmentReads => _minColumnstoreSegmentReads;
    public long? MaxColumnstoreSegmentReads => _maxColumnstoreSegmentReads;
    public long? TotalColumnstoreSegmentSkips => _totalColumnstoreSegmentSkips;
    public long? LastColumnstoreSegmentSkips => _lastColumnstoreSegmentSkips;
    public long? MinColumnstoreSegmentSkips => _minColumnstoreSegmentSkips;
    public long? MaxColumnstoreSegmentSkips => _maxColumnstoreSegmentSkips;
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
