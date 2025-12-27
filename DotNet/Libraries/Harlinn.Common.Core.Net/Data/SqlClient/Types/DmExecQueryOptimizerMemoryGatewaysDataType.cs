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

public class DmExecQueryOptimizerMemoryGatewaysDataType
{
    readonly int _poolId = 0;
    readonly string _name = string.Empty;
    readonly int _maxCount = 0;
    readonly int _activeCount = 0;
    readonly int _waiterCount = 0;
    readonly long _thresholdFactor = 0;
    readonly long _threshold = 0;
    readonly bool _isActive = false;

    public DmExecQueryOptimizerMemoryGatewaysDataType( )
    {
    }

    public DmExecQueryOptimizerMemoryGatewaysDataType(int poolId,
        string name,
        int maxCount,
        int activeCount,
        int waiterCount,
        long thresholdFactor,
        long threshold,
        bool isActive)
    {
        _poolId = poolId;
        _name = name;
        _maxCount = maxCount;
        _activeCount = activeCount;
        _waiterCount = waiterCount;
        _thresholdFactor = thresholdFactor;
        _threshold = threshold;
        _isActive = isActive;
    }

    public int PoolId => _poolId;
    public string Name => _name;
    public int MaxCount => _maxCount;
    public int ActiveCount => _activeCount;
    public int WaiterCount => _waiterCount;
    public long ThresholdFactor => _thresholdFactor;
    public long Threshold => _threshold;
    public bool IsActive => _isActive;
}
