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

public class DmResourceGovernorResourcePoolsDataType
{
    readonly int _poolId = 0;
    readonly string _name = string.Empty;
    readonly DateTime _statisticsStartTime;
    readonly long _totalCpuUsageMs = 0;
    readonly long _cacheMemoryKb = 0;
    readonly long _compileMemoryKb = 0;
    readonly long _usedMemgrantKb = 0;
    readonly long _totalMemgrantCount = 0;
    readonly long _totalMemgrantTimeoutCount = 0;
    readonly int _activeMemgrantCount = 0;
    readonly long _activeMemgrantKb = 0;
    readonly int _memgrantWaiterCount = 0;
    readonly long _maxMemoryKb = 0;
    readonly long _usedMemoryKb = 0;
    readonly long _targetMemoryKb = 0;
    readonly long _outOfMemoryCount = 0;
    readonly int _minCpuPercent = 0;
    readonly int _maxCpuPercent = 0;
    readonly int _minMemoryPercent = 0;
    readonly int _maxMemoryPercent = 0;
    readonly int _capCpuPercent = 0;
    readonly int? _minIopsPerVolume;
    readonly int? _maxIopsPerVolume;
    readonly int? _readIoQueuedTotal;
    readonly int? _readIoIssuedTotal;
    readonly int _readIoCompletedTotal = 0;
    readonly int? _readIoThrottledTotal;
    readonly long _readBytesTotal = 0;
    readonly long _readIoStallTotalMs = 0;
    readonly long? _readIoStallQueuedMs;
    readonly int? _writeIoQueuedTotal;
    readonly int? _writeIoIssuedTotal;
    readonly int _writeIoCompletedTotal = 0;
    readonly int? _writeIoThrottledTotal;
    readonly long _writeBytesTotal = 0;
    readonly long _writeIoStallTotalMs = 0;
    readonly long? _writeIoStallQueuedMs;
    readonly int? _ioIssueViolationsTotal;
    readonly long? _ioIssueDelayTotalMs;
    readonly long? _ioIssueAheadTotalMs;
    readonly int? _reservedIoLimitedByVolumeTotal;
    readonly long? _ioIssueDelayNonThrottledTotalMs;
    readonly long _totalCpuDelayedMs = 0;
    readonly long _totalCpuActiveMs = 0;
    readonly long _totalCpuViolationDelayMs = 0;
    readonly long _totalCpuViolationSec = 0;
    readonly long _totalCpuUsagePreemptiveMs = 0;

    public DmResourceGovernorResourcePoolsDataType( )
    {
    }

    public DmResourceGovernorResourcePoolsDataType(int poolId,
        string name,
        DateTime statisticsStartTime,
        long totalCpuUsageMs,
        long cacheMemoryKb,
        long compileMemoryKb,
        long usedMemgrantKb,
        long totalMemgrantCount,
        long totalMemgrantTimeoutCount,
        int activeMemgrantCount,
        long activeMemgrantKb,
        int memgrantWaiterCount,
        long maxMemoryKb,
        long usedMemoryKb,
        long targetMemoryKb,
        long outOfMemoryCount,
        int minCpuPercent,
        int maxCpuPercent,
        int minMemoryPercent,
        int maxMemoryPercent,
        int capCpuPercent,
        int? minIopsPerVolume,
        int? maxIopsPerVolume,
        int? readIoQueuedTotal,
        int? readIoIssuedTotal,
        int readIoCompletedTotal,
        int? readIoThrottledTotal,
        long readBytesTotal,
        long readIoStallTotalMs,
        long? readIoStallQueuedMs,
        int? writeIoQueuedTotal,
        int? writeIoIssuedTotal,
        int writeIoCompletedTotal,
        int? writeIoThrottledTotal,
        long writeBytesTotal,
        long writeIoStallTotalMs,
        long? writeIoStallQueuedMs,
        int? ioIssueViolationsTotal,
        long? ioIssueDelayTotalMs,
        long? ioIssueAheadTotalMs,
        int? reservedIoLimitedByVolumeTotal,
        long? ioIssueDelayNonThrottledTotalMs,
        long totalCpuDelayedMs,
        long totalCpuActiveMs,
        long totalCpuViolationDelayMs,
        long totalCpuViolationSec,
        long totalCpuUsagePreemptiveMs)
    {
        _poolId = poolId;
        _name = name;
        _statisticsStartTime = statisticsStartTime;
        _totalCpuUsageMs = totalCpuUsageMs;
        _cacheMemoryKb = cacheMemoryKb;
        _compileMemoryKb = compileMemoryKb;
        _usedMemgrantKb = usedMemgrantKb;
        _totalMemgrantCount = totalMemgrantCount;
        _totalMemgrantTimeoutCount = totalMemgrantTimeoutCount;
        _activeMemgrantCount = activeMemgrantCount;
        _activeMemgrantKb = activeMemgrantKb;
        _memgrantWaiterCount = memgrantWaiterCount;
        _maxMemoryKb = maxMemoryKb;
        _usedMemoryKb = usedMemoryKb;
        _targetMemoryKb = targetMemoryKb;
        _outOfMemoryCount = outOfMemoryCount;
        _minCpuPercent = minCpuPercent;
        _maxCpuPercent = maxCpuPercent;
        _minMemoryPercent = minMemoryPercent;
        _maxMemoryPercent = maxMemoryPercent;
        _capCpuPercent = capCpuPercent;
        _minIopsPerVolume = minIopsPerVolume;
        _maxIopsPerVolume = maxIopsPerVolume;
        _readIoQueuedTotal = readIoQueuedTotal;
        _readIoIssuedTotal = readIoIssuedTotal;
        _readIoCompletedTotal = readIoCompletedTotal;
        _readIoThrottledTotal = readIoThrottledTotal;
        _readBytesTotal = readBytesTotal;
        _readIoStallTotalMs = readIoStallTotalMs;
        _readIoStallQueuedMs = readIoStallQueuedMs;
        _writeIoQueuedTotal = writeIoQueuedTotal;
        _writeIoIssuedTotal = writeIoIssuedTotal;
        _writeIoCompletedTotal = writeIoCompletedTotal;
        _writeIoThrottledTotal = writeIoThrottledTotal;
        _writeBytesTotal = writeBytesTotal;
        _writeIoStallTotalMs = writeIoStallTotalMs;
        _writeIoStallQueuedMs = writeIoStallQueuedMs;
        _ioIssueViolationsTotal = ioIssueViolationsTotal;
        _ioIssueDelayTotalMs = ioIssueDelayTotalMs;
        _ioIssueAheadTotalMs = ioIssueAheadTotalMs;
        _reservedIoLimitedByVolumeTotal = reservedIoLimitedByVolumeTotal;
        _ioIssueDelayNonThrottledTotalMs = ioIssueDelayNonThrottledTotalMs;
        _totalCpuDelayedMs = totalCpuDelayedMs;
        _totalCpuActiveMs = totalCpuActiveMs;
        _totalCpuViolationDelayMs = totalCpuViolationDelayMs;
        _totalCpuViolationSec = totalCpuViolationSec;
        _totalCpuUsagePreemptiveMs = totalCpuUsagePreemptiveMs;
    }

    public int PoolId => _poolId;
    public string Name => _name;
    public DateTime StatisticsStartTime => _statisticsStartTime;
    public long TotalCpuUsageMs => _totalCpuUsageMs;
    public long CacheMemoryKb => _cacheMemoryKb;
    public long CompileMemoryKb => _compileMemoryKb;
    public long UsedMemgrantKb => _usedMemgrantKb;
    public long TotalMemgrantCount => _totalMemgrantCount;
    public long TotalMemgrantTimeoutCount => _totalMemgrantTimeoutCount;
    public int ActiveMemgrantCount => _activeMemgrantCount;
    public long ActiveMemgrantKb => _activeMemgrantKb;
    public int MemgrantWaiterCount => _memgrantWaiterCount;
    public long MaxMemoryKb => _maxMemoryKb;
    public long UsedMemoryKb => _usedMemoryKb;
    public long TargetMemoryKb => _targetMemoryKb;
    public long OutOfMemoryCount => _outOfMemoryCount;
    public int MinCpuPercent => _minCpuPercent;
    public int MaxCpuPercent => _maxCpuPercent;
    public int MinMemoryPercent => _minMemoryPercent;
    public int MaxMemoryPercent => _maxMemoryPercent;
    public int CapCpuPercent => _capCpuPercent;
    public int? MinIopsPerVolume => _minIopsPerVolume;
    public int? MaxIopsPerVolume => _maxIopsPerVolume;
    public int? ReadIoQueuedTotal => _readIoQueuedTotal;
    public int? ReadIoIssuedTotal => _readIoIssuedTotal;
    public int ReadIoCompletedTotal => _readIoCompletedTotal;
    public int? ReadIoThrottledTotal => _readIoThrottledTotal;
    public long ReadBytesTotal => _readBytesTotal;
    public long ReadIoStallTotalMs => _readIoStallTotalMs;
    public long? ReadIoStallQueuedMs => _readIoStallQueuedMs;
    public int? WriteIoQueuedTotal => _writeIoQueuedTotal;
    public int? WriteIoIssuedTotal => _writeIoIssuedTotal;
    public int WriteIoCompletedTotal => _writeIoCompletedTotal;
    public int? WriteIoThrottledTotal => _writeIoThrottledTotal;
    public long WriteBytesTotal => _writeBytesTotal;
    public long WriteIoStallTotalMs => _writeIoStallTotalMs;
    public long? WriteIoStallQueuedMs => _writeIoStallQueuedMs;
    public int? IoIssueViolationsTotal => _ioIssueViolationsTotal;
    public long? IoIssueDelayTotalMs => _ioIssueDelayTotalMs;
    public long? IoIssueAheadTotalMs => _ioIssueAheadTotalMs;
    public int? ReservedIoLimitedByVolumeTotal => _reservedIoLimitedByVolumeTotal;
    public long? IoIssueDelayNonThrottledTotalMs => _ioIssueDelayNonThrottledTotalMs;
    public long TotalCpuDelayedMs => _totalCpuDelayedMs;
    public long TotalCpuActiveMs => _totalCpuActiveMs;
    public long TotalCpuViolationDelayMs => _totalCpuViolationDelayMs;
    public long TotalCpuViolationSec => _totalCpuViolationSec;
    public long TotalCpuUsagePreemptiveMs => _totalCpuUsagePreemptiveMs;
}
