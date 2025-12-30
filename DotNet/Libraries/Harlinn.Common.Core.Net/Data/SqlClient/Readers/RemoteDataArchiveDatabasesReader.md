# RemoteDataArchiveDatabasesReader

Overview

`RemoteDataArchiveDatabasesReader` wraps `sys.remote_data_archive_databases` and returns metadata about databases registered as remote data archive targets.

Reader SQL

```
SELECT
  rdad.[remote_database_id],
  rdad.[remote_database_name],
  rdad.[data_source_id],
  rdad.[federated_service_account]
FROM
  [sys].[remote_data_archive_databases] rdad
```

Columns and interpretation

- `remote_database_id` (int): Identifier for the remote archive database.
- `remote_database_name` (string): Name of the remote database as registered.
- `data_source_id` (int): Identifier of the data source object used to reach the remote archive.
- `federated_service_account` (bool?): Whether the federated service account is used (nullable).

How to interpret

- Remote data archive is used for archiving historical data to remote databases; these rows describe registered targets.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RemoteDataArchiveDatabasesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RemoteDataArchiveDatabasesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Id:{r.RemoteDatabaseId} Name:{r.RemoteDatabaseName} DataSource:{r.DataSourceId}");
}
```

See also:

- [sys.remote_data_archive_databases](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-remote-data-archive-databases)

