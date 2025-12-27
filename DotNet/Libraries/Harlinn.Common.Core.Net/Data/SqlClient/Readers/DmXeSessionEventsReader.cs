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

public class DmXeSessionEventsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_session_events]";
    public const string TableName = "dm_xe_session_events";
    public const string ShortName = "dxse";
    public const string Sql = """
        SELECT
          dxse.[event_session_address],
          dxse.[event_name],
          dxse.[event_package_guid],
          dxse.[event_predicate]
        FROM
          [sys].[dm_xe_session_events] dxse
        """;

    public const int EVENTSESSIONADDRESS_FIELD_ID = 0;
    public const int EVENTNAME_FIELD_ID = 1;
    public const int EVENTPACKAGEGUID_FIELD_ID = 2;
    public const int EVENTPREDICATE_FIELD_ID = 3;


    public DmXeSessionEventsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionEventsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionEventsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] EventSessionAddress
    {
        get
        {
            return base.GetBinary(EVENTSESSIONADDRESS_FIELD_ID);
        }
    }

    public string EventName
    {
        get
        {
            return base.GetString(EVENTNAME_FIELD_ID);
        }
    }

    public Guid EventPackageGuid
    {
        get
        {
            return base.GetGuid(EVENTPACKAGEGUID_FIELD_ID);
        }
    }

    public string? EventPredicate
    {
        get
        {
            return base.GetNullableString(EVENTPREDICATE_FIELD_ID);
        }
    }


    public Types.DmXeSessionEventsDataType ToDataObject()
    {
        return new Types.DmXeSessionEventsDataType(EventSessionAddress,
            EventName,
            EventPackageGuid,
            EventPredicate);
    }

    public List<Types.DmXeSessionEventsDataType> ToList()
    {
        var list = new List<Types.DmXeSessionEventsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
