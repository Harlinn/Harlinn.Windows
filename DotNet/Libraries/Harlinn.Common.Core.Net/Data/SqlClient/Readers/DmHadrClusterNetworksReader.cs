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

public class DmHadrClusterNetworksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_cluster_networks]";
    public const string TableName = "dm_hadr_cluster_networks";
    public const string ShortName = "dhcn";
    public const string Sql = """
        SELECT
          dhcn.[member_name],
          dhcn.[network_subnet_ip],
          dhcn.[network_subnet_ipv4_mask],
          dhcn.[network_subnet_prefix_length],
          dhcn.[is_public],
          dhcn.[is_ipv4]
        FROM
          [sys].[dm_hadr_cluster_networks] dhcn
        """;

    public const int MEMBERNAME_FIELD_ID = 0;
    public const int NETWORKSUBNETIP_FIELD_ID = 1;
    public const int NETWORKSUBNETIPV4MASK_FIELD_ID = 2;
    public const int NETWORKSUBNETPREFIXLENGTH_FIELD_ID = 3;
    public const int ISPUBLIC_FIELD_ID = 4;
    public const int ISIPV4_FIELD_ID = 5;


    public DmHadrClusterNetworksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterNetworksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrClusterNetworksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string MemberName
    {
        get
        {
            return base.GetString(MEMBERNAME_FIELD_ID);
        }
    }

    public string NetworkSubnetIp
    {
        get
        {
            return base.GetString(NETWORKSUBNETIP_FIELD_ID);
        }
    }

    public string? NetworkSubnetIpv4Mask
    {
        get
        {
            return base.GetNullableString(NETWORKSUBNETIPV4MASK_FIELD_ID);
        }
    }

    public int? NetworkSubnetPrefixLength
    {
        get
        {
            return base.GetNullableInt32(NETWORKSUBNETPREFIXLENGTH_FIELD_ID);
        }
    }

    public bool IsPublic
    {
        get
        {
            return base.GetBoolean(ISPUBLIC_FIELD_ID);
        }
    }

    public bool IsIpv4
    {
        get
        {
            return base.GetBoolean(ISIPV4_FIELD_ID);
        }
    }


    public Types.DmHadrClusterNetworksDataType ToDataObject()
    {
        return new Types.DmHadrClusterNetworksDataType(MemberName,
            NetworkSubnetIp,
            NetworkSubnetIpv4Mask,
            NetworkSubnetPrefixLength,
            IsPublic,
            IsIpv4);
    }

    public List<Types.DmHadrClusterNetworksDataType> ToList()
    {
        var list = new List<Types.DmHadrClusterNetworksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
