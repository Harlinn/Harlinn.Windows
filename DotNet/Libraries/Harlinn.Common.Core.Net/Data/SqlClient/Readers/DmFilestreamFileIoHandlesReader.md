# DmFilestreamFileIoHandlesReader — reference

Overview

`DmFilestreamFileIoHandlesReader` wraps `sys.dm_filestream_file_io_handles` and returns details about file I/O handles opened against FILESTREAM data, including client identifiers and logical/physical paths.

Reader SQL

```
SELECT
  dffih.[handle_context_address],
  dffih.[creation_request_id],
  dffih.[creation_irp_id],
  dffih.[handle_id],
  dffih.[creation_client_thread_id],
  dffih.[creation_client_process_id],
  dffih.[filestream_transaction_id],
  dffih.[access_type],
  dffih.[logical_path],
  dffih.[physical_path]
FROM
  [sys].[dm_filestream_file_io_handles] dffih
```

Columns and interpretation

- `handle_context_address` ? `HandleContextAddress` (binary)
  - Internal address identifying handle context.

- `creation_request_id` ? `CreationRequestId` (int)
  - Request id that created the handle.

- `creation_irp_id` ? `CreationIrpId` (int)
  - IRP id at creation.

- `handle_id` ? `HandleId` (int)
  - Numeric handle identifier.

- `creation_client_thread_id` / `creation_client_process_id` ? binary client thread/process ids captured at creation.

- `filestream_transaction_id` ? binary id of the FILESTREAM transaction.

- `access_type` ? `AccessType` (string)
  - Access mode (Read, Write, Read/Write) used for the handle.

- `logical_path` / `physical_path` ? logical and physical paths for the file referenced by the handle.

How to interpret

- Use `handle_id` and `creation_request_id` to correlate open FILESTREAM handles to client activity and I/O requests.
- `access_type` shows permitted operations for the handle.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFilestreamFileIoHandlesReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmFilestreamFileIoHandlesReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"Handle {h.HandleId} Request:{h.CreationRequestId} Access:{h.AccessType} Logical:{h.LogicalPath} Physical:{h.PhysicalPath}");
}
```

See also:

- [sys.dm_filestream_file_io_handles](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-filestream-file-io-handles)
