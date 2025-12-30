# DmExecQueryResourceSemaphoresReader — reference

Overview

`DmExecQueryResourceSemaphoresReader` wraps `sys.dm_exec_query_resource_semaphores` and provides memory semaphore state for query resource groups/pools. It shows current memory targets, grants, usage and waiting counts.

Reader SQL

```
SELECT
  deqrs.[resource_semaphore_id],
  deqrs.[target_memory_kb],
  deqrs.[max_target_memory_kb],
  deqrs.[total_memory_kb],
  deqrs.[available_memory_kb],
  deqrs.[granted_memory_kb],
  deqrs.[used_memory_kb],
  deqrs.[grantee_count],
  deqrs.[waiter_count],
  deqrs.[timeout_error_count],
  deqrs.[forced_grant_count],
  deqrs.[pool_id]
FROM
  [sys].[dm_exec_query_resource_semaphores] deqrs
```

Columns and interpretation

- `resource_semaphore_id` ? internal semaphore id.
- `target_memory_kb` / `max_target_memory_kb` ? target and maximum target memory in KB for the resource group.
- `total_memory_kb` ? total memory allocated for the semaphore.
- `available_memory_kb` ? currently available memory.
- `granted_memory_kb` ? memory currently granted to requests.
- `used_memory_kb` ? memory currently used by running queries.
- `grantee_count` ? number of requests that have been granted memory.
- `waiter_count` ? number of waiting requests queued for grants.
- `timeout_error_count` ? number of requests that timed out waiting for memory grants.
- `forced_grant_count` ? number of forced grants issued to prevent starvation.
- `pool_id` ? ID of the pool/resource group this semaphore belongs to.

How to interpret

- Low `available_memory_kb` with non-zero `waiter_count` indicates memory pressure and likely delays for queries requiring grants.
- `timeout_error_count` is a critical indicator of failing grant requests.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryResourceSemaphoresReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecQueryResourceSemaphoresReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Sem {s.ResourceSemaphoreId} Pool {s.PoolId} TargetKB:{s.TargetMemoryKb} AvailableKB:{s.AvailableMemoryKb} GrantedKB:{s.GrantedMemoryKb} Waiters:{s.WaiterCount}");
}
```

See also:

- [sys.dm_exec_query_resource_semaphores](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-resource-semaphores)
