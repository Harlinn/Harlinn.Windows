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

public class ConversationEndpointsDataType
{
    readonly Guid _conversationHandle;
    readonly Guid _conversationId;
    readonly bool _isInitiator = false;
    readonly int _serviceContractId = 0;
    readonly Guid _conversationGroupId;
    readonly int _serviceId = 0;
    readonly DateTime _lifetime;
    readonly string _state = string.Empty;
    readonly string? _stateDesc;
    readonly string _farService = string.Empty;
    readonly string? _farBrokerInstance;
    readonly int _principalId = 0;
    readonly int _farPrincipalId = 0;
    readonly Guid _outboundSessionKeyIdentifier;
    readonly Guid _inboundSessionKeyIdentifier;
    readonly DateTime _securityTimestamp;
    readonly DateTime _dialogTimer;
    readonly long _sendSequence = 0;
    readonly byte[] _lastSendTranId = Array.Empty<byte>();
    readonly long _endDialogSequence = 0;
    readonly long _receiveSequence = 0;
    readonly int _receiveSequenceFrag = 0;
    readonly long _systemSequence = 0;
    readonly long _firstOutOfOrderSequence = 0;
    readonly long _lastOutOfOrderSequence = 0;
    readonly int _lastOutOfOrderFrag = 0;
    readonly bool _isSystem = false;
    readonly byte _priority = 0;

    public ConversationEndpointsDataType( )
    {
    }

    public ConversationEndpointsDataType(Guid conversationHandle,
        Guid conversationId,
        bool isInitiator,
        int serviceContractId,
        Guid conversationGroupId,
        int serviceId,
        DateTime lifetime,
        string state,
        string? stateDesc,
        string farService,
        string? farBrokerInstance,
        int principalId,
        int farPrincipalId,
        Guid outboundSessionKeyIdentifier,
        Guid inboundSessionKeyIdentifier,
        DateTime securityTimestamp,
        DateTime dialogTimer,
        long sendSequence,
        byte[] lastSendTranId,
        long endDialogSequence,
        long receiveSequence,
        int receiveSequenceFrag,
        long systemSequence,
        long firstOutOfOrderSequence,
        long lastOutOfOrderSequence,
        int lastOutOfOrderFrag,
        bool isSystem,
        byte priority)
    {
        _conversationHandle = conversationHandle;
        _conversationId = conversationId;
        _isInitiator = isInitiator;
        _serviceContractId = serviceContractId;
        _conversationGroupId = conversationGroupId;
        _serviceId = serviceId;
        _lifetime = lifetime;
        _state = state;
        _stateDesc = stateDesc;
        _farService = farService;
        _farBrokerInstance = farBrokerInstance;
        _principalId = principalId;
        _farPrincipalId = farPrincipalId;
        _outboundSessionKeyIdentifier = outboundSessionKeyIdentifier;
        _inboundSessionKeyIdentifier = inboundSessionKeyIdentifier;
        _securityTimestamp = securityTimestamp;
        _dialogTimer = dialogTimer;
        _sendSequence = sendSequence;
        _lastSendTranId = lastSendTranId;
        _endDialogSequence = endDialogSequence;
        _receiveSequence = receiveSequence;
        _receiveSequenceFrag = receiveSequenceFrag;
        _systemSequence = systemSequence;
        _firstOutOfOrderSequence = firstOutOfOrderSequence;
        _lastOutOfOrderSequence = lastOutOfOrderSequence;
        _lastOutOfOrderFrag = lastOutOfOrderFrag;
        _isSystem = isSystem;
        _priority = priority;
    }

    public Guid ConversationHandle => _conversationHandle;
    public Guid ConversationId => _conversationId;
    public bool IsInitiator => _isInitiator;
    public int ServiceContractId => _serviceContractId;
    public Guid ConversationGroupId => _conversationGroupId;
    public int ServiceId => _serviceId;
    public DateTime Lifetime => _lifetime;
    public string State => _state;
    public string? StateDesc => _stateDesc;
    public string FarService => _farService;
    public string? FarBrokerInstance => _farBrokerInstance;
    public int PrincipalId => _principalId;
    public int FarPrincipalId => _farPrincipalId;
    public Guid OutboundSessionKeyIdentifier => _outboundSessionKeyIdentifier;
    public Guid InboundSessionKeyIdentifier => _inboundSessionKeyIdentifier;
    public DateTime SecurityTimestamp => _securityTimestamp;
    public DateTime DialogTimer => _dialogTimer;
    public long SendSequence => _sendSequence;
    public byte[] LastSendTranId => _lastSendTranId;
    public long EndDialogSequence => _endDialogSequence;
    public long ReceiveSequence => _receiveSequence;
    public int ReceiveSequenceFrag => _receiveSequenceFrag;
    public long SystemSequence => _systemSequence;
    public long FirstOutOfOrderSequence => _firstOutOfOrderSequence;
    public long LastOutOfOrderSequence => _lastOutOfOrderSequence;
    public int LastOutOfOrderFrag => _lastOutOfOrderFrag;
    public bool IsSystem => _isSystem;
    public byte Priority => _priority;
}
