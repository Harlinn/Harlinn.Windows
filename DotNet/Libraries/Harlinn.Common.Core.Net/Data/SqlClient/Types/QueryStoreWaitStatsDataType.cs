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

public class QueryStoreWaitStatsDataType
{
    readonly long _waitStatsId = 0;
    readonly long _planId = 0;
    readonly long _runtimeStatsIntervalId = 0;
    readonly short _waitCategory = 0;
    readonly string? _waitCategoryDesc;
    readonly byte _executionType = 0;
    readonly string? _executionTypeDesc;
    readonly long _totalQueryWaitTimeMs = 0;
    readonly double? _avgQueryWaitTimeMs;
    readonly long _lastQueryWaitTimeMs = 0;
    readonly long _minQueryWaitTimeMs = 0;
    readonly long _maxQueryWaitTimeMs = 0;
    readonly double? _stdevQueryWaitTimeMs;

    public QueryStoreWaitStatsDataType( )
    {
    }

    public QueryStoreWaitStatsDataType(long waitStatsId,
        long planId,
        long runtimeStatsIntervalId,
        short waitCategory,
        string? waitCategoryDesc,
        byte executionType,
        string? executionTypeDesc,
        long totalQueryWaitTimeMs,
        double? avgQueryWaitTimeMs,
        long lastQueryWaitTimeMs,
        long minQueryWaitTimeMs,
        long maxQueryWaitTimeMs,
        double? stdevQueryWaitTimeMs)
    {
        _waitStatsId = waitStatsId;
        _planId = planId;
        _runtimeStatsIntervalId = runtimeStatsIntervalId;
        _waitCategory = waitCategory;
        _waitCategoryDesc = waitCategoryDesc;
        _executionType = executionType;
        _executionTypeDesc = executionTypeDesc;
        _totalQueryWaitTimeMs = totalQueryWaitTimeMs;
        _avgQueryWaitTimeMs = avgQueryWaitTimeMs;
        _lastQueryWaitTimeMs = lastQueryWaitTimeMs;
        _minQueryWaitTimeMs = minQueryWaitTimeMs;
        _maxQueryWaitTimeMs = maxQueryWaitTimeMs;
        _stdevQueryWaitTimeMs = stdevQueryWaitTimeMs;
    }

    public long WaitStatsId => _waitStatsId;
    public long PlanId => _planId;
    public long RuntimeStatsIntervalId => _runtimeStatsIntervalId;
    public short WaitCategory => _waitCategory;
    public string? WaitCategoryDesc => _waitCategoryDesc;
    public byte ExecutionType => _executionType;
    public string? ExecutionTypeDesc => _executionTypeDesc;
    public long TotalQueryWaitTimeMs => _totalQueryWaitTimeMs;
    public double? AvgQueryWaitTimeMs => _avgQueryWaitTimeMs;
    public long LastQueryWaitTimeMs => _lastQueryWaitTimeMs;
    public long MinQueryWaitTimeMs => _minQueryWaitTimeMs;
    public long MaxQueryWaitTimeMs => _maxQueryWaitTimeMs;
    public double? StdevQueryWaitTimeMs => _stdevQueryWaitTimeMs;
}
