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

public class DmDbColumnStoreRowGroupOperationalStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_column_store_row_group_operational_stats]";
    public const string TableName = "dm_db_column_store_row_group_operational_stats";
    public const string ShortName = "ddcsrgos";
    public const string Sql = """
        SELECT
          ddcsrgos.[object_id],
          ddcsrgos.[index_id],
          ddcsrgos.[partition_number],
          ddcsrgos.[row_group_id],
          ddcsrgos.[index_scan_count],
          ddcsrgos.[scan_count],
          ddcsrgos.[delete_buffer_scan_count],
          ddcsrgos.[row_group_lock_count],
          ddcsrgos.[row_group_lock_wait_count],
          ddcsrgos.[row_group_lock_wait_in_ms],
          ddcsrgos.[returned_row_count],
          ddcsrgos.[returned_aggregate_count],
          ddcsrgos.[returned_group_count],
          ddcsrgos.[input_groupby_row_count]
        FROM
          [sys].[dm_db_column_store_row_group_operational_stats] ddcsrgos
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int PARTITIONNUMBER_FIELD_ID = 2;
    public const int ROWGROUPID_FIELD_ID = 3;
    public const int INDEXSCANCOUNT_FIELD_ID = 4;
    public const int SCANCOUNT_FIELD_ID = 5;
    public const int DELETEBUFFERSCANCOUNT_FIELD_ID = 6;
    public const int ROWGROUPLOCKCOUNT_FIELD_ID = 7;
    public const int ROWGROUPLOCKWAITCOUNT_FIELD_ID = 8;
    public const int ROWGROUPLOCKWAITINMS_FIELD_ID = 9;
    public const int RETURNEDROWCOUNT_FIELD_ID = 10;
    public const int RETURNEDAGGREGATECOUNT_FIELD_ID = 11;
    public const int RETURNEDGROUPCOUNT_FIELD_ID = 12;
    public const int INPUTGROUPBYROWCOUNT_FIELD_ID = 13;


    public DmDbColumnStoreRowGroupOperationalStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbColumnStoreRowGroupOperationalStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbColumnStoreRowGroupOperationalStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
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

    public int RowGroupId
    {
        get
        {
            return base.GetInt32(ROWGROUPID_FIELD_ID);
        }
    }

    public long IndexScanCount
    {
        get
        {
            return base.GetInt64(INDEXSCANCOUNT_FIELD_ID);
        }
    }

    public long ScanCount
    {
        get
        {
            return base.GetInt64(SCANCOUNT_FIELD_ID);
        }
    }

    public long DeleteBufferScanCount
    {
        get
        {
            return base.GetInt64(DELETEBUFFERSCANCOUNT_FIELD_ID);
        }
    }

    public long RowGroupLockCount
    {
        get
        {
            return base.GetInt64(ROWGROUPLOCKCOUNT_FIELD_ID);
        }
    }

    public long RowGroupLockWaitCount
    {
        get
        {
            return base.GetInt64(ROWGROUPLOCKWAITCOUNT_FIELD_ID);
        }
    }

    public long RowGroupLockWaitInMs
    {
        get
        {
            return base.GetInt64(ROWGROUPLOCKWAITINMS_FIELD_ID);
        }
    }

    public long ReturnedRowCount
    {
        get
        {
            return base.GetInt64(RETURNEDROWCOUNT_FIELD_ID);
        }
    }

    public long ReturnedAggregateCount
    {
        get
        {
            return base.GetInt64(RETURNEDAGGREGATECOUNT_FIELD_ID);
        }
    }

    public long ReturnedGroupCount
    {
        get
        {
            return base.GetInt64(RETURNEDGROUPCOUNT_FIELD_ID);
        }
    }

    public long InputGroupbyRowCount
    {
        get
        {
            return base.GetInt64(INPUTGROUPBYROWCOUNT_FIELD_ID);
        }
    }


    public Types.DmDbColumnStoreRowGroupOperationalStatsDataType ToDataObject()
    {
        return new Types.DmDbColumnStoreRowGroupOperationalStatsDataType(ObjectId,
            IndexId,
            PartitionNumber,
            RowGroupId,
            IndexScanCount,
            ScanCount,
            DeleteBufferScanCount,
            RowGroupLockCount,
            RowGroupLockWaitCount,
            RowGroupLockWaitInMs,
            ReturnedRowCount,
            ReturnedAggregateCount,
            ReturnedGroupCount,
            InputGroupbyRowCount);
    }

    public List<Types.DmDbColumnStoreRowGroupOperationalStatsDataType> ToList()
    {
        var list = new List<Types.DmDbColumnStoreRowGroupOperationalStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
