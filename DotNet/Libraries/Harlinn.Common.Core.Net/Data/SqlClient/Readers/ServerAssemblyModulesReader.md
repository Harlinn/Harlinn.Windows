# ServerAssemblyModulesReader

Overview

`ServerAssemblyModulesReader` wraps `sys.server_assembly_modules` and exposes CLR assembly module mappings for server-scoped assemblies.

Reader SQL

```
SELECT
  sam.[object_id],
  sam.[assembly_id],
  sam.[assembly_class],
  sam.[assembly_method],
  sam.[execute_as_principal_id]
FROM
  [sys].[server_assembly_modules] sam
```

Columns and interpretation

- `object_id` (int): Object id of the assembly module object.
- `assembly_id` (int): Identifier of the assembly to which this module belongs.
- `assembly_class` (string?): CLR class name exposed by the assembly module.
- `assembly_method` (string?): CLR method name used.
- `execute_as_principal_id` (int?): Principal id used for execution context (EXECUTE AS).

How to interpret

- These rows relate CLR assembly modules to the server-level assembly registration. Use `assembly_id` to join to assembly metadata.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerAssemblyModulesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerAssemblyModulesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Assembly:{r.AssemblyId} Class:{r.AssemblyClass} Method:{r.AssemblyMethod}");
```

See also:

- [sys.server_assembly_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-assembly-modules)

