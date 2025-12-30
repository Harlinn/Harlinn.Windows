# PartitionsReader — reference

Overview

`PartitionsReader` wraps `sys.partitions` and returns partition-level metadata for tables and indexes, including HOBT id, row counts and compression.

Reader SQL

```
SELECT
  p1.[partition_id],
  p1.[object_id],
  p1.[index_id],
  p1.[partition_number],
  p1.[hobt_id],
  p1.[Rows],
  p1.[filestream_filegroup_id],
  p1.[data_compression],
  p1.[data_compression_desc]
FROM
  [sys].[partitions] p1
```

Columns and interpretation

- `partition_id` — internal id for the partition.
- `object_id` — object id of the table / index.
- `index_id` — index id.
- `partition_number` — partition ordinal number.
- `hobt_id` — HOBT id referencing the storage allocation unit.
- `Rows` — row count for the partition (nullable).
- `filestream_filegroup_id` — filegroup id for FILESTREAM data.
- `data_compression` / `data_compression_desc` — compression type and description.

How to interpret

- Use to examine distribution of data across partitions; `hobt_id` helps correlate partitions to physical allocation units. Row counts are useful for balancing and performance.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PartitionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PartitionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Partition:{r.PartitionId} Obj:{r.ObjectId} Index:{r.IndexId} PartNo:{r.PartitionNumber} Rows:{r.Rows}");
}
```

See also:

- [sys.partitions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-partitions)
