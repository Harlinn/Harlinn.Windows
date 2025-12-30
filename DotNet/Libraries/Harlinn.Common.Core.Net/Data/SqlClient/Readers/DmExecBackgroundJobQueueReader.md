# DmExecBackgroundJobQueueReader — reference

Overview

`DmExecBackgroundJobQueueReader` wraps `sys.dm_exec_background_job_queue` and exposes queued background job items, their parameters and status. These jobs are used by various internal background processes.

Reader SQL

```
SELECT
  debjq.[time_queued],
  debjq.[job_id],
  debjq.[database_id],
  debjq.[object_id1],
  debjq.[object_id2],
  debjq.[object_id3],
  debjq.[object_id4],
  debjq.[error_code],
  debjq.[request_type],
  debjq.[retry_count],
  debjq.[in_progress],
  debjq.[session_id]
FROM
  [sys].[dm_exec_background_job_queue] debjq
```

Columns (interpretation)

- `time_queued` ? `TimeQueued` (DateTime)
  - When the job was enqueued.

- `job_id` ? `JobId` (int)
  - Identifier for the job type or instance.

- `database_id` ? `DatabaseId` (int)
  - Database associated with the job.

- `object_id1..4` ? object identifiers used as parameters for the job (int). Interpret according to `job_id` semantics.

- `error_code` ? `ErrorCode` (int?)
  - Error code reported by processing the job, if any.

- `request_type` ? `RequestType` (short)
  - Numeric code for the request type; map using product docs.

- `retry_count` ? `RetryCount` (short)
  - Number of times the job has been retried.

- `in_progress` ? `InProgress` (short)
  - Flag indicating whether the job is currently being processed (1) or waiting (0).

- `session_id` ? `SessionId` (short?)
  - Session id that enqueued or is processing the job.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecBackgroundJobQueueReader.Sql;
using var rdr = cmd.ExecuteReader();
var q = new DmExecBackgroundJobQueueReader(rdr, ownsReader:false);
while (q.Read())
{
    Console.WriteLine($"Job {q.JobId} Queued: {q.TimeQueued} DB: {q.DatabaseId} InProgress: {q.InProgress}");
    Console.WriteLine($" Params: {q.ObjectId1},{q.ObjectId2},{q.ObjectId3},{q.ObjectId4} Retries: {q.RetryCount} Error: {q.ErrorCode}");
}
```

See also:

- [sys.dm_exec_background_job_queue](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-background-job-queue)
