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

public class DmOsSysMemoryReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_sys_memory]";
    public const string TableName = "dm_os_sys_memory";
    public const string ShortName = "dosm";
    public const string Sql = """
        SELECT
          dosm.[total_physical_memory_kb],
          dosm.[available_physical_memory_kb],
          dosm.[total_page_file_kb],
          dosm.[available_page_file_kb],
          dosm.[system_cache_kb],
          dosm.[kernel_paged_pool_kb],
          dosm.[kernel_nonpaged_pool_kb],
          dosm.[system_high_memory_signal_state],
          dosm.[system_low_memory_signal_state],
          dosm.[system_memory_state_desc]
        FROM
          [sys].[dm_os_sys_memory] dosm
        """;

    public const int TOTALPHYSICALMEMORYKB_FIELD_ID = 0;
    public const int AVAILABLEPHYSICALMEMORYKB_FIELD_ID = 1;
    public const int TOTALPAGEFILEKB_FIELD_ID = 2;
    public const int AVAILABLEPAGEFILEKB_FIELD_ID = 3;
    public const int SYSTEMCACHEKB_FIELD_ID = 4;
    public const int KERNELPAGEDPOOLKB_FIELD_ID = 5;
    public const int KERNELNONPAGEDPOOLKB_FIELD_ID = 6;
    public const int SYSTEMHIGHMEMORYSIGNALSTATE_FIELD_ID = 7;
    public const int SYSTEMLOWMEMORYSIGNALSTATE_FIELD_ID = 8;
    public const int SYSTEMMEMORYSTATEDESC_FIELD_ID = 9;


    public DmOsSysMemoryReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsSysMemoryReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsSysMemoryReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long TotalPhysicalMemoryKb
    {
        get
        {
            return base.GetInt64(TOTALPHYSICALMEMORYKB_FIELD_ID);
        }
    }

    public long AvailablePhysicalMemoryKb
    {
        get
        {
            return base.GetInt64(AVAILABLEPHYSICALMEMORYKB_FIELD_ID);
        }
    }

    public long TotalPageFileKb
    {
        get
        {
            return base.GetInt64(TOTALPAGEFILEKB_FIELD_ID);
        }
    }

    public long AvailablePageFileKb
    {
        get
        {
            return base.GetInt64(AVAILABLEPAGEFILEKB_FIELD_ID);
        }
    }

    public long SystemCacheKb
    {
        get
        {
            return base.GetInt64(SYSTEMCACHEKB_FIELD_ID);
        }
    }

    public long KernelPagedPoolKb
    {
        get
        {
            return base.GetInt64(KERNELPAGEDPOOLKB_FIELD_ID);
        }
    }

    public long KernelNonpagedPoolKb
    {
        get
        {
            return base.GetInt64(KERNELNONPAGEDPOOLKB_FIELD_ID);
        }
    }

    public bool SystemHighMemorySignalState
    {
        get
        {
            return base.GetBoolean(SYSTEMHIGHMEMORYSIGNALSTATE_FIELD_ID);
        }
    }

    public bool SystemLowMemorySignalState
    {
        get
        {
            return base.GetBoolean(SYSTEMLOWMEMORYSIGNALSTATE_FIELD_ID);
        }
    }

    public string SystemMemoryStateDesc
    {
        get
        {
            return base.GetString(SYSTEMMEMORYSTATEDESC_FIELD_ID);
        }
    }


    public Types.DmOsSysMemoryDataType ToDataObject()
    {
        return new Types.DmOsSysMemoryDataType(TotalPhysicalMemoryKb,
            AvailablePhysicalMemoryKb,
            TotalPageFileKb,
            AvailablePageFileKb,
            SystemCacheKb,
            KernelPagedPoolKb,
            KernelNonpagedPoolKb,
            SystemHighMemorySignalState,
            SystemLowMemorySignalState,
            SystemMemoryStateDesc);
    }

    public List<Types.DmOsSysMemoryDataType> ToList()
    {
        var list = new List<Types.DmOsSysMemoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
