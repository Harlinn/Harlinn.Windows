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

public class TriggerEventsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trigger_events]";
    public const string TableName = "trigger_events";
    public const string ShortName = "te0";
    public const string Sql = """
        SELECT
          te0.[object_id],
          te0.[Type],
          te0.[type_desc],
          te0.[is_first],
          te0.[is_last],
          te0.[event_group_type],
          te0.[event_group_type_desc],
          te0.[is_trigger_event]
        FROM
          [sys].[trigger_events] te0
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int TYPEDESC_FIELD_ID = 2;
    public const int ISFIRST_FIELD_ID = 3;
    public const int ISLAST_FIELD_ID = 4;
    public const int EVENTGROUPTYPE_FIELD_ID = 5;
    public const int EVENTGROUPTYPEDESC_FIELD_ID = 6;
    public const int ISTRIGGEREVENT_FIELD_ID = 7;


    public TriggerEventsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TriggerEventsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TriggerEventsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int Type
    {
        get
        {
            return base.GetInt32(TYPE_FIELD_ID);
        }
    }

    public string TypeDesc
    {
        get
        {
            return base.GetString(TYPEDESC_FIELD_ID);
        }
    }

    public bool? IsFirst
    {
        get
        {
            return base.GetNullableBoolean(ISFIRST_FIELD_ID);
        }
    }

    public bool? IsLast
    {
        get
        {
            return base.GetNullableBoolean(ISLAST_FIELD_ID);
        }
    }

    public int? EventGroupType
    {
        get
        {
            return base.GetNullableInt32(EVENTGROUPTYPE_FIELD_ID);
        }
    }

    public string? EventGroupTypeDesc
    {
        get
        {
            return base.GetNullableString(EVENTGROUPTYPEDESC_FIELD_ID);
        }
    }

    public bool? IsTriggerEvent
    {
        get
        {
            return base.GetNullableBoolean(ISTRIGGEREVENT_FIELD_ID);
        }
    }


    public Types.TriggerEvent ToDataObject()
    {
        return new Types.TriggerEvent(ObjectId,
            Type,
            TypeDesc,
            IsFirst,
            IsLast,
            EventGroupType,
            EventGroupTypeDesc,
            IsTriggerEvent);
    }

    public List<Types.TriggerEvent> ToList()
    {
        var list = new List<Types.TriggerEvent>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
