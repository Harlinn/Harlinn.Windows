# DmHadrAgThreadsReader — reference

Overview

`DmHadrAgThreadsReader` wraps `sys.dm_hadr_ag_threads` and returns counts of various Always On Availability Groups threads such as capture, redo and parallel redo threads per AG.

Reader SQL

```
SELECT
  dhat.[group_id],
  dhat.[Name],
  dhat.[num_databases],
  dhat.[num_capture_threads],
  dhat.[num_redo_threads],
  dhat.[num_parallel_redo_threads],
  dhat.[num_hadr_threads]
FROM
  [sys].[dm_hadr_ag_threads] dhat
```

Columns and interpretation

- `group_id` ? AG identifier (GUID).
- `Name` ? AG name.
- `num_databases` ? number of databases in the AG.
- `num_capture_threads` ? number of log capture threads.
- `num_redo_threads` ? number of redo threads.
- `num_parallel_redo_threads` ? number of parallel redo threads.
- `num_hadr_threads` ? total HADR-related threads.

How to interpret

- Use thread counts and `num_databases` to assess whether AG thread resources scale with the number of databases.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAgThreadsReader.Sql;
using var rdr = cmd.ExecuteReader();
var t = new DmHadrAgThreadsReader(rdr, ownsReader:false);
while (t.Read())
{
    Console.WriteLine($"AG:{t.Name} DBs:{t.NumDatabases} Capture:{t.NumCaptureThreads} Redo:{t.NumRedoThreads} ParallelRedo:{t.NumParallelRedoThreads}");
}
```

See also:

- [sys.dm_hadr_ag_threads](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-ag-threads)
