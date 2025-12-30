# DmExecQueryOptimizerInfoReader — reference

Overview

`DmExecQueryOptimizerInfoReader` wraps `sys.dm_exec_query_optimizer_info` and exposes counters/metrics emitted by the query optimizer. This view provides insight into optimizer internals and heuristic counters used during optimization.

Reader SQL

```
SELECT
  deqoi.[Counter],
  deqoi.[Occurrence],
  deqoi.[Value]
FROM
  [sys].[dm_exec_query_optimizer_info] deqoi
```

Columns and interpretation

- `Counter` ? `Counter` (string)
  - Name of the optimizer counter or event. Examples include counts for rule triggers or heuristic thresholds.

- `Occurrence` ? `Occurrence` (long)
  - Number of times the counter occurred.

- `Value` ? `Value` (double?)
  - Numeric value associated with the counter (may be null for counters that are purely occurrence-based).

How to interpret

- Use these counters to understand optimizer behavior at runtime, such as how often certain transformation rules were applied or statistics sampling occurred.
- Correlate with query performance and plan choices to diagnose suboptimal plans driven by optimizer heuristics.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryOptimizerInfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var info = new DmExecQueryOptimizerInfoReader(rdr, ownsReader:false);
while (info.Read())
{
    Console.WriteLine($"Counter: {info.Counter} Occurrence: {info.Occurrence} Value: {info.Value}");
}
```

See also:

- [sys.dm_exec_query_optimizer_info](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-optimizer-info)
