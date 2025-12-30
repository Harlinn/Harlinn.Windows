# DmOsSpinlockStatsReader — reference

Overview

`DmOsSpinlockStatsReader` wraps `sys.dm_os_spinlock_stats` and exposes spinlock contention statistics such as collisions, spins, sleep time and backoffs for named spinlocks.

Reader SQL

```
SELECT
  doss.[Name],
  doss.[Collisions],
  doss.[Spins],
  doss.[spins_per_collision],
  doss.[sleep_time],
  doss.[Backoffs]
FROM
  [sys].[dm_os_spinlock_stats] doss
```

Columns and interpretation

- `Name` — friendly name identifying the spinlock or category.
- `Collisions` — number of times a thread found the spinlock already held (contention count).
- `Spins` — number of spin attempts made while waiting for the lock.
- `spins_per_collision` — average spins performed per collision; higher values indicate more busy-waiting per contention.
- `sleep_time` — cumulative time spent sleeping (typically in microseconds or milliseconds depending on platform) while waiting for the spinlock. Probably/guesswork: unit may vary.
- `Backoffs` — number of exponential backoff events where the waiter yielded or backed off to avoid hot spinning.

How to interpret

- High `Collisions` and `Spins` indicate heavy contention; investigate associated subsystem.
- Large `spins_per_collision` suggests long busy-waiting; tuning backoffs may help.
- `Sleep_time` and `Backoffs` show how often waiting threads are yielding rather than spinning.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsSpinlockStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsSpinlockStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.Name}: Collisions={r.Collisions} Spins={r.Spins} Spins/Collision={r.SpinsPerCollision} Backoffs={r.Backoffs}");
}
```

See also:

- [sys.dm_os_spinlock_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-spinlock-stats)
