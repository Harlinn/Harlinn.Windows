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

public class DmOsThreadsDataType
{
    readonly byte[] _threadAddress = Array.Empty<byte>();
    readonly bool _startedBySqlservr = false;
    readonly int _osThreadId = 0;
    readonly int _status = 0;
    readonly byte[]? _instructionAddress;
    readonly DateTime? _creationTime;
    readonly long? _kernelTime;
    readonly long? _usermodeTime;
    readonly byte[] _stackBaseAddress = Array.Empty<byte>();
    readonly byte[]? _stackEndAddress;
    readonly int _stackBytesCommitted = 0;
    readonly int? _stackBytesUsed;
    readonly long _affinity = 0;
    readonly int? _priority;
    readonly int? _locale;
    readonly byte[]? _token;
    readonly int? _isImpersonating;
    readonly int? _isWaitingOnLoaderLock;
    readonly byte[]? _fiberData;
    readonly byte[]? _threadHandle;
    readonly byte[]? _eventHandle;
    readonly byte[]? _schedulerAddress;
    readonly byte[]? _workerAddress;
    readonly byte[]? _fiberContextAddress;
    readonly byte[]? _selfAddress;
    readonly short _processorGroup = 0;

    public DmOsThreadsDataType( )
    {
    }

    public DmOsThreadsDataType(byte[] threadAddress,
        bool startedBySqlservr,
        int osThreadId,
        int status,
        byte[]? instructionAddress,
        DateTime? creationTime,
        long? kernelTime,
        long? usermodeTime,
        byte[] stackBaseAddress,
        byte[]? stackEndAddress,
        int stackBytesCommitted,
        int? stackBytesUsed,
        long affinity,
        int? priority,
        int? locale,
        byte[]? token,
        int? isImpersonating,
        int? isWaitingOnLoaderLock,
        byte[]? fiberData,
        byte[]? threadHandle,
        byte[]? eventHandle,
        byte[]? schedulerAddress,
        byte[]? workerAddress,
        byte[]? fiberContextAddress,
        byte[]? selfAddress,
        short processorGroup)
    {
        _threadAddress = threadAddress;
        _startedBySqlservr = startedBySqlservr;
        _osThreadId = osThreadId;
        _status = status;
        _instructionAddress = instructionAddress;
        _creationTime = creationTime;
        _kernelTime = kernelTime;
        _usermodeTime = usermodeTime;
        _stackBaseAddress = stackBaseAddress;
        _stackEndAddress = stackEndAddress;
        _stackBytesCommitted = stackBytesCommitted;
        _stackBytesUsed = stackBytesUsed;
        _affinity = affinity;
        _priority = priority;
        _locale = locale;
        _token = token;
        _isImpersonating = isImpersonating;
        _isWaitingOnLoaderLock = isWaitingOnLoaderLock;
        _fiberData = fiberData;
        _threadHandle = threadHandle;
        _eventHandle = eventHandle;
        _schedulerAddress = schedulerAddress;
        _workerAddress = workerAddress;
        _fiberContextAddress = fiberContextAddress;
        _selfAddress = selfAddress;
        _processorGroup = processorGroup;
    }

    public byte[] ThreadAddress => _threadAddress;
    public bool StartedBySqlservr => _startedBySqlservr;
    public int OsThreadId => _osThreadId;
    public int Status => _status;
    public byte[]? InstructionAddress => _instructionAddress;
    public DateTime? CreationTime => _creationTime;
    public long? KernelTime => _kernelTime;
    public long? UsermodeTime => _usermodeTime;
    public byte[] StackBaseAddress => _stackBaseAddress;
    public byte[]? StackEndAddress => _stackEndAddress;
    public int StackBytesCommitted => _stackBytesCommitted;
    public int? StackBytesUsed => _stackBytesUsed;
    public long Affinity => _affinity;
    public int? Priority => _priority;
    public int? Locale => _locale;
    public byte[]? Token => _token;
    public int? IsImpersonating => _isImpersonating;
    public int? IsWaitingOnLoaderLock => _isWaitingOnLoaderLock;
    public byte[]? FiberData => _fiberData;
    public byte[]? ThreadHandle => _threadHandle;
    public byte[]? EventHandle => _eventHandle;
    public byte[]? SchedulerAddress => _schedulerAddress;
    public byte[]? WorkerAddress => _workerAddress;
    public byte[]? FiberContextAddress => _fiberContextAddress;
    public byte[]? SelfAddress => _selfAddress;
    public short ProcessorGroup => _processorGroup;
}
