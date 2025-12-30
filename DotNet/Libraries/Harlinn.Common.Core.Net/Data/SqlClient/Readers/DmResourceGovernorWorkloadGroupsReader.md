# DmResourceGovernorWorkloadGroupsReader — reference

Overview

`DmResourceGovernorWorkloadGroupsReader` wraps `sys.dm_resource_governor_workload_groups` and provides statistics and configuration for workload groups within Resource Governor.

Reader SQL

```
SELECT
  drgwg.[group_id],
  drgwg.[Name],
  drgwg.[pool_id],
  drgwg.[external_pool_id],
  drgwg.[statistics_start_time],
  drgwg.[total_request_count],
  drgwg.[total_queued_request_count],
  drgwg.[active_request_count],
  drgwg.[queued_request_count],
  drgwg.[total_cpu_limit_violation_count],
  drgwg.[total_cpu_usage_ms],
  drgwg.[max_request_cpu_time_ms],
  drgwg.[blocked_task_count],
  drgwg.[total_lock_wait_count],
  drgwg.[total_lock_wait_time_ms],
  drgwg.[total_query_optimization_count],
  drgwg.[total_suboptimal_plan_generation_count],
  drgwg.[total_reduced_memgrant_count],
  drgwg.[max_request_grant_memory_kb],
  drgwg.[active_parallel_thread_count],
  drgwg.[Importance],
  drgwg.[request_max_memory_grant_percent],
  drgwg.[request_max_cpu_time_sec],
  drgwg.[request_memory_grant_timeout_sec],
  drgwg.[group_max_requests],
  drgwg.[max_dop],
  drgwg.[effective_max_dop],
  drgwg.[total_cpu_usage_preemptive_ms],
  drgwg.[request_max_memory_grant_percent_numeric]
FROM
  [sys].[dm_resource_governor_workload_groups] drgwg
```

Columns and interpretation

- `group_id`, `Name` — identifier and name of the workload group.
- `pool_id`, `external_pool_id` — associated internal and external pool identifiers.
- `statistics_start_time` — when statistics collection began.
- Request counters (`total_request_count`, `total_queued_request_count`, `active_request_count`, `queued_request_count`) — workload activity metrics.
- CPU and resource violation counters (`total_cpu_limit_violation_count`, `total_cpu_usage_ms`, `max_request_cpu_time_ms`) — indicate CPU usage and limit breaches.
- `blocked_task_count`, `total_lock_wait_count`, `total_lock_wait_time_ms` — locking and blocking metrics.
- Optimization and plan metrics (`total_query_optimization_count`, `total_suboptimal_plan_generation_count`) — counts related to query optimization events.
- Memory grant metrics (`total_reduced_memgrant_count`, `max_request_grant_memory_kb`, `request_max_memory_grant_percent`, `request_max_memory_grant_percent_numeric`, `request_memory_grant_timeout_sec`) — track memory grant behavior.
- Parallelism (`active_parallel_thread_count`, `max_dop`, `effective_max_dop`) — parallel execution controls and counts.
- `Importance` — group importance as a descriptive string.
- `group_max_requests` — configured cap on concurrent requests for the group.
- `total_cpu_usage_preemptive_ms` — CPU usage measured during preemptive execution.

How to interpret

- Monitor request and queue counters for throttling or excessive queuing.
- Memory grant and CPU violation counters indicate resource pressure or misconfiguration.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorWorkloadGroupsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorWorkloadGroupsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Group:{r.Name} Pool:{r.PoolId} ActiveReq:{r.ActiveRequestCount} Queued:{r.QueuedRequestCount} CPUms:{r.TotalCpuUsageMs}");
}
```

See also:

- [sys.dm_resource_governor_workload_groups](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-workload-groups)
