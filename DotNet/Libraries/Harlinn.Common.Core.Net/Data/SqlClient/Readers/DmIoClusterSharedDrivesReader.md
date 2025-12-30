# DmIoClusterSharedDrivesReader — reference

Overview

`DmIoClusterSharedDrivesReader` wraps `sys.dm_io_cluster_shared_drives` and returns the drive letters or names for drives shared in a Windows cluster that may be used for clustered storage.

Reader SQL

```
SELECT
  dicsd.[Drivename]
FROM
  [sys].[dm_io_cluster_shared_drives] dicsd
```

Columns and interpretation

- `Drivename` ? `Drivename` (string?)
  - The drive name or letter for a cluster-shared drive. May be null if not available.

How to interpret

- Useful to discover cluster-shared storage accessible to SQL Server for placing clustered databases or backups.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmIoClusterSharedDrivesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmIoClusterSharedDrivesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Drive:{r.Drivename}");
}
```

See also:

- [sys.dm_io_cluster_shared_drives](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-io-cluster-shared-drives)
