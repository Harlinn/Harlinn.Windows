# DmXeSessionEventsReader — reference

Overview

`DmXeSessionEventsReader` wraps `sys.dm_xe_session_events` and returns events configured in active Extended Events sessions with optional predicates.

Reader SQL

```
SELECT
  dxse.[event_session_address],
  dxse.[event_name],
  dxse.[event_package_guid],
  dxse.[event_predicate]
FROM
  [sys].[dm_xe_session_events] dxse
```

Columns and interpretation

- `event_session_address` — binary address for the session instance.
- `event_name` — event name configured in the session.
- `event_package_guid` — GUID of the package providing the event.
- `event_predicate` — predicate expression (filter) applied to the event (nullable string).

How to interpret

- Use to list configured events for sessions and to inspect predicates that filter which events are captured.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeSessionEventsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeSessionEventsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Session:{BitConverter.ToString(r.EventSessionAddress)} Event:{r.EventName} Predicate:{r.EventPredicate}");
}
```

See also:

- [sys.dm_xe_session_events](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-session-events)
