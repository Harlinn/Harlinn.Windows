# TraceSubclassValuesReader

Overview

`TraceSubclassValuesReader` reads `sys.trace_subclass_values`, which provides mappings for subclass names and numeric values for trace columns on particular events.

Reader SQL

```
SELECT
  tsv.[trace_event_id],
  tsv.[trace_column_id],
  tsv.[subclass_name],
  tsv.[subclass_value]
FROM
  [sys].[trace_subclass_values] tsv
```

Columns and interpretation

- `trace_event_id` (smallint): Identifier for the trace event to which the subclass mapping applies.
- `trace_column_id` (smallint): Identifier for the trace column that has subclass values.
- `subclass_name` (nvarchar): Human readable name describing the subclass value.
- `subclass_value` (smallint?): Numeric value representing the subclass; used when trace column values are enumerations.

How to interpret

- Some trace columns encode enumerated values; this view maps the numeric codes to readable names. Use it to translate captured numeric codes into human-friendly descriptions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TraceSubclassValuesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TraceSubclassValuesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Event:{r.TraceEventId} Column:{r.TraceColumnId} Value:{r.SubclassValue} Name:{r.SubclassName}");
```

See also:

- [sys.trace_subclass_values](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trace-subclass-values)
