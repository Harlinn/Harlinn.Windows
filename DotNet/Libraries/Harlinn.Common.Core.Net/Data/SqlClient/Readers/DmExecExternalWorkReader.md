# DmExecExternalWorkReader — reference

Overview

`DmExecExternalWorkReader` wraps `sys.dm_exec_external_work` and reports details about external input/output work performed as part of external or distributed query processing. This includes input names, read locations, processing sizes and timing.

Reader SQL

```
SELECT
  deew.[execution_id],
  deew.[step_index],
  deew.[dms_step_index],
  deew.[work_id],
  deew.[compute_node_id],
  deew.[Type],
  deew.[input_name],
  deew.[read_location],
  deew.[read_command],
  deew.[bytes_processed],
  deew.[Length],
  deew.[start_time],
  deew.[end_time],
  deew.[total_elapsed_time],
  deew.[Status],
  deew.[compute_pool_id]
FROM
  [sys].[dm_exec_external_work] deew
```

Columns and interpretation

- `execution_id` / `step_index` / `dms_step_index` ? identifiers to correlate external work with distributed execution steps.
- `work_id` ? identifier for the external work item.
- `compute_node_id` ? compute node processing the work item.
- `Type` ? work type (e.g., ReadInput, WriteOutput).
- `input_name` ? name of the input source (file, external table, container).
- `read_location` ? offset or starting location within the input (long?).
- `read_command` ? command used to read the input (string SQL/command).
- `bytes_processed` / `Length` ? bytes processed and total length of input.
- `start_time` / `end_time` / `total_elapsed_time` ? timing metrics for the work.
- `Status` ? status of the work item (Completed/Failed/Running).
- `compute_pool_id` ? pool id where the work executed.

Interpretation

- Useful to find slow external reads or large input splits causing performance issues.
- `bytes_processed` relative to `Length` indicates progress; end_time null indicates ongoing work.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecExternalWorkReader.Sql;
using var rdr = cmd.ExecuteReader();
var w = new DmExecExternalWorkReader(rdr, ownsReader:false);
while (w.Read())
{
    Console.WriteLine($"Exec {w.ExecutionId} Work {w.WorkId} Node {w.ComputeNodeId} Type {w.Type} Input {w.InputName}");
    Console.WriteLine($" Bytes processed: {w.BytesProcessed}/{w.Length} Time(ms): {w.TotalElapsedTime} Status: {w.Status}");
}
```

See also:

- [sys.dm_exec_external_work](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-external-work)
