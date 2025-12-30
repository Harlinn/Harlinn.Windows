# DmIoPendingIoRequestsReader — reference

Overview

`DmIoPendingIoRequestsReader` wraps `sys.dm_io_pending_io_requests` and returns details about pending I/O requests at the OS layer including request addresses, types, wait time and associated handles.

Reader SQL

```
SELECT
  dipir.[io_completion_request_address],
  dipir.[io_type],
  dipir.[io_pending_ms_ticks],
  dipir.[io_pending],
  dipir.[io_completion_routine_address],
  dipir.[io_user_data_address],
  dipir.[scheduler_address],
  dipir.[io_handle],
  dipir.[io_offset],
  dipir.[io_handle_path]
FROM
  [sys].[dm_io_pending_io_requests] dipir
```

Columns and interpretation

- `io_completion_request_address` ? binary address identifying the completion request context.
- `io_type` ? textual IO type (Read/Write/Flush/etc.).
- `io_pending_ms_ticks` ? milliseconds ticks the IO has been pending.
- `io_pending` ? numeric pending count.
- `io_completion_routine_address` ? address of completion routine if present.
- `io_user_data_address` ? user data pointer/address for the IO operation.
- `scheduler_address` ? internal scheduler address tied to the request.
- `io_handle` ? handle token related to the IO operation.
- `io_offset` ? file offset for the IO.
- `io_handle_path` ? optional path for the target handle.

How to interpret

- Use `io_pending_ms_ticks` and `io_pending` to identify long-waiting I/O operations.
- `io_handle_path` helps map pending I/O to a file or resource path.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmIoPendingIoRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmIoPendingIoRequestsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Type:{r.IoType} PendingMs:{r.IoPendingMsTicks} Count:{r.IoPending} Offset:{r.IoOffset} Path:{r.IoHandlePath}");
}
```

See also:

- [sys.dm_io_pending_io_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-io-pending-io-requests)
