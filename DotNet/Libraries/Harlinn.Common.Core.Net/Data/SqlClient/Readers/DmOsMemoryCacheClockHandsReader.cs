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

public class DmOsMemoryCacheClockHandsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_cache_clock_hands]";
    public const string TableName = "dm_os_memory_cache_clock_hands";
    public const string ShortName = "domcch";
    public const string Sql = """
        SELECT
          domcch.[cache_address],
          domcch.[Name],
          domcch.[Type],
          domcch.[clock_hand],
          domcch.[clock_status],
          domcch.[rounds_count],
          domcch.[removed_all_rounds_count],
          domcch.[updated_last_round_count],
          domcch.[removed_last_round_count],
          domcch.[last_tick_time],
          domcch.[round_start_time],
          domcch.[last_round_start_time]
        FROM
          [sys].[dm_os_memory_cache_clock_hands] domcch
        """;

    public const int CACHEADDRESS_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int CLOCKHAND_FIELD_ID = 3;
    public const int CLOCKSTATUS_FIELD_ID = 4;
    public const int ROUNDSCOUNT_FIELD_ID = 5;
    public const int REMOVEDALLROUNDSCOUNT_FIELD_ID = 6;
    public const int UPDATEDLASTROUNDCOUNT_FIELD_ID = 7;
    public const int REMOVEDLASTROUNDCOUNT_FIELD_ID = 8;
    public const int LASTTICKTIME_FIELD_ID = 9;
    public const int ROUNDSTARTTIME_FIELD_ID = 10;
    public const int LASTROUNDSTARTTIME_FIELD_ID = 11;


    public DmOsMemoryCacheClockHandsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheClockHandsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheClockHandsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] CacheAddress
    {
        get
        {
            return base.GetBinary(CACHEADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string ClockHand
    {
        get
        {
            return base.GetString(CLOCKHAND_FIELD_ID);
        }
    }

    public string ClockStatus
    {
        get
        {
            return base.GetString(CLOCKSTATUS_FIELD_ID);
        }
    }

    public long RoundsCount
    {
        get
        {
            return base.GetInt64(ROUNDSCOUNT_FIELD_ID);
        }
    }

    public long RemovedAllRoundsCount
    {
        get
        {
            return base.GetInt64(REMOVEDALLROUNDSCOUNT_FIELD_ID);
        }
    }

    public long UpdatedLastRoundCount
    {
        get
        {
            return base.GetInt64(UPDATEDLASTROUNDCOUNT_FIELD_ID);
        }
    }

    public long RemovedLastRoundCount
    {
        get
        {
            return base.GetInt64(REMOVEDLASTROUNDCOUNT_FIELD_ID);
        }
    }

    public long LastTickTime
    {
        get
        {
            return base.GetInt64(LASTTICKTIME_FIELD_ID);
        }
    }

    public long RoundStartTime
    {
        get
        {
            return base.GetInt64(ROUNDSTARTTIME_FIELD_ID);
        }
    }

    public long LastRoundStartTime
    {
        get
        {
            return base.GetInt64(LASTROUNDSTARTTIME_FIELD_ID);
        }
    }


    public Types.DmOsMemoryCacheClockHandsDataType ToDataObject()
    {
        return new Types.DmOsMemoryCacheClockHandsDataType(CacheAddress,
            Name,
            Type,
            ClockHand,
            ClockStatus,
            RoundsCount,
            RemovedAllRoundsCount,
            UpdatedLastRoundCount,
            RemovedLastRoundCount,
            LastTickTime,
            RoundStartTime,
            LastRoundStartTime);
    }

    public List<Types.DmOsMemoryCacheClockHandsDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryCacheClockHandsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
