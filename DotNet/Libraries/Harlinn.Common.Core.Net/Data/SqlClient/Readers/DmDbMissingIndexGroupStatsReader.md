# DmDbMissingIndexGroupStatsReader — reference

Overview

`DmDbMissingIndexGroupStatsReader` wraps `sys.dm_db_missing_index_group_stats` and provides aggregated statistics for missing index groups. Use this to prioritize index creation by combined cost and usage metrics.

Reader SQL

```
SELECT
  ddmigs.[group_handle],
  ddmigs.[unique_compiles],
  ddmigs.[user_seeks],
  ddmigs.[user_scans],
  ddmigs.[last_user_seek],
  ddmigs.[last_user_scan],
  ddmigs.[avg_total_user_cost],
  ddmigs.[avg_user_impact],
  ddmigs.[system_seeks],
  ddmigs.[system_scans],
  ddmigs.[last_system_seek],
  ddmigs.[last_system_scan],
  ddmigs.[avg_total_system_cost],
  ddmigs.[avg_system_impact]
FROM
  [sys].[dm_db_missing_index_group_stats] ddmigs
```

Columns (detailed)

- `group_handle` ? `GroupHandle` (int)
  - Identifier of the missing index group.

- `unique_compiles` ? `UniqueCompiles` (long?)
  - Number of unique plan compilations associated with queries in the group, indicating compilation overhead.

- `user_seeks` / `user_scans` ? `UserSeeks` / `UserScans` (long?)
  - Aggregate counts of user attempts that could have benefited from an index.

- `last_user_seek` / `last_user_scan` ? timestamp of last user activity.

- `avg_total_user_cost` ? `AvgTotalUserCost` (double?)
  - Average estimated total cost per user execution across queries in this group.

- `avg_user_impact` ? `AvgUserImpact` (double?)
  - Estimated average improvement impact for user executions if the index is created.

- `system_seeks` / `system_scans` / `last_system_seek` / `last_system_scan` ? same counters for system-initiated operations.

- `avg_total_system_cost` / `avg_system_impact` ? average cost and impact for system executions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMissingIndexGroupStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var gReader = new DmDbMissingIndexGroupStatsReader(reader, ownsReader: false);
while (gReader.Read())
{
    Console.WriteLine($"Group: {gReader.GroupHandle}, Unique compiles: {gReader.UniqueCompiles}");
    Console.WriteLine($" User seeks/scans: {gReader.UserSeeks}/{gReader.UserScans} Avg impact: {gReader.AvgUserImpact}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-missing-index-group-stats
