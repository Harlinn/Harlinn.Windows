# DmDbMissingIndexGroupStatsQueryReader — reference

Overview

`DmDbMissingIndexGroupStatsQueryReader` wraps `sys.dm_db_missing_index_group_stats_query` and provides per-query statistics for missing index recommendation groups. This combines query-level counters and cost/impact estimates useful for prioritizing index creation.

Reader SQL

```
SELECT
  ddmigsq.[group_handle],
  ddmigsq.[query_hash],
  ddmigsq.[query_plan_hash],
  ddmigsq.[last_sql_handle],
  ddmigsq.[last_statement_start_offset],
  ddmigsq.[last_statement_end_offset],
  ddmigsq.[last_statement_sql_handle],
  ddmigsq.[user_seeks],
  ddmigsq.[user_scans],
  ddmigsq.[last_user_seek],
  ddmigsq.[last_user_scan],
  ddmigsq.[avg_total_user_cost],
  ddmigsq.[avg_user_impact],
  ddmigsq.[system_seeks],
  ddmigsq.[system_scans],
  ddmigsq.[last_system_seek],
  ddmigsq.[last_system_scan],
  ddmigsq.[avg_total_system_cost],
  ddmigsq.[avg_system_impact]
FROM
  [sys].[dm_db_missing_index_group_stats_query] ddmigsq
```

Columns (detailed)

- `group_handle` ? `GroupHandle` (int)
  - Identifier for the missing index group this query belongs to (join with group stats).

- `query_hash` ? `QueryHash` (byte[])
  - Hash of the query text used to group similar queries.

- `query_plan_hash` ? `QueryPlanHash` (byte[])
  - Hash of the query execution plan.

- `last_sql_handle` ? `LastSqlHandle` (byte[])
  - SQL handle of the last compiled batch or module that triggered the recommendation.

- `last_statement_start_offset` / `last_statement_end_offset` ? offsets within the batch for the statement that caused the recommendation.

- `last_statement_sql_handle` ? `LastStatementSqlHandle` (byte[]?)
  - SQL handle for the specific statement if available.

- `user_seeks` / `user_scans` ? counts of user-initiated seeks and scans for the related query (long)

- `last_user_seek` / `last_user_scan` ? last times these operations happened (DateTime?)

- `avg_total_user_cost` ? `AvgTotalUserCost` (double?)
  - Average estimated total query cost for user executions; higher values indicate expensive queries that could benefit from indexing.

- `avg_user_impact` ? `AvgUserImpact` (double)
  - Estimated per-query user impact metric (higher => larger improvement expected from index).

- `system_seeks` / `system_scans` / `last_system_seek` / `last_system_scan` ? same as user counters but for system-initiated executions.

- `avg_total_system_cost` / `avg_system_impact` ? average cost and impact for system executions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMissingIndexGroupStatsQueryReader.Sql;
using var reader = cmd.ExecuteReader();
var qReader = new DmDbMissingIndexGroupStatsQueryReader(reader, ownsReader: false);
while (qReader.Read())
{
    Console.WriteLine($"Group: {qReader.GroupHandle}, QueryHash: {BitConverter.ToString(qReader.QueryHash)}");
    Console.WriteLine($" Avg user cost: {qReader.AvgTotalUserCost}, Impact: {qReader.AvgUserImpact}");
    Console.WriteLine($" User seeks/scans: {qReader.UserSeeks}/{qReader.UserScans}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-missing-index-group-stats-query
