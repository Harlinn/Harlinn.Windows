# DmXeSessionTargetsReader — reference

Overview

`DmXeSessionTargetsReader` wraps `sys.dm_xe_session_targets` and returns information about targets configured for active Extended Events sessions, including execution metrics and target payload data.

Reader SQL

```
SELECT
  dxst.[event_session_address],
  dxst.[target_name],
  dxst.[target_package_guid],
  dxst.[execution_count],
  dxst.[execution_duration_ms],
  dxst.[target_data],
  dxst.[bytes_written]
FROM
  [sys].[dm_xe_session_targets] dxst
```

Columns and interpretation

- `event_session_address` — binary identifier for the session instance. Use to correlate with session-addressed DMVs such as `sys.dm_xe_sessions` and `sys.dm_xe_session_events`.
- `target_name` — name of the configured target (for example, `event_file`, `histogram`, `ring_buffer`).
- `target_package_guid` — GUID of the package implementing the target; useful for mapping to packages in `sys.dm_xe_packages`.
- `execution_count` — number of times the target has been executed (for example, number of buffer flushes or writes performed).
- `execution_duration_ms` — accumulated execution time for the target in milliseconds.
- `target_data` — textual or XML configuration/state data for the target (nullable). Content depends on target type (e.g., file path, ring buffer XML).
- `bytes_written` — number of bytes produced/written by the target (useful for monitoring volume produced by session targets).

How to interpret

- High `execution_count` and `bytes_written` indicate heavy event output activity. Use `target_data` to determine target destination and configuration.
- Correlate `event_session_address` with session-level metrics to find which session instance each target belongs to.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeSessionTargetsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeSessionTargetsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Session:{BitConverter.ToString(r.EventSessionAddress)} Target:{r.TargetName} ExecCount:{r.ExecutionCount} Bytes:{r.BytesWritten}");
    if (!string.IsNullOrEmpty(r.TargetData)) Console.WriteLine($"  Data: {r.TargetData}");
}
```

See also:

- [sys.dm_xe_session_targets](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-session-targets)
