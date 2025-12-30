# DmFilestreamFileIoRequestsReader — reference

Overview

`DmFilestreamFileIoRequestsReader` wraps `sys.dm_filestream_file_io_requests` and exposes outstanding FILESTREAM I/O requests including request type/state and associated client identifiers.

Reader SQL

```
SELECT
  dffir.[request_context_address],
  dffir.[current_spid],
  dffir.[request_type],
  dffir.[request_state],
  dffir.[request_id],
  dffir.[irp_id],
  dffir.[handle_id],
  dffir.[client_thread_id],
  dffir.[client_process_id],
  dffir.[handle_context_address],
  dffir.[filestream_transaction_id]
FROM
  [sys].[dm_filestream_file_io_requests] dffir
```

Columns and interpretation

- `request_context_address` ? internal address identifying the request context (binary).
- `current_spid` ? server process id handling the request.
- `request_type` ? type of IO request (Read/Write/Flush/etc.).
- `request_state` ? current state of the IO request (Queued/Processing/Completed).
- `request_id` / `irp_id` ? identifiers for the request and its IRP.
- `handle_id` ? associated handle id.
- `client_thread_id` / `client_process_id` ? client identifiers captured for the request.
- `handle_context_address` ? reference to the handle context.
- `filestream_transaction_id` ? transaction id (binary) if associated with a FILESTREAM transaction.

How to interpret

- Use `request_type` and `request_state` to identify stalled or long-running FILESTREAM operations.
- Correlate `current_spid` and client ids with session and process monitoring to diagnose issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFilestreamFileIoRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmFilestreamFileIoRequestsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Req {BitConverter.ToString(r.RequestContextAddress)} SPID:{r.CurrentSpid} Type:{r.RequestType} State:{r.RequestState} Handle:{r.HandleId}");
}
```

See also:

- [sys.dm_filestream_file_io_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-filestream-file-io-requests)
