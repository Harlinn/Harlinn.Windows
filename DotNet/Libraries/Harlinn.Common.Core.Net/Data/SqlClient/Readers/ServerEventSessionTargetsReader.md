# ServerEventSessionTargetsReader

Overview

`ServerEventSessionTargetsReader` wraps `sys.server_event_session_targets` and exposes targets configured for Extended Events server event sessions.

Reader SQL

```
SELECT
  sest.[event_session_id],
  sest.[target_id],
  sest.[Name],
  sest.[Package],
  sest.[Module]
FROM
  [sys].[server_event_session_targets] sest
```

Columns and interpretation

- `event_session_id` (int): Identifier of the event session.
- `target_id` (int): Identifier of the target within the session.
- `Name` (string?): Target name.
- `Package` (string?): Package containing the target.
- `Module` (string?): Module name for the target.

How to interpret

- Targets are destinations where events are delivered (e.g., ring_buffer, event_file). Combine with target configuration to understand persisted data.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventSessionTargetsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventSessionTargetsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Session:{r.EventSessionId} Target:{r.Name} Package:{r.Package}");
```

See also:

- [sys.server_event_session_targets](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-session-targets)

