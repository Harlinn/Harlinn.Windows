# ColumnStoreSegmentsReader — reference

Overview

`ColumnStoreSegmentsReader` wraps `sys.column_store_segments` and exposes metadata about physical segments for columnstore columns.

Reader SQL

```
SELECT scss.[partition_id]
      ,scss.[hobt_id]
      ,scss.[column_id]
      ,scss.[segment_id]
      ,scss.[version]
      ,scss.[encoding_type]
      ,scss.[row_count]
      ,scss.[has_nulls]
      ,scss.[base_id]
      ,scss.[magnitude]
      ,scss.[primary_dictionary_id]
      ,scss.[secondary_dictionary_id]
      ,scss.[min_data_id]
      ,scss.[max_data_id]
      ,scss.[null_value]
      ,scss.[on_disk_size]
FROM [sys].[column_store_segments] scss
```

Selected columns (method mapping and brief meaning)

- `partition_id` ? `GetPartitionId()` (int): Partition id containing the segment.
- `hobt_id` ? `GetHobtId()` (long): HOBT id containing the segment.
- `column_id` ? `GetColumnId()` (int): Column id the segment belongs to.
- `segment_id` ? `GetSegmentId()` (long): Segment identifier.
- `version` ? `GetVersion()` (int): Segment format version.
- `encoding_type` ? `GetEncodingType()` (byte): Encoding type code.
- `row_count` ? `GetRowCount()` (long): Rows in the segment.
- `has_nulls` ? `GetHasNulls()` (bool): Whether segment contains NULLs.
- `base_id` ? `GetBaseId()` (long?): Base id for delta/base relations.
- `magnitude` ? `GetMagnitude()` (int?): Magnitude attribute for the stored data.
- `primary_dictionary_id` / `secondary_dictionary_id` ? dictionary ids used by segment.
- `min_data_id` / `max_data_id` ? min/max data ids stored in segment.
- `null_value` ? `GetNullValue()` (string?): Representation of null value for segment.
- `on_disk_size` ? `GetOnDiskSize()` (long): Size on disk in bytes.

Helpers

- `GetColumnStoreSegment()` returns a `ColumnStoreSegment` instance from current row.
- `GetColumnStoreSegments()` reads all rows and returns a list.
