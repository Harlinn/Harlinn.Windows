# DmExecDistributedSqlRequestsReader — reference

Overview

`DmExecDistributedSqlRequestsReader` wraps `sys.dm_exec_distributed_sql_requests` and reports details for SQL requests executed on remote/compute nodes as part of distributed query execution. Use it to correlate execution ids, step indexes, compute node identifiers, timing, row counts and error/status info for individual SQL requests executed remotely.

Reader SQL

```
SELECT
  dedsr.[execution_id],
  dedsr.[step_index],
  dedsr.[compute_node_id],
  dedsr.[distribution_id],
  dedsr.[Status],
  dedsr.[error_id],
  dedsr.[start_time],
  dedsr.[end_time],
  dedsr.[total_elapsed_time],
  dedsr.[row_count],
  dedsr.[Spid],
  dedsr.[Command],
  dedsr.[compute_pool_id]
FROM
  [sys].[dm_exec_distributed_sql_requests] dedsr
```

Columns and interpretation

- `execution_id` ? `ExecutionId` (string?)
  - Correlation id for the distributed execution. Use to match related rows across DMVs and compute node logs.

- `step_index` ? `StepIndex` (int?)
  - Index of this step within the distributed plan; helps map to plan steps and exchange/worker records.

- `compute_node_id` ? `ComputeNodeId` (int?)
  - Identifier of the compute node that executed this SQL request.

- `distribution_id` ? `DistributionId` (int?)
  - Identifier for distribution partition involved; use to understand which slice of data was processed.

- `Status` ? `Status` (string?)
  - Textual status (Running/Completed/Failed); use to detect failures and in-progress work.

- `error_id` ? `ErrorId` (string?)
  - Error identifier string if the request failed; consult logs and docs to map to actionable error.

- `start_time` / `end_time` ? timestamps for the request execution window. `end_time` may be null if still running.

- `total_elapsed_time` ? elapsed duration for the request (units typically milliseconds; confirm in docs).

- `row_count` ? number of rows produced/processed by this request slice; useful when totaling across slices.

- `Spid` ? server session id on the compute node where the request ran (int?).

- `Command` ? SQL text run on the compute node for this request step (string?).

- `compute_pool_id` ? compute pool identifier associated with the request.

How to interpret

- Correlate `ExecutionId` with `dm_exec_distributed_request_steps` and `dm_exec_dms_workers` rows to get per-step and per-worker metrics.
- High `total_elapsed_time` relative to other slices may indicate stragglers and skew; inspect `row_count` to detect data skew.
- Non-empty `ErrorId` indicates failures — check compute node errors and logs for details.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecDistributedSqlRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var reader = new DmExecDistributedSqlRequestsReader(rdr, ownsReader:false);
while (reader.Read())
{
    Console.WriteLine($"Exec {reader.ExecutionId} Step:{reader.StepIndex} Node:{reader.ComputeNodeId} Status:{reader.Status}");
    Console.WriteLine($" Rows:{reader.RowCount} Time(ms):{reader.TotalElapsedTime} Command: {reader.Command}\n");
}
```

See also:

- [sys.dm_exec_distributed_sql_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-distributed-sql-requests)
