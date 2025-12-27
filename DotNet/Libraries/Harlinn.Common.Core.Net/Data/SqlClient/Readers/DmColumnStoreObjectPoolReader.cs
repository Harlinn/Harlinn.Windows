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

public class DmColumnStoreObjectPoolReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_column_store_object_pool]";
    public const string TableName = "dm_column_store_object_pool";
    public const string ShortName = "dcsop";
    public const string Sql = """
        SELECT
          dcsop.[database_id],
          dcsop.[object_id],
          dcsop.[index_id],
          dcsop.[partition_number],
          dcsop.[column_id],
          dcsop.[row_group_id],
          dcsop.[object_type],
          dcsop.[object_type_desc],
          dcsop.[access_count],
          dcsop.[memory_used_in_bytes],
          dcsop.[object_load_time]
        FROM
          [sys].[dm_column_store_object_pool] dcsop
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int PARTITIONNUMBER_FIELD_ID = 3;
    public const int COLUMNID_FIELD_ID = 4;
    public const int ROWGROUPID_FIELD_ID = 5;
    public const int OBJECTTYPE_FIELD_ID = 6;
    public const int OBJECTTYPEDESC_FIELD_ID = 7;
    public const int ACCESSCOUNT_FIELD_ID = 8;
    public const int MEMORYUSEDINBYTES_FIELD_ID = 9;
    public const int OBJECTLOADTIME_FIELD_ID = 10;


    public DmColumnStoreObjectPoolReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmColumnStoreObjectPoolReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmColumnStoreObjectPoolReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
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

    public int? ColumnId
    {
        get
        {
            return base.GetNullableInt32(COLUMNID_FIELD_ID);
        }
    }

    public int RowGroupId
    {
        get
        {
            return base.GetInt32(ROWGROUPID_FIELD_ID);
        }
    }

    public int ObjectType
    {
        get
        {
            return base.GetInt32(OBJECTTYPE_FIELD_ID);
        }
    }

    public string ObjectTypeDesc
    {
        get
        {
            return base.GetString(OBJECTTYPEDESC_FIELD_ID);
        }
    }

    public long AccessCount
    {
        get
        {
            return base.GetInt64(ACCESSCOUNT_FIELD_ID);
        }
    }

    public long MemoryUsedInBytes
    {
        get
        {
            return base.GetInt64(MEMORYUSEDINBYTES_FIELD_ID);
        }
    }

    public DateTime ObjectLoadTime
    {
        get
        {
            return base.GetDateTime(OBJECTLOADTIME_FIELD_ID);
        }
    }


    public Types.DmColumnStoreObjectPoolDataType ToDataObject()
    {
        return new Types.DmColumnStoreObjectPoolDataType(DatabaseId,
            ObjectId,
            IndexId,
            PartitionNumber,
            ColumnId,
            RowGroupId,
            ObjectType,
            ObjectTypeDesc,
            AccessCount,
            MemoryUsedInBytes,
            ObjectLoadTime);
    }

    public List<Types.DmColumnStoreObjectPoolDataType> ToList()
    {
        var list = new List<Types.DmColumnStoreObjectPoolDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
