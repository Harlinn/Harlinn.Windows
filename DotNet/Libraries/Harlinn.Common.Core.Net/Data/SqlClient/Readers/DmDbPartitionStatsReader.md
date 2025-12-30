# DmDbPartitionStatsReader — reference

Overview

`DmDbPartitionStatsReader` wraps `sys.dm_db_partition_stats` and exposes storage statistics per partition, including page counts and row counts for in-row data, LOB data and row-overflow data.

Reader SQL

```
SELECT
  ddps.[partition_id],
  ddps.[object_id],
  ddps.[index_id],
  ddps.[partition_number],
  ddps.[in_row_data_page_count],
  ddps.[in_row_used_page_count],
  ddps.[in_row_reserved_page_count],
  ddps.[lob_used_page_count],
  ddps.[lob_reserved_page_count],
  ddps.[row_overflow_used_page_count],
  ddps.[row_overflow_reserved_page_count],
  ddps.[used_page_count],
  ddps.[reserved_page_count],
  ddps.[row_count]
FROM
  [sys].[dm_db_partition_stats] ddps
```

Columns (detailed)

- `partition_id` ? `PartitionId` (long?)
  - Unique partition identifier.

- `object_id` ? `ObjectId` (int)
  - Object id (table or indexed view) owning the partition.

- `index_id` ? `IndexId` (int)
  - Index id (0 = heap) of the partition.

- `partition_number` ? `PartitionNumber` (int)
  - Partition ordinal number within the partition function.

- `in_row_data_page_count` ? `InRowDataPageCount` (long?)
  - Number of pages that store in-row data (data that fits on the base row).

- `in_row_used_page_count` ? `InRowUsedPageCount` (long?)
  - Pages currently used to store in-row data (may exclude reserved pages).

- `in_row_reserved_page_count` ? `InRowReservedPageCount` (long?)
  - Pages reserved for in-row data.

- `lob_used_page_count` ? `LobUsedPageCount` (long?)
  - Pages used to store LOB (large object) data for this partition.

- `lob_reserved_page_count` ? `LobReservedPageCount` (long?)
  - Pages reserved for LOB storage.

- `row_overflow_used_page_count` ? `RowOverflowUsedPageCount` (long?)
  - Pages used for row-overflow data when columns exceed in-row size.

- `row_overflow_reserved_page_count` ? `RowOverflowReservedPageCount` (long?)
  - Reserved pages for row-overflow data.

- `used_page_count` ? `UsedPageCount` (long?)
  - Total number of pages used by the partition (sum of used pages across types).

- `reserved_page_count` ? `ReservedPageCount` (long?)
  - Total number of pages reserved for the partition.

- `row_count` ? `RowCount` (long?)
  - Number of rows present in the partition.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbPartitionStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var pReader = new DmDbPartitionStatsReader(reader, ownsReader: false);
while (pReader.Read())
{
    Console.WriteLine($"Object {pReader.ObjectId} Index {pReader.IndexId} Partition {pReader.PartitionNumber} (Id {pReader.PartitionId})");
    Console.WriteLine($" Rows: {pReader.RowCount ?? 0}, Used pages: {pReader.UsedPageCount ?? 0}, Reserved pages: {pReader.ReservedPageCount ?? 0}");
    Console.WriteLine($" In-row used/reserved: {pReader.InRowUsedPageCount ?? 0}/{pReader.InRowReservedPageCount ?? 0}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-partition-stats
