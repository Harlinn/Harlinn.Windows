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

public class DmOsSpinlockStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_spinlock_stats]";
    public const string TableName = "dm_os_spinlock_stats";
    public const string ShortName = "doss";
    public const string Sql = """
        SELECT
          doss.[Name],
          doss.[Collisions],
          doss.[Spins],
          doss.[spins_per_collision],
          doss.[sleep_time],
          doss.[Backoffs]
        FROM
          [sys].[dm_os_spinlock_stats] doss
        """;

    public const int NAME_FIELD_ID = 0;
    public const int COLLISIONS_FIELD_ID = 1;
    public const int SPINS_FIELD_ID = 2;
    public const int SPINSPERCOLLISION_FIELD_ID = 3;
    public const int SLEEPTIME_FIELD_ID = 4;
    public const int BACKOFFS_FIELD_ID = 5;


    public DmOsSpinlockStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsSpinlockStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsSpinlockStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public long? Collisions
    {
        get
        {
            return base.GetNullableInt64(COLLISIONS_FIELD_ID);
        }
    }

    public long? Spins
    {
        get
        {
            return base.GetNullableInt64(SPINS_FIELD_ID);
        }
    }

    public float? SpinsPerCollision
    {
        get
        {
            return base.GetNullableSingle(SPINSPERCOLLISION_FIELD_ID);
        }
    }

    public long? SleepTime
    {
        get
        {
            return base.GetNullableInt64(SLEEPTIME_FIELD_ID);
        }
    }

    public long? Backoffs
    {
        get
        {
            return base.GetNullableInt64(BACKOFFS_FIELD_ID);
        }
    }


    public Types.DmOsSpinlockStatsDataType ToDataObject()
    {
        return new Types.DmOsSpinlockStatsDataType(Name,
            Collisions,
            Spins,
            SpinsPerCollision,
            SleepTime,
            Backoffs);
    }

    public List<Types.DmOsSpinlockStatsDataType> ToList()
    {
        var list = new List<Types.DmOsSpinlockStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
