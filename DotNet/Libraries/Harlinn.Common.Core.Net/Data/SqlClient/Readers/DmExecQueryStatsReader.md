# DmExecQueryStatsReader — reference

Overview

`DmExecQueryStatsReader` wraps `sys.dm_exec_query_stats` and provides aggregated performance statistics for cached query plans, including CPU, IO, elapsed time, row counts, DOP and memory grants metrics aggregated across executions.

Reader SQL

```
SELECT
  deqs.[sql_handle],
  deqs.[statement_start_offset],
  deqs.[statement_end_offset],
  deqs.[plan_generation_num],
  deqs.[plan_handle],
  deqs.[creation_time],
  deqs.[last_execution_time],
  deqs.[execution_count],
  deqs.[total_worker_time],
  deqs.[last_worker_time],
  deqs.[min_worker_time],
  deqs.[max_worker_time],
  deqs.[total_physical_reads],
  deqs.[last_physical_reads],
  deqs.[min_physical_reads],
  deqs.[max_physical_reads],
  deqs.[total_logical_writes],
  deqs.[last_logical_writes],
  deqs.[min_logical_writes],
  deqs.[max_logical_writes],
  deqs.[total_logical_reads],
  deqs.[last_logical_reads],
  deqs.[min_logical_reads],
  deqs.[max_logical_reads],
  deqs.[total_clr_time],
  deqs.[last_clr_time],
  deqs.[min_clr_time],
  deqs.[max_clr_time],
  deqs.[total_elapsed_time],
  deqs.[last_elapsed_time],
  deqs.[min_elapsed_time],
  deqs.[max_elapsed_time],
  deqs.[query_hash],
  deqs.[query_plan_hash],
  deqs.[total_rows],
  deqs.[last_rows],
  deqs.[min_rows],
  deqs.[max_rows],
  deqs.[statement_sql_handle],
  deqs.[statement_context_id],
  deqs.[total_dop],
  deqs.[last_dop],
  deqs.[min_dop],
  deqs.[max_dop],
  deqs.[total_grant_kb],
  deqs.[last_grant_kb],
  deqs.[min_grant_kb],
  deqs.[max_grant_kb],
  deqs.[total_used_grant_kb],
  deqs.[last_used_grant_kb],
  deqs.[min_used_grant_kb],
  deqs.[max_used_grant_kb],
  deqs.[total_ideal_grant_kb],
  deqs.[last_ideal_grant_kb],
  deqs.[min_ideal_grant_kb],
  deqs.[max_ideal_grant_kb],
  deqs.[total_reserved_threads],
  deqs.[last_reserved_threads],
  deqs.[min_reserved_threads],
  deqs.[max_reserved_threads],
  deqs.[total_used_threads],
  deqs.[last_used_threads],
  deqs.[min_used_threads],
  deqs.[max_used_threads],
  deqs.[total_columnstore_segment_reads],
  deqs.[last_columnstore_segment_reads],
  deqs.[min_columnstore_segment_reads],
  deqs.[max_columnstore_segment_reads],
  deqs.[total_columnstore_segment_skips],
  deqs.[last_columnstore_segment_skips],
  deqs.[min_columnstore_segment_skips],
  deqs.[max_columnstore_segment_skips],
  deqs.[total_spills],
  deqs.[last_spills],
  deqs.[min_spills],
  deqs.[max_spills],
  deqs.[total_num_physical_reads],
  deqs.[last_num_physical_reads],
  deqs.[min_num_physical_reads],
  deqs.[max_num_physical_reads],
  deqs.[total_page_server_reads],
  deqs.[last_page_server_reads],
  deqs.[min_page_server_reads],
  deqs.[max_page_server_reads],
  deqs.[total_num_page_server_reads],
  deqs.[last_num_page_server_reads],
  deqs.[min_num_page_server_reads],
  deqs.[max_num_page_server_reads]
FROM
  [sys].[dm_exec_query_stats] deqs
```

Columns and interpretation

- `sql_handle`, `plan_handle`, `statement_sql_handle` ? handles for retrieving SQL text and execution plans using other DMVs.
- Offsets (`statement_start_offset`, `statement_end_offset`) identify the statement within a batch.
- `plan_generation_num` ? generation number indicating recompiled plan versions.
- `creation_time`, `last_execution_time` ? timestamps for plan creation and last execution.
- Execution counters: `execution_count`, `total_worker_time`, `last_worker_time`, `min/max_worker_time` (CPU); `total_elapsed_time` and last/min/max elapsed (wall-clock).
- IO counters: `total_physical_reads`, `total_logical_reads`, `total_logical_writes`, plus last/min/max variants.
- CLR, rows, DOP, memory grants, thread counts and columnstore metrics are exposed as aggregated totals and last/min/max variants.
- `query_hash` / `query_plan_hash` ? binary hashes for grouping queries and plans.

How to interpret

- Derive averages by dividing total counters by `execution_count`.
- Use `query_hash` to group similar queries; use `plan_generation_num` to detect plan churn.
- Memory grant metrics (`total_grant_kb`, `total_used_grant_kb`, `total_ideal_grant_kb`) reveal memory usage and inefficiencies; compare granted vs used.
- Spills indicate memory pressure; high `total_spills` suggests tuning memory grants or query rewrites.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecQueryStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"QueryHash:{(s.QueryHash!=null?BitConverter.ToString(s.QueryHash):"(null)")} ExecCount:{s.ExecutionCount} TotalCPU:{s.TotalWorkerTime} TotalElapsed:{s.TotalElapsedTime}");
    Console.WriteLine($" AvgCPU(ms):{(s.ExecutionCount>0? (s.TotalWorkerTime/s.ExecutionCount):0)} AvgElapsed(ms):{(s.ExecutionCount>0?(s.TotalElapsedTime/s.ExecutionCount):0)}");
}
```

See also:

- [sys.dm_exec_query_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-stats)
