# DmTranPersistentVersionStoreStatsReader — reference

Overview

`DmTranPersistentVersionStoreStatsReader` wraps `sys.dm_tran_persistent_version_store_stats` and reports statistics about the persistent version store for a database, including size and cleaner activity.

Reader SQL

```
SELECT
  dtpvss.[database_id],
  dtpvss.[pvs_filegroup_id],
  dtpvss.[persistent_version_store_size_kb],
  dtpvss.[online_index_version_store_size_kb],
  dtpvss.[current_aborted_transaction_count],
  dtpvss.[oldest_active_transaction_id],
  dtpvss.[oldest_aborted_transaction_id],
  dtpvss.[min_transaction_timestamp],
  dtpvss.[online_index_min_transaction_timestamp],
  dtpvss.[secondary_low_water_mark],
  dtpvss.[offrow_version_cleaner_start_time],
  dtpvss.[offrow_version_cleaner_end_time],
  dtpvss.[aborted_version_cleaner_start_time],
  dtpvss.[aborted_version_cleaner_end_time],
  dtpvss.[pvs_off_row_page_skipped_low_water_mark],
  dtpvss.[pvs_off_row_page_skipped_transaction_not_cleaned],
  dtpvss.[pvs_off_row_page_skipped_oldest_active_xdesid],
  dtpvss.[pvs_off_row_page_skipped_min_useful_xts],
  dtpvss.[pvs_off_row_page_skipped_oldest_snapshot]
FROM
  [sys].[dm_tran_persistent_version_store_stats] dtpvss
```

Columns and interpretation

- `database_id` — database id for which stats apply.
- `pvs_filegroup_id` — filegroup id containing the persistent version store.
- `persistent_version_store_size_kb` — size of the persistent version store in KB.
- `online_index_version_store_size_kb` — size used by online index operations.
- `current_aborted_transaction_count` — count of aborted transactions currently tracked.
- `oldest_active_transaction_id`, `oldest_aborted_transaction_id` — ids of oldest active and aborted transactions.
- `min_transaction_timestamp` — minimum transaction timestamp present in the store.
- `online_index_min_transaction_timestamp` — min timestamp for online index operations.
- `secondary_low_water_mark` — secondary low water mark used in cleanup calculations.
- `offrow_version_cleaner_start_time` / `end_time` — timestamps for the off-row version cleaner activity.
- `aborted_version_cleaner_start_time` / `end_time` — timestamps for aborted version cleaner activity.
- `pvs_off_row_page_skipped_*` fields — counters and markers for pages skipped during cleaning due to various conditions.

How to interpret

- Use sizes and timestamps to assess version store growth and cleanup health; high sizes or skipped pages indicate cleanup issues.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranPersistentVersionStoreStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranPersistentVersionStoreStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} PVSSizeKB:{r.PersistentVersionStoreSizeKb} CurrentAborted:{r.CurrentAbortedTransactionCount} OldestActive:{r.OldestActiveTransactionId}");
}
```

See also:

- [sys.dm_tran_persistent_version_store_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-persistent-version-store-stats)
