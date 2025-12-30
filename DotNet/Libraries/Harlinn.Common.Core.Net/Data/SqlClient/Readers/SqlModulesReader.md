# SqlModulesReader

Overview

`SqlModulesReader` wraps `sys.sql_modules` and exposes T-SQL module definitions and attributes for programmable objects (functions, procedures, triggers, views).

Reader SQL

```
SELECT sm.[object_id]
    ,sm.[definition]
    ,sm.[uses_ansi_nulls]
    ,sm.[uses_quoted_identifier]
    ,sm.[is_schema_bound]
    ,sm.[uses_database_collation]
    ,sm.[is_recompiled]
    ,sm.[null_on_null_input]
    ,sm.[execute_as_principal_id]
    ,sm.[uses_native_compilation]
    ,sm.[inline_type]
FROM [sys].[sql_modules] sm
```

Columns and interpretation

- `object_id` (int): Object id of the module (procedure, function, view, trigger).
- `definition` (string?): T-SQL source text of the module.
- `uses_ansi_nulls` (bool): Whether ANSI_NULLS was ON when the module was created.
- `uses_quoted_identifier` (bool): Whether QUOTED_IDENTIFIER was ON when created.
- `is_schema_bound` (bool): Whether the module is schema-bound.
- `uses_database_collation` (bool): Whether database collation is used for the module.
- `is_recompiled` (bool): Whether module is marked to recompile on use.
- `null_on_null_input` (bool): Indicates RETURNS NULL ON NULL INPUT semantics (for scalar functions).
- `execute_as_principal_id` (int?): Principal id used for EXECUTE AS context, if any.
- `uses_native_compilation` (bool): Whether module uses native compilation (In-Memory OLTP natively compiled modules).
- `inline_type` (bool): Whether function is inline (inline table-valued function) or not.

How to interpret

- `definition` contains the module body; use `is_schema_bound` to determine if referenced objects can be altered without dropping the module. `uses_native_compilation` and `inline_type` indicate special execution models.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SqlModulesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SqlModulesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Object:{r.GetObjectId()} SchemaBound:{r.GetIsSchemaBound()} Native:{r.GetUsesNativeCompilation()}");
```

See also:

- [sys.sql_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-modules)
