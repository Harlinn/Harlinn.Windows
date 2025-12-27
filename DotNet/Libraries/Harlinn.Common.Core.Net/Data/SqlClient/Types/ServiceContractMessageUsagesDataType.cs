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

public class ServiceContractMessageUsagesDataType
{
    readonly int _serviceContractId = 0;
    readonly int _messageTypeId = 0;
    readonly bool _isSentByInitiator = false;
    readonly bool _isSentByTarget = false;

    public ServiceContractMessageUsagesDataType( )
    {
    }

    public ServiceContractMessageUsagesDataType(int serviceContractId,
        int messageTypeId,
        bool isSentByInitiator,
        bool isSentByTarget)
    {
        _serviceContractId = serviceContractId;
        _messageTypeId = messageTypeId;
        _isSentByInitiator = isSentByInitiator;
        _isSentByTarget = isSentByTarget;
    }

    public int ServiceContractId => _serviceContractId;
    public int MessageTypeId => _messageTypeId;
    public bool IsSentByInitiator => _isSentByInitiator;
    public bool IsSentByTarget => _isSentByTarget;
}
