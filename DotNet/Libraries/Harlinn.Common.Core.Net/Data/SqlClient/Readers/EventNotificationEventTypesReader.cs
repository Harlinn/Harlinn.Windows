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

public class EventNotificationEventTypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[event_notification_event_types]";
    public const string TableName = "event_notification_event_types";
    public const string ShortName = "enet";
    public const string Sql = """
        SELECT
          enet.[Type],
          enet.[type_name],
          enet.[parent_type]
        FROM
          [sys].[event_notification_event_types] enet
        """;

    public const int TYPE_FIELD_ID = 0;
    public const int TYPENAME_FIELD_ID = 1;
    public const int PARENTTYPE_FIELD_ID = 2;


    public EventNotificationEventTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public EventNotificationEventTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public EventNotificationEventTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Type
    {
        get
        {
            return base.GetInt32(TYPE_FIELD_ID);
        }
    }

    public string? TypeName
    {
        get
        {
            return base.GetNullableString(TYPENAME_FIELD_ID);
        }
    }

    public int? ParentType
    {
        get
        {
            return base.GetNullableInt32(PARENTTYPE_FIELD_ID);
        }
    }


    public Types.EventNotificationEventTypesDataType ToDataObject()
    {
        return new Types.EventNotificationEventTypesDataType(Type,
            TypeName,
            ParentType);
    }

    public List<Types.EventNotificationEventTypesDataType> ToList()
    {
        var list = new List<Types.EventNotificationEventTypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
