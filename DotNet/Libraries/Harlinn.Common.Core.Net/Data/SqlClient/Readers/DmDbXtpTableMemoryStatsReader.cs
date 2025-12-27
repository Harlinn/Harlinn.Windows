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

public class DmDbXtpTableMemoryStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_table_memory_stats]";
    public const string TableName = "dm_db_xtp_table_memory_stats";
    public const string ShortName = "ddxtms";
    public const string Sql = """
        SELECT
          ddxtms.[object_id],
          ddxtms.[memory_allocated_for_table_kb],
          ddxtms.[memory_used_by_table_kb],
          ddxtms.[memory_allocated_for_indexes_kb],
          ddxtms.[memory_used_by_indexes_kb]
        FROM
          [sys].[dm_db_xtp_table_memory_stats] ddxtms
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int MEMORYALLOCATEDFORTABLEKB_FIELD_ID = 1;
    public const int MEMORYUSEDBYTABLEKB_FIELD_ID = 2;
    public const int MEMORYALLOCATEDFORINDEXESKB_FIELD_ID = 3;
    public const int MEMORYUSEDBYINDEXESKB_FIELD_ID = 4;


    public DmDbXtpTableMemoryStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpTableMemoryStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpTableMemoryStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ObjectId
    {
        get
        {
            return base.GetNullableInt32(OBJECTID_FIELD_ID);
        }
    }

    public long? MemoryAllocatedForTableKb
    {
        get
        {
            return base.GetNullableInt64(MEMORYALLOCATEDFORTABLEKB_FIELD_ID);
        }
    }

    public long? MemoryUsedByTableKb
    {
        get
        {
            return base.GetNullableInt64(MEMORYUSEDBYTABLEKB_FIELD_ID);
        }
    }

    public long? MemoryAllocatedForIndexesKb
    {
        get
        {
            return base.GetNullableInt64(MEMORYALLOCATEDFORINDEXESKB_FIELD_ID);
        }
    }

    public long? MemoryUsedByIndexesKb
    {
        get
        {
            return base.GetNullableInt64(MEMORYUSEDBYINDEXESKB_FIELD_ID);
        }
    }


    public Types.DmDbXtpTableMemoryStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpTableMemoryStatsDataType(ObjectId,
            MemoryAllocatedForTableKb,
            MemoryUsedByTableKb,
            MemoryAllocatedForIndexesKb,
            MemoryUsedByIndexesKb);
    }

    public List<Types.DmDbXtpTableMemoryStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpTableMemoryStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
