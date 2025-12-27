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

public class DmDbXtpHashIndexStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_hash_index_stats]";
    public const string TableName = "dm_db_xtp_hash_index_stats";
    public const string ShortName = "ddxhis";
    public const string Sql = """
        SELECT
          ddxhis.[object_id],
          ddxhis.[xtp_object_id],
          ddxhis.[index_id],
          ddxhis.[total_bucket_count],
          ddxhis.[empty_bucket_count],
          ddxhis.[avg_chain_length],
          ddxhis.[max_chain_length]
        FROM
          [sys].[dm_db_xtp_hash_index_stats] ddxhis
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int XTPOBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int TOTALBUCKETCOUNT_FIELD_ID = 3;
    public const int EMPTYBUCKETCOUNT_FIELD_ID = 4;
    public const int AVGCHAINLENGTH_FIELD_ID = 5;
    public const int MAXCHAINLENGTH_FIELD_ID = 6;


    public DmDbXtpHashIndexStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpHashIndexStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpHashIndexStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int XtpObjectId
    {
        get
        {
            return base.GetInt32(XTPOBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public long TotalBucketCount
    {
        get
        {
            return base.GetInt64(TOTALBUCKETCOUNT_FIELD_ID);
        }
    }

    public long? EmptyBucketCount
    {
        get
        {
            return base.GetNullableInt64(EMPTYBUCKETCOUNT_FIELD_ID);
        }
    }

    public long AvgChainLength
    {
        get
        {
            return base.GetInt64(AVGCHAINLENGTH_FIELD_ID);
        }
    }

    public long MaxChainLength
    {
        get
        {
            return base.GetInt64(MAXCHAINLENGTH_FIELD_ID);
        }
    }


    public Types.DmDbXtpHashIndexStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpHashIndexStatsDataType(ObjectId,
            XtpObjectId,
            IndexId,
            TotalBucketCount,
            EmptyBucketCount,
            AvgChainLength,
            MaxChainLength);
    }

    public List<Types.DmDbXtpHashIndexStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpHashIndexStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
