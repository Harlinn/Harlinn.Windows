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

public class DmOsMemoryNodesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_nodes]";
    public const string TableName = "dm_os_memory_nodes";
    public const string ShortName = "domn";
    public const string Sql = """
        SELECT
          domn.[memory_node_id],
          domn.[virtual_address_space_reserved_kb],
          domn.[virtual_address_space_committed_kb],
          domn.[locked_page_allocations_kb],
          domn.[pages_kb],
          domn.[shared_memory_reserved_kb],
          domn.[shared_memory_committed_kb],
          domn.[cpu_affinity_mask],
          domn.[online_scheduler_mask],
          domn.[processor_group],
          domn.[foreign_committed_kb],
          domn.[target_kb]
        FROM
          [sys].[dm_os_memory_nodes] domn
        """;

    public const int MEMORYNODEID_FIELD_ID = 0;
    public const int VIRTUALADDRESSSPACERESERVEDKB_FIELD_ID = 1;
    public const int VIRTUALADDRESSSPACECOMMITTEDKB_FIELD_ID = 2;
    public const int LOCKEDPAGEALLOCATIONSKB_FIELD_ID = 3;
    public const int PAGESKB_FIELD_ID = 4;
    public const int SHAREDMEMORYRESERVEDKB_FIELD_ID = 5;
    public const int SHAREDMEMORYCOMMITTEDKB_FIELD_ID = 6;
    public const int CPUAFFINITYMASK_FIELD_ID = 7;
    public const int ONLINESCHEDULERMASK_FIELD_ID = 8;
    public const int PROCESSORGROUP_FIELD_ID = 9;
    public const int FOREIGNCOMMITTEDKB_FIELD_ID = 10;
    public const int TARGETKB_FIELD_ID = 11;


    public DmOsMemoryNodesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryNodesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryNodesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short MemoryNodeId
    {
        get
        {
            return base.GetInt16(MEMORYNODEID_FIELD_ID);
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

    public long LockedPageAllocationsKb
    {
        get
        {
            return base.GetInt64(LOCKEDPAGEALLOCATIONSKB_FIELD_ID);
        }
    }

    public long PagesKb
    {
        get
        {
            return base.GetInt64(PAGESKB_FIELD_ID);
        }
    }

    public long SharedMemoryReservedKb
    {
        get
        {
            return base.GetInt64(SHAREDMEMORYRESERVEDKB_FIELD_ID);
        }
    }

    public long SharedMemoryCommittedKb
    {
        get
        {
            return base.GetInt64(SHAREDMEMORYCOMMITTEDKB_FIELD_ID);
        }
    }

    public long CpuAffinityMask
    {
        get
        {
            return base.GetInt64(CPUAFFINITYMASK_FIELD_ID);
        }
    }

    public long OnlineSchedulerMask
    {
        get
        {
            return base.GetInt64(ONLINESCHEDULERMASK_FIELD_ID);
        }
    }

    public short ProcessorGroup
    {
        get
        {
            return base.GetInt16(PROCESSORGROUP_FIELD_ID);
        }
    }

    public long ForeignCommittedKb
    {
        get
        {
            return base.GetInt64(FOREIGNCOMMITTEDKB_FIELD_ID);
        }
    }

    public long TargetKb
    {
        get
        {
            return base.GetInt64(TARGETKB_FIELD_ID);
        }
    }


    public Types.DmOsMemoryNodesDataType ToDataObject()
    {
        return new Types.DmOsMemoryNodesDataType(MemoryNodeId,
            VirtualAddressSpaceReservedKb,
            VirtualAddressSpaceCommittedKb,
            LockedPageAllocationsKb,
            PagesKb,
            SharedMemoryReservedKb,
            SharedMemoryCommittedKb,
            CpuAffinityMask,
            OnlineSchedulerMask,
            ProcessorGroup,
            ForeignCommittedKb,
            TargetKb);
    }

    public List<Types.DmOsMemoryNodesDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryNodesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
