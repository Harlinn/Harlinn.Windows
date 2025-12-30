# DmExecFunctionStatsReader — reference

Overview

`DmExecFunctionStatsReader` wraps `sys.dm_exec_function_stats` and reports runtime execution statistics for cached scalar functions and table-valued functions. It provides cumulative and last/min/max metrics for CPU, reads/writes, elapsed time, and related page/IO counters.

Reader SQL

```
SELECT
  defs.[database_id],
  defs.[object_id],
  defs.[Type],
  defs.[type_desc],
  defs.[sql_handle],
  defs.[plan_handle],
  defs.[cached_time],
  defs.[last_execution_time],
  defs.[execution_count],
  defs.[total_worker_time],
  defs.[last_worker_time],
  defs.[min_worker_time],
  defs.[max_worker_time],
  defs.[total_physical_reads],
  defs.[last_physical_reads],
  defs.[min_physical_reads],
  defs.[max_physical_reads],
  defs.[total_logical_writes],
  defs.[last_logical_writes],
  defs.[min_logical_writes],
  defs.[max_logical_writes],
  defs.[total_logical_reads],
  defs.[last_logical_reads],
  defs.[min_logical_reads],
  defs.[max_logical_reads],
  defs.[total_elapsed_time],
  defs.[last_elapsed_time],
  defs.[min_elapsed_time],
  defs.[max_elapsed_time],
  defs.[total_num_physical_reads],
  defs.[last_num_physical_reads],
  defs.[min_num_physical_reads],
  defs.[max_num_physical_reads],
  defs.[total_page_server_reads],
  defs.[last_page_server_reads],
  defs.[min_page_server_reads],
  defs.[max_page_server_reads],
  defs.[total_num_page_server_reads],
  defs.[last_num_page_server_reads],
  defs.[min_num_page_server_reads],
  defs.[max_num_page_server_reads]
FROM
  [sys].[dm_exec_function_stats] defs
```

Columns and interpretation

- `database_id`, `object_id` ? identify the function's owning database and object id.
- `Type` / `type_desc` ? function type and description.
- `sql_handle` / `plan_handle` ? handles that can be used with other DMVs to retrieve SQL text and execution plan.
- `cached_time` / `last_execution_time` ? timestamps when the plan was cached and last executed.
- `execution_count` ? number of times the function has been executed since the plan was cached.
- `total_worker_time`, `last_worker_time`, `min_worker_time`, `max_worker_time` ? CPU time counters (in microseconds or ms depending on documentation) aggregated and per-execution stats.
- `total_physical_reads`, `last_physical_reads`, `min_physical_reads`, `max_physical_reads` ? physical I/O read counters; high physical reads indicate physical IO usage.
- `total_logical_writes`, `total_logical_reads`, and their last/min/max variants ? logical IO counters.
- `total_elapsed_time`, `last_elapsed_time`, `min_elapsed_time`, `max_elapsed_time` ? wall-clock elapsed time counters.
- `total_num_physical_reads`, `total_page_server_reads`, and page server variants ? additional IO counters (may refer to page server reads in distributed/remote storage scenarios).

How to interpret

- Compare `total_*` with `execution_count` to compute average per-execution resource usage.
- Large `max_*` values may indicate occasional heavy executions; investigate last execution timestamp to correlate with events.
- Use `sql_handle` and `plan_handle` with `sys.dm_exec_query_plan` and `sys.dm_exec_sql_text` to inspect the plan and source SQL.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecFunctionStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecFunctionStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Func {s.ObjectId} DB:{s.DatabaseId} ExecCount:{s.ExecutionCount}");
    Console.WriteLine($" CPU total/last: {s.TotalWorkerTime}/{s.LastWorkerTime} Elapsed total/last: {s.TotalElapsedTime}/{s.LastElapsedTime}");
}
```

See also:

- [sys.dm_exec_function_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-function-stats)
