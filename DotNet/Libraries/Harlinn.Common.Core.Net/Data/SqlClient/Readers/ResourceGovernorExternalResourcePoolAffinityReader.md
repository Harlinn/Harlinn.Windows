# ResourceGovernorExternalResourcePoolAffinityReader

Overview

`ResourceGovernorExternalResourcePoolAffinityReader` wraps `sys.resource_governor_external_resource_pool_affinity` and exposes CPU affinity settings for external resource pools.

Reader SQL

```
SELECT
  rgerpa.[external_pool_id],
  rgerpa.[processor_group],
  rgerpa.[cpu_mask]
FROM
  [sys].[resource_governor_external_resource_pool_affinity] rgerpa
```

Columns and interpretation

- `external_pool_id` (int): Identifier of the external resource pool.
- `processor_group` (short): Processor group number this affinity applies to.
- `cpu_mask` (long): Bitmask representing CPUs within the group assigned to the pool.

How to interpret

- `cpu_mask` is a bitmask where each bit corresponds to a logical CPU in the processor group. Combine with `processor_group` to determine exact CPUs.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorExternalResourcePoolAffinityReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorExternalResourcePoolAffinityReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Pool:{r.ExternalPoolId} Group:{r.ProcessorGroup} Mask:{r.CpuMask}");
```

See also:

- [sys.resource_governor_external_resource_pool_affinity](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-external-resource-pool-affinity)

