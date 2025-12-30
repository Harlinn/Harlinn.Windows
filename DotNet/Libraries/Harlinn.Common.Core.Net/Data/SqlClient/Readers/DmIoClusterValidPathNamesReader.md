# DmIoClusterValidPathNamesReader — reference

Overview

`DmIoClusterValidPathNamesReader` wraps `sys.dm_io_cluster_valid_path_names` and returns valid cluster-aware path names, their owning cluster node and whether they are cluster-shared volumes.

Reader SQL

```
SELECT
  dicvpn.[path_name],
  dicvpn.[cluster_owner_node],
  dicvpn.[is_cluster_shared_volume]
FROM
  [sys].[dm_io_cluster_valid_path_names] dicvpn
```

Columns and interpretation

- `path_name` ? `PathName` (string?)
  - Path that is recognized as valid in the cluster context.

- `cluster_owner_node` ? `ClusterOwnerNode` (string?)
  - Name of the cluster node that owns the path.

- `is_cluster_shared_volume` ? `IsClusterSharedVolume` (bool)
  - True if the path corresponds to a Cluster Shared Volume (CSV).

How to interpret

- Use to determine which paths are cluster-aware and which nodes own them; crucial for placing database files on cluster-supported storage.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmIoClusterValidPathNamesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmIoClusterValidPathNamesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Path:{r.PathName} Owner:{r.ClusterOwnerNode} CSV:{r.IsClusterSharedVolume}");
}
```

See also:

- [sys.dm_io_cluster_valid_path_names](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-io-cluster-valid-path-names)
