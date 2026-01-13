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

public class DmDbXtpMemoryConsumersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_memory_consumers]";
    public const string TableName = "dm_db_xtp_memory_consumers";
    public const string ShortName = "ddxmc";
    public const string Sql = """
        SELECT
          ddxmc.[memory_consumer_id],
          ddxmc.[memory_consumer_type],
          ddxmc.[memory_consumer_type_desc],
          ddxmc.[memory_consumer_desc],
          ddxmc.[object_id],
          ddxmc.[xtp_object_id],
          ddxmc.[index_id],
          ddxmc.[allocated_bytes],
          ddxmc.[used_bytes],
          ddxmc.[allocation_count],
          ddxmc.[partition_count],
          ddxmc.[sizeclass_count],
          ddxmc.[min_sizeclass],
          ddxmc.[max_sizeclass],
          ddxmc.[memory_consumer_address]
        FROM
          [sys].[dm_db_xtp_memory_consumers] ddxmc
        """;

    public const int MEMORYCONSUMERID_FIELD_ID = 0;
    public const int MEMORYCONSUMERTYPE_FIELD_ID = 1;
    public const int MEMORYCONSUMERTYPEDESC_FIELD_ID = 2;
    public const int MEMORYCONSUMERDESC_FIELD_ID = 3;
    public const int OBJECTID_FIELD_ID = 4;
    public const int XTPOBJECTID_FIELD_ID = 5;
    public const int INDEXID_FIELD_ID = 6;
    public const int ALLOCATEDBYTES_FIELD_ID = 7;
    public const int USEDBYTES_FIELD_ID = 8;
    public const int ALLOCATIONCOUNT_FIELD_ID = 9;
    public const int PARTITIONCOUNT_FIELD_ID = 10;
    public const int SIZECLASSCOUNT_FIELD_ID = 11;
    public const int MINSIZECLASS_FIELD_ID = 12;
    public const int MAXSIZECLASS_FIELD_ID = 13;
    public const int MEMORYCONSUMERADDRESS_FIELD_ID = 14;


    public DmDbXtpMemoryConsumersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpMemoryConsumersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpMemoryConsumersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long MemoryConsumerId
    {
        get
        {
            return base.GetInt64(MEMORYCONSUMERID_FIELD_ID);
        }
    }

    public int MemoryConsumerType
    {
        get
        {
            return base.GetInt32(MEMORYCONSUMERTYPE_FIELD_ID);
        }
    }

    public string MemoryConsumerTypeDesc
    {
        get
        {
            return base.GetString(MEMORYCONSUMERTYPEDESC_FIELD_ID);
        }
    }

    public string? MemoryConsumerDesc
    {
        get
        {
            return base.GetNullableString(MEMORYCONSUMERDESC_FIELD_ID);
        }
    }

    public int? ObjectId
    {
        get
        {
            return base.GetNullableInt32(OBJECTID_FIELD_ID);
        }
    }

    public int? XtpObjectId
    {
        get
        {
            return base.GetNullableInt32(XTPOBJECTID_FIELD_ID);
        }
    }

    public int? IndexId
    {
        get
        {
            return base.GetNullableInt32(INDEXID_FIELD_ID);
        }
    }

    public long AllocatedBytes
    {
        get
        {
            return base.GetInt64(ALLOCATEDBYTES_FIELD_ID);
        }
    }

    public long UsedBytes
    {
        get
        {
            return base.GetInt64(USEDBYTES_FIELD_ID);
        }
    }

    public long AllocationCount
    {
        get
        {
            return base.GetInt64(ALLOCATIONCOUNT_FIELD_ID);
        }
    }

    public int PartitionCount
    {
        get
        {
            return base.GetInt32(PARTITIONCOUNT_FIELD_ID);
        }
    }

    public int SizeclassCount
    {
        get
        {
            return base.GetInt32(SIZECLASSCOUNT_FIELD_ID);
        }
    }

    public int MinSizeclass
    {
        get
        {
            return base.GetInt32(MINSIZECLASS_FIELD_ID);
        }
    }

    public int MaxSizeclass
    {
        get
        {
            return base.GetInt32(MAXSIZECLASS_FIELD_ID);
        }
    }

    public byte[] MemoryConsumerAddress
    {
        get
        {
            return base.GetBinary(MEMORYCONSUMERADDRESS_FIELD_ID);
        }
    }


    public Types.DmDbXtpMemoryConsumersDataType ToDataObject()
    {
        return new Types.DmDbXtpMemoryConsumersDataType(MemoryConsumerId,
            MemoryConsumerType,
            MemoryConsumerTypeDesc,
            MemoryConsumerDesc,
            ObjectId,
            XtpObjectId,
            IndexId,
            AllocatedBytes,
            UsedBytes,
            AllocationCount,
            PartitionCount,
            SizeclassCount,
            MinSizeclass,
            MaxSizeclass,
            MemoryConsumerAddress);
    }

    public List<Types.DmDbXtpMemoryConsumersDataType> ToList()
    {
        var list = new List<Types.DmDbXtpMemoryConsumersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
