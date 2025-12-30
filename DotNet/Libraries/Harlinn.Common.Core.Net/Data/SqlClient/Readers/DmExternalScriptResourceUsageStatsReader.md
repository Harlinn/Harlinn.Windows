# DmExternalScriptResourceUsageStatsReader — reference

Overview

`DmExternalScriptResourceUsageStatsReader` wraps `sys.dm_external_script_resource_usage_stats` and returns per-package resource usage statistics such as memory and CPU usage for external script runtimes.

Reader SQL

```
SELECT
  desrus.[package_name],
  desrus.[memory_usage],
  desrus.[cpu_usage]
FROM
  [sys].[dm_external_script_resource_usage_stats] desrus
```

Columns and interpretation

- `package_name` ? `PackageName` (string)
  - Name of the external script package or runtime host.

- `memory_usage` ? `MemoryUsage` (long)
  - Memory usage reported for the package (units typically bytes; check DMV docs).

- `cpu_usage` ? `CpuUsage` (long)
  - CPU usage reported for the package (units typically milliseconds or percent-counter; check DMV docs).

How to interpret

- Use these metrics to identify packages consuming excessive memory or CPU.
- Combine with `sys.dm_external_script_execution_stats` for execution counts and failure rates.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExternalScriptResourceUsageStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExternalScriptResourceUsageStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Package:{s.PackageName} Memory:{s.MemoryUsage} CPU:{s.CpuUsage}");
}
```

See also:

- [sys.dm_external_script_resource_usage_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-external-script-resource-usage-stats)
