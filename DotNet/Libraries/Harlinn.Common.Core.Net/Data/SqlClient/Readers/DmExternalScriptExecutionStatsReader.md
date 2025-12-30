# DmExternalScriptExecutionStatsReader — reference

Overview

`DmExternalScriptExecutionStatsReader` wraps `sys.dm_external_script_execution_stats` and reports counters for external script execution engines (R, Python) such as number of executions, failures or resource counters grouped by language.

Reader SQL

```
SELECT
  deses.[Language],
  deses.[counter_name],
  deses.[counter_value]
FROM
  [sys].[dm_external_script_execution_stats] deses
```

Columns and interpretation

- `Language` ? `Language` (string?)
  - External language name (e.g., `R`, `Python`) the counter applies to.

- `counter_name` ? `CounterName` (string)
  - Name of the statistic/counter (examples: `executions`, `failures`, `execution_time_ms`).

- `counter_value` ? `CounterValue` (long)
  - Numeric value of the counter.

How to interpret

- Use these counters to monitor usage and reliability of external script execution engines.
- Combine `counter_name` values per `Language` to build dashboards (e.g., executions per minute, failure rates).

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExternalScriptExecutionStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExternalScriptExecutionStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Lang:{s.Language} {s.CounterName} = {s.CounterValue}");
}
```

See also:

- [sys.dm_external_script_execution_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-external-script-execution-stats)
