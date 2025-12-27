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

public class DmDbFtsIndexPhysicalStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_fts_index_physical_stats]";
    public const string TableName = "dm_db_fts_index_physical_stats";
    public const string ShortName = "ddfips";
    public const string Sql = """
        SELECT
          ddfips.[object_id],
          ddfips.[fulltext_index_page_count],
          ddfips.[keyphrase_index_page_count],
          ddfips.[similarity_index_page_count]
        FROM
          [sys].[dm_db_fts_index_physical_stats] ddfips
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int FULLTEXTINDEXPAGECOUNT_FIELD_ID = 1;
    public const int KEYPHRASEINDEXPAGECOUNT_FIELD_ID = 2;
    public const int SIMILARITYINDEXPAGECOUNT_FIELD_ID = 3;


    public DmDbFtsIndexPhysicalStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbFtsIndexPhysicalStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbFtsIndexPhysicalStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long? FulltextIndexPageCount
    {
        get
        {
            return base.GetNullableInt64(FULLTEXTINDEXPAGECOUNT_FIELD_ID);
        }
    }

    public long? KeyphraseIndexPageCount
    {
        get
        {
            return base.GetNullableInt64(KEYPHRASEINDEXPAGECOUNT_FIELD_ID);
        }
    }

    public long? SimilarityIndexPageCount
    {
        get
        {
            return base.GetNullableInt64(SIMILARITYINDEXPAGECOUNT_FIELD_ID);
        }
    }


    public Types.DmDbFtsIndexPhysicalStatsDataType ToDataObject()
    {
        return new Types.DmDbFtsIndexPhysicalStatsDataType(ObjectId,
            FulltextIndexPageCount,
            KeyphraseIndexPageCount,
            SimilarityIndexPageCount);
    }

    public List<Types.DmDbFtsIndexPhysicalStatsDataType> ToList()
    {
        var list = new List<Types.DmDbFtsIndexPhysicalStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
