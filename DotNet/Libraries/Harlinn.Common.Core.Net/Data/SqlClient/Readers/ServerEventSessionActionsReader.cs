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

public class ServerEventSessionActionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_event_session_actions]";
    public const string TableName = "server_event_session_actions";
    public const string ShortName = "sesa";
    public const string Sql = """
        SELECT
          sesa.[event_session_id],
          sesa.[event_id],
          sesa.[Name],
          sesa.[Package],
          sesa.[Module]
        FROM
          [sys].[server_event_session_actions] sesa
        """;

    public const int EVENTSESSIONID_FIELD_ID = 0;
    public const int EVENTID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int PACKAGE_FIELD_ID = 3;
    public const int MODULE_FIELD_ID = 4;


    public ServerEventSessionActionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerEventSessionActionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerEventSessionActionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int EventId
    {
        get
        {
            return base.GetInt32(EVENTID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? Package
    {
        get
        {
            return base.GetNullableString(PACKAGE_FIELD_ID);
        }
    }

    public string? Module
    {
        get
        {
            return base.GetNullableString(MODULE_FIELD_ID);
        }
    }


    public Types.ServerEventSessionActionsDataType ToDataObject()
    {
        return new Types.ServerEventSessionActionsDataType(EventSessionId,
            EventId,
            Name,
            Package,
            Module);
    }

    public List<Types.ServerEventSessionActionsDataType> ToList()
    {
        var list = new List<Types.ServerEventSessionActionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
