# SystemInternalsPartitionsReader

Overview

`SystemInternalsPartitionsReader` wraps `sys.system_internals_partitions` and surfaces partition-level internal metadata.

Reader SQL

```
SELECT
  sip.[partition_id],
  sip.[object_id],
  sip.[index_id],
  sip.[partition_number],
  sip.[Rows],
  sip.[filestream_filegroup_id],
  sip.[is_orphaned],
  sip.[dropped_lob_column_state],
  sip.[is_unique],
  sip.[is_replicated],
  sip.[is_logged_for_replication],
  sip.[is_sereplicated],
  sip.[max_null_bit_used],
  sip.[max_leaf_length],
  sip.[min_leaf_length],
  sip.[max_internal_length],
  sip.[min_internal_length],
  sip.[allows_nullable_keys],
  sip.[allow_row_locks],
  sip.[allow_page_locks],
  sip.[is_data_row_format],
  sip.[is_not_versioned],
  sip.[filestream_guid],
  sip.[Ownertype],
  sip.[is_columnstore],
  sip.[optimize_for_sequential_key]
FROM
  [sys].[system_internals_partitions] sip
```

Columns and interpretation

- `partition_id` (bigint): Partition identifier.
- `object_id` (int): Object id the partition belongs to.
- `index_id` (int): Index id within the object.
- `partition_number` (int): Partition number.
- `Rows` (bigint): Row count in the partition.
- `filestream_filegroup_id` (smallint): Filegroup id for FILESTREAM data.
- `is_orphaned` (bit?): Whether the partition is orphaned.
- `dropped_lob_column_state` (tinyint?): State code for dropped LOB columns.
- `is_unique` (bit?): Whether index/partition enforces uniqueness.
- `is_replicated` (bit?): Replication flag.
- `is_logged_for_replication` (bit?): Logged for replication flag.
- `is_sereplicated` (bit): SEREPLICATION flag (internal).
- `max_null_bit_used` (smallint): Maximum null bit used.
- `max_leaf_length`/`min_leaf_length` (int/smallint): Leaf record lengths.
- `max_internal_length`/`min_internal_length` (smallint): Internal node lengths.
- `allows_nullable_keys` (bit?): Whether nullable keys allowed.
- `allow_row_locks`/`allow_page_locks` (bit?): Locking options.
- `is_data_row_format` (bit?): Whether data row format used.
- `is_not_versioned` (bit?): Versioning indicator.
- `filestream_guid` (uniqueidentifier?): GUID for FILESTREAM data.
- `Ownertype` (tinyint): Owner type code.
- `is_columnstore` (bit?): Whether partition is columnstore.
- `optimize_for_sequential_key` (bit?): Optimize for sequential key flag.

How to interpret

- Use when diagnosing partitioning and storage internals. For user-friendly metrics use `sys.partitions`, `sys.indexes`, and `sys.dm_db_partition_stats`.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemInternalsPartitionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemInternalsPartitionsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Partition:{r.PartitionId} Object:{r.ObjectId} Index:{r.IndexId} Rows:{r.Rows} IsColumnstore:{r.IsColumnstore}");
```

See also:

- [sys.system_internals_partitions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-internals-partitions)
