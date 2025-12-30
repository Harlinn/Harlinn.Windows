# ServerMemoryOptimizedHybridBufferPoolConfigurationReader

Overview

`ServerMemoryOptimizedHybridBufferPoolConfigurationReader` wraps `sys.server_memory_optimized_hybrid_buffer_pool_configuration` and exposes whether the hybrid buffer pool for memory-optimized objects is configured and enabled.

Reader SQL

```
SELECT
  smohbpc.[is_configured],
  smohbpc.[is_enabled]
FROM
  [sys].[server_memory_optimized_hybrid_buffer_pool_configuration] smohbpc
```

Columns and interpretation

- `is_configured` (object?): Whether the hybrid buffer pool has been configured on the server. Could be boolean or other indicator.
- `is_enabled` (object?): Whether the hybrid buffer pool is currently enabled.

How to interpret

- Values indicate whether the server is set up to use the hybrid buffer pool feature for memory-optimized tables; interpretation may vary by SQL Server build — inspect returned types in your environment.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerMemoryOptimizedHybridBufferPoolConfigurationReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerMemoryOptimizedHybridBufferPoolConfigurationReader(rdr, ownsReader:false);
if (r.Read())
    Console.WriteLine($"Configured:{r.IsConfigured} Enabled:{r.IsEnabled}");
```

See also:

- [sys.server_memory_optimized_hybrid_buffer_pool_configuration](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-memory-optimized-hybrid-buffer-pool-configuration)

