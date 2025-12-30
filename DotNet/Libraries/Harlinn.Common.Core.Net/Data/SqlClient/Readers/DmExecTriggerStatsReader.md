# DmExecTriggerStatsReader — reference

Overview

`DmExecTriggerStatsReader` wraps `sys.dm_exec_trigger_stats` and provides aggregated execution statistics for database triggers, including CPU, IO, elapsed time and spill metrics.

Reader SQL

```
SELECT
  dets.[database_id],
  dets.[object_id],
  dets.[Type],
  dets.[type_desc],
  dets.[sql_handle],
  dets.[plan_handle],
  dets.[cached_time],
  dets.[last_execution_time],
  dets.[execution_count],
  dets.[total_worker_time],
  dets.[last_worker_time],
  dets.[min_worker_time],
  dets.[max_worker_time],
  dets.[total_physical_reads],
  dets.[last_physical_reads],
  dets.[min_physical_reads],
  dets.[max_physical_reads],
  dets.[total_logical_writes],
  dets.[last_logical_writes],
  dets.[min_logical_writes],
  dets.[max_logical_writes],
  dets.[total_logical_reads],
  dets.[last_logical_reads],
  dets.[min_logical_reads],
  dets.[max_logical_reads],
  dets.[total_elapsed_time],
  dets.[last_elapsed_time],
  dets.[min_elapsed_time],
  dets.[max_elapsed_time],
  dets.[total_spills],
  dets.[last_spills],
  dets.[min_spills],
  dets.[max_spills],
  dets.[total_num_physical_reads],
  dets.[last_num_physical_reads],
  dets.[min_num_physical_reads],
  dets.[max_num_physical_reads],
  dets.[total_page_server_reads],
  dets.[last_page_server_reads],
  dets.[min_page_server_reads],
  dets.[max_page_server_reads],
  dets.[total_num_page_server_reads],
  dets.[last_num_page_server_reads],
  dets.[min_num_page_server_reads],
  dets.[max_num_page_server_reads]
FROM
  [sys].[dm_exec_trigger_stats] dets
```

Columns and interpretation

- `database_id`, `object_id` ? identify the trigger object.
- `Type` / `type_desc` ? trigger type and description.
- `sql_handle` / `plan_handle` ? handles for retrieving SQL text and plan.
- `cached_time` / `last_execution_time` ? timestamps for caching and latest execution.
- Execution counters: `execution_count`, `total_worker_time`, and last/min/max variants for CPU, IO and elapsed time.
- `total_spills` and related fields indicate spills to disk during execution (memory pressure).
- Page server and physical read counters provide IO diagnostics in remote/page server contexts.

How to interpret

- Average metrics can be computed by dividing `total_*` by `execution_count`.
- Spills indicate memory pressure for triggers; investigate if triggers perform heavy work.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecTriggerStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var t = new DmExecTriggerStatsReader(rdr, ownsReader:false);
while (t.Read())
{
    Console.WriteLine($"Trigger OID:{t.ObjectId} DB:{t.DatabaseId} ExecCount:{t.ExecutionCount} TotalCPU:{t.TotalWorkerTime}");
}
```

See also:

- [sys.dm_exec_trigger_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-trigger-stats)
