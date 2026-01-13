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

public class QueryStoreRuntimeStatsDataType
{
    readonly long _runtimeStatsId = 0;
    readonly long _planId = 0;
    readonly long _runtimeStatsIntervalId = 0;
    readonly byte _executionType = 0;
    readonly string? _executionTypeDesc;
    readonly DateTime _firstExecutionTime;
    readonly DateTime _lastExecutionTime;
    readonly long _countExecutions = 0;
    readonly double? _avgDuration;
    readonly long _lastDuration = 0;
    readonly long _minDuration = 0;
    readonly long _maxDuration = 0;
    readonly double? _stdevDuration;
    readonly double? _avgCpuTime;
    readonly long _lastCpuTime = 0;
    readonly long _minCpuTime = 0;
    readonly long _maxCpuTime = 0;
    readonly double? _stdevCpuTime;
    readonly double? _avgLogicalIoReads;
    readonly long _lastLogicalIoReads = 0;
    readonly long _minLogicalIoReads = 0;
    readonly long _maxLogicalIoReads = 0;
    readonly double? _stdevLogicalIoReads;
    readonly double? _avgLogicalIoWrites;
    readonly long _lastLogicalIoWrites = 0;
    readonly long _minLogicalIoWrites = 0;
    readonly long _maxLogicalIoWrites = 0;
    readonly double? _stdevLogicalIoWrites;
    readonly double? _avgPhysicalIoReads;
    readonly long _lastPhysicalIoReads = 0;
    readonly long _minPhysicalIoReads = 0;
    readonly long _maxPhysicalIoReads = 0;
    readonly double? _stdevPhysicalIoReads;
    readonly double? _avgClrTime;
    readonly long _lastClrTime = 0;
    readonly long _minClrTime = 0;
    readonly long _maxClrTime = 0;
    readonly double? _stdevClrTime;
    readonly double? _avgDop;
    readonly long _lastDop = 0;
    readonly long _minDop = 0;
    readonly long _maxDop = 0;
    readonly double? _stdevDop;
    readonly double? _avgQueryMaxUsedMemory;
    readonly long _lastQueryMaxUsedMemory = 0;
    readonly long _minQueryMaxUsedMemory = 0;
    readonly long _maxQueryMaxUsedMemory = 0;
    readonly double? _stdevQueryMaxUsedMemory;
    readonly double? _avgRowcount;
    readonly long _lastRowcount = 0;
    readonly long _minRowcount = 0;
    readonly long _maxRowcount = 0;
    readonly double? _stdevRowcount;
    readonly double? _avgNumPhysicalIoReads;
    readonly long? _lastNumPhysicalIoReads;
    readonly long? _minNumPhysicalIoReads;
    readonly long? _maxNumPhysicalIoReads;
    readonly double? _stdevNumPhysicalIoReads;
    readonly double? _avgLogBytesUsed;
    readonly long? _lastLogBytesUsed;
    readonly long? _minLogBytesUsed;
    readonly long? _maxLogBytesUsed;
    readonly double? _stdevLogBytesUsed;
    readonly double? _avgTempdbSpaceUsed;
    readonly long? _lastTempdbSpaceUsed;
    readonly long? _minTempdbSpaceUsed;
    readonly long? _maxTempdbSpaceUsed;
    readonly double? _stdevTempdbSpaceUsed;

    public QueryStoreRuntimeStatsDataType( )
    {
    }

    public QueryStoreRuntimeStatsDataType(long runtimeStatsId,
        long planId,
        long runtimeStatsIntervalId,
        byte executionType,
        string? executionTypeDesc,
        DateTime firstExecutionTime,
        DateTime lastExecutionTime,
        long countExecutions,
        double? avgDuration,
        long lastDuration,
        long minDuration,
        long maxDuration,
        double? stdevDuration,
        double? avgCpuTime,
        long lastCpuTime,
        long minCpuTime,
        long maxCpuTime,
        double? stdevCpuTime,
        double? avgLogicalIoReads,
        long lastLogicalIoReads,
        long minLogicalIoReads,
        long maxLogicalIoReads,
        double? stdevLogicalIoReads,
        double? avgLogicalIoWrites,
        long lastLogicalIoWrites,
        long minLogicalIoWrites,
        long maxLogicalIoWrites,
        double? stdevLogicalIoWrites,
        double? avgPhysicalIoReads,
        long lastPhysicalIoReads,
        long minPhysicalIoReads,
        long maxPhysicalIoReads,
        double? stdevPhysicalIoReads,
        double? avgClrTime,
        long lastClrTime,
        long minClrTime,
        long maxClrTime,
        double? stdevClrTime,
        double? avgDop,
        long lastDop,
        long minDop,
        long maxDop,
        double? stdevDop,
        double? avgQueryMaxUsedMemory,
        long lastQueryMaxUsedMemory,
        long minQueryMaxUsedMemory,
        long maxQueryMaxUsedMemory,
        double? stdevQueryMaxUsedMemory,
        double? avgRowcount,
        long lastRowcount,
        long minRowcount,
        long maxRowcount,
        double? stdevRowcount,
        double? avgNumPhysicalIoReads,
        long? lastNumPhysicalIoReads,
        long? minNumPhysicalIoReads,
        long? maxNumPhysicalIoReads,
        double? stdevNumPhysicalIoReads,
        double? avgLogBytesUsed,
        long? lastLogBytesUsed,
        long? minLogBytesUsed,
        long? maxLogBytesUsed,
        double? stdevLogBytesUsed,
        double? avgTempdbSpaceUsed,
        long? lastTempdbSpaceUsed,
        long? minTempdbSpaceUsed,
        long? maxTempdbSpaceUsed,
        double? stdevTempdbSpaceUsed)
    {
        _runtimeStatsId = runtimeStatsId;
        _planId = planId;
        _runtimeStatsIntervalId = runtimeStatsIntervalId;
        _executionType = executionType;
        _executionTypeDesc = executionTypeDesc;
        _firstExecutionTime = firstExecutionTime;
        _lastExecutionTime = lastExecutionTime;
        _countExecutions = countExecutions;
        _avgDuration = avgDuration;
        _lastDuration = lastDuration;
        _minDuration = minDuration;
        _maxDuration = maxDuration;
        _stdevDuration = stdevDuration;
        _avgCpuTime = avgCpuTime;
        _lastCpuTime = lastCpuTime;
        _minCpuTime = minCpuTime;
        _maxCpuTime = maxCpuTime;
        _stdevCpuTime = stdevCpuTime;
        _avgLogicalIoReads = avgLogicalIoReads;
        _lastLogicalIoReads = lastLogicalIoReads;
        _minLogicalIoReads = minLogicalIoReads;
        _maxLogicalIoReads = maxLogicalIoReads;
        _stdevLogicalIoReads = stdevLogicalIoReads;
        _avgLogicalIoWrites = avgLogicalIoWrites;
        _lastLogicalIoWrites = lastLogicalIoWrites;
        _minLogicalIoWrites = minLogicalIoWrites;
        _maxLogicalIoWrites = maxLogicalIoWrites;
        _stdevLogicalIoWrites = stdevLogicalIoWrites;
        _avgPhysicalIoReads = avgPhysicalIoReads;
        _lastPhysicalIoReads = lastPhysicalIoReads;
        _minPhysicalIoReads = minPhysicalIoReads;
        _maxPhysicalIoReads = maxPhysicalIoReads;
        _stdevPhysicalIoReads = stdevPhysicalIoReads;
        _avgClrTime = avgClrTime;
        _lastClrTime = lastClrTime;
        _minClrTime = minClrTime;
        _maxClrTime = maxClrTime;
        _stdevClrTime = stdevClrTime;
        _avgDop = avgDop;
        _lastDop = lastDop;
        _minDop = minDop;
        _maxDop = maxDop;
        _stdevDop = stdevDop;
        _avgQueryMaxUsedMemory = avgQueryMaxUsedMemory;
        _lastQueryMaxUsedMemory = lastQueryMaxUsedMemory;
        _minQueryMaxUsedMemory = minQueryMaxUsedMemory;
        _maxQueryMaxUsedMemory = maxQueryMaxUsedMemory;
        _stdevQueryMaxUsedMemory = stdevQueryMaxUsedMemory;
        _avgRowcount = avgRowcount;
        _lastRowcount = lastRowcount;
        _minRowcount = minRowcount;
        _maxRowcount = maxRowcount;
        _stdevRowcount = stdevRowcount;
        _avgNumPhysicalIoReads = avgNumPhysicalIoReads;
        _lastNumPhysicalIoReads = lastNumPhysicalIoReads;
        _minNumPhysicalIoReads = minNumPhysicalIoReads;
        _maxNumPhysicalIoReads = maxNumPhysicalIoReads;
        _stdevNumPhysicalIoReads = stdevNumPhysicalIoReads;
        _avgLogBytesUsed = avgLogBytesUsed;
        _lastLogBytesUsed = lastLogBytesUsed;
        _minLogBytesUsed = minLogBytesUsed;
        _maxLogBytesUsed = maxLogBytesUsed;
        _stdevLogBytesUsed = stdevLogBytesUsed;
        _avgTempdbSpaceUsed = avgTempdbSpaceUsed;
        _lastTempdbSpaceUsed = lastTempdbSpaceUsed;
        _minTempdbSpaceUsed = minTempdbSpaceUsed;
        _maxTempdbSpaceUsed = maxTempdbSpaceUsed;
        _stdevTempdbSpaceUsed = stdevTempdbSpaceUsed;
    }

    public long RuntimeStatsId => _runtimeStatsId;
    public long PlanId => _planId;
    public long RuntimeStatsIntervalId => _runtimeStatsIntervalId;
    public byte ExecutionType => _executionType;
    public string? ExecutionTypeDesc => _executionTypeDesc;
    public DateTime FirstExecutionTime => _firstExecutionTime;
    public DateTime LastExecutionTime => _lastExecutionTime;
    public long CountExecutions => _countExecutions;
    public double? AvgDuration => _avgDuration;
    public long LastDuration => _lastDuration;
    public long MinDuration => _minDuration;
    public long MaxDuration => _maxDuration;
    public double? StdevDuration => _stdevDuration;
    public double? AvgCpuTime => _avgCpuTime;
    public long LastCpuTime => _lastCpuTime;
    public long MinCpuTime => _minCpuTime;
    public long MaxCpuTime => _maxCpuTime;
    public double? StdevCpuTime => _stdevCpuTime;
    public double? AvgLogicalIoReads => _avgLogicalIoReads;
    public long LastLogicalIoReads => _lastLogicalIoReads;
    public long MinLogicalIoReads => _minLogicalIoReads;
    public long MaxLogicalIoReads => _maxLogicalIoReads;
    public double? StdevLogicalIoReads => _stdevLogicalIoReads;
    public double? AvgLogicalIoWrites => _avgLogicalIoWrites;
    public long LastLogicalIoWrites => _lastLogicalIoWrites;
    public long MinLogicalIoWrites => _minLogicalIoWrites;
    public long MaxLogicalIoWrites => _maxLogicalIoWrites;
    public double? StdevLogicalIoWrites => _stdevLogicalIoWrites;
    public double? AvgPhysicalIoReads => _avgPhysicalIoReads;
    public long LastPhysicalIoReads => _lastPhysicalIoReads;
    public long MinPhysicalIoReads => _minPhysicalIoReads;
    public long MaxPhysicalIoReads => _maxPhysicalIoReads;
    public double? StdevPhysicalIoReads => _stdevPhysicalIoReads;
    public double? AvgClrTime => _avgClrTime;
    public long LastClrTime => _lastClrTime;
    public long MinClrTime => _minClrTime;
    public long MaxClrTime => _maxClrTime;
    public double? StdevClrTime => _stdevClrTime;
    public double? AvgDop => _avgDop;
    public long LastDop => _lastDop;
    public long MinDop => _minDop;
    public long MaxDop => _maxDop;
    public double? StdevDop => _stdevDop;
    public double? AvgQueryMaxUsedMemory => _avgQueryMaxUsedMemory;
    public long LastQueryMaxUsedMemory => _lastQueryMaxUsedMemory;
    public long MinQueryMaxUsedMemory => _minQueryMaxUsedMemory;
    public long MaxQueryMaxUsedMemory => _maxQueryMaxUsedMemory;
    public double? StdevQueryMaxUsedMemory => _stdevQueryMaxUsedMemory;
    public double? AvgRowcount => _avgRowcount;
    public long LastRowcount => _lastRowcount;
    public long MinRowcount => _minRowcount;
    public long MaxRowcount => _maxRowcount;
    public double? StdevRowcount => _stdevRowcount;
    public double? AvgNumPhysicalIoReads => _avgNumPhysicalIoReads;
    public long? LastNumPhysicalIoReads => _lastNumPhysicalIoReads;
    public long? MinNumPhysicalIoReads => _minNumPhysicalIoReads;
    public long? MaxNumPhysicalIoReads => _maxNumPhysicalIoReads;
    public double? StdevNumPhysicalIoReads => _stdevNumPhysicalIoReads;
    public double? AvgLogBytesUsed => _avgLogBytesUsed;
    public long? LastLogBytesUsed => _lastLogBytesUsed;
    public long? MinLogBytesUsed => _minLogBytesUsed;
    public long? MaxLogBytesUsed => _maxLogBytesUsed;
    public double? StdevLogBytesUsed => _stdevLogBytesUsed;
    public double? AvgTempdbSpaceUsed => _avgTempdbSpaceUsed;
    public long? LastTempdbSpaceUsed => _lastTempdbSpaceUsed;
    public long? MinTempdbSpaceUsed => _minTempdbSpaceUsed;
    public long? MaxTempdbSpaceUsed => _maxTempdbSpaceUsed;
    public double? StdevTempdbSpaceUsed => _stdevTempdbSpaceUsed;
}
