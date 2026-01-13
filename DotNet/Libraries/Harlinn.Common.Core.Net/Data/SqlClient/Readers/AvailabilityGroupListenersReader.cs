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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class AvailabilityGroupListenersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_group_listeners]";
    public const string TableName = "availability_group_listeners";
    public const string ShortName = "agl";
    public const string Sql = """
        SELECT
          agl.[group_id],
          agl.[listener_id],
          agl.[dns_name],
          agl.[Port],
          agl.[is_conformant],
          agl.[ip_configuration_string_from_cluster]
        FROM
          [sys].[availability_group_listeners] agl
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int LISTENERID_FIELD_ID = 1;
    public const int DNSNAME_FIELD_ID = 2;
    public const int PORT_FIELD_ID = 3;
    public const int ISCONFORMANT_FIELD_ID = 4;
    public const int IPCONFIGURATIONSTRINGFROMCLUSTER_FIELD_ID = 5;


    public AvailabilityGroupListenersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupListenersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupListenersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public string? ListenerId
    {
        get
        {
            return base.GetNullableString(LISTENERID_FIELD_ID);
        }
    }

    public string? DnsName
    {
        get
        {
            return base.GetNullableString(DNSNAME_FIELD_ID);
        }
    }

    public int? Port
    {
        get
        {
            return base.GetNullableInt32(PORT_FIELD_ID);
        }
    }

    public bool IsConformant
    {
        get
        {
            return base.GetBoolean(ISCONFORMANT_FIELD_ID);
        }
    }

    public string? IpConfigurationStringFromCluster
    {
        get
        {
            return base.GetNullableString(IPCONFIGURATIONSTRINGFROMCLUSTER_FIELD_ID);
        }
    }


    public Types.AvailabilityGroupListenersDataType ToDataObject()
    {
        return new Types.AvailabilityGroupListenersDataType(GroupId,
            ListenerId,
            DnsName,
            Port,
            IsConformant,
            IpConfigurationStringFromCluster);
    }

    public List<Types.AvailabilityGroupListenersDataType> ToList()
    {
        var list = new List<Types.AvailabilityGroupListenersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
