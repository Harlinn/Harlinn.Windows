# SchemasReader

Overview

`SchemasReader` wraps `sys.schemas` and exposes database schemas and their owning principals.

Reader SQL

```
SELECT [name]
    ,[schema_id]
    ,[principal_id]
FROM [sys].[schemas]
```

Columns and interpretation

- `name` (string): Schema name.
- `schema_id` (int): Schema identifier.
- `principal_id` (int): Owning principal id.

How to interpret

- `principal_id` maps to an entry in `sys.database_principals` for the owner.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SchemasReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SchemasReader(rdr, ownsReader:false);
foreach (var s in r.GetSchemas())
    Console.WriteLine($"Schema:{s.Name} Id:{s.SchemaId} Owner:{s.PrincipalId}");
```

See also:

- [sys.schemas](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-schemas)

