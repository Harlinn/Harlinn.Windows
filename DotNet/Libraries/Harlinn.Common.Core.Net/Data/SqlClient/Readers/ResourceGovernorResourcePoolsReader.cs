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

public class ResourceGovernorResourcePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[resource_governor_resource_pools]";
    public const string TableName = "resource_governor_resource_pools";
    public const string ShortName = "rgrp";
    public const string Sql = """
        SELECT
          rgrp.[pool_id],
          rgrp.[Name],
          rgrp.[min_cpu_percent],
          rgrp.[max_cpu_percent],
          rgrp.[min_memory_percent],
          rgrp.[max_memory_percent],
          rgrp.[cap_cpu_percent],
          rgrp.[min_iops_per_volume],
          rgrp.[max_iops_per_volume]
        FROM
          [sys].[resource_governor_resource_pools] rgrp
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MINCPUPERCENT_FIELD_ID = 2;
    public const int MAXCPUPERCENT_FIELD_ID = 3;
    public const int MINMEMORYPERCENT_FIELD_ID = 4;
    public const int MAXMEMORYPERCENT_FIELD_ID = 5;
    public const int CAPCPUPERCENT_FIELD_ID = 6;
    public const int MINIOPSPERVOLUME_FIELD_ID = 7;
    public const int MAXIOPSPERVOLUME_FIELD_ID = 8;


    public ResourceGovernorResourcePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorResourcePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorResourcePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int MinCpuPercent
    {
        get
        {
            return base.GetInt32(MINCPUPERCENT_FIELD_ID);
        }
    }

    public int MaxCpuPercent
    {
        get
        {
            return base.GetInt32(MAXCPUPERCENT_FIELD_ID);
        }
    }

    public int MinMemoryPercent
    {
        get
        {
            return base.GetInt32(MINMEMORYPERCENT_FIELD_ID);
        }
    }

    public int MaxMemoryPercent
    {
        get
        {
            return base.GetInt32(MAXMEMORYPERCENT_FIELD_ID);
        }
    }

    public int CapCpuPercent
    {
        get
        {
            return base.GetInt32(CAPCPUPERCENT_FIELD_ID);
        }
    }

    public int MinIopsPerVolume
    {
        get
        {
            return base.GetInt32(MINIOPSPERVOLUME_FIELD_ID);
        }
    }

    public int MaxIopsPerVolume
    {
        get
        {
            return base.GetInt32(MAXIOPSPERVOLUME_FIELD_ID);
        }
    }


    public Types.ResourceGovernorResourcePoolsDataType ToDataObject()
    {
        return new Types.ResourceGovernorResourcePoolsDataType(PoolId,
            Name,
            MinCpuPercent,
            MaxCpuPercent,
            MinMemoryPercent,
            MaxMemoryPercent,
            CapCpuPercent,
            MinIopsPerVolume,
            MaxIopsPerVolume);
    }

    public List<Types.ResourceGovernorResourcePoolsDataType> ToList()
    {
        var list = new List<Types.ResourceGovernorResourcePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
