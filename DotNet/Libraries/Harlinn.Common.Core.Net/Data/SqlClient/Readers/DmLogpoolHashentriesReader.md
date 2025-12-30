# DmLogpoolHashentriesReader — reference

Overview

`DmLogpoolHashentriesReader` wraps `sys.dm_logpool_hashentries` and exposes internal log pool hash bucket entries used by SQL Server's log pool caching mechanism.

Reader SQL

```
SELECT
  dlh.[bucket_no],
  dlh.[database_id],
  dlh.[recovery_unit_id],
  dlh.[log_block_id],
  dlh.[cache_buffer]
FROM
  [sys].[dm_logpool_hashentries] dlh
```

Columns and interpretation

- `bucket_no` ? hash bucket number within the logpool's hash table.
- `database_id` ? database id owning the log entry.
- `recovery_unit_id` ? id of the recovery unit (internal grouping for log blocks).
- `log_block_id` ? identifier for the log block.
- `cache_buffer` ? binary contents of the cached log buffer.

How to interpret

- Useful for diagnosing log pool caching behavior, cache hits/misses and inspecting cached log buffer contents.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmLogpoolHashentriesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmLogpoolHashentriesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Bucket:{r.BucketNo} DB:{r.DatabaseId} RecUnit:{r.RecoveryUnitId} LogBlock:{r.LogBlockId} BufferLen:{r.CacheBuffer.Length}");
}
```

See also:

- [sys.dm_logpool_hashentries](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-logpool-hashentries)
