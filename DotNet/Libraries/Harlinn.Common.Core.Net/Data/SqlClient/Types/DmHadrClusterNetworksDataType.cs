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

public class DmHadrClusterNetworksDataType
{
    readonly string _memberName = string.Empty;
    readonly string _networkSubnetIp = string.Empty;
    readonly string? _networkSubnetIpv4Mask;
    readonly int? _networkSubnetPrefixLength;
    readonly bool _isPublic = false;
    readonly bool _isIpv4 = false;

    public DmHadrClusterNetworksDataType( )
    {
    }

    public DmHadrClusterNetworksDataType(string memberName,
        string networkSubnetIp,
        string? networkSubnetIpv4Mask,
        int? networkSubnetPrefixLength,
        bool isPublic,
        bool isIpv4)
    {
        _memberName = memberName;
        _networkSubnetIp = networkSubnetIp;
        _networkSubnetIpv4Mask = networkSubnetIpv4Mask;
        _networkSubnetPrefixLength = networkSubnetPrefixLength;
        _isPublic = isPublic;
        _isIpv4 = isIpv4;
    }

    public string MemberName => _memberName;
    public string NetworkSubnetIp => _networkSubnetIp;
    public string? NetworkSubnetIpv4Mask => _networkSubnetIpv4Mask;
    public int? NetworkSubnetPrefixLength => _networkSubnetPrefixLength;
    public bool IsPublic => _isPublic;
    public bool IsIpv4 => _isIpv4;
}
