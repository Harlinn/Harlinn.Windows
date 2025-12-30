# DmExecQueryParallelWorkersReader — reference

Overview

`DmExecQueryParallelWorkersReader` wraps `sys.dm_exec_query_parallel_workers` and reports per-node worker availability and usage for parallel query execution. Use this view to inspect worker thread capacity and utilization across nodes.

Reader SQL

```
SELECT
  deqpw.[node_id],
  deqpw.[scheduler_count],
  deqpw.[max_worker_count],
  deqpw.[reserved_worker_count],
  deqpw.[free_worker_count],
  deqpw.[used_worker_count]
FROM
  [sys].[dm_exec_query_parallel_workers] deqpw
```

Columns and interpretation

- `node_id` ? `NodeId` (int)
  - Identifier for the node (NUMA node or compute node) where workers are provisioned.

- `scheduler_count` ? `SchedulerCount` (int)
  - Number of schedulers available on the node. Correlates with logical CPUs used for scheduling worker threads.

- `max_worker_count` ? `MaxWorkerCount` (int)
  - Maximum number of worker threads the node can allocate for parallel queries.

- `reserved_worker_count` ? `ReservedWorkerCount` (int)
  - Number of worker threads reserved for currently running queries. Reserved threads are allocated but may not be actively used yet.

- `free_worker_count` ? `FreeWorkerCount` (int)
  - Number of worker threads currently free/available for new parallel work.

- `used_worker_count` ? `UsedWorkerCount` (int)
  - Number of worker threads currently used by queries on the node.

How to interpret

- Compare `UsedWorkerCount` against `MaxWorkerCount` to detect contention for parallel workers.
- High `ReservedWorkerCount` with low `FreeWorkerCount` indicates parallelism pressure; investigate queries with high DOP or many parallel workers.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryParallelWorkersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecQueryParallelWorkersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Node {r.NodeId}: schedulers={r.SchedulerCount} maxWorkers={r.MaxWorkerCount} used={r.UsedWorkerCount} free={r.FreeWorkerCount}");
}
```

See also:

- [sys.dm_exec_query_parallel_workers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-parallel-workers)
