# DmOsMemoryNodeAccessStatsReader — reference

Overview

`DmOsMemoryNodeAccessStatsReader` wraps `sys.dm_os_memory_node_access_stats` and exposes remote vs local memory access counts between NUMA nodes for various page classes.

Reader SQL

```
SELECT
  domnas.[local_node],
  domnas.[remote_node],
  domnas.[page_class],
  domnas.[read_count],
  domnas.[write_count]
FROM
  [sys].[dm_os_memory_node_access_stats] domnas
```

Columns and interpretation

- `local_node` ? local NUMA node id.
- `remote_node` ? remote NUMA node id from which memory was accessed.
- `page_class` ? classification of pages (buffer pool, procedure cache, etc.).
- `read_count` / `write_count` ? counts of read and write accesses from remote to local node.

How to interpret

- Use to detect NUMA cross-node memory traffic; high remote read/write counts may indicate poor NUMA locality and potential performance issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryNodeAccessStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmOsMemoryNodeAccessStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Local:{s.LocalNode} Remote:{s.RemoteNode} PageClass:{s.PageClass} Reads:{s.ReadCount} Writes:{s.WriteCount}");
}
```

See also:

- [sys.dm_os_memory_node_access_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-node-access-stats)
