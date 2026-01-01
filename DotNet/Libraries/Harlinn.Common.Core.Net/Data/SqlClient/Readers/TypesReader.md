# TypesReader

Overview

`TypesReader` wraps `sys.types` and exposes metadata about data types available in the database (system and user-defined types).

Reader SQL

```
SELECT st.[name]
    ,st.[system_type_id]
    ,st.[user_type_id]
    ,st.[schema_id]
    ,st.[principal_id]
    ,st.[max_length]
    ,st.[precision]
    ,st.[scale]
    ,st.[collation_name]
    ,st.[is_nullable]
    ,st.[is_user_defined]
    ,st.[is_assembly_type]
    ,st.[default_object_id]
    ,st.[rule_object_id]
    ,st.[is_table_type]
FROM [sys].[types] st
```

Columns and interpretation

- `name` (nvarchar): Type name.
- `system_type_id` (tinyint): Internal system type id.
- `user_type_id` (int): Database-unique id for the type.
- `schema_id` (int): Schema id of the type.
- `principal_id` (int?): Principal id of the owner, if different from schema owner.
- `max_length` (smallint): Maximum byte length.
- `precision` (tinyint): Numeric precision.
- `scale` (tinyint): Numeric scale.
- `collation_name` (nvarchar?): Collation name if applicable.
- `is_nullable` (bit): Whether the type allows NULLs.
- `is_user_defined` (bit): Whether the type is user-defined.
- `is_assembly_type` (bit): Whether the type is implemented in CLR assembly.
- `default_object_id` (int): Default constraint object id if defined.
- `rule_object_id` (int): Rule object id if defined.
- `is_table_type` (bit): Whether the type is a table type.

How to interpret

- Use `user_type_id` to reference the type in other catalog views and `name` for display.
- Assembly-backed types will have `is_assembly_type` true; join to `sys.assemblies` via `sys.type_assembly_usages` for implementation details.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TypesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Type:{r.GetName()} UserTypeId:{r.GetUserTypeId()} MaxLen:{r.GetMaxLength()} AssemblyType:{r.GetIsAssemblyType()}");
```

See also:

- [sys.types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-types)
