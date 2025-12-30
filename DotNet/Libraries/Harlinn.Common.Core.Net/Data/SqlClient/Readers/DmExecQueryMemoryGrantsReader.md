# DmExecQueryMemoryGrantsReader — reference

Overview

`DmExecQueryMemoryGrantsReader` wraps `sys.dm_exec_query_memory_grants` and reports memory grant and queueing information for queries requesting memory for execution. It is useful to diagnose memory grant waits, query memory usage, and worker reservations.

Reader SQL

```
SELECT
  deqmg.[session_id],
  deqmg.[request_id],
  deqmg.[scheduler_id],
  deqmg.[Dop],
  deqmg.[request_time],
  deqmg.[grant_time],
  deqmg.[requested_memory_kb],
  deqmg.[granted_memory_kb],
  deqmg.[required_memory_kb],
  deqmg.[used_memory_kb],
  deqmg.[max_used_memory_kb],
  deqmg.[query_cost],
  deqmg.[timeout_sec],
  deqmg.[resource_semaphore_id],
  deqmg.[queue_id],
  deqmg.[wait_order],
  deqmg.[is_next_candidate],
  deqmg.[wait_time_ms],
  deqmg.[plan_handle],
  deqmg.[sql_handle],
  deqmg.[group_id],
  deqmg.[pool_id],
  deqmg.[is_small],
  deqmg.[ideal_memory_kb],
  deqmg.[reserved_worker_count],
  deqmg.[used_worker_count],
  deqmg.[max_used_worker_count],
  deqmg.[reserved_node_bitmap]
FROM
  [sys].[dm_exec_query_memory_grants] deqmg
```

Columns and interpretation

- `session_id`, `request_id`, `scheduler_id` ? identifiers for session/request and scheduler.
- `Dop` ? degree of parallelism requested/used.
- `request_time`, `grant_time` ? timestamps for request and when memory was granted.
- `requested_memory_kb` ? memory requested for query (KB).
- `granted_memory_kb` ? memory actually granted to the query (KB).
- `required_memory_kb` ? minimum required memory for the query to run without spilling.
- `used_memory_kb`, `max_used_memory_kb` ? current and historical peak memory used by the query.
- `query_cost` ? optimizer estimated cost used in grant decisions.
- `timeout_sec` ? timeout for memory grant request.
- `resource_semaphore_id`, `queue_id`, `wait_order` ? internal queue/semaphore and ordering info for waiting grants.
- `is_next_candidate` ? whether this request is next to receive grant when memory frees up.
- `wait_time_ms` ? how long the request waited for grant (ms).
- `plan_handle` / `sql_handle` ? handles to retrieve plan/text.
- `group_id` / `pool_id` ? group and pool association of the grant.
- `is_small` ? indicator if query was considered small (special handling).
- `ideal_memory_kb` ? ideal memory amount for optimal execution.
- `reserved_worker_count`, `used_worker_count`, `max_used_worker_count` ? worker thread allocation metrics reserved/used by the query.
- `reserved_node_bitmap` ? bitmap representing reserved nodes for distributed/scale-out execution.

How to interpret

- If `granted_memory_kb` < `required_memory_kb`, query may spill to disk causing degraded performance. Check spills in `dm_exec_procedure_stats` or `dm_exec_query_stats`.
- Long `wait_time_ms` values and non-zero `queue_id` indicate memory pressure; consider increasing server memory or adjusting workload.
- `is_next_candidate` true indicates the request will likely get memory next.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryMemoryGrantsReader.Sql;
using var rdr = cmd.ExecuteReader();
var g = new DmExecQueryMemoryGrantsReader(rdr, ownsReader:false);
while (g.Read())
{
    Console.WriteLine($"Session {g.SessionId} Request {g.RequestId} RequestedKB: {g.RequestedMemoryKb} GrantedKB: {g.GrantedMemoryKb} RequiredKB: {g.RequiredMemoryKb}");
    Console.WriteLine($" UsedKB/MaxKB: {g.UsedMemoryKb}/{g.MaxUsedMemoryKb} Wait(ms): {g.WaitTimeMs} IsNext: {g.IsNextCandidate}");
}
```

See also:

- [sys.dm_exec_query_memory_grants](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-memory-grants)
