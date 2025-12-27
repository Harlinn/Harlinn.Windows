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

public class DmResourceGovernorResourcePoolAffinityReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_resource_pool_affinity]";
    public const string TableName = "dm_resource_governor_resource_pool_affinity";
    public const string ShortName = "drgrpa";
    public const string Sql = """
        SELECT
          drgrpa.[pool_id],
          drgrpa.[processor_group],
          drgrpa.[scheduler_mask]
        FROM
          [sys].[dm_resource_governor_resource_pool_affinity] drgrpa
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int PROCESSORGROUP_FIELD_ID = 1;
    public const int SCHEDULERMASK_FIELD_ID = 2;


    public DmResourceGovernorResourcePoolAffinityReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolAffinityReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolAffinityReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short ProcessorGroup
    {
        get
        {
            return base.GetInt16(PROCESSORGROUP_FIELD_ID);
        }
    }

    public long SchedulerMask
    {
        get
        {
            return base.GetInt64(SCHEDULERMASK_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorResourcePoolAffinityDataType ToDataObject()
    {
        return new Types.DmResourceGovernorResourcePoolAffinityDataType(PoolId,
            ProcessorGroup,
            SchedulerMask);
    }

    public List<Types.DmResourceGovernorResourcePoolAffinityDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorResourcePoolAffinityDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
