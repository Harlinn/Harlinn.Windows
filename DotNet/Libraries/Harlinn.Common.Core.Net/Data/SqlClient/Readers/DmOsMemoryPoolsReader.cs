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

public class DmOsMemoryPoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_pools]";
    public const string TableName = "dm_os_memory_pools";
    public const string ShortName = "domp";
    public const string Sql = """
        SELECT
          domp.[memory_pool_address],
          domp.[pool_id],
          domp.[Type],
          domp.[Name],
          domp.[max_free_entries_count],
          domp.[free_entries_count],
          domp.[removed_in_all_rounds_count]
        FROM
          [sys].[dm_os_memory_pools] domp
        """;

    public const int MEMORYPOOLADDRESS_FIELD_ID = 0;
    public const int POOLID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int NAME_FIELD_ID = 3;
    public const int MAXFREEENTRIESCOUNT_FIELD_ID = 4;
    public const int FREEENTRIESCOUNT_FIELD_ID = 5;
    public const int REMOVEDINALLROUNDSCOUNT_FIELD_ID = 6;


    public DmOsMemoryPoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryPoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryPoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] MemoryPoolAddress
    {
        get
        {
            return base.GetBinary(MEMORYPOOLADDRESS_FIELD_ID);
        }
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public long MaxFreeEntriesCount
    {
        get
        {
            return base.GetInt64(MAXFREEENTRIESCOUNT_FIELD_ID);
        }
    }

    public long FreeEntriesCount
    {
        get
        {
            return base.GetInt64(FREEENTRIESCOUNT_FIELD_ID);
        }
    }

    public long RemovedInAllRoundsCount
    {
        get
        {
            return base.GetInt64(REMOVEDINALLROUNDSCOUNT_FIELD_ID);
        }
    }


    public Types.DmOsMemoryPoolsDataType ToDataObject()
    {
        return new Types.DmOsMemoryPoolsDataType(MemoryPoolAddress,
            PoolId,
            Type,
            Name,
            MaxFreeEntriesCount,
            FreeEntriesCount,
            RemovedInAllRoundsCount);
    }

    public List<Types.DmOsMemoryPoolsDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryPoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
