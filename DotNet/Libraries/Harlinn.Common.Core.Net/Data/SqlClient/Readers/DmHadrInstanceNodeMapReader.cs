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

public class DmHadrInstanceNodeMapReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_instance_node_map]";
    public const string TableName = "dm_hadr_instance_node_map";
    public const string ShortName = "dhinm";
    public const string Sql = """
        SELECT
          dhinm.[ag_resource_id],
          dhinm.[instance_name],
          dhinm.[node_name]
        FROM
          [sys].[dm_hadr_instance_node_map] dhinm
        """;

    public const int AGRESOURCEID_FIELD_ID = 0;
    public const int INSTANCENAME_FIELD_ID = 1;
    public const int NODENAME_FIELD_ID = 2;


    public DmHadrInstanceNodeMapReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrInstanceNodeMapReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrInstanceNodeMapReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string AgResourceId
    {
        get
        {
            return base.GetString(AGRESOURCEID_FIELD_ID);
        }
    }

    public string InstanceName
    {
        get
        {
            return base.GetString(INSTANCENAME_FIELD_ID);
        }
    }

    public string NodeName
    {
        get
        {
            return base.GetString(NODENAME_FIELD_ID);
        }
    }


    public Types.DmHadrInstanceNodeMapDataType ToDataObject()
    {
        return new Types.DmHadrInstanceNodeMapDataType(AgResourceId,
            InstanceName,
            NodeName);
    }

    public List<Types.DmHadrInstanceNodeMapDataType> ToList()
    {
        var list = new List<Types.DmHadrInstanceNodeMapDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
