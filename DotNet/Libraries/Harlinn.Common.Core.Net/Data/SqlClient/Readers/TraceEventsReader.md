# TraceEventsReader

Overview

`TraceEventsReader` wraps `sys.trace_events` and lists available trace events, their categories, and names.

Reader SQL

```
SELECT
  te.[trace_event_id],
  te.[category_id],
  te.[Name]
FROM
  [sys].[trace_events] te
```

Columns and interpretation

- `trace_event_id` (smallint): Numeric identifier for the trace event. Use this when specifying events to capture in a trace.
- `category_id` (smallint): Identifier of the category (see `sys.trace_categories`) to which the event belongs.
- `Name` (nvarchar): Human readable event name.

How to interpret

- Use `trace_event_id` together with `sys.trace_event_bindings` to determine which columns are available for an event.
- Events are grouped by `category_id`; join with `sys.trace_categories` for category names.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TraceEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TraceEventsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"EventId:{r.TraceEventId} CategoryId:{r.CategoryId} Name:{r.Name}");
```

See also:

- [sys.trace_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trace-events)
