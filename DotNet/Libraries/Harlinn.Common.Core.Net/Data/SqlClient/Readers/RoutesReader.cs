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

public class RoutesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[routes]";
    public const string TableName = "routes";
    public const string ShortName = "r";
    public const string Sql = """
        SELECT
          r.[Name],
          r.[route_id],
          r.[principal_id],
          r.[remote_service_name],
          r.[broker_instance],
          r.[Lifetime],
          r.[Address],
          r.[mirror_address]
        FROM
          [sys].[routes] r
        """;

    public const int NAME_FIELD_ID = 0;
    public const int ROUTEID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int REMOTESERVICENAME_FIELD_ID = 3;
    public const int BROKERINSTANCE_FIELD_ID = 4;
    public const int LIFETIME_FIELD_ID = 5;
    public const int ADDRESS_FIELD_ID = 6;
    public const int MIRRORADDRESS_FIELD_ID = 7;


    public RoutesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RoutesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RoutesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int RouteId
    {
        get
        {
            return base.GetInt32(ROUTEID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public string? RemoteServiceName
    {
        get
        {
            return base.GetNullableString(REMOTESERVICENAME_FIELD_ID);
        }
    }

    public string? BrokerInstance
    {
        get
        {
            return base.GetNullableString(BROKERINSTANCE_FIELD_ID);
        }
    }

    public DateTime? Lifetime
    {
        get
        {
            return base.GetNullableDateTime(LIFETIME_FIELD_ID);
        }
    }

    public string? Address
    {
        get
        {
            return base.GetNullableString(ADDRESS_FIELD_ID);
        }
    }

    public string? MirrorAddress
    {
        get
        {
            return base.GetNullableString(MIRRORADDRESS_FIELD_ID);
        }
    }


    public Types.RoutesDataType ToDataObject()
    {
        return new Types.RoutesDataType(Name,
            RouteId,
            PrincipalId,
            RemoteServiceName,
            BrokerInstance,
            Lifetime,
            Address,
            MirrorAddress);
    }

    public List<Types.RoutesDataType> ToList()
    {
        var list = new List<Types.RoutesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
