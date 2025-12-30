# DmDbTaskSpaceUsageReader — reference

Overview

`DmDbTaskSpaceUsageReader` wraps `sys.dm_db_task_space_usage` and reports per-task allocation/deallocation page counts for user and internal objects. Helps diagnose tasks that allocate excessive temporary space.

Reader SQL

```
SELECT
  ddtsu.[task_address],
  ddtsu.[is_remote_task],
  ddtsu.[session_id],
  ddtsu.[request_id],
  ddtsu.[exec_context_id],
  ddtsu.[database_id],
  ddtsu.[user_objects_alloc_page_count],
  ddtsu.[user_objects_dealloc_page_count],
  ddtsu.[internal_objects_alloc_page_count],
  ddtsu.[internal_objects_dealloc_page_count]
FROM
  [sys].[dm_db_task_space_usage] ddtsu
```

Columns (detailed)

- `task_address` ? `TaskAddress` (byte[]?)
  - Binary token that uniquely identifies the task within the SQL OS instance.

- `is_remote_task` ? `IsRemoteTask` (bool)
  - Whether the task is from a remote execution context.

- `session_id` ? `SessionId` (short?)
  - Session (SPID) associated with the task if applicable.

- `request_id` ? `RequestId` (int?)
  - Request id associated with the task.

- `exec_context_id` ? `ExecContextId` (int?)
  - Execution context identifier for the task.

- `database_id` ? `DatabaseId` (int?)
  - Database where the allocations were made.

- `user_objects_alloc_page_count` / `user_objects_dealloc_page_count` ? page counts (long?)
  - Pages allocated and deallocated for user objects.

- `internal_objects_alloc_page_count` / `internal_objects_dealloc_page_count` ? page counts (long?)
  - Pages allocated and deallocated for internal objects.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbTaskSpaceUsageReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbTaskSpaceUsageReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Task: {BitConverter.ToString(r.TaskAddress ?? Array.Empty<byte>())} Remote: {r.IsRemoteTask}");
    Console.WriteLine($" Session: {r.SessionId} Request: {r.RequestId} DB: {r.DatabaseId}");
    Console.WriteLine($" User alloc/dealloc: {r.UserObjectsAllocPageCount}/{r.UserObjectsDeallocPageCount}");
}
```

See also:

- [sys.dm_db_task_space_usage](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-task-space-usage)
