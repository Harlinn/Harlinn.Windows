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

public class DmFtsIndexPopulationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_index_population]";
    public const string TableName = "dm_fts_index_population";
    public const string ShortName = "dfip";
    public const string Sql = """
        SELECT
          dfip.[database_id],
          dfip.[catalog_id],
          dfip.[table_id],
          dfip.[memory_address],
          dfip.[population_type],
          dfip.[population_type_description],
          dfip.[is_clustered_index_scan],
          dfip.[range_count],
          dfip.[completed_range_count],
          dfip.[outstanding_batch_count],
          dfip.[Status],
          dfip.[status_description],
          dfip.[completion_type],
          dfip.[completion_type_description],
          dfip.[worker_count],
          dfip.[queued_population_type],
          dfip.[queued_population_type_description],
          dfip.[start_time],
          dfip.[incremental_timestamp]
        FROM
          [sys].[dm_fts_index_population] dfip
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int CATALOGID_FIELD_ID = 1;
    public const int TABLEID_FIELD_ID = 2;
    public const int MEMORYADDRESS_FIELD_ID = 3;
    public const int POPULATIONTYPE_FIELD_ID = 4;
    public const int POPULATIONTYPEDESCRIPTION_FIELD_ID = 5;
    public const int ISCLUSTEREDINDEXSCAN_FIELD_ID = 6;
    public const int RANGECOUNT_FIELD_ID = 7;
    public const int COMPLETEDRANGECOUNT_FIELD_ID = 8;
    public const int OUTSTANDINGBATCHCOUNT_FIELD_ID = 9;
    public const int STATUS_FIELD_ID = 10;
    public const int STATUSDESCRIPTION_FIELD_ID = 11;
    public const int COMPLETIONTYPE_FIELD_ID = 12;
    public const int COMPLETIONTYPEDESCRIPTION_FIELD_ID = 13;
    public const int WORKERCOUNT_FIELD_ID = 14;
    public const int QUEUEDPOPULATIONTYPE_FIELD_ID = 15;
    public const int QUEUEDPOPULATIONTYPEDESCRIPTION_FIELD_ID = 16;
    public const int STARTTIME_FIELD_ID = 17;
    public const int INCREMENTALTIMESTAMP_FIELD_ID = 18;


    public DmFtsIndexPopulationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsIndexPopulationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsIndexPopulationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public int PopulationType
    {
        get
        {
            return base.GetInt32(POPULATIONTYPE_FIELD_ID);
        }
    }

    public string? PopulationTypeDescription
    {
        get
        {
            return base.GetNullableString(POPULATIONTYPEDESCRIPTION_FIELD_ID);
        }
    }

    public bool IsClusteredIndexScan
    {
        get
        {
            return base.GetBoolean(ISCLUSTEREDINDEXSCAN_FIELD_ID);
        }
    }

    public int RangeCount
    {
        get
        {
            return base.GetInt32(RANGECOUNT_FIELD_ID);
        }
    }

    public int CompletedRangeCount
    {
        get
        {
            return base.GetInt32(COMPLETEDRANGECOUNT_FIELD_ID);
        }
    }

    public int OutstandingBatchCount
    {
        get
        {
            return base.GetInt32(OUTSTANDINGBATCHCOUNT_FIELD_ID);
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

    public int QueuedPopulationType
    {
        get
        {
            return base.GetInt32(QUEUEDPOPULATIONTYPE_FIELD_ID);
        }
    }

    public string? QueuedPopulationTypeDescription
    {
        get
        {
            return base.GetNullableString(QUEUEDPOPULATIONTYPEDESCRIPTION_FIELD_ID);
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


    public Types.DmFtsIndexPopulationDataType ToDataObject()
    {
        return new Types.DmFtsIndexPopulationDataType(DatabaseId,
            CatalogId,
            TableId,
            MemoryAddress,
            PopulationType,
            PopulationTypeDescription,
            IsClusteredIndexScan,
            RangeCount,
            CompletedRangeCount,
            OutstandingBatchCount,
            Status,
            StatusDescription,
            CompletionType,
            CompletionTypeDescription,
            WorkerCount,
            QueuedPopulationType,
            QueuedPopulationTypeDescription,
            StartTime,
            IncrementalTimestamp);
    }

    public List<Types.DmFtsIndexPopulationDataType> ToList()
    {
        var list = new List<Types.DmFtsIndexPopulationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
