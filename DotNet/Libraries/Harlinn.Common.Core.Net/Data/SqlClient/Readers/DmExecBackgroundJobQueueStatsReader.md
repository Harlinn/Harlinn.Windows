# DmExecBackgroundJobQueueStatsReader — reference

Overview

`DmExecBackgroundJobQueueStatsReader` wraps `sys.dm_exec_background_job_queue_stats` and exposes aggregate statistics for the background job queue such as enqueue/dequeue counts and failure counts. Use for monitoring background job throughput and failures.

Reader SQL

```
SELECT
  debjqs.[queue_max_len],
  debjqs.[enqueued_count],
  debjqs.[started_count],
  debjqs.[ended_count],
  debjqs.[failed_lock_count],
  debjqs.[failed_other_count],
  debjqs.[failed_giveup_count],
  debjqs.[enqueue_failed_full_count],
  debjqs.[enqueue_failed_duplicate_count],
  debjqs.[elapsed_avg_ms],
  debjqs.[elapsed_max_ms]
FROM
  [sys].[dm_exec_background_job_queue_stats] debjqs
```

Columns (interpretation)

- `queue_max_len` ? `QueueMaxLen` (int)
  - Maximum queue depth observed.

- `enqueued_count` ? `EnqueuedCount` (int)
  - Total number of jobs enqueued.

- `started_count` ? `StartedCount` (int)
  - Number of jobs that have started processing.

- `ended_count` ? `EndedCount` (int)
  - Number of jobs that completed processing (success or failure count included based on view semantics).

- `failed_lock_count` / `failed_other_count` / `failed_giveup_count` ? counts of failed jobs by category.

- `enqueue_failed_full_count` ? times enqueue failed due to full queue.

- `enqueue_failed_duplicate_count` ? times enqueue failed because of duplicate job detection.

- `elapsed_avg_ms` ? `ElapsedAvgMs` (int)
  - Average processing time in milliseconds per job.

- `elapsed_max_ms` ? `ElapsedMaxMs` (int)
  - Maximum observed processing time in milliseconds.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecBackgroundJobQueueStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecBackgroundJobQueueStatsReader(rdr, ownsReader:false);
if (s.Read())
{
    Console.WriteLine($"Queue max len: {s.QueueMaxLen} Enqueued: {s.EnqueuedCount} Started: {s.StartedCount} Ended: {s.EndedCount}");
    Console.WriteLine($" Failures: lock={s.FailedLockCount} other={s.FailedOtherCount} giveup={s.FailedGiveupCount}");
    Console.WriteLine($" Avg/Max elapsed (ms): {s.ElapsedAvgMs}/{s.ElapsedMaxMs}");
}
```

See also:

- [sys.dm_exec_background_job_queue_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-background-job-queue-stats)
