# DmOsClusterNodesReader — reference

Overview

`DmOsClusterNodesReader` wraps `sys.dm_os_cluster_nodes` and provides information about Windows cluster nodes recognized by SQL Server including status and ownership.

Reader SQL

```
SELECT
  docn.[Nodename],
  docn.[Status],
  docn.[status_description],
  docn.[is_current_owner]
FROM
  [sys].[dm_os_cluster_nodes] docn
```

Columns and interpretation

- `Nodename` ? `Nodename` (string?)
  - Name of the cluster node.

- `Status` / `status_description` ? `Status` (int?), `StatusDescription` (string)
  - Numeric and textual status for the node (Up/Down/Unknown/etc.).

- `is_current_owner` ? `IsCurrentOwner` (bool?)
  - True if the node currently owns cluster resources relevant to SQL Server.

How to interpret

- Use node status and ownership to determine cluster health and where resources are hosted.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsClusterNodesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsClusterNodesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Node:{r.Nodename} Status:{r.StatusDescription} Owner:{r.IsCurrentOwner}");
}
```

See also:

- [sys.dm_os_cluster_nodes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-cluster-nodes)
