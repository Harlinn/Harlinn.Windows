# DmDbIndexUsageStatsReader — reference

Overview

`DmDbIndexUsageStatsReader` wraps the dynamic management view `sys.dm_db_index_usage_stats` and exposes usage counters for indexes at the database level. Use this data to evaluate index utilization (seeks, scans, lookups, updates) and to identify candidates for index maintenance or removal.

Reader SQL

```
SELECT
  ddius.[database_id],
  ddius.[object_id],
  ddius.[index_id],
  ddius.[user_seeks],
  ddius.[user_scans],
  ddius.[user_lookups],
  ddius.[user_updates],
  ddius.[last_user_seek],
  ddius.[last_user_scan],
  ddius.[last_user_lookup],
  ddius.[last_user_update],
  ddius.[system_seeks],
  ddius.[system_scans],
  ddius.[system_lookups],
  ddius.[system_updates],
  ddius.[last_system_seek],
  ddius.[last_system_scan],
  ddius.[last_system_lookup],
  ddius.[last_system_update]
FROM
  [sys].[dm_db_index_usage_stats] ddius
```

Columns (detailed)

- `database_id` ? `DatabaseId` (short)
  - ID of the database where the index usage is observed. Use `DB_NAME(database_id)` to get the database name.

- `object_id` ? `ObjectId` (int)
  - Object id (table or view) that contains the index. Translate with `OBJECT_NAME(object_id, database_id)` to get the object name.

- `index_id` ? `IndexId` (int)
  - Index identifier within the object (0 indicates heap).

- `user_seeks` ? `UserSeeks` (long)
  - Number of user-initiated seek operations that used the index. High value indicates targeted seek usage (good index utilization).

- `user_scans` ? `UserScans` (long)
  - Number of user-initiated index scan operations. High scan counts may indicate missing or non-selective indexes.

- `user_lookups` ? `UserLookups` (long)
  - Number of user-initiated lookups (key lookups) performed by the engine using this index to retrieve additional columns.

- `user_updates` ? `UserUpdates` (long)
  - Number of user-initiated updates that modified the index. High update counts increase maintenance cost for the index.

- `last_user_seek` ? `LastUserSeek` (DateTime?)
  - Timestamp of the last user seek against this index.

- `last_user_scan` ? `LastUserScan` (DateTime?)
  - Timestamp of the last user scan.

- `last_user_lookup` ? `LastUserLookup` (DateTime?)
  - Timestamp of the last user lookup.

- `last_user_update` ? `LastUserUpdate` (DateTime?)
  - Timestamp of the last user update affecting the index.

- `system_seeks` ? `SystemSeeks` (long)
  - Number of internal/system-initiated seeks (e.g., by the optimizer or background processes).

- `system_scans` ? `SystemScans` (long)
  - Number of internal scans.

- `system_lookups` ? `SystemLookups` (long)
  - Number of internal lookups.

- `system_updates` ? `SystemUpdates` (long)
  - Number of internal updates to the index.

- `last_system_seek` ? `LastSystemSeek` (DateTime?)
  - Timestamp of the last system seek.

- `last_system_scan` ? `LastSystemScan` (DateTime?)
  - Timestamp of the last system scan.

- `last_system_lookup` ? `LastSystemLookup` (DateTime?)
  - Timestamp of the last system lookup.

- `last_system_update` ? `LastSystemUpdate` (DateTime?)
  - Timestamp of the last system update.

Usage notes

- Counters are cumulative since the last SQL Server restart or since statistics reset; interpret relative differences over time.
- Combine `dm_db_index_usage_stats` with `sys.indexes` and `sys.dm_db_partition_stats` to calculate per-index efficiency and storage cost.

Example

The following example shows how to query and display a human-readable index usage report for the current database:

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbIndexUsageStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var usage = new DmDbIndexUsageStatsReader(reader, ownsReader: false);
while (usage.Read())
{
    Console.WriteLine($"DB: {usage.DatabaseId}, Object: {usage.ObjectId}, Index: {usage.IndexId}");
    Console.WriteLine($"  User seeks: {usage.UserSeeks}, scans: {usage.UserScans}, lookups: {usage.UserLookups}, updates: {usage.UserUpdates}");
    Console.WriteLine($"  Last user seek: {usage.LastUserSeek}");
    Console.WriteLine($"  System seeks: {usage.SystemSeeks}, system scans: {usage.SystemScans}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-index-usage-stats
