# DmOsMemoryClerksReader — reference

Overview

`DmOsMemoryClerksReader` wraps `sys.dm_os_memory_clerks` and lists memory clerks with memory usage breakdowns and related addresses.

Reader SQL

```
SELECT
  domc.[memory_clerk_address],
  domc.[Type],
  domc.[Name],
  domc.[memory_node_id],
  domc.[pages_kb],
  domc.[virtual_memory_reserved_kb],
  domc.[virtual_memory_committed_kb],
  domc.[awe_allocated_kb],
  domc.[shared_memory_reserved_kb],
  domc.[shared_memory_committed_kb],
  domc.[page_size_in_bytes],
  domc.[page_allocator_address],
  domc.[host_address],
  domc.[parent_memory_broker_type]
FROM
  [sys].[dm_os_memory_clerks] domc
```

Columns and interpretation

- `memory_clerk_address` ? binary address for the clerk instance.
- `Type` / `Name` ? clerk type and human name.
- `memory_node_id` ? NUMA node id where the clerk's pages reside.
- `pages_kb` ? KB held by the clerk in pages.
- `virtual_memory_reserved_kb` / `virtual_memory_committed_kb` ? virtual memory reserved and committed.
- `awe_allocated_kb` ? KB allocated via AWE (on 32-bit/older configurations).
- `shared_memory_reserved_kb` / `shared_memory_committed_kb` ? shared memory usage.
- `page_size_in_bytes` ? OS page size used by the clerk.
- `page_allocator_address` ? address of page allocator structure.
- `host_address` ? host address associated with the clerk.
- `parent_memory_broker_type` ? optional parent memory broker type string.

How to interpret

- Use to break down memory usage by clerk and NUMA node to find memory fragmentation or hot clerks.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryClerksReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmOsMemoryClerksReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Clerk:{c.Name} Type:{c.Type} PagesKB:{c.PagesKb} VMCommittedKB:{c.VirtualMemoryCommittedKb}");
}
```

See also:

- [sys.dm_os_memory_clerks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-clerks)
