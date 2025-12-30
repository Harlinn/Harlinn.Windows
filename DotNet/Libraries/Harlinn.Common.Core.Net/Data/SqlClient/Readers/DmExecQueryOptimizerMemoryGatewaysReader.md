# DmExecQueryOptimizerMemoryGatewaysReader — reference

Overview

`DmExecQueryOptimizerMemoryGatewaysReader` wraps `sys.dm_exec_query_optimizer_memory_gateways` and reports configuration and runtime state of memory gateways used by the optimizer to manage memory granting and concurrency. Gateways are per-pool constructs that gate memory usage across consumers.

Reader SQL

```
SELECT
  deqomg.[pool_id],
  deqomg.[Name],
  deqomg.[max_count],
  deqomg.[active_count],
  deqomg.[waiter_count],
  deqomg.[threshold_factor],
  deqomg.[Threshold],
  deqomg.[is_active]
FROM
  [sys].[dm_exec_query_optimizer_memory_gateways] deqomg
```

Columns and interpretation

- `pool_id` ? pool identifier for which the gateway is configured.
- `Name` ? gateway name.
- `max_count` ? maximum number of concurrent grants or entries the gateway allows.
- `active_count` ? current number of active grants/consumers.
- `waiter_count` ? number of waiting requests queued for the gateway.
- `threshold_factor` ? scaling factor used to compute threshold values; implementation detail for gateway sizing.
- `Threshold` ? computed absolute threshold for memory or concurrency the gateway enforces.
- `is_active` ? whether the gateway is currently enforcing limits.

How to interpret

- High `waiter_count` with `active_count` close to `max_count` indicates contention for memory resources; consider increasing pool memory or resizing gateways.
- `Threshold` and `ThresholdFactor` explain how limits are calculated.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryOptimizerMemoryGatewaysReader.Sql;
using var rdr = cmd.ExecuteReader();
var g = new DmExecQueryOptimizerMemoryGatewaysReader(rdr, ownsReader:false);
while (g.Read())
{
    Console.WriteLine($"Pool {g.PoolId} Gateway {g.Name} Active:{g.ActiveCount}/{g.MaxCount} Waiters:{g.WaiterCount} Threshold:{g.Threshold}");
}
```

See also:

- [sys.dm_exec_query_optimizer_memory_gateways](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-optimizer-memory-gateways)
