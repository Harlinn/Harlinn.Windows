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

public class ServiceBrokerEndpointsDataType
{
    readonly string _name = string.Empty;
    readonly int _endpointId = 0;
    readonly int? _principalId;
    readonly byte _protocol = 0;
    readonly string? _protocolDesc;
    readonly byte _type = 0;
    readonly string? _typeDesc;
    readonly byte? _state;
    readonly string? _stateDesc;
    readonly bool _isAdminEndpoint = false;
    readonly bool _isMessageForwardingEnabled = false;
    readonly int _messageForwardingSize = 0;
    readonly byte _connectionAuth = 0;
    readonly string? _connectionAuthDesc;
    readonly int _certificateId = 0;
    readonly byte _encryptionAlgorithm = 0;
    readonly string? _encryptionAlgorithmDesc;

    public ServiceBrokerEndpointsDataType( )
    {
    }

    public ServiceBrokerEndpointsDataType(string name,
        int endpointId,
        int? principalId,
        byte protocol,
        string? protocolDesc,
        byte type,
        string? typeDesc,
        byte? state,
        string? stateDesc,
        bool isAdminEndpoint,
        bool isMessageForwardingEnabled,
        int messageForwardingSize,
        byte connectionAuth,
        string? connectionAuthDesc,
        int certificateId,
        byte encryptionAlgorithm,
        string? encryptionAlgorithmDesc)
    {
        _name = name;
        _endpointId = endpointId;
        _principalId = principalId;
        _protocol = protocol;
        _protocolDesc = protocolDesc;
        _type = type;
        _typeDesc = typeDesc;
        _state = state;
        _stateDesc = stateDesc;
        _isAdminEndpoint = isAdminEndpoint;
        _isMessageForwardingEnabled = isMessageForwardingEnabled;
        _messageForwardingSize = messageForwardingSize;
        _connectionAuth = connectionAuth;
        _connectionAuthDesc = connectionAuthDesc;
        _certificateId = certificateId;
        _encryptionAlgorithm = encryptionAlgorithm;
        _encryptionAlgorithmDesc = encryptionAlgorithmDesc;
    }

    public string Name => _name;
    public int EndpointId => _endpointId;
    public int? PrincipalId => _principalId;
    public byte Protocol => _protocol;
    public string? ProtocolDesc => _protocolDesc;
    public byte Type => _type;
    public string? TypeDesc => _typeDesc;
    public byte? State => _state;
    public string? StateDesc => _stateDesc;
    public bool IsAdminEndpoint => _isAdminEndpoint;
    public bool IsMessageForwardingEnabled => _isMessageForwardingEnabled;
    public int MessageForwardingSize => _messageForwardingSize;
    public byte ConnectionAuth => _connectionAuth;
    public string? ConnectionAuthDesc => _connectionAuthDesc;
    public int CertificateId => _certificateId;
    public byte EncryptionAlgorithm => _encryptionAlgorithm;
    public string? EncryptionAlgorithmDesc => _encryptionAlgorithmDesc;
}
