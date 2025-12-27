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

public class DmExecConnectionsDataType
{
    readonly int? _sessionId;
    readonly int? _mostRecentSessionId;
    readonly DateTime _connectTime;
    readonly string _netTransport = string.Empty;
    readonly string? _protocolType;
    readonly int? _protocolVersion;
    readonly int? _endpointId;
    readonly string _encryptOption = string.Empty;
    readonly string _authScheme = string.Empty;
    readonly short _nodeAffinity = 0;
    readonly int? _numReads;
    readonly int? _numWrites;
    readonly DateTime? _lastRead;
    readonly DateTime? _lastWrite;
    readonly int? _netPacketSize;
    readonly string? _clientNetAddress;
    readonly int? _clientTcpPort;
    readonly string? _localNetAddress;
    readonly int? _localTcpPort;
    readonly Guid _connectionId;
    readonly Guid? _parentConnectionId;
    readonly byte[]? _mostRecentSqlHandle;

    public DmExecConnectionsDataType( )
    {
    }

    public DmExecConnectionsDataType(int? sessionId,
        int? mostRecentSessionId,
        DateTime connectTime,
        string netTransport,
        string? protocolType,
        int? protocolVersion,
        int? endpointId,
        string encryptOption,
        string authScheme,
        short nodeAffinity,
        int? numReads,
        int? numWrites,
        DateTime? lastRead,
        DateTime? lastWrite,
        int? netPacketSize,
        string? clientNetAddress,
        int? clientTcpPort,
        string? localNetAddress,
        int? localTcpPort,
        Guid connectionId,
        Guid? parentConnectionId,
        byte[]? mostRecentSqlHandle)
    {
        _sessionId = sessionId;
        _mostRecentSessionId = mostRecentSessionId;
        _connectTime = connectTime;
        _netTransport = netTransport;
        _protocolType = protocolType;
        _protocolVersion = protocolVersion;
        _endpointId = endpointId;
        _encryptOption = encryptOption;
        _authScheme = authScheme;
        _nodeAffinity = nodeAffinity;
        _numReads = numReads;
        _numWrites = numWrites;
        _lastRead = lastRead;
        _lastWrite = lastWrite;
        _netPacketSize = netPacketSize;
        _clientNetAddress = clientNetAddress;
        _clientTcpPort = clientTcpPort;
        _localNetAddress = localNetAddress;
        _localTcpPort = localTcpPort;
        _connectionId = connectionId;
        _parentConnectionId = parentConnectionId;
        _mostRecentSqlHandle = mostRecentSqlHandle;
    }

    public int? SessionId => _sessionId;
    public int? MostRecentSessionId => _mostRecentSessionId;
    public DateTime ConnectTime => _connectTime;
    public string NetTransport => _netTransport;
    public string? ProtocolType => _protocolType;
    public int? ProtocolVersion => _protocolVersion;
    public int? EndpointId => _endpointId;
    public string EncryptOption => _encryptOption;
    public string AuthScheme => _authScheme;
    public short NodeAffinity => _nodeAffinity;
    public int? NumReads => _numReads;
    public int? NumWrites => _numWrites;
    public DateTime? LastRead => _lastRead;
    public DateTime? LastWrite => _lastWrite;
    public int? NetPacketSize => _netPacketSize;
    public string? ClientNetAddress => _clientNetAddress;
    public int? ClientTcpPort => _clientTcpPort;
    public string? LocalNetAddress => _localNetAddress;
    public int? LocalTcpPort => _localTcpPort;
    public Guid ConnectionId => _connectionId;
    public Guid? ParentConnectionId => _parentConnectionId;
    public byte[]? MostRecentSqlHandle => _mostRecentSqlHandle;
}
