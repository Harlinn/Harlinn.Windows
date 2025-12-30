# DmPalVmStatsReader — reference

Overview

`DmPalVmStatsReader` wraps `sys.dm_pal_vm_stats` and returns counts for various virtual memory metrics identified by name.

Reader SQL

```
SELECT
  dpvs.[vm_metric_name],
  dpvs.[Count]
FROM
  [sys].[dm_pal_vm_stats] dpvs
```

Columns and interpretation

- `vm_metric_name` — textual name for the metric (e.g., page faults, swap events).
- `Count` — numeric count associated with the metric.

How to interpret

- These are platform-specific VM counters; use for OS-level memory diagnostics on supported platforms.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalVmStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalVmStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.VmMetricName}: {r.Count}");
}
```

See also:

- [sys.dm_pal_vm_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-vm-stats)
