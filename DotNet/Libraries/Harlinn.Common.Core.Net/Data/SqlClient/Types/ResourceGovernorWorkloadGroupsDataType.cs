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

public class ResourceGovernorWorkloadGroupsDataType
{
    readonly int _groupId = 0;
    readonly string _name = string.Empty;
    readonly string _importance = string.Empty;
    readonly int _requestMaxMemoryGrantPercent = 0;
    readonly int _requestMaxCpuTimeSec = 0;
    readonly int _requestMemoryGrantTimeoutSec = 0;
    readonly int _maxDop = 0;
    readonly int _groupMaxRequests = 0;
    readonly int _poolId = 0;
    readonly int _externalPoolId = 0;
    readonly double _requestMaxMemoryGrantPercentNumeric = 0.0;

    public ResourceGovernorWorkloadGroupsDataType( )
    {
    }

    public ResourceGovernorWorkloadGroupsDataType(int groupId,
        string name,
        string importance,
        int requestMaxMemoryGrantPercent,
        int requestMaxCpuTimeSec,
        int requestMemoryGrantTimeoutSec,
        int maxDop,
        int groupMaxRequests,
        int poolId,
        int externalPoolId,
        double requestMaxMemoryGrantPercentNumeric)
    {
        _groupId = groupId;
        _name = name;
        _importance = importance;
        _requestMaxMemoryGrantPercent = requestMaxMemoryGrantPercent;
        _requestMaxCpuTimeSec = requestMaxCpuTimeSec;
        _requestMemoryGrantTimeoutSec = requestMemoryGrantTimeoutSec;
        _maxDop = maxDop;
        _groupMaxRequests = groupMaxRequests;
        _poolId = poolId;
        _externalPoolId = externalPoolId;
        _requestMaxMemoryGrantPercentNumeric = requestMaxMemoryGrantPercentNumeric;
    }

    public int GroupId => _groupId;
    public string Name => _name;
    public string Importance => _importance;
    public int RequestMaxMemoryGrantPercent => _requestMaxMemoryGrantPercent;
    public int RequestMaxCpuTimeSec => _requestMaxCpuTimeSec;
    public int RequestMemoryGrantTimeoutSec => _requestMemoryGrantTimeoutSec;
    public int MaxDop => _maxDop;
    public int GroupMaxRequests => _groupMaxRequests;
    public int PoolId => _poolId;
    public int ExternalPoolId => _externalPoolId;
    public double RequestMaxMemoryGrantPercentNumeric => _requestMaxMemoryGrantPercentNumeric;
}
