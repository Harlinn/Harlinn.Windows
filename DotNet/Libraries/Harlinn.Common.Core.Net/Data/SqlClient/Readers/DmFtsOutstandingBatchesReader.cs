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

public class DmFtsOutstandingBatchesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_outstanding_batches]";
    public const string TableName = "dm_fts_outstanding_batches";
    public const string ShortName = "dfob";
    public const string Sql = """
        SELECT
          dfob.[database_id],
          dfob.[catalog_id],
          dfob.[table_id],
          dfob.[batch_id],
          dfob.[memory_address],
          dfob.[crawl_memory_address],
          dfob.[memregion_memory_address],
          dfob.[hr_batch],
          dfob.[is_retry_batch],
          dfob.[retry_hints],
          dfob.[retry_hints_description],
          dfob.[doc_failed],
          dfob.[batch_timestamp]
        FROM
          [sys].[dm_fts_outstanding_batches] dfob
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int CATALOGID_FIELD_ID = 1;
    public const int TABLEID_FIELD_ID = 2;
    public const int BATCHID_FIELD_ID = 3;
    public const int MEMORYADDRESS_FIELD_ID = 4;
    public const int CRAWLMEMORYADDRESS_FIELD_ID = 5;
    public const int MEMREGIONMEMORYADDRESS_FIELD_ID = 6;
    public const int HRBATCH_FIELD_ID = 7;
    public const int ISRETRYBATCH_FIELD_ID = 8;
    public const int RETRYHINTS_FIELD_ID = 9;
    public const int RETRYHINTSDESCRIPTION_FIELD_ID = 10;
    public const int DOCFAILED_FIELD_ID = 11;
    public const int BATCHTIMESTAMP_FIELD_ID = 12;


    public DmFtsOutstandingBatchesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsOutstandingBatchesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsOutstandingBatchesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int BatchId
    {
        get
        {
            return base.GetInt32(BATCHID_FIELD_ID);
        }
    }

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public byte[] CrawlMemoryAddress
    {
        get
        {
            return base.GetBinary(CRAWLMEMORYADDRESS_FIELD_ID);
        }
    }

    public byte[] MemregionMemoryAddress
    {
        get
        {
            return base.GetBinary(MEMREGIONMEMORYADDRESS_FIELD_ID);
        }
    }

    public int HrBatch
    {
        get
        {
            return base.GetInt32(HRBATCH_FIELD_ID);
        }
    }

    public bool IsRetryBatch
    {
        get
        {
            return base.GetBoolean(ISRETRYBATCH_FIELD_ID);
        }
    }

    public int RetryHints
    {
        get
        {
            return base.GetInt32(RETRYHINTS_FIELD_ID);
        }
    }

    public string? RetryHintsDescription
    {
        get
        {
            return base.GetNullableString(RETRYHINTSDESCRIPTION_FIELD_ID);
        }
    }

    public long DocFailed
    {
        get
        {
            return base.GetInt64(DOCFAILED_FIELD_ID);
        }
    }

    public byte[] BatchTimestamp
    {
        get
        {
            return base.GetBinary(BATCHTIMESTAMP_FIELD_ID);
        }
    }


    public Types.DmFtsOutstandingBatchesDataType ToDataObject()
    {
        return new Types.DmFtsOutstandingBatchesDataType(DatabaseId,
            CatalogId,
            TableId,
            BatchId,
            MemoryAddress,
            CrawlMemoryAddress,
            MemregionMemoryAddress,
            HrBatch,
            IsRetryBatch,
            RetryHints,
            RetryHintsDescription,
            DocFailed,
            BatchTimestamp);
    }

    public List<Types.DmFtsOutstandingBatchesDataType> ToList()
    {
        var list = new List<Types.DmFtsOutstandingBatchesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
