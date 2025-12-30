# DmOsSchedulersReader — reference

Overview

`DmOsSchedulersReader` wraps `sys.dm_os_schedulers` and returns per-scheduler metrics such as task counts, switch counts, CPU usage and queue lengths.

Reader SQL

```
SELECT
  dos.[scheduler_address],
  dos.[parent_node_id],
  dos.[scheduler_id],
  dos.[cpu_id],
  dos.[Status],
  dos.[is_online],
  dos.[is_idle],
  dos.[preemptive_switches_count],
  dos.[context_switches_count],
  dos.[idle_switches_count],
  dos.[current_tasks_count],
  dos.[runnable_tasks_count],
  dos.[current_workers_count],
  dos.[active_workers_count],
  dos.[work_queue_count],
  dos.[pending_disk_io_count],
  dos.[load_factor],
  dos.[yield_count],
  dos.[last_timer_activity],
  dos.[failed_to_create_worker],
  dos.[active_worker_address],
  dos.[memory_object_address],
  dos.[task_memory_object_address],
  dos.[quantum_length_us],
  dos.[total_cpu_usage_ms],
  dos.[total_cpu_idle_capped_ms],
  dos.[total_scheduler_delay_ms],
  dos.[ideal_workers_limit]
FROM
  [sys].[dm_os_schedulers] dos
```

Columns and interpretation

- `scheduler_address` ? binary address identifying the scheduler.
- `parent_node_id` ? node that owns the scheduler.
- `scheduler_id` / `cpu_id` ? scheduler and associated CPU id.
- `Status` / `is_online` / `is_idle` ? scheduler state indicators.
- `preemptive_switches_count` / `context_switches_count` / `idle_switches_count` ? switch counters.
- `current_tasks_count` / `runnable_tasks_count` ? number of tasks assigned and runnable tasks.
- `current_workers_count` / `active_workers_count` ? worker counts.
- `work_queue_count` ? length of the work queue.
- `pending_disk_io_count` ? number of pending disk IO for the scheduler.
- `load_factor` / `yield_count` / `last_timer_activity` ? load metrics and scheduling telemetry.
- `failed_to_create_worker` ? indicator if worker creation failed recently.
- `active_worker_address` / `memory_object_address` / `task_memory_object_address` ? addresses related to worker and task memory.
- `quantum_length_us` ? scheduling quantum in microseconds.
- `total_cpu_usage_ms` / `total_cpu_idle_capped_ms` / `total_scheduler_delay_ms` ? cumulative timing metrics.
- `ideal_workers_limit` ? ideal maximum workers for this scheduler.

How to interpret

- Use to identify scheduler CPU saturation, high runnable tasks, or frequent context switches that could indicate scheduling pressure.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsSchedulersReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmOsSchedulersReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Sched:{s.SchedulerId} CPU:{s.CpuId} Online:{s.IsOnline} Idle:{s.IsIdle} Runnable:{s.RunnableTasksCount} WorkQueue:{s.WorkQueueCount} CPUms:{s.TotalCpuUsageMs}");
}
```

See also:

- [sys.dm_os_schedulers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-schedulers)
