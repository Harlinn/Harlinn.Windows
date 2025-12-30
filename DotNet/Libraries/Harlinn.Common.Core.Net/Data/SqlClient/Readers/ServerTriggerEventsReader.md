# ServerTriggerEventsReader

Overview

`ServerTriggerEventsReader` wraps `sys.server_trigger_events` and exposes server-level trigger event definitions.

Reader SQL

```
SELECT
  ste.[object_id],
  ste.[Type],
  ste.[type_desc],
  ste.[is_trigger_event],
  ste.[is_first],
  ste.[is_last],
  ste.[event_group_type],
  ste.[event_group_type_desc]
FROM
  [sys].[server_trigger_events] ste
```

Columns and interpretation

- `object_id` (int): Object id for the event definition.
- `Type` (int): Numeric event type code.
- `type_desc` (string): Human-readable description of the event type.
- `is_trigger_event` (bool?): Whether this event is associated with triggers.
- `is_first`, `is_last` (bool?): Flags indicating event ordering semantics.
- `event_group_type` (int?): Grouping code for the event.
- `event_group_type_desc` (string?): Description for the event group type.

How to interpret

- Use these rows to understand server-level events that can fire triggers. The `is_first` and `is_last` flags are used for events where ordering matters.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerTriggerEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerTriggerEventsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"EventId:{r.ObjectId} Type:{r.TypeDesc} Trigger:{r.IsTriggerEvent}");
```

See also:

- [sys.server_trigger_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-trigger-events)
