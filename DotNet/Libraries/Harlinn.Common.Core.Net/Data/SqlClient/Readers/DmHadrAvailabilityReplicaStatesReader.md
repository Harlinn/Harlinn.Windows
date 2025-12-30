# DmHadrAvailabilityReplicaStatesReader — reference

Overview

`DmHadrAvailabilityReplicaStatesReader` wraps `sys.dm_hadr_availability_replica_states` and reports detailed replica state information such as role, connectivity, recovery and synchronization health.

Reader SQL

```
SELECT
  dhars.[replica_id],
  dhars.[group_id],
  dhars.[is_local],
  dhars.[Role],
  dhars.[role_desc],
  dhars.[operational_state],
  dhars.[operational_state_desc],
  dhars.[connected_state],
  dhars.[connected_state_desc],
  dhars.[recovery_health],
  dhars.[recovery_health_desc],
  dhars.[synchronization_health],
  dhars.[synchronization_health_desc],
  dhars.[last_connect_error_number],
  dhars.[last_connect_error_description],
  dhars.[last_connect_error_timestamp],
  dhars.[write_lease_remaining_ticks],
  dhars.[current_configuration_commit_start_time_utc]
FROM
  [sys].[dm_hadr_availability_replica_states] dhars
```

Columns and interpretation

- Replica and group ids, locality (`is_local`).
- `Role` / `role_desc` ? role of the replica (Primary/Secondary).
- `operational_state` / `operational_state_desc` ? operational indicators.
- Connectivity and recovery health fields with descriptions.
- `last_connect_error_*` fields provide last connectivity error details.
- `write_lease_remaining_ticks` ? remaining ticks for the write lease.
- `current_configuration_commit_start_time_utc` ? timestamp for current configuration commit start.

How to interpret

- Use these fields to monitor replica health, connectivity and recovery; `last_connect_error_description` helps diagnose communication issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAvailabilityReplicaStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrAvailabilityReplicaStatesReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Replica:{s.ReplicaId} Role:{s.RoleDesc} Connected:{s.ConnectedStateDesc} SyncHealth:{s.SynchronizationHealthDesc}");
}
```

See also:

- [sys.dm_hadr_availability_replica_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-availability-replica-states)
