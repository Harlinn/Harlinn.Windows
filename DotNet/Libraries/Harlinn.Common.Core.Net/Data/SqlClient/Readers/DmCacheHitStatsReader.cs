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

public class DmCacheHitStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cache_hit_stats]";
    public const string TableName = "dm_cache_hit_stats";
    public const string ShortName = "dchs";
    public const string Sql = """
        SELECT
          dchs.[distribution_id],
          dchs.[cache_hit],
          dchs.[remote_hit],
          dchs.[collection_start_time]
        FROM
          [sys].[dm_cache_hit_stats] dchs
        """;

    public const int DISTRIBUTIONID_FIELD_ID = 0;
    public const int CACHEHIT_FIELD_ID = 1;
    public const int REMOTEHIT_FIELD_ID = 2;
    public const int COLLECTIONSTARTTIME_FIELD_ID = 3;


    public DmCacheHitStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmCacheHitStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmCacheHitStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long? CacheHit
    {
        get
        {
            return base.GetNullableInt64(CACHEHIT_FIELD_ID);
        }
    }

    public long? RemoteHit
    {
        get
        {
            return base.GetNullableInt64(REMOTEHIT_FIELD_ID);
        }
    }

    public DateTime? CollectionStartTime
    {
        get
        {
            return base.GetNullableDateTime(COLLECTIONSTARTTIME_FIELD_ID);
        }
    }


    public Types.DmCacheHitStatsDataType ToDataObject()
    {
        return new Types.DmCacheHitStatsDataType(DistributionId,
            CacheHit,
            RemoteHit,
            CollectionStartTime);
    }

    public List<Types.DmCacheHitStatsDataType> ToList()
    {
        var list = new List<Types.DmCacheHitStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
