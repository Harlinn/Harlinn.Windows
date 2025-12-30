# DmOsMemoryObjectsReader — reference

Overview

`DmOsMemoryObjectsReader` wraps `sys.dm_os_memory_objects` and returns information about memory objects allocated by SQL Server including sizes, ownership, node affinity and contention metrics.

Reader SQL

```
SELECT
  domo.[memory_object_address],
  domo.[parent_address],
  domo.[pages_in_bytes],
  domo.[creation_options],
  domo.[bytes_used],
  domo.[Type],
  domo.[Name],
  domo.[memory_node_id],
  domo.[creation_time],
  domo.[page_size_in_bytes],
  domo.[max_pages_in_bytes],
  domo.[page_allocator_address],
  domo.[creation_stack_address],
  domo.[sequence_num],
  domo.[partition_type],
  domo.[partition_type_desc],
  domo.[contention_factor],
  domo.[waiting_tasks_count],
  domo.[exclusive_access_count]
FROM
  [sys].[dm_os_memory_objects] domo
```

Columns and interpretation

- `memory_object_address` ? binary id/address of the memory object.
- `parent_address` ? optional parent object address.
- `pages_in_bytes` ? allocated pages in bytes for the object.
- `creation_options` ? numeric flags for creation options.
- `bytes_used` ? actual bytes used by the object.
- `Type` / `Name` ? object type and optional name.
- `memory_node_id` ? NUMA node id for the object.
- `creation_time` ? allocation timestamp.
- `page_size_in_bytes` / `max_pages_in_bytes` ? page size and maximum allowed pages in bytes.
- `page_allocator_address` ? allocator structure address.
- `creation_stack_address` ? optional stack address for creation site.
- `sequence_num` ? creation sequence number.
- `partition_type` / `partition_type_desc` ? partitioning info.
- `contention_factor` / `waiting_tasks_count` / `exclusive_access_count` ? contention metrics for the object.

How to interpret

- Useful to inspect large or contended memory objects and identify their node placement. High contention metrics indicate synchronization bottlenecks on the memory object.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryObjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var o = new DmOsMemoryObjectsReader(rdr, ownsReader:false);
while (o.Read())
{
    Console.WriteLine($"Obj:{BitConverter.ToString(o.MemoryObjectAddress)} Name:{o.Name} Type:{o.Type} Bytes:{o.BytesUsed} PagesBytes:{o.PagesInBytes} Node:{o.MemoryNodeId}");
}
```

See also:

- [sys.dm_os_memory_objects](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-objects)
