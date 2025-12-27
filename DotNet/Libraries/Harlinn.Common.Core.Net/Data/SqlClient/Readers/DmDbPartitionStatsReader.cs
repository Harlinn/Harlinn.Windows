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

public class DmDbPartitionStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_partition_stats]";
    public const string TableName = "dm_db_partition_stats";
    public const string ShortName = "ddps";
    public const string Sql = """
        SELECT
          ddps.[partition_id],
          ddps.[object_id],
          ddps.[index_id],
          ddps.[partition_number],
          ddps.[in_row_data_page_count],
          ddps.[in_row_used_page_count],
          ddps.[in_row_reserved_page_count],
          ddps.[lob_used_page_count],
          ddps.[lob_reserved_page_count],
          ddps.[row_overflow_used_page_count],
          ddps.[row_overflow_reserved_page_count],
          ddps.[used_page_count],
          ddps.[reserved_page_count],
          ddps.[row_count]
        FROM
          [sys].[dm_db_partition_stats] ddps
        """;

    public const int PARTITIONID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int PARTITIONNUMBER_FIELD_ID = 3;
    public const int INROWDATAPAGECOUNT_FIELD_ID = 4;
    public const int INROWUSEDPAGECOUNT_FIELD_ID = 5;
    public const int INROWRESERVEDPAGECOUNT_FIELD_ID = 6;
    public const int LOBUSEDPAGECOUNT_FIELD_ID = 7;
    public const int LOBRESERVEDPAGECOUNT_FIELD_ID = 8;
    public const int ROWOVERFLOWUSEDPAGECOUNT_FIELD_ID = 9;
    public const int ROWOVERFLOWRESERVEDPAGECOUNT_FIELD_ID = 10;
    public const int USEDPAGECOUNT_FIELD_ID = 11;
    public const int RESERVEDPAGECOUNT_FIELD_ID = 12;
    public const int ROWCOUNT_FIELD_ID = 13;


    public DmDbPartitionStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbPartitionStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbPartitionStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? PartitionId
    {
        get
        {
            return base.GetNullableInt64(PARTITIONID_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public int PartitionNumber
    {
        get
        {
            return base.GetInt32(PARTITIONNUMBER_FIELD_ID);
        }
    }

    public long? InRowDataPageCount
    {
        get
        {
            return base.GetNullableInt64(INROWDATAPAGECOUNT_FIELD_ID);
        }
    }

    public long? InRowUsedPageCount
    {
        get
        {
            return base.GetNullableInt64(INROWUSEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? InRowReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(INROWRESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? LobUsedPageCount
    {
        get
        {
            return base.GetNullableInt64(LOBUSEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? LobReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(LOBRESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? RowOverflowUsedPageCount
    {
        get
        {
            return base.GetNullableInt64(ROWOVERFLOWUSEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? RowOverflowReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(ROWOVERFLOWRESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? UsedPageCount
    {
        get
        {
            return base.GetNullableInt64(USEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? ReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(RESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? RowCount
    {
        get
        {
            return base.GetNullableInt64(ROWCOUNT_FIELD_ID);
        }
    }


    public Types.DmDbPartitionStatsDataType ToDataObject()
    {
        return new Types.DmDbPartitionStatsDataType(PartitionId,
            ObjectId,
            IndexId,
            PartitionNumber,
            InRowDataPageCount,
            InRowUsedPageCount,
            InRowReservedPageCount,
            LobUsedPageCount,
            LobReservedPageCount,
            RowOverflowUsedPageCount,
            RowOverflowReservedPageCount,
            UsedPageCount,
            ReservedPageCount,
            RowCount);
    }

    public List<Types.DmDbPartitionStatsDataType> ToList()
    {
        var list = new List<Types.DmDbPartitionStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
