# TypeAssemblyUsagesReader

Overview

`TypeAssemblyUsagesReader` reads `sys.type_assembly_usages`, which maps user-defined types to the assemblies that implement them.

Reader SQL

```
SELECT
  tau.[user_type_id],
  tau.[assembly_id]
FROM
  [sys].[type_assembly_usages] tau
```

Columns and interpretation

- `user_type_id` (int): The ID of the user-defined type in `sys.types` that is implemented in an assembly.
- `assembly_id` (int): The ID of the assembly in `sys.assemblies` that provides the implementation for the user-defined type.

How to interpret

- Join `user_type_id` to `sys.types` and `assembly_id` to `sys.assemblies` to find which CLR assembly implements a given user-defined type.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TypeAssemblyUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TypeAssemblyUsagesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"UserTypeId:{r.UserTypeId} AssemblyId:{r.AssemblyId}");
```

See also:

- [sys.type_assembly_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-type-assembly-usages)
