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

public class DmBrokerConnectionsDataType
{
    readonly Guid? _connectionId;
    readonly Guid? _transportStreamId;
    readonly short? _state;
    readonly string? _stateDesc;
    readonly DateTime? _connectTime;
    readonly DateTime? _loginTime;
    readonly string? _authenticationMethod;
    readonly string? _principalName;
    readonly string? _remoteUserName;
    readonly DateTime? _lastActivityTime;
    readonly bool? _isAccept;
    readonly short? _loginState;
    readonly string? _loginStateDesc;
    readonly int? _peerCertificateId;
    readonly short? _encryptionAlgorithm;
    readonly string? _encryptionAlgorithmDesc;
    readonly short? _receivesPosted;
    readonly bool? _isReceiveFlowControlled;
    readonly short? _sendsPosted;
    readonly bool? _isSendFlowControlled;
    readonly long? _totalBytesSent;
    readonly long? _totalBytesReceived;
    readonly long? _totalFragmentsSent;
    readonly long? _totalFragmentsReceived;
    readonly long? _totalSends;
    readonly long? _totalReceives;
    readonly Guid? _peerArbitrationId;

    public DmBrokerConnectionsDataType( )
    {
    }

    public DmBrokerConnectionsDataType(Guid? connectionId,
        Guid? transportStreamId,
        short? state,
        string? stateDesc,
        DateTime? connectTime,
        DateTime? loginTime,
        string? authenticationMethod,
        string? principalName,
        string? remoteUserName,
        DateTime? lastActivityTime,
        bool? isAccept,
        short? loginState,
        string? loginStateDesc,
        int? peerCertificateId,
        short? encryptionAlgorithm,
        string? encryptionAlgorithmDesc,
        short? receivesPosted,
        bool? isReceiveFlowControlled,
        short? sendsPosted,
        bool? isSendFlowControlled,
        long? totalBytesSent,
        long? totalBytesReceived,
        long? totalFragmentsSent,
        long? totalFragmentsReceived,
        long? totalSends,
        long? totalReceives,
        Guid? peerArbitrationId)
    {
        _connectionId = connectionId;
        _transportStreamId = transportStreamId;
        _state = state;
        _stateDesc = stateDesc;
        _connectTime = connectTime;
        _loginTime = loginTime;
        _authenticationMethod = authenticationMethod;
        _principalName = principalName;
        _remoteUserName = remoteUserName;
        _lastActivityTime = lastActivityTime;
        _isAccept = isAccept;
        _loginState = loginState;
        _loginStateDesc = loginStateDesc;
        _peerCertificateId = peerCertificateId;
        _encryptionAlgorithm = encryptionAlgorithm;
        _encryptionAlgorithmDesc = encryptionAlgorithmDesc;
        _receivesPosted = receivesPosted;
        _isReceiveFlowControlled = isReceiveFlowControlled;
        _sendsPosted = sendsPosted;
        _isSendFlowControlled = isSendFlowControlled;
        _totalBytesSent = totalBytesSent;
        _totalBytesReceived = totalBytesReceived;
        _totalFragmentsSent = totalFragmentsSent;
        _totalFragmentsReceived = totalFragmentsReceived;
        _totalSends = totalSends;
        _totalReceives = totalReceives;
        _peerArbitrationId = peerArbitrationId;
    }

    public Guid? ConnectionId => _connectionId;
    public Guid? TransportStreamId => _transportStreamId;
    public short? State => _state;
    public string? StateDesc => _stateDesc;
    public DateTime? ConnectTime => _connectTime;
    public DateTime? LoginTime => _loginTime;
    public string? AuthenticationMethod => _authenticationMethod;
    public string? PrincipalName => _principalName;
    public string? RemoteUserName => _remoteUserName;
    public DateTime? LastActivityTime => _lastActivityTime;
    public bool? IsAccept => _isAccept;
    public short? LoginState => _loginState;
    public string? LoginStateDesc => _loginStateDesc;
    public int? PeerCertificateId => _peerCertificateId;
    public short? EncryptionAlgorithm => _encryptionAlgorithm;
    public string? EncryptionAlgorithmDesc => _encryptionAlgorithmDesc;
    public short? ReceivesPosted => _receivesPosted;
    public bool? IsReceiveFlowControlled => _isReceiveFlowControlled;
    public short? SendsPosted => _sendsPosted;
    public bool? IsSendFlowControlled => _isSendFlowControlled;
    public long? TotalBytesSent => _totalBytesSent;
    public long? TotalBytesReceived => _totalBytesReceived;
    public long? TotalFragmentsSent => _totalFragmentsSent;
    public long? TotalFragmentsReceived => _totalFragmentsReceived;
    public long? TotalSends => _totalSends;
    public long? TotalReceives => _totalReceives;
    public Guid? PeerArbitrationId => _peerArbitrationId;
}
