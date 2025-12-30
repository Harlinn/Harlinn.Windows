# DmExecSessionWaitStatsReader — reference

Overview

`DmExecSessionWaitStatsReader` wraps `sys.dm_exec_session_wait_stats` and provides aggregated wait statistics per session and wait type. Useful for identifying common waits experienced by sessions.

Reader SQL

```
SELECT
  desws.[session_id],
  desws.[wait_type],
  desws.[waiting_tasks_count],
  desws.[wait_time_ms],
  desws.[max_wait_time_ms],
  desws.[signal_wait_time_ms]
FROM
  [sys].[dm_exec_session_wait_stats] desws
```

Columns and interpretation

- `session_id` ? session identifier to which the waits apply.
- `wait_type` ? the type of wait (e.g., LCK_M_X, CXPACKET).
- `waiting_tasks_count` ? number of waiting tasks observed for that wait type.
- `wait_time_ms` ? cumulative wait time in milliseconds.
- `max_wait_time_ms` ? maximum observed wait time for a single wait occurrence.
- `signal_wait_time_ms` ? portion of wait time spent in signal (time waiting on CPU after being scheduled).

How to interpret

- High `wait_time_ms` with high `waiting_tasks_count` indicates a widespread or chronic wait type for the session.
- `signal_wait_time_ms` helps distinguish between waits that are IO/blocking vs CPU scheduling delays.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecSessionWaitStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var w = new DmExecSessionWaitStatsReader(rdr, ownsReader:false);
while (w.Read())
{
    Console.WriteLine($"Sess:{w.SessionId} Wait:{w.WaitType} Count:{w.WaitingTasksCount} TotalMs:{w.WaitTimeMs} MaxMs:{w.MaxWaitTimeMs} SignalMs:{w.SignalWaitTimeMs}");
}
```

See also:

- [sys.dm_exec_session_wait_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-session-wait-stats)
