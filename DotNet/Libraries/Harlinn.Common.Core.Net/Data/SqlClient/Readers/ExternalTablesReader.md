# ExternalTablesReader — reference

Overview

`ExternalTablesReader` wraps `sys.external_tables` and returns metadata about external tables used to access external data sources (e.g., PolyBase external tables), including storage, format, distribution and rejection handling.

Reader SQL

```
SELECT
  et.[Name],
  et.[object_id],
  et.[principal_id],
  et.[schema_id],
  et.[parent_object_id],
  et.[Type],
  et.[type_desc],
  et.[create_date],
  et.[modify_date],
  et.[is_ms_shipped],
  et.[is_published],
  et.[is_schema_published],
  et.[max_column_id_used],
  et.[uses_ansi_nulls],
  et.[data_source_id],
  et.[file_format_id],
  et.[Location],
  et.[reject_type],
  et.[reject_value],
  et.[reject_sample_value],
  et.[distribution_type],
  et.[distribution_desc],
  et.[sharding_col_id],
  et.[remote_schema_name],
  et.[remote_object_name],
  et.[rejected_row_location]
FROM
  [sys].[external_tables] et
```

Columns and interpretation

- `Name` — external table name.
- `object_id` — object id of the external table.
- `principal_id` — owner principal id (nullable).
- `schema_id` — schema id.
- `parent_object_id` — parent object id (usually same as object_id for table objects).
- `Type` / `type_desc` — type code/description for the schema object.
- `create_date` / `modify_date` — timestamps for creation and modification.
- `is_ms_shipped`, `is_published`, `is_schema_published` — flags describing origin and publication status.
- `max_column_id_used` — highest column id assigned in the external table (nullable).
- `uses_ansi_nulls` — whether ANSI NULLs semantics are used (nullable boolean).
- `data_source_id` — external data source id referencing `sys.external_data_sources`.
- `file_format_id` — optional file format id referencing `sys.external_file_formats`.
- `Location` — location/path within the external data source (nullable).
- `reject_type`, `reject_value`, `reject_sample_value` — rejection behavior and thresholds when reading external data (nullable). `reject_type` details how rejected rows are handled; `reject_value` typically numeric threshold; `reject_sample_value` a sample value causing reject.
- `distribution_type` / `distribution_desc` — distribution type code and description (e.g., HASH, ROUND_ROBIN) for external table.
- `sharding_col_id` — column id used for sharding/distribution (nullable).
- `remote_schema_name` / `remote_object_name` — names used on remote system for mapping.
- `rejected_row_location` — path or location where rejected rows are written (nullable).

How to interpret

- Use `data_source_id` and `file_format_id` to correlate external tables to their data source and parsing settings.
- `distribution_type` and `sharding_col_id` indicate how data is distributed among compute nodes.
- Rejection settings (`reject_*`) are important for handling malformed data when importing from external sources.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalTablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalTablesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Table:{r.Name} Obj:{r.ObjectId} DataSource:{r.DataSourceId} Location:{r.Location} Distribution:{r.DistributionDesc}");
}
```

See also:

- [sys.external_tables](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-tables)
