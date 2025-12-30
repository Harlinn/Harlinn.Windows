# DmExecProcedureStatsReader — reference

Overview

`DmExecProcedureStatsReader` wraps `sys.dm_exec_procedure_stats` and reports runtime performance statistics for cached stored procedures and compiled plans. It provides aggregated and per-execution min/avg/max values for CPU, IO, elapsed time, spills, and page server reads.

Reader SQL

```
SELECT
  deps.[database_id],
  deps.[object_id],
  deps.[Type],
  deps.[type_desc],
  deps.[sql_handle],
  deps.[plan_handle],
  deps.[cached_time],
  deps.[last_execution_time],
  deps.[execution_count],
  deps.[total_worker_time],
  deps.[last_worker_time],
  deps.[min_worker_time],
  deps.[max_worker_time],
  deps.[total_physical_reads],
  deps.[last_physical_reads],
  deps.[min_physical_reads],
  deps.[max_physical_reads],
  deps.[total_logical_writes],
  deps.[last_logical_writes],
  deps.[min_logical_writes],
  deps.[max_logical_writes],
  deps.[total_logical_reads],
  deps.[last_logical_reads],
  deps.[min_logical_reads],
  deps.[max_logical_reads],
  deps.[total_elapsed_time],
  deps.[last_elapsed_time],
  deps.[min_elapsed_time],
  deps.[max_elapsed_time],
  deps.[total_spills],
  deps.[last_spills],
  deps.[min_spills],
  deps.[max_spills],
  deps.[total_num_physical_reads],
  deps.[last_num_physical_reads],
  deps.[min_num_physical_reads],
  deps.[max_num_physical_reads],
  deps.[total_page_server_reads],
  deps.[last_page_server_reads],
  deps.[min_page_server_reads],
  deps.[max_page_server_reads],
  deps.[total_num_page_server_reads],
  deps.[last_num_page_server_reads],
  deps.[min_num_page_server_reads],
  deps.[max_num_page_server_reads]
FROM
  [sys].[dm_exec_procedure_stats] deps
```

Columns and interpretation

- `database_id`, `object_id` ? identify the stored procedure.
- `Type` / `type_desc` ? object type.
- `sql_handle` / `plan_handle` ? handles to obtain SQL text or plan.
- `cached_time` / `last_execution_time` ? timings for caching and last execution.
- `execution_count` ? number of executions since cached.
- `total_worker_time`, `last_worker_time`, `min_worker_time`, `max_worker_time` ? CPU time counters.
- `total_physical_reads`, `total_logical_writes`, `total_logical_reads` and min/last/max variants ? IO counters.
- `total_elapsed_time` and min/last/max variants ? elapsed time counters.
- `total_spills` / `last_spills` / ... ? spill counts indicating memory spills to disk; spikes may indicate memory pressure.
- `total_num_physical_reads`, `total_page_server_reads`, etc. ? additional IO counters helpful in remote/page server scenarios.

Interpretation

- Compute average per-execution metrics by dividing `total_*` by `execution_count`.
- High `max_*` values indicate outlier executions; check `last_execution_time` to see if recent.
- Spills indicate queries that could not keep required data in memory and spilled to tempdb; investigate plan and memory grants.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecProcedureStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecProcedureStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Proc {s.ObjectId} DB:{s.DatabaseId} ExecCount:{s.ExecutionCount}");
    Console.WriteLine($" CPU total/last: {s.TotalWorkerTime}/{s.LastWorkerTime} Elapsed total/last: {s.TotalElapsedTime}/{s.LastElapsedTime}");
    Console.WriteLine($" Spills total/last: {s.TotalSpills}/{s.LastSpills}");
}
```

See also:

- [sys.dm_exec_procedure_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-procedure-stats)
