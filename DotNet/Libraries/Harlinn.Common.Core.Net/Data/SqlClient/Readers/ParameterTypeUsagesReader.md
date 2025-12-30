# ParameterTypeUsagesReader — reference

Overview

`ParameterTypeUsagesReader` wraps `sys.parameter_type_usages` and returns mappings where a parameter uses a specific user-defined type.

Reader SQL

```
SELECT
  ptu.[object_id],
  ptu.[parameter_id],
  ptu.[user_type_id]
FROM
  [sys].[parameter_type_usages] ptu
```

Columns and interpretation

- `object_id` — object id of the procedure/function containing the parameter.
- `parameter_id` — parameter ordinal id.
- `user_type_id` — user type id that the parameter uses (from `sys.types`).

How to interpret

- Useful to identify where user-defined types are used in parameter signatures. Join to `sys.types` to get the type name.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ParameterTypeUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ParameterTypeUsagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} ParamId:{r.ParameterId} UserTypeId:{r.UserTypeId}");
}
```

See also:

- [sys.parameter_type_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-parameter-type-usages)
