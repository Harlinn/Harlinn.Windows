# DmResourceGovernorExternalResourcePoolAffinityReader — reference

Overview

`DmResourceGovernorExternalResourcePoolAffinityReader` wraps `sys.dm_resource_governor_external_resource_pool_affinity` and returns CPU affinity mapping for external resource pools.

Reader SQL

```
SELECT
  drgerpa.[external_pool_id],
  drgerpa.[processor_group],
  drgerpa.[cpu_mask]
FROM
  [sys].[dm_resource_governor_external_resource_pool_affinity] drgerpa
```

Columns and interpretation

- `external_pool_id` — identifier for the external resource pool.
- `processor_group` — processor group number for affinity mapping.
- `cpu_mask` — bitmask identifying CPUs assigned to the pool within the processor group.

How to interpret

- Use `cpu_mask` and `processor_group` to understand which CPUs a given external resource pool will use; helpful when diagnosing CPU contention and ensuring isolation.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorExternalResourcePoolAffinityReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorExternalResourcePoolAffinityReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Pool:{r.ExternalPoolId} Group:{r.ProcessorGroup} Mask:0x{r.CpuMask:X}");
}
```

See also:

- [sys.dm_resource_governor_external_resource_pool_affinity](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-external-resource-pool-affinity)
