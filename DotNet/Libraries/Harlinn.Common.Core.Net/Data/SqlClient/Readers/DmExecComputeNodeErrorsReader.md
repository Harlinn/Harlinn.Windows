# DmExecComputeNodeErrorsReader — reference

Overview

`DmExecComputeNodeErrorsReader` wraps `sys.dm_exec_compute_node_errors` and lists errors reported by compute nodes in distributed/scale-out compute pools. Each row represents a reported error with context (node id, execution id, thread/spid, details).

Reader SQL

```
SELECT
  decne.[error_id],
  decne.[Source],
  decne.[Type],
  decne.[create_time],
  decne.[compute_node_id],
  decne.[execution_id],
  decne.[Spid],
  decne.[thread_id],
  decne.[Details],
  decne.[compute_pool_id]
FROM
  [sys].[dm_exec_compute_node_errors] decne
```

Columns (interpretation)

- `error_id` ? `ErrorId` (string?)
  - Error identifier string; correlate with logs or product documentation.

- `Source` ? `Source` (string?)
  - Source component reporting the error.

- `Type` ? `Type` (string?)
  - Error category/type.

- `create_time` ? `CreateTime` (DateTime?)
  - When the error was recorded.

- `compute_node_id` ? `ComputeNodeId` (int?)
  - Node id reporting the error.

- `execution_id` ? `ExecutionId` (string?)
  - Distributed execution id associated with the error.

- `Spid` ? `Spid` (int?)
  - Session id on the compute node.

- `thread_id` ? `ThreadId` (int?)
  - Thread id reporting the error.

- `Details` ? `Details` (string?)
  - Detailed error message and context.

- `compute_pool_id` ? `ComputePoolId` (int)
  - Compute pool identifier containing the node.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecComputeNodeErrorsReader.Sql;
using var rdr = cmd.ExecuteReader();
var e = new DmExecComputeNodeErrorsReader(rdr, ownsReader:false);
while (e.Read())
{
    Console.WriteLine($"Error {e.ErrorId} Source: {e.Source} Type: {e.Type} Time: {e.CreateTime}");
    Console.WriteLine($" Node: {e.ComputeNodeId} Pool: {e.ComputePoolId} Exec: {e.ExecutionId} SPID: {e.Spid}");
    Console.WriteLine($" Details: {e.Details}");
}
```

See also:

- [sys.dm_exec_compute_node_errors](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-compute-node-errors)
