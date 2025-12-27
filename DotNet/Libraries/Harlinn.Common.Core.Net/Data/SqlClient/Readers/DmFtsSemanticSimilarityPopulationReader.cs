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

public class DmFtsSemanticSimilarityPopulationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_semantic_similarity_population]";
    public const string TableName = "dm_fts_semantic_similarity_population";
    public const string ShortName = "dfssp";
    public const string Sql = """
        SELECT
          dfssp.[database_id],
          dfssp.[catalog_id],
          dfssp.[table_id],
          dfssp.[document_count],
          dfssp.[document_processed_count],
          dfssp.[completion_type],
          dfssp.[completion_type_description],
          dfssp.[worker_count],
          dfssp.[Status],
          dfssp.[status_description],
          dfssp.[start_time],
          dfssp.[incremental_timestamp]
        FROM
          [sys].[dm_fts_semantic_similarity_population] dfssp
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int CATALOGID_FIELD_ID = 1;
    public const int TABLEID_FIELD_ID = 2;
    public const int DOCUMENTCOUNT_FIELD_ID = 3;
    public const int DOCUMENTPROCESSEDCOUNT_FIELD_ID = 4;
    public const int COMPLETIONTYPE_FIELD_ID = 5;
    public const int COMPLETIONTYPEDESCRIPTION_FIELD_ID = 6;
    public const int WORKERCOUNT_FIELD_ID = 7;
    public const int STATUS_FIELD_ID = 8;
    public const int STATUSDESCRIPTION_FIELD_ID = 9;
    public const int STARTTIME_FIELD_ID = 10;
    public const int INCREMENTALTIMESTAMP_FIELD_ID = 11;


    public DmFtsSemanticSimilarityPopulationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsSemanticSimilarityPopulationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsSemanticSimilarityPopulationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int CatalogId
    {
        get
        {
            return base.GetInt32(CATALOGID_FIELD_ID);
        }
    }

    public int TableId
    {
        get
        {
            return base.GetInt32(TABLEID_FIELD_ID);
        }
    }

    public long DocumentCount
    {
        get
        {
            return base.GetInt64(DOCUMENTCOUNT_FIELD_ID);
        }
    }

    public long DocumentProcessedCount
    {
        get
        {
            return base.GetInt64(DOCUMENTPROCESSEDCOUNT_FIELD_ID);
        }
    }

    public int CompletionType
    {
        get
        {
            return base.GetInt32(COMPLETIONTYPE_FIELD_ID);
        }
    }

    public string? CompletionTypeDescription
    {
        get
        {
            return base.GetNullableString(COMPLETIONTYPEDESCRIPTION_FIELD_ID);
        }
    }

    public int WorkerCount
    {
        get
        {
            return base.GetInt32(WORKERCOUNT_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public string? StatusDescription
    {
        get
        {
            return base.GetNullableString(STATUSDESCRIPTION_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public byte[] IncrementalTimestamp
    {
        get
        {
            return base.GetBinary(INCREMENTALTIMESTAMP_FIELD_ID);
        }
    }


    public Types.DmFtsSemanticSimilarityPopulationDataType ToDataObject()
    {
        return new Types.DmFtsSemanticSimilarityPopulationDataType(DatabaseId,
            CatalogId,
            TableId,
            DocumentCount,
            DocumentProcessedCount,
            CompletionType,
            CompletionTypeDescription,
            WorkerCount,
            Status,
            StatusDescription,
            StartTime,
            IncrementalTimestamp);
    }

    public List<Types.DmFtsSemanticSimilarityPopulationDataType> ToList()
    {
        var list = new List<Types.DmFtsSemanticSimilarityPopulationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
