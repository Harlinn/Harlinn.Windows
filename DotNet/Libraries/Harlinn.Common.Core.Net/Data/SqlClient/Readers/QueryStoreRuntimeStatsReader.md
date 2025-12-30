# QueryStoreRuntimeStatsReader

Overview

`QueryStoreRuntimeStatsReader` wraps `sys.query_store_runtime_stats` and exposes runtime metric aggregates captured by Query Store for individual plans and runtime intervals.

Reader SQL

```
SELECT
  qsrs.[runtime_stats_id],
  qsrs.[plan_id],
  qsrs.[runtime_stats_interval_id],
  qsrs.[execution_type],
  qsrs.[execution_type_desc],
  qsrs.[first_execution_time],
  qsrs.[last_execution_time],
  qsrs.[count_executions],
  qsrs.[avg_duration],
  qsrs.[last_duration],
  qsrs.[min_duration],
  qsrs.[max_duration],
  qsrs.[stdev_duration],
  qsrs.[avg_cpu_time],
  qsrs.[last_cpu_time],
  qsrs.[min_cpu_time],
  qsrs.[max_cpu_time],
  qsrs.[stdev_cpu_time],
  qsrs.[avg_logical_io_reads],
  qsrs.[last_logical_io_reads],
  qsrs.[min_logical_io_reads],
  qsrs.[max_logical_io_reads],
  qsrs.[stdev_logical_io_reads],
  qsrs.[avg_logical_io_writes],
  qsrs.[last_logical_io_writes],
  qsrs.[min_logical_io_writes],
  qsrs.[max_logical_io_writes],
  qsrs.[stdev_logical_io_writes],
  qsrs.[avg_physical_io_reads],
  qsrs.[last_physical_io_reads],
  qsrs.[min_physical_io_reads],
  qsrs.[max_physical_io_reads],
  qsrs.[stdev_physical_io_reads],
  qsrs.[avg_clr_time],
  qsrs.[last_clr_time],
  qsrs.[min_clr_time],
  qsrs.[max_clr_time],
  qsrs.[stdev_clr_time],
  qsrs.[avg_dop],
  qsrs.[last_dop],
  qsrs.[min_dop],
  qsrs.[max_dop],
  qsrs.[stdev_dop],
  qsrs.[avg_query_max_used_memory],
  qsrs.[last_query_max_used_memory],
  qsrs.[min_query_max_used_memory],
  qsrs.[max_query_max_used_memory],
  qsrs.[stdev_query_max_used_memory],
  qsrs.[avg_rowcount],
  qsrs.[last_rowcount],
  qsrs.[min_rowcount],
  qsrs.[max_rowcount],
  qsrs.[stdev_rowcount],
  qsrs.[avg_num_physical_io_reads],
  qsrs.[last_num_physical_io_reads],
  qsrs.[min_num_physical_io_reads],
  qsrs.[max_num_physical_io_reads],
  qsrs.[stdev_num_physical_io_reads],
  qsrs.[avg_log_bytes_used],
  qsrs.[last_log_bytes_used],
  qsrs.[min_log_bytes_used],
  qsrs.[max_log_bytes_used],
  qsrs.[stdev_log_bytes_used],
  qsrs.[avg_tempdb_space_used],
  qsrs.[last_tempdb_space_used],
  qsrs.[min_tempdb_space_used],
  qsrs.[max_tempdb_space_used],
  qsrs.[stdev_tempdb_space_used]
FROM
  [sys].[query_store_runtime_stats] qsrs
```

Columns and interpretation

- `runtime_stats_id` (long): Unique identifier for the runtime stats row.
- `plan_id` (long): Identifier of the plan (links to `sys.query_store_plan`).
- `runtime_stats_interval_id` (long): Identifier of the runtime interval (time bucket) for this aggregation.
- `execution_type` (byte): Numeric code for execution type (e.g., ad-hoc vs multi-statement). See `execution_type_desc` for text.
- `execution_type_desc` (string?): Human readable description of execution type.
- `first_execution_time` (DateTime): Timestamp of the first execution in the interval.
- `last_execution_time` (DateTime): Timestamp of the last execution in the interval.
- `count_executions` (long): Number of executions aggregated into this row.
- `avg_duration`, `last_duration`, `min_duration`, `max_duration` (double?/long): Aggregate duration statistics for executions.
  - Probably/guesswork: The units are implementation-dependent; treat as milliseconds unless Query Store documentation for your SQL Server version states otherwise.
- `stdev_duration` (double?): Sample standard deviation of durations.
- `avg_cpu_time`, `last_cpu_time`, `min_cpu_time`, `max_cpu_time`, `stdev_cpu_time`: CPU-time aggregates for executions (probably in milliseconds).
- `avg_logical_io_reads`, `last_logical_io_reads`, `min_logical_io_reads`, `max_logical_io_reads`, `stdev_logical_io_reads`: Logical I/O reads aggregates (counts of logical reads).
- `avg_logical_io_writes`, ...: Logical write aggregates.
- `avg_physical_io_reads`, ...: Physical I/O reads aggregates.
- `avg_clr_time`, ...: Aggregates for CLR execution time (if CLR used).
- `avg_dop`, `last_dop`, `min_dop`, `max_dop`, `stdev_dop`: Degree of parallelism aggregates (DOP values observed across executions).
- `avg_query_max_used_memory`, ...: Memory usage aggregates for queries (bytes or KB depending on server; prefix with "Probably/guesswork:" when unit is unknown).
- `avg_rowcount`, ...: Rowcount aggregates observed for executions.
- `avg_num_physical_io_reads`, ...: Alternative physical IO reads aggregates.
- `avg_log_bytes_used`, ...: Transaction log bytes used aggregates.
- `avg_tempdb_space_used`, ...: tempdb space used aggregates.

How to interpret

- Each row is an aggregation for a single plan within a specific runtime interval. Use `plan_id` to join to plan and `runtime_stats_interval_id` to join to the intervals view.
- Averages and standard deviations allow quick identification of resource-heavy plans or high-variance behaviour.
- Be cautious about units — Query Store column units can differ by SQL Server version. When precise units are required, consult the platform documentation for your version.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStoreRuntimeStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var reader = new QueryStoreRuntimeStatsReader(rdr, ownsReader: false);
while (reader.Read())
{
    Console.WriteLine($"Plan:{reader.PlanId} Count:{reader.CountExecutions} AvgDur:{reader.AvgDuration}");
}
```

See also:

- [sys.query_store_runtime_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-runtime-stats)

