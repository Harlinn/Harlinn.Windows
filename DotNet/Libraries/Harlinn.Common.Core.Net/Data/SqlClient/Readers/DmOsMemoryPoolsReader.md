# DmOsMemoryPoolsReader — reference

Overview

`DmOsMemoryPoolsReader` wraps `sys.dm_os_memory_pools` and returns information about memory pools including free entry counts and removal metrics used by pool allocators.

Reader SQL

```
SELECT
  domp.[memory_pool_address],
  domp.[pool_id],
  domp.[Type],
  domp.[Name],
  domp.[max_free_entries_count],
  domp.[free_entries_count],
  domp.[removed_in_all_rounds_count]
FROM
  [sys].[dm_os_memory_pools] domp
```

Columns and interpretation

- `memory_pool_address` ? binary address for memory pool instance.
- `pool_id` ? numeric pool identifier.
- `Type` / `Name` ? pool type and name.
- `max_free_entries_count` ? maximum number of free entries allowed.
- `free_entries_count` ? current free entry count.
- `removed_in_all_rounds_count` ? total removed entries across clock rounds.

How to interpret

- Monitor `free_entries_count` to ensure the pool maintains capacity. High removed counts indicate frequent eviction.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryPoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmOsMemoryPoolsReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Pool:{p.Name} FreeEntries:{p.FreeEntriesCount} MaxFree:{p.MaxFreeEntriesCount} RemovedAllRounds:{p.RemovedInAllRoundsCount}");
}
```

See also:

- [sys.dm_os_memory_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-pools)
