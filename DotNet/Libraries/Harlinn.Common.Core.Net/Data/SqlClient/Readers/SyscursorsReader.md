# SyscursorsReader

Overview

`SyscursorsReader` wraps `sys.syscursors` and exposes runtime metadata about server-side cursors (legacy diagnostic view).

Reader SQL

```
SELECT
  s18.[cursor_handle],
  s18.[cursor_name],
  s18.[Status],
  s18.[Model],
  s18.[Concurrency],
  s18.[Scrollable],
  s18.[open_status],
  s18.[cursor_rows],
  s18.[fetch_status],
  s18.[column_count],
  s18.[row_count],
  s18.[last_operation]
FROM
  [sys].[syscursors] s18
```

Columns and interpretation

- `cursor_handle` (int): Internal cursor handle.
- `cursor_name` (string?): Name of the cursor if assigned.
- `Status` (int): Status flags describing cursor state.
- `Model` (byte): Cursor model (STATIC/KEYSET/FAST_FORWARD/OTHER).
- `Concurrency` (byte): Concurrency model (READ_ONLY/SCROLL/LOCKING specifics).
- `Scrollable` (byte): Whether cursor supports scrolling.
- `open_status` (byte): Whether the cursor is open.
- `cursor_rows` (decimal?): Estimated or actual rows in cursor.
- `fetch_status` (short): Last fetch status code.
- `column_count` (short): Number of columns in result set.
- `row_count` (decimal?): Number of rows returned so far.
- `last_operation` (byte): Last operation performed (fetch/scroll/open/etc.).

How to interpret

- Use this view to diagnose cursor behavior and resource usage. `Model` and `Concurrency` codes need to be mapped to known cursor semantics.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscursorsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscursorsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Cursor:{r.CursorHandle} Name:{r.CursorName} Open:{r.OpenStatus} Rows:{r.CursorRows}");
```

See also:

- sys.syscursors (legacy)
