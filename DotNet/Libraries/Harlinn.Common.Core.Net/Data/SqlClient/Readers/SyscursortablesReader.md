# SyscursortablesReader

Overview

`SyscursortablesReader` wraps `sys.syscursortables` and exposes table references used by server-side cursors (legacy view).

Reader SQL

```
SELECT
  s17.[cursor_handle],
  s17.[table_owner],
  s17.[table_name],
  s17.[optimizer_hint],
  s17.[lock_type],
  s17.[server_name],
  s17.[Objectid],
  s17.[Dbid],
  s17.[Dbname]
FROM
  [sys].[syscursortables] s17
```

Columns and interpretation

- `cursor_handle` (int): Cursor handle referencing the table.
- `table_owner` (string?): Owner/schema of the referenced table.
- `table_name` (string?): Table name.
- `optimizer_hint` (short): Hint provided for query optimizer when cursor defined.
- `lock_type` (short): Locking mode used for cursor (shared, exclusive, etc.).
- `server_name` (string?): Remote server name for distributed queries.
- `Objectid`, `Dbid`, `Dbname` (int/string?): Identifiers mapping to object and database.

How to interpret

- This view helps map cursor-result tables to their definitions, locking and optimizer hints used during cursor creation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscursortablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscursortablesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Cursor:{r.CursorHandle} Table:{r.TableOwner}.{r.UserTableName} Lock:{r.LockType} OptimizerHint:{r.OptimizerHint}");
```

See also:

- sys.syscursortables (legacy)
