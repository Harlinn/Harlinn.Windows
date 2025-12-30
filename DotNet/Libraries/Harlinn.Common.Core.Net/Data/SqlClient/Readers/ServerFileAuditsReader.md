# ServerFileAuditsReader

Overview

`ServerFileAuditsReader` wraps `sys.server_file_audits` and exposes configuration details for file-based server audits.

Reader SQL

```
SELECT
  sfa.[audit_id],
  sfa.[Name],
  sfa.[audit_guid],
  sfa.[create_date],
  sfa.[modify_date],
  sfa.[principal_id],
  sfa.[Type],
  sfa.[type_desc],
  sfa.[on_failure],
  sfa.[on_failure_desc],
  sfa.[is_state_enabled],
  sfa.[queue_delay],
  sfa.[Predicate],
  sfa.[max_file_size],
  sfa.[max_rollover_files],
  sfa.[max_files],
  sfa.[reserve_disk_space],
  sfa.[log_file_path],
  sfa.[log_file_name],
  sfa.[retention_days]
FROM
  [sys].[server_file_audits] sfa
```

Columns and interpretation

- `audit_id` (int): Identifier of the file audit.
- `Name` (string): Audit name.
- `audit_guid` (Guid?): GUID for the audit.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `principal_id` (int?): Owning principal id.
- `Type`, `type_desc` (string): Target type and description.
- `on_failure`, `on_failure_desc` (byte?/string?): Behavior on failure.
- `is_state_enabled` (bool?): Whether audit is enabled.
- `queue_delay` (int?): Queue delay in ms.
- `Predicate` (string?): Audit filter predicate.
- `max_file_size` (long?): Maximum size of a single log file (bytes).
- `max_rollover_files` (int?): Number of rollover files to keep.
- `max_files` (int?): Maximum number of files.
- `reserve_disk_space` (bool?): Whether disk space is reserved.
- `log_file_path`, `log_file_name` (string?): Path and name pattern for log files.
- `retention_days` (int?): Days to retain files before deletion.

How to interpret

- These settings control file-based audit storage and how files roll over, are retained, and how failures are handled.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerFileAuditsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerFileAuditsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"FileAudit:{r.Name} Path:{r.LogFilePath} MaxSize:{r.MaxFileSize} RetentionDays:{r.RetentionDays}");
```

See also:

- [sys.server_file_audits](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-file-audits)

