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

/// <summary>
/// Represents a message queued for transmission in a service broker or messaging system, including metadata such as
/// conversation handle, service names, message body, and status information.
/// </summary>
/// <remarks>
/// Use this class to encapsulate all relevant details of a message pending transmission between
/// services, including routing, sequencing, and status flags. Instances are typically created to track or inspect
/// messages as they move through the transmission pipeline.</remarks>
public class TransmissionQueue
{
    readonly Guid _conversationHandle;
    readonly string? _toServiceName;
    readonly string? _toBrokerInstance;
    readonly string? _fromServiceName;
    readonly string? _serviceContractName;
    readonly DateTime _enqueueTime;
    readonly long _messageSequenceNumber = 0;
    readonly string? _messageTypeName;
    readonly bool _isConversationError = false;
    readonly bool _isEndOfDialog = false;
    readonly byte[]? _messageBody;
    readonly string? _transmissionStatus;
    readonly byte _priority = 0;

    public TransmissionQueue( )
    {
    }

    public TransmissionQueue(Guid conversationHandle,
        string? toServiceName,
        string? toBrokerInstance,
        string? fromServiceName,
        string? serviceContractName,
        DateTime enqueueTime,
        long messageSequenceNumber,
        string? messageTypeName,
        bool isConversationError,
        bool isEndOfDialog,
        byte[]? messageBody,
        string? transmissionStatus,
        byte priority)
    {
        _conversationHandle = conversationHandle;
        _toServiceName = toServiceName;
        _toBrokerInstance = toBrokerInstance;
        _fromServiceName = fromServiceName;
        _serviceContractName = serviceContractName;
        _enqueueTime = enqueueTime;
        _messageSequenceNumber = messageSequenceNumber;
        _messageTypeName = messageTypeName;
        _isConversationError = isConversationError;
        _isEndOfDialog = isEndOfDialog;
        _messageBody = messageBody;
        _transmissionStatus = transmissionStatus;
        _priority = priority;
    }

    public Guid ConversationHandle => _conversationHandle;
    public string? ToServiceName => _toServiceName;
    public string? ToBrokerInstance => _toBrokerInstance;
    public string? FromServiceName => _fromServiceName;
    public string? ServiceContractName => _serviceContractName;
    public DateTime EnqueueTime => _enqueueTime;
    public long MessageSequenceNumber => _messageSequenceNumber;
    public string? MessageTypeName => _messageTypeName;
    public bool IsConversationError => _isConversationError;
    public bool IsEndOfDialog => _isEndOfDialog;
    public byte[]? MessageBody => _messageBody;
    public string? TransmissionStatus => _transmissionStatus;
    public byte Priority => _priority;
}
