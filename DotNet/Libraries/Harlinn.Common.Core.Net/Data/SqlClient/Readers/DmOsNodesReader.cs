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

public class DmOsNodesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_nodes]";
    public const string TableName = "dm_os_nodes";
    public const string ShortName = "don";
    public const string Sql = """
        SELECT
          don.[node_id],
          don.[node_state_desc],
          don.[memory_object_address],
          don.[memory_clerk_address],
          don.[io_completion_worker_address],
          don.[memory_node_id],
          don.[cpu_affinity_mask],
          don.[online_scheduler_count],
          don.[idle_scheduler_count],
          don.[active_worker_count],
          don.[avg_load_balance],
          don.[timer_task_affinity_mask],
          don.[permanent_task_affinity_mask],
          don.[resource_monitor_state],
          don.[online_scheduler_mask],
          don.[processor_group],
          don.[cpu_count]
        FROM
          [sys].[dm_os_nodes] don
        """;

    public const int NODEID_FIELD_ID = 0;
    public const int NODESTATEDESC_FIELD_ID = 1;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 2;
    public const int MEMORYCLERKADDRESS_FIELD_ID = 3;
    public const int IOCOMPLETIONWORKERADDRESS_FIELD_ID = 4;
    public const int MEMORYNODEID_FIELD_ID = 5;
    public const int CPUAFFINITYMASK_FIELD_ID = 6;
    public const int ONLINESCHEDULERCOUNT_FIELD_ID = 7;
    public const int IDLESCHEDULERCOUNT_FIELD_ID = 8;
    public const int ACTIVEWORKERCOUNT_FIELD_ID = 9;
    public const int AVGLOADBALANCE_FIELD_ID = 10;
    public const int TIMERTASKAFFINITYMASK_FIELD_ID = 11;
    public const int PERMANENTTASKAFFINITYMASK_FIELD_ID = 12;
    public const int RESOURCEMONITORSTATE_FIELD_ID = 13;
    public const int ONLINESCHEDULERMASK_FIELD_ID = 14;
    public const int PROCESSORGROUP_FIELD_ID = 15;
    public const int CPUCOUNT_FIELD_ID = 16;


    public DmOsNodesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsNodesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsNodesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short NodeId
    {
        get
        {
            return base.GetInt16(NODEID_FIELD_ID);
        }
    }

    public string NodeStateDesc
    {
        get
        {
            return base.GetString(NODESTATEDESC_FIELD_ID);
        }
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public byte[] MemoryClerkAddress
    {
        get
        {
            return base.GetBinary(MEMORYCLERKADDRESS_FIELD_ID);
        }
    }

    public byte[]? IoCompletionWorkerAddress
    {
        get
        {
            return base.GetNullableBinary(IOCOMPLETIONWORKERADDRESS_FIELD_ID);
        }
    }

    public short MemoryNodeId
    {
        get
        {
            return base.GetInt16(MEMORYNODEID_FIELD_ID);
        }
    }

    public long CpuAffinityMask
    {
        get
        {
            return base.GetInt64(CPUAFFINITYMASK_FIELD_ID);
        }
    }

    public short OnlineSchedulerCount
    {
        get
        {
            return base.GetInt16(ONLINESCHEDULERCOUNT_FIELD_ID);
        }
    }

    public short IdleSchedulerCount
    {
        get
        {
            return base.GetInt16(IDLESCHEDULERCOUNT_FIELD_ID);
        }
    }

    public int ActiveWorkerCount
    {
        get
        {
            return base.GetInt32(ACTIVEWORKERCOUNT_FIELD_ID);
        }
    }

    public int AvgLoadBalance
    {
        get
        {
            return base.GetInt32(AVGLOADBALANCE_FIELD_ID);
        }
    }

    public long TimerTaskAffinityMask
    {
        get
        {
            return base.GetInt64(TIMERTASKAFFINITYMASK_FIELD_ID);
        }
    }

    public long PermanentTaskAffinityMask
    {
        get
        {
            return base.GetInt64(PERMANENTTASKAFFINITYMASK_FIELD_ID);
        }
    }

    public bool ResourceMonitorState
    {
        get
        {
            return base.GetBoolean(RESOURCEMONITORSTATE_FIELD_ID);
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

    public int CpuCount
    {
        get
        {
            return base.GetInt32(CPUCOUNT_FIELD_ID);
        }
    }


    public Types.DmOsNodesDataType ToDataObject()
    {
        return new Types.DmOsNodesDataType(NodeId,
            NodeStateDesc,
            MemoryObjectAddress,
            MemoryClerkAddress,
            IoCompletionWorkerAddress,
            MemoryNodeId,
            CpuAffinityMask,
            OnlineSchedulerCount,
            IdleSchedulerCount,
            ActiveWorkerCount,
            AvgLoadBalance,
            TimerTaskAffinityMask,
            PermanentTaskAffinityMask,
            ResourceMonitorState,
            OnlineSchedulerMask,
            ProcessorGroup,
            CpuCount);
    }

    public List<Types.DmOsNodesDataType> ToList()
    {
        var list = new List<Types.DmOsNodesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
