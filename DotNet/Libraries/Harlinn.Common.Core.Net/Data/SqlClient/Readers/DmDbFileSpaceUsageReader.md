# DmDbFileSpaceUsageReader — reference

Overview

`DmDbFileSpaceUsageReader` wraps `sys.dm_db_file_space_usage` and exposes information about file and extent allocation and usage within a database.

Reader SQL

```
SELECT
  ddfsu.[database_id],
  ddfsu.[file_id],
  ddfsu.[filegroup_id],
  ddfsu.[total_page_count],
  ddfsu.[allocated_extent_page_count],
  ddfsu.[unallocated_extent_page_count],
  ddfsu.[version_store_reserved_page_count],
  ddfsu.[user_object_reserved_page_count],
  ddfsu.[internal_object_reserved_page_count],
  ddfsu.[mixed_extent_page_count],
  ddfsu.[modified_extent_page_count]
FROM
  [sys].[dm_db_file_space_usage] ddfsu
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int?)
  - Database identifier.

- `file_id` ? `FileId` (short?)
  - File id within database.

- `filegroup_id` ? `FilegroupId` (short?)
  - Filegroup id the file belongs to.

- `total_page_count` ? `TotalPageCount` (long?)
  - Total pages in file.

- `allocated_extent_page_count` ? `AllocatedExtentPageCount` (long?)
  - Pages allocated in extents.

- `unallocated_extent_page_count` ? `UnallocatedExtentPageCount` (long?)
  - Pages available/unallocated.

- `version_store_reserved_page_count` ? `VersionStoreReservedPageCount` (long?)
  - Pages reserved for version store (tempdb usage for row versioning).

- `user_object_reserved_page_count` ? `UserObjectReservedPageCount` (long?)
  - Pages reserved for user objects.

- `internal_object_reserved_page_count` ? `InternalObjectReservedPageCount` (long?)
  - Pages reserved for internal objects.

- `mixed_extent_page_count` ? `MixedExtentPageCount` (long?)
  - Pages in mixed extents.

- `modified_extent_page_count` ? `ModifiedExtentPageCount` (long?)
  - Pages where data has been modified.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbFileSpaceUsageDataType` objects.
