# SystemSqlModulesReader

Overview

`SystemSqlModulesReader` wraps `sys.system_sql_modules` and exposes SQL module definitions and related options for stored procedures, functions, triggers, and views.

Reader SQL

```
SELECT
  ssm.[object_id],
  ssm.[Definition],
  ssm.[uses_ansi_nulls],
  ssm.[uses_quoted_identifier],
  ssm.[is_schema_bound],
  ssm.[uses_database_collation],
  ssm.[is_recompiled],
  ssm.[null_on_null_input],
  ssm.[execute_as_principal_id],
  ssm.[uses_native_compilation],
  ssm.[inline_type],
  ssm.[is_inlineable]
FROM
  [sys].[system_sql_modules] ssm
```

Columns and interpretation

- `object_id` (int): Object id of the SQL module.
- `Definition` (string?): SQL text definition of the module.
- `uses_ansi_nulls` (bit): Whether ANSI_NULLS were ON when module was created.
- `uses_quoted_identifier` (bit): Whether QUOTED_IDENTIFIER was ON.
- `is_schema_bound` (bit): Whether the module is schema-bound.
- `uses_database_collation` (bit): Whether database collation is used.
- `is_recompiled` (bit): Whether the module should be recompiled on execution.
- `null_on_null_input` (bit): Whether module returns NULL on NULL input (for deterministic functions).
- `execute_as_principal_id` (int?): Principal id for EXECUTE AS clause.
- `uses_native_compilation` (bit): Whether native compilation is used (for natively compiled modules).
- `inline_type` (bit): Inline type indicator.
- `is_inlineable` (bit): Whether module is inlineable.

How to interpret

- `Definition` provides the module body; use for script extraction or analysis.
- Execution context and compilation flags help determine runtime behavior and security context.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemSqlModulesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemSqlModulesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} UsesAnsiNulls:{r.UsesAnsiNulls} Recompiled:{r.IsRecompiled} ExecAs:{r.ExecuteAsPrincipalId}");
```

See also:

- [sys.system_sql_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-sql-modules)
