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

public class DmExecQueryMemoryGrantsDataType
{
    readonly short? _sessionId;
    readonly int? _requestId;
    readonly int? _schedulerId;
    readonly short? _dop;
    readonly DateTime? _requestTime;
    readonly DateTime? _grantTime;
    readonly long? _requestedMemoryKb;
    readonly long? _grantedMemoryKb;
    readonly long? _requiredMemoryKb;
    readonly long? _usedMemoryKb;
    readonly long? _maxUsedMemoryKb;
    readonly double? _queryCost;
    readonly int? _timeoutSec;
    readonly short? _resourceSemaphoreId;
    readonly short? _queueId;
    readonly int? _waitOrder;
    readonly bool? _isNextCandidate;
    readonly long? _waitTimeMs;
    readonly byte[]? _planHandle;
    readonly byte[]? _sqlHandle;
    readonly int? _groupId;
    readonly int? _poolId;
    readonly bool? _isSmall;
    readonly long? _idealMemoryKb;
    readonly int? _reservedWorkerCount;
    readonly int? _usedWorkerCount;
    readonly int? _maxUsedWorkerCount;
    readonly long? _reservedNodeBitmap;

    public DmExecQueryMemoryGrantsDataType( )
    {
    }

    public DmExecQueryMemoryGrantsDataType(short? sessionId,
        int? requestId,
        int? schedulerId,
        short? dop,
        DateTime? requestTime,
        DateTime? grantTime,
        long? requestedMemoryKb,
        long? grantedMemoryKb,
        long? requiredMemoryKb,
        long? usedMemoryKb,
        long? maxUsedMemoryKb,
        double? queryCost,
        int? timeoutSec,
        short? resourceSemaphoreId,
        short? queueId,
        int? waitOrder,
        bool? isNextCandidate,
        long? waitTimeMs,
        byte[]? planHandle,
        byte[]? sqlHandle,
        int? groupId,
        int? poolId,
        bool? isSmall,
        long? idealMemoryKb,
        int? reservedWorkerCount,
        int? usedWorkerCount,
        int? maxUsedWorkerCount,
        long? reservedNodeBitmap)
    {
        _sessionId = sessionId;
        _requestId = requestId;
        _schedulerId = schedulerId;
        _dop = dop;
        _requestTime = requestTime;
        _grantTime = grantTime;
        _requestedMemoryKb = requestedMemoryKb;
        _grantedMemoryKb = grantedMemoryKb;
        _requiredMemoryKb = requiredMemoryKb;
        _usedMemoryKb = usedMemoryKb;
        _maxUsedMemoryKb = maxUsedMemoryKb;
        _queryCost = queryCost;
        _timeoutSec = timeoutSec;
        _resourceSemaphoreId = resourceSemaphoreId;
        _queueId = queueId;
        _waitOrder = waitOrder;
        _isNextCandidate = isNextCandidate;
        _waitTimeMs = waitTimeMs;
        _planHandle = planHandle;
        _sqlHandle = sqlHandle;
        _groupId = groupId;
        _poolId = poolId;
        _isSmall = isSmall;
        _idealMemoryKb = idealMemoryKb;
        _reservedWorkerCount = reservedWorkerCount;
        _usedWorkerCount = usedWorkerCount;
        _maxUsedWorkerCount = maxUsedWorkerCount;
        _reservedNodeBitmap = reservedNodeBitmap;
    }

    public short? SessionId => _sessionId;
    public int? RequestId => _requestId;
    public int? SchedulerId => _schedulerId;
    public short? Dop => _dop;
    public DateTime? RequestTime => _requestTime;
    public DateTime? GrantTime => _grantTime;
    public long? RequestedMemoryKb => _requestedMemoryKb;
    public long? GrantedMemoryKb => _grantedMemoryKb;
    public long? RequiredMemoryKb => _requiredMemoryKb;
    public long? UsedMemoryKb => _usedMemoryKb;
    public long? MaxUsedMemoryKb => _maxUsedMemoryKb;
    public double? QueryCost => _queryCost;
    public int? TimeoutSec => _timeoutSec;
    public short? ResourceSemaphoreId => _resourceSemaphoreId;
    public short? QueueId => _queueId;
    public int? WaitOrder => _waitOrder;
    public bool? IsNextCandidate => _isNextCandidate;
    public long? WaitTimeMs => _waitTimeMs;
    public byte[]? PlanHandle => _planHandle;
    public byte[]? SqlHandle => _sqlHandle;
    public int? GroupId => _groupId;
    public int? PoolId => _poolId;
    public bool? IsSmall => _isSmall;
    public long? IdealMemoryKb => _idealMemoryKb;
    public int? ReservedWorkerCount => _reservedWorkerCount;
    public int? UsedWorkerCount => _usedWorkerCount;
    public int? MaxUsedWorkerCount => _maxUsedWorkerCount;
    public long? ReservedNodeBitmap => _reservedNodeBitmap;
}
