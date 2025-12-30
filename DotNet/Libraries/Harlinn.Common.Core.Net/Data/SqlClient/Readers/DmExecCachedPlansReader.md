# DmExecCachedPlansReader — reference

Overview

`DmExecCachedPlansReader` wraps `sys.dm_exec_cached_plans` and exposes information about cached execution plans in the server plan cache. It includes memory addresses, sizes and reference counters helpful to analyze plan cache usage.

Reader SQL

```
SELECT
  decp.[Bucketid],
  decp.[Refcounts],
  decp.[Usecounts],
  decp.[size_in_bytes],
  decp.[memory_object_address],
  decp.[Cacheobjtype],
  decp.[Objtype],
  decp.[plan_handle],
  decp.[pool_id],
  decp.[parent_plan_handle]
FROM
  [sys].[dm_exec_cached_plans] decp
```

Columns (interpretation)

- `Bucketid` ? `Bucketid` (int)
  - Internal bucket id for the cache map.

- `Refcounts` ? `Refcounts` (int)
  - Reference count for the cached object. Higher suggests more active references preventing eviction.

- `Usecounts` ? `Usecounts` (int)
  - Use count showing how often the plan is used.

- `size_in_bytes` ? `SizeInBytes` (int)
  - Plan size in bytes. Useful to identify large plans consuming cache memory.

- `memory_object_address` ? `MemoryObjectAddress` (binary)
  - Internal memory address of the cached object.

- `Cacheobjtype` ? `Cacheobjtype` (string)
  - Cache object type (e.g., Compiled Plan, Bound Tree).

- `Objtype` ? `Objtype` (string)
  - Object type (e.g., Adhoc, Prepared, Proc, View).

- `plan_handle` ? `PlanHandle` (binary)
  - Opaque plan handle you can pass to other DMVs (e.g., `sys.dm_exec_query_plan`) to retrieve plan details.

- `pool_id` ? `PoolId` (int)
  - Memory pool id where the plan is allocated.

- `parent_plan_handle` ? `ParentPlanHandle` (binary?)
  - Parent plan handle if applicable (e.g., for child plans).

Usage notes

- Use `plan_handle` with `sys.dm_exec_query_plan(plan_handle)` or `sys.dm_exec_sql_text(plan_handle)` to get plan shape and SQL text.
- Large `SizeInBytes` entries with low `Usecounts` are candidates for eviction to free memory.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecCachedPlansReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecCachedPlansReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Plan size: {r.SizeInBytes} bytes Uses: {r.Usecounts} Refs: {r.Refcounts} Type: {r.Objtype}");
    Console.WriteLine($" PlanHandle: {BitConverter.ToString(r.PlanHandle)} Parent: { (r.ParentPlanHandle != null ? BitConverter.ToString(r.ParentPlanHandle) : "(none)") }");
}
```

See also:

- [sys.dm_exec_cached_plans](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-cached-plans)
