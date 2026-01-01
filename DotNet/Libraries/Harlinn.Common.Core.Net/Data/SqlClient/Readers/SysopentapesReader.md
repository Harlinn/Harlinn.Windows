# SysopentapesReader

Overview

`SysopentapesReader` wraps `sys.sysopentapes` (legacy) and exposes names of currently open tape devices or tape entries (legacy feature).

Reader SQL

```
SELECT
  s10.[Opentape]
FROM
  [sys].[sysopentapes] s10
```

Columns and interpretation

- `Opentape` (string): Name or identifier of an open tape device or tape entry.

How to interpret

- This view is a relic of older SQL Server functionality for tape devices and may be empty or unsupported on modern installations.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysopentapesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysopentapesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"OpenTape:{r.Opentape}");
```

See also:

- [sys.sysopentapes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysopentapes)
