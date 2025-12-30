# DmOsMemoryCacheHashTablesReader — reference

Overview

`DmOsMemoryCacheHashTablesReader` wraps `sys.dm_os_memory_cache_hash_tables` and returns hash table statistics for memory caches: bucket counts, hit/miss counts and bucket length distributions.

Reader SQL

```
SELECT
  domcht.[cache_address],
  domcht.[Name],
  domcht.[Type],
  domcht.[table_level],
  domcht.[buckets_count],
  domcht.[buckets_in_use_count],
  domcht.[buckets_min_length],
  domcht.[buckets_max_length],
  domcht.[buckets_avg_length],
  domcht.[buckets_max_length_ever],
  domcht.[hits_count],
  domcht.[misses_count],
  domcht.[buckets_avg_scan_hit_length],
  domcht.[buckets_avg_scan_miss_length]
FROM
  [sys].[dm_os_memory_cache_hash_tables] domcht
```

Columns and interpretation

- `cache_address` ? binary cache id.
- `Name` ? cache name.
- `Type` ? cache type.
- `table_level` ? hash table level (for multi-level hash implementations).
- `buckets_count` ? total buckets in the hash table.
- `buckets_in_use_count` ? number of buckets currently containing entries.
- `buckets_min_length` / `buckets_max_length` / `buckets_avg_length` ? distribution metrics for bucket chain lengths.
- `buckets_max_length_ever` ? historical max bucket length observed.
- `hits_count` / `misses_count` ? access hit/miss counters for hash lookups.
- `buckets_avg_scan_hit_length` / `buckets_avg_scan_miss_length` ? average scan lengths for hits and misses.

How to interpret

- Use hit/miss ratios and bucket lengths to detect hash table congestion. Increasing avg scan lengths indicate collision growth.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryCacheHashTablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmOsMemoryCacheHashTablesReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"Cache:{h.Name} Buckets:{h.BucketsCount} InUse:{h.BucketsInUseCount} Hits:{h.HitsCount} Misses:{h.MissesCount} AvgLen:{h.BucketsAvgLength}");
}
```

See also:

- [sys.dm_os_memory_cache_hash_tables](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-cache-hash-tables)
