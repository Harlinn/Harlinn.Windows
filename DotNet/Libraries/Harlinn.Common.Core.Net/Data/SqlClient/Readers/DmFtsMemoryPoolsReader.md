# DmFtsMemoryPoolsReader — reference

Overview

`DmFtsMemoryPoolsReader` wraps `sys.dm_fts_memory_pools` and reports memory pool configuration such as buffer size and limits.

Reader SQL

```
SELECT
  dfmp.[pool_id],
  dfmp.[buffer_size],
  dfmp.[min_buffer_limit],
  dfmp.[max_buffer_limit],
  dfmp.[buffer_count]
FROM
  [sys].[dm_fts_memory_pools] dfmp
```

Columns and interpretation

- `pool_id` ? memory pool identifier.
- `buffer_size` ? size of each buffer in the pool (bytes).
- `min_buffer_limit` / `max_buffer_limit` ? configured minimum and maximum buffer counts.
- `buffer_count` ? current number of buffers allocated in the pool.

How to interpret

- Compare `buffer_count` against `min_buffer_limit` and `max_buffer_limit` to see if pool scaling is active or constrained.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsMemoryPoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmFtsMemoryPoolsReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Pool:{p.PoolId} BufferSize:{p.BufferSize} Buffers:{p.BufferCount} Min:{p.MinBufferLimit} Max:{p.MaxBufferLimit}");
}
```

See also:

- [sys.dm_fts_memory_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-memory-pools)
