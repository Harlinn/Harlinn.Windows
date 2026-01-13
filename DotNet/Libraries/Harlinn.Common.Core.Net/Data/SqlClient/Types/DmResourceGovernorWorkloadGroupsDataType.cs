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

public class DmResourceGovernorWorkloadGroupsDataType
{
    readonly int _groupId = 0;
    readonly string _name = string.Empty;
    readonly int _poolId = 0;
    readonly int? _externalPoolId;
    readonly DateTime _statisticsStartTime;
    readonly long _totalRequestCount = 0;
    readonly long _totalQueuedRequestCount = 0;
    readonly int _activeRequestCount = 0;
    readonly int _queuedRequestCount = 0;
    readonly long _totalCpuLimitViolationCount = 0;
    readonly long _totalCpuUsageMs = 0;
    readonly long _maxRequestCpuTimeMs = 0;
    readonly int _blockedTaskCount = 0;
    readonly long _totalLockWaitCount = 0;
    readonly long _totalLockWaitTimeMs = 0;
    readonly long _totalQueryOptimizationCount = 0;
    readonly long _totalSuboptimalPlanGenerationCount = 0;
    readonly long _totalReducedMemgrantCount = 0;
    readonly long _maxRequestGrantMemoryKb = 0;
    readonly long _activeParallelThreadCount = 0;
    readonly string _importance = string.Empty;
    readonly int _requestMaxMemoryGrantPercent = 0;
    readonly int _requestMaxCpuTimeSec = 0;
    readonly int _requestMemoryGrantTimeoutSec = 0;
    readonly int _groupMaxRequests = 0;
    readonly int _maxDop = 0;
    readonly int _effectiveMaxDop = 0;
    readonly long _totalCpuUsagePreemptiveMs = 0;
    readonly double _requestMaxMemoryGrantPercentNumeric = 0.0;

    public DmResourceGovernorWorkloadGroupsDataType( )
    {
    }

    public DmResourceGovernorWorkloadGroupsDataType(int groupId,
        string name,
        int poolId,
        int? externalPoolId,
        DateTime statisticsStartTime,
        long totalRequestCount,
        long totalQueuedRequestCount,
        int activeRequestCount,
        int queuedRequestCount,
        long totalCpuLimitViolationCount,
        long totalCpuUsageMs,
        long maxRequestCpuTimeMs,
        int blockedTaskCount,
        long totalLockWaitCount,
        long totalLockWaitTimeMs,
        long totalQueryOptimizationCount,
        long totalSuboptimalPlanGenerationCount,
        long totalReducedMemgrantCount,
        long maxRequestGrantMemoryKb,
        long activeParallelThreadCount,
        string importance,
        int requestMaxMemoryGrantPercent,
        int requestMaxCpuTimeSec,
        int requestMemoryGrantTimeoutSec,
        int groupMaxRequests,
        int maxDop,
        int effectiveMaxDop,
        long totalCpuUsagePreemptiveMs,
        double requestMaxMemoryGrantPercentNumeric)
    {
        _groupId = groupId;
        _name = name;
        _poolId = poolId;
        _externalPoolId = externalPoolId;
        _statisticsStartTime = statisticsStartTime;
        _totalRequestCount = totalRequestCount;
        _totalQueuedRequestCount = totalQueuedRequestCount;
        _activeRequestCount = activeRequestCount;
        _queuedRequestCount = queuedRequestCount;
        _totalCpuLimitViolationCount = totalCpuLimitViolationCount;
        _totalCpuUsageMs = totalCpuUsageMs;
        _maxRequestCpuTimeMs = maxRequestCpuTimeMs;
        _blockedTaskCount = blockedTaskCount;
        _totalLockWaitCount = totalLockWaitCount;
        _totalLockWaitTimeMs = totalLockWaitTimeMs;
        _totalQueryOptimizationCount = totalQueryOptimizationCount;
        _totalSuboptimalPlanGenerationCount = totalSuboptimalPlanGenerationCount;
        _totalReducedMemgrantCount = totalReducedMemgrantCount;
        _maxRequestGrantMemoryKb = maxRequestGrantMemoryKb;
        _activeParallelThreadCount = activeParallelThreadCount;
        _importance = importance;
        _requestMaxMemoryGrantPercent = requestMaxMemoryGrantPercent;
        _requestMaxCpuTimeSec = requestMaxCpuTimeSec;
        _requestMemoryGrantTimeoutSec = requestMemoryGrantTimeoutSec;
        _groupMaxRequests = groupMaxRequests;
        _maxDop = maxDop;
        _effectiveMaxDop = effectiveMaxDop;
        _totalCpuUsagePreemptiveMs = totalCpuUsagePreemptiveMs;
        _requestMaxMemoryGrantPercentNumeric = requestMaxMemoryGrantPercentNumeric;
    }

    public int GroupId => _groupId;
    public string Name => _name;
    public int PoolId => _poolId;
    public int? ExternalPoolId => _externalPoolId;
    public DateTime StatisticsStartTime => _statisticsStartTime;
    public long TotalRequestCount => _totalRequestCount;
    public long TotalQueuedRequestCount => _totalQueuedRequestCount;
    public int ActiveRequestCount => _activeRequestCount;
    public int QueuedRequestCount => _queuedRequestCount;
    public long TotalCpuLimitViolationCount => _totalCpuLimitViolationCount;
    public long TotalCpuUsageMs => _totalCpuUsageMs;
    public long MaxRequestCpuTimeMs => _maxRequestCpuTimeMs;
    public int BlockedTaskCount => _blockedTaskCount;
    public long TotalLockWaitCount => _totalLockWaitCount;
    public long TotalLockWaitTimeMs => _totalLockWaitTimeMs;
    public long TotalQueryOptimizationCount => _totalQueryOptimizationCount;
    public long TotalSuboptimalPlanGenerationCount => _totalSuboptimalPlanGenerationCount;
    public long TotalReducedMemgrantCount => _totalReducedMemgrantCount;
    public long MaxRequestGrantMemoryKb => _maxRequestGrantMemoryKb;
    public long ActiveParallelThreadCount => _activeParallelThreadCount;
    public string Importance => _importance;
    public int RequestMaxMemoryGrantPercent => _requestMaxMemoryGrantPercent;
    public int RequestMaxCpuTimeSec => _requestMaxCpuTimeSec;
    public int RequestMemoryGrantTimeoutSec => _requestMemoryGrantTimeoutSec;
    public int GroupMaxRequests => _groupMaxRequests;
    public int MaxDop => _maxDop;
    public int EffectiveMaxDop => _effectiveMaxDop;
    public long TotalCpuUsagePreemptiveMs => _totalCpuUsagePreemptiveMs;
    public double RequestMaxMemoryGrantPercentNumeric => _requestMaxMemoryGrantPercentNumeric;
}
