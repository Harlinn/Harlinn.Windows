# ServerEventSessionsReader

Overview

`ServerEventSessionsReader` wraps `sys.server_event_sessions` and exposes configuration details for Extended Events server event sessions.

Reader SQL

```
SELECT
  ses.[event_session_id],
  ses.[Name],
  ses.[event_retention_mode],
  ses.[event_retention_mode_desc],
  ses.[max_dispatch_latency],
  ses.[max_memory],
  ses.[max_event_size],
  ses.[memory_partition_mode],
  ses.[memory_partition_mode_desc],
  ses.[track_causality],
  ses.[startup_state],
  ses.[has_long_running_target]
FROM
  [sys].[server_event_sessions] ses
```

Columns and interpretation

- `event_session_id` (int): Identifier of the event session.
- `Name` (string?): Session name.
- `event_retention_mode`, `event_retention_mode_desc` (string?): Retention mode and description (how events are retained in session targets).
- `max_dispatch_latency` (int?): Maximum dispatch latency in milliseconds.
- `max_memory` (int?): Maximum memory allocated to the session.
- `max_event_size` (int?): Max allowed single event size.
- `memory_partition_mode`, `memory_partition_mode_desc` (string?): Memory partitioning settings and description.
- `track_causality` (bool?): Whether causality tracking is enabled.
- `startup_state` (bool?): Whether session starts automatically on server startup.
- `has_long_running_target` (bool?): Whether the session has a long-running target configured.

How to interpret

- Use these settings to understand resource limits and behavior for an Extended Events session.
- `max_dispatch_latency` vs `max_memory` helps tune performance vs resource usage.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerEventSessionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerEventSessionsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Session:{r.Name} TrackCausality:{r.TrackCausality} Startup:{r.StartupState}");
```

See also:

- [sys.server_event_sessions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-event-sessions)

