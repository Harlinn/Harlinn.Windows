# DmOsMemoryBrokersReader — reference

Overview

`DmOsMemoryBrokersReader` wraps `sys.dm_os_memory_brokers` and exposes aggregated allocation metrics, targets and limits for memory brokers managing memory pools.

Reader SQL

```
SELECT
  domb.[pool_id],
  domb.[memory_broker_type],
  domb.[allocations_kb],
  domb.[allocations_kb_per_sec],
  domb.[predicted_allocations_kb],
  domb.[target_allocations_kb],
  domb.[future_allocations_kb],
  domb.[overall_limit_kb],
  domb.[last_notification]
FROM
  [sys].[dm_os_memory_brokers] domb
```

Columns and interpretation

- `pool_id` ? identifier for the memory pool.
- `memory_broker_type` ? type name of the broker managing allocations.
- `allocations_kb` ? current allocated kilobytes.
- `allocations_kb_per_sec` ? allocation rate in KB/s.
- `predicted_allocations_kb` ? predicted future allocations in KB.
- `target_allocations_kb` ? allocation target for the broker.
- `future_allocations_kb` ? expected future allocations in KB.
- `overall_limit_kb` ? overall memory limit for the broker in KB.
- `last_notification` ? textual info about last memory notification event.

How to interpret

- Use to monitor allocation rates and whether predicted allocations approach or exceed limits, indicating potential memory pressure.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryBrokersReader.Sql;
using var rdr = cmd.ExecuteReader();
var b = new DmOsMemoryBrokersReader(rdr, ownsReader:false);
while (b.Read())
{
    Console.WriteLine($"Pool:{b.PoolId} Type:{b.MemoryBrokerType} AllocKB:{b.AllocationsKb} RateKB/s:{b.AllocationsKbPerSec} LimitKB:{b.OverallLimitKb}");
}
```

See also:

- [sys.dm_os_memory_brokers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-brokers)
