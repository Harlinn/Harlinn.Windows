# SystemInternalsPartitionColumnsReader

Overview

`SystemInternalsPartitionColumnsReader` wraps `sys.system_internals_partition_columns` and exposes internal metadata about partition columns used by storage engine.

Reader SQL

```
SELECT
  sipc.[partition_id],
  sipc.[partition_column_id],
  sipc.[modified_count],
  sipc.[max_inrow_length],
  sipc.[is_replicated],
  sipc.[is_logged_for_replication],
  sipc.[is_dropped],
  sipc.[system_type_id],
  sipc.[max_length],
  sipc.[Precision],
  sipc.[Scale],
  sipc.[collation_name],
  sipc.[is_filestream],
  sipc.[key_ordinal],
  sipc.[is_nullable],
  sipc.[is_descending_key],
  sipc.[is_uniqueifier],
  sipc.[leaf_offset],
  sipc.[internal_offset],
  sipc.[leaf_bit_position],
  sipc.[internal_bit_position],
  sipc.[leaf_null_bit],
  sipc.[internal_null_bit],
  sipc.[is_anti_matter],
  sipc.[partition_column_guid],
  sipc.[is_sparse],
  sipc.[has_default],
  sipc.[default_value]
FROM
  [sys].[system_internals_partition_columns] sipc
```

Columns and interpretation

- `partition_id` (bigint): Partition identifier.
- `partition_column_id` (int): Column id within the partition metadata.
- `modified_count` (bigint): Modification counter for the column in the partition.
- `max_inrow_length` (smallint?): Maximum in-row byte length for the column.
- `is_replicated` (bit?): Whether the column is replicated.
- `is_logged_for_replication` (bit?): Whether changes are logged for replication.
- `is_dropped` (bit?): Whether the column has been dropped.
- `system_type_id` (tinyint?): System type id of the column.
- `max_length` (smallint?): Maximum byte length.
- `Precision` (tinyint?): Numeric precision.
- `Scale` (tinyint?): Numeric scale.
- `collation_name` (string?): Collation for character columns.
- `is_filestream` (bit?): Whether the column is FILESTREAM.
- `key_ordinal` (smallint): Ordinal within the partition key.
- `is_nullable` (bit?): Nullable flag.
- `is_descending_key` (bit?): Whether the key is descending.
- `is_uniqueifier` (bit?): Internal flag for uniqueifier column.
- `leaf_offset`/`internal_offset` (smallint?): Offsets used internally for record layout.
- `leaf_bit_position`/`internal_bit_position` (tinyint?): Bit positions used internally for null bitmap or flags.
- `leaf_null_bit`/`internal_null_bit` (smallint?): Null bit positions.
- `is_anti_matter` (bit?): Internal flag for “anti-matter” rows used by versioning or deletes.
- `partition_column_guid` (uniqueidentifier?): GUID identifying the partition column metadata.
- `is_sparse` (bit?): Whether the column is SPARSE.
- `has_default` (bit): Whether a default exists for the column.
- `default_value` (sql_variant/object?): Default value if `has_default` is true.

How to interpret

- This view is internal to SQL Server storage metadata. Use standard catalog views (`sys.columns`, `sys.partitions`) for most user tasks.
- Numeric offsets and bit positions are internal details about record structure in pages; only use when diagnosing deep storage issues.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemInternalsPartitionColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemInternalsPartitionColumnsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Partition:{r.PartitionId} ColId:{r.PartitionColumnId} Modified:{r.ModifiedCount} Nullable:{r.IsNullable}");
```

See also:

- [sys.system_internals_partition_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-internals-partition-columns)
