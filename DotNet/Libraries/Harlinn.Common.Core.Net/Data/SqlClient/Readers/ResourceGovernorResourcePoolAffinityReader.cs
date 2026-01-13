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

public class ResourceGovernorResourcePoolAffinityReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[resource_governor_resource_pool_affinity]";
    public const string TableName = "resource_governor_resource_pool_affinity";
    public const string ShortName = "rgrpa";
    public const string Sql = """
        SELECT
          rgrpa.[pool_id],
          rgrpa.[processor_group],
          rgrpa.[scheduler_mask]
        FROM
          [sys].[resource_governor_resource_pool_affinity] rgrpa
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int PROCESSORGROUP_FIELD_ID = 1;
    public const int SCHEDULERMASK_FIELD_ID = 2;


    public ResourceGovernorResourcePoolAffinityReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorResourcePoolAffinityReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorResourcePoolAffinityReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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


    public Types.ResourceGovernorResourcePoolAffinityDataType ToDataObject()
    {
        return new Types.ResourceGovernorResourcePoolAffinityDataType(PoolId,
            ProcessorGroup,
            SchedulerMask);
    }

    public List<Types.ResourceGovernorResourcePoolAffinityDataType> ToList()
    {
        var list = new List<Types.ResourceGovernorResourcePoolAffinityDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
