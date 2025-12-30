# MemoryOptimizedTablesInternalAttributesReader — reference

Overview

`MemoryOptimizedTablesInternalAttributesReader` wraps `sys.memory_optimized_tables_internal_attributes` and returns internal attributes for memory-optimized (In-Memory OLTP) tables, including xtp object id and type description.

Reader SQL

```
SELECT
  motia.[object_id],
  motia.[xtp_object_id],
  motia.[Type],
  motia.[type_desc],
  motia.[minor_id]
FROM
  [sys].[memory_optimized_tables_internal_attributes] motia
```

Columns and interpretation

- `object_id` — object id of the parent table (nullable for some internal artifacts).
- `xtp_object_id` — internal XTP (In-Memory OLTP) object id.
- `Type` / `type_desc` — internal attribute type and description.
- `minor_id` — minor id used to distinguish internal objects associated with the table.

How to interpret

- Use to inspect internal metadata for memory-optimized objects; `xtp_object_id` links to internal engine artifacts.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MemoryOptimizedTablesInternalAttributesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MemoryOptimizedTablesInternalAttributesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} XTP:{r.XtpObjectId} Type:{r.TypeDesc} Minor:{r.MinorId}");
}
```

See also:

- [sys.memory_optimized_tables_internal_attributes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-memory-optimized-tables-internal-attributes)
