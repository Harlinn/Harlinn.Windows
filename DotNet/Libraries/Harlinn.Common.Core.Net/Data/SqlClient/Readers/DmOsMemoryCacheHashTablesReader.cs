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

public class DmOsMemoryCacheHashTablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_cache_hash_tables]";
    public const string TableName = "dm_os_memory_cache_hash_tables";
    public const string ShortName = "domcht";
    public const string Sql = """
        SELECT
          domcht.[cache_address],
          domcht.[Name],
          domcht.[Type],
          domcht.[table_level],
          domcht.[buckets_count],
          domcht.[buckets_in_use_count],
          domcht.[buckets_min_length],
          domcht.[buckets_max_length],
          domcht.[buckets_avg_length],
          domcht.[buckets_max_length_ever],
          domcht.[hits_count],
          domcht.[misses_count],
          domcht.[buckets_avg_scan_hit_length],
          domcht.[buckets_avg_scan_miss_length]
        FROM
          [sys].[dm_os_memory_cache_hash_tables] domcht
        """;

    public const int CACHEADDRESS_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TABLELEVEL_FIELD_ID = 3;
    public const int BUCKETSCOUNT_FIELD_ID = 4;
    public const int BUCKETSINUSECOUNT_FIELD_ID = 5;
    public const int BUCKETSMINLENGTH_FIELD_ID = 6;
    public const int BUCKETSMAXLENGTH_FIELD_ID = 7;
    public const int BUCKETSAVGLENGTH_FIELD_ID = 8;
    public const int BUCKETSMAXLENGTHEVER_FIELD_ID = 9;
    public const int HITSCOUNT_FIELD_ID = 10;
    public const int MISSESCOUNT_FIELD_ID = 11;
    public const int BUCKETSAVGSCANHITLENGTH_FIELD_ID = 12;
    public const int BUCKETSAVGSCANMISSLENGTH_FIELD_ID = 13;


    public DmOsMemoryCacheHashTablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheHashTablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheHashTablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int TableLevel
    {
        get
        {
            return base.GetInt32(TABLELEVEL_FIELD_ID);
        }
    }

    public int BucketsCount
    {
        get
        {
            return base.GetInt32(BUCKETSCOUNT_FIELD_ID);
        }
    }

    public int BucketsInUseCount
    {
        get
        {
            return base.GetInt32(BUCKETSINUSECOUNT_FIELD_ID);
        }
    }

    public int BucketsMinLength
    {
        get
        {
            return base.GetInt32(BUCKETSMINLENGTH_FIELD_ID);
        }
    }

    public int BucketsMaxLength
    {
        get
        {
            return base.GetInt32(BUCKETSMAXLENGTH_FIELD_ID);
        }
    }

    public int BucketsAvgLength
    {
        get
        {
            return base.GetInt32(BUCKETSAVGLENGTH_FIELD_ID);
        }
    }

    public int BucketsMaxLengthEver
    {
        get
        {
            return base.GetInt32(BUCKETSMAXLENGTHEVER_FIELD_ID);
        }
    }

    public long HitsCount
    {
        get
        {
            return base.GetInt64(HITSCOUNT_FIELD_ID);
        }
    }

    public long MissesCount
    {
        get
        {
            return base.GetInt64(MISSESCOUNT_FIELD_ID);
        }
    }

    public int BucketsAvgScanHitLength
    {
        get
        {
            return base.GetInt32(BUCKETSAVGSCANHITLENGTH_FIELD_ID);
        }
    }

    public int BucketsAvgScanMissLength
    {
        get
        {
            return base.GetInt32(BUCKETSAVGSCANMISSLENGTH_FIELD_ID);
        }
    }


    public Types.DmOsMemoryCacheHashTablesDataType ToDataObject()
    {
        return new Types.DmOsMemoryCacheHashTablesDataType(CacheAddress,
            Name,
            Type,
            TableLevel,
            BucketsCount,
            BucketsInUseCount,
            BucketsMinLength,
            BucketsMaxLength,
            BucketsAvgLength,
            BucketsMaxLengthEver,
            HitsCount,
            MissesCount,
            BucketsAvgScanHitLength,
            BucketsAvgScanMissLength);
    }

    public List<Types.DmOsMemoryCacheHashTablesDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryCacheHashTablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
