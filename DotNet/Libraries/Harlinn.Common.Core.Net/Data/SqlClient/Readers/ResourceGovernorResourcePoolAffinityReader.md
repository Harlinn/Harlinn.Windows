# ResourceGovernorResourcePoolAffinityReader

Overview

`ResourceGovernorResourcePoolAffinityReader` wraps `sys.resource_governor_resource_pool_affinity` and exposes CPU affinity for internal resource pools.

Reader SQL

```
SELECT
  rgrpa.[pool_id],
  rgrpa.[processor_group],
  rgrpa.[scheduler_mask]
FROM
  [sys].[resource_governor_resource_pool_affinity] rgrpa
```

Columns and interpretation

- `pool_id` (int): Resource pool identifier.
- `processor_group` (short): Processor group number.
- `scheduler_mask` (long): Bitmask indicating which schedulers/CPUs in the group are assigned to this pool.

How to interpret

- Like external pool affinity, `scheduler_mask` uses bit positions to indicate CPU affinity. Combine with `processor_group` for full mapping.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorResourcePoolAffinityReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorResourcePoolAffinityReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Pool:{r.PoolId} Group:{r.ProcessorGroup} Mask:{r.SchedulerMask}");
```

See also:

- [sys.resource_governor_resource_pool_affinity](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-resource-pool-affinity)

