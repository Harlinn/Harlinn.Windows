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

public class DmExternalScriptResourceUsageStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_external_script_resource_usage_stats]";
    public const string TableName = "dm_external_script_resource_usage_stats";
    public const string ShortName = "desrus";
    public const string Sql = """
        SELECT
          desrus.[package_name],
          desrus.[memory_usage],
          desrus.[cpu_usage]
        FROM
          [sys].[dm_external_script_resource_usage_stats] desrus
        """;

    public const int PACKAGENAME_FIELD_ID = 0;
    public const int MEMORYUSAGE_FIELD_ID = 1;
    public const int CPUUSAGE_FIELD_ID = 2;


    public DmExternalScriptResourceUsageStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptResourceUsageStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptResourceUsageStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string PackageName
    {
        get
        {
            return base.GetString(PACKAGENAME_FIELD_ID);
        }
    }

    public long MemoryUsage
    {
        get
        {
            return base.GetInt64(MEMORYUSAGE_FIELD_ID);
        }
    }

    public long CpuUsage
    {
        get
        {
            return base.GetInt64(CPUUSAGE_FIELD_ID);
        }
    }


    public Types.DmExternalScriptResourceUsageStatsDataType ToDataObject()
    {
        return new Types.DmExternalScriptResourceUsageStatsDataType(PackageName,
            MemoryUsage,
            CpuUsage);
    }

    public List<Types.DmExternalScriptResourceUsageStatsDataType> ToList()
    {
        var list = new List<Types.DmExternalScriptResourceUsageStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
