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

public class DmOsDispatchersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_dispatchers]";
    public const string TableName = "dm_os_dispatchers";
    public const string ShortName = "dod";
    public const string Sql = """
        SELECT
          dod.[dispatcher_pool_address],
          dod.[task_address],
          dod.[State],
          dod.[wait_duration],
          dod.[current_item_duration],
          dod.[items_processed],
          dod.[fade_end_time]
        FROM
          [sys].[dm_os_dispatchers] dod
        """;

    public const int DISPATCHERPOOLADDRESS_FIELD_ID = 0;
    public const int TASKADDRESS_FIELD_ID = 1;
    public const int STATE_FIELD_ID = 2;
    public const int WAITDURATION_FIELD_ID = 3;
    public const int CURRENTITEMDURATION_FIELD_ID = 4;
    public const int ITEMSPROCESSED_FIELD_ID = 5;
    public const int FADEENDTIME_FIELD_ID = 6;


    public DmOsDispatchersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsDispatchersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsDispatchersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte[] TaskAddress
    {
        get
        {
            return base.GetBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public string State
    {
        get
        {
            return base.GetString(STATE_FIELD_ID);
        }
    }

    public long? WaitDuration
    {
        get
        {
            return base.GetNullableInt64(WAITDURATION_FIELD_ID);
        }
    }

    public long? CurrentItemDuration
    {
        get
        {
            return base.GetNullableInt64(CURRENTITEMDURATION_FIELD_ID);
        }
    }

    public long ItemsProcessed
    {
        get
        {
            return base.GetInt64(ITEMSPROCESSED_FIELD_ID);
        }
    }

    public int? FadeEndTime
    {
        get
        {
            return base.GetNullableInt32(FADEENDTIME_FIELD_ID);
        }
    }


    public Types.DmOsDispatchersDataType ToDataObject()
    {
        return new Types.DmOsDispatchersDataType(DispatcherPoolAddress,
            TaskAddress,
            State,
            WaitDuration,
            CurrentItemDuration,
            ItemsProcessed,
            FadeEndTime);
    }

    public List<Types.DmOsDispatchersDataType> ToList()
    {
        var list = new List<Types.DmOsDispatchersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
