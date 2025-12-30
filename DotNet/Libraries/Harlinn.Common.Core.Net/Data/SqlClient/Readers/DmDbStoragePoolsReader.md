# DmDbStoragePoolsReader — reference

Overview

`DmDbStoragePoolsReader` wraps `sys.dm_db_storage_pools` and exposes storage pool metadata defined in the database.

Reader SQL

```
SELECT
  ddsp.[storage_pool_id],
  ddsp.[Name],
  ddsp.[Location]
FROM
  [sys].[dm_db_storage_pools] ddsp
```

Columns

- `storage_pool_id` ? `StoragePoolId` (int)
  - Identifier of the storage pool.

- `Name` ? `Name` (string?)
  - Name of the storage pool.

- `Location` ? `Location` (string)
  - Location identifier (path or logical location) used for the pool.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbStoragePoolsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbStoragePoolsReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Pool {r.StoragePoolId}: {r.Name} at {r.Location}");
}
```

See also:

- [sys.dm_db_storage_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-storage-pools)
