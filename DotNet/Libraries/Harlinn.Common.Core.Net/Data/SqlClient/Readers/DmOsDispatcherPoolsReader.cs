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

public class DmOsDispatcherPoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_dispatcher_pools]";
    public const string TableName = "dm_os_dispatcher_pools";
    public const string ShortName = "dodp";
    public const string Sql = """
        SELECT
          dodp.[dispatcher_pool_address],
          dodp.[Type],
          dodp.[Name],
          dodp.[dispatcher_count],
          dodp.[dispatcher_ideal_count],
          dodp.[dispatcher_timeout_ms],
          dodp.[dispatcher_waiting_count],
          dodp.[queue_length]
        FROM
          [sys].[dm_os_dispatcher_pools] dodp
        """;

    public const int DISPATCHERPOOLADDRESS_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int DISPATCHERCOUNT_FIELD_ID = 3;
    public const int DISPATCHERIDEALCOUNT_FIELD_ID = 4;
    public const int DISPATCHERTIMEOUTMS_FIELD_ID = 5;
    public const int DISPATCHERWAITINGCOUNT_FIELD_ID = 6;
    public const int QUEUELENGTH_FIELD_ID = 7;


    public DmOsDispatcherPoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsDispatcherPoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsDispatcherPoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] DispatcherPoolAddress
    {
        get
        {
            return base.GetBinary(DISPATCHERPOOLADDRESS_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int DispatcherCount
    {
        get
        {
            return base.GetInt32(DISPATCHERCOUNT_FIELD_ID);
        }
    }

    public int DispatcherIdealCount
    {
        get
        {
            return base.GetInt32(DISPATCHERIDEALCOUNT_FIELD_ID);
        }
    }

    public int DispatcherTimeoutMs
    {
        get
        {
            return base.GetInt32(DISPATCHERTIMEOUTMS_FIELD_ID);
        }
    }

    public int DispatcherWaitingCount
    {
        get
        {
            return base.GetInt32(DISPATCHERWAITINGCOUNT_FIELD_ID);
        }
    }

    public int QueueLength
    {
        get
        {
            return base.GetInt32(QUEUELENGTH_FIELD_ID);
        }
    }


    public Types.DmOsDispatcherPoolsDataType ToDataObject()
    {
        return new Types.DmOsDispatcherPoolsDataType(DispatcherPoolAddress,
            Type,
            Name,
            DispatcherCount,
            DispatcherIdealCount,
            DispatcherTimeoutMs,
            DispatcherWaitingCount,
            QueueLength);
    }

    public List<Types.DmOsDispatcherPoolsDataType> ToList()
    {
        var list = new List<Types.DmOsDispatcherPoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
