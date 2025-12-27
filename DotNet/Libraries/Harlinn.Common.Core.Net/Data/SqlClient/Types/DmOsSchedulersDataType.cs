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

public class DmOsSchedulersDataType
{
    readonly byte[] _schedulerAddress = Array.Empty<byte>();
    readonly int _parentNodeId = 0;
    readonly int _schedulerId = 0;
    readonly int _cpuId = 0;
    readonly string _status = string.Empty;
    readonly bool _isOnline = false;
    readonly bool _isIdle = false;
    readonly int _preemptiveSwitchesCount = 0;
    readonly int _contextSwitchesCount = 0;
    readonly int _idleSwitchesCount = 0;
    readonly int _currentTasksCount = 0;
    readonly int _runnableTasksCount = 0;
    readonly int _currentWorkersCount = 0;
    readonly int _activeWorkersCount = 0;
    readonly long _workQueueCount = 0;
    readonly int _pendingDiskIoCount = 0;
    readonly int _loadFactor = 0;
    readonly int _yieldCount = 0;
    readonly long _lastTimerActivity = 0;
    readonly bool _failedToCreateWorker = false;
    readonly byte[]? _activeWorkerAddress;
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly byte[] _taskMemoryObjectAddress = Array.Empty<byte>();
    readonly long _quantumLengthUs = 0;
    readonly long _totalCpuUsageMs = 0;
    readonly long? _totalCpuIdleCappedMs;
    readonly long _totalSchedulerDelayMs = 0;
    readonly int _idealWorkersLimit = 0;

    public DmOsSchedulersDataType( )
    {
    }

    public DmOsSchedulersDataType(byte[] schedulerAddress,
        int parentNodeId,
        int schedulerId,
        int cpuId,
        string status,
        bool isOnline,
        bool isIdle,
        int preemptiveSwitchesCount,
        int contextSwitchesCount,
        int idleSwitchesCount,
        int currentTasksCount,
        int runnableTasksCount,
        int currentWorkersCount,
        int activeWorkersCount,
        long workQueueCount,
        int pendingDiskIoCount,
        int loadFactor,
        int yieldCount,
        long lastTimerActivity,
        bool failedToCreateWorker,
        byte[]? activeWorkerAddress,
        byte[] memoryObjectAddress,
        byte[] taskMemoryObjectAddress,
        long quantumLengthUs,
        long totalCpuUsageMs,
        long? totalCpuIdleCappedMs,
        long totalSchedulerDelayMs,
        int idealWorkersLimit)
    {
        _schedulerAddress = schedulerAddress;
        _parentNodeId = parentNodeId;
        _schedulerId = schedulerId;
        _cpuId = cpuId;
        _status = status;
        _isOnline = isOnline;
        _isIdle = isIdle;
        _preemptiveSwitchesCount = preemptiveSwitchesCount;
        _contextSwitchesCount = contextSwitchesCount;
        _idleSwitchesCount = idleSwitchesCount;
        _currentTasksCount = currentTasksCount;
        _runnableTasksCount = runnableTasksCount;
        _currentWorkersCount = currentWorkersCount;
        _activeWorkersCount = activeWorkersCount;
        _workQueueCount = workQueueCount;
        _pendingDiskIoCount = pendingDiskIoCount;
        _loadFactor = loadFactor;
        _yieldCount = yieldCount;
        _lastTimerActivity = lastTimerActivity;
        _failedToCreateWorker = failedToCreateWorker;
        _activeWorkerAddress = activeWorkerAddress;
        _memoryObjectAddress = memoryObjectAddress;
        _taskMemoryObjectAddress = taskMemoryObjectAddress;
        _quantumLengthUs = quantumLengthUs;
        _totalCpuUsageMs = totalCpuUsageMs;
        _totalCpuIdleCappedMs = totalCpuIdleCappedMs;
        _totalSchedulerDelayMs = totalSchedulerDelayMs;
        _idealWorkersLimit = idealWorkersLimit;
    }

    public byte[] SchedulerAddress => _schedulerAddress;
    public int ParentNodeId => _parentNodeId;
    public int SchedulerId => _schedulerId;
    public int CpuId => _cpuId;
    public string Status => _status;
    public bool IsOnline => _isOnline;
    public bool IsIdle => _isIdle;
    public int PreemptiveSwitchesCount => _preemptiveSwitchesCount;
    public int ContextSwitchesCount => _contextSwitchesCount;
    public int IdleSwitchesCount => _idleSwitchesCount;
    public int CurrentTasksCount => _currentTasksCount;
    public int RunnableTasksCount => _runnableTasksCount;
    public int CurrentWorkersCount => _currentWorkersCount;
    public int ActiveWorkersCount => _activeWorkersCount;
    public long WorkQueueCount => _workQueueCount;
    public int PendingDiskIoCount => _pendingDiskIoCount;
    public int LoadFactor => _loadFactor;
    public int YieldCount => _yieldCount;
    public long LastTimerActivity => _lastTimerActivity;
    public bool FailedToCreateWorker => _failedToCreateWorker;
    public byte[]? ActiveWorkerAddress => _activeWorkerAddress;
    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public byte[] TaskMemoryObjectAddress => _taskMemoryObjectAddress;
    public long QuantumLengthUs => _quantumLengthUs;
    public long TotalCpuUsageMs => _totalCpuUsageMs;
    public long? TotalCpuIdleCappedMs => _totalCpuIdleCappedMs;
    public long TotalSchedulerDelayMs => _totalSchedulerDelayMs;
    public int IdealWorkersLimit => _idealWorkersLimit;
}
