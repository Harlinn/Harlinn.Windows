# DmOsMemoryNodesReader — reference

Overview

`DmOsMemoryNodesReader` wraps `sys.dm_os_memory_nodes` and provides per-NUMA node memory usage and configuration data.

Reader SQL

```
SELECT
  domn.[memory_node_id],
  domn.[virtual_address_space_reserved_kb],
  domn.[virtual_address_space_committed_kb],
  domn.[locked_page_allocations_kb],
  domn.[pages_kb],
  domn.[shared_memory_reserved_kb],
  domn.[shared_memory_committed_kb],
  domn.[cpu_affinity_mask],
  domn.[online_scheduler_mask],
  domn.[processor_group],
  domn.[foreign_committed_kb],
  domn.[target_kb]
FROM
  [sys].[dm_os_memory_nodes] domn
```

Columns and interpretation

- `memory_node_id` ? NUMA node id.
- `virtual_address_space_reserved_kb` / `virtual_address_space_committed_kb` ? virtual address reservation/commitment in KB.
- `locked_page_allocations_kb` ? locked page allocations in KB.
- `pages_kb` ? KB consumed by pages on this node.
- `shared_memory_reserved_kb` / `shared_memory_committed_kb` ? shared memory usage on the node.
- `cpu_affinity_mask` ? CPU affinity mask for the node.
- `online_scheduler_mask` ? mask of online schedulers associated with the node.
- `processor_group` ? processor group id for the node.
- `foreign_committed_kb` ? KB committed by foreign allocations.
- `target_kb` ? target KB for allocations on this node.

How to interpret

- Use to verify NUMA memory distribution and ensure memory allocations align with expected targets.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryNodesReader.Sql;
using var rdr = cmd.ExecuteReader();
var n = new DmOsMemoryNodesReader(rdr, ownsReader:false);
while (n.Read())
{
    Console.WriteLine($"Node:{n.MemoryNodeId} PagesKB:{n.PagesKb} ReservedVAKB:{n.VirtualAddressSpaceReservedKb} OnlineMask:{n.OnlineSchedulerMask}");
}
```

See also:

- [sys.dm_os_memory_nodes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-nodes)
