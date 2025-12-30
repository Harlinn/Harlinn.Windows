# DmDistributedExchangeStatsReader — reference

Overview

`DmDistributedExchangeStatsReader` wraps `sys.dm_distributed_exchange_stats` and reports metrics for distributed exchange operations used by parallel/distributed query execution. The view exposes throughput, progress, timing and error information for exchange steps.

Reader SQL

```
SELECT
  ddes.[request_id],
  ddes.[step_index],
  ddes.[dms_step_index],
  ddes.[source_distribution_id],
  ddes.[destination_distribution_id],
  ddes.[Type],
  ddes.[Status],
  ddes.[bytes_per_sec],
  ddes.[bytes_processed],
  ddes.[rows_processed],
  ddes.[start_time],
  ddes.[end_time],
  ddes.[total_elapsed_time],
  ddes.[cpu_time],
  ddes.[query_time],
  ddes.[buffers_available],
  ddes.[sql_spid],
  ddes.[dms_cpid],
  ddes.[error_id],
  ddes.[source_info],
  ddes.[destination_info]
FROM
  [sys].[dm_distributed_exchange_stats] ddes
```

Columns and interpretation

- `request_id` ? `RequestId` (string?)
  - Correlation identifier for the distributed request. Use to associate multiple exchange rows belonging to the same request.

- `step_index` ? `StepIndex` (int)
  - Local index of the step in the distributed execution plan.

- `dms_step_index` ? `DmsStepIndex` (int?)
  - Probably/guesswork: DMS-internal step index mapping; may be null for some steps.

- `source_distribution_id` ? `SourceDistributionId` (int)
  - Identifier of the source distribution (producer) side.

- `destination_distribution_id` ? `DestinationDistributionId` (int?)
  - Identifier of the destination distribution (consumer) side; null if not applicable.

- `Type` ? `Type` (string?)
  - Exchange type (e.g., shuffle, broadcast). Use to understand data movement pattern.

- `Status` ? `Status` (string?)
  - Current status of the exchange step (Running, Completed, Failed, etc.).

- `bytes_per_sec` ? `BytesPerSec` (long)
  - Throughput measured in bytes per second for this exchange step. Use to identify bottlenecks.

- `bytes_processed` ? `BytesProcessed` (long)
  - Total bytes transmitted/processed by the exchange step.

- `rows_processed` ? `RowsProcessed` (long)
  - Total rows transmitted/processed.

- `start_time` ? `StartTime` (DateTime)
  - Timestamp when the exchange step started.

- `end_time` ? `EndTime` (DateTime?)
  - Timestamp when the exchange step ended (null if still running).

- `total_elapsed_time` ? `TotalElapsedTime` (int)
  - Total elapsed time (ms?) for the step; check product docs for unit — often milliseconds.

- `cpu_time` ? `CpuTime` (long?)
  - CPU time consumed by the step (ms or microseconds depending on view documentation).

- `query_time` ? `QueryTime` (int)
  - Query-level time metric associated with this step (unit likely ms).

- `buffers_available` ? `BuffersAvailable` (int?)
  - Probably/guesswork: number of buffers available to the exchange; low values indicate memory pressure.

- `sql_spid` ? `SqlSpid` (int)
  - SQL Server session id associated with the exchange operation on the local node.

- `dms_cpid` ? `DmsCpid` (int?)
  - Probably/guesswork: DMS compute process id for the remote/compute node.

- `error_id` ? `ErrorId` (string?)
  - Error identifier or code if the exchange encountered failures.

- `source_info` / `destination_info` ? `SourceInfo` / `DestinationInfo` (string?)
  - Textual details about the source and destination endpoints involved in the exchange (addresses or node identifiers).

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDistributedExchangeStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var reader = new DmDistributedExchangeStatsReader(rdr, ownsReader:false);
while (reader.Read())
{
    Console.WriteLine($"Request: {reader.RequestId} Step: {reader.StepIndex} Type: {reader.Type} Status: {reader.Status}");
    Console.WriteLine($" Throughput: {reader.BytesPerSec:N0} B/s Processed: {reader.BytesProcessed:N0} rows: {reader.RowsProcessed:N0}");
    Console.WriteLine($" Start: {reader.StartTime} End: {reader.EndTime} Elapsed: {reader.TotalElapsedTime}");
    if (!string.IsNullOrEmpty(reader.ErrorId)) Console.WriteLine($" Error: {reader.ErrorId} {reader.SourceInfo} -> {reader.DestinationInfo}");
}
```

See also:

- [sys.dm_distributed_exchange_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-distributed-exchange-stats)
