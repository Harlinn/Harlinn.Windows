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

public class DmOsMemoryNodeAccessStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_node_access_stats]";
    public const string TableName = "dm_os_memory_node_access_stats";
    public const string ShortName = "domnas";
    public const string Sql = """
        SELECT
          domnas.[local_node],
          domnas.[remote_node],
          domnas.[page_class],
          domnas.[read_count],
          domnas.[write_count]
        FROM
          [sys].[dm_os_memory_node_access_stats] domnas
        """;

    public const int LOCALNODE_FIELD_ID = 0;
    public const int REMOTENODE_FIELD_ID = 1;
    public const int PAGECLASS_FIELD_ID = 2;
    public const int READCOUNT_FIELD_ID = 3;
    public const int WRITECOUNT_FIELD_ID = 4;


    public DmOsMemoryNodeAccessStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryNodeAccessStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryNodeAccessStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? LocalNode
    {
        get
        {
            return base.GetNullableInt32(LOCALNODE_FIELD_ID);
        }
    }

    public int? RemoteNode
    {
        get
        {
            return base.GetNullableInt32(REMOTENODE_FIELD_ID);
        }
    }

    public string? PageClass
    {
        get
        {
            return base.GetNullableString(PAGECLASS_FIELD_ID);
        }
    }

    public long? ReadCount
    {
        get
        {
            return base.GetNullableInt64(READCOUNT_FIELD_ID);
        }
    }

    public long? WriteCount
    {
        get
        {
            return base.GetNullableInt64(WRITECOUNT_FIELD_ID);
        }
    }


    public Types.DmOsMemoryNodeAccessStatsDataType ToDataObject()
    {
        return new Types.DmOsMemoryNodeAccessStatsDataType(LocalNode,
            RemoteNode,
            PageClass,
            ReadCount,
            WriteCount);
    }

    public List<Types.DmOsMemoryNodeAccessStatsDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryNodeAccessStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
