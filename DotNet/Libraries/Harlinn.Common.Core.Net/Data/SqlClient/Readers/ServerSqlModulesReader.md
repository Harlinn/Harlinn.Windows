# ServerSqlModulesReader

Overview

`ServerSqlModulesReader` wraps `sys.server_sql_modules` and exposes T-SQL module definitions stored at server scope (e.g., server assemblies' SQL wrappers).

Reader SQL

```
SELECT
  ssm0.[object_id],
  ssm0.[Definition],
  ssm0.[uses_ansi_nulls],
  ssm0.[uses_quoted_identifier],
  ssm0.[execute_as_principal_id]
FROM
  [sys].[server_sql_modules] ssm0
```

Columns and interpretation

- `object_id` (int): Object id of the server-level module.
- `Definition` (string?): The T-SQL source text of the module.
- `uses_ansi_nulls` (bool?): Whether the module was created with ANSI NULL settings enabled.
- `uses_quoted_identifier` (bool?): Whether QUOTED_IDENTIFIER was enabled at creation.
- `execute_as_principal_id` (int?): Principal id used for EXECUTE AS context.

How to interpret

- `Definition` contains the SQL body; observe `uses_ansi_nulls` and `uses_quoted_identifier` for compatibility and deterministic behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerSqlModulesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerSqlModulesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} ExecAs:{r.ExecuteAsPrincipalId} UsesAnsiNulls:{r.UsesAnsiNulls}");
```

See also:

- [sys.server_sql_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-sql-modules)
