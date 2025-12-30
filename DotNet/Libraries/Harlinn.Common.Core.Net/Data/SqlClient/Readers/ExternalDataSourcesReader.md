# ExternalDataSourcesReader — reference

Overview

`ExternalDataSourcesReader` wraps `sys.external_data_sources` and returns configuration about external data sources used by PolyBase and external tables, including locations, credentials and pushdown options.

Reader SQL

```
SELECT
  eds.[data_source_id],
  eds.[Name],
  eds.[Location],
  eds.[type_desc],
  eds.[Type],
  eds.[resource_manager_location],
  eds.[credential_id],
  eds.[database_name],
  eds.[shard_map_name],
  eds.[connection_options],
  eds.[Pushdown]
FROM
  [sys].[external_data_sources] eds
```

Columns and interpretation

- `data_source_id` — id of the external data source.
- `Name` — external data source name.
- `Location` — location/URI of the external source (e.g., HDFS path, Azure storage, server address).
- `type_desc` / `Type` — textual type and numeric type code for the data source (HADOOP, RDBMS, AZURE_BLOB_STORAGE, etc.).
- `resource_manager_location` — resource manager endpoint location (nullable).
- `credential_id` — credential object id used to access the external source (nullable integer).
- `database_name` — remote database name if applicable.
- `shard_map_name` — shard map name for sharding scenarios (nullable).
- `connection_options` — connection options string for the external source.
- `Pushdown` — pushdown options indicating whether query pushdown is enabled.

How to interpret

- Use `Location` and `Type` to determine how external tables connect to external storage or remote databases; `credential_id` links to credentials defined in SQL Server.
- `Pushdown` indicates whether some processing is performed on the remote system to reduce data movement.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalDataSourcesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalDataSourcesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DataSource:{r.DataSourceId} Name:{r.Name} Location:{r.Location} Type:{r.TypeDesc} Pushdown:{r.Pushdown}");
}
```

See also:

- [sys.external_data_sources](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-data-sources)
