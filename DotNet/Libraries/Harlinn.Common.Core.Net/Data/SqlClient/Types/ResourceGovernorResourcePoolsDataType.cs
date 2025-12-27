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

public class ResourceGovernorResourcePoolsDataType
{
    readonly int _poolId = 0;
    readonly string _name = string.Empty;
    readonly int _minCpuPercent = 0;
    readonly int _maxCpuPercent = 0;
    readonly int _minMemoryPercent = 0;
    readonly int _maxMemoryPercent = 0;
    readonly int _capCpuPercent = 0;
    readonly int _minIopsPerVolume = 0;
    readonly int _maxIopsPerVolume = 0;

    public ResourceGovernorResourcePoolsDataType( )
    {
    }

    public ResourceGovernorResourcePoolsDataType(int poolId,
        string name,
        int minCpuPercent,
        int maxCpuPercent,
        int minMemoryPercent,
        int maxMemoryPercent,
        int capCpuPercent,
        int minIopsPerVolume,
        int maxIopsPerVolume)
    {
        _poolId = poolId;
        _name = name;
        _minCpuPercent = minCpuPercent;
        _maxCpuPercent = maxCpuPercent;
        _minMemoryPercent = minMemoryPercent;
        _maxMemoryPercent = maxMemoryPercent;
        _capCpuPercent = capCpuPercent;
        _minIopsPerVolume = minIopsPerVolume;
        _maxIopsPerVolume = maxIopsPerVolume;
    }

    public int PoolId => _poolId;
    public string Name => _name;
    public int MinCpuPercent => _minCpuPercent;
    public int MaxCpuPercent => _maxCpuPercent;
    public int MinMemoryPercent => _minMemoryPercent;
    public int MaxMemoryPercent => _maxMemoryPercent;
    public int CapCpuPercent => _capCpuPercent;
    public int MinIopsPerVolume => _minIopsPerVolume;
    public int MaxIopsPerVolume => _maxIopsPerVolume;
}
