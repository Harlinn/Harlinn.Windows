# DmFtsMemoryBuffersReader — reference

Overview

`DmFtsMemoryBuffersReader` wraps `sys.dm_fts_memory_buffers` and reports buffer usage for full-text search memory pools including rows, bytes used and usage percent.

Reader SQL

```
SELECT
  dfmb.[pool_id],
  dfmb.[memory_address],
  dfmb.[Name],
  dfmb.[is_free],
  dfmb.[row_count],
  dfmb.[bytes_used],
  dfmb.[percent_used]
FROM
  [sys].[dm_fts_memory_buffers] dfmb
```

Columns and interpretation

- `pool_id` ? memory pool identifier.
- `memory_address` ? internal memory address token.
- `Name` ? buffer name.
- `is_free` ? whether buffer is free.
- `row_count` ? number of rows currently stored in the buffer.
- `bytes_used` ? amount of memory used by the buffer in bytes.
- `percent_used` ? percentage of buffer capacity used.

How to interpret

- Use `is_free` and `percent_used` to find hotspots or resource exhaustion in FTS memory buffers.
- `bytes_used` combined with `row_count` gives density information.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsMemoryBuffersReader.Sql;
using var rdr = cmd.ExecuteReader();
var b = new DmFtsMemoryBuffersReader(rdr, ownsReader:false);
while (b.Read())
{
    Console.WriteLine($"Pool:{b.PoolId} Buffer:{b.Name} Free:{b.IsFree} Rows:{b.RowCount} Bytes:{b.BytesUsed} %Used:{b.PercentUsed}");
}
```

See also:

- [sys.dm_fts_memory_buffers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-memory-buffers)
