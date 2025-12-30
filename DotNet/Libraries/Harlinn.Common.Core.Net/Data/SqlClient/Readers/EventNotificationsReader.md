# EventNotificationsReader — reference

Overview

`EventNotificationsReader` wraps `sys.event_notifications` and returns configuration for server- or database-scoped event notifications that post messages to Service Broker services when events occur.

Reader SQL

```
SELECT
  en.[Name],
  en.[object_id],
  en.[parent_class],
  en.[parent_class_desc],
  en.[parent_id],
  en.[create_date],
  en.[modify_date],
  en.[service_name],
  en.[broker_instance],
  en.[creator_sid],
  en.[principal_id]
FROM
  [sys].[event_notifications] en
```

Columns and interpretation

- `Name` — event notification name.
- `object_id` — object id of the notification object.
- `parent_class` / `parent_class_desc` — scope of the notification (DATABASE, SERVER) and textual description.
- `parent_id` — id of the parent object the notification is bound to (database id, server scope may be zero).
- `create_date` / `modify_date` — timestamps for creation and modification.
- `service_name` — Service Broker service name that receives the event messages.
- `broker_instance` — broker instance identifier for the target service (nullable string).
- `creator_sid` — security identifier of the creator (nullable binary).
- `principal_id` — owning principal id (nullable).

How to interpret

- Use `service_name` and `broker_instance` to route messages produced by the notification. `parent_class` indicates whether the notification is server- or database-scoped.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EventNotificationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EventNotificationsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Notification:{r.Name} Scope:{r.ParentClassDesc} Service:{r.ServiceName} Created:{r.CreateDate}");
}
```

See also:

- [sys.event_notifications](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-event-notifications)
