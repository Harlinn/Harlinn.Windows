# ServerEventsReader

Overview

`ServerEventsReader` wraps `sys.server_events` and exposes definitions for server-level events available to notifications and auditing.

Reader SQL

```
SELECT
  se.[object_id],
  se.[Type],
  se.[type_desc],
  se.[is_trigger_event],
  se.[event_group_type],
  se.[event_group_type_desc]
FROM
  [sys].[server_events] se
```

Columns and interpretation

- `object_id` (int): Object id of the event definition.
- `Type` (int): Numeric event type code.
- `type_desc` (string): Text description of the event type.
- `is_trigger_event` (bool?): Whether event is a trigger event.
- `event_group_type` (int?): Grouping code for the event.
- `event_group_type_desc` (string?): Description of event group.

How to interpret

- Use `type`/`type_desc` to find events suitable for event notifications or extended event targets.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Event:{r.ObjectId} Type:{r.TypeDesc} Trigger:{r.IsTriggerEvent}");
```

See also:

- [sys.server_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-events)

