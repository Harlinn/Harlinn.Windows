# DmDbSessionSpaceUsageReader — reference

Overview

`DmDbSessionSpaceUsageReader` wraps `sys.dm_db_session_space_usage` and reports per-session allocation and deallocation counts for user and internal objects measured in pages. Useful for diagnosing sessions that allocate large amounts of space.

Reader SQL

```
SELECT
  ddssu.[session_id],
  ddssu.[database_id],
  ddssu.[user_objects_alloc_page_count],
  ddssu.[user_objects_dealloc_page_count],
  ddssu.[internal_objects_alloc_page_count],
  ddssu.[internal_objects_dealloc_page_count],
  ddssu.[user_objects_deferred_dealloc_page_count]
FROM
  [sys].[dm_db_session_space_usage] ddssu
```

Columns (detailed)

- `session_id` ? `SessionId` (short?)
  - Session id (SPID) associated with the allocations.

- `database_id` ? `DatabaseId` (int?)
  - Database id where allocations occurred.

- `user_objects_alloc_page_count` ? `UserObjectsAllocPageCount` (long?)
  - Pages allocated for user objects by the session.

- `user_objects_dealloc_page_count` ? `UserObjectsDeallocPageCount` (long?)
  - Pages deallocated for user objects by the session.

- `internal_objects_alloc_page_count` ? `InternalObjectsAllocPageCount` (long?)
  - Pages allocated for internal objects by the session.

- `internal_objects_dealloc_page_count` ? `InternalObjectsDeallocPageCount` (long?)
  - Pages deallocated for internal objects by the session.

- `user_objects_deferred_dealloc_page_count` ? `UserObjectsDeferredDeallocPageCount` (long?)
  - Pages of user objects marked for deferred deallocation.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbSessionSpaceUsageReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbSessionSpaceUsageReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Session: {r.SessionId} DB: {r.DatabaseId}");
    Console.WriteLine($" User alloc/dealloc pages: {r.UserObjectsAllocPageCount}/{r.UserObjectsDeallocPageCount}");
}
```

See also:

- [sys.dm_db_session_space_usage](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-session-space-usage)
