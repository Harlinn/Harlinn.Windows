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

public class DmExecQueryResourceSemaphoresReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_resource_semaphores]";
    public const string TableName = "dm_exec_query_resource_semaphores";
    public const string ShortName = "deqrs";
    public const string Sql = """
        SELECT
          deqrs.[resource_semaphore_id],
          deqrs.[target_memory_kb],
          deqrs.[max_target_memory_kb],
          deqrs.[total_memory_kb],
          deqrs.[available_memory_kb],
          deqrs.[granted_memory_kb],
          deqrs.[used_memory_kb],
          deqrs.[grantee_count],
          deqrs.[waiter_count],
          deqrs.[timeout_error_count],
          deqrs.[forced_grant_count],
          deqrs.[pool_id]
        FROM
          [sys].[dm_exec_query_resource_semaphores] deqrs
        """;

    public const int RESOURCESEMAPHOREID_FIELD_ID = 0;
    public const int TARGETMEMORYKB_FIELD_ID = 1;
    public const int MAXTARGETMEMORYKB_FIELD_ID = 2;
    public const int TOTALMEMORYKB_FIELD_ID = 3;
    public const int AVAILABLEMEMORYKB_FIELD_ID = 4;
    public const int GRANTEDMEMORYKB_FIELD_ID = 5;
    public const int USEDMEMORYKB_FIELD_ID = 6;
    public const int GRANTEECOUNT_FIELD_ID = 7;
    public const int WAITERCOUNT_FIELD_ID = 8;
    public const int TIMEOUTERRORCOUNT_FIELD_ID = 9;
    public const int FORCEDGRANTCOUNT_FIELD_ID = 10;
    public const int POOLID_FIELD_ID = 11;


    public DmExecQueryResourceSemaphoresReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryResourceSemaphoresReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryResourceSemaphoresReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? ResourceSemaphoreId
    {
        get
        {
            return base.GetNullableInt16(RESOURCESEMAPHOREID_FIELD_ID);
        }
    }

    public long? TargetMemoryKb
    {
        get
        {
            return base.GetNullableInt64(TARGETMEMORYKB_FIELD_ID);
        }
    }

    public long? MaxTargetMemoryKb
    {
        get
        {
            return base.GetNullableInt64(MAXTARGETMEMORYKB_FIELD_ID);
        }
    }

    public long? TotalMemoryKb
    {
        get
        {
            return base.GetNullableInt64(TOTALMEMORYKB_FIELD_ID);
        }
    }

    public long? AvailableMemoryKb
    {
        get
        {
            return base.GetNullableInt64(AVAILABLEMEMORYKB_FIELD_ID);
        }
    }

    public long? GrantedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(GRANTEDMEMORYKB_FIELD_ID);
        }
    }

    public long? UsedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(USEDMEMORYKB_FIELD_ID);
        }
    }

    public int? GranteeCount
    {
        get
        {
            return base.GetNullableInt32(GRANTEECOUNT_FIELD_ID);
        }
    }

    public int? WaiterCount
    {
        get
        {
            return base.GetNullableInt32(WAITERCOUNT_FIELD_ID);
        }
    }

    public long? TimeoutErrorCount
    {
        get
        {
            return base.GetNullableInt64(TIMEOUTERRORCOUNT_FIELD_ID);
        }
    }

    public long? ForcedGrantCount
    {
        get
        {
            return base.GetNullableInt64(FORCEDGRANTCOUNT_FIELD_ID);
        }
    }

    public int? PoolId
    {
        get
        {
            return base.GetNullableInt32(POOLID_FIELD_ID);
        }
    }


    public Types.DmExecQueryResourceSemaphoresDataType ToDataObject()
    {
        return new Types.DmExecQueryResourceSemaphoresDataType(ResourceSemaphoreId,
            TargetMemoryKb,
            MaxTargetMemoryKb,
            TotalMemoryKb,
            AvailableMemoryKb,
            GrantedMemoryKb,
            UsedMemoryKb,
            GranteeCount,
            WaiterCount,
            TimeoutErrorCount,
            ForcedGrantCount,
            PoolId);
    }

    public List<Types.DmExecQueryResourceSemaphoresDataType> ToList()
    {
        var list = new List<Types.DmExecQueryResourceSemaphoresDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
