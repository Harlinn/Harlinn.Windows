# DmResourceGovernorResourcePoolAffinityReader — reference

Overview

`DmResourceGovernorResourcePoolAffinityReader` wraps `sys.dm_resource_governor_resource_pool_affinity` and exposes CPU affinity mapping for internal resource pools.

Reader SQL

```
SELECT
  drgrpa.[pool_id],
  drgrpa.[processor_group],
  drgrpa.[scheduler_mask]
FROM
  [sys].[dm_resource_governor_resource_pool_affinity] drgrpa
```

Columns and interpretation

- `pool_id` — identifier of the resource pool.
- `processor_group` — processor group number for CPU affinity.
- `scheduler_mask` — bitmask identifying schedulers/CPUs assigned to the pool.

How to interpret

- Inspect `scheduler_mask` and `processor_group` to understand CPU assignment for resource pools and verify intended isolation.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorResourcePoolAffinityReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorResourcePoolAffinityReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Pool:{r.PoolId} Group:{r.ProcessorGroup} Mask:0x{r.SchedulerMask:X}");
}
```

See also:

- [sys.dm_resource_governor_resource_pool_affinity](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-resource-pool-affinity)
