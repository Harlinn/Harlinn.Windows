# DmOsPerformanceCountersReader — reference

Overview

`DmOsPerformanceCountersReader` wraps `sys.dm_os_performance_counters` and exposes OS and SQL Server performance counters enumerated in SQL Server.

Reader SQL

```
SELECT
  dopc.[object_name],
  dopc.[counter_name],
  dopc.[instance_name],
  dopc.[cntr_value],
  dopc.[cntr_type]
FROM
  [sys].[dm_os_performance_counters] dopc
```

Columns and interpretation

- `object_name` ? performance object category (e.g., "Buffer Manager").
- `counter_name` ? specific counter name under the object (e.g., "Page life expectancy").
- `instance_name` ? instance qualifier for counters that are instance-specific.
- `cntr_value` ? numeric value of the counter.
- `cntr_type` ? type code indicating how to interpret the counter (raw, rate, base, etc.).

How to interpret

- Use to read the same metrics exposed via Windows PerfMon but from within SQL Server. `cntr_type` indicates if the value is instantaneous or needs calculation with a base counter.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsPerformanceCountersReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmOsPerformanceCountersReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"{p.ObjectName} - {p.CounterName} ({p.InstanceName}): {p.CntrValue} Type:{p.CntrType}");
}
```

See also:

- [sys.dm_os_performance_counters](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-performance-counters)
