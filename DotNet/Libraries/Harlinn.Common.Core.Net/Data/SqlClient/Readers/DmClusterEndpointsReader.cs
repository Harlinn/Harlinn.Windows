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

public class DmClusterEndpointsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cluster_endpoints]";
    public const string TableName = "dm_cluster_endpoints";
    public const string ShortName = "dce0";
    public const string Sql = """
        SELECT
          dce0.[Name],
          dce0.[Description],
          dce0.[Endpoint],
          dce0.[protocol_desc]
        FROM
          [sys].[dm_cluster_endpoints] dce0
        """;

    public const int NAME_FIELD_ID = 0;
    public const int DESCRIPTION_FIELD_ID = 1;
    public const int ENDPOINT_FIELD_ID = 2;
    public const int PROTOCOLDESC_FIELD_ID = 3;


    public DmClusterEndpointsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmClusterEndpointsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmClusterEndpointsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string Description
    {
        get
        {
            return base.GetString(DESCRIPTION_FIELD_ID);
        }
    }

    public string Endpoint
    {
        get
        {
            return base.GetString(ENDPOINT_FIELD_ID);
        }
    }

    public string? ProtocolDesc
    {
        get
        {
            return base.GetNullableString(PROTOCOLDESC_FIELD_ID);
        }
    }


    public Types.DmClusterEndpointsDataType ToDataObject()
    {
        return new Types.DmClusterEndpointsDataType(Name,
            Description,
            Endpoint,
            ProtocolDesc);
    }

    public List<Types.DmClusterEndpointsDataType> ToList()
    {
        var list = new List<Types.DmClusterEndpointsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
