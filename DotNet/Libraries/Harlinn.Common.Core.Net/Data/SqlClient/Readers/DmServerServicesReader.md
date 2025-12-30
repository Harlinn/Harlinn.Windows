# DmServerServicesReader — reference

Overview

`DmServerServicesReader` wraps `sys.dm_server_services` and returns information about OS services related to SQL Server installation including startup type, status, account and executable path.

Reader SQL

```
SELECT
  dss.[Servicename],
  dss.[startup_type],
  dss.[startup_type_desc],
  dss.[Status],
  dss.[status_desc],
  dss.[process_id],
  dss.[last_startup_time],
  dss.[service_account],
  dss.[Filename],
  dss.[is_clustered],
  dss.[cluster_nodename],
  dss.[instant_file_initialization_enabled]
FROM
  [sys].[dm_server_services] dss
```

Columns and interpretation

- `Servicename` — service display name.
- `startup_type` / `startup_type_desc` — numeric and textual startup type (e.g., automatic, manual).
- `Status` / `status_desc` — numeric and textual service status.
- `process_id` — PID of the running service process (if applicable).
- `last_startup_time` — timestamp when the service last started.
- `service_account` — account under which the service runs.
- `Filename` — path to the service executable.
- `is_clustered` — textual indicator if service is part of a cluster.
- `cluster_nodename` — name of cluster node hosting the service (nullable).
- `instant_file_initialization_enabled` — textual indicator whether instant file initialization is enabled.

How to interpret

- Useful for verifying SQL Server services are running, under expected accounts, and for checking clustering or file initialization settings.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmServerServicesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmServerServicesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Service:{r.Servicename} Status:{r.StatusDesc} PID:{r.ProcessId} Account:{r.ServiceAccount} Path:{r.Filename}");
}
```

See also:

- [sys.dm_server_services](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-server-services)
