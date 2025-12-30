# SyscursorrefsReader

Overview

`SyscursorrefsReader` wraps `sys.syscursorrefs` and exposes references to cursor names and scope information (legacy view).

Reader SQL

```
SELECT
  s19.[reference_name],
  s19.[cursor_scope],
  s19.[cursor_handl]
FROM
  [sys].[syscursorrefs] s19
```

Columns and interpretation

- `reference_name` (string?): Name used to reference the cursor.
- `cursor_scope` (byte): Scope code indicating where the cursor is valid (local/global/session).
- `cursor_handl` (int): Numeric handle identifying the cursor instance.

How to interpret

- Use this view to map named cursor references to their internal handles and scope.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscursorrefsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscursorrefsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Ref:{r.ReferenceName} Scope:{r.CursorScope} Handle:{r.CursorHandl}");
```

See also:

- sys.syscursorrefs (legacy)
