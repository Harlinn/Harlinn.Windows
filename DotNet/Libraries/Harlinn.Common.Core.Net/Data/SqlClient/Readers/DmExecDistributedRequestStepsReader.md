# DmExecDistributedRequestStepsReader — reference

Overview

`DmExecDistributedRequestStepsReader` wraps `sys.dm_exec_distributed_request_steps` and reports per-step details for distributed requests, including operation type, distribution and location, status, timing and row counts.

Reader SQL

```
SELECT
  dedrs.[execution_id],
  dedrs.[step_index],
  dedrs.[operation_type],
  dedrs.[distribution_type],
  dedrs.[location_type],
  dedrs.[Status],
  dedrs.[error_id],
  dedrs.[start_time],
  dedrs.[end_time],
  dedrs.[total_elapsed_time],
  dedrs.[row_count],
  dedrs.[Command],
  dedrs.[compute_pool_id]
FROM
  [sys].[dm_exec_distributed_request_steps] dedrs
```

Columns (interpretation)

- `execution_id` ? distributed execution id.
- `step_index` ? index of the step in the distributed plan.
- `operation_type` ? operation performed at this step (Scan, Join, Aggregate, etc.).
- `distribution_type` ? how data is distributed for this step (Shuffle, Broadcast, etc.).
- `location_type` ? where the step ran (Local, Remote, Compute pool, etc.).
- `Status` ? status of the step (Running, Completed, Failed).
- `error_id` ? error identifier if any.
- `start_time` / `end_time` ? step timestamps.
- `total_elapsed_time` ? elapsed time for the step (ms?).
- `row_count` ? number of rows processed by the step.
- `Command` ? textual SQL command executed at this step.
- `compute_pool_id` ? compute pool used to execute the step.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecDistributedRequestStepsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecDistributedRequestStepsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Exec {s.ExecutionId} Step {s.StepIndex} Op: {s.OperationType} Dist: {s.DistributionType} Loc: {s.LocationType}");
    Console.WriteLine($" Status: {s.Status} Rows: {s.RowCount} Time(ms): {s.TotalElapsedTime}");
    Console.WriteLine($" Command: {s.Command}");
}
```

See also:

- [sys.dm_exec_distributed_request_steps](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-distributed-request-steps)
