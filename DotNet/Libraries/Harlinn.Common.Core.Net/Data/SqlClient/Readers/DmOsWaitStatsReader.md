# DmOsWaitStatsReader — reference

Overview

`DmOsWaitStatsReader` wraps `sys.dm_os_wait_stats` and returns aggregated wait statistics per wait type for the server.

Reader SQL

```
SELECT
  dows.[wait_type],
  dows.[waiting_tasks_count],
  dows.[wait_time_ms],
  dows.[max_wait_time_ms],
  dows.[signal_wait_time_ms]
FROM
  [sys].[dm_os_wait_stats] dows
```

Columns and interpretation

- `wait_type` — name of the wait type.
- `waiting_tasks_count` — cumulative number of waits of this type.
- `wait_time_ms` — cumulative wait time in milliseconds.
- `max_wait_time_ms` — maximum observed wait time for the wait type in milliseconds.
- `signal_wait_time_ms` — cumulative time spent on signal waits (time after being signaled) in milliseconds.

How to interpret

- High `wait_time_ms` with high `waiting_tasks_count` points to important bottlenecks; inspect top wait types.
- `signal_wait_time_ms` indicates time that threads spent runnable but waiting for CPU after the wait completed.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsWaitStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsWaitStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.WaitType}: Count={r.WaitingTasksCount} TotalMs={r.WaitTimeMs} MaxMs={r.MaxWaitTimeMs} SignalMs={r.SignalWaitTimeMs}");
}
```

See also:

- [sys.dm_os_wait_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-wait-stats)
