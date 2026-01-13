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

public class ResourceGovernorExternalResourcePoolsDataType
{
    readonly int _externalPoolId = 0;
    readonly string _name = string.Empty;
    readonly int _maxCpuPercent = 0;
    readonly int _maxMemoryPercent = 0;
    readonly int _maxProcesses = 0;
    readonly long _version = 0;

    public ResourceGovernorExternalResourcePoolsDataType( )
    {
    }

    public ResourceGovernorExternalResourcePoolsDataType(int externalPoolId,
        string name,
        int maxCpuPercent,
        int maxMemoryPercent,
        int maxProcesses,
        long version)
    {
        _externalPoolId = externalPoolId;
        _name = name;
        _maxCpuPercent = maxCpuPercent;
        _maxMemoryPercent = maxMemoryPercent;
        _maxProcesses = maxProcesses;
        _version = version;
    }

    public int ExternalPoolId => _externalPoolId;
    public string Name => _name;
    public int MaxCpuPercent => _maxCpuPercent;
    public int MaxMemoryPercent => _maxMemoryPercent;
    public int MaxProcesses => _maxProcesses;
    public long Version => _version;
}
