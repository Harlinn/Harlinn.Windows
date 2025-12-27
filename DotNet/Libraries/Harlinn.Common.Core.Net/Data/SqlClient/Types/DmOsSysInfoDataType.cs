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

public class DmOsSysInfoDataType
{
    readonly long _cpuTicks = 0;
    readonly long _msTicks = 0;
    readonly int _cpuCount = 0;
    readonly int _hyperthreadRatio = 0;
    readonly long _physicalMemoryKb = 0;
    readonly long _virtualMemoryKb = 0;
    readonly long _committedKb = 0;
    readonly long _committedTargetKb = 0;
    readonly long _visibleTargetKb = 0;
    readonly int _stackSizeInBytes = 0;
    readonly long _osQuantum = 0;
    readonly int _osErrorMode = 0;
    readonly int? _osPriorityClass;
    readonly int _maxWorkersCount = 0;
    readonly int _schedulerCount = 0;
    readonly int _schedulerTotalCount = 0;
    readonly int _deadlockMonitorSerialNumber = 0;
    readonly long _sqlserverStartTimeMsTicks = 0;
    readonly DateTime _sqlserverStartTime;
    readonly int _affinityType = 0;
    readonly string _affinityTypeDesc = string.Empty;
    readonly long _processKernelTimeMs = 0;
    readonly long _processUserTimeMs = 0;
    readonly int _timeSource = 0;
    readonly string _timeSourceDesc = string.Empty;
    readonly int _virtualMachineType = 0;
    readonly string _virtualMachineTypeDesc = string.Empty;
    readonly int _softnumaConfiguration = 0;
    readonly string _softnumaConfigurationDesc = string.Empty;
    readonly string _processPhysicalAffinity = string.Empty;
    readonly int _sqlMemoryModel = 0;
    readonly string _sqlMemoryModelDesc = string.Empty;
    readonly int _socketCount = 0;
    readonly int _coresPerSocket = 0;
    readonly int _numaNodeCount = 0;
    readonly int _containerType = 0;
    readonly string _containerTypeDesc = string.Empty;

    public DmOsSysInfoDataType( )
    {
    }

    public DmOsSysInfoDataType(long cpuTicks,
        long msTicks,
        int cpuCount,
        int hyperthreadRatio,
        long physicalMemoryKb,
        long virtualMemoryKb,
        long committedKb,
        long committedTargetKb,
        long visibleTargetKb,
        int stackSizeInBytes,
        long osQuantum,
        int osErrorMode,
        int? osPriorityClass,
        int maxWorkersCount,
        int schedulerCount,
        int schedulerTotalCount,
        int deadlockMonitorSerialNumber,
        long sqlserverStartTimeMsTicks,
        DateTime sqlserverStartTime,
        int affinityType,
        string affinityTypeDesc,
        long processKernelTimeMs,
        long processUserTimeMs,
        int timeSource,
        string timeSourceDesc,
        int virtualMachineType,
        string virtualMachineTypeDesc,
        int softnumaConfiguration,
        string softnumaConfigurationDesc,
        string processPhysicalAffinity,
        int sqlMemoryModel,
        string sqlMemoryModelDesc,
        int socketCount,
        int coresPerSocket,
        int numaNodeCount,
        int containerType,
        string containerTypeDesc)
    {
        _cpuTicks = cpuTicks;
        _msTicks = msTicks;
        _cpuCount = cpuCount;
        _hyperthreadRatio = hyperthreadRatio;
        _physicalMemoryKb = physicalMemoryKb;
        _virtualMemoryKb = virtualMemoryKb;
        _committedKb = committedKb;
        _committedTargetKb = committedTargetKb;
        _visibleTargetKb = visibleTargetKb;
        _stackSizeInBytes = stackSizeInBytes;
        _osQuantum = osQuantum;
        _osErrorMode = osErrorMode;
        _osPriorityClass = osPriorityClass;
        _maxWorkersCount = maxWorkersCount;
        _schedulerCount = schedulerCount;
        _schedulerTotalCount = schedulerTotalCount;
        _deadlockMonitorSerialNumber = deadlockMonitorSerialNumber;
        _sqlserverStartTimeMsTicks = sqlserverStartTimeMsTicks;
        _sqlserverStartTime = sqlserverStartTime;
        _affinityType = affinityType;
        _affinityTypeDesc = affinityTypeDesc;
        _processKernelTimeMs = processKernelTimeMs;
        _processUserTimeMs = processUserTimeMs;
        _timeSource = timeSource;
        _timeSourceDesc = timeSourceDesc;
        _virtualMachineType = virtualMachineType;
        _virtualMachineTypeDesc = virtualMachineTypeDesc;
        _softnumaConfiguration = softnumaConfiguration;
        _softnumaConfigurationDesc = softnumaConfigurationDesc;
        _processPhysicalAffinity = processPhysicalAffinity;
        _sqlMemoryModel = sqlMemoryModel;
        _sqlMemoryModelDesc = sqlMemoryModelDesc;
        _socketCount = socketCount;
        _coresPerSocket = coresPerSocket;
        _numaNodeCount = numaNodeCount;
        _containerType = containerType;
        _containerTypeDesc = containerTypeDesc;
    }

    public long CpuTicks => _cpuTicks;
    public long MsTicks => _msTicks;
    public int CpuCount => _cpuCount;
    public int HyperthreadRatio => _hyperthreadRatio;
    public long PhysicalMemoryKb => _physicalMemoryKb;
    public long VirtualMemoryKb => _virtualMemoryKb;
    public long CommittedKb => _committedKb;
    public long CommittedTargetKb => _committedTargetKb;
    public long VisibleTargetKb => _visibleTargetKb;
    public int StackSizeInBytes => _stackSizeInBytes;
    public long OsQuantum => _osQuantum;
    public int OsErrorMode => _osErrorMode;
    public int? OsPriorityClass => _osPriorityClass;
    public int MaxWorkersCount => _maxWorkersCount;
    public int SchedulerCount => _schedulerCount;
    public int SchedulerTotalCount => _schedulerTotalCount;
    public int DeadlockMonitorSerialNumber => _deadlockMonitorSerialNumber;
    public long SqlserverStartTimeMsTicks => _sqlserverStartTimeMsTicks;
    public DateTime SqlserverStartTime => _sqlserverStartTime;
    public int AffinityType => _affinityType;
    public string AffinityTypeDesc => _affinityTypeDesc;
    public long ProcessKernelTimeMs => _processKernelTimeMs;
    public long ProcessUserTimeMs => _processUserTimeMs;
    public int TimeSource => _timeSource;
    public string TimeSourceDesc => _timeSourceDesc;
    public int VirtualMachineType => _virtualMachineType;
    public string VirtualMachineTypeDesc => _virtualMachineTypeDesc;
    public int SoftnumaConfiguration => _softnumaConfiguration;
    public string SoftnumaConfigurationDesc => _softnumaConfigurationDesc;
    public string ProcessPhysicalAffinity => _processPhysicalAffinity;
    public int SqlMemoryModel => _sqlMemoryModel;
    public string SqlMemoryModelDesc => _sqlMemoryModelDesc;
    public int SocketCount => _socketCount;
    public int CoresPerSocket => _coresPerSocket;
    public int NumaNodeCount => _numaNodeCount;
    public int ContainerType => _containerType;
    public string ContainerTypeDesc => _containerTypeDesc;
}
