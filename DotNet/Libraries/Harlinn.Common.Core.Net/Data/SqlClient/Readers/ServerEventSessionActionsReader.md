# ServerEventSessionActionsReader

Overview

`ServerEventSessionActionsReader` wraps `sys.server_event_session_actions` and exposes configured actions for Extended Events server event sessions.

Reader SQL

```
SELECT
  sesa.[event_session_id],
  sesa.[event_id],
  sesa.[Name],
  sesa.[Package],
  sesa.[Module]
FROM
  [sys].[server_event_session_actions] sesa
```

Columns and interpretation

- `event_session_id` (int): Identifier of the event session.
- `event_id` (int): Identifier of the action within the session (internal id).
- `Name` (string?): Action name.
- `Package` (string?): Package containing the action.
- `Module` (string?): Module name for the action.

How to interpret

- Actions are used to add contextual data when events are captured (e.g., sql_text action captures T-SQL text).

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventSessionActionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventSessionActionsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Session:{r.EventSessionId} Action:{r.Name} Package:{r.Package}");
```

See also:

- [sys.server_event_session_actions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-session-actions)

