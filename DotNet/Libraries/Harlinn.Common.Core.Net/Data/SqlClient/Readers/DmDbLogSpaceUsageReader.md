# DmDbLogSpaceUsageReader — reference

Overview

`DmDbLogSpaceUsageReader` wraps `sys.dm_db_log_space_usage` and exposes log file space usage metrics for each database, including total size, used size, and the amount of log generated since last backup.

Reader SQL

```
SELECT
  ddlsu.[database_id],
  ddlsu.[total_log_size_in_bytes],
  ddlsu.[used_log_space_in_bytes],
  ddlsu.[used_log_space_in_percent],
  ddlsu.[log_space_in_bytes_since_last_backup]
FROM
  [sys].[dm_db_log_space_usage] ddlsu
```

Columns (detailed)

- `database_id` ? `DatabaseId` (int?)
  - Database identifier for which the log space metrics are reported.

- `total_log_size_in_bytes` ? `TotalLogSizeInBytes` (long?)
  - Total size of the transaction log file(s) for the database in bytes.

- `used_log_space_in_bytes` ? `UsedLogSpaceInBytes` (long?)
  - Bytes currently used in the log for active log records.

- `used_log_space_in_percent` ? `UsedLogSpaceInPercent` (float?)
  - Percentage of the log file that is currently used.

- `log_space_in_bytes_since_last_backup` ? `LogSpaceInBytesSinceLastBackup` (long?)
  - Amount of log generated (in bytes) since the last log backup. Useful to estimate growth and backup frequency needs.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbLogSpaceUsageReader.Sql;
using var reader = cmd.ExecuteReader();
var logReader = new DmDbLogSpaceUsageReader(reader, ownsReader: false);
while (logReader.Read())
{
    Console.WriteLine($"DatabaseId: {logReader.DatabaseId}");
    Console.WriteLine($" Total log size: {logReader.TotalLogSizeInBytes ?? 0:N0} bytes");
    Console.WriteLine($" Used log: {logReader.UsedLogSpaceInBytes ?? 0:N0} bytes ({logReader.UsedLogSpaceInPercent:P})");
    Console.WriteLine($" Log generated since last backup: {logReader.LogSpaceInBytesSinceLastBackup ?? 0:N0} bytes");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-log-space-usage
