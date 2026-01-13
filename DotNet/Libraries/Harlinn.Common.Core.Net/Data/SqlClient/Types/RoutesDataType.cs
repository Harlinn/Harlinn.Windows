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

public class RoutesDataType
{
    readonly string _name = string.Empty;
    readonly int _routeId = 0;
    readonly int? _principalId;
    readonly string? _remoteServiceName;
    readonly string? _brokerInstance;
    readonly DateTime? _lifetime;
    readonly string? _address;
    readonly string? _mirrorAddress;

    public RoutesDataType( )
    {
    }

    public RoutesDataType(string name,
        int routeId,
        int? principalId,
        string? remoteServiceName,
        string? brokerInstance,
        DateTime? lifetime,
        string? address,
        string? mirrorAddress)
    {
        _name = name;
        _routeId = routeId;
        _principalId = principalId;
        _remoteServiceName = remoteServiceName;
        _brokerInstance = brokerInstance;
        _lifetime = lifetime;
        _address = address;
        _mirrorAddress = mirrorAddress;
    }

    public string Name => _name;
    public int RouteId => _routeId;
    public int? PrincipalId => _principalId;
    public string? RemoteServiceName => _remoteServiceName;
    public string? BrokerInstance => _brokerInstance;
    public DateTime? Lifetime => _lifetime;
    public string? Address => _address;
    public string? MirrorAddress => _mirrorAddress;
}
