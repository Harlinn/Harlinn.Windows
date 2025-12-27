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

public class DmOsLatchStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_latch_stats]";
    public const string TableName = "dm_os_latch_stats";
    public const string ShortName = "dols";
    public const string Sql = """
        SELECT
          dols.[latch_class],
          dols.[waiting_requests_count],
          dols.[wait_time_ms],
          dols.[max_wait_time_ms]
        FROM
          [sys].[dm_os_latch_stats] dols
        """;

    public const int LATCHCLASS_FIELD_ID = 0;
    public const int WAITINGREQUESTSCOUNT_FIELD_ID = 1;
    public const int WAITTIMEMS_FIELD_ID = 2;
    public const int MAXWAITTIMEMS_FIELD_ID = 3;


    public DmOsLatchStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsLatchStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsLatchStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string LatchClass
    {
        get
        {
            return base.GetString(LATCHCLASS_FIELD_ID);
        }
    }

    public long? WaitingRequestsCount
    {
        get
        {
            return base.GetNullableInt64(WAITINGREQUESTSCOUNT_FIELD_ID);
        }
    }

    public long? WaitTimeMs
    {
        get
        {
            return base.GetNullableInt64(WAITTIMEMS_FIELD_ID);
        }
    }

    public long? MaxWaitTimeMs
    {
        get
        {
            return base.GetNullableInt64(MAXWAITTIMEMS_FIELD_ID);
        }
    }


    public Types.DmOsLatchStatsDataType ToDataObject()
    {
        return new Types.DmOsLatchStatsDataType(LatchClass,
            WaitingRequestsCount,
            WaitTimeMs,
            MaxWaitTimeMs);
    }

    public List<Types.DmOsLatchStatsDataType> ToList()
    {
        var list = new List<Types.DmOsLatchStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
