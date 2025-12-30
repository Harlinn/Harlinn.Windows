# ColumnStoreRowGroupsReader — reference

Overview

`ColumnStoreRowGroupsReader` wraps `sys.column_store_row_groups` and exposes metadata about row groups in columnstore indexes.

Reader SQL

```
SELECT scsrg.[object_id]
      ,scsrg.[index_id]
      ,scsrg.[partition_number]
      ,scsrg.[row_group_id]
      ,scsrg.[delta_store_hobt_id]
      ,scsrg.[state]
      ,scsrg.[state_description]
      ,scsrg.[total_rows]
      ,scsrg.[deleted_rows]
      ,scsrg.[size_in_bytes]
FROM [sys].[column_store_row_groups] scsrg
```

Selected columns (method mapping and brief meaning)

- `object_id` ? `GetObjectId()` (int): Object id that contains the columnstore index.
- `index_id` ? `GetIndexId()` (int): Index id containing the row group.
- `partition_number` ? `GetPartitionNumber()` (int): Partition number within index.
- `row_group_id` ? `GetRowGroupId()` (int): Row group identifier.
- `delta_store_hobt_id` ? `GetDeltaStoreHobtId()` (long?): HOBT id for delta store (may be NULL).
- `state` ? `GetState()` (byte): Numeric state code of the row group.
- `state_description` ? `GetStateDescription()` (string?): Human readable state description.
- `total_rows` ? `GetTotalRows()` (long): Number of rows in the row group.
- `deleted_rows` ? `GetDeletedRows()` (long): Number of deleted rows in the row group.
- `size_in_bytes` ? `GetSizeInBytes()` (long): Size on disk in bytes.

Helpers

- `GetColumnStoreRowGroup()` returns a `ColumnStoreRowGroup` instance populated from current row.
- `GetColumnStoreRowGroups()` reads all rows and returns a list.
