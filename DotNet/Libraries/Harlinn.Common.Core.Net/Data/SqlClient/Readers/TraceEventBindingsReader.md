# TraceEventBindingsReader

Overview

`TraceEventBindingsReader` reads `sys.trace_event_bindings`, which maps trace events to the trace columns they expose.

Reader SQL

```
SELECT
  teb.[trace_event_id],
  teb.[trace_column_id]
FROM
  [sys].[trace_event_bindings] teb
```

Columns and interpretation

- `trace_event_id` (smallint): Identifier of a trace event. Join with `sys.trace_events` to get the event name.
- `trace_column_id` (smallint): Identifier of a trace column (from `sys.trace_columns`) that is associated with the event.

How to interpret

- For each trace event, the view lists which columns are available for that event. Use these mappings when constructing trace captures to know which data can be collected for a given event.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TraceEventBindingsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TraceEventBindingsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"EventId:{r.TraceEventId} ColumnId:{r.TraceColumnId}");
```

See also:

- [sys.trace_event_bindings](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trace-event-bindings)
