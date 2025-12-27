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

public class DmOsMemoryBrokersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_brokers]";
    public const string TableName = "dm_os_memory_brokers";
    public const string ShortName = "domb";
    public const string Sql = """
        SELECT
          domb.[pool_id],
          domb.[memory_broker_type],
          domb.[allocations_kb],
          domb.[allocations_kb_per_sec],
          domb.[predicted_allocations_kb],
          domb.[target_allocations_kb],
          domb.[future_allocations_kb],
          domb.[overall_limit_kb],
          domb.[last_notification]
        FROM
          [sys].[dm_os_memory_brokers] domb
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int MEMORYBROKERTYPE_FIELD_ID = 1;
    public const int ALLOCATIONSKB_FIELD_ID = 2;
    public const int ALLOCATIONSKBPERSEC_FIELD_ID = 3;
    public const int PREDICTEDALLOCATIONSKB_FIELD_ID = 4;
    public const int TARGETALLOCATIONSKB_FIELD_ID = 5;
    public const int FUTUREALLOCATIONSKB_FIELD_ID = 6;
    public const int OVERALLLIMITKB_FIELD_ID = 7;
    public const int LASTNOTIFICATION_FIELD_ID = 8;


    public DmOsMemoryBrokersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryBrokersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryBrokersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public string MemoryBrokerType
    {
        get
        {
            return base.GetString(MEMORYBROKERTYPE_FIELD_ID);
        }
    }

    public long AllocationsKb
    {
        get
        {
            return base.GetInt64(ALLOCATIONSKB_FIELD_ID);
        }
    }

    public long AllocationsKbPerSec
    {
        get
        {
            return base.GetInt64(ALLOCATIONSKBPERSEC_FIELD_ID);
        }
    }

    public long PredictedAllocationsKb
    {
        get
        {
            return base.GetInt64(PREDICTEDALLOCATIONSKB_FIELD_ID);
        }
    }

    public long TargetAllocationsKb
    {
        get
        {
            return base.GetInt64(TARGETALLOCATIONSKB_FIELD_ID);
        }
    }

    public long FutureAllocationsKb
    {
        get
        {
            return base.GetInt64(FUTUREALLOCATIONSKB_FIELD_ID);
        }
    }

    public long OverallLimitKb
    {
        get
        {
            return base.GetInt64(OVERALLLIMITKB_FIELD_ID);
        }
    }

    public string LastNotification
    {
        get
        {
            return base.GetString(LASTNOTIFICATION_FIELD_ID);
        }
    }


    public Types.DmOsMemoryBrokersDataType ToDataObject()
    {
        return new Types.DmOsMemoryBrokersDataType(PoolId,
            MemoryBrokerType,
            AllocationsKb,
            AllocationsKbPerSec,
            PredictedAllocationsKb,
            TargetAllocationsKb,
            FutureAllocationsKb,
            OverallLimitKb,
            LastNotification);
    }

    public List<Types.DmOsMemoryBrokersDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryBrokersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
