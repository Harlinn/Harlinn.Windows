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

public class DmDbXtpNonclusteredIndexStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_nonclustered_index_stats]";
    public const string TableName = "dm_db_xtp_nonclustered_index_stats";
    public const string ShortName = "ddxnis";
    public const string Sql = """
        SELECT
          ddxnis.[object_id],
          ddxnis.[xtp_object_id],
          ddxnis.[index_id],
          ddxnis.[delta_pages],
          ddxnis.[internal_pages],
          ddxnis.[leaf_pages],
          ddxnis.[outstanding_retired_nodes],
          ddxnis.[page_update_count],
          ddxnis.[page_update_retry_count],
          ddxnis.[page_consolidation_count],
          ddxnis.[page_consolidation_retry_count],
          ddxnis.[page_split_count],
          ddxnis.[page_split_retry_count],
          ddxnis.[key_split_count],
          ddxnis.[key_split_retry_count],
          ddxnis.[page_merge_count],
          ddxnis.[page_merge_retry_count],
          ddxnis.[key_merge_count],
          ddxnis.[key_merge_retry_count],
          ddxnis.[uses_key_normalization]
        FROM
          [sys].[dm_db_xtp_nonclustered_index_stats] ddxnis
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int XTPOBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int DELTAPAGES_FIELD_ID = 3;
    public const int INTERNALPAGES_FIELD_ID = 4;
    public const int LEAFPAGES_FIELD_ID = 5;
    public const int OUTSTANDINGRETIREDNODES_FIELD_ID = 6;
    public const int PAGEUPDATECOUNT_FIELD_ID = 7;
    public const int PAGEUPDATERETRYCOUNT_FIELD_ID = 8;
    public const int PAGECONSOLIDATIONCOUNT_FIELD_ID = 9;
    public const int PAGECONSOLIDATIONRETRYCOUNT_FIELD_ID = 10;
    public const int PAGESPLITCOUNT_FIELD_ID = 11;
    public const int PAGESPLITRETRYCOUNT_FIELD_ID = 12;
    public const int KEYSPLITCOUNT_FIELD_ID = 13;
    public const int KEYSPLITRETRYCOUNT_FIELD_ID = 14;
    public const int PAGEMERGECOUNT_FIELD_ID = 15;
    public const int PAGEMERGERETRYCOUNT_FIELD_ID = 16;
    public const int KEYMERGECOUNT_FIELD_ID = 17;
    public const int KEYMERGERETRYCOUNT_FIELD_ID = 18;
    public const int USESKEYNORMALIZATION_FIELD_ID = 19;


    public DmDbXtpNonclusteredIndexStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpNonclusteredIndexStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpNonclusteredIndexStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long DeltaPages
    {
        get
        {
            return base.GetInt64(DELTAPAGES_FIELD_ID);
        }
    }

    public long InternalPages
    {
        get
        {
            return base.GetInt64(INTERNALPAGES_FIELD_ID);
        }
    }

    public long LeafPages
    {
        get
        {
            return base.GetInt64(LEAFPAGES_FIELD_ID);
        }
    }

    public long OutstandingRetiredNodes
    {
        get
        {
            return base.GetInt64(OUTSTANDINGRETIREDNODES_FIELD_ID);
        }
    }

    public long PageUpdateCount
    {
        get
        {
            return base.GetInt64(PAGEUPDATECOUNT_FIELD_ID);
        }
    }

    public long PageUpdateRetryCount
    {
        get
        {
            return base.GetInt64(PAGEUPDATERETRYCOUNT_FIELD_ID);
        }
    }

    public long PageConsolidationCount
    {
        get
        {
            return base.GetInt64(PAGECONSOLIDATIONCOUNT_FIELD_ID);
        }
    }

    public long PageConsolidationRetryCount
    {
        get
        {
            return base.GetInt64(PAGECONSOLIDATIONRETRYCOUNT_FIELD_ID);
        }
    }

    public long PageSplitCount
    {
        get
        {
            return base.GetInt64(PAGESPLITCOUNT_FIELD_ID);
        }
    }

    public long PageSplitRetryCount
    {
        get
        {
            return base.GetInt64(PAGESPLITRETRYCOUNT_FIELD_ID);
        }
    }

    public long KeySplitCount
    {
        get
        {
            return base.GetInt64(KEYSPLITCOUNT_FIELD_ID);
        }
    }

    public long KeySplitRetryCount
    {
        get
        {
            return base.GetInt64(KEYSPLITRETRYCOUNT_FIELD_ID);
        }
    }

    public long PageMergeCount
    {
        get
        {
            return base.GetInt64(PAGEMERGECOUNT_FIELD_ID);
        }
    }

    public long PageMergeRetryCount
    {
        get
        {
            return base.GetInt64(PAGEMERGERETRYCOUNT_FIELD_ID);
        }
    }

    public long KeyMergeCount
    {
        get
        {
            return base.GetInt64(KEYMERGECOUNT_FIELD_ID);
        }
    }

    public long KeyMergeRetryCount
    {
        get
        {
            return base.GetInt64(KEYMERGERETRYCOUNT_FIELD_ID);
        }
    }

    public bool UsesKeyNormalization
    {
        get
        {
            return base.GetBoolean(USESKEYNORMALIZATION_FIELD_ID);
        }
    }


    public Types.DmDbXtpNonclusteredIndexStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpNonclusteredIndexStatsDataType(ObjectId,
            XtpObjectId,
            IndexId,
            DeltaPages,
            InternalPages,
            LeafPages,
            OutstandingRetiredNodes,
            PageUpdateCount,
            PageUpdateRetryCount,
            PageConsolidationCount,
            PageConsolidationRetryCount,
            PageSplitCount,
            PageSplitRetryCount,
            KeySplitCount,
            KeySplitRetryCount,
            PageMergeCount,
            PageMergeRetryCount,
            KeyMergeCount,
            KeyMergeRetryCount,
            UsesKeyNormalization);
    }

    public List<Types.DmDbXtpNonclusteredIndexStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpNonclusteredIndexStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
