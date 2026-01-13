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

public class DmFtsMemoryBuffersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_memory_buffers]";
    public const string TableName = "dm_fts_memory_buffers";
    public const string ShortName = "dfmb";
    public const string Sql = """
        SELECT
          dfmb.[pool_id],
          dfmb.[memory_address],
          dfmb.[Name],
          dfmb.[is_free],
          dfmb.[row_count],
          dfmb.[bytes_used],
          dfmb.[percent_used]
        FROM
          [sys].[dm_fts_memory_buffers] dfmb
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int MEMORYADDRESS_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int ISFREE_FIELD_ID = 3;
    public const int ROWCOUNT_FIELD_ID = 4;
    public const int BYTESUSED_FIELD_ID = 5;
    public const int PERCENTUSED_FIELD_ID = 6;


    public DmFtsMemoryBuffersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsMemoryBuffersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsMemoryBuffersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public bool IsFree
    {
        get
        {
            return base.GetBoolean(ISFREE_FIELD_ID);
        }
    }

    public int RowCount
    {
        get
        {
            return base.GetInt32(ROWCOUNT_FIELD_ID);
        }
    }

    public int BytesUsed
    {
        get
        {
            return base.GetInt32(BYTESUSED_FIELD_ID);
        }
    }

    public int PercentUsed
    {
        get
        {
            return base.GetInt32(PERCENTUSED_FIELD_ID);
        }
    }


    public Types.DmFtsMemoryBuffersDataType ToDataObject()
    {
        return new Types.DmFtsMemoryBuffersDataType(PoolId,
            MemoryAddress,
            Name,
            IsFree,
            RowCount,
            BytesUsed,
            PercentUsed);
    }

    public List<Types.DmFtsMemoryBuffersDataType> ToList()
    {
        var list = new List<Types.DmFtsMemoryBuffersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
