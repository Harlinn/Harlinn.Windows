# DmDbXtpMemoryConsumersReader — reference

Overview

`DmDbXtpMemoryConsumersReader` wraps `sys.dm_db_xtp_memory_consumers` and reports memory usage details per XTP memory consumer (tables, indexes, caches). Useful for tracking memory allocation and pressure across memory-optimized objects.

Reader SQL

```
SELECT
  ddxmc.[memory_consumer_id],
  ddxmc.[memory_consumer_type],
  ddxmc.[memory_consumer_type_desc],
  ddxmc.[memory_consumer_desc],
  ddxmc.[object_id],
  ddxmc.[xtp_object_id],
  ddxmc.[index_id],
  ddxmc.[allocated_bytes],
  ddxmc.[used_bytes],
  ddxmc.[allocation_count],
  ddxmc.[partition_count],
  ddxmc.[sizeclass_count],
  ddxmc.[min_sizeclass],
  ddxmc.[max_sizeclass],
  ddxmc.[memory_consumer_address]
FROM
  [sys].[dm_db_xtp_memory_consumers] ddxmc
```

Columns (how to interpret)

- `memory_consumer_id` ? unique id for the memory consumer.

- `memory_consumer_type` / `memory_consumer_type_desc` ? numeric type and human-friendly description (e.g., table allocator, index buffer).

- `memory_consumer_desc` ? textual description with more details.

- `object_id` / `xtp_object_id` / `index_id` ? identity of the associated object/index when applicable.

- `allocated_bytes` ? total bytes allocated for this consumer.

- `used_bytes` ? portion of allocated bytes currently in use.

- `allocation_count` ? number of allocation operations performed.

- `partition_count` ? number of partitions contributing to the consumer's allocations.

- `sizeclass_count` / `min_sizeclass` / `max_sizeclass` ? distribution of allocation size classes; used to analyze fragmentation and sizing.

- `memory_consumer_address` ? internal address token for the consumer; useful for low-level diagnostics.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpMemoryConsumersReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbXtpMemoryConsumersReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Consumer {r.MemoryConsumerId} Type: {r.MemoryConsumerTypeDesc} Allocated: {r.AllocatedBytes} Used: {r.UsedBytes}");
    Console.WriteLine($" Partitions: {r.PartitionCount} Size classes: {r.SizeclassCount} ({r.MinSizeclass}-{r.MaxSizeclass})");
}
```

See also:

- [sys.dm_db_xtp_memory_consumers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-memory-consumers)
