# DmDbXtpCheckpointStatsReader — reference

Overview

`DmDbXtpCheckpointStatsReader` wraps `sys.dm_db_xtp_checkpoint_stats` and exposes comprehensive metrics about In-Memory OLTP checkpointing. Use these metrics to monitor checkpoint lag, serialization throughput, wait times, and checkpoint lifecycle counters.

Reader SQL

```
SELECT
  ddxcs.[last_lsn_processed],
  ddxcs.[end_of_log_lsn],
  ddxcs.[bytes_to_end_of_log],
  ddxcs.[log_consumption_rate],
  ddxcs.[active_scan_time_in_ms],
  ddxcs.[total_wait_time_in_ms],
  ddxcs.[waits_for_io_count],
  ddxcs.[io_wait_time_in_ms],
  ddxcs.[waits_for_new_log_count],
  ddxcs.[new_log_wait_time_in_ms],
  ddxcs.[idle_attempts_count],
  ddxcs.[tx_segments_dispatched_count],
  ddxcs.[segment_bytes_dispatched],
  ddxcs.[bytes_serialized],
  ddxcs.[serializer_user_time_in_ms],
  ddxcs.[serializer_kernel_time_in_ms],
  ddxcs.[xtp_log_bytes_consumed],
  ddxcs.[checkpoints_closed],
  ddxcs.[last_closed_checkpoint_ts],
  ddxcs.[hardened_recovery_lsn],
  ddxcs.[hardened_root_file_guid],
  ddxcs.[hardened_root_file_watermark],
  ddxcs.[hardened_truncation_lsn],
  ddxcs.[log_bytes_since_last_close],
  ddxcs.[time_since_last_close_in_ms],
  ddxcs.[current_checkpoint_id],
  ddxcs.[current_checkpoint_segment_count],
  ddxcs.[recovery_lsn_candidate],
  ddxcs.[outstanding_checkpoint_count],
  ddxcs.[closing_checkpoint_id],
  ddxcs.[recovery_checkpoint_id],
  ddxcs.[recovery_checkpoint_ts],
  ddxcs.[bootstrap_recovery_lsn],
  ddxcs.[bootstrap_root_file_guid],
  ddxcs.[internal_error_code],
  ddxcs.[tail_cache_page_count],
  ddxcs.[tail_cache_max_page_count],
  ddxcs.[tail_cache_min_needed_lsn],
  ddxcs.[merge_outstanding_merges],
  ddxcs.[merge_stats_number_of_merges],
  ddxcs.[merge_stats_log_blocks_merged],
  ddxcs.[merge_stats_bytes_merged],
  ddxcs.[merge_stats_user_time],
  ddxcs.[merge_stats_kernel_time],
  ddxcs.[bytes_of_large_data_serialized]
FROM
  [sys].[dm_db_xtp_checkpoint_stats] ddxcs
```

Columns (how to interpret)

- `last_lsn_processed` ? `LastLsnProcessed` (decimal?)
  - LSN of the last transaction log record processed by the XTP checkpoint serializer. If close to end_of_log_lsn, serializer is caught up.

- `end_of_log_lsn` ? `EndOfLogLsn` (decimal?)
  - Current end-of-log LSN. Used as a reference to measure serializer lag (end_of_log_lsn - last_lsn_processed).

- `bytes_to_end_of_log` ? `BytesToEndOfLog` (long?)
  - Approximate bytes between last processed LSN and end of log; lower values indicate less backlog.

- `log_consumption_rate` ? `LogConsumptionRate` (long?)
  - Rate (bytes/sec?) at which log is consumed by serializer; higher means faster processing.

- `active_scan_time_in_ms` ? `ActiveScanTimeInMs` (long?)
  - Cumulative time spent in active scan operations during checkpointing.

- `total_wait_time_in_ms` ? `TotalWaitTimeInMs` (long?)
  - Total time spent waiting (I/O, new log availability etc.) during checkpoint operations.

- `waits_for_io_count` / `io_wait_time_in_ms` ? counts and cumulative time waiting for I/O. High values suggest I/O bottlenecks.

- `waits_for_new_log_count` / `new_log_wait_time_in_ms` ? counts and time spent waiting for new log records to be available.

- `idle_attempts_count` ? `IdleAttemptsCount` (long?)
  - Number of attempts where serializer found no work and was idle.

- `tx_segments_dispatched_count` / `segment_bytes_dispatched` ? counts/bytes dispatched to serializer segments.

- `bytes_serialized` ? `BytesSerialized` (long?)
  - Total bytes serialized into checkpoint files.

- `serializer_user_time_in_ms` / `serializer_kernel_time_in_ms` ? CPU time consumed by serializer in user/kernel mode.

- `xtp_log_bytes_consumed` ? `XtpLogBytesConsumed` (long?)
  - Total XTP log bytes consumed by checkpointing since service start.

- `checkpoints_closed` ? `CheckpointsClosed` (long?)
  - Number of checkpoints fully closed.

- `last_closed_checkpoint_ts` ? `LastClosedCheckpointTs` (long?)
  - Timestamp for last closed checkpoint (opaque ticks).

- Hardened-related fields (`hardened_recovery_lsn`, `hardened_root_file_guid`, `hardened_root_file_watermark`, `hardened_truncation_lsn`) indicate on-disk hardened checkpoint info useful for recovery and truncation decisions.

- `log_bytes_since_last_close` / `time_since_last_close_in_ms` ? growth since last checkpoint close.

- `current_checkpoint_id` / `current_checkpoint_segment_count` ? tracking current open checkpoint and its segment count.

- `recovery_lsn_candidate` ? candidate LSN for recovery operations.

- `outstanding_checkpoint_count` / `closing_checkpoint_id` / `recovery_checkpoint_id` / `recovery_checkpoint_ts` ? lifecycle bookkeeping for checkpoints in flight or used for recovery.

- `bootstrap_recovery_lsn` / `bootstrap_root_file_guid` ? bootstrap checkpoint references for initial recovery.

- `internal_error_code` ? internal error numeric code if checkpoint subsystem reports an issue; consult product docs for mapping.

- Tail cache and merge stats (`tail_cache_page_count`, `merge_outstanding_merges`, `merge_stats_*`) provide insight into background merge operations and tail-cache usage.

- `bytes_of_large_data_serialized` ? number of bytes from large objects serialized.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpCheckpointStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpCheckpointStatsReader(reader, ownsReader: false);
if (s.Read())
{
    Console.WriteLine($"LastLSNProcessed: {s.LastLsnProcessed} EndOfLogLSN: {s.EndOfLogLsn}");
    Console.WriteLine($"Bytes to end of log: {s.BytesToEndOfLog}, Consumption rate: {s.LogConsumptionRate}");
    Console.WriteLine($"Bytes serialized: {s.BytesSerialized} Serializer CPU(ms): {s.SerializerUserTimeInMs}/{s.SerializerKernelTimeInMs}");
    Console.WriteLine($"Outstanding checkpoints: {s.OutstandingCheckpointCount} CurrentCheckpointId: {s.CurrentCheckpointId}");
}
```

See also:

- [sys.dm_db_xtp_checkpoint_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-checkpoint-stats)
