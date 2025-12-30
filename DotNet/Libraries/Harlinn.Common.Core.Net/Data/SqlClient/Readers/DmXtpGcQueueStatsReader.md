# DmXtpGcQueueStatsReader — reference

Overview

`DmXtpGcQueueStatsReader` wraps `sys.dm_xtp_gc_queue_stats` and returns statistics for garbage collection queues used by In-Memory OLTP (XTP) garbage collector.

Reader SQL

```
SELECT
  dxgqs.[queue_id],
  dxgqs.[total_enqueues],
  dxgqs.[total_dequeues],
  dxgqs.[current_queue_depth],
  dxgqs.[maximum_queue_depth],
  dxgqs.[last_service_ticks]
FROM
  [sys].[dm_xtp_gc_queue_stats] dxgqs
```

Columns and interpretation

- `queue_id` — identifier for the GC queue.
- `total_enqueues` — cumulative count of items enqueued into the GC queue.
- `total_dequeues` — cumulative count of items dequeued (processed) from the GC queue.
- `current_queue_depth` — current number of items waiting in the queue.
- `maximum_queue_depth` — maximum observed depth of the queue.
- `last_service_ticks` — timestamp in tick units when the queue was last serviced.

How to interpret

- A growing `current_queue_depth` or high `maximum_queue_depth` indicates the GC cannot keep up with workload, possibly causing pressure on memory.
- Compare `total_enqueues` and `total_dequeues` to see processing lag.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpGcQueueStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpGcQueueStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Queue:{r.QueueId} Depth:{r.CurrentQueueDepth}/{r.MaximumQueueDepth} Enq:{r.TotalEnqueues} Deq:{r.TotalDequeues} LastServicedTicks:{r.LastServiceTicks}");
}
```

See also:

- [sys.dm_xtp_gc_queue_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-gc-queue-stats)
