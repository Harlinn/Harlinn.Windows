# DmOsSublatchesReader — reference

Overview

`DmOsSublatchesReader` wraps `sys.dm_os_sublatches` and exposes latch hierarchy information including superlatch and sublatch addresses and partitioning.

Reader SQL

```
SELECT
  dos0.[superlatch_address],
  dos0.[sublatch_address],
  dos0.[partition_id]
FROM
  [sys].[dm_os_sublatches] dos0
```

Columns and interpretation

- `superlatch_address` — binary address of the parent latch; may be NULL when not applicable.
- `sublatch_address` — binary address of the sublatch.
- `partition_id` — partition identifier associated with the latch (used for partitioned data structures).

How to interpret

- Latches are lightweight synchronization primitives; `superlatch_address` groups sublatches used for partitioned structures.
- Use `partition_id` to map contention or latch activity to specific partitions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsSublatchesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsSublatchesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Super:{(r.SuperlatchAddress==null?"<null>":BitConverter.ToString(r.SuperlatchAddress))} Sublatch:{BitConverter.ToString(r.SublatchAddress)} Partition:{r.PartitionId}");
}
```

See also:

- [sys.dm_os_sublatches](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-sublatches)
