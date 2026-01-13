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

public class DmResourceGovernorResourcePoolAffinityDataType
{
    readonly int _poolId = 0;
    readonly short _processorGroup = 0;
    readonly long _schedulerMask = 0;

    public DmResourceGovernorResourcePoolAffinityDataType( )
    {
    }

    public DmResourceGovernorResourcePoolAffinityDataType(int poolId,
        short processorGroup,
        long schedulerMask)
    {
        _poolId = poolId;
        _processorGroup = processorGroup;
        _schedulerMask = schedulerMask;
    }

    public int PoolId => _poolId;
    public short ProcessorGroup => _processorGroup;
    public long SchedulerMask => _schedulerMask;
}
