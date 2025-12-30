# DmHadrAvailabilityGroupStatesReader — reference

Overview

`DmHadrAvailabilityGroupStatesReader` wraps `sys.dm_hadr_availability_group_states` and reports health and synchronization state summaries for availability groups.

Reader SQL

```
SELECT
  dhags.[group_id],
  dhags.[primary_replica],
  dhags.[primary_recovery_health],
  dhags.[primary_recovery_health_desc],
  dhags.[secondary_recovery_health],
  dhags.[secondary_recovery_health_desc],
  dhags.[synchronization_health],
  dhags.[synchronization_health_desc]
FROM
  [sys].[dm_hadr_availability_group_states] dhags
```

Columns and interpretation

- `group_id` ? AG identifier.
- `primary_replica` ? name of the primary replica server.
- `primary_recovery_health` / `primary_recovery_health_desc` ? numeric and textual recovery health for the primary.
- `secondary_recovery_health` / `secondary_recovery_health_desc` ? recovery health for secondaries.
- `synchronization_health` / `synchronization_health_desc` ? overall synchronization health metrics.

How to interpret

- Use health descriptors to triage AG-level problems and identify whether primary/secondary replicas require attention.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAvailabilityGroupStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrAvailabilityGroupStatesReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"AG:{s.GroupId} Primary:{s.PrimaryReplica} PrimaryHealth:{s.PrimaryRecoveryHealthDesc} SyncHealth:{s.SynchronizationHealthDesc}");
}
```

See also:

- [sys.dm_hadr_availability_group_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-availability-group-states)
