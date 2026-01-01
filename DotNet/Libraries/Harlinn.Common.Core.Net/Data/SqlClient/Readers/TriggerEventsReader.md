# TriggerEventsReader

Overview

`TriggerEventsReader` reads `sys.trigger_events`, which lists events that can be associated with triggers including various event groupings and flags.

Reader SQL

```
SELECT
  te0.[object_id],
  te0.[Type],
  te0.[type_desc],
  te0.[is_first],
  te0.[is_last],
  te0.[event_group_type],
  te0.[event_group_type_desc],
  te0.[is_trigger_event]
FROM
  [sys].[trigger_events] te0
```

Columns and interpretation

- `object_id` (int): The object id of the object the trigger event is associated with.
- `Type` (int): Numeric code for the trigger event type.
- `type_desc` (nvarchar): Human readable description of the type.
- `is_first` (bit?): Whether this event is considered the first in a sequence for multi-part events.
- `is_last` (bit?): Whether this event is the last in a multi-part event sequence.
- `event_group_type` (int?): Grouping code for the event.
- `event_group_type_desc` (nvarchar?): Description of the event group type.
- `is_trigger_event` (bit?): Whether the row corresponds to a triggerable event.

How to interpret

- Used to determine which events are available for triggers on objects. The `Type` and `event_group_type` fields are primarily internal codes; use descriptive fields where possible.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TriggerEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TriggerEventsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} Type:{r.TypeDesc} IsTrigger:{r.IsTriggerEvent} First:{r.IsFirst} Last:{r.IsLast}");
```

See also:

- [sys.trigger_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trigger-events)
