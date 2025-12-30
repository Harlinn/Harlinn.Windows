# DmColumnStoreObjectPoolReader — reference

Overview

`DmColumnStoreObjectPoolReader` wraps `sys.dm_column_store_object_pool` and exposes information about columnstore objects cached in the in-memory pool.

Reader SQL

```
SELECT
  dcsop.[database_id],
  dcsop.[object_id],
  dcsop.[index_id],
  dcsop.[partition_number],
  dcsop.[column_id],
  dcsop.[row_group_id],
  dcsop.[object_type],
  dcsop.[object_type_desc],
  dcsop.[access_count],
  dcsop.[memory_used_in_bytes],
  dcsop.[object_load_time]
FROM
  [sys].[dm_column_store_object_pool] dcsop
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int)
  - Database containing the columnstore object.

- `object_id` ? `ObjectId` (int)
  - Object id (table or index) the row group belongs to.

- `index_id` ? `IndexId` (int)
  - Index id for the columnstore index.

- `partition_number` ? `PartitionNumber` (int)
  - Partition number within the index.

- `column_id` ? `ColumnId` (int?)
  - Column id for column-level objects; null for whole-row groups.

- `row_group_id` ? `RowGroupId` (int)
  - Identifier for the row group within the columnstore.

- `object_type` ? `ObjectType` (int)
  - Numeric code for object type.

- `object_type_desc` ? `ObjectTypeDesc` (string)
  - Description of the object type (e.g., ROW_GROUP, DELTA_STORE).

- `access_count` ? `AccessCount` (long)
  - Number of times this object has been accessed.

- `memory_used_in_bytes` ? `MemoryUsedInBytes` (long)
  - Memory currently used by the object in the pool.

- `object_load_time` ? `ObjectLoadTime` (DateTime)
  - Timestamp when object was loaded into pool.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmColumnStoreObjectPoolDataType` objects.
