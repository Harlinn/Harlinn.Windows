# DmOsWorkersReader — reference

Overview

`DmOsWorkersReader` wraps `sys.dm_os_workers` and exposes per-worker execution and scheduling details including status flags, context addresses, and timing counters.

Reader SQL

```
SELECT
  dow.[worker_address],
  dow.[Status],
  dow.[is_preemptive],
  dow.[is_fiber],
  dow.[is_sick],
  dow.[is_in_cc_exception],
  dow.[is_fatal_exception],
  dow.[is_inside_catch],
  dow.[is_in_polling_io_completion_routine],
  dow.[context_switch_count],
  dow.[pending_io_count],
  dow.[pending_io_byte_count],
  dow.[pending_io_byte_average],
  dow.[wait_started_ms_ticks],
  dow.[wait_resumed_ms_ticks],
  dow.[task_bound_ms_ticks],
  dow.[worker_created_ms_ticks],
  dow.[exception_num],
  dow.[exception_severity],
  dow.[exception_address],
  dow.[Affinity],
  dow.[State],
  dow.[start_quantum],
  dow.[end_quantum],
  dow.[last_wait_type],
  dow.[return_code],
  dow.[quantum_used],
  dow.[max_quantum],
  dow.[boost_count],
  dow.[tasks_processed_count],
  dow.[fiber_address],
  dow.[task_address],
  dow.[memory_object_address],
  dow.[thread_address],
  dow.[signal_worker_address],
  dow.[scheduler_address],
  dow.[processor_group],
  dow.[worker_migration_count]
FROM
  [sys].[dm_os_workers] dow
```

Columns and interpretation

- `worker_address` — binary address of the worker.
- `Status` — numeric status code for the worker.
- `is_preemptive` — indicates worker is executing preemptive code.
- `is_fiber` — indicates the worker is a fiber.
- `is_sick` — indicates a sick worker state.
- `is_in_cc_exception` — indicates the worker is in a concurrency control exception.
- `is_fatal_exception` — indicates a fatal exception occurred.
- `is_inside_catch` — indicates worker is inside an exception handler.
- `is_in_polling_io_completion_routine` — indicates worker is in polling I/O completion.
- `context_switch_count` — number of context switches this worker experienced.
- `pending_io_count` — number of pending I/O ops for the worker.
- `pending_io_byte_count` — total bytes pending for I/O operations.
- `pending_io_byte_average` — average bytes per pending I/O operation.
- `wait_started_ms_ticks` — ms tick when the current wait started.
- `wait_resumed_ms_ticks` — ms tick when the wait was resumed.
- `task_bound_ms_ticks` — cumulative ms ticks bound to task.
- `worker_created_ms_ticks` — creation time in ms ticks for the worker.
- `exception_num` — exception number if one occurred.
- `exception_severity` — severity code for exception.
- `exception_address` — address associated with exception.
- `Affinity` — CPU affinity mask for the worker.
- `State` — textual state description for the worker.
- `start_quantum` / `end_quantum` — quantum window timing values.
- `last_wait_type` — last wait type string for the worker.
- `return_code` — last return code observed on worker.
- `quantum_used` — quantum used so far.
- `max_quantum` — maximum quantum assigned.
- `boost_count` — number of priority boosts.
- `tasks_processed_count` — number of tasks the worker has processed.
- `fiber_address` — fiber structure address if fiber-based.
- `task_address` — task address associated with the worker.
- `memory_object_address` — memory object address used by worker.
- `thread_address` — thread structure address associated with worker.
- `signal_worker_address` — worker address used for signaling.
- `scheduler_address` — scheduler address associated with worker.
- `processor_group` — processor group for the worker.
- `worker_migration_count` — number of migrations between schedulers or processors.

How to interpret

- The worker rows provide low-level insight into scheduling, IO wait, and exception conditions.
- Use `pending_io_*` and `wait_*` fields to investigate IO-bound workers.
- `worker_migration_count` can indicate load balancing or scheduler pressure.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsWorkersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsWorkersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Worker:{BitConverter.ToString(r.WorkerAddress)} Status:{r.Status} PendingIO:{r.PendingIoCount} Tasks:{r.TasksProcessedCount} Migrations:{r.WorkerMigrationCount}");
}
```

See also:

- [sys.dm_os_workers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-workers)
