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

public class QueryStorePlanDataType
{
    readonly long _planId = 0;
    readonly long _queryId = 0;
    readonly long? _planGroupId;
    readonly string? _engineVersion;
    readonly short _compatibilityLevel = 0;
    readonly byte[] _queryPlanHash = Array.Empty<byte>();
    readonly string? _queryPlan;
    readonly bool _isOnlineIndexPlan = false;
    readonly bool _isTrivialPlan = false;
    readonly bool _isParallelPlan = false;
    readonly bool _isForcedPlan = false;
    readonly bool _isNativelyCompiled = false;
    readonly long _forceFailureCount = 0;
    readonly int _lastForceFailureReason = 0;
    readonly string? _lastForceFailureReasonDesc;
    readonly long? _countCompiles;
    readonly DateTime _initialCompileStartTime;
    readonly DateTime? _lastCompileStartTime;
    readonly DateTime? _lastExecutionTime;
    readonly double? _avgCompileDuration;
    readonly long? _lastCompileDuration;
    readonly int _planForcingType = 0;
    readonly string? _planForcingTypeDesc;

    public QueryStorePlanDataType( )
    {
    }

    public QueryStorePlanDataType(long planId,
        long queryId,
        long? planGroupId,
        string? engineVersion,
        short compatibilityLevel,
        byte[] queryPlanHash,
        string? queryPlan,
        bool isOnlineIndexPlan,
        bool isTrivialPlan,
        bool isParallelPlan,
        bool isForcedPlan,
        bool isNativelyCompiled,
        long forceFailureCount,
        int lastForceFailureReason,
        string? lastForceFailureReasonDesc,
        long? countCompiles,
        DateTime initialCompileStartTime,
        DateTime? lastCompileStartTime,
        DateTime? lastExecutionTime,
        double? avgCompileDuration,
        long? lastCompileDuration,
        int planForcingType,
        string? planForcingTypeDesc)
    {
        _planId = planId;
        _queryId = queryId;
        _planGroupId = planGroupId;
        _engineVersion = engineVersion;
        _compatibilityLevel = compatibilityLevel;
        _queryPlanHash = queryPlanHash;
        _queryPlan = queryPlan;
        _isOnlineIndexPlan = isOnlineIndexPlan;
        _isTrivialPlan = isTrivialPlan;
        _isParallelPlan = isParallelPlan;
        _isForcedPlan = isForcedPlan;
        _isNativelyCompiled = isNativelyCompiled;
        _forceFailureCount = forceFailureCount;
        _lastForceFailureReason = lastForceFailureReason;
        _lastForceFailureReasonDesc = lastForceFailureReasonDesc;
        _countCompiles = countCompiles;
        _initialCompileStartTime = initialCompileStartTime;
        _lastCompileStartTime = lastCompileStartTime;
        _lastExecutionTime = lastExecutionTime;
        _avgCompileDuration = avgCompileDuration;
        _lastCompileDuration = lastCompileDuration;
        _planForcingType = planForcingType;
        _planForcingTypeDesc = planForcingTypeDesc;
    }

    public long PlanId => _planId;
    public long QueryId => _queryId;
    public long? PlanGroupId => _planGroupId;
    public string? EngineVersion => _engineVersion;
    public short CompatibilityLevel => _compatibilityLevel;
    public byte[] QueryPlanHash => _queryPlanHash;
    public string? QueryPlan => _queryPlan;
    public bool IsOnlineIndexPlan => _isOnlineIndexPlan;
    public bool IsTrivialPlan => _isTrivialPlan;
    public bool IsParallelPlan => _isParallelPlan;
    public bool IsForcedPlan => _isForcedPlan;
    public bool IsNativelyCompiled => _isNativelyCompiled;
    public long ForceFailureCount => _forceFailureCount;
    public int LastForceFailureReason => _lastForceFailureReason;
    public string? LastForceFailureReasonDesc => _lastForceFailureReasonDesc;
    public long? CountCompiles => _countCompiles;
    public DateTime InitialCompileStartTime => _initialCompileStartTime;
    public DateTime? LastCompileStartTime => _lastCompileStartTime;
    public DateTime? LastExecutionTime => _lastExecutionTime;
    public double? AvgCompileDuration => _avgCompileDuration;
    public long? LastCompileDuration => _lastCompileDuration;
    public int PlanForcingType => _planForcingType;
    public string? PlanForcingTypeDesc => _planForcingTypeDesc;
}
