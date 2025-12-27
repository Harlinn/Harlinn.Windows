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

public class ResourceGovernorExternalResourcePoolAffinityDataType
{
    readonly int _externalPoolId = 0;
    readonly short _processorGroup = 0;
    readonly long _cpuMask = 0;

    public ResourceGovernorExternalResourcePoolAffinityDataType( )
    {
    }

    public ResourceGovernorExternalResourcePoolAffinityDataType(int externalPoolId,
        short processorGroup,
        long cpuMask)
    {
        _externalPoolId = externalPoolId;
        _processorGroup = processorGroup;
        _cpuMask = cpuMask;
    }

    public int ExternalPoolId => _externalPoolId;
    public short ProcessorGroup => _processorGroup;
    public long CpuMask => _cpuMask;
}
