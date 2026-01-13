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

public class DmOsTasksDataType
{
    readonly byte[] _taskAddress = Array.Empty<byte>();
    readonly string? _taskState;
    readonly int? _contextSwitchesCount;
    readonly int? _pendingIoCount;
    readonly long? _pendingIoByteCount;
    readonly int? _pendingIoByteAverage;
    readonly int _schedulerId = 0;
    readonly short? _sessionId;
    readonly int? _execContextId;
    readonly int? _requestId;
    readonly byte[]? _workerAddress;
    readonly byte[] _hostAddress = Array.Empty<byte>();
    readonly byte[]? _parentTaskAddress;

    public DmOsTasksDataType( )
    {
    }

    public DmOsTasksDataType(byte[] taskAddress,
        string? taskState,
        int? contextSwitchesCount,
        int? pendingIoCount,
        long? pendingIoByteCount,
        int? pendingIoByteAverage,
        int schedulerId,
        short? sessionId,
        int? execContextId,
        int? requestId,
        byte[]? workerAddress,
        byte[] hostAddress,
        byte[]? parentTaskAddress)
    {
        _taskAddress = taskAddress;
        _taskState = taskState;
        _contextSwitchesCount = contextSwitchesCount;
        _pendingIoCount = pendingIoCount;
        _pendingIoByteCount = pendingIoByteCount;
        _pendingIoByteAverage = pendingIoByteAverage;
        _schedulerId = schedulerId;
        _sessionId = sessionId;
        _execContextId = execContextId;
        _requestId = requestId;
        _workerAddress = workerAddress;
        _hostAddress = hostAddress;
        _parentTaskAddress = parentTaskAddress;
    }

    public byte[] TaskAddress => _taskAddress;
    public string? TaskState => _taskState;
    public int? ContextSwitchesCount => _contextSwitchesCount;
    public int? PendingIoCount => _pendingIoCount;
    public long? PendingIoByteCount => _pendingIoByteCount;
    public int? PendingIoByteAverage => _pendingIoByteAverage;
    public int SchedulerId => _schedulerId;
    public short? SessionId => _sessionId;
    public int? ExecContextId => _execContextId;
    public int? RequestId => _requestId;
    public byte[]? WorkerAddress => _workerAddress;
    public byte[] HostAddress => _hostAddress;
    public byte[]? ParentTaskAddress => _parentTaskAddress;
}
