# DmOsServerDiagnosticsLogConfigurationsReader — reference

Overview

`DmOsServerDiagnosticsLogConfigurationsReader` wraps `sys.dm_os_server_diagnostics_log_configurations` and exposes server diagnostics log configuration such as enabled state, path, and retention settings.

Reader SQL

```
SELECT
  dosdlc.[is_enabled],
  dosdlc.[Path],
  dosdlc.[max_size],
  dosdlc.[max_files]
FROM
  [sys].[dm_os_server_diagnostics_log_configurations] dosdlc
```

Columns and interpretation

- `is_enabled` — 1 if the server diagnostics logging is enabled; 0 or NULL if disabled.
- `Path` — filesystem path where the diagnostics logs are written.
- `max_size` — maximum size (in MB) configured for the log file. Probably/guesswork: value unit is MB according to typical configuration semantics.
- `max_files` — maximum number of rotated files to retain for diagnostics logs.

How to interpret

- Check `is_enabled` to see whether the diagnostics log is active.
- Use `Path` to locate physical log files for inspection.
- `max_size` and `max_files` indicate retention/rotation settings; large values allow more historical data but require more disk space.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsServerDiagnosticsLogConfigurationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsServerDiagnosticsLogConfigurationsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Enabled:{r.IsEnabled} Path:{r.Path} MaxSize:{r.MaxSize} MaxFiles:{r.MaxFiles}");
}
```

See also:

- [sys.dm_os_server_diagnostics_log_configurations](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-server-diagnostics-log-configurations)
