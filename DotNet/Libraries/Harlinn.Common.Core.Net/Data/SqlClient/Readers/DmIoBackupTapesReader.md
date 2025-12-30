# DmIoBackupTapesReader — reference

Overview

`DmIoBackupTapesReader` wraps `sys.dm_io_backup_tapes` and returns information about backup tape devices (physical and logical names), mount requests, media set information and related status fields.

Reader SQL

```
SELECT
  dibt.[physical_device_name],
  dibt.[logical_device_name],
  dibt.[Status],
  dibt.[status_desc],
  dibt.[mount_request_time],
  dibt.[mount_expiration_time],
  dibt.[database_name],
  dibt.[Spid],
  dibt.[Command],
  dibt.[command_desc],
  dibt.[media_family_id],
  dibt.[media_set_name],
  dibt.[media_set_guid],
  dibt.[media_sequence_number],
  dibt.[tape_operation],
  dibt.[tape_operation_desc],
  dibt.[mount_request_type],
  dibt.[mount_request_type_desc]
FROM
  [sys].[dm_io_backup_tapes] dibt
```

Columns and interpretation

- `physical_device_name` ? `PhysicalDeviceName` (string)
  - The OS-level device path for the tape device.

- `logical_device_name` ? `LogicalDeviceName` (string?)
  - Logical device name used by SQL Server for the tape, may be null.

- `Status` / `status_desc` ? `Status` (int), `StatusDesc` (string)
  - Numeric status and textual description for the tape/mount state.

- `mount_request_time` / `mount_expiration_time` ? DateTime?
  - Time when mount was requested and when the mount request will expire.

- `database_name` ? database associated with the mount request.

- `Spid` ? server process id that requested the mount.

- `Command` / `CommandDesc` ? command id and description that initiated the mount.

- `media_family_id`, `media_set_name`, `media_set_guid`, `media_sequence_number` ? media set identifiers and metadata.

- `tape_operation` / `tape_operation_desc` ? operation code & description (mount/unmount/read/write etc.).

- `mount_request_type` / `mount_request_type_desc` ? type of mount request (user/automated/etc.).

How to interpret

- Use these fields to monitor tape mount requests, their status, which database initiated them, and related media set info for backup/restore operations.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmIoBackupTapesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmIoBackupTapesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Physical:{r.PhysicalDeviceName} Logical:{r.LogicalDeviceName} Status:{r.StatusDesc} DB:{r.DatabaseName} SPID:{r.Spid}");
}
```

See also:

- [sys.dm_io_backup_tapes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-io-backup-tapes)
