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

public class DmLogpoolStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_logpool_stats]";
    public const string TableName = "dm_logpool_stats";
    public const string ShortName = "dls";
    public const string Sql = """
        SELECT
          dls.[hash_hit_total_search_length],
          dls.[hash_miss_total_search_length],
          dls.[hash_hits],
          dls.[hash_misses],
          dls.[hash_bucket_count],
          dls.[mem_status_stamp],
          dls.[mem_status],
          dls.[logpoolmgr_count],
          dls.[total_pages],
          dls.[private_pages]
        FROM
          [sys].[dm_logpool_stats] dls
        """;

    public const int HASHHITTOTALSEARCHLENGTH_FIELD_ID = 0;
    public const int HASHMISSTOTALSEARCHLENGTH_FIELD_ID = 1;
    public const int HASHHITS_FIELD_ID = 2;
    public const int HASHMISSES_FIELD_ID = 3;
    public const int HASHBUCKETCOUNT_FIELD_ID = 4;
    public const int MEMSTATUSSTAMP_FIELD_ID = 5;
    public const int MEMSTATUS_FIELD_ID = 6;
    public const int LOGPOOLMGRCOUNT_FIELD_ID = 7;
    public const int TOTALPAGES_FIELD_ID = 8;
    public const int PRIVATEPAGES_FIELD_ID = 9;


    public DmLogpoolStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmLogpoolStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmLogpoolStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long HashHitTotalSearchLength
    {
        get
        {
            return base.GetInt64(HASHHITTOTALSEARCHLENGTH_FIELD_ID);
        }
    }

    public long HashMissTotalSearchLength
    {
        get
        {
            return base.GetInt64(HASHMISSTOTALSEARCHLENGTH_FIELD_ID);
        }
    }

    public long HashHits
    {
        get
        {
            return base.GetInt64(HASHHITS_FIELD_ID);
        }
    }

    public long HashMisses
    {
        get
        {
            return base.GetInt64(HASHMISSES_FIELD_ID);
        }
    }

    public int HashBucketCount
    {
        get
        {
            return base.GetInt32(HASHBUCKETCOUNT_FIELD_ID);
        }
    }

    public long MemStatusStamp
    {
        get
        {
            return base.GetInt64(MEMSTATUSSTAMP_FIELD_ID);
        }
    }

    public int MemStatus
    {
        get
        {
            return base.GetInt32(MEMSTATUS_FIELD_ID);
        }
    }

    public int LogpoolmgrCount
    {
        get
        {
            return base.GetInt32(LOGPOOLMGRCOUNT_FIELD_ID);
        }
    }

    public long TotalPages
    {
        get
        {
            return base.GetInt64(TOTALPAGES_FIELD_ID);
        }
    }

    public long PrivatePages
    {
        get
        {
            return base.GetInt64(PRIVATEPAGES_FIELD_ID);
        }
    }


    public Types.DmLogpoolStatsDataType ToDataObject()
    {
        return new Types.DmLogpoolStatsDataType(HashHitTotalSearchLength,
            HashMissTotalSearchLength,
            HashHits,
            HashMisses,
            HashBucketCount,
            MemStatusStamp,
            MemStatus,
            LogpoolmgrCount,
            TotalPages,
            PrivatePages);
    }

    public List<Types.DmLogpoolStatsDataType> ToList()
    {
        var list = new List<Types.DmLogpoolStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
