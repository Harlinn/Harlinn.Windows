# QueryStoreWaitStatsReader

Overview

`QueryStoreWaitStatsReader` wraps `sys.query_store_wait_stats` and exposes aggregated wait statistics captured by Query Store for plan executions and runtime intervals.

Reader SQL

```
SELECT
  qsws.[wait_stats_id],
  qsws.[plan_id],
  qsws.[runtime_stats_interval_id],
  qsws.[wait_category],
  qsws.[wait_category_desc],
  qsws.[execution_type],
  qsws.[execution_type_desc],
  qsws.[total_query_wait_time_ms],
  qsws.[avg_query_wait_time_ms],
  qsws.[last_query_wait_time_ms],
  qsws.[min_query_wait_time_ms],
  qsws.[max_query_wait_time_ms],
  qsws.[stdev_query_wait_time_ms]
FROM
  [sys].[query_store_wait_stats] qsws
```

Columns and interpretation

- `wait_stats_id` (long): Unique identifier for the wait stats row.
- `plan_id` (long): Identifier of the plan (links to `sys.query_store_plan`).
- `runtime_stats_interval_id` (long): Identifier of the runtime interval for this aggregation.
- `wait_category` (short): Numeric code classifying the wait type group.
- `wait_category_desc` (string?): Text label for the wait category.
- `execution_type` (byte): Execution type code; see `execution_type_desc` for description.
- `execution_type_desc` (string?): Human readable execution type.
- `total_query_wait_time_ms` (long): Total wait time across all executions aggregated (milliseconds).
- `avg_query_wait_time_ms` (double?): Average wait time per execution (milliseconds).
- `last_query_wait_time_ms`, `min_query_wait_time_ms`, `max_query_wait_time_ms` (long): Last/min/max wait times observed (milliseconds).
- `stdev_query_wait_time_ms` (double?): Standard deviation of wait times.

How to interpret

- Use `wait_category` and `wait_category_desc` to group waits by type (CPU, IO, blocking, etc.).
- Large values in `total_query_wait_time_ms` indicate waits that contribute most to overall latency for a plan.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStoreWaitStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryStoreWaitStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Plan:{r.PlanId} WaitCategory:{r.WaitCategoryDesc} TotalWaitMs:{r.TotalQueryWaitTimeMs}");
}
```

See also:

- [sys.query_store_wait_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-wait-stats)

