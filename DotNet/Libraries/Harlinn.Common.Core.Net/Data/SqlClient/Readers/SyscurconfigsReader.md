# SyscurconfigsReader

Overview

`SyscurconfigsReader` wraps `sys.syscurconfigs` and exposes current server or database configuration values (legacy view).

Reader SQL

```
SELECT
  s21.[Value],
  s21.[Config],
  s21.[Comment],
  s21.[Status]
FROM
  [sys].[syscurconfigs] s21
```

Columns and interpretation

- `Value` (int): Current value of the configuration.
- `Config` (short?): Configuration option id.
- `Comment` (string): Description of the configuration option.
- `Status` (short?): Status flags.

How to interpret

- Use this to inspect runtime-configured parameters. Prefer using `sys.configurations` and `sp_configure` for modern configuration management.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscurconfigsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscurconfigsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Config:{r.Config} Value:{r.Value} Comment:{r.Comment}");
```

See also:

- sys.syscurconfigs (legacy)
- [sys.configurations](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-configurations)
