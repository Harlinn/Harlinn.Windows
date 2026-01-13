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

public class DmOsClusterNodesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_cluster_nodes]";
    public const string TableName = "dm_os_cluster_nodes";
    public const string ShortName = "docn";
    public const string Sql = """
        SELECT
          docn.[Nodename],
          docn.[Status],
          docn.[status_description],
          docn.[is_current_owner]
        FROM
          [sys].[dm_os_cluster_nodes] docn
        """;

    public const int NODENAME_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int STATUSDESCRIPTION_FIELD_ID = 2;
    public const int ISCURRENTOWNER_FIELD_ID = 3;


    public DmOsClusterNodesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsClusterNodesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsClusterNodesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Nodename
    {
        get
        {
            return base.GetNullableString(NODENAME_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public string StatusDescription
    {
        get
        {
            return base.GetString(STATUSDESCRIPTION_FIELD_ID);
        }
    }

    public bool? IsCurrentOwner
    {
        get
        {
            return base.GetNullableBoolean(ISCURRENTOWNER_FIELD_ID);
        }
    }


    public Types.DmOsClusterNodesDataType ToDataObject()
    {
        return new Types.DmOsClusterNodesDataType(Nodename,
            Status,
            StatusDescription,
            IsCurrentOwner);
    }

    public List<Types.DmOsClusterNodesDataType> ToList()
    {
        var list = new List<Types.DmOsClusterNodesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
