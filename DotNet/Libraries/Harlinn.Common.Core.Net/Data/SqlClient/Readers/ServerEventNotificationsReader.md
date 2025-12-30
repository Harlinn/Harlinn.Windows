# ServerEventNotificationsReader

Overview

`ServerEventNotificationsReader` wraps `sys.server_event_notifications` and exposes Service Broker event notifications defined at server scope.

Reader SQL

```
SELECT
  sen.[Name],
  sen.[object_id],
  sen.[parent_class],
  sen.[parent_class_desc],
  sen.[parent_id],
  sen.[create_date],
  sen.[modify_date],
  sen.[service_name],
  sen.[broker_instance],
  sen.[creator_sid],
  sen.[principal_id]
FROM
  [sys].[server_event_notifications] sen
```

Columns and interpretation

- `Name` (string): Name of the event notification.
- `object_id` (int): Object id of the notification object.
- `parent_class` (byte): Parent class code for the event target (server, database, etc.).
- `parent_class_desc` (string?): Description of the parent class.
- `parent_id` (int): Parent object's id.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `service_name` (string?): Service Broker service used to deliver events.
- `broker_instance` (string?): Broker instance name.
- `creator_sid` (byte[]?): SID of the creator principal.
- `principal_id` (int?): Owning principal id.

How to interpret

- Server event notifications send DDL or other server-level events to Service Broker services. Use `service_name` and `broker_instance` to locate target address.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventNotificationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventNotificationsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Notification:{r.Name} Service:{r.ServiceName} Parent:{r.ParentClassDesc}");
```

See also:

- [sys.server_event_notifications](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-notifications)

