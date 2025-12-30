# QueryStorePlanReader — reference

Overview

`QueryStorePlanReader` wraps `sys.query_store_plan` and returns stored plans captured by the Query Store, including plan characteristics and forcing information.

Reader SQL

```
SELECT
  qsp.[plan_id],
  qsp.[query_id],
  qsp.[plan_group_id],
  qsp.[engine_version],
  qsp.[compatibility_level],
  qsp.[query_plan_hash],
  qsp.[query_plan],
  qsp.[is_online_index_plan],
  qsp.[is_trivial_plan],
  qsp.[is_parallel_plan],
  qsp.[is_forced_plan],
  qsp.[is_natively_compiled],
  qsp.[force_failure_count],
  qsp.[last_force_failure_reason],
  qsp.[last_force_failure_reason_desc],
  qsp.[count_compiles],
  qsp.[initial_compile_start_time],
  qsp.[last_compile_start_time],
  qsp.[last_execution_time],
  qsp.[avg_compile_duration],
  qsp.[last_compile_duration],
  qsp.[plan_forcing_type],
  qsp.[plan_forcing_type_desc]
FROM
  [sys].[query_store_plan] qsp
```

Columns and interpretation

- `plan_id`, `query_id` — unique identifiers for the plan and parent query in Query Store.
- `plan_group_id` — optional group id relating similar plans.
- `engine_version` — engine/optimizer version capturing the plan.
- `compatibility_level` — database compatibility level when plan was compiled.
- `query_plan_hash` — binary hash for the plan structure.
- `query_plan` — XML or text representation of the plan (nullable).
- Flags: `is_online_index_plan`, `is_trivial_plan`, `is_parallel_plan`, `is_forced_plan`, `is_natively_compiled`.
- Forcing metadata: `force_failure_count`, `last_force_failure_reason`, `last_force_failure_reason_desc`, `plan_forcing_type`, `plan_forcing_type_desc`.
- Compile/execution metrics: `count_compiles`, `initial_compile_start_time`, `last_compile_start_time`, `last_execution_time`, `avg_compile_duration`, `last_compile_duration`.

How to interpret

- Query Store retains plan artifacts and statistics; use this view to retrieve the plan XML and understand whether a plan was forced (and why forcing may have failed).

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStorePlanReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryStorePlanReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"PlanId:{r.PlanId} QueryId:{r.QueryId} Forced:{r.IsForcedPlan} Parallel:{r.IsParallelPlan} Compiled:{r.CountCompiles}");
}
```

See also:

- [sys.query_store_plan](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-plan)
