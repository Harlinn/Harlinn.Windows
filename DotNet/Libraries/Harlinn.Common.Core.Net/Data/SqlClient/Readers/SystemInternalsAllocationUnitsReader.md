# SystemInternalsAllocationUnitsReader

Overview

`SystemInternalsAllocationUnitsReader` wraps `sys.system_internals_allocation_units` and exposes allocation unit metadata used by storage internals.

Reader SQL

```
SELECT
  siau.[allocation_unit_id],
  siau.[Type],
  siau.[type_desc],
  siau.[container_id],
  siau.[filegroup_id],
  siau.[total_pages],
  siau.[used_pages],
  siau.[data_pages],
  siau.[first_page],
  siau.[root_page],
  siau.[first_iam_page]
FROM
  [sys].[system_internals_allocation_units] siau
```

Columns and interpretation

- `allocation_unit_id` (bigint): Unique allocation unit identifier.
- `Type` (tinyint): Allocation unit type code.
- `type_desc` (string?): Allocation unit type description (e.g., IN_ROW_DATA, LOB_DATA, ROW_OVERFLOW_DATA).
- `container_id` (bigint): Container id linking to partition or object.
- `filegroup_id` (smallint): Filegroup id where allocation resides.
- `total_pages` (bigint): Total pages allocated to the unit.
- `used_pages` (bigint): Pages currently used.
- `data_pages` (bigint): Data pages count.
- `first_page` (binary): Binary representation/pointer to the first page.
- `root_page` (binary): Binary pointer to the root page.
- `first_iam_page` (binary): Binary pointer to the first IAM page.

How to interpret

- These internals are useful for low-level storage diagnostics and estimating space usage per allocation unit. For most admin tasks, `sys.allocation_units` and `sys.partitions` and `sys.dm_db_partition_stats` provide higher-level metrics.
- Binary page pointer fields are internal and not meant for direct manipulation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemInternalsAllocationUnitsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemInternalsAllocationUnitsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"AU:{r.AllocationUnitId} Type:{r.TypeDesc} Container:{r.ContainerId} TotalPages:{r.TotalPages} Used:{r.UsedPages}");
```

See also:

- [sys.system_internals_allocation_units](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-internals-allocation-units)
