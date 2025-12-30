# DmPalWaitStatsReader — reference

Overview

`DmPalWaitStatsReader` wraps `sys.dm_pal_wait_stats` and returns wait statistics from the platform abstraction layer, typically used on non-Windows platforms.

Reader SQL

```
SELECT
  dpws.[wait_type],
  dpws.[waiting_threads_count],
  dpws.[wait_time_ms],
  dpws.[max_wait_time_ms]
FROM
  [sys].[dm_pal_wait_stats] dpws
```

Columns and interpretation

- `wait_type` — name of the PAL wait type.
- `waiting_threads_count` — cumulative count of waits for the wait type.
- `wait_time_ms` — cumulative wait time in milliseconds.
- `max_wait_time_ms` — maximum observed wait time in milliseconds.

How to interpret

- Similar to `dm_os_wait_stats` but for PAL instrumentation; helps identify low-level wait bottlenecks.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalWaitStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalWaitStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.WaitType}: Count={r.WaitingThreadsCount} TotalMs={r.WaitTimeMs} MaxMs={r.MaxWaitTimeMs}");
}
```

See also:

- [sys.dm_pal_wait_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-wait-stats)
