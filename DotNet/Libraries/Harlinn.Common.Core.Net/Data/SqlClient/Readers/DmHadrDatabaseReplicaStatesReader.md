# DmHadrDatabaseReplicaStatesReader — reference

Overview

`DmHadrDatabaseReplicaStatesReader` wraps `sys.dm_hadr_database_replica_states` and reports detailed database-level replica state information including LSN positions, send/redo rates and suspension reasons.

Reader SQL

```
SELECT
  dhdrs.[database_id],
  dhdrs.[group_id],
  dhdrs.[replica_id],
  dhdrs.[group_database_id],
  dhdrs.[is_local],
  dhdrs.[is_primary_replica],
  dhdrs.[synchronization_state],
  dhdrs.[synchronization_state_desc],
  dhdrs.[is_commit_participant],
  dhdrs.[synchronization_health],
  dhdrs.[synchronization_health_desc],
  dhdrs.[database_state],
  dhdrs.[database_state_desc],
  dhdrs.[is_suspended],
  dhdrs.[suspend_reason],
  dhdrs.[suspend_reason_desc],
  dhdrs.[recovery_lsn],
  dhdrs.[truncation_lsn],
  dhdrs.[last_sent_lsn],
  dhdrs.[last_sent_time],
  dhdrs.[last_received_lsn],
  dhdrs.[last_received_time],
  dhdrs.[last_hardened_lsn],
  dhdrs.[last_hardened_time],
  dhdrs.[last_redone_lsn],
  dhdrs.[last_redone_time],
  dhdrs.[log_send_queue_size],
  dhdrs.[log_send_rate],
  dhdrs.[redo_queue_size],
  dhdrs.[redo_rate],
  dhdrs.[filestream_send_rate],
  dhdrs.[end_of_log_lsn],
  dhdrs.[last_commit_lsn],
  dhdrs.[last_commit_time],
  dhdrs.[low_water_mark_for_ghosts],
  dhdrs.[secondary_lag_seconds],
  dhdrs.[quorum_commit_lsn],
  dhdrs.[quorum_commit_time]
FROM
  [sys].[dm_hadr_database_replica_states] dhdrs
```

Columns and interpretation

- Identifiers: `database_id`, `group_id`, `replica_id`, `group_database_id`.
- Locality and role flags: `is_local`, `is_primary_replica`.
- Synchronization and health descriptors.
- Suspension flags and reason descriptors.
- LSN positions and timestamps: `recovery_lsn`, `truncation_lsn`, `last_sent_lsn`, `last_received_lsn`, `last_hardened_lsn`, `last_redone_lsn`, `end_of_log_lsn`, `last_commit_lsn`.
- Send and redo metrics: `log_send_queue_size`, `log_send_rate`, `redo_queue_size`, `redo_rate`, `filestream_send_rate`.
- `secondary_lag_seconds` ? approximate lag in seconds for secondaries.
- `quorum_commit_lsn` and `quorum_commit_time` ? commit points achieved across quorum.

How to interpret

- These fields collectively provide a view into replica synchronization progress and performance.
- Compare `last_sent_lsn`/`last_received_lsn`/`last_hardened_lsn` to find lag and bottlenecks.
- `redo_rate` and `log_send_rate` help identify throughput issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrDatabaseReplicaStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrDatabaseReplicaStatesReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"DB:{s.DatabaseId} Replica:{s.ReplicaId} Role:{s.IsPrimaryReplica} LastSentLSN:{s.LastSentLsn} LastReceivedLSN:{s.LastReceivedLsn} RedoRate:{s.RedoRate}");
}
```

See also:

- [sys.dm_hadr_database_replica_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-database-replica-states)
