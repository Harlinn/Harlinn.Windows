# DmOsWaitingTasksReader — reference

Overview

`DmOsWaitingTasksReader` wraps `sys.dm_os_waiting_tasks` and exposes tasks that are currently waiting including wait type, duration and blocking information.

Reader SQL

```
SELECT
  dowt.[waiting_task_address],
  dowt.[session_id],
  dowt.[exec_context_id],
  dowt.[wait_duration_ms],
  dowt.[wait_type],
  dowt.[resource_address],
  dowt.[blocking_task_address],
  dowt.[blocking_session_id],
  dowt.[blocking_exec_context_id],
  dowt.[resource_description]
FROM
  [sys].[dm_os_waiting_tasks] dowt
```

Columns and interpretation

- `waiting_task_address` — address identifying the waiting task.
- `session_id` — session id associated with the waiting task (nullable).
- `exec_context_id` — execution context id within the session.
- `wait_duration_ms` — how long the task has been waiting in milliseconds.
- `wait_type` — type or category of the wait (e.g., LCK_M_S, PAGEIOLATCH_EX).
- `resource_address` — address of the resource the task is waiting on (binary; may map to objects or locks).
- `blocking_task_address` — address of the task currently blocking the waiting task.
- `blocking_session_id` — session id of the blocking task.
- `blocking_exec_context_id` — execution context id of the blocking task.
- `resource_description` — textual description of the resource (lock, latch, etc.)

How to interpret

- Use `wait_duration_ms` and `wait_type` to identify long waits and their causes.
- `blocking_*` fields point to the blocker; correlate with other DMVs to find statements or sessions responsible.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsWaitingTasksReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsWaitingTasksReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"WaitType:{r.WaitType} DurationMs:{r.WaitDurationMs} Session:{r.SessionId} BlockingSession:{r.BlockingSessionId} ResourceDesc:{r.ResourceDescription}");
}
```

See also:

- [sys.dm_os_waiting_tasks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-waiting-tasks)
