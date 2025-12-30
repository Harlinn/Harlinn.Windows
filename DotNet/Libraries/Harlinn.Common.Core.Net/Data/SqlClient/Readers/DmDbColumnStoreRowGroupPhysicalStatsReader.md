# DmDbColumnStoreRowGroupPhysicalStatsReader — reference

Overview

`DmDbColumnStoreRowGroupPhysicalStatsReader` wraps `sys.dm_db_column_store_row_group_physical_stats` and exposes physical and lifecycle stats for columnstore row groups.

Reader SQL

```
SELECT
  ddcsrgps.[object_id],
  ddcsrgps.[index_id],
  ddcsrgps.[partition_number],
  ddcsrgps.[row_group_id],
  ddcsrgps.[delta_store_hobt_id],
  ddcsrgps.[State],
  ddcsrgps.[state_desc],
  ddcsrgps.[total_rows],
  ddcsrgps.[deleted_rows],
  ddcsrgps.[size_in_bytes],
  ddcsrgps.[trim_reason],
  ddcsrgps.[trim_reason_desc],
  ddcsrgps.[transition_to_compressed_state],
  ddcsrgps.[transition_to_compressed_state_desc],
  ddcsrgps.[has_vertipaq_optimization],
  ddcsrgps.[Generation],
  ddcsrgps.[created_time],
  ddcsrgps.[closed_time]
FROM
  [sys].[dm_db_column_store_row_group_physical_stats] ddcsrgps
```

Selected columns (property mapping and brief meaning)

- `object_id` ? `ObjectId` (int?) — object containing the row group.
- `index_id` ? `IndexId` (int?) — index id for the columnstore index.
- `partition_number` ? `PartitionNumber` (int?) — partition number.
- `row_group_id` ? `RowGroupId` (int?) — row group id.
- `delta_store_hobt_id` ? `DeltaStoreHobtId` (long?) — HOBT id for the delta store backing this row group (if applicable).
- `State` ? `State` (byte?) — numeric state code.
- `state_desc` ? `StateDesc` (string) — textual state description.
- `total_rows` ? `TotalRows` (long?) — total rows in the row group.
- `deleted_rows` ? `DeletedRows` (long?) — number of logically deleted rows.
- `size_in_bytes` ? `SizeInBytes` (long?) — size of the row group on disk.
- `trim_reason` ? `TrimReason` (byte?) — code indicating why a trim occurred.
- `trim_reason_desc` ? `TrimReasonDesc` (string?) — description of the trim reason.
- `transition_to_compressed_state` ? `TransitionToCompressedState` (byte?) — code for transition action.
- `transition_to_compressed_state_desc` ? `TransitionToCompressedStateDesc` (string?) — description of transition.
- `has_vertipaq_optimization` ? `HasVertipaqOptimization` (bool?) — whether VertiPaq optimizations applied.
- `Generation` ? `Generation` (long?) — generation number for the row group.
- `created_time` ? `CreatedTime` (DateTime?) — when row group was created.
- `closed_time` ? `ClosedTime` (DateTime?) — when row group was closed.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbColumnStoreRowGroupPhysicalStatsDataType` objects.
