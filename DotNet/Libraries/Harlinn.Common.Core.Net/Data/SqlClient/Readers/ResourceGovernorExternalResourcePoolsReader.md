# ResourceGovernorExternalResourcePoolsReader

Overview

`ResourceGovernorExternalResourcePoolsReader` wraps `sys.resource_governor_external_resource_pools` and exposes configuration for external resource pools.

Reader SQL

```
SELECT
  rgerp.[external_pool_id],
  rgerp.[Name],
  rgerp.[max_cpu_percent],
  rgerp.[max_memory_percent],
  rgerp.[max_processes],
  rgerp.[Version]
FROM
  [sys].[resource_governor_external_resource_pools] rgerp
```

Columns and interpretation

- `external_pool_id` (int): Identifier of the external resource pool.
- `Name` (string): Name of the external pool.
- `max_cpu_percent` (int): Maximum CPU percent configured for the pool.
- `max_memory_percent` (int): Maximum memory percent configured for the pool.
- `max_processes` (int): Max number of processes allowed.
- `Version` (long): Version number indicating configuration change version.

How to interpret

- These rows describe limits placed on external resource pools that may be managed by a cluster or external resource manager.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorExternalResourcePoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorExternalResourcePoolsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Pool:{r.Name} CPU%:{r.MaxCpuPercent} Mem%:{r.MaxMemoryPercent}");
```

See also:

- [sys.resource_governor_external_resource_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-external-resource-pools)

