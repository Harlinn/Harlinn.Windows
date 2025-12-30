# DmHadrAvailabilityReplicaClusterStatesReader — reference

Overview

`DmHadrAvailabilityReplicaClusterStatesReader` wraps `sys.dm_hadr_availability_replica_cluster_states` and reports replica cluster join states for availability replicas.

Reader SQL

```
SELECT
  dharcs.[replica_id],
  dharcs.[replica_server_name],
  dharcs.[group_id],
  dharcs.[join_state],
  dharcs.[join_state_desc]
FROM
  [sys].[dm_hadr_availability_replica_cluster_states] dharcs
```

Columns and interpretation

- `replica_id` ? replica identifier (GUID).
- `replica_server_name` ? server name for the replica.
- `group_id` ? availability group identifier.
- `join_state` / `join_state_desc` ? numeric and textual state describing cluster join status.

How to interpret

- `join_state_desc` helps determine whether the replica is successfully joined to the cluster or is pending/failed.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAvailabilityReplicaClusterStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrAvailabilityReplicaClusterStatesReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Replica:{s.ReplicaServerName} Group:{s.GroupId} JoinState:{s.JoinStateDesc}");
}
```

See also:

- [sys.dm_hadr_availability_replica_cluster_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-availability-replica-cluster-states)
