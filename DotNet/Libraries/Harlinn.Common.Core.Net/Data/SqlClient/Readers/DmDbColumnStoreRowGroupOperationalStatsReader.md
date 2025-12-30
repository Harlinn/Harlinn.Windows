# DmDbColumnStoreRowGroupOperationalStatsReader — reference

Overview

`DmDbColumnStoreRowGroupOperationalStatsReader` wraps `sys.dm_db_column_store_row_group_operational_stats` and exposes runtime operational counters for columnstore row groups.

Reader SQL

```
SELECT
  ddcsrgos.[object_id],
  ddcsrgos.[index_id],
  ddcsrgos.[partition_number],
  ddcsrgos.[row_group_id],
  ddcsrgos.[index_scan_count],
  ddcsrgos.[scan_count],
  ddcsrgos.[delete_buffer_scan_count],
  ddcsrgos.[row_group_lock_count],
  ddcsrgos.[row_group_lock_wait_count],
  ddcsrgos.[row_group_lock_wait_in_ms],
  ddcsrgos.[returned_row_count],
  ddcsrgos.[returned_aggregate_count],
  ddcsrgos.[returned_group_count],
  ddcsrgos.[input_groupby_row_count]
FROM
  [sys].[dm_db_column_store_row_group_operational_stats] ddcsrgos
```

Selected columns (property mapping and brief meaning)

- `object_id` ? `ObjectId` (int)
  - Object (table) id.

- `index_id` ? `IndexId` (int)
  - Index id for the columnstore index.

- `partition_number` ? `PartitionNumber` (int)
  - Partition number.

- `row_group_id` ? `RowGroupId` (int)
  - Row group id within the index.

- `index_scan_count` ? `IndexScanCount` (long)
  - Count of index-level scans involving this row group.

- `scan_count` ? `ScanCount` (long)
  - Count of scans directly against this row group.

- `delete_buffer_scan_count` ? `DeleteBufferScanCount` (long)
  - Number of scans against the delete buffer.

- `row_group_lock_count` ? `RowGroupLockCount` (long)
  - Number of row-group locks acquired.

- `row_group_lock_wait_count` ? `RowGroupLockWaitCount` (long)
  - Number of times acquisition of a row-group lock had to wait.

- `row_group_lock_wait_in_ms` ? `RowGroupLockWaitInMs` (long)
  - Aggregate wait time in milliseconds for row-group locks.

- `returned_row_count` ? `ReturnedRowCount` (long)
  - Number of rows returned from this row group.

- `returned_aggregate_count` ? `ReturnedAggregateCount` (long)
  - Number of aggregate results returned involving this row group.

- `returned_group_count` ? `ReturnedGroupCount` (long)
  - Number of groups produced from group-by operations.

- `input_groupby_row_count` ? `InputGroupbyRowCount` (long)
  - Count of input rows processed for group-by operations.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbColumnStoreRowGroupOperationalStatsDataType` objects.
