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

public class DmOsHostsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_hosts]";
    public const string TableName = "dm_os_hosts";
    public const string ShortName = "doh";
    public const string Sql = """
        SELECT
          doh.[host_address],
          doh.[Type],
          doh.[Name],
          doh.[enqueued_tasks_count],
          doh.[active_tasks_count],
          doh.[completed_ios_count],
          doh.[completed_ios_in_bytes],
          doh.[active_ios_count],
          doh.[default_memory_clerk_address]
        FROM
          [sys].[dm_os_hosts] doh
        """;

    public const int HOSTADDRESS_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int ENQUEUEDTASKSCOUNT_FIELD_ID = 3;
    public const int ACTIVETASKSCOUNT_FIELD_ID = 4;
    public const int COMPLETEDIOSCOUNT_FIELD_ID = 5;
    public const int COMPLETEDIOSINBYTES_FIELD_ID = 6;
    public const int ACTIVEIOSCOUNT_FIELD_ID = 7;
    public const int DEFAULTMEMORYCLERKADDRESS_FIELD_ID = 8;


    public DmOsHostsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsHostsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsHostsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] HostAddress
    {
        get
        {
            return base.GetBinary(HOSTADDRESS_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int? EnqueuedTasksCount
    {
        get
        {
            return base.GetNullableInt32(ENQUEUEDTASKSCOUNT_FIELD_ID);
        }
    }

    public int? ActiveTasksCount
    {
        get
        {
            return base.GetNullableInt32(ACTIVETASKSCOUNT_FIELD_ID);
        }
    }

    public int? CompletedIosCount
    {
        get
        {
            return base.GetNullableInt32(COMPLETEDIOSCOUNT_FIELD_ID);
        }
    }

    public long? CompletedIosInBytes
    {
        get
        {
            return base.GetNullableInt64(COMPLETEDIOSINBYTES_FIELD_ID);
        }
    }

    public int? ActiveIosCount
    {
        get
        {
            return base.GetNullableInt32(ACTIVEIOSCOUNT_FIELD_ID);
        }
    }

    public byte[] DefaultMemoryClerkAddress
    {
        get
        {
            return base.GetBinary(DEFAULTMEMORYCLERKADDRESS_FIELD_ID);
        }
    }


    public Types.DmOsHostsDataType ToDataObject()
    {
        return new Types.DmOsHostsDataType(HostAddress,
            Type,
            Name,
            EnqueuedTasksCount,
            ActiveTasksCount,
            CompletedIosCount,
            CompletedIosInBytes,
            ActiveIosCount,
            DefaultMemoryClerkAddress);
    }

    public List<Types.DmOsHostsDataType> ToList()
    {
        var list = new List<Types.DmOsHostsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
