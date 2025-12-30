# DmHadrDbThreadsReader — reference

Overview

`DmHadrDbThreadsReader` wraps `sys.dm_hadr_db_threads` and returns counts of HADR-related threads per database such as redo and capture threads.

Reader SQL

```
SELECT
  dhdbt.[group_database_id],
  dhdbt.[Name],
  dhdbt.[num_databases],
  dhdbt.[num_capture_threads],
  dhdbt.[num_redo_threads],
  dhdbt.[num_parallel_redo_threads],
  dhdbt.[num_hadr_threads]
FROM
  [sys].[dm_hadr_db_threads] dhdbt
```

Columns and interpretation

- `group_database_id` ? identifier for the group-database mapping.
- `Name` ? database name.
- `num_databases` ? number of databases (contextual).
- `num_capture_threads`, `num_redo_threads`, `num_parallel_redo_threads`, `num_hadr_threads` ? thread counts for database-level HADR operations.

How to interpret

- Use thread counts to evaluate resource use for database-level replication tasks.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrDbThreadsReader.Sql;
using var rdr = cmd.ExecuteReader();
var t = new DmHadrDbThreadsReader(rdr, ownsReader:false);
while (t.Read())
{
    Console.WriteLine($"DB:{t.Name} Capture:{t.NumCaptureThreads} Redo:{t.NumRedoThreads} ParallelRedo:{t.NumParallelRedoThreads}");
}
```

See also:

- [sys.dm_hadr_db_threads](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-db-threads)
