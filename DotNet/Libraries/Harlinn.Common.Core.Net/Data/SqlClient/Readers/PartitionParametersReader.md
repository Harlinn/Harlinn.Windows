# PartitionParametersReader — reference

Overview

`PartitionParametersReader` wraps `sys.partition_parameters` and returns the type metadata for parameters used by partition functions.

Reader SQL

```
SELECT
  pp.[function_id],
  pp.[parameter_id],
  pp.[system_type_id],
  pp.[max_length],
  pp.[Precision],
  pp.[Scale],
  pp.[collation_name],
  pp.[user_type_id]
FROM
  [sys].[partition_parameters] pp
```

Columns and interpretation

- `function_id` — id of the partition function.
- `parameter_id` — parameter id within the function signature.
- `system_type_id`, `user_type_id`, `max_length`, `Precision`, `Scale`, `collation_name` — type metadata for the partition parameter.

How to interpret

- Use to inspect what data types are used for partition function boundaries; collation is relevant for string boundaries.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PartitionParametersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PartitionParametersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"FunctionId:{r.FunctionId} ParamId:{r.ParameterId} TypeId:{r.SystemTypeId} MaxLen:{r.MaxLength}");
}
```

See also:

- [sys.partition_parameters](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-partition-parameters)
