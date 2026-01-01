# TablesReader

Overview

`TablesReader` wraps `sys.tables` and exposes metadata about user tables in the database.

Reader SQL

```
SELECT [name]
    ,[object_id]
    ,[principal_id]
    ,[schema_id]
    ,[parent_object_id]
    ,[type]
    ,[type_desc]
    ,[create_date]
    ,[modify_date]
    ,[is_ms_shipped]
    ,[is_published]
    ,[is_schema_published]
    ,[lob_data_space_id]
    ,[filestream_data_space_id]
    ,[max_column_id_used]
    ,[lock_on_bulk_load]
    ,[uses_ansi_nulls]
    ,[is_replicated]
    ,[has_replication_filter]
    ,[is_merge_published]
    ,[is_sync_tran_subscribed]
    ,[has_unchecked_assembly_data]
    ,[text_in_row_limit]
    ,[large_value_types_out_of_row]
    ,[is_tracked_by_cdc]
    ,[lock_escalation]
    ,[lock_escalation_desc]
    ,[is_filetable]
    ,[is_memory_optimized]
    ,[durability]
    ,[durability_desc]
    ,[temporal_type]
    ,[temporal_type_desc]
    ,[history_table_id]
    ,[is_remote_data_archive_enabled]
    ,[is_external]
    ,[history_retention_period]
    ,[history_retention_period_unit]
    ,[history_retention_period_unit_desc]
    ,[is_node]
    ,[is_edge]
FROM [sys].[tables]
```

Columns and interpretation

- `name` (string): Table name.
- `object_id` (int): Object id.
- `principal_id` (int?): Principal id (owner) of the table.
- `schema_id` (int): Schema id for the table.
- `parent_object_id` (int?): Parent object id.
- `type`/`type_desc` (string): Object type and description.
- `create_date`/`modify_date` (datetime): Creation and modification timestamps.
- `is_ms_shipped` (bit): Whether Microsoft shipped the table.
- `is_published`/`is_schema_published` (bit): Publication flags.
- `lob_data_space_id`/`filestream_data_space_id` (int): Filegroup/data space ids for LOB/FILESTREAM data.
- `max_column_id_used` (int): Highest column id used in the table.
- `lock_on_bulk_load` (bit): Bulk load locking behavior.
- `uses_ansi_nulls` (bit): ANSI NULLS usage.
- `is_replicated`/`has_replication_filter`/`is_merge_published`/`is_sync_tran_subscribed` (bit): Replication and subscription flags.
- `has_unchecked_assembly_data` (bit): Whether assembly data is unchecked.
- `text_in_row_limit` (int): Limit for text in row storage.
- `large_value_types_out_of_row` (bit): Whether large value types are stored out of row.
- `is_tracked_by_cdc` (bit): Change data capture tracking flag.
- `lock_escalation`/`lock_escalation_desc` (tinyint/string): Lock escalation setting and description.
- `is_filetable` (bit): Whether table is a FILETABLE.
- `is_memory_optimized` (bit): Whether table is memory-optimized.
- `durability`/`durability_desc` (tinyint/string): Durability setting for memory-optimized tables.
- `temporal_type`/`temporal_type_desc` (tinyint/string): Temporal table settings.
- `history_table_id` (int?): Object id of the history table for temporal tables.
- `is_remote_data_archive_enabled` (bit): Remote data archive flag.
- `is_external` (bit): External table flag.
- `history_retention_period`/`history_retention_period_unit`/`history_retention_period_unit_desc`: Temporal retention settings.
- `is_node`/`is_edge` (bit): Graph table node/edge flags.

How to interpret

- Use `object_id` and `schema_id` to join with other metadata views and retrieve columns, indexes, and constraints.
- Temporal and memory-optimized fields are relevant when diagnosing modern table features.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TablesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Table:{r.GetName()} Id:{r.GetObjectId()} SchemaId:{r.GetSchemaId()} Created:{r.GetCreateDate()} MemoryOptimized:{r.GetIsMemoryOptimized()}");
```

See also:

- [sys.tables](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-tables)
