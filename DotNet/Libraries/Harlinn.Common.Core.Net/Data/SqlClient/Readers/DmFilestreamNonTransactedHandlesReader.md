# DmFilestreamNonTransactedHandlesReader — reference

Overview

`DmFilestreamNonTransactedHandlesReader` wraps `sys.dm_filestream_non_transacted_handles` and returns information about non-transacted FILESTREAM handles including file context, access rights, and client/login information.

Reader SQL

```
SELECT
  dfnth.[database_id],
  dfnth.[object_id],
  dfnth.[handle_id],
  dfnth.[file_object_type],
  dfnth.[file_object_type_desc],
  dfnth.[correlation_process_id],
  dfnth.[correlation_thread_id],
  dfnth.[file_context],
  dfnth.[State],
  dfnth.[state_desc],
  dfnth.[current_workitem_type],
  dfnth.[current_workitem_type_desc],
  dfnth.[fcb_id],
  dfnth.[item_id],
  dfnth.[is_directory],
  dfnth.[item_name],
  dfnth.[opened_file_name],
  dfnth.[database_directory_name],
  dfnth.[table_directory_name],
  dfnth.[remaining_file_name],
  dfnth.[open_time],
  dfnth.[Flags],
  dfnth.[login_id],
  dfnth.[login_name],
  dfnth.[login_sid],
  dfnth.[read_access],
  dfnth.[write_access],
  dfnth.[delete_access],
  dfnth.[share_read],
  dfnth.[share_write],
  dfnth.[share_delete],
  dfnth.[create_disposition]
FROM
  [sys].[dm_filestream_non_transacted_handles] dfnth
```

Columns and interpretation

- `database_id`, `object_id` ? database and object that owns the FILESTREAM data.
- `handle_id` ? numeric handle id.
- `file_object_type` / `file_object_type_desc` ? type of file object.
- `correlation_process_id` / `correlation_thread_id` ? client correlation ids.
- `file_context` ? binary file context token.
- `State` / `state_desc` ? state of the handle.
- `current_workitem_type` / `current_workitem_type_desc` ? description of current work item processing the handle.
- `fcb_id`, `item_id` ? internal file control block id and item id for the filestream object.
- `is_directory` ? whether handle points to a directory.
- `item_name`, `opened_file_name`, `database_directory_name`, `table_directory_name`, `remaining_file_name` ? path/name related fields.
- `open_time` ? time when handle was opened.
- `Flags` ? numeric flags for the handle.
- `login_id`, `login_name`, `login_sid` ? security context for the handle owner.
- Access booleans: `read_access`, `write_access`, `delete_access`, and share flags `share_read`, `share_write`, `share_delete`.
- `create_disposition` ? create disposition used when opening the handle.

How to interpret

- Useful to audit open non-transactional FILESTREAM handles and assess who/which processes are accessing FILESTREAM data and with what permissions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFilestreamNonTransactedHandlesReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmFilestreamNonTransactedHandlesReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"DB:{h.DatabaseId} Obj:{h.ObjectId} Handle:{h.HandleId} Name:{h.ItemName} Opened:{h.OpenedFileName} Login:{h.LoginName}");
}
```

See also:

- [sys.dm_filestream_non_transacted_handles](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-filestream-non-transacted-handles)
