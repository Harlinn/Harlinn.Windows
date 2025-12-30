# DmXtpSystemMemoryConsumersReader — reference

Overview

`DmXtpSystemMemoryConsumersReader` wraps `sys.dm_xtp_system_memory_consumers` and returns memory allocation statistics for various In-Memory OLTP (XTP) memory consumers, including lookaside structures and size-class distributions.

Reader SQL

```
SELECT
  dxsmc.[memory_consumer_id],
  dxsmc.[memory_consumer_type],
  dxsmc.[memory_consumer_type_desc],
  dxsmc.[memory_consumer_desc],
  dxsmc.[lookaside_id],
  dxsmc.[allocated_bytes],
  dxsmc.[used_bytes],
  dxsmc.[allocation_count],
  dxsmc.[partition_count],
  dxsmc.[sizeclass_count],
  dxsmc.[min_sizeclass],
  dxsmc.[max_sizeclass],
  dxsmc.[memory_consumer_address]
FROM
  [sys].[dm_xtp_system_memory_consumers] dxsmc
```

Columns and interpretation

- `memory_consumer_id` — numeric id for the memory consumer.
- `memory_consumer_type` — numeric code for the type of consumer.
- `memory_consumer_type_desc` — textual description of the consumer type.
- `memory_consumer_desc` — optional detailed description of the consumer (nullable).
- `lookaside_id` — optional lookaside allocator id used by the consumer (nullable).
- `allocated_bytes` — total bytes allocated for this consumer.
- `used_bytes` — bytes currently in use by consumer.
- `allocation_count` — number of allocations performed.
- `partition_count` — number of partitions used by consumer (for scalability).
- `sizeclass_count` — number of distinct size classes tracked.
- `min_sizeclass` / `max_sizeclass` — minimum and maximum size classes observed.
- `memory_consumer_address` — binary address pointer for the consumer's structure.

How to interpret

- Compare `allocated_bytes` and `used_bytes` to spot fragmentation or over-reservation.
- `allocation_count` and `partition_count` indicate allocation churn and scalability.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpSystemMemoryConsumersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpSystemMemoryConsumersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Consumer:{r.MemoryConsumerId} Type:{r.MemoryConsumerTypeDesc} Alloc:{r.AllocatedBytes} Used:{r.UsedBytes} Partitions:{r.PartitionCount}");
}
```

See also:

- [sys.dm_xtp_system_memory_consumers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-system-memory-consumers)
