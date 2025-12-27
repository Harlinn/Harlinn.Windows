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

public class InternalPartitionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[internal_partitions]";
    public const string TableName = "internal_partitions";
    public const string ShortName = "ip";
    public const string Sql = """
        SELECT
          ip.[partition_id],
          ip.[object_id],
          ip.[index_id],
          ip.[partition_number],
          ip.[hobt_id],
          ip.[internal_object_type],
          ip.[internal_object_type_desc],
          ip.[row_group_id],
          ip.[Rows],
          ip.[data_compression],
          ip.[data_compression_desc]
        FROM
          [sys].[internal_partitions] ip
        """;

    public const int PARTITIONID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int PARTITIONNUMBER_FIELD_ID = 3;
    public const int HOBTID_FIELD_ID = 4;
    public const int INTERNALOBJECTTYPE_FIELD_ID = 5;
    public const int INTERNALOBJECTTYPEDESC_FIELD_ID = 6;
    public const int ROWGROUPID_FIELD_ID = 7;
    public const int ROWS_FIELD_ID = 8;
    public const int DATACOMPRESSION_FIELD_ID = 9;
    public const int DATACOMPRESSIONDESC_FIELD_ID = 10;


    public InternalPartitionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public InternalPartitionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public InternalPartitionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long PartitionId
    {
        get
        {
            return base.GetInt64(PARTITIONID_FIELD_ID);
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

    public long HobtId
    {
        get
        {
            return base.GetInt64(HOBTID_FIELD_ID);
        }
    }

    public byte? InternalObjectType
    {
        get
        {
            return base.GetNullableByte(INTERNALOBJECTTYPE_FIELD_ID);
        }
    }

    public string? InternalObjectTypeDesc
    {
        get
        {
            return base.GetNullableString(INTERNALOBJECTTYPEDESC_FIELD_ID);
        }
    }

    public int? RowGroupId
    {
        get
        {
            return base.GetNullableInt32(ROWGROUPID_FIELD_ID);
        }
    }

    public long? Rows
    {
        get
        {
            return base.GetNullableInt64(ROWS_FIELD_ID);
        }
    }

    public byte? DataCompression
    {
        get
        {
            return base.GetNullableByte(DATACOMPRESSION_FIELD_ID);
        }
    }

    public string? DataCompressionDesc
    {
        get
        {
            return base.GetNullableString(DATACOMPRESSIONDESC_FIELD_ID);
        }
    }


    public Types.InternalPartitionsDataType ToDataObject()
    {
        return new Types.InternalPartitionsDataType(PartitionId,
            ObjectId,
            IndexId,
            PartitionNumber,
            HobtId,
            InternalObjectType,
            InternalObjectTypeDesc,
            RowGroupId,
            Rows,
            DataCompression,
            DataCompressionDesc);
    }

    public List<Types.InternalPartitionsDataType> ToList()
    {
        var list = new List<Types.InternalPartitionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
