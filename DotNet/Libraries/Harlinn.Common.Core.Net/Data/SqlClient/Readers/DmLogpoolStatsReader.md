# DmLogpoolStatsReader — reference

Overview

`DmLogpoolStatsReader` wraps `sys.dm_logpool_stats` and returns aggregated statistical counters for the log pool cache such as hits, misses, search lengths and memory status.

Reader SQL

```
SELECT
  dls.[hash_hit_total_search_length],
  dls.[hash_miss_total_search_length],
  dls.[hash_hits],
  dls.[hash_misses],
  dls.[hash_bucket_count],
  dls.[mem_status_stamp],
  dls.[mem_status],
  dls.[logpoolmgr_count],
  dls.[total_pages],
  dls.[private_pages]
FROM
  [sys].[dm_logpool_stats] dls
```

Columns and interpretation

- `hash_hit_total_search_length` ? cumulative search length for successful hash lookups; lower values indicate faster average search.
- `hash_miss_total_search_length` ? cumulative search length for lookups that missed.
- `hash_hits` ? number of hash table hits.
- `hash_misses` ? number of hash misses.
- `hash_bucket_count` ? number of buckets in the hash table.
- `mem_status_stamp` ? timestamp or counter indicating last memory status update.
- `mem_status` ? numeric memory status indicator.
- `logpoolmgr_count` ? number of log pool manager threads or instances.
- `total_pages` ? number of pages allocated to log pool.
- `private_pages` ? number of private pages used by log pool.

How to interpret

- `hash_hits` vs `hash_misses` and search lengths help quantify hash table efficiency. High misses or long search lengths indicate hash contention or inadequate sizing.
- `mem_status` and page counts indicate memory pressure or allocation behavior.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmLogpoolStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmLogpoolStatsReader(rdr, ownsReader:false);
if (s.Read())
{
    Console.WriteLine($"Hits:{s.HashHits} Misses:{s.HashMisses} HitSearchLen:{s.HashHitTotalSearchLength} MissSearchLen:{s.HashMissTotalSearchLength} Buckets:{s.HashBucketCount}");
}
```

See also:

- [sys.dm_logpool_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-logpool-stats)
