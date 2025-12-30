# ResourceGovernorResourcePoolsReader

Overview

`ResourceGovernorResourcePoolsReader` wraps `sys.resource_governor_resource_pools` and exposes configuration for internal resource pools.

Reader SQL

```
SELECT
  rgrp.[pool_id],
  rgrp.[Name],
  rgrp.[min_cpu_percent],
  rgrp.[max_cpu_percent],
  rgrp.[min_memory_percent],
  rgrp.[max_memory_percent],
  rgrp.[cap_cpu_percent],
  rgrp.[min_iops_per_volume],
  rgrp.[max_iops_per_volume]
FROM
  [sys].[resource_governor_resource_pools] rgrp
```

Columns and interpretation

- `pool_id` (int): Identifier of the resource pool.
- `Name` (string): Name of the resource pool.
- `min_cpu_percent`, `max_cpu_percent` (int): CPU percent floor and ceiling for the pool.
- `min_memory_percent`, `max_memory_percent` (int): Memory percentage bounds for the pool.
- `cap_cpu_percent` (int): Capped CPU percentage.
- `min_iops_per_volume`, `max_iops_per_volume` (int): IOPS per volume limits.

How to interpret

- These settings define how Resource Governor divides CPU, memory, and I/O among workload groups in the pool.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorResourcePoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorResourcePoolsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Pool:{r.Name} CPU:{r.MinCpuPercent}-{r.MaxCpuPercent} Mem:{r.MinMemoryPercent}-{r.MaxMemoryPercent}");
```

See also:

- [sys.resource_governor_resource_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-resource-pools)

