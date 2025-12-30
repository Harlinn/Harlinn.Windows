# DmFtsActiveCatalogsReader — reference

Overview

`DmFtsActiveCatalogsReader` wraps `sys.dm_fts_active_catalogs` and provides information about active full-text catalogs including status, worker counts and population counts.

Reader SQL

```
SELECT
  dfac.[database_id],
  dfac.[catalog_id],
  dfac.[memory_address],
  dfac.[Name],
  dfac.[is_paused],
  dfac.[Status],
  dfac.[status_description],
  dfac.[previous_status],
  dfac.[previous_status_description],
  dfac.[worker_count],
  dfac.[active_fts_index_count],
  dfac.[auto_population_count],
  dfac.[manual_population_count],
  dfac.[full_incremental_population_count],
  dfac.[row_count_in_thousands],
  dfac.[is_importing]
FROM
  [sys].[dm_fts_active_catalogs] dfac
```

Columns and interpretation

- `database_id`, `catalog_id` ? identifiers for the catalog and owning database.
- `memory_address` ? internal memory address token.
- `Name` ? catalog name.
- `is_paused` ? whether population/searching is paused for the catalog.
- `Status` / `status_description` ? numeric status and description.
- `previous_status` / `previous_status_description` ? prior status information.
- `worker_count` ? number of worker threads serving the catalog.
- `active_fts_index_count` ? number of active full-text indexes.
- Population-related counters: `auto_population_count`, `manual_population_count`, `full_incremental_population_count`.
- `row_count_in_thousands` ? approximate row count in the catalog (thousands).
- `is_importing` ? whether an import operation is currently in progress.

How to interpret

- Use status and worker counts to detect catalogs that may be stalled or starved of resources.
- Population counts indicate ongoing indexing activity and whether operations are auto or manual.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsActiveCatalogsReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmFtsActiveCatalogsReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Catalog:{c.Name} DB:{c.DatabaseId} Status:{c.StatusDescription} Workers:{c.WorkerCount} ActiveIndexes:{c.ActiveFtsIndexCount}");
}
```

See also:

- [sys.dm_fts_active_catalogs](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-active-catalogs)
