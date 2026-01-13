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

public class PartitionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[partitions]";
    public const string TableName = "partitions";
    public const string ShortName = "p1";
    public const string Sql = """
        SELECT
          p1.[partition_id],
          p1.[object_id],
          p1.[index_id],
          p1.[partition_number],
          p1.[hobt_id],
          p1.[Rows],
          p1.[filestream_filegroup_id],
          p1.[data_compression],
          p1.[data_compression_desc]
        FROM
          [sys].[partitions] p1
        """;

    public const int PARTITIONID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int PARTITIONNUMBER_FIELD_ID = 3;
    public const int HOBTID_FIELD_ID = 4;
    public const int ROWS_FIELD_ID = 5;
    public const int FILESTREAMFILEGROUPID_FIELD_ID = 6;
    public const int DATACOMPRESSION_FIELD_ID = 7;
    public const int DATACOMPRESSIONDESC_FIELD_ID = 8;


    public PartitionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PartitionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PartitionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long? Rows
    {
        get
        {
            return base.GetNullableInt64(ROWS_FIELD_ID);
        }
    }

    public short FilestreamFilegroupId
    {
        get
        {
            return base.GetInt16(FILESTREAMFILEGROUPID_FIELD_ID);
        }
    }

    public byte DataCompression
    {
        get
        {
            return base.GetByte(DATACOMPRESSION_FIELD_ID);
        }
    }

    public string? DataCompressionDesc
    {
        get
        {
            return base.GetNullableString(DATACOMPRESSIONDESC_FIELD_ID);
        }
    }


    public Types.PartitionsDataType ToDataObject()
    {
        return new Types.PartitionsDataType(PartitionId,
            ObjectId,
            IndexId,
            PartitionNumber,
            HobtId,
            Rows,
            FilestreamFilegroupId,
            DataCompression,
            DataCompressionDesc);
    }

    public List<Types.PartitionsDataType> ToList()
    {
        var list = new List<Types.PartitionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
