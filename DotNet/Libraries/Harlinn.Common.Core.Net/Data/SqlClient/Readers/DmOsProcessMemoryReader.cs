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

public class DmOsProcessMemoryReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_process_memory]";
    public const string TableName = "dm_os_process_memory";
    public const string ShortName = "dopm";
    public const string Sql = """
        SELECT
          dopm.[physical_memory_in_use_kb],
          dopm.[large_page_allocations_kb],
          dopm.[locked_page_allocations_kb],
          dopm.[total_virtual_address_space_kb],
          dopm.[virtual_address_space_reserved_kb],
          dopm.[virtual_address_space_committed_kb],
          dopm.[virtual_address_space_available_kb],
          dopm.[page_fault_count],
          dopm.[memory_utilization_percentage],
          dopm.[available_commit_limit_kb],
          dopm.[process_physical_memory_low],
          dopm.[process_virtual_memory_low]
        FROM
          [sys].[dm_os_process_memory] dopm
        """;

    public const int PHYSICALMEMORYINUSEKB_FIELD_ID = 0;
    public const int LARGEPAGEALLOCATIONSKB_FIELD_ID = 1;
    public const int LOCKEDPAGEALLOCATIONSKB_FIELD_ID = 2;
    public const int TOTALVIRTUALADDRESSSPACEKB_FIELD_ID = 3;
    public const int VIRTUALADDRESSSPACERESERVEDKB_FIELD_ID = 4;
    public const int VIRTUALADDRESSSPACECOMMITTEDKB_FIELD_ID = 5;
    public const int VIRTUALADDRESSSPACEAVAILABLEKB_FIELD_ID = 6;
    public const int PAGEFAULTCOUNT_FIELD_ID = 7;
    public const int MEMORYUTILIZATIONPERCENTAGE_FIELD_ID = 8;
    public const int AVAILABLECOMMITLIMITKB_FIELD_ID = 9;
    public const int PROCESSPHYSICALMEMORYLOW_FIELD_ID = 10;
    public const int PROCESSVIRTUALMEMORYLOW_FIELD_ID = 11;


    public DmOsProcessMemoryReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsProcessMemoryReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsProcessMemoryReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long PhysicalMemoryInUseKb
    {
        get
        {
            return base.GetInt64(PHYSICALMEMORYINUSEKB_FIELD_ID);
        }
    }

    public long LargePageAllocationsKb
    {
        get
        {
            return base.GetInt64(LARGEPAGEALLOCATIONSKB_FIELD_ID);
        }
    }

    public long LockedPageAllocationsKb
    {
        get
        {
            return base.GetInt64(LOCKEDPAGEALLOCATIONSKB_FIELD_ID);
        }
    }

    public long TotalVirtualAddressSpaceKb
    {
        get
        {
            return base.GetInt64(TOTALVIRTUALADDRESSSPACEKB_FIELD_ID);
        }
    }

    public long VirtualAddressSpaceReservedKb
    {
        get
        {
            return base.GetInt64(VIRTUALADDRESSSPACERESERVEDKB_FIELD_ID);
        }
    }

    public long VirtualAddressSpaceCommittedKb
    {
        get
        {
            return base.GetInt64(VIRTUALADDRESSSPACECOMMITTEDKB_FIELD_ID);
        }
    }

    public long VirtualAddressSpaceAvailableKb
    {
        get
        {
            return base.GetInt64(VIRTUALADDRESSSPACEAVAILABLEKB_FIELD_ID);
        }
    }

    public long PageFaultCount
    {
        get
        {
            return base.GetInt64(PAGEFAULTCOUNT_FIELD_ID);
        }
    }

    public int MemoryUtilizationPercentage
    {
        get
        {
            return base.GetInt32(MEMORYUTILIZATIONPERCENTAGE_FIELD_ID);
        }
    }

    public long AvailableCommitLimitKb
    {
        get
        {
            return base.GetInt64(AVAILABLECOMMITLIMITKB_FIELD_ID);
        }
    }

    public bool ProcessPhysicalMemoryLow
    {
        get
        {
            return base.GetBoolean(PROCESSPHYSICALMEMORYLOW_FIELD_ID);
        }
    }

    public bool ProcessVirtualMemoryLow
    {
        get
        {
            return base.GetBoolean(PROCESSVIRTUALMEMORYLOW_FIELD_ID);
        }
    }


    public Types.DmOsProcessMemoryDataType ToDataObject()
    {
        return new Types.DmOsProcessMemoryDataType(PhysicalMemoryInUseKb,
            LargePageAllocationsKb,
            LockedPageAllocationsKb,
            TotalVirtualAddressSpaceKb,
            VirtualAddressSpaceReservedKb,
            VirtualAddressSpaceCommittedKb,
            VirtualAddressSpaceAvailableKb,
            PageFaultCount,
            MemoryUtilizationPercentage,
            AvailableCommitLimitKb,
            ProcessPhysicalMemoryLow,
            ProcessVirtualMemoryLow);
    }

    public List<Types.DmOsProcessMemoryDataType> ToList()
    {
        var list = new List<Types.DmOsProcessMemoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
