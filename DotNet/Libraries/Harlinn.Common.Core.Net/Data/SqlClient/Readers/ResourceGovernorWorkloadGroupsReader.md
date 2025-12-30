# ResourceGovernorWorkloadGroupsReader

Overview

`ResourceGovernorWorkloadGroupsReader` wraps `sys.resource_governor_workload_groups` and exposes workload group settings used by Resource Governor.

Reader SQL

```
SELECT
  rgwg.[group_id],
  rgwg.[Name],
  rgwg.[Importance],
  rgwg.[request_max_memory_grant_percent],
  rgwg.[request_max_cpu_time_sec],
  rgwg.[request_memory_grant_timeout_sec],
  rgwg.[max_dop],
  rgwg.[group_max_requests],
  rgwg.[pool_id],
  rgwg.[external_pool_id],
  rgwg.[request_max_memory_grant_percent_numeric]
FROM
  [sys].[resource_governor_workload_groups] rgwg
```

Columns and interpretation

- `group_id` (int): Identifier of the workload group.
- `Name` (string): Name of the workload group.
- `Importance` (string): Importance level (e.g., High/Medium/Low) used by scheduler.
- `request_max_memory_grant_percent` (int): Max memory grant percent for requests (integer representation).
- `request_max_cpu_time_sec` (int): Max CPU time in seconds for requests.
- `request_memory_grant_timeout_sec` (int): Memory grant timeout in seconds.
- `max_dop` (int): Max degree of parallelism allowed for queries in the group.
- `group_max_requests` (int): Max concurrent requests for the group.
- `pool_id` (int): Associated internal pool id.
- `external_pool_id` (int): Associated external pool id (if using external pools).
- `request_max_memory_grant_percent_numeric` (double): Numeric representation of memory grant percent with decimals.

How to interpret

- Workload groups map sessions/requests to pools and control per-request resource limits.
- Use `Importance` and `request_max_*` columns to spot restrictive settings.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorWorkloadGroupsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorWorkloadGroupsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Group:{r.Name} Importance:{r.Importance} Pool:{r.PoolId}");
```

See also:

- [sys.resource_governor_workload_groups](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-workload-groups)

