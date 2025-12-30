# DmExecComputeNodeStatusReader — reference

Overview

`DmExecComputeNodeStatusReader` wraps `sys.dm_exec_compute_node_status` and provides runtime status metrics for compute nodes including memory, CPU, thread counts and timestamps for last status update.

Reader SQL

```
SELECT
  decns.[compute_node_id],
  decns.[process_id],
  decns.[process_name],
  decns.[allocated_memory],
  decns.[available_memory],
  decns.[process_cpu_usage],
  decns.[total_cpu_usage],
  decns.[thread_count],
  decns.[handle_count],
  decns.[total_elapsed_time],
  decns.[is_available],
  decns.[sent_time],
  decns.[received_time],
  decns.[error_id],
  decns.[compute_pool_id]
FROM
  [sys].[dm_exec_compute_node_status] decns
```

Columns (interpretation)

- `compute_node_id` ? id of the node.
- `process_id` / `process_name` ? OS process id and name for the node process.
- `allocated_memory` / `available_memory` ? bytes of memory allocated and available on the node process.
- `process_cpu_usage` / `total_cpu_usage` ? CPU usage metrics (units likely ms or percent depending on view docs).
- `thread_count` / `handle_count` ? OS thread and handle counts for the node process.
- `total_elapsed_time` ? cumulative elapsed time recorded for the process.
- `is_available` ? whether the node reports available/online.
- `sent_time` / `received_time` ? timestamps when status was sent/received; use to detect stale status.
- `error_id` ? any error id reported by the node.
- `compute_pool_id` ? pool id the node belongs to.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecComputeNodeStatusReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecComputeNodeStatusReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Node {s.ComputeNodeId} Process: {s.ProcessId} {s.ProcessName}");
    Console.WriteLine($" Memory allocated/avail: {s.AllocatedMemory}/{s.AvailableMemory} CPU: {s.ProcessCpuUsage}/{s.TotalCpuUsage}");
    Console.WriteLine($" Threads: {s.ThreadCount} Handles: {s.HandleCount} Available: {s.IsAvailable}");
}
```

See also:

- [sys.dm_exec_compute_node_status](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-compute-node-status)
