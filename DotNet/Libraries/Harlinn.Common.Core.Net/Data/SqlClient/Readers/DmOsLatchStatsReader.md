# DmOsLatchStatsReader — reference

Overview

`DmOsLatchStatsReader` wraps `sys.dm_os_latch_stats` and provides latch contention statistics grouped by latch class.

Reader SQL

```
SELECT
  dols.[latch_class],
  dols.[waiting_requests_count],
  dols.[wait_time_ms],
  dols.[max_wait_time_ms]
FROM
  [sys].[dm_os_latch_stats] dols
```

Columns and interpretation

- `latch_class` ? latch class name (string).
- `waiting_requests_count` ? number of requests waiting for this latch class.
- `wait_time_ms` ? cumulative wait time in milliseconds for this latch class.
- `max_wait_time_ms` ? maximum single wait time in milliseconds observed.

How to interpret

- Use to identify latch contention hotspots. High waiting counts or large wait times indicate contention on internal structures.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsLatchStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var l = new DmOsLatchStatsReader(rdr, ownsReader:false);
while (l.Read())
{
    Console.WriteLine($"Latch:{l.LatchClass} Waiting:{l.WaitingRequestsCount} WaitMs:{l.WaitTimeMs} MaxWaitMs:{l.MaxWaitTimeMs}");
}
```

See also:

- [sys.dm_os_latch_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-latch-stats)
