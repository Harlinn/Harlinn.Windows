# DmPalSpinlockStatsReader — reference

Overview

`DmPalSpinlockStatsReader` wraps `sys.dm_pal_spinlock_stats` and returns spinlock statistics reported by the platform abstraction layer, similar to `dm_os_spinlock_stats` but for PAL.

Reader SQL

```
SELECT
  dpss.[Name],
  dpss.[Collisions],
  dpss.[Spins],
  dpss.[spins_per_collision],
  dpss.[sleep_time],
  dpss.[Backoffs]
FROM
  [sys].[dm_pal_spinlock_stats] dpss
```

Columns and interpretation

- `Name` — name identifying the spinlock.
- `Collisions` — count of contention events.
- `Spins` — number of spins performed while waiting.
- `spins_per_collision` — average spins per collision.
- `sleep_time` — time spent sleeping while waiting (unit platform-dependent).
- `Backoffs` — count of backoff events when waiting threads yielded.

How to interpret

- Use to diagnose contention on PAL-level spinlocks; high values indicate contention hotspots.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalSpinlockStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalSpinlockStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.Name}: Collisions={r.Collisions} Spins={r.Spins} Backoffs={r.Backoffs}");
}
```

See also:

- [sys.dm_pal_spinlock_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-spinlock-stats)
