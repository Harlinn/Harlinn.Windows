# DmExecExternalOperationsReader — reference

Overview

`DmExecExternalOperationsReader` wraps `sys.dm_exec_external_operations` and reports progress and metadata for external operations (such as map/reduce parts) invoked as part of distributed or external compute tasks.

Reader SQL

```
SELECT
  deeo.[execution_id],
  deeo.[step_index],
  deeo.[operation_type],
  deeo.[operation_name],
  deeo.[map_progress],
  deeo.[reduce_progress],
  deeo.[compute_pool_id]
FROM
  [sys].[dm_exec_external_operations] deeo
```

Columns and interpretation

- `execution_id` ? distributed execution id.
- `step_index` ? step index within the distributed plan.
- `operation_type` ? type of external operation (Map, Reduce, UDF, etc.).
- `operation_name` ? name of the operation or external function.
- `map_progress` / `reduce_progress` ? fractional progress indicators (0..1 or percentage) for the map/reduce phases.
- `compute_pool_id` ? compute pool id that ran the external operation.

Interpretation

- `map_progress` and `reduce_progress` help track long-running external operations; values close to 1 indicate near-completion.
- Join `execution_id` with distributed request/step DMVs to correlate progress with SQL-level stages.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecExternalOperationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecExternalOperationsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Exec {r.ExecutionId} Step:{r.StepIndex} Operation: {r.OperationType}/{r.OperationName} Map:{r.MapProgress} Reduce:{r.ReduceProgress}");
}
```

See also:

- [sys.dm_exec_external_operations](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-external-operations)
