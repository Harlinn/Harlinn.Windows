# DmCacheSizeReader — reference

Overview

`DmCacheSizeReader` wraps `sys.dm_cache_size` and exposes cache size metrics (used, available, capacity) per distribution.

Reader SQL

```
SELECT
  dcs0.[distribution_id],
  dcs0.[cache_used],
  dcs0.[cache_available],
  dcs0.[cache_capacity]
FROM
  [sys].[dm_cache_size] dcs0
```

Selected columns (property mapping and brief meaning)

- `distribution_id` ? `DistributionId` (short?): Identifier grouping cache statistics.
- `cache_used` ? `CacheUsed` (long?): Amount of cache currently in use (units per SQL Server docs).
- `cache_available` ? `CacheAvailable` (long?): Amount of cache available.
- `cache_capacity` ? `CacheCapacity` (long?): Total cache capacity.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCacheSizeDataType` objects.
