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

public class DmOsJobObjectDataType
{
    readonly int? _cpuRate;
    readonly long? _cpuAffinityMask;
    readonly int? _cpuAffinityGroup;
    readonly long? _memoryLimitMb;
    readonly long? _processMemoryLimitMb;
    readonly long? _workingsetLimitMb;
    readonly long? _nonSosMemGapMb;
    readonly long? _lowMemSignalThresholdMb;
    readonly long? _totalUserTime;
    readonly long? _totalKernelTime;
    readonly long? _writeOperationCount;
    readonly long? _readOperationCount;
    readonly long? _peakProcessMemoryUsedMb;
    readonly long? _peakJobMemoryUsedMb;
    readonly string _processPhysicalAffinity = string.Empty;

    public DmOsJobObjectDataType( )
    {
    }

    public DmOsJobObjectDataType(int? cpuRate,
        long? cpuAffinityMask,
        int? cpuAffinityGroup,
        long? memoryLimitMb,
        long? processMemoryLimitMb,
        long? workingsetLimitMb,
        long? nonSosMemGapMb,
        long? lowMemSignalThresholdMb,
        long? totalUserTime,
        long? totalKernelTime,
        long? writeOperationCount,
        long? readOperationCount,
        long? peakProcessMemoryUsedMb,
        long? peakJobMemoryUsedMb,
        string processPhysicalAffinity)
    {
        _cpuRate = cpuRate;
        _cpuAffinityMask = cpuAffinityMask;
        _cpuAffinityGroup = cpuAffinityGroup;
        _memoryLimitMb = memoryLimitMb;
        _processMemoryLimitMb = processMemoryLimitMb;
        _workingsetLimitMb = workingsetLimitMb;
        _nonSosMemGapMb = nonSosMemGapMb;
        _lowMemSignalThresholdMb = lowMemSignalThresholdMb;
        _totalUserTime = totalUserTime;
        _totalKernelTime = totalKernelTime;
        _writeOperationCount = writeOperationCount;
        _readOperationCount = readOperationCount;
        _peakProcessMemoryUsedMb = peakProcessMemoryUsedMb;
        _peakJobMemoryUsedMb = peakJobMemoryUsedMb;
        _processPhysicalAffinity = processPhysicalAffinity;
    }

    public int? CpuRate => _cpuRate;
    public long? CpuAffinityMask => _cpuAffinityMask;
    public int? CpuAffinityGroup => _cpuAffinityGroup;
    public long? MemoryLimitMb => _memoryLimitMb;
    public long? ProcessMemoryLimitMb => _processMemoryLimitMb;
    public long? WorkingsetLimitMb => _workingsetLimitMb;
    public long? NonSosMemGapMb => _nonSosMemGapMb;
    public long? LowMemSignalThresholdMb => _lowMemSignalThresholdMb;
    public long? TotalUserTime => _totalUserTime;
    public long? TotalKernelTime => _totalKernelTime;
    public long? WriteOperationCount => _writeOperationCount;
    public long? ReadOperationCount => _readOperationCount;
    public long? PeakProcessMemoryUsedMb => _peakProcessMemoryUsedMb;
    public long? PeakJobMemoryUsedMb => _peakJobMemoryUsedMb;
    public string ProcessPhysicalAffinity => _processPhysicalAffinity;
}
