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

public class DmBrokerForwardedMessagesDataType
{
    readonly Guid? _conversationId;
    readonly bool? _isInitiator;
    readonly string? _toServiceName;
    readonly string? _toBrokerInstance;
    readonly string? _fromServiceName;
    readonly string? _fromBrokerInstance;
    readonly string? _adjacentBrokerAddress;
    readonly long? _messageSequenceNumber;
    readonly int? _messageFragmentNumber;
    readonly byte? _hopsRemaining;
    readonly int? _timeToLive;
    readonly int? _timeConsumed;
    readonly Guid? _messageId;

    public DmBrokerForwardedMessagesDataType( )
    {
    }

    public DmBrokerForwardedMessagesDataType(Guid? conversationId,
        bool? isInitiator,
        string? toServiceName,
        string? toBrokerInstance,
        string? fromServiceName,
        string? fromBrokerInstance,
        string? adjacentBrokerAddress,
        long? messageSequenceNumber,
        int? messageFragmentNumber,
        byte? hopsRemaining,
        int? timeToLive,
        int? timeConsumed,
        Guid? messageId)
    {
        _conversationId = conversationId;
        _isInitiator = isInitiator;
        _toServiceName = toServiceName;
        _toBrokerInstance = toBrokerInstance;
        _fromServiceName = fromServiceName;
        _fromBrokerInstance = fromBrokerInstance;
        _adjacentBrokerAddress = adjacentBrokerAddress;
        _messageSequenceNumber = messageSequenceNumber;
        _messageFragmentNumber = messageFragmentNumber;
        _hopsRemaining = hopsRemaining;
        _timeToLive = timeToLive;
        _timeConsumed = timeConsumed;
        _messageId = messageId;
    }

    public Guid? ConversationId => _conversationId;
    public bool? IsInitiator => _isInitiator;
    public string? ToServiceName => _toServiceName;
    public string? ToBrokerInstance => _toBrokerInstance;
    public string? FromServiceName => _fromServiceName;
    public string? FromBrokerInstance => _fromBrokerInstance;
    public string? AdjacentBrokerAddress => _adjacentBrokerAddress;
    public long? MessageSequenceNumber => _messageSequenceNumber;
    public int? MessageFragmentNumber => _messageFragmentNumber;
    public byte? HopsRemaining => _hopsRemaining;
    public int? TimeToLive => _timeToLive;
    public int? TimeConsumed => _timeConsumed;
    public Guid? MessageId => _messageId;
}
