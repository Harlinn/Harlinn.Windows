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

public class DmFtsPopulationRangesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_population_ranges]";
    public const string TableName = "dm_fts_population_ranges";
    public const string ShortName = "dfpr";
    public const string Sql = """
        SELECT
          dfpr.[memory_address],
          dfpr.[parent_memory_address],
          dfpr.[is_retry],
          dfpr.[session_id],
          dfpr.[processed_row_count],
          dfpr.[error_count]
        FROM
          [sys].[dm_fts_population_ranges] dfpr
        """;

    public const int MEMORYADDRESS_FIELD_ID = 0;
    public const int PARENTMEMORYADDRESS_FIELD_ID = 1;
    public const int ISRETRY_FIELD_ID = 2;
    public const int SESSIONID_FIELD_ID = 3;
    public const int PROCESSEDROWCOUNT_FIELD_ID = 4;
    public const int ERRORCOUNT_FIELD_ID = 5;


    public DmFtsPopulationRangesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsPopulationRangesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsPopulationRangesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public byte[] ParentMemoryAddress
    {
        get
        {
            return base.GetBinary(PARENTMEMORYADDRESS_FIELD_ID);
        }
    }

    public bool IsRetry
    {
        get
        {
            return base.GetBoolean(ISRETRY_FIELD_ID);
        }
    }

    public short SessionId
    {
        get
        {
            return base.GetInt16(SESSIONID_FIELD_ID);
        }
    }

    public int ProcessedRowCount
    {
        get
        {
            return base.GetInt32(PROCESSEDROWCOUNT_FIELD_ID);
        }
    }

    public int ErrorCount
    {
        get
        {
            return base.GetInt32(ERRORCOUNT_FIELD_ID);
        }
    }


    public Types.DmFtsPopulationRangesDataType ToDataObject()
    {
        return new Types.DmFtsPopulationRangesDataType(MemoryAddress,
            ParentMemoryAddress,
            IsRetry,
            SessionId,
            ProcessedRowCount,
            ErrorCount);
    }

    public List<Types.DmFtsPopulationRangesDataType> ToList()
    {
        var list = new List<Types.DmFtsPopulationRangesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
