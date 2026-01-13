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

public class DmOsMemoryBrokersDataType
{
    readonly int _poolId = 0;
    readonly string _memoryBrokerType = string.Empty;
    readonly long _allocationsKb = 0;
    readonly long _allocationsKbPerSec = 0;
    readonly long _predictedAllocationsKb = 0;
    readonly long _targetAllocationsKb = 0;
    readonly long _futureAllocationsKb = 0;
    readonly long _overallLimitKb = 0;
    readonly string _lastNotification = string.Empty;

    public DmOsMemoryBrokersDataType( )
    {
    }

    public DmOsMemoryBrokersDataType(int poolId,
        string memoryBrokerType,
        long allocationsKb,
        long allocationsKbPerSec,
        long predictedAllocationsKb,
        long targetAllocationsKb,
        long futureAllocationsKb,
        long overallLimitKb,
        string lastNotification)
    {
        _poolId = poolId;
        _memoryBrokerType = memoryBrokerType;
        _allocationsKb = allocationsKb;
        _allocationsKbPerSec = allocationsKbPerSec;
        _predictedAllocationsKb = predictedAllocationsKb;
        _targetAllocationsKb = targetAllocationsKb;
        _futureAllocationsKb = futureAllocationsKb;
        _overallLimitKb = overallLimitKb;
        _lastNotification = lastNotification;
    }

    public int PoolId => _poolId;
    public string MemoryBrokerType => _memoryBrokerType;
    public long AllocationsKb => _allocationsKb;
    public long AllocationsKbPerSec => _allocationsKbPerSec;
    public long PredictedAllocationsKb => _predictedAllocationsKb;
    public long TargetAllocationsKb => _targetAllocationsKb;
    public long FutureAllocationsKb => _futureAllocationsKb;
    public long OverallLimitKb => _overallLimitKb;
    public string LastNotification => _lastNotification;
}
