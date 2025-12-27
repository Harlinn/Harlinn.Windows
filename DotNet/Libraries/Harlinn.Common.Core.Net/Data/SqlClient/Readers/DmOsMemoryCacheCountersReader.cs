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

public class DmOsMemoryCacheCountersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_cache_counters]";
    public const string TableName = "dm_os_memory_cache_counters";
    public const string ShortName = "domcc";
    public const string Sql = """
        SELECT
          domcc.[cache_address],
          domcc.[Name],
          domcc.[Type],
          domcc.[pages_kb],
          domcc.[pages_in_use_kb],
          domcc.[entries_count],
          domcc.[entries_in_use_count]
        FROM
          [sys].[dm_os_memory_cache_counters] domcc
        """;

    public const int CACHEADDRESS_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int PAGESKB_FIELD_ID = 3;
    public const int PAGESINUSEKB_FIELD_ID = 4;
    public const int ENTRIESCOUNT_FIELD_ID = 5;
    public const int ENTRIESINUSECOUNT_FIELD_ID = 6;


    public DmOsMemoryCacheCountersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheCountersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheCountersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] CacheAddress
    {
        get
        {
            return base.GetBinary(CACHEADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public long PagesKb
    {
        get
        {
            return base.GetInt64(PAGESKB_FIELD_ID);
        }
    }

    public long? PagesInUseKb
    {
        get
        {
            return base.GetNullableInt64(PAGESINUSEKB_FIELD_ID);
        }
    }

    public long EntriesCount
    {
        get
        {
            return base.GetInt64(ENTRIESCOUNT_FIELD_ID);
        }
    }

    public long EntriesInUseCount
    {
        get
        {
            return base.GetInt64(ENTRIESINUSECOUNT_FIELD_ID);
        }
    }


    public Types.DmOsMemoryCacheCountersDataType ToDataObject()
    {
        return new Types.DmOsMemoryCacheCountersDataType(CacheAddress,
            Name,
            Type,
            PagesKb,
            PagesInUseKb,
            EntriesCount,
            EntriesInUseCount);
    }

    public List<Types.DmOsMemoryCacheCountersDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryCacheCountersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
