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

public class DmIoPendingIoRequestsDataType
{
    readonly byte[] _ioCompletionRequestAddress = Array.Empty<byte>();
    readonly string _ioType = string.Empty;
    readonly long _ioPendingMsTicks = 0;
    readonly int _ioPending = 0;
    readonly byte[]? _ioCompletionRoutineAddress;
    readonly byte[]? _ioUserDataAddress;
    readonly byte[] _schedulerAddress = Array.Empty<byte>();
    readonly byte[]? _ioHandle;
    readonly long _ioOffset = 0;
    readonly string? _ioHandlePath;

    public DmIoPendingIoRequestsDataType( )
    {
    }

    public DmIoPendingIoRequestsDataType(byte[] ioCompletionRequestAddress,
        string ioType,
        long ioPendingMsTicks,
        int ioPending,
        byte[]? ioCompletionRoutineAddress,
        byte[]? ioUserDataAddress,
        byte[] schedulerAddress,
        byte[]? ioHandle,
        long ioOffset,
        string? ioHandlePath)
    {
        _ioCompletionRequestAddress = ioCompletionRequestAddress;
        _ioType = ioType;
        _ioPendingMsTicks = ioPendingMsTicks;
        _ioPending = ioPending;
        _ioCompletionRoutineAddress = ioCompletionRoutineAddress;
        _ioUserDataAddress = ioUserDataAddress;
        _schedulerAddress = schedulerAddress;
        _ioHandle = ioHandle;
        _ioOffset = ioOffset;
        _ioHandlePath = ioHandlePath;
    }

    public byte[] IoCompletionRequestAddress => _ioCompletionRequestAddress;
    public string IoType => _ioType;
    public long IoPendingMsTicks => _ioPendingMsTicks;
    public int IoPending => _ioPending;
    public byte[]? IoCompletionRoutineAddress => _ioCompletionRoutineAddress;
    public byte[]? IoUserDataAddress => _ioUserDataAddress;
    public byte[] SchedulerAddress => _schedulerAddress;
    public byte[]? IoHandle => _ioHandle;
    public long IoOffset => _ioOffset;
    public string? IoHandlePath => _ioHandlePath;
}
