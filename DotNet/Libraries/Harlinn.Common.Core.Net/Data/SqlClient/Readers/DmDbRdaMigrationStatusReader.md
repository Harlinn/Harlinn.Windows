# DmDbRdaMigrationStatusReader — reference

Overview

`DmDbRdaMigrationStatusReader` wraps `sys.dm_db_rda_migration_status` and exposes status information for RDA (Remote Data Access / resource migration) operations for tables.

Reader SQL

```
SELECT
  ddrms.[table_id],
  ddrms.[database_id],
  ddrms.[migrated_rows],
  ddrms.[start_time_utc],
  ddrms.[end_time_utc],
  ddrms.[error_number],
  ddrms.[error_severity],
  ddrms.[error_state]
FROM
  [sys].[dm_db_rda_migration_status] ddrms
```

Columns

- `table_id` ? `TableId` (int?)
  - Object id of the table being migrated.

- `database_id` ? `DatabaseId` (int?)
  - Database id where the migration is performed.

- `migrated_rows` ? `MigratedRows` (long?)
  - Number of rows migrated for the table during the operation.

- `start_time_utc` / `end_time_utc` ? timestamps (DateTime?) for start and end of migration.

- `error_number` / `error_severity` / `error_state` ? error information if migration failed or had issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbRdaMigrationStatusReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbRdaMigrationStatusReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Table: {r.TableId} DB: {r.DatabaseId} Migrated rows: {r.MigratedRows}");
    Console.WriteLine($" Start: {r.StartTimeUtc} End: {r.EndTimeUtc} Error: {r.ErrorNumber}");
}
```

See also:

- [sys.dm_db_rda_migration_status](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-rda-migration-status)
