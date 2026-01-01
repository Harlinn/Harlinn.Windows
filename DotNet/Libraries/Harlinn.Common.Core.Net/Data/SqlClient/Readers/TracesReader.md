# TracesReader

Overview

`TracesReader` reads `sys.traces`, which returns metadata about currently configured traces on the SQL Server instance (including default trace and any server-side traces).

Reader SQL

```
SELECT
  t.[Id],
  t.[Status],
  t.[Path],
  t.[max_size],
  t.[stop_time],
  t.[max_files],
  t.[is_rowset],
  t.[is_rollover],
  t.[is_shutdown],
  t.[is_default],
  t.[buffer_count],
  t.[buffer_size],
  t.[file_position],
  t.[reader_spid],
  t.[start_time],
  t.[last_event_time],
  t.[event_count],
  t.[dropped_event_count]
FROM
  [sys].[traces] t
```

Columns and interpretation

- `Id` (int): Trace id used to control the trace (e.g., stop, start, set event/column). Use as the primary identifier for trace operations.
- `Status` (int): Status code for the trace (running, stopped, etc.).
- `Path` (nvarchar): File path or destination for trace files.
- `max_size` (bigint?): Maximum file size for trace segments.
- `stop_time` (datetime?): Time at which the trace was stopped.
- `max_files` (int?): Maximum number of rollover files to keep.
- `is_rowset` (bit?): Whether the trace is exposing a rowset interface.
- `is_rollover` (bit?): Whether trace uses rollover to multiple files.
- `is_shutdown` (bit?): Whether trace is marked to stop on server shutdown.
- `is_default` (bit?): Whether this trace is the default trace.
- `buffer_count` (int?): Number of buffers allocated for trace.
- `buffer_size` (int?): Size of each buffer in KB.
- `file_position` (bigint?): Current file position for trace writes.
- `reader_spid` (int?): Server process id reading the trace.
- `start_time` (datetime?): Start time of the trace.
- `last_event_time` (datetime?): Last time an event was recorded.
- `event_count` (bigint?): Number of events captured.
- `dropped_event_count` (int?): Number of events dropped due to resource pressure.

How to interpret

- Use `Id` to manage server traces via stored procedures (sp_trace_setstatus, sp_trace_setevent, etc.).
- `is_default` indicates the server's default trace; its files are typically located in the SQL Server log directory.
- `dropped_event_count` can indicate if the trace is dropping events due to high volume or insufficient resources and may require adjusting buffer_size/count.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TracesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TracesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"TraceId:{r.Id} Path:{r.Path} Running:{r.Status} Events:{r.EventCount} Dropped:{r.DroppedEventCount}");
```

See also:

- [sys.traces](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-traces)
