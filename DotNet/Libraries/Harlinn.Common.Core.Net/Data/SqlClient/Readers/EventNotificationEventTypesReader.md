# EventNotificationEventTypesReader — reference

Overview

`EventNotificationEventTypesReader` wraps `sys.event_notification_event_types` and returns event type mappings used by event notifications.

Reader SQL

```
SELECT
  enet.[Type],
  enet.[type_name],
  enet.[parent_type]
FROM
  [sys].[event_notification_event_types] enet
```

Columns and interpretation

- `Type` — numeric code of the event type.
- `type_name` — textual name of the event type.
- `parent_type` — optional parent event type id (nullable) allowing hierarchical categorization of event types.

How to interpret

- Use to understand event categories supported by Event Notifications and map numeric codes to names.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EventNotificationEventTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EventNotificationEventTypesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Type:{r.Type} Name:{r.TypeName} Parent:{r.ParentType}");
}
```

See also:

- [sys.event_notification_event_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-event-notification-event-types)
