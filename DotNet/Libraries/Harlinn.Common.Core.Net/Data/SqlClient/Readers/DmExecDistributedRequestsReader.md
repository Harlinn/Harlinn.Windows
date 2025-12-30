# DmExecDistributedRequestsReader — reference

Overview

`DmExecDistributedRequestsReader` wraps `sys.dm_exec_distributed_requests` and lists distributed request submissions to compute pools. It includes execution id, status, error and timing information.

Reader SQL

```
SELECT
  dedr.[sql_handle],
  dedr.[execution_id],
  dedr.[Status],
  dedr.[error_id],
  dedr.[start_time],
  dedr.[end_time],
  dedr.[total_elapsed_time],
  dedr.[compute_pool_id]
FROM
  [sys].[dm_exec_distributed_requests] dedr
```

Columns (interpretation)

- `sql_handle` ? `SqlHandle` (binary?)
  - Plan handle for the SQL batch submitted as part of the distributed request.

- `execution_id` ? `ExecutionId` (string?)
  - Unique id for the distributed execution; use to correlate with step-level metrics and compute node logs.

- `Status` ? `Status` (string?)
  - Current status (e.g., Running, Completed, Failed).

- `error_id` ? `ErrorId` (string?)
  - Error identifier if the distributed request failed.

- `start_time` / `end_time` ? timestamps when request started and ended.

- `total_elapsed_time` ? elapsed time (ms?) for the request.

- `compute_pool_id` ? which compute pool processed the request.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecDistributedRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecDistributedRequestsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Exec {r.ExecutionId} Status: {r.Status} Pool: {r.ComputePoolId}");
    Console.WriteLine($" Start: {r.StartTime} End: {r.EndTime} Elapsed: {r.TotalElapsedTime} Error: {r.ErrorId}");
}
```

See also:

- [sys.dm_exec_distributed_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-distributed-requests)
