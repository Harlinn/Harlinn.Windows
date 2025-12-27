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

public class ServicesDataType
{
    readonly string _name = string.Empty;
    readonly int _serviceId = 0;
    readonly int? _principalId;
    readonly int _serviceQueueId = 0;

    public ServicesDataType( )
    {
    }

    public ServicesDataType(string name,
        int serviceId,
        int? principalId,
        int serviceQueueId)
    {
        _name = name;
        _serviceId = serviceId;
        _principalId = principalId;
        _serviceQueueId = serviceQueueId;
    }

    public string Name => _name;
    public int ServiceId => _serviceId;
    public int? PrincipalId => _principalId;
    public int ServiceQueueId => _serviceQueueId;
}
