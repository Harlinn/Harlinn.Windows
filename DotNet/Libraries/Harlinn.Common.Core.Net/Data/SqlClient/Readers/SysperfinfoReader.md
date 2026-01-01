# SysperfinfoReader

Overview

`SysperfinfoReader` wraps `sys.sysperfinfo` (legacy) and exposes performance counter data collected by SQL Server.

Reader SQL

```
SELECT
  s9.[object_name],
  s9.[counter_name],
  s9.[instance_name],
  s9.[cntr_value],
  s9.[cntr_type]
FROM
  [sys].[sysperfinfo] s9
```

Columns and interpretation

- `object_name` (string): Performance object name (category) such as "SQLServer:Buffer Manager" or other perf object.
- `counter_name` (string): Name of the performance counter.
- `instance_name` (string?): Instance name associated with the counter, may be NULL for instanceless counters.
- `cntr_value` (bigint): Counter value (counter-specific meaning, raw value depending on counter type).
- `cntr_type` (int): Counter type code indicating how to interpret the counter (e.g., raw count, rate, fraction).

How to interpret

- Counter semantics depend on `counter_name` and `cntr_type`; refer to Windows performance counter documentation or SQL Server perf counter docs.
- Use `instance_name` to disambiguate counters that are per-database or per-object.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysperfinfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysperfinfoReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Obj:{r.ObjectName} Counter:{r.CounterName} Instance:{r.InstanceName} Value:{r.CntrValue} Type:{r.CntrType}");
```

See also:

- [sys.sysperfinfo](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysperfinfo)
