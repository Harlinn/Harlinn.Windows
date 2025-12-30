# DmCacheStatsReader — reference

Overview

`DmCacheStatsReader` wraps `sys.dm_cache_stats` and exposes aggregated cache statistics including hits and sizes.

Reader SQL

```
SELECT
  dcs.[distribution_id],
  dcs.[cache_hit],
  dcs.[remote_hit],
  dcs.[collection_start_time],
  dcs.[cache_used],
  dcs.[cache_available],
  dcs.[cache_capacity]
FROM
  [sys].[dm_cache_stats] dcs
```

Selected columns (property mapping and brief meaning)

- `distribution_id` ? `DistributionId` (short?): Identifier for the distribution.
- `cache_hit` ? `CacheHit` (long?): Number of cache hits.
- `remote_hit` ? `RemoteHit` (long?): Number of remote hits.
- `collection_start_time` ? `CollectionStartTime` (DateTime?): Start time for collection window.
- `cache_used` ? `CacheUsed` (long?): Cache used amount.
- `cache_available` ? `CacheAvailable` (long?): Cache available amount.
- `cache_capacity` ? `CacheCapacity` (long?): Cache total capacity.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCacheStatsDataType` objects.
