# DmOsMemoryCacheCountersReader — reference

Overview

`DmOsMemoryCacheCountersReader` wraps `sys.dm_os_memory_cache_counters` and returns capacity and entry counts for SQL Server memory caches.

Reader SQL

```
SELECT
  domcc.[cache_address],
  domcc.[Name],
  domcc.[Type],
  domcc.[pages_kb],
  domcc.[pages_in_use_kb],
  domcc.[entries_count],
  domcc.[entries_in_use_count]
FROM
  [sys].[dm_os_memory_cache_counters] domcc
```

Columns and interpretation

- `cache_address` ? binary identifier for cache.
- `Name` ? cache name.
- `Type` ? cache type string.
- `pages_kb` ? total pages in KB allocated for cache.
- `pages_in_use_kb` ? KB currently in use by entries.
- `entries_count` ? total number of entries the cache can hold or has seen.
- `entries_in_use_count` ? number of entries currently in use.

How to interpret

- Useful for capacity planning of caches. Compare `pages_in_use_kb` to `pages_kb` to find cache utilization.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryCacheCountersReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmOsMemoryCacheCountersReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Cache:{c.Name} PagesKB:{c.PagesKb} InUseKB:{c.PagesInUseKb} Entries:{c.EntriesInUseCount}/{c.EntriesCount}");
}
```

See also:

- [sys.dm_os_memory_cache_counters](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-cache-counters)
