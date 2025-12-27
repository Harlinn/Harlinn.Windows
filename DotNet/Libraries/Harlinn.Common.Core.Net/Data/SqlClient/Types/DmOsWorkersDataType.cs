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

public class DmOsWorkersDataType
{
    readonly byte[] _workerAddress = Array.Empty<byte>();
    readonly int _status = 0;
    readonly bool? _isPreemptive;
    readonly bool? _isFiber;
    readonly bool? _isSick;
    readonly bool? _isInCcException;
    readonly bool? _isFatalException;
    readonly bool? _isInsideCatch;
    readonly bool? _isInPollingIoCompletionRoutine;
    readonly int _contextSwitchCount = 0;
    readonly int _pendingIoCount = 0;
    readonly long _pendingIoByteCount = 0;
    readonly int _pendingIoByteAverage = 0;
    readonly long _waitStartedMsTicks = 0;
    readonly long _waitResumedMsTicks = 0;
    readonly long _taskBoundMsTicks = 0;
    readonly long _workerCreatedMsTicks = 0;
    readonly int _exceptionNum = 0;
    readonly int _exceptionSeverity = 0;
    readonly byte[]? _exceptionAddress;
    readonly long _affinity = 0;
    readonly string? _state;
    readonly long _startQuantum = 0;
    readonly long _endQuantum = 0;
    readonly string? _lastWaitType;
    readonly int _returnCode = 0;
    readonly long _quantumUsed = 0;
    readonly long _maxQuantum = 0;
    readonly int _boostCount = 0;
    readonly int _tasksProcessedCount = 0;
    readonly byte[]? _fiberAddress;
    readonly byte[]? _taskAddress;
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly byte[]? _threadAddress;
    readonly byte[]? _signalWorkerAddress;
    readonly byte[]? _schedulerAddress;
    readonly short _processorGroup = 0;
    readonly int _workerMigrationCount = 0;

    public DmOsWorkersDataType( )
    {
    }

    public DmOsWorkersDataType(byte[] workerAddress,
        int status,
        bool? isPreemptive,
        bool? isFiber,
        bool? isSick,
        bool? isInCcException,
        bool? isFatalException,
        bool? isInsideCatch,
        bool? isInPollingIoCompletionRoutine,
        int contextSwitchCount,
        int pendingIoCount,
        long pendingIoByteCount,
        int pendingIoByteAverage,
        long waitStartedMsTicks,
        long waitResumedMsTicks,
        long taskBoundMsTicks,
        long workerCreatedMsTicks,
        int exceptionNum,
        int exceptionSeverity,
        byte[]? exceptionAddress,
        long affinity,
        string? state,
        long startQuantum,
        long endQuantum,
        string? lastWaitType,
        int returnCode,
        long quantumUsed,
        long maxQuantum,
        int boostCount,
        int tasksProcessedCount,
        byte[]? fiberAddress,
        byte[]? taskAddress,
        byte[] memoryObjectAddress,
        byte[]? threadAddress,
        byte[]? signalWorkerAddress,
        byte[]? schedulerAddress,
        short processorGroup,
        int workerMigrationCount)
    {
        _workerAddress = workerAddress;
        _status = status;
        _isPreemptive = isPreemptive;
        _isFiber = isFiber;
        _isSick = isSick;
        _isInCcException = isInCcException;
        _isFatalException = isFatalException;
        _isInsideCatch = isInsideCatch;
        _isInPollingIoCompletionRoutine = isInPollingIoCompletionRoutine;
        _contextSwitchCount = contextSwitchCount;
        _pendingIoCount = pendingIoCount;
        _pendingIoByteCount = pendingIoByteCount;
        _pendingIoByteAverage = pendingIoByteAverage;
        _waitStartedMsTicks = waitStartedMsTicks;
        _waitResumedMsTicks = waitResumedMsTicks;
        _taskBoundMsTicks = taskBoundMsTicks;
        _workerCreatedMsTicks = workerCreatedMsTicks;
        _exceptionNum = exceptionNum;
        _exceptionSeverity = exceptionSeverity;
        _exceptionAddress = exceptionAddress;
        _affinity = affinity;
        _state = state;
        _startQuantum = startQuantum;
        _endQuantum = endQuantum;
        _lastWaitType = lastWaitType;
        _returnCode = returnCode;
        _quantumUsed = quantumUsed;
        _maxQuantum = maxQuantum;
        _boostCount = boostCount;
        _tasksProcessedCount = tasksProcessedCount;
        _fiberAddress = fiberAddress;
        _taskAddress = taskAddress;
        _memoryObjectAddress = memoryObjectAddress;
        _threadAddress = threadAddress;
        _signalWorkerAddress = signalWorkerAddress;
        _schedulerAddress = schedulerAddress;
        _processorGroup = processorGroup;
        _workerMigrationCount = workerMigrationCount;
    }

    public byte[] WorkerAddress => _workerAddress;
    public int Status => _status;
    public bool? IsPreemptive => _isPreemptive;
    public bool? IsFiber => _isFiber;
    public bool? IsSick => _isSick;
    public bool? IsInCcException => _isInCcException;
    public bool? IsFatalException => _isFatalException;
    public bool? IsInsideCatch => _isInsideCatch;
    public bool? IsInPollingIoCompletionRoutine => _isInPollingIoCompletionRoutine;
    public int ContextSwitchCount => _contextSwitchCount;
    public int PendingIoCount => _pendingIoCount;
    public long PendingIoByteCount => _pendingIoByteCount;
    public int PendingIoByteAverage => _pendingIoByteAverage;
    public long WaitStartedMsTicks => _waitStartedMsTicks;
    public long WaitResumedMsTicks => _waitResumedMsTicks;
    public long TaskBoundMsTicks => _taskBoundMsTicks;
    public long WorkerCreatedMsTicks => _workerCreatedMsTicks;
    public int ExceptionNum => _exceptionNum;
    public int ExceptionSeverity => _exceptionSeverity;
    public byte[]? ExceptionAddress => _exceptionAddress;
    public long Affinity => _affinity;
    public string? State => _state;
    public long StartQuantum => _startQuantum;
    public long EndQuantum => _endQuantum;
    public string? LastWaitType => _lastWaitType;
    public int ReturnCode => _returnCode;
    public long QuantumUsed => _quantumUsed;
    public long MaxQuantum => _maxQuantum;
    public int BoostCount => _boostCount;
    public int TasksProcessedCount => _tasksProcessedCount;
    public byte[]? FiberAddress => _fiberAddress;
    public byte[]? TaskAddress => _taskAddress;
    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public byte[]? ThreadAddress => _threadAddress;
    public byte[]? SignalWorkerAddress => _signalWorkerAddress;
    public byte[]? SchedulerAddress => _schedulerAddress;
    public short ProcessorGroup => _processorGroup;
    public int WorkerMigrationCount => _workerMigrationCount;
}
