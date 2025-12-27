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

public class ServerEventsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_events]";
    public const string TableName = "server_events";
    public const string ShortName = "se";
    public const string Sql = """
        SELECT
          se.[object_id],
          se.[Type],
          se.[type_desc],
          se.[is_trigger_event],
          se.[event_group_type],
          se.[event_group_type_desc]
        FROM
          [sys].[server_events] se
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int TYPEDESC_FIELD_ID = 2;
    public const int ISTRIGGEREVENT_FIELD_ID = 3;
    public const int EVENTGROUPTYPE_FIELD_ID = 4;
    public const int EVENTGROUPTYPEDESC_FIELD_ID = 5;


    public ServerEventsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerEventsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerEventsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool? IsTriggerEvent
    {
        get
        {
            return base.GetNullableBoolean(ISTRIGGEREVENT_FIELD_ID);
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


    public Types.ServerEventsDataType ToDataObject()
    {
        return new Types.ServerEventsDataType(ObjectId,
            Type,
            TypeDesc,
            IsTriggerEvent,
            EventGroupType,
            EventGroupTypeDesc);
    }

    public List<Types.ServerEventsDataType> ToList()
    {
        var list = new List<Types.ServerEventsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
