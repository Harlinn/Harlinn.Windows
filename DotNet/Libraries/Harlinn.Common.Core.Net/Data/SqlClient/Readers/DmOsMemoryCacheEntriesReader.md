# DmOsMemoryCacheEntriesReader — reference

Overview

`DmOsMemoryCacheEntriesReader` wraps `sys.dm_os_memory_cache_entries` and returns details about individual cache entries including sizes, cost metrics and usage statistics.

Reader SQL

```
SELECT
  domce.[cache_address],
  domce.[Name],
  domce.[Type],
  domce.[entry_address],
  domce.[entry_data_address],
  domce.[in_use_count],
  domce.[is_dirty],
  domce.[disk_ios_count],
  domce.[context_switches_count],
  domce.[original_cost],
  domce.[current_cost],
  domce.[memory_object_address],
  domce.[pages_kb],
  domce.[entry_data],
  domce.[pool_id],
  domce.[time_to_generate],
  domce.[use_count],
  domce.[average_time_between_uses],
  domce.[time_since_last_use],
  domce.[probability_of_reuse],
  domce.[Value]
FROM
  [sys].[dm_os_memory_cache_entries] domce
```

Columns and interpretation

- `cache_address` ? binary cache identifier.
- `Name` ? cache name.
- `Type` ? cache type.
- `entry_address` / `entry_data_address` ? addresses for entry metadata and data.
- `in_use_count` ? count of concurrent users of the entry.
- `is_dirty` ? whether the entry has been modified and not synchronized to backing store.
- `disk_ios_count` ? number of disk I/O operations related to this entry.
- `context_switches_count` ? context switches while servicing this entry.
- `original_cost` / `current_cost` ? cost heuristics used for eviction prioritization.
- `memory_object_address` ? associated memory object address if present.
- `pages_kb` ? KB consumed by the entry.
- `entry_data` ? possibly textual representation of entry data.
- `pool_id` ? id of memory pool used.
- `time_to_generate` ? time required to generate the entry (if expensive to produce).
- `use_count` ? usage count for the entry.
- `average_time_between_uses` / `time_since_last_use` ? temporal usage statistics.
- `probability_of_reuse` ? heuristic probability for reuse.
- `Value` ? computed value metric used by cache algorithms.

How to interpret

- Use cost, use_count and probability metrics to identify entries that should be retained vs evicted. High `time_to_generate` and high `probability_of_reuse` indicate expensive and frequently used entries.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryCacheEntriesReader.Sql;
using var rdr = cmd.ExecuteReader();
var e = new DmOsMemoryCacheEntriesReader(rdr, ownsReader:false);
while (e.Read())
{
    Console.WriteLine($"Cache:{e.Name} EntryPagesKB:{e.PagesKb} InUse:{e.InUseCount} Dirty:{e.IsDirty} UseCount:{e.UseCount} Value:{e.Value}");
}
```

See also:

- [sys.dm_os_memory_cache_entries](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-cache-entries)
