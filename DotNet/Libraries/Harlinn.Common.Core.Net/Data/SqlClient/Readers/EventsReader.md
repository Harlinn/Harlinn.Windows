# EventsReader — reference

Overview

`EventsReader` wraps `sys.events` and returns metadata about built-in and user-defined event types used by SQL Server objects such as event notifications and trace/event frameworks.

Reader SQL

```
SELECT
  e0.[object_id],
  e0.[Type],
  e0.[type_desc],
  e0.[is_trigger_event],
  e0.[event_group_type],
  e0.[event_group_type_desc]
FROM
  [sys].[events] e0
```

Columns and interpretation

- `object_id` — object id of the event definition.
- `Type` — numeric event type code.
- `type_desc` — textual description of the type.
- `is_trigger_event` — optional flag indicating whether the event is associated with triggers.
- `event_group_type` / `event_group_type_desc` — grouping of event types and textual description.

How to interpret

- Use to list and categorize available event types and determine whether an event relates to trigger execution.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EventsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"EventObj:{r.ObjectId} Type:{r.TypeDesc} Trigger:{r.IsTriggerEvent}");
}
```

See also:

- [sys.events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-events)
