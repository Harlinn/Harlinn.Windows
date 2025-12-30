# DmDbXtpIndexStatsReader — reference

Overview

`DmDbXtpIndexStatsReader` wraps `sys.dm_db_xtp_index_stats` and provides runtime statistics for indexes on memory-optimized objects, including scan and phantom scan metrics. Use these counters to assess index activity and ghost/expiration behavior.

Reader SQL

```
SELECT
  ddxis.[object_id],
  ddxis.[xtp_object_id],
  ddxis.[index_id],
  ddxis.[scans_started],
  ddxis.[scans_retries],
  ddxis.[rows_returned],
  ddxis.[rows_touched],
  ddxis.[rows_expiring],
  ddxis.[rows_expired],
  ddxis.[rows_expired_removed],
  ddxis.[phantom_scans_started],
  ddxis.[phantom_scans_retries],
  ddxis.[phantom_rows_touched],
  ddxis.[phantom_expiring_rows_encountered],
  ddxis.[phantom_expired_removed_rows_encountered],
  ddxis.[phantom_expired_rows_removed],
  ddxis.[object_address]
FROM
  [sys].[dm_db_xtp_index_stats] ddxis
```

Columns (how to interpret)

- `object_id` / `xtp_object_id` / `index_id` ? identity of the object and index.

- `scans_started` ? count of index scans initiated. Use to measure read activity.

- `scans_retries` ? number of times scans had to retry (e.g., due to concurrent modifications); high counts may indicate contention.

- `rows_returned` ? total rows returned to query operators via this index.

- `rows_touched` ? rows examined/touched during scans; ratio rows_touched/rows_returned indicates selectivity.

- `rows_expiring` / `rows_expired` / `rows_expired_removed` ? track expiration-based lifecycle events for rows with sysdatetime-based expiration.

- Phantom metrics (`phantom_scans_*`, `phantom_rows_touched`, `phantom_expiring_rows_encountered`, etc.) ? related to phantom avoidance/handling during scans in presence of concurrent deletes/expiration; review to understand runtime overhead for phantom handling.

- `object_address` ? binary internal address of the object; typically used for low-level correlation.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpIndexStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpIndexStatsReader(reader, ownsReader: false);
while (s.Read())
{
    Console.WriteLine($"Obj {s.ObjectId} Id {s.IndexId} Scans: {s.ScansStarted} Retries: {s.ScansRetries}");
    Console.WriteLine($" Rows returned/touched: {s.RowsReturned}/{s.RowsTouched} Expired: {s.RowsExpired}");
}
```

See also:

- [sys.dm_db_xtp_index_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-index-stats)
