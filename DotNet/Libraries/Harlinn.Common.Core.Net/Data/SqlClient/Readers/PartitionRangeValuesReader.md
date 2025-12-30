# PartitionRangeValuesReader — reference

Overview

`PartitionRangeValuesReader` wraps `sys.partition_range_values` and returns the boundary values for partition functions.

Reader SQL

```
SELECT
  prv.[function_id],
  prv.[boundary_id],
  prv.[parameter_id],
  prv.[Value]
FROM
  [sys].[partition_range_values] prv
```

Columns and interpretation

- `function_id` — id of the partition function.
- `boundary_id` — ordinal id for the boundary (1-based for boundary values).
- `parameter_id` — parameter id (for multi-parameter partition functions).
- `Value` — the boundary value; type depends on partition parameter type.

How to interpret

- Boundaries define how data maps to partition numbers. For single-parameter partition functions, boundary ids enumerate the cut points. Combine with `boundary_value_on_right` from `sys.partition_functions` to decide which partition includes the boundary value.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PartitionRangeValuesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PartitionRangeValuesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Function:{r.FunctionId} BoundaryId:{r.BoundaryId} Value:{r.Value}");
}
```

See also:

- [sys.partition_range_values](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-partition-range-values)
