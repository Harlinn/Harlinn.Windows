# DmOsTasksReader — reference

Overview

`DmOsTasksReader` wraps `sys.dm_os_tasks` and returns information about internal OS-level tasks used by SQL Server workers including context switches, pending I/O and associations to workers and requests.

Reader SQL

```
SELECT
  dot0.[task_address],
  dot0.[task_state],
  dot0.[context_switches_count],
  dot0.[pending_io_count],
  dot0.[pending_io_byte_count],
  dot0.[pending_io_byte_average],
  dot0.[scheduler_id],
  dot0.[session_id],
  dot0.[exec_context_id],
  dot0.[request_id],
  dot0.[worker_address],
  dot0.[host_address],
  dot0.[parent_task_address]
FROM
  [sys].[dm_os_tasks] dot0
```

Columns and interpretation

- `task_address` — binary address identifying the task.
- `task_state` — textual or code representation of the task state.
- `context_switches_count` — number of context switches observed for the task.
- `pending_io_count` — number of pending I/O operations for the task.
- `pending_io_byte_count` — total bytes pending for I/O operations.
- `pending_io_byte_average` — average size per pending I/O.
- `scheduler_id` — scheduler id this task is/was associated with.
- `session_id` — session id if the task is associated with a user session.
- `exec_context_id` — execution context id.
- `request_id` — request id linked to this task.
- `worker_address` — binary address of the worker handling the task (may be NULL).
- `host_address` — binary address of the host task structure.
- `parent_task_address` — binary address of a parent task if this is a subtask.

How to interpret

- Use `pending_io_*` fields to detect tasks waiting on I/O.
- `context_switches_count` can indicate CPU scheduling churn at task granularity.
- Map `worker_address`/`session_id` to higher-level DMVs to find associated requests.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsTasksReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsTasksReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Task:{BitConverter.ToString(r.TaskAddress)} State:{r.TaskState} Scheduler:{r.SchedulerId} Session:{r.SessionId} PendingIO:{r.PendingIoCount} Bytes:{r.PendingIoByteCount}");
}
```

See also:

- [sys.dm_os_tasks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-tasks)
