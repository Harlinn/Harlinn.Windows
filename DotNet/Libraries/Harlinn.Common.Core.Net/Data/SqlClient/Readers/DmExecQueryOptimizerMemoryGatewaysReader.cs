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

public class DmExecQueryOptimizerMemoryGatewaysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_optimizer_memory_gateways]";
    public const string TableName = "dm_exec_query_optimizer_memory_gateways";
    public const string ShortName = "deqomg";
    public const string Sql = """
        SELECT
          deqomg.[pool_id],
          deqomg.[Name],
          deqomg.[max_count],
          deqomg.[active_count],
          deqomg.[waiter_count],
          deqomg.[threshold_factor],
          deqomg.[Threshold],
          deqomg.[is_active]
        FROM
          [sys].[dm_exec_query_optimizer_memory_gateways] deqomg
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MAXCOUNT_FIELD_ID = 2;
    public const int ACTIVECOUNT_FIELD_ID = 3;
    public const int WAITERCOUNT_FIELD_ID = 4;
    public const int THRESHOLDFACTOR_FIELD_ID = 5;
    public const int THRESHOLD_FIELD_ID = 6;
    public const int ISACTIVE_FIELD_ID = 7;


    public DmExecQueryOptimizerMemoryGatewaysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryOptimizerMemoryGatewaysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryOptimizerMemoryGatewaysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int MaxCount
    {
        get
        {
            return base.GetInt32(MAXCOUNT_FIELD_ID);
        }
    }

    public int ActiveCount
    {
        get
        {
            return base.GetInt32(ACTIVECOUNT_FIELD_ID);
        }
    }

    public int WaiterCount
    {
        get
        {
            return base.GetInt32(WAITERCOUNT_FIELD_ID);
        }
    }

    public long ThresholdFactor
    {
        get
        {
            return base.GetInt64(THRESHOLDFACTOR_FIELD_ID);
        }
    }

    public long Threshold
    {
        get
        {
            return base.GetInt64(THRESHOLD_FIELD_ID);
        }
    }

    public bool IsActive
    {
        get
        {
            return base.GetBoolean(ISACTIVE_FIELD_ID);
        }
    }


    public Types.DmExecQueryOptimizerMemoryGatewaysDataType ToDataObject()
    {
        return new Types.DmExecQueryOptimizerMemoryGatewaysDataType(PoolId,
            Name,
            MaxCount,
            ActiveCount,
            WaiterCount,
            ThresholdFactor,
            Threshold,
            IsActive);
    }

    public List<Types.DmExecQueryOptimizerMemoryGatewaysDataType> ToList()
    {
        var list = new List<Types.DmExecQueryOptimizerMemoryGatewaysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
