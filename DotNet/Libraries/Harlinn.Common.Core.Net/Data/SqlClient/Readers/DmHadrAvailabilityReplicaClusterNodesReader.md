# DmHadrAvailabilityReplicaClusterNodesReader — reference

Overview

`DmHadrAvailabilityReplicaClusterNodesReader` wraps `sys.dm_hadr_availability_replica_cluster_nodes` and lists cluster nodes associated with availability replicas and groups.

Reader SQL

```
SELECT
  dharcn.[group_name],
  dharcn.[replica_server_name],
  dharcn.[node_name]
FROM
  [sys].[dm_hadr_availability_replica_cluster_nodes] dharcn
```

Columns and interpretation

- `group_name` ? availability group name.
- `replica_server_name` ? server name of the replica.
- `node_name` ? cluster node name where replica resides.

How to interpret

- Use this view to map AG replicas to cluster nodes for troubleshooting network or cluster membership issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAvailabilityReplicaClusterNodesReader.Sql;
using var rdr = cmd.ExecuteReader();
var n = new DmHadrAvailabilityReplicaClusterNodesReader(rdr, ownsReader:false);
while (n.Read())
{
    Console.WriteLine($"Group:{n.GroupName} Replica:{n.ReplicaServerName} Node:{n.NodeName}");
}
```

See also:

- [sys.dm_hadr_availability_replica_cluster_nodes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-availability-replica-cluster-nodes)
