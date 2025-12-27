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

public class DmBrokerQueueMonitorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_broker_queue_monitors]";
    public const string TableName = "dm_broker_queue_monitors";
    public const string ShortName = "dbqm";
    public const string Sql = """
        SELECT
          dbqm.[database_id],
          dbqm.[queue_id],
          dbqm.[State],
          dbqm.[last_empty_rowset_time],
          dbqm.[last_activated_time],
          dbqm.[tasks_waiting]
        FROM
          [sys].[dm_broker_queue_monitors] dbqm
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int QUEUEID_FIELD_ID = 1;
    public const int STATE_FIELD_ID = 2;
    public const int LASTEMPTYROWSETTIME_FIELD_ID = 3;
    public const int LASTACTIVATEDTIME_FIELD_ID = 4;
    public const int TASKSWAITING_FIELD_ID = 5;


    public DmBrokerQueueMonitorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmBrokerQueueMonitorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmBrokerQueueMonitorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public int? QueueId
    {
        get
        {
            return base.GetNullableInt32(QUEUEID_FIELD_ID);
        }
    }

    public string? State
    {
        get
        {
            return base.GetNullableString(STATE_FIELD_ID);
        }
    }

    public DateTime? LastEmptyRowsetTime
    {
        get
        {
            return base.GetNullableDateTime(LASTEMPTYROWSETTIME_FIELD_ID);
        }
    }

    public DateTime? LastActivatedTime
    {
        get
        {
            return base.GetNullableDateTime(LASTACTIVATEDTIME_FIELD_ID);
        }
    }

    public int? TasksWaiting
    {
        get
        {
            return base.GetNullableInt32(TASKSWAITING_FIELD_ID);
        }
    }


    public Types.DmBrokerQueueMonitorsDataType ToDataObject()
    {
        return new Types.DmBrokerQueueMonitorsDataType(DatabaseId,
            QueueId,
            State,
            LastEmptyRowsetTime,
            LastActivatedTime,
            TasksWaiting);
    }

    public List<Types.DmBrokerQueueMonitorsDataType> ToList()
    {
        var list = new List<Types.DmBrokerQueueMonitorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
