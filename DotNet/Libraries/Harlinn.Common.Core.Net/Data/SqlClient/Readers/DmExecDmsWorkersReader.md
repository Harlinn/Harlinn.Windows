# DmExecDmsWorkersReader — reference

Overview

`DmExecDmsWorkersReader` wraps `sys.dm_exec_dms_workers` and reports per-worker metrics for distributed execution workers. It includes throughput, progress, timing and status information for each worker processing a slice of a distributed query.

Reader SQL

```
SELECT
  dedw.[execution_id],
  dedw.[step_index],
  dedw.[dms_step_index],
  dedw.[compute_node_id],
  dedw.[distribution_id],
  dedw.[Type],
  dedw.[Status],
  dedw.[bytes_per_sec],
  dedw.[bytes_processed],
  dedw.[rows_processed],
  dedw.[start_time],
  dedw.[end_time],
  dedw.[total_elapsed_time],
  dedw.[cpu_time],
  dedw.[query_time],
  dedw.[buffers_available],
  dedw.[dms_cpid],
  dedw.[sql_spid],
  dedw.[error_id],
  dedw.[source_info],
  dedw.[destination_info],
  dedw.[Command],
  dedw.[compute_pool_id]
FROM
  [sys].[dm_exec_dms_workers] dedw
```

Columns and interpretation

- `execution_id` ? execution correlation id; use to join with request-level and step-level views.
- `step_index` / `dms_step_index` ? indices representing the step within plan and DMS internals.
- `compute_node_id` / `distribution_id` ? identifiers for compute node and distribution slice.
- `Type` / `Status` ? textual type and current status of the worker.
- `bytes_per_sec`, `bytes_processed`, `rows_processed` ? throughput and progress metrics.
- `start_time` / `end_time` / `total_elapsed_time` ? timing metrics for the worker's execution window.
- `cpu_time` / `query_time` ? CPU and query time consumed by the worker (units ms or as documented).
- `buffers_available` ? number of buffers available to the worker; low values indicate resource pressure.
- `dms_cpid` / `sql_spid` ? DMS compute process id and SQL session id respectively.
- `error_id` / `source_info` / `destination_info` ? error and endpoint info when failures occur.
- `Command` ? SQL executed by the worker.
- `compute_pool_id` ? pool id where the worker ran.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecDmsWorkersReader.Sql;
using var rdr = cmd.ExecuteReader();
var w = new DmExecDmsWorkersReader(rdr, ownsReader:false);
while (w.Read())
{
    Console.WriteLine($"Exec {w.ExecutionId} Step {w.StepIndex} Node {w.ComputeNodeId} Type:{w.Type} Status:{w.Status}");
    Console.WriteLine($" Throughput: {w.BytesPerSec} B/s Processed: {w.BytesProcessed} rows: {w.RowsProcessed}");
}
```

See also:

- [sys.dm_exec_dms_workers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-dms-workers)
