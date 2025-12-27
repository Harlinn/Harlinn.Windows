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

public class DmOsProcessMemoryDataType
{
    readonly long _physicalMemoryInUseKb = 0;
    readonly long _largePageAllocationsKb = 0;
    readonly long _lockedPageAllocationsKb = 0;
    readonly long _totalVirtualAddressSpaceKb = 0;
    readonly long _virtualAddressSpaceReservedKb = 0;
    readonly long _virtualAddressSpaceCommittedKb = 0;
    readonly long _virtualAddressSpaceAvailableKb = 0;
    readonly long _pageFaultCount = 0;
    readonly int _memoryUtilizationPercentage = 0;
    readonly long _availableCommitLimitKb = 0;
    readonly bool _processPhysicalMemoryLow = false;
    readonly bool _processVirtualMemoryLow = false;

    public DmOsProcessMemoryDataType( )
    {
    }

    public DmOsProcessMemoryDataType(long physicalMemoryInUseKb,
        long largePageAllocationsKb,
        long lockedPageAllocationsKb,
        long totalVirtualAddressSpaceKb,
        long virtualAddressSpaceReservedKb,
        long virtualAddressSpaceCommittedKb,
        long virtualAddressSpaceAvailableKb,
        long pageFaultCount,
        int memoryUtilizationPercentage,
        long availableCommitLimitKb,
        bool processPhysicalMemoryLow,
        bool processVirtualMemoryLow)
    {
        _physicalMemoryInUseKb = physicalMemoryInUseKb;
        _largePageAllocationsKb = largePageAllocationsKb;
        _lockedPageAllocationsKb = lockedPageAllocationsKb;
        _totalVirtualAddressSpaceKb = totalVirtualAddressSpaceKb;
        _virtualAddressSpaceReservedKb = virtualAddressSpaceReservedKb;
        _virtualAddressSpaceCommittedKb = virtualAddressSpaceCommittedKb;
        _virtualAddressSpaceAvailableKb = virtualAddressSpaceAvailableKb;
        _pageFaultCount = pageFaultCount;
        _memoryUtilizationPercentage = memoryUtilizationPercentage;
        _availableCommitLimitKb = availableCommitLimitKb;
        _processPhysicalMemoryLow = processPhysicalMemoryLow;
        _processVirtualMemoryLow = processVirtualMemoryLow;
    }

    public long PhysicalMemoryInUseKb => _physicalMemoryInUseKb;
    public long LargePageAllocationsKb => _largePageAllocationsKb;
    public long LockedPageAllocationsKb => _lockedPageAllocationsKb;
    public long TotalVirtualAddressSpaceKb => _totalVirtualAddressSpaceKb;
    public long VirtualAddressSpaceReservedKb => _virtualAddressSpaceReservedKb;
    public long VirtualAddressSpaceCommittedKb => _virtualAddressSpaceCommittedKb;
    public long VirtualAddressSpaceAvailableKb => _virtualAddressSpaceAvailableKb;
    public long PageFaultCount => _pageFaultCount;
    public int MemoryUtilizationPercentage => _memoryUtilizationPercentage;
    public long AvailableCommitLimitKb => _availableCommitLimitKb;
    public bool ProcessPhysicalMemoryLow => _processPhysicalMemoryLow;
    public bool ProcessVirtualMemoryLow => _processVirtualMemoryLow;
}
