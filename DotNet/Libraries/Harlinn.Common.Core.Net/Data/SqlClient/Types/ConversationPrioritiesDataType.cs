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

public class ConversationPrioritiesDataType
{
    readonly int _priorityId = 0;
    readonly string _name = string.Empty;
    readonly int? _serviceContractId;
    readonly int? _localServiceId;
    readonly string? _remoteServiceName;
    readonly byte _priority = 0;

    public ConversationPrioritiesDataType( )
    {
    }

    public ConversationPrioritiesDataType(int priorityId,
        string name,
        int? serviceContractId,
        int? localServiceId,
        string? remoteServiceName,
        byte priority)
    {
        _priorityId = priorityId;
        _name = name;
        _serviceContractId = serviceContractId;
        _localServiceId = localServiceId;
        _remoteServiceName = remoteServiceName;
        _priority = priority;
    }

    public int PriorityId => _priorityId;
    public string Name => _name;
    public int? ServiceContractId => _serviceContractId;
    public int? LocalServiceId => _localServiceId;
    public string? RemoteServiceName => _remoteServiceName;
    public byte Priority => _priority;
}
