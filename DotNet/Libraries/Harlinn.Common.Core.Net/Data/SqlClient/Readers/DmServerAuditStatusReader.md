# DmServerAuditStatusReader — reference

Overview

`DmServerAuditStatusReader` wraps `sys.dm_server_audit_status` and returns status information for server audits including file paths and sizes.

Reader SQL

```
SELECT
  dsas.[audit_id],
  dsas.[Name],
  dsas.[Status],
  dsas.[status_desc],
  dsas.[status_time],
  dsas.[event_session_address],
  dsas.[audit_file_path],
  dsas.[audit_file_size]
FROM
  [sys].[dm_server_audit_status] dsas
```

Columns and interpretation

- `audit_id` — audit identifier.
- `Name` — audit name.
- `Status` — numeric status code for the audit.
- `status_desc` — textual description of audit status (e.g., STARTED, STOPPED).
- `status_time` — time status last changed.
- `event_session_address` — internal address for the underlying event session.
- `audit_file_path` — path to the audit file on disk (if file-based).
- `audit_file_size` — current file size in bytes (nullable).

How to interpret

- Use `status_desc` and `status_time` to determine whether audits are active and recent.
- `audit_file_path`/`audit_file_size` help locate audit output and assess disk usage.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmServerAuditStatusReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmServerAuditStatusReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Audit:{r.Name} Status:{r.StatusDesc} Time:{r.StatusTime} File:{r.AuditFilePath} Size:{r.AuditFileSize}");
}
```

See also:

- [sys.dm_server_audit_status](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-server-audit-status)
