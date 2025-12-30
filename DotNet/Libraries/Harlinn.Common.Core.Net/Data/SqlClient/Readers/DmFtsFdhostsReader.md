# DmFtsFdhostsReader — reference

Overview

`DmFtsFdhostsReader` wraps `sys.dm_fts_fdhosts` and reports on FTS file-distribution hosts, their process ids, types and batch counts used in full-text population.

Reader SQL

```
SELECT
  dff.[fdhost_id],
  dff.[fdhost_name],
  dff.[fdhost_process_id],
  dff.[fdhost_type],
  dff.[max_thread],
  dff.[batch_count]
FROM
  [sys].[dm_fts_fdhosts] dff
```

Columns and interpretation

- `fdhost_id` ? identifier of the FD host.
- `fdhost_name` ? host name.
- `fdhost_process_id` ? process id for the host.
- `fdhost_type` ? type of FD host.
- `max_thread` ? maximum threads allowed for the host.
- `batch_count` ? number of batches in processing queue for that host.

How to interpret

- Use `batch_count` and `max_thread` to identify hosts that are overloaded or under-provisioned.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsFdhostsReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmFtsFdhostsReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"Host:{h.FdhostName} PID:{h.FdhostProcessId} Type:{h.FdhostType} MaxThreads:{h.MaxThread} Batches:{h.BatchCount}");
}
```

See also:

- [sys.dm_fts_fdhosts](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-fdhosts)
