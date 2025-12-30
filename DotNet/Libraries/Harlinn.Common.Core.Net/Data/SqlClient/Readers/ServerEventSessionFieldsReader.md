# ServerEventSessionFieldsReader

Overview

`ServerEventSessionFieldsReader` wraps `sys.server_event_session_fields` and exposes custom field mappings for Extended Events server event sessions.

Reader SQL

```
SELECT
  sesf.[event_session_id],
  sesf.[object_id],
  sesf.[Name],
  sesf.[Value]
FROM
  [sys].[server_event_session_fields] sesf
```

Columns and interpretation

- `event_session_id` (int): Identifier of the event session.
- `object_id` (int): Object id of the event or object this field relates to.
- `Name` (string?): Field name.
- `Value` (object?): Field value; type depends on action/field configuration.

How to interpret

- Fields represent captured data elements attached to events. The `Value` column may be typed (int/string/binary) depending on the field.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventSessionFieldsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventSessionFieldsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Session:{r.EventSessionId} Field:{r.Name} Value:{r.Value}");
```

See also:

- [sys.server_event_session_fields](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-session-fields)

