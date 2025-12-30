# DmCacheHitStatsReader — reference

Overview

`DmCacheHitStatsReader` wraps `sys.dm_cache_hit_stats` and exposes cache hit metrics for various distributions.

Reader SQL

```
SELECT
  dchs.[distribution_id],
  dchs.[cache_hit],
  dchs.[remote_hit],
  dchs.[collection_start_time]
FROM
  [sys].[dm_cache_hit_stats] dchs
```

Selected columns (property mapping and brief meaning)

- `distribution_id` ? `DistributionId` (short?): Identifier for trace or distribution bucket.
- `cache_hit` ? `CacheHit` (long?): Number of cache hits observed.
- `remote_hit` ? `RemoteHit` (long?): Number of remote hits observed.
- `collection_start_time` ? `CollectionStartTime` (DateTime?): Time when this collection/window began.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCacheHitStatsDataType` objects.
