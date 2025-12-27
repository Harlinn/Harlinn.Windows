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

public class FulltextIndexesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_indexes]";
    public const string TableName = "fulltext_indexes";
    public const string ShortName = "fi";
    public const string Sql = """
        SELECT
          fi.[object_id],
          fi.[unique_index_id],
          fi.[fulltext_catalog_id],
          fi.[is_enabled],
          fi.[change_tracking_state],
          fi.[change_tracking_state_desc],
          fi.[has_crawl_completed],
          fi.[crawl_type],
          fi.[crawl_type_desc],
          fi.[crawl_start_date],
          fi.[crawl_end_date],
          fi.[incremental_timestamp],
          fi.[stoplist_id],
          fi.[property_list_id],
          fi.[data_space_id]
        FROM
          [sys].[fulltext_indexes] fi
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int UNIQUEINDEXID_FIELD_ID = 1;
    public const int FULLTEXTCATALOGID_FIELD_ID = 2;
    public const int ISENABLED_FIELD_ID = 3;
    public const int CHANGETRACKINGSTATE_FIELD_ID = 4;
    public const int CHANGETRACKINGSTATEDESC_FIELD_ID = 5;
    public const int HASCRAWLCOMPLETED_FIELD_ID = 6;
    public const int CRAWLTYPE_FIELD_ID = 7;
    public const int CRAWLTYPEDESC_FIELD_ID = 8;
    public const int CRAWLSTARTDATE_FIELD_ID = 9;
    public const int CRAWLENDDATE_FIELD_ID = 10;
    public const int INCREMENTALTIMESTAMP_FIELD_ID = 11;
    public const int STOPLISTID_FIELD_ID = 12;
    public const int PROPERTYLISTID_FIELD_ID = 13;
    public const int DATASPACEID_FIELD_ID = 14;


    public FulltextIndexesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int UniqueIndexId
    {
        get
        {
            return base.GetInt32(UNIQUEINDEXID_FIELD_ID);
        }
    }

    public int? FulltextCatalogId
    {
        get
        {
            return base.GetNullableInt32(FULLTEXTCATALOGID_FIELD_ID);
        }
    }

    public bool IsEnabled
    {
        get
        {
            return base.GetBoolean(ISENABLED_FIELD_ID);
        }
    }

    public string? ChangeTrackingState
    {
        get
        {
            return base.GetNullableString(CHANGETRACKINGSTATE_FIELD_ID);
        }
    }

    public string? ChangeTrackingStateDesc
    {
        get
        {
            return base.GetNullableString(CHANGETRACKINGSTATEDESC_FIELD_ID);
        }
    }

    public bool HasCrawlCompleted
    {
        get
        {
            return base.GetBoolean(HASCRAWLCOMPLETED_FIELD_ID);
        }
    }

    public string CrawlType
    {
        get
        {
            return base.GetString(CRAWLTYPE_FIELD_ID);
        }
    }

    public string? CrawlTypeDesc
    {
        get
        {
            return base.GetNullableString(CRAWLTYPEDESC_FIELD_ID);
        }
    }

    public DateTime? CrawlStartDate
    {
        get
        {
            return base.GetNullableDateTime(CRAWLSTARTDATE_FIELD_ID);
        }
    }

    public DateTime? CrawlEndDate
    {
        get
        {
            return base.GetNullableDateTime(CRAWLENDDATE_FIELD_ID);
        }
    }

    public byte[]? IncrementalTimestamp
    {
        get
        {
            return base.GetNullableBinary(INCREMENTALTIMESTAMP_FIELD_ID);
        }
    }

    public int? StoplistId
    {
        get
        {
            return base.GetNullableInt32(STOPLISTID_FIELD_ID);
        }
    }

    public int? PropertyListId
    {
        get
        {
            return base.GetNullableInt32(PROPERTYLISTID_FIELD_ID);
        }
    }

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }


    public Types.FulltextIndexesDataType ToDataObject()
    {
        return new Types.FulltextIndexesDataType(ObjectId,
            UniqueIndexId,
            FulltextCatalogId,
            IsEnabled,
            ChangeTrackingState,
            ChangeTrackingStateDesc,
            HasCrawlCompleted,
            CrawlType,
            CrawlTypeDesc,
            CrawlStartDate,
            CrawlEndDate,
            IncrementalTimestamp,
            StoplistId,
            PropertyListId,
            DataSpaceId);
    }

    public List<Types.FulltextIndexesDataType> ToList()
    {
        var list = new List<Types.FulltextIndexesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
