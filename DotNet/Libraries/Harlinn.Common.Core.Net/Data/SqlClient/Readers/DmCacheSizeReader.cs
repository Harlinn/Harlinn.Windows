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

public class DmCacheSizeReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cache_size]";
    public const string TableName = "dm_cache_size";
    public const string ShortName = "dcs0";
    public const string Sql = """
        SELECT
          dcs0.[distribution_id],
          dcs0.[cache_used],
          dcs0.[cache_available],
          dcs0.[cache_capacity]
        FROM
          [sys].[dm_cache_size] dcs0
        """;

    public const int DISTRIBUTIONID_FIELD_ID = 0;
    public const int CACHEUSED_FIELD_ID = 1;
    public const int CACHEAVAILABLE_FIELD_ID = 2;
    public const int CACHECAPACITY_FIELD_ID = 3;


    public DmCacheSizeReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmCacheSizeReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmCacheSizeReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? DistributionId
    {
        get
        {
            return base.GetNullableInt16(DISTRIBUTIONID_FIELD_ID);
        }
    }

    public long? CacheUsed
    {
        get
        {
            return base.GetNullableInt64(CACHEUSED_FIELD_ID);
        }
    }

    public long? CacheAvailable
    {
        get
        {
            return base.GetNullableInt64(CACHEAVAILABLE_FIELD_ID);
        }
    }

    public long? CacheCapacity
    {
        get
        {
            return base.GetNullableInt64(CACHECAPACITY_FIELD_ID);
        }
    }


    public Types.DmCacheSizeDataType ToDataObject()
    {
        return new Types.DmCacheSizeDataType(DistributionId,
            CacheUsed,
            CacheAvailable,
            CacheCapacity);
    }

    public List<Types.DmCacheSizeDataType> ToList()
    {
        var list = new List<Types.DmCacheSizeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
