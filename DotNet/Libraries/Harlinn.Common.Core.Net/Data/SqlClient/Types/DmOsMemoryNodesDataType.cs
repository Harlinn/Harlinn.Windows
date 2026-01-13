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

public class DmOsMemoryNodesDataType
{
    readonly short _memoryNodeId = 0;
    readonly long _virtualAddressSpaceReservedKb = 0;
    readonly long _virtualAddressSpaceCommittedKb = 0;
    readonly long _lockedPageAllocationsKb = 0;
    readonly long _pagesKb = 0;
    readonly long _sharedMemoryReservedKb = 0;
    readonly long _sharedMemoryCommittedKb = 0;
    readonly long _cpuAffinityMask = 0;
    readonly long _onlineSchedulerMask = 0;
    readonly short _processorGroup = 0;
    readonly long _foreignCommittedKb = 0;
    readonly long _targetKb = 0;

    public DmOsMemoryNodesDataType( )
    {
    }

    public DmOsMemoryNodesDataType(short memoryNodeId,
        long virtualAddressSpaceReservedKb,
        long virtualAddressSpaceCommittedKb,
        long lockedPageAllocationsKb,
        long pagesKb,
        long sharedMemoryReservedKb,
        long sharedMemoryCommittedKb,
        long cpuAffinityMask,
        long onlineSchedulerMask,
        short processorGroup,
        long foreignCommittedKb,
        long targetKb)
    {
        _memoryNodeId = memoryNodeId;
        _virtualAddressSpaceReservedKb = virtualAddressSpaceReservedKb;
        _virtualAddressSpaceCommittedKb = virtualAddressSpaceCommittedKb;
        _lockedPageAllocationsKb = lockedPageAllocationsKb;
        _pagesKb = pagesKb;
        _sharedMemoryReservedKb = sharedMemoryReservedKb;
        _sharedMemoryCommittedKb = sharedMemoryCommittedKb;
        _cpuAffinityMask = cpuAffinityMask;
        _onlineSchedulerMask = onlineSchedulerMask;
        _processorGroup = processorGroup;
        _foreignCommittedKb = foreignCommittedKb;
        _targetKb = targetKb;
    }

    public short MemoryNodeId => _memoryNodeId;
    public long VirtualAddressSpaceReservedKb => _virtualAddressSpaceReservedKb;
    public long VirtualAddressSpaceCommittedKb => _virtualAddressSpaceCommittedKb;
    public long LockedPageAllocationsKb => _lockedPageAllocationsKb;
    public long PagesKb => _pagesKb;
    public long SharedMemoryReservedKb => _sharedMemoryReservedKb;
    public long SharedMemoryCommittedKb => _sharedMemoryCommittedKb;
    public long CpuAffinityMask => _cpuAffinityMask;
    public long OnlineSchedulerMask => _onlineSchedulerMask;
    public short ProcessorGroup => _processorGroup;
    public long ForeignCommittedKb => _foreignCommittedKb;
    public long TargetKb => _targetKb;
}
