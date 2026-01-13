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

public class DmResourceGovernorExternalResourcePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_external_resource_pools]";
    public const string TableName = "dm_resource_governor_external_resource_pools";
    public const string ShortName = "drgerp";
    public const string Sql = """
        SELECT
          drgerp.[external_pool_id],
          drgerp.[Name],
          drgerp.[pool_version],
          drgerp.[max_cpu_percent],
          drgerp.[max_processes],
          drgerp.[max_memory_percent],
          drgerp.[statistics_start_time],
          drgerp.[peak_memory_kb],
          drgerp.[write_io_count],
          drgerp.[read_io_count],
          drgerp.[total_cpu_kernel_ms],
          drgerp.[total_cpu_user_ms],
          drgerp.[active_processes_count]
        FROM
          [sys].[dm_resource_governor_external_resource_pools] drgerp
        """;

    public const int EXTERNALPOOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int POOLVERSION_FIELD_ID = 2;
    public const int MAXCPUPERCENT_FIELD_ID = 3;
    public const int MAXPROCESSES_FIELD_ID = 4;
    public const int MAXMEMORYPERCENT_FIELD_ID = 5;
    public const int STATISTICSSTARTTIME_FIELD_ID = 6;
    public const int PEAKMEMORYKB_FIELD_ID = 7;
    public const int WRITEIOCOUNT_FIELD_ID = 8;
    public const int READIOCOUNT_FIELD_ID = 9;
    public const int TOTALCPUKERNELMS_FIELD_ID = 10;
    public const int TOTALCPUUSERMS_FIELD_ID = 11;
    public const int ACTIVEPROCESSESCOUNT_FIELD_ID = 12;


    public DmResourceGovernorExternalResourcePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorExternalResourcePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorExternalResourcePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long PoolVersion
    {
        get
        {
            return base.GetInt64(POOLVERSION_FIELD_ID);
        }
    }

    public int MaxCpuPercent
    {
        get
        {
            return base.GetInt32(MAXCPUPERCENT_FIELD_ID);
        }
    }

    public int MaxProcesses
    {
        get
        {
            return base.GetInt32(MAXPROCESSES_FIELD_ID);
        }
    }

    public int MaxMemoryPercent
    {
        get
        {
            return base.GetInt32(MAXMEMORYPERCENT_FIELD_ID);
        }
    }

    public DateTime StatisticsStartTime
    {
        get
        {
            return base.GetDateTime(STATISTICSSTARTTIME_FIELD_ID);
        }
    }

    public long PeakMemoryKb
    {
        get
        {
            return base.GetInt64(PEAKMEMORYKB_FIELD_ID);
        }
    }

    public long WriteIoCount
    {
        get
        {
            return base.GetInt64(WRITEIOCOUNT_FIELD_ID);
        }
    }

    public long ReadIoCount
    {
        get
        {
            return base.GetInt64(READIOCOUNT_FIELD_ID);
        }
    }

    public long TotalCpuKernelMs
    {
        get
        {
            return base.GetInt64(TOTALCPUKERNELMS_FIELD_ID);
        }
    }

    public long TotalCpuUserMs
    {
        get
        {
            return base.GetInt64(TOTALCPUUSERMS_FIELD_ID);
        }
    }

    public long ActiveProcessesCount
    {
        get
        {
            return base.GetInt64(ACTIVEPROCESSESCOUNT_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorExternalResourcePoolsDataType ToDataObject()
    {
        return new Types.DmResourceGovernorExternalResourcePoolsDataType(ExternalPoolId,
            Name,
            PoolVersion,
            MaxCpuPercent,
            MaxProcesses,
            MaxMemoryPercent,
            StatisticsStartTime,
            PeakMemoryKb,
            WriteIoCount,
            ReadIoCount,
            TotalCpuKernelMs,
            TotalCpuUserMs,
            ActiveProcessesCount);
    }

    public List<Types.DmResourceGovernorExternalResourcePoolsDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorExternalResourcePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
