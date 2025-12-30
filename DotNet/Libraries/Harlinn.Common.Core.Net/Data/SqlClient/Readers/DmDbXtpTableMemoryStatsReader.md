# DmDbXtpTableMemoryStatsReader — reference

Overview

`DmDbXtpTableMemoryStatsReader` wraps `sys.dm_db_xtp_table_memory_stats` and reports memory allocations and usage (in KB) per memory-optimized table and its indexes. Useful for capacity planning and diagnosing memory pressure.

Reader SQL

```
SELECT
  ddxtms.[object_id],
  ddxtms.[memory_allocated_for_table_kb],
  ddxtms.[memory_used_by_table_kb],
  ddxtms.[memory_allocated_for_indexes_kb],
  ddxtms.[memory_used_by_indexes_kb]
FROM
  [sys].[dm_db_xtp_table_memory_stats] ddxtms
```

Columns (how to interpret)

- `object_id` ? `ObjectId` (int?)
  - Table object id. Null for global stats or if object removed.

- `memory_allocated_for_table_kb` ? allocated KB for table structures (long?)
  - Total memory reserved for table data structures including allocation overhead.

- `memory_used_by_table_kb` ? used KB by actual data for the table (long?)
  - Portion of allocated memory currently used by table data.

- `memory_allocated_for_indexes_kb` / `memory_used_by_indexes_kb`
  - Similar metrics for indexes associated with the table.

Interpretation

- If allocated >> used, memory may be fragmented or reserved but unused. Consider tuning size classes or instance-level settings.
- Use these per-table metrics to attribute memory consumption and plan memory pool sizing.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpTableMemoryStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpTableMemoryStatsReader(reader, ownsReader: false);
while (s.Read())
{
    Console.WriteLine($"Object {s.ObjectId} TableAllocatedKB: {s.MemoryAllocatedForTableKb} UsedKB: {s.MemoryUsedByTableKb}");
    Console.WriteLine($" IndexAllocatedKB: {s.MemoryAllocatedForIndexesKb} UsedKB: {s.MemoryUsedByIndexesKb}");
}
```

See also:

- [sys.dm_db_xtp_table_memory_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-table-memory-stats)
