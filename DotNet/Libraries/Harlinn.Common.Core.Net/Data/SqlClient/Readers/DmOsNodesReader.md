# DmOsNodesReader — reference

Overview

`DmOsNodesReader` wraps `sys.dm_os_nodes` and returns node-level information for SQL Server scheduler and worker infrastructure, mapping to logical nodes and scheduler masks.

Reader SQL

```
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
```

Columns and interpretation

- `node_id` ? logical node id.
- `node_state_desc` ? textual state description (Online/Offline/etc.).
- `memory_object_address` / `memory_clerk_address` ? addresses linking node to memory structures.
- `io_completion_worker_address` ? address for IO completion worker if present.
- `memory_node_id` ? NUMA memory node id.
- `cpu_affinity_mask` ? CPU affinity mask for this node.
- `online_scheduler_count` / `idle_scheduler_count` ? scheduler counts.
- `active_worker_count` ? active worker threads count.
- `avg_load_balance` ? average load balancing metric.
- `timer_task_affinity_mask` / `permanent_task_affinity_mask` ? affinity masks for timer/permanent tasks.
- `resource_monitor_state` ? bool indicating if resource monitor is active.
- `online_scheduler_mask` ? mask for online schedulers.
- `processor_group` ? processor group id.
- `cpu_count` ? number of CPUs associated with the node.

How to interpret

- Useful to inspect scheduler distribution, CPU affinity and node-level resource assignments.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsNodesReader.Sql;
using var rdr = cmd.ExecuteReader();
var n = new DmOsNodesReader(rdr, ownsReader:false);
while (n.Read())
{
    Console.WriteLine($"Node:{n.NodeId} State:{n.NodeStateDesc} CPUs:{n.CpuCount} OnlineSched:{n.OnlineSchedulerCount} ActiveWorkers:{n.ActiveWorkerCount}");
}
```

See also:

- [sys.dm_os_nodes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-nodes)
