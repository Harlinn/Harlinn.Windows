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

public class AvailabilityGroupListenersDataType
{
    readonly Guid _groupId;
    readonly string? _listenerId;
    readonly string? _dnsName;
    readonly int? _port;
    readonly bool _isConformant = false;
    readonly string? _ipConfigurationStringFromCluster;

    public AvailabilityGroupListenersDataType( )
    {
    }

    public AvailabilityGroupListenersDataType(Guid groupId,
        string? listenerId,
        string? dnsName,
        int? port,
        bool isConformant,
        string? ipConfigurationStringFromCluster)
    {
        _groupId = groupId;
        _listenerId = listenerId;
        _dnsName = dnsName;
        _port = port;
        _isConformant = isConformant;
        _ipConfigurationStringFromCluster = ipConfigurationStringFromCluster;
    }

    public Guid GroupId => _groupId;
    public string? ListenerId => _listenerId;
    public string? DnsName => _dnsName;
    public int? Port => _port;
    public bool IsConformant => _isConformant;
    public string? IpConfigurationStringFromCluster => _ipConfigurationStringFromCluster;
}
