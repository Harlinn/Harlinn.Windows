# DmResourceGovernorResourcePoolsReader — reference

Overview

`DmResourceGovernorResourcePoolsReader` wraps `sys.dm_resource_governor_resource_pools` and returns detailed runtime statistics and configuration for internal resource pools managed by Resource Governor.

Reader SQL

```
SELECT
  drgrp.[pool_id],
  drgrp.[Name],
  drgrp.[statistics_start_time],
  drgrp.[total_cpu_usage_ms],
  drgrp.[cache_memory_kb],
  drgrp.[compile_memory_kb],
  drgrp.[used_memgrant_kb],
  drgrp.[total_memgrant_count],
  drgrp.[total_memgrant_timeout_count],
  drgrp.[active_memgrant_count],
  drgrp.[active_memgrant_kb],
  drgrp.[memgrant_waiter_count],
  drgrp.[max_memory_kb],
  drgrp.[used_memory_kb],
  drgrp.[target_memory_kb],
  drgrp.[out_of_memory_count],
  drgrp.[min_cpu_percent],
  drgrp.[max_cpu_percent],
  drgrp.[min_memory_percent],
  drgrp.[max_memory_percent],
  drgrp.[cap_cpu_percent],
  drgrp.[min_iops_per_volume],
  drgrp.[max_iops_per_volume],
  drgrp.[read_io_queued_total],
  drgrp.[read_io_issued_total],
  drgrp.[read_io_completed_total],
  drgrp.[read_io_throttled_total],
  drgrp.[read_bytes_total],
  drgrp.[read_io_stall_total_ms],
  drgrp.[read_io_stall_queued_ms],
  drgrp.[write_io_queued_total],
  drgrp.[write_io_issued_total],
  drgrp.[write_io_completed_total],
  drgrp.[write_io_throttled_total],
  drgrp.[write_bytes_total],
  drgrp.[write_io_stall_total_ms],
  drgrp.[write_io_stall_queued_ms],
  drgrp.[io_issue_violations_total],
  drgrp.[io_issue_delay_total_ms],
  drgrp.[io_issue_ahead_total_ms],
  drgrp.[reserved_io_limited_by_volume_total],
  drgrp.[io_issue_delay_non_throttled_total_ms],
  drgrp.[total_cpu_delayed_ms],
  drgrp.[total_cpu_active_ms],
  drgrp.[total_cpu_violation_delay_ms],
  drgrp.[total_cpu_violation_sec],
  drgrp.[total_cpu_usage_preemptive_ms]
FROM
  [sys].[dm_resource_governor_resource_pools] drgrp
```

Columns and interpretation

- `pool_id` / `Name` — pool identifier and name.
- `statistics_start_time` — start time for the collected statistics.
- CPU/memory fields (`total_cpu_usage_ms`, `cache_memory_kb`, `compile_memory_kb`, `used_memgrant_kb`, `total_memgrant_count`, `total_memgrant_timeout_count`, `active_memgrant_count`, `active_memgrant_kb`, `memgrant_waiter_count`, `max_memory_kb`, `used_memory_kb`, `target_memory_kb`, `out_of_memory_count`) — memory and grant usage metrics.
- `min_cpu_percent`, `max_cpu_percent`, `min_memory_percent`, `max_memory_percent`, `cap_cpu_percent` — configured CPU and memory limits.
- I/O metrics (`min_iops_per_volume`, `max_iops_per_volume`, `read_io_*`, `write_io_*`, `read_bytes_total`, `write_bytes_total`, `*_io_stall_*`, `io_issue_*`) — I/O usage and throttling statistics per pool.
- `total_cpu_delayed_ms`, `total_cpu_active_ms`, `total_cpu_violation_delay_ms`, `total_cpu_violation_sec`, `total_cpu_usage_preemptive_ms` — CPU delay and violation metrics.

How to interpret

- Use these metrics to monitor pool resource usage, check for memory grant pressure and I/O throttling, and validate Resource Governor behavior versus configured limits.
- High `memgrant_waiter_count` or `total_memgrant_timeout_count` indicates memory grant pressure. I/O stall metrics show storage-related contention.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorResourcePoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorResourcePoolsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Pool:{r.PoolId} Name:{r.Name} CPUms:{r.TotalCpuUsageMs} UsedMemKB:{r.UsedMemoryKb} MemGrantWaiters:{r.MemgrantWaiterCount}");
}
```

See also:

- [sys.dm_resource_governor_resource_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-resource-pools)
