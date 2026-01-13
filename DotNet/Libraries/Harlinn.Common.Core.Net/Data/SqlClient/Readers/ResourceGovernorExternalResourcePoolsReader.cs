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

public class ResourceGovernorExternalResourcePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[resource_governor_external_resource_pools]";
    public const string TableName = "resource_governor_external_resource_pools";
    public const string ShortName = "rgerp";
    public const string Sql = """
        SELECT
          rgerp.[external_pool_id],
          rgerp.[Name],
          rgerp.[max_cpu_percent],
          rgerp.[max_memory_percent],
          rgerp.[max_processes],
          rgerp.[Version]
        FROM
          [sys].[resource_governor_external_resource_pools] rgerp
        """;

    public const int EXTERNALPOOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MAXCPUPERCENT_FIELD_ID = 2;
    public const int MAXMEMORYPERCENT_FIELD_ID = 3;
    public const int MAXPROCESSES_FIELD_ID = 4;
    public const int VERSION_FIELD_ID = 5;


    public ResourceGovernorExternalResourcePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorExternalResourcePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorExternalResourcePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ExternalPoolId
    {
        get
        {
            return base.GetInt32(EXTERNALPOOLID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int MaxCpuPercent
    {
        get
        {
            return base.GetInt32(MAXCPUPERCENT_FIELD_ID);
        }
    }

    public int MaxMemoryPercent
    {
        get
        {
            return base.GetInt32(MAXMEMORYPERCENT_FIELD_ID);
        }
    }

    public int MaxProcesses
    {
        get
        {
            return base.GetInt32(MAXPROCESSES_FIELD_ID);
        }
    }

    public long Version
    {
        get
        {
            return base.GetInt64(VERSION_FIELD_ID);
        }
    }


    public Types.ResourceGovernorExternalResourcePoolsDataType ToDataObject()
    {
        return new Types.ResourceGovernorExternalResourcePoolsDataType(ExternalPoolId,
            Name,
            MaxCpuPercent,
            MaxMemoryPercent,
            MaxProcesses,
            Version);
    }

    public List<Types.ResourceGovernorExternalResourcePoolsDataType> ToList()
    {
        var list = new List<Types.ResourceGovernorExternalResourcePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
