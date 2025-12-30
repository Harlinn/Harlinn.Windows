# PartitionSchemesReader — reference

Overview

`PartitionSchemesReader` wraps `sys.partition_schemes` and returns metadata about partition schemes that map partitions to filegroups or data spaces.

Reader SQL

```
SELECT
  ps.[Name],
  ps.[data_space_id],
  ps.[Type],
  ps.[type_desc],
  ps.[is_default],
  ps.[is_system],
  ps.[function_id]
FROM
  [sys].[partition_schemes] ps
```

Columns and interpretation

- `Name` — name of the partition scheme.
- `data_space_id` — id of the data space (filegroup/partitioning target).
- `Type` / `type_desc` — type and description of the scheme.
- `is_default` — whether the scheme is the default for the database.
- `is_system` — whether the scheme is a system scheme.
- `function_id` — partition function id associated with the scheme.

How to interpret

- Partition schemes map function partitions to storage. Use `function_id` to link to the partition function and `data_space_id` to map to filegroups or partitioning targets.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PartitionSchemesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PartitionSchemesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Scheme:{r.Name} DataSpaceId:{r.DataSpaceId} FunctionId:{r.FunctionId} Default:{r.IsDefault}");
}
```

See also:

- [sys.partition_schemes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-partition-schemes)
