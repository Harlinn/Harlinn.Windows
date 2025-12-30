# ModuleAssemblyUsagesReader — reference

Overview

`ModuleAssemblyUsagesReader` wraps `sys.module_assembly_usages` and returns the associations between modules (CLR objects, assemblies) and the assemblies they reference.

Reader SQL

```
SELECT
  mau.[object_id],
  mau.[assembly_id]
FROM
  [sys].[module_assembly_usages] mau
```

Columns and interpretation

- `object_id` — object id of the module that references an assembly (for example a CLR stored procedure, function or type).
- `assembly_id` — id of the referenced assembly (from `sys.assemblies`).

How to interpret

- Use the pair to see which CLR modules depend on which assemblies. Join to `sys.assemblies` to get assembly names or `sys.objects` to get module metadata.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ModuleAssemblyUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ModuleAssemblyUsagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"ModuleObj:{r.ObjectId} AssemblyId:{r.AssemblyId}");
}
```

See also:

- [sys.module_assembly_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-module-assembly-usages)
