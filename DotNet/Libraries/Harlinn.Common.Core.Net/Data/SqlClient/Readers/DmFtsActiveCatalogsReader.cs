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

public class DmFtsActiveCatalogsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_active_catalogs]";
    public const string TableName = "dm_fts_active_catalogs";
    public const string ShortName = "dfac";
    public const string Sql = """
        SELECT
          dfac.[database_id],
          dfac.[catalog_id],
          dfac.[memory_address],
          dfac.[Name],
          dfac.[is_paused],
          dfac.[Status],
          dfac.[status_description],
          dfac.[previous_status],
          dfac.[previous_status_description],
          dfac.[worker_count],
          dfac.[active_fts_index_count],
          dfac.[auto_population_count],
          dfac.[manual_population_count],
          dfac.[full_incremental_population_count],
          dfac.[row_count_in_thousands],
          dfac.[is_importing]
        FROM
          [sys].[dm_fts_active_catalogs] dfac
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int CATALOGID_FIELD_ID = 1;
    public const int MEMORYADDRESS_FIELD_ID = 2;
    public const int NAME_FIELD_ID = 3;
    public const int ISPAUSED_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int STATUSDESCRIPTION_FIELD_ID = 6;
    public const int PREVIOUSSTATUS_FIELD_ID = 7;
    public const int PREVIOUSSTATUSDESCRIPTION_FIELD_ID = 8;
    public const int WORKERCOUNT_FIELD_ID = 9;
    public const int ACTIVEFTSINDEXCOUNT_FIELD_ID = 10;
    public const int AUTOPOPULATIONCOUNT_FIELD_ID = 11;
    public const int MANUALPOPULATIONCOUNT_FIELD_ID = 12;
    public const int FULLINCREMENTALPOPULATIONCOUNT_FIELD_ID = 13;
    public const int ROWCOUNTINTHOUSANDS_FIELD_ID = 14;
    public const int ISIMPORTING_FIELD_ID = 15;


    public DmFtsActiveCatalogsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsActiveCatalogsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsActiveCatalogsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte[] MemoryAddress
    {
        get
        {
            return base.GetBinary(MEMORYADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public bool IsPaused
    {
        get
        {
            return base.GetBoolean(ISPAUSED_FIELD_ID);
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

    public int PreviousStatus
    {
        get
        {
            return base.GetInt32(PREVIOUSSTATUS_FIELD_ID);
        }
    }

    public string? PreviousStatusDescription
    {
        get
        {
            return base.GetNullableString(PREVIOUSSTATUSDESCRIPTION_FIELD_ID);
        }
    }

    public int WorkerCount
    {
        get
        {
            return base.GetInt32(WORKERCOUNT_FIELD_ID);
        }
    }

    public int ActiveFtsIndexCount
    {
        get
        {
            return base.GetInt32(ACTIVEFTSINDEXCOUNT_FIELD_ID);
        }
    }

    public int AutoPopulationCount
    {
        get
        {
            return base.GetInt32(AUTOPOPULATIONCOUNT_FIELD_ID);
        }
    }

    public int ManualPopulationCount
    {
        get
        {
            return base.GetInt32(MANUALPOPULATIONCOUNT_FIELD_ID);
        }
    }

    public int FullIncrementalPopulationCount
    {
        get
        {
            return base.GetInt32(FULLINCREMENTALPOPULATIONCOUNT_FIELD_ID);
        }
    }

    public int RowCountInThousands
    {
        get
        {
            return base.GetInt32(ROWCOUNTINTHOUSANDS_FIELD_ID);
        }
    }

    public bool IsImporting
    {
        get
        {
            return base.GetBoolean(ISIMPORTING_FIELD_ID);
        }
    }


    public Types.DmFtsActiveCatalogsDataType ToDataObject()
    {
        return new Types.DmFtsActiveCatalogsDataType(DatabaseId,
            CatalogId,
            MemoryAddress,
            Name,
            IsPaused,
            Status,
            StatusDescription,
            PreviousStatus,
            PreviousStatusDescription,
            WorkerCount,
            ActiveFtsIndexCount,
            AutoPopulationCount,
            ManualPopulationCount,
            FullIncrementalPopulationCount,
            RowCountInThousands,
            IsImporting);
    }

    public List<Types.DmFtsActiveCatalogsDataType> ToList()
    {
        var list = new List<Types.DmFtsActiveCatalogsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
