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

public class DmIoClusterValidPathNamesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_io_cluster_valid_path_names]";
    public const string TableName = "dm_io_cluster_valid_path_names";
    public const string ShortName = "dicvpn";
    public const string Sql = """
        SELECT
          dicvpn.[path_name],
          dicvpn.[cluster_owner_node],
          dicvpn.[is_cluster_shared_volume]
        FROM
          [sys].[dm_io_cluster_valid_path_names] dicvpn
        """;

    public const int PATHNAME_FIELD_ID = 0;
    public const int CLUSTEROWNERNODE_FIELD_ID = 1;
    public const int ISCLUSTERSHAREDVOLUME_FIELD_ID = 2;


    public DmIoClusterValidPathNamesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmIoClusterValidPathNamesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmIoClusterValidPathNamesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? PathName
    {
        get
        {
            return base.GetNullableString(PATHNAME_FIELD_ID);
        }
    }

    public string? ClusterOwnerNode
    {
        get
        {
            return base.GetNullableString(CLUSTEROWNERNODE_FIELD_ID);
        }
    }

    public bool IsClusterSharedVolume
    {
        get
        {
            return base.GetBoolean(ISCLUSTERSHAREDVOLUME_FIELD_ID);
        }
    }


    public Types.DmIoClusterValidPathNamesDataType ToDataObject()
    {
        return new Types.DmIoClusterValidPathNamesDataType(PathName,
            ClusterOwnerNode,
            IsClusterSharedVolume);
    }

    public List<Types.DmIoClusterValidPathNamesDataType> ToList()
    {
        var list = new List<Types.DmIoClusterValidPathNamesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
