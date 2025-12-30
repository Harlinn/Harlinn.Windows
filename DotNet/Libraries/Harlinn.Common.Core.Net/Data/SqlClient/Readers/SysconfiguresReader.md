# SysconfiguresReader

Overview

`SysconfiguresReader` wraps `sys.sysconfigures` and exposes server or database configuration options (legacy internal view).

Reader SQL

```
SELECT
  s22.[Value],
  s22.[Config],
  s22.[Comment],
  s22.[Status]
FROM
  [sys].[sysconfigures] s22
```

Columns and interpretation

- `Value` (int?): The configured value for the option.
- `Config` (int): Configuration option id.
- `Comment` (string): Description of the configuration option.
- `Status` (short?): Status flags for the configuration entry.

How to interpret

- This view provides legacy configuration entries; modern servers expose configuration via `sp_configure` and dynamic management views. Use `Config` to map to known configuration options.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysconfiguresReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysconfiguresReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Config:{r.Config} Value:{r.Value} Comment:{r.Comment}");
```

See also:

- sys.sysconfigures (legacy)
- sp_configure (documentation): https://learn.microsoft.com/en-us/sql/database-engine/configure-windows/sp-configure
