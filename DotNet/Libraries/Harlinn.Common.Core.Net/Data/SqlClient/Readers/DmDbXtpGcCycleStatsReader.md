# DmDbXtpGcCycleStatsReader — reference

Overview

`DmDbXtpGcCycleStatsReader` wraps `sys.dm_db_xtp_gc_cycle_stats` and exposes per-garbage-collection (GC) cycle statistics for In-Memory OLTP. This helps understand GC behavior, generation distribution and cycle timings.

Reader SQL

```
SELECT
  ddxgcs.[cycle_id],
  ddxgcs.[ticks_at_cycle_start],
  ddxgcs.[ticks_at_cycle_end],
  ddxgcs.[node_id],
  ddxgcs.[base_generation],
  ddxgcs.[xacts_copied_to_local],
  ddxgcs.[xacts_in_gen_0],
  ...
  ddxgcs.[xacts_in_gen_15]
FROM
  [sys].[dm_db_xtp_gc_cycle_stats] ddxgcs
```

Columns (how to interpret)

- `cycle_id` ? `CycleId` (long)
  - Unique identifier for the GC cycle. Use to order cycles.

- `ticks_at_cycle_start` / `ticks_at_cycle_end` ? start/end tick counters for the cycle; subtract to get cycle duration in ticks.

- `node_id` ? `NodeId` (int)
  - NUMA/node identifier where the cycle was recorded.

- `base_generation` ? `BaseGeneration` (long)
  - Generation baseline for this cycle.

- `xacts_copied_to_local` ? `XactsCopiedToLocal` (long)
  - Number of transactions copied to local structures during cycle.

- `xacts_in_gen_N` ? counts of transactions in each generation (0..15). Interpret as the distribution of transaction ages; higher-generation counts indicate older transactions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpGcCycleStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var g = new DmDbXtpGcCycleStatsReader(reader, ownsReader: false);
while (g.Read())
{
    Console.WriteLine($"Cycle {g.CycleId} Node {g.NodeId} BaseGen {g.BaseGeneration}");
    Console.WriteLine($" Duration ticks: {g.TicksAtCycleEnd - g.TicksAtCycleStart}");
    Console.WriteLine($" Transactions by generation: gen0={g.XactsInGen0} gen1={g.XactsInGen1} ... gen15={g.XactsInGen15}");
}
```

See also:

- [sys.dm_db_xtp_gc_cycle_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-gc-cycle-stats)
