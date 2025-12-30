# DmExecQueryTransformationStatsReader — reference

Overview

`DmExecQueryTransformationStatsReader` wraps `sys.dm_exec_query_transformation_stats` and exposes counts related to optimizer transformations (promises, substitutions, successes) for transformation rules.

Reader SQL

```
SELECT
  deqts.[Name],
  deqts.[promise_total],
  deqts.[promise_avg],
  deqts.[Promised],
  deqts.[built_substitute],
  deqts.[Succeeded]
FROM
  [sys].[dm_exec_query_transformation_stats] deqts
```

Columns and interpretation

- `Name` ? transformation rule name.
- `promise_total` ? total number of promise evaluations (long).
- `promise_avg` ? average promise value (double) for the rule; higher promise indicates stronger preference.
- `Promised` ? count of times the rule promised a valid alternative.
- `built_substitute` ? count of times a substitute plan/tree was built based on the transformation.
- `Succeeded` ? count of successful transformations applied.

How to interpret

- Use these counters to understand optimizer behavior and which transformation rules are applied frequently; `promise_avg` helps identify highly preferred rules.
- High `built_substitute` but low `Succeeded` might indicate transformations that are often generated but not chosen.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryTransformationStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var t = new DmExecQueryTransformationStatsReader(rdr, ownsReader:false);
while (t.Read())
{
    Console.WriteLine($"Rule:{t.Name} TotalPromises:{t.PromiseTotal} Avg:{t.PromiseAvg} Promised:{t.Promised} Built:{t.BuiltSubstitute} Succeeded:{t.Succeeded}");
}
```

See also:

- [sys.dm_exec_query_transformation_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-transformation-stats)
