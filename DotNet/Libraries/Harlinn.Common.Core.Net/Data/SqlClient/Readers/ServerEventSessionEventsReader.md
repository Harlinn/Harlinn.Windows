# ServerEventSessionEventsReader

Overview

`ServerEventSessionEventsReader` wraps `sys.server_event_session_events` and exposes configured events for Extended Events server event sessions.

Reader SQL

```
SELECT
  sese.[event_session_id],
  sese.[event_id],
  sese.[Name],
  sese.[Package],
  sese.[Module],
  sese.[Predicate],
  sese.[predicate_xml]
FROM
  [sys].[server_event_session_events] sese
```

Columns and interpretation

- `event_session_id` (int): Identifier of the event session.
- `event_id` (int): Internal event identifier.
- `Name` (string?): Event name.
- `Package` (string?): Package containing the event.
- `Module` (string?): Module name.
- `Predicate` (string?): Human-readable predicate/filter for the event.
- `predicate_xml` (string?): XML representation of the predicate.

How to interpret

- Use `predicate` to understand filtering applied to captured events. `predicate_xml` is helpful when reconstructing or programmatically analyzing filters.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventSessionEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventSessionEventsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Session:{r.EventSessionId} Event:{r.Name} Predicate:{r.Predicate}");
```

See also:

- [sys.server_event_session_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-session-events)

