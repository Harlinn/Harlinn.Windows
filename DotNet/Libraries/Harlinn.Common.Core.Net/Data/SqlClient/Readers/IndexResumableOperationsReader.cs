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

public class IndexResumableOperationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[index_resumable_operations]";
    public const string TableName = "index_resumable_operations";
    public const string ShortName = "iro";
    public const string Sql = """
        SELECT
          iro.[object_id],
          iro.[index_id],
          iro.[Name],
          iro.[sql_text],
          iro.[last_max_dop_used],
          iro.[partition_number],
          iro.[State],
          iro.[state_desc],
          iro.[start_time],
          iro.[last_pause_time],
          iro.[total_execution_time],
          iro.[percent_complete],
          iro.[page_count]
        FROM
          [sys].[index_resumable_operations] iro
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int SQLTEXT_FIELD_ID = 3;
    public const int LASTMAXDOPUSED_FIELD_ID = 4;
    public const int PARTITIONNUMBER_FIELD_ID = 5;
    public const int STATE_FIELD_ID = 6;
    public const int STATEDESC_FIELD_ID = 7;
    public const int STARTTIME_FIELD_ID = 8;
    public const int LASTPAUSETIME_FIELD_ID = 9;
    public const int TOTALEXECUTIONTIME_FIELD_ID = 10;
    public const int PERCENTCOMPLETE_FIELD_ID = 11;
    public const int PAGECOUNT_FIELD_ID = 12;


    public IndexResumableOperationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public IndexResumableOperationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public IndexResumableOperationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string? SqlText
    {
        get
        {
            return base.GetNullableString(SQLTEXT_FIELD_ID);
        }
    }

    public short LastMaxDopUsed
    {
        get
        {
            return base.GetInt16(LASTMAXDOPUSED_FIELD_ID);
        }
    }

    public int? PartitionNumber
    {
        get
        {
            return base.GetNullableInt32(PARTITIONNUMBER_FIELD_ID);
        }
    }

    public byte State
    {
        get
        {
            return base.GetByte(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime? LastPauseTime
    {
        get
        {
            return base.GetNullableDateTime(LASTPAUSETIME_FIELD_ID);
        }
    }

    public int TotalExecutionTime
    {
        get
        {
            return base.GetInt32(TOTALEXECUTIONTIME_FIELD_ID);
        }
    }

    public double PercentComplete
    {
        get
        {
            return base.GetDouble(PERCENTCOMPLETE_FIELD_ID);
        }
    }

    public long PageCount
    {
        get
        {
            return base.GetInt64(PAGECOUNT_FIELD_ID);
        }
    }


    public Types.IndexResumableOperationsDataType ToDataObject()
    {
        return new Types.IndexResumableOperationsDataType(ObjectId,
            IndexId,
            Name,
            SqlText,
            LastMaxDopUsed,
            PartitionNumber,
            State,
            StateDesc,
            StartTime,
            LastPauseTime,
            TotalExecutionTime,
            PercentComplete,
            PageCount);
    }

    public List<Types.IndexResumableOperationsDataType> ToList()
    {
        var list = new List<Types.IndexResumableOperationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
