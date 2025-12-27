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

public class AvailabilityGroupListenerIpAddressesDataType
{
    readonly string? _listenerId;
    readonly string? _ipAddress;
    readonly string? _ipSubnetMask;
    readonly bool _isDhcp = false;
    readonly string? _networkSubnetIp;
    readonly int? _networkSubnetPrefixLength;
    readonly string? _networkSubnetIpv4Mask;
    readonly byte? _state;
    readonly string? _stateDesc;

    public AvailabilityGroupListenerIpAddressesDataType( )
    {
    }

    public AvailabilityGroupListenerIpAddressesDataType(string? listenerId,
        string? ipAddress,
        string? ipSubnetMask,
        bool isDhcp,
        string? networkSubnetIp,
        int? networkSubnetPrefixLength,
        string? networkSubnetIpv4Mask,
        byte? state,
        string? stateDesc)
    {
        _listenerId = listenerId;
        _ipAddress = ipAddress;
        _ipSubnetMask = ipSubnetMask;
        _isDhcp = isDhcp;
        _networkSubnetIp = networkSubnetIp;
        _networkSubnetPrefixLength = networkSubnetPrefixLength;
        _networkSubnetIpv4Mask = networkSubnetIpv4Mask;
        _state = state;
        _stateDesc = stateDesc;
    }

    public string? ListenerId => _listenerId;
    public string? IpAddress => _ipAddress;
    public string? IpSubnetMask => _ipSubnetMask;
    public bool IsDhcp => _isDhcp;
    public string? NetworkSubnetIp => _networkSubnetIp;
    public int? NetworkSubnetPrefixLength => _networkSubnetPrefixLength;
    public string? NetworkSubnetIpv4Mask => _networkSubnetIpv4Mask;
    public byte? State => _state;
    public string? StateDesc => _stateDesc;
}
