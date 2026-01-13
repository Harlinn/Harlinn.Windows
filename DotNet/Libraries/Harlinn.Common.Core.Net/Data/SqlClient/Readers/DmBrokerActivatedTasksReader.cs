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

public class DmBrokerActivatedTasksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_broker_activated_tasks]";
    public const string TableName = "dm_broker_activated_tasks";
    public const string ShortName = "dbat";
    public const string Sql = """
        SELECT
          dbat.[Spid],
          dbat.[database_id],
          dbat.[queue_id],
          dbat.[procedure_name],
          dbat.[execute_as]
        FROM
          [sys].[dm_broker_activated_tasks] dbat
        """;

    public const int SPID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int QUEUEID_FIELD_ID = 2;
    public const int PROCEDURENAME_FIELD_ID = 3;
    public const int EXECUTEAS_FIELD_ID = 4;


    public DmBrokerActivatedTasksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmBrokerActivatedTasksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmBrokerActivatedTasksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? Spid
    {
        get
        {
            return base.GetNullableInt32(SPID_FIELD_ID);
        }
    }

    public short? DatabaseId
    {
        get
        {
            return base.GetNullableInt16(DATABASEID_FIELD_ID);
        }
    }

    public int? QueueId
    {
        get
        {
            return base.GetNullableInt32(QUEUEID_FIELD_ID);
        }
    }

    public string? ProcedureName
    {
        get
        {
            return base.GetNullableString(PROCEDURENAME_FIELD_ID);
        }
    }

    public int? ExecuteAs
    {
        get
        {
            return base.GetNullableInt32(EXECUTEAS_FIELD_ID);
        }
    }


    public Types.DmBrokerActivatedTasksDataType ToDataObject()
    {
        return new Types.DmBrokerActivatedTasksDataType(Spid,
            DatabaseId,
            QueueId,
            ProcedureName,
            ExecuteAs);
    }

    public List<Types.DmBrokerActivatedTasksDataType> ToList()
    {
        var list = new List<Types.DmBrokerActivatedTasksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
