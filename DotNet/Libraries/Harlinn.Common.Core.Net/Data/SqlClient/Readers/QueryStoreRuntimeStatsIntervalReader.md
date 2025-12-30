# QueryStoreRuntimeStatsIntervalReader — reference

Overview

`QueryStoreRuntimeStatsIntervalReader` wraps `sys.query_store_runtime_stats_interval` and returns time intervals used by Query Store to aggregate runtime statistics.

Reader SQL

```
SELECT
  qsrsi.[runtime_stats_interval_id],
  qsrsi.[start_time],
  qsrsi.[end_time],
  qsrsi.[Comment]
FROM
  [sys].[query_store_runtime_stats_interval] qsrsi
```

Columns and interpretation

- `runtime_stats_interval_id` — id for the interval.
- `start_time` / `end_time` — time range for the interval.
- `Comment` — optional description or annotation for the interval.

How to interpret

- Query Store aggregates runtime statistics into intervals. Use these intervals to correlate performance metrics to wall-clock time ranges.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStoreRuntimeStatsIntervalReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryStoreRuntimeStatsIntervalReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"IntervalId:{r.RuntimeStatsIntervalId} {r.StartTime} - {r.EndTime} Comment:{r.Comment}");
}
```

See also:

- [sys.query_store_runtime_stats_interval](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-runtime-stats-interval)
