# DmOsMemoryCacheClockHandsReader — reference

Overview

`DmOsMemoryCacheClockHandsReader` wraps `sys.dm_os_memory_cache_clock_hands` and returns per-cache clock hand traversal statistics used by cache eviction algorithms.

Reader SQL

```
SELECT
  domcch.[cache_address],
  domcch.[Name],
  domcch.[Type],
  domcch.[clock_hand],
  domcch.[clock_status],
  domcch.[rounds_count],
  domcch.[removed_all_rounds_count],
  domcch.[updated_last_round_count],
  domcch.[removed_last_round_count],
  domcch.[last_tick_time],
  domcch.[round_start_time],
  domcch.[last_round_start_time]
FROM
  [sys].[dm_os_memory_cache_clock_hands] domcch
```

Columns and interpretation

- `cache_address` ? binary address for the cache instance.
- `Name` ? cache name.
- `Type` ? cache type.
- `clock_hand` ? position/state of the clock hand used for eviction.
- `clock_status` ? textual status of the clock traversal.
- `rounds_count` ? number of full rounds performed by the clock hand.
- `removed_all_rounds_count` ? count of items removed during all rounds.
- `updated_last_round_count` ? items updated during last round.
- `removed_last_round_count` ? items removed during last round.
- `last_tick_time` / `round_start_time` / `last_round_start_time` ? timing metrics (ticks/epoch values) for clock operations.

How to interpret

- These metrics help understand cache eviction behavior. High removed counts indicate aggressive eviction; long round times indicate larger caches or slow processing.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryCacheClockHandsReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmOsMemoryCacheClockHandsReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Cache:{c.Name} Type:{c.Type} Rounds:{c.RoundsCount} RemovedLast:{c.RemovedLastRoundCount}");
}
```

See also:

- [sys.dm_os_memory_cache_clock_hands](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-cache-clock-hands)
