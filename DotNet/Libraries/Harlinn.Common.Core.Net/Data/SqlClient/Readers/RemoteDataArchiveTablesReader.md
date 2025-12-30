# RemoteDataArchiveTablesReader

Overview

`RemoteDataArchiveTablesReader` wraps `sys.remote_data_archive_tables` and exposes table-level configuration for remote data archive.

Reader SQL

```
SELECT
  rdat.[object_id],
  rdat.[remote_database_id],
  rdat.[remote_table_name],
  rdat.[filter_predicate],
  rdat.[migration_direction],
  rdat.[migration_direction_desc],
  rdat.[is_migration_paused],
  rdat.[is_reconciled]
FROM
  [sys].[remote_data_archive_tables] rdat
```

Columns and interpretation

- `object_id` (int): The object_id of the table in this database.
- `remote_database_id` (int): Identifier of the remote archive database target.
- `remote_table_name` (string?): Name of the remote table used for archive.
- `filter_predicate` (string?): Predicate expression used to filter rows for migration.
- `migration_direction` (byte?): Numeric code indicating migration direction (push/pull/both); use `migration_direction_desc` for human text.
- `migration_direction_desc` (string?): Textual description of the migration direction.
- `is_migration_paused` (bool?): Whether migration is currently paused for this table.
- `is_reconciled` (bool?): Whether the table migration has been reconciled (synchronized).

How to interpret

- Combine `object_id` with `sys.objects` to get table name in this database. `filter_predicate` defines which rows are archived.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RemoteDataArchiveTablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RemoteDataArchiveTablesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Object:{r.ObjectId} RemoteTable:{r.RemoteTableName} Paused:{r.IsMigrationPaused}");
}
```

See also:

- [sys.remote_data_archive_tables](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-remote-data-archive-tables)

