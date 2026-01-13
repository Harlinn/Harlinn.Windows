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

public class DmFtsMemoryPoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_memory_pools]";
    public const string TableName = "dm_fts_memory_pools";
    public const string ShortName = "dfmp";
    public const string Sql = """
        SELECT
          dfmp.[pool_id],
          dfmp.[buffer_size],
          dfmp.[min_buffer_limit],
          dfmp.[max_buffer_limit],
          dfmp.[buffer_count]
        FROM
          [sys].[dm_fts_memory_pools] dfmp
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int BUFFERSIZE_FIELD_ID = 1;
    public const int MINBUFFERLIMIT_FIELD_ID = 2;
    public const int MAXBUFFERLIMIT_FIELD_ID = 3;
    public const int BUFFERCOUNT_FIELD_ID = 4;


    public DmFtsMemoryPoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsMemoryPoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsMemoryPoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int BufferSize
    {
        get
        {
            return base.GetInt32(BUFFERSIZE_FIELD_ID);
        }
    }

    public int MinBufferLimit
    {
        get
        {
            return base.GetInt32(MINBUFFERLIMIT_FIELD_ID);
        }
    }

    public int MaxBufferLimit
    {
        get
        {
            return base.GetInt32(MAXBUFFERLIMIT_FIELD_ID);
        }
    }

    public int BufferCount
    {
        get
        {
            return base.GetInt32(BUFFERCOUNT_FIELD_ID);
        }
    }


    public Types.DmFtsMemoryPoolsDataType ToDataObject()
    {
        return new Types.DmFtsMemoryPoolsDataType(PoolId,
            BufferSize,
            MinBufferLimit,
            MaxBufferLimit,
            BufferCount);
    }

    public List<Types.DmFtsMemoryPoolsDataType> ToList()
    {
        var list = new List<Types.DmFtsMemoryPoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
