# DmOsClusterPropertiesReader — reference

Overview

`DmOsClusterPropertiesReader` wraps `sys.dm_os_cluster_properties` and provides cluster-level configuration properties that SQL Server uses when running in a Windows Server Failover Cluster.

Reader SQL

```
SELECT
  docp.[Verboselogging],
  docp.[Sqldumperdumpflags],
  docp.[Sqldumperdumppath],
  docp.[Sqldumperdumptimeout],
  docp.[Failureconditionlevel],
  docp.[Healthchecktimeout]
FROM
  [sys].[dm_os_cluster_properties] docp
```

Columns and interpretation

- `Verboselogging` ? `Verboselogging` (long?)
  - Numeric indicator whether verbose logging is enabled for cluster operations.

- `Sqldumperdumpflags` ? `Sqldumperdumpflags` (long?)
  - Flags used to control SQLDumper behavior for crash dumps.

- `Sqldumperdumppath` ? `Sqldumperdumppath` (string)
  - Path where SQLDumper output is written.

- `Sqldumperdumptimeout` ? `Sqldumperdumptimeout` (long?)
  - Timeout value for SQLDumper operations.

- `Failureconditionlevel` ? `Failureconditionlevel` (long?)
  - Threshold for what conditions constitute a failure for clustering (used by cluster health checks).

- `Healthchecktimeout` ? `Healthchecktimeout` (long?)
  - Timeout for cluster health checks.

How to interpret

- Use to inspect cluster-related configuration that can affect diagnostics, dump generation and automated failure detection.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsClusterPropertiesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsClusterPropertiesReader(rdr, ownsReader:false);
if (r.Read())
{
    Console.WriteLine($"DumpPath:{r.Sqldumperdumppath} DumpTimeout:{r.Sqldumperdumptimeout} FailureLevel:{r.Failureconditionlevel}");
}
```

See also:

- [sys.dm_os_cluster_properties](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-cluster-properties)
