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

public class DmExecQueryResourceSemaphoresDataType
{
    readonly short? _resourceSemaphoreId;
    readonly long? _targetMemoryKb;
    readonly long? _maxTargetMemoryKb;
    readonly long? _totalMemoryKb;
    readonly long? _availableMemoryKb;
    readonly long? _grantedMemoryKb;
    readonly long? _usedMemoryKb;
    readonly int? _granteeCount;
    readonly int? _waiterCount;
    readonly long? _timeoutErrorCount;
    readonly long? _forcedGrantCount;
    readonly int? _poolId;

    public DmExecQueryResourceSemaphoresDataType( )
    {
    }

    public DmExecQueryResourceSemaphoresDataType(short? resourceSemaphoreId,
        long? targetMemoryKb,
        long? maxTargetMemoryKb,
        long? totalMemoryKb,
        long? availableMemoryKb,
        long? grantedMemoryKb,
        long? usedMemoryKb,
        int? granteeCount,
        int? waiterCount,
        long? timeoutErrorCount,
        long? forcedGrantCount,
        int? poolId)
    {
        _resourceSemaphoreId = resourceSemaphoreId;
        _targetMemoryKb = targetMemoryKb;
        _maxTargetMemoryKb = maxTargetMemoryKb;
        _totalMemoryKb = totalMemoryKb;
        _availableMemoryKb = availableMemoryKb;
        _grantedMemoryKb = grantedMemoryKb;
        _usedMemoryKb = usedMemoryKb;
        _granteeCount = granteeCount;
        _waiterCount = waiterCount;
        _timeoutErrorCount = timeoutErrorCount;
        _forcedGrantCount = forcedGrantCount;
        _poolId = poolId;
    }

    public short? ResourceSemaphoreId => _resourceSemaphoreId;
    public long? TargetMemoryKb => _targetMemoryKb;
    public long? MaxTargetMemoryKb => _maxTargetMemoryKb;
    public long? TotalMemoryKb => _totalMemoryKb;
    public long? AvailableMemoryKb => _availableMemoryKb;
    public long? GrantedMemoryKb => _grantedMemoryKb;
    public long? UsedMemoryKb => _usedMemoryKb;
    public int? GranteeCount => _granteeCount;
    public int? WaiterCount => _waiterCount;
    public long? TimeoutErrorCount => _timeoutErrorCount;
    public long? ForcedGrantCount => _forcedGrantCount;
    public int? PoolId => _poolId;
}
