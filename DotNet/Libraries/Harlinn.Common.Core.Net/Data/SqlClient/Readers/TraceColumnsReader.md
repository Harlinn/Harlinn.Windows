# TraceColumnsReader

Overview

`TraceColumnsReader` wraps `sys.trace_columns` and exposes metadata for columns available in SQL Server traces. Each trace column represents a piece of data captured for trace events.

Reader SQL

```
SELECT
  tc.[trace_column_id],
  tc.[Name],
  tc.[type_name],
  tc.[max_size],
  tc.[is_filterable],
  tc.[is_repeatable],
  tc.[is_repeated_base]
FROM
  [sys].[trace_columns] tc
```

Columns and interpretation

- `trace_column_id` (smallint): Numeric identifier of the trace column. Use this id when selecting columns in server-side traces.
- `Name` (nvarchar): Human readable column name (e.g., TextData, LoginName).
- `type_name` (nvarchar): Data type name for the column values (e.g., nvarchar, int).
- `max_size` (int?): Maximum size in bytes of the column values; NULL if not applicable.
- `is_filterable` (bit): Whether the column can be used in a trace filter (WHERE clause) when defining traces.
- `is_repeatable` (bit): Whether the column value repeats across multiple events or captures (internal semantics).
- `is_repeated_base` (bit): Whether this column acts as a base for repeated values (internal semantics used for grouping repeated data).

How to interpret

- Use `trace_column_id` to configure which columns to collect in server traces or extended events mapping.
- `is_filterable` determines whether a column can be used for filtering at trace configuration time.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TraceColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TraceColumnsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"ColumnId:{r.TraceColumnId} Name:{r.Name} Type:{r.TypeName} MaxSize:{r.MaxSize} Filterable:{r.IsFilterable}");
```

See also:

- [sys.trace_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trace-columns)
