# DmResourceGovernorConfigurationReader — reference

Overview

`DmResourceGovernorConfigurationReader` wraps `sys.dm_resource_governor_configuration` and exposes current Resource Governor configuration such as classifier function and I/O limits.

Reader SQL

```
SELECT
  drgc.[classifier_function_id],
  drgc.[is_reconfiguration_pending],
  drgc.[max_outstanding_io_per_volume]
FROM
  [sys].[dm_resource_governor_configuration] drgc
```

Columns and interpretation

- `classifier_function_id` — ID of the classifier function used to map sessions to workload groups.
- `is_reconfiguration_pending` — flag indicating if a resource governor reconfiguration is pending and will be applied on next RECONFIGURE.
- `max_outstanding_io_per_volume` — maximum outstanding I/O per volume allowed by configuration.

How to interpret

- Use `is_reconfiguration_pending` to determine whether configuration changes have been staged but not applied.
- `classifier_function_id` maps to a user-defined classifier function; null/zero indicates no classifier.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorConfigurationReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorConfigurationReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"ClassifierId:{r.ClassifierFunctionId} Pending:{r.IsReconfigurationPending} MaxIOPerVol:{r.MaxOutstandingIoPerVolume}");
}
```

See also:

- [sys.dm_resource_governor_configuration](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-configuration)
