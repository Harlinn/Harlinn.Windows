# DmXeSessionEventActionsReader — reference

Overview

`DmXeSessionEventActionsReader` wraps `sys.dm_xe_session_event_actions` and returns the actions configured for events within active Extended Events sessions.

Reader SQL

```
SELECT
  dxsea.[event_session_address],
  dxsea.[action_name],
  dxsea.[action_package_guid],
  dxsea.[event_name],
  dxsea.[event_package_guid]
FROM
  [sys].[dm_xe_session_event_actions] dxsea
```

Columns and interpretation

- `event_session_address` — binary address identifying the event session instance.
- `action_name` — name of the action configured.
- `action_package_guid` — GUID of the package providing the action.
- `event_name` — name of the event the action is associated with.
- `event_package_guid` — GUID for the event's package.

How to interpret

- Use to enumerate actions attached to events for a session, helpful when inspecting session configuration and diagnosing missing actions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeSessionEventActionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeSessionEventActionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"SessionAddr:{BitConverter.ToString(r.EventSessionAddress)} Event:{r.EventName} Action:{r.ActionName} ActionPkg:{r.ActionPackageGuid}");
}
```

See also:

- [sys.dm_xe_session_event_actions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-session-event-actions)
