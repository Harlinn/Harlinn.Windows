# DmOsMemoryAllocationsReader — reference

Overview

`DmOsMemoryAllocationsReader` wraps `sys.dm_os_memory_allocations` and returns detailed information about individual memory allocations within the SQL Server process, including allocation addresses, size, creation time and allocation site.

Reader SQL

```
SELECT
  doma.[memory_allocation_address],
  doma.[size_in_bytes],
  doma.[creation_time],
  doma.[memory_object_address],
  doma.[memory_node_id],
  doma.[allocator_stack_address],
  doma.[source_file],
  doma.[line_num],
  doma.[sequence_num],
  doma.[Tag]
FROM
  [sys].[dm_os_memory_allocations] doma
```

Columns and interpretation

- `memory_allocation_address` ? binary identifier for the allocation.
- `size_in_bytes` ? allocated size in bytes.
- `creation_time` ? timestamp when allocation occurred.
- `memory_object_address` ? associated memory object address.
- `memory_node_id` ? NUMA memory node id where allocation resides.
- `allocator_stack_address` ? stack address representing allocation call site.
- `source_file` ? source file name if available (debug builds).
- `line_num` ? source code line number for allocation site.
- `sequence_num` ? allocation sequence number.
- `Tag` ? numeric tag to categorize allocations.

How to interpret

- Use to investigate memory leaks, hot allocation sites and NUMA distribution of allocated memory.
- `source_file` and `line_num` are most valuable in debug/diagnostic builds where allocation site info is available.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryAllocationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var a = new DmOsMemoryAllocationsReader(rdr, ownsReader:false);
while (a.Read())
{
    Console.WriteLine($"Addr:{BitConverter.ToString(a.MemoryAllocationAddress)} Size:{a.SizeInBytes} Node:{a.MemoryNodeId} File:{a.SourceFile}:{a.LineNum} Tag:{a.Tag}");
}
```

See also:

- [sys.dm_os_memory_allocations](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-allocations)
