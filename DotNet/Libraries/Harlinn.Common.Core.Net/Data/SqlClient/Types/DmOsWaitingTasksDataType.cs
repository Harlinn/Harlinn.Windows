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

public class DmOsWaitingTasksDataType
{
    readonly byte[] _waitingTaskAddress = Array.Empty<byte>();
    readonly short? _sessionId;
    readonly int? _execContextId;
    readonly long? _waitDurationMs;
    readonly string? _waitType;
    readonly byte[]? _resourceAddress;
    readonly byte[]? _blockingTaskAddress;
    readonly short? _blockingSessionId;
    readonly int? _blockingExecContextId;
    readonly string? _resourceDescription;

    public DmOsWaitingTasksDataType( )
    {
    }

    public DmOsWaitingTasksDataType(byte[] waitingTaskAddress,
        short? sessionId,
        int? execContextId,
        long? waitDurationMs,
        string? waitType,
        byte[]? resourceAddress,
        byte[]? blockingTaskAddress,
        short? blockingSessionId,
        int? blockingExecContextId,
        string? resourceDescription)
    {
        _waitingTaskAddress = waitingTaskAddress;
        _sessionId = sessionId;
        _execContextId = execContextId;
        _waitDurationMs = waitDurationMs;
        _waitType = waitType;
        _resourceAddress = resourceAddress;
        _blockingTaskAddress = blockingTaskAddress;
        _blockingSessionId = blockingSessionId;
        _blockingExecContextId = blockingExecContextId;
        _resourceDescription = resourceDescription;
    }

    public byte[] WaitingTaskAddress => _waitingTaskAddress;
    public short? SessionId => _sessionId;
    public int? ExecContextId => _execContextId;
    public long? WaitDurationMs => _waitDurationMs;
    public string? WaitType => _waitType;
    public byte[]? ResourceAddress => _resourceAddress;
    public byte[]? BlockingTaskAddress => _blockingTaskAddress;
    public short? BlockingSessionId => _blockingSessionId;
    public int? BlockingExecContextId => _blockingExecContextId;
    public string? ResourceDescription => _resourceDescription;
}
