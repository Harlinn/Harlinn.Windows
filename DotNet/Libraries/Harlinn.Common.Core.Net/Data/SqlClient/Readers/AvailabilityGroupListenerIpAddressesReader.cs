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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class AvailabilityGroupListenerIpAddressesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_group_listener_ip_addresses]";
    public const string TableName = "availability_group_listener_ip_addresses";
    public const string ShortName = "aglia";
    public const string Sql = """
        SELECT
          aglia.[listener_id],
          aglia.[ip_address],
          aglia.[ip_subnet_mask],
          aglia.[is_dhcp],
          aglia.[network_subnet_ip],
          aglia.[network_subnet_prefix_length],
          aglia.[network_subnet_ipv4_mask],
          aglia.[State],
          aglia.[state_desc]
        FROM
          [sys].[availability_group_listener_ip_addresses] aglia
        """;

    public const int LISTENERID_FIELD_ID = 0;
    public const int IPADDRESS_FIELD_ID = 1;
    public const int IPSUBNETMASK_FIELD_ID = 2;
    public const int ISDHCP_FIELD_ID = 3;
    public const int NETWORKSUBNETIP_FIELD_ID = 4;
    public const int NETWORKSUBNETPREFIXLENGTH_FIELD_ID = 5;
    public const int NETWORKSUBNETIPV4MASK_FIELD_ID = 6;
    public const int STATE_FIELD_ID = 7;
    public const int STATEDESC_FIELD_ID = 8;


    public AvailabilityGroupListenerIpAddressesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupListenerIpAddressesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupListenerIpAddressesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ListenerId
    {
        get
        {
            return base.GetNullableString(LISTENERID_FIELD_ID);
        }
    }

    public string? IpAddress
    {
        get
        {
            return base.GetNullableString(IPADDRESS_FIELD_ID);
        }
    }

    public string? IpSubnetMask
    {
        get
        {
            return base.GetNullableString(IPSUBNETMASK_FIELD_ID);
        }
    }

    public bool IsDhcp
    {
        get
        {
            return base.GetBoolean(ISDHCP_FIELD_ID);
        }
    }

    public string? NetworkSubnetIp
    {
        get
        {
            return base.GetNullableString(NETWORKSUBNETIP_FIELD_ID);
        }
    }

    public int? NetworkSubnetPrefixLength
    {
        get
        {
            return base.GetNullableInt32(NETWORKSUBNETPREFIXLENGTH_FIELD_ID);
        }
    }

    public string? NetworkSubnetIpv4Mask
    {
        get
        {
            return base.GetNullableString(NETWORKSUBNETIPV4MASK_FIELD_ID);
        }
    }

    public byte? State
    {
        get
        {
            return base.GetNullableByte(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }


    public Types.AvailabilityGroupListenerIpAddressesDataType ToDataObject()
    {
        return new Types.AvailabilityGroupListenerIpAddressesDataType(ListenerId,
            IpAddress,
            IpSubnetMask,
            IsDhcp,
            NetworkSubnetIp,
            NetworkSubnetPrefixLength,
            NetworkSubnetIpv4Mask,
            State,
            StateDesc);
    }

    public List<Types.AvailabilityGroupListenerIpAddressesDataType> ToList()
    {
        var list = new List<Types.AvailabilityGroupListenerIpAddressesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
