# DmHadrDatabaseReplicaClusterStatesReader — reference

Overview

`DmHadrDatabaseReplicaClusterStatesReader` wraps `sys.dm_hadr_database_replica_cluster_states` and reports whether databases are joined to the cluster, failover readiness and LSN information.

Reader SQL

```
SELECT
  dhdrcs.[replica_id],
  dhdrcs.[group_database_id],
  dhdrcs.[database_name],
  dhdrcs.[is_failover_ready],
  dhdrcs.[is_pending_secondary_suspend],
  dhdrcs.[is_database_joined],
  dhdrcs.[recovery_lsn],
  dhdrcs.[truncation_lsn]
FROM
  [sys].[dm_hadr_database_replica_cluster_states] dhdrcs
```

Columns and interpretation

- `replica_id`, `group_database_id` ? identifiers for the replica and database mapping.
- `database_name` ? name of the database.
- `is_failover_ready` ? whether the database is ready for failover.
- `is_pending_secondary_suspend` ? indicates pending suspension on secondary.
- `is_database_joined` ? whether the database is joined with AG.
- `recovery_lsn` / `truncation_lsn` ? LSN values relevant for recovery and truncation.

How to interpret

- `is_failover_ready` and `is_database_joined` are key indicators for readiness and health in failover planning.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrDatabaseReplicaClusterStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrDatabaseReplicaClusterStatesReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"DB:{s.DatabaseName} Replica:{s.ReplicaId} FailoverReady:{s.IsFailoverReady} Joined:{s.IsDatabaseJoined} RecoveryLSN:{s.RecoveryLsn}");
}
```

See also:

- [sys.dm_hadr_database_replica_cluster_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-database-replica-cluster-states)
