# SyscursorcolumnsReader

Overview

`SyscursorcolumnsReader` wraps `sys.syscursorcolumns` and exposes metadata about columns returned by server-side cursors (legacy diagnostic view).

Reader SQL

```
SELECT
  s20.[cursor_handle],
  s20.[column_name],
  s20.[ordinal_position],
  s20.[column_characteristics_flags],
  s20.[column_size],
  s20.[data_type_sql],
  s20.[column_precision],
  s20.[column_scale],
  s20.[order_position],
  s20.[order_direction],
  s20.[hidden_column],
  s20.[Columnid],
  s20.[Objectid],
  s20.[Dbid],
  s20.[Dbname]
FROM
  [sys].[syscursorcolumns] s20
```

Columns and interpretation

- `cursor_handle` (int): Numeric handle identifying the cursor.
- `column_name` (string?): Column name returned by the cursor.
- `ordinal_position` (int): Position of the column in the cursor result set.
- `column_characteristics_flags` (int): Bit flags describing column attributes (nullable, identity, etc.).
- `column_size` (int): Size in bytes or chars for the column data.
- `data_type_sql` (int): Internal code for SQL data type.
- `column_precision`/`column_scale` (byte): Precision and scale for numeric types.
- `order_position`, `order_direction` (int/string?): Ordering information for the column if used in ORDER BY.
- `hidden_column` (short): Flag indicating if the column is hidden (e.g., shadow columns).
- `Columnid`, `Objectid`, `Dbid`, `Dbname` (int/string?): Identifiers to map the column back to its source object and database.

How to interpret

- Use to introspect server-side cursor result set layout. `column_characteristics_flags` requires decoding according to internal flag definitions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscursorcolumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscursorcolumnsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Cursor:{r.CursorHandle} Col:{r.ColumnName} Pos:{r.OrdinalPosition} Size:{r.ColumnSize} TypeCode:{r.DataTypeSql}");
```

See also:

- sys.syscursorcolumns (legacy)
