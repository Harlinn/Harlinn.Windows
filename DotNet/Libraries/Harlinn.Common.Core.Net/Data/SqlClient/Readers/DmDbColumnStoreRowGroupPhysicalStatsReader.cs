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

public class DmDbColumnStoreRowGroupPhysicalStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_column_store_row_group_physical_stats]";
    public const string TableName = "dm_db_column_store_row_group_physical_stats";
    public const string ShortName = "ddcsrgps";
    public const string Sql = """
        SELECT
          ddcsrgps.[object_id],
          ddcsrgps.[index_id],
          ddcsrgps.[partition_number],
          ddcsrgps.[row_group_id],
          ddcsrgps.[delta_store_hobt_id],
          ddcsrgps.[State],
          ddcsrgps.[state_desc],
          ddcsrgps.[total_rows],
          ddcsrgps.[deleted_rows],
          ddcsrgps.[size_in_bytes],
          ddcsrgps.[trim_reason],
          ddcsrgps.[trim_reason_desc],
          ddcsrgps.[transition_to_compressed_state],
          ddcsrgps.[transition_to_compressed_state_desc],
          ddcsrgps.[has_vertipaq_optimization],
          ddcsrgps.[Generation],
          ddcsrgps.[created_time],
          ddcsrgps.[closed_time]
        FROM
          [sys].[dm_db_column_store_row_group_physical_stats] ddcsrgps
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int PARTITIONNUMBER_FIELD_ID = 2;
    public const int ROWGROUPID_FIELD_ID = 3;
    public const int DELTASTOREHOBTID_FIELD_ID = 4;
    public const int STATE_FIELD_ID = 5;
    public const int STATEDESC_FIELD_ID = 6;
    public const int TOTALROWS_FIELD_ID = 7;
    public const int DELETEDROWS_FIELD_ID = 8;
    public const int SIZEINBYTES_FIELD_ID = 9;
    public const int TRIMREASON_FIELD_ID = 10;
    public const int TRIMREASONDESC_FIELD_ID = 11;
    public const int TRANSITIONTOCOMPRESSEDSTATE_FIELD_ID = 12;
    public const int TRANSITIONTOCOMPRESSEDSTATEDESC_FIELD_ID = 13;
    public const int HASVERTIPAQOPTIMIZATION_FIELD_ID = 14;
    public const int GENERATION_FIELD_ID = 15;
    public const int CREATEDTIME_FIELD_ID = 16;
    public const int CLOSEDTIME_FIELD_ID = 17;


    public DmDbColumnStoreRowGroupPhysicalStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbColumnStoreRowGroupPhysicalStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbColumnStoreRowGroupPhysicalStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? IndexId
    {
        get
        {
            return base.GetNullableInt32(INDEXID_FIELD_ID);
        }
    }

    public int? PartitionNumber
    {
        get
        {
            return base.GetNullableInt32(PARTITIONNUMBER_FIELD_ID);
        }
    }

    public int? RowGroupId
    {
        get
        {
            return base.GetNullableInt32(ROWGROUPID_FIELD_ID);
        }
    }

    public long? DeltaStoreHobtId
    {
        get
        {
            return base.GetNullableInt64(DELTASTOREHOBTID_FIELD_ID);
        }
    }

    public byte? State
    {
        get
        {
            return base.GetNullableByte(STATE_FIELD_ID);
        }
    }

    public string StateDesc
    {
        get
        {
            return base.GetString(STATEDESC_FIELD_ID);
        }
    }

    public long? TotalRows
    {
        get
        {
            return base.GetNullableInt64(TOTALROWS_FIELD_ID);
        }
    }

    public long? DeletedRows
    {
        get
        {
            return base.GetNullableInt64(DELETEDROWS_FIELD_ID);
        }
    }

    public long? SizeInBytes
    {
        get
        {
            return base.GetNullableInt64(SIZEINBYTES_FIELD_ID);
        }
    }

    public byte? TrimReason
    {
        get
        {
            return base.GetNullableByte(TRIMREASON_FIELD_ID);
        }
    }

    public string? TrimReasonDesc
    {
        get
        {
            return base.GetNullableString(TRIMREASONDESC_FIELD_ID);
        }
    }

    public byte? TransitionToCompressedState
    {
        get
        {
            return base.GetNullableByte(TRANSITIONTOCOMPRESSEDSTATE_FIELD_ID);
        }
    }

    public string? TransitionToCompressedStateDesc
    {
        get
        {
            return base.GetNullableString(TRANSITIONTOCOMPRESSEDSTATEDESC_FIELD_ID);
        }
    }

    public bool? HasVertipaqOptimization
    {
        get
        {
            return base.GetNullableBoolean(HASVERTIPAQOPTIMIZATION_FIELD_ID);
        }
    }

    public long? Generation
    {
        get
        {
            return base.GetNullableInt64(GENERATION_FIELD_ID);
        }
    }

    public DateTime? CreatedTime
    {
        get
        {
            return base.GetNullableDateTime(CREATEDTIME_FIELD_ID);
        }
    }

    public DateTime? ClosedTime
    {
        get
        {
            return base.GetNullableDateTime(CLOSEDTIME_FIELD_ID);
        }
    }


    public Types.DmDbColumnStoreRowGroupPhysicalStatsDataType ToDataObject()
    {
        return new Types.DmDbColumnStoreRowGroupPhysicalStatsDataType(ObjectId,
            IndexId,
            PartitionNumber,
            RowGroupId,
            DeltaStoreHobtId,
            State,
            StateDesc,
            TotalRows,
            DeletedRows,
            SizeInBytes,
            TrimReason,
            TrimReasonDesc,
            TransitionToCompressedState,
            TransitionToCompressedStateDesc,
            HasVertipaqOptimization,
            Generation,
            CreatedTime,
            ClosedTime);
    }

    public List<Types.DmDbColumnStoreRowGroupPhysicalStatsDataType> ToList()
    {
        var list = new List<Types.DmDbColumnStoreRowGroupPhysicalStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
