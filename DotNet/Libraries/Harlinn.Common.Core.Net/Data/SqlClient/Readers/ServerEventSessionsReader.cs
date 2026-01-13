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

public class ServerEventSessionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_event_sessions]";
    public const string TableName = "server_event_sessions";
    public const string ShortName = "ses";
    public const string Sql = """
        SELECT
          ses.[event_session_id],
          ses.[Name],
          ses.[event_retention_mode],
          ses.[event_retention_mode_desc],
          ses.[max_dispatch_latency],
          ses.[max_memory],
          ses.[max_event_size],
          ses.[memory_partition_mode],
          ses.[memory_partition_mode_desc],
          ses.[track_causality],
          ses.[startup_state],
          ses.[has_long_running_target]
        FROM
          [sys].[server_event_sessions] ses
        """;

    public const int EVENTSESSIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int EVENTRETENTIONMODE_FIELD_ID = 2;
    public const int EVENTRETENTIONMODEDESC_FIELD_ID = 3;
    public const int MAXDISPATCHLATENCY_FIELD_ID = 4;
    public const int MAXMEMORY_FIELD_ID = 5;
    public const int MAXEVENTSIZE_FIELD_ID = 6;
    public const int MEMORYPARTITIONMODE_FIELD_ID = 7;
    public const int MEMORYPARTITIONMODEDESC_FIELD_ID = 8;
    public const int TRACKCAUSALITY_FIELD_ID = 9;
    public const int STARTUPSTATE_FIELD_ID = 10;
    public const int HASLONGRUNNINGTARGET_FIELD_ID = 11;


    public ServerEventSessionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerEventSessionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerEventSessionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int EventSessionId
    {
        get
        {
            return base.GetInt32(EVENTSESSIONID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? EventRetentionMode
    {
        get
        {
            return base.GetNullableString(EVENTRETENTIONMODE_FIELD_ID);
        }
    }

    public string? EventRetentionModeDesc
    {
        get
        {
            return base.GetNullableString(EVENTRETENTIONMODEDESC_FIELD_ID);
        }
    }

    public int? MaxDispatchLatency
    {
        get
        {
            return base.GetNullableInt32(MAXDISPATCHLATENCY_FIELD_ID);
        }
    }

    public int? MaxMemory
    {
        get
        {
            return base.GetNullableInt32(MAXMEMORY_FIELD_ID);
        }
    }

    public int? MaxEventSize
    {
        get
        {
            return base.GetNullableInt32(MAXEVENTSIZE_FIELD_ID);
        }
    }

    public string? MemoryPartitionMode
    {
        get
        {
            return base.GetNullableString(MEMORYPARTITIONMODE_FIELD_ID);
        }
    }

    public string? MemoryPartitionModeDesc
    {
        get
        {
            return base.GetNullableString(MEMORYPARTITIONMODEDESC_FIELD_ID);
        }
    }

    public bool? TrackCausality
    {
        get
        {
            return base.GetNullableBoolean(TRACKCAUSALITY_FIELD_ID);
        }
    }

    public bool? StartupState
    {
        get
        {
            return base.GetNullableBoolean(STARTUPSTATE_FIELD_ID);
        }
    }

    public bool? HasLongRunningTarget
    {
        get
        {
            return base.GetNullableBoolean(HASLONGRUNNINGTARGET_FIELD_ID);
        }
    }


    public Types.ServerEventSessionsDataType ToDataObject()
    {
        return new Types.ServerEventSessionsDataType(EventSessionId,
            Name,
            EventRetentionMode,
            EventRetentionModeDesc,
            MaxDispatchLatency,
            MaxMemory,
            MaxEventSize,
            MemoryPartitionMode,
            MemoryPartitionModeDesc,
            TrackCausality,
            StartupState,
            HasLongRunningTarget);
    }

    public List<Types.ServerEventSessionsDataType> ToList()
    {
        var list = new List<Types.ServerEventSessionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
