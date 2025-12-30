# IndexResumableOperationsReader — reference

Overview

`IndexResumableOperationsReader` wraps `sys.index_resumable_operations` and returns details about currently resumable index operations (such as rebuilds), including progress and execution metrics.

Reader SQL

```
SELECT
  iro.[object_id],
  iro.[index_id],
  iro.[Name],
  iro.[sql_text],
  iro.[last_max_dop_used],
  iro.[partition_number],
  iro.[State],
  iro.[state_desc],
  iro.[start_time],
  iro.[last_pause_time],
  iro.[total_execution_time],
  iro.[percent_complete],
  iro.[page_count]
FROM
  [sys].[index_resumable_operations] iro
```

Columns and interpretation

- `object_id`, `index_id`, `Name` — identity of the index operation.
- `sql_text` — the T-SQL statement text driving the operation (nullable).
- `last_max_dop_used` — last MAXDOP value used for the operation.
- `partition_number` — partition number the operation targets (nullable for whole-index operations).
- `State` / `state_desc` — state code and description (e.g., RUNNING, PAUSED).
- `start_time` — when the operation started.
- `last_pause_time` — when operation was last paused (nullable).
- `total_execution_time` — cumulative execution time in seconds or milliseconds (depending on view semantics).
- `percent_complete` — completion percentage (0-100).
- `page_count` — number of pages processed or to process.

How to interpret

- Useful for monitoring progress of large index operations. Combine `percent_complete` with `total_execution_time` to estimate remaining work.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = IndexResumableOperationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new IndexResumableOperationsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Index Obj:{r.ObjectId} Id:{r.IndexId} State:{r.StateDesc} {r.PercentComplete}% Started:{r.StartTime}");
}
```

See also:

- [sys.index_resumable_operations](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-index-resumable-operations)
