# PartitionFunctionsReader — reference

Overview

`PartitionFunctionsReader` wraps `sys.partition_functions` and returns metadata about partition functions, including boundary behavior and partition count (fanout).

Reader SQL

```
SELECT
  pf.[Name],
  pf.[function_id],
  pf.[Type],
  pf.[type_desc],
  pf.[Fanout],
  pf.[boundary_value_on_right],
  pf.[is_system],
  pf.[create_date],
  pf.[modify_date]
FROM
  [sys].[partition_functions] pf
```

Columns and interpretation

- `Name` — name of the partition function.
- `function_id` — id of the partition function object.
- `Type` / `type_desc` — type code and description for the partition function.
- `Fanout` — number of partitions produced by the function (number of boundary values + 1).
- `boundary_value_on_right` — whether boundary values are assigned to the right partition.
- `is_system` — whether function is system-defined.
- `create_date` / `modify_date` — timestamps.

How to interpret

- `Fanout` indicates total partitions using the function. `boundary_value_on_right` is important to interpret how boundary points map to partition numbers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PartitionFunctionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PartitionFunctionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Function:{r.Name} Id:{r.FunctionId} Fanout:{r.Fanout} BoundaryOnRight:{r.BoundaryValueOnRight}");
}
```

See also:

- [sys.partition_functions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-partition-functions)
