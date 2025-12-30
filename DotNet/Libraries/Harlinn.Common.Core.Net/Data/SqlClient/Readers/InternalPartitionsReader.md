# InternalPartitionsReader — reference

Overview

`InternalPartitionsReader` wraps `sys.internal_partitions` and returns internal partition/row-group metadata for physical storage structures, including HOBT id and compression.

Reader SQL

```
SELECT
  ip.[partition_id],
  ip.[object_id],
  ip.[index_id],
  ip.[partition_number],
  ip.[hobt_id],
  ip.[internal_object_type],
  ip.[internal_object_type_desc],
  ip.[row_group_id],
  ip.[Rows],
  ip.[data_compression],
  ip.[data_compression_desc]
FROM
  [sys].[internal_partitions] ip
```

Columns and interpretation

- `partition_id` — internal identifier for the partition.
- `object_id` — object id of the table/index.
- `index_id` — index id within the object.
- `partition_number` — partition ordinal number.
- `hobt_id` — HOBT id (Heap Or B-Tree) representing the storage internal object id.
- `internal_object_type` / `internal_object_type_desc` — type and description for the internal object (for example allocation unit types).
- `row_group_id` — row group id for columnstore segments (nullable).
- `Rows` — number of rows in this internal partition (nullable).
- `data_compression` / `data_compression_desc` — compression type and description (e.g., NONE, ROW, PAGE, COLUMNSTORE).

How to interpret

- Use `hobt_id` and `row_group_id` to correlate to storage artifacts for maintenance or diagnostics. Compression desc shows if partition uses compression.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = InternalPartitionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new InternalPartitionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Partition:{r.PartitionId} Obj:{r.ObjectId} Index:{r.IndexId} HOBT:{r.HobtId} Rows:{r.Rows} Compression:{r.DataCompressionDesc}");
}
```

See also:

- [sys.internal_partitions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-internal-partitions)
